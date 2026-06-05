/*
 * Copyright (c) 2022-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : EncBISS.c
 * Author        : Summer
 * Date          : 2022-09-21
 * Description   : BiSS Encoder decoding function.
 *
 * Record        :
 * V1.0, 2022-09-21, Summer: Created file
 */


#include <Myproject.h>
#include <Encoder.h>


#if ENCODER_SEL_BISS_ENABLED > 0
/*=================================================================================
    Function Name	:	BiSS_Encoder_Init(void)
    Description		:	BiSS initial function
	Parameter		:	None.
=================================================================================*/
void BiSS_Encoder_Init(void)
{
	clr_csr(PH_SEL, DTCT);				// 0: MA-PA10;SL-PA11; 1: MA-PA13;SL-PA14;
	write_csr(BISS_STATE, 0);			// Clear Biss State Register
	write_csr(BISS_CLK_CNT, 7);			// 0 = 12 MHz; 1 = 6 MHz; 2 = 4 MHz; 3 = 3 MHz	//48M时钟，24M/(N+1)
	write_csr(BISS_OVERTIME_CNT, 400);		// OverTime Register: 400 * MA Clk
	write_csr(BISS_DATA_LEN, 30);		// BiSS Data Length
	
	// 绝对式编码器自动触发周期选择 00 :每1个载波中断 01 :每2个载波中断
	// 绝对式编码器自动触发周期选择 10 :每4个载波中断 11 :每8个载波中断
#if DRV32K_ENABLE_SWITCH > 0
	clr_csr(DRV1_FCR5, ENCODER_STA_CYCLE1);
	set_csr(DRV1_FCR5, ENCODER_STA_CYCLE0);
#else
	clr_csr(DRV1_FCR5, ENCODER_STA_CYCLE1);
	clr_csr(DRV1_FCR5, ENCODER_STA_CYCLE0);
#endif
}

/*=================================================================================
	Function Name	:	BiSS_Encoder_Enable(void)
	Description		:	BiSS enable function
	Parameter		:	None.
=================================================================================*/
void BiSS_Encoder_Enable(void)
{
	mcEncoder.BiSS.Multi = 0;
	clr_csr(CK_CR, SFCKEN);									// 关闭TMG模块时钟
	set_csr(CK_CR, BISSCKEN);								// 打开BiSS模块时钟

#ifdef SLRE_PIN
	clr_csr(SLRE_GPIO, SLRE_PIN);							// 拉低SL的RE脚
#endif
#ifdef MARE_PIN
	set_csr(MARE_GPIO, MARE_PIN);							// 拉高MA的RE脚
#endif

	set_csr(BISS_STATE, BISS_AUTO_EN);						// 自动触发使能
	set_csr(BISS_STATE, BISSEN);
//	set_csr(BISS_STATE, BISSBUSY);							// BiSS Transfer Start+
}

/*=================================================================================
	Function Name	:	BiSS_Encoder_Disable(void)
	Description		:	BiSS disable function
	Parameter		:	None.
=================================================================================*/
void BiSS_Encoder_Disable(void)
{
	clr_csr(CK_CR, BISSCKEN);									// 关闭BiSS模块时钟
#ifdef SLRE_PIN
	clr_csr(SLRE_GPIO, SLRE_PIN);
#endif
	clr_csr(BISS_STATE, BISSEN);
	clr_csr(BISS_STATE, BISS_AUTO_EN);							// 关闭自动触发使能
	clr_csr(BISS_STATE, BISSBUSY);								// BiSS Transfer Start+
}

/*=================================================================================
Function Name	:	BiSS_Encoder_Update(void)
Description		:	BiSS update data length and MA frequency function
Parameter		:	None.
=================================================================================*/
void BiSS_Encoder_Update(void)
{
	int16 temp;
		
	if (mcEncoder.BiSS.DataBits != usSRegHoldBuf[ENCDATABITS])
	{
		mcEncoder.BiSS.DataBits = usSRegHoldBuf[ENCDATABITS];
		write_csr(BISS_DATA_LEN, mcEncoder.BiSS.DataBits + BISS_ERRSIZE);
	}

	if (mcEncoder.BiSS.ValidBits != usSRegHoldBuf[ENCVALIDBITS])
	{
		mcEncoder.BiSS.ValidBits = usSRegHoldBuf[ENCVALIDBITS];
		mcEncoder.BiSS.DataMask = (1 << (mcEncoder.BiSS.ValidBits + mcEncoder.BiSS.ZeroBits)) - 1;
		mcEncoder.BiSS.SingleHalf = 1 << (mcEncoder.BiSS.ValidBits - 1);
	}

	if (mcEncoder.BiSS.ZeroBits != usSRegHoldBuf[ENCZEROBITS])
	{
		mcEncoder.BiSS.ZeroBits = usSRegHoldBuf[ENCZEROBITS];
		mcEncoder.BiSS.DataMask = (1 << (mcEncoder.BiSS.ValidBits + mcEncoder.BiSS.ZeroBits)) - 1;
	}

	if (mcEncoder.BiSS.ClockFreq != usSRegHoldBuf[ENCCLKFREQ])
	{
		mcEncoder.BiSS.ClockFreq = usSRegHoldBuf[ENCCLKFREQ];
		write_csr(BISS_CLK_CNT, mcEncoder.BiSS.ClockFreq);
	}
}

/*=================================================================================
	Function Name	:	BiSS_Encoder_GetPos(void)
	Description		:	get biss data and state, then start a new biss request.
	Parameter		:	None.
=================================================================================*/
uint16 BiSS_Encoder_GetPos(uint32* pEncPos) //获取绝对值编码器位置的函数
{
	uint16 EncState;										// BiSS State
	uint32 SDataL;											// BiSS Data low 32 bit
	uint32 SDataH;											// BiSS Data high 32 bit
	uint16 errCode = 0;	

	EncState = read_csr(BISS_STATE);		//读取BISS_STATE状态寄存器
	SDataL = read_csr(BISS_SDATAL);//读取BISS数据
	SDataH = read_csr(BISS_SDATAH);

	if (EncState & BISSENDIF)				//如果数据传输完成标志位
	{
		write_csr(BISS_STATE, BISSEN);				//这里需要给BISS_STATE寄存器中的使能位拉高，其他位拉低
		set_csr(BISS_STATE, BISSBUSY);	// BiSS Transfer Start

		if (EncState & (BISSCRCERR | BISSOTIF)) // Timeout or CRC error exists
		{
			errCode = (EncState & BISS_CRCTOUTMASK) >> BISS_ERRSHIFT;
		}
		else
		{
			errCode = (EncState & BISS_ERRMASK) >> BISS_ERRSHIFT;

			mcEncoder.BiSS.SingleLatch = mcEncoder.BiSS.Single;
			mcEncoder.BiSS.Single = ((SDataH << (32 - (BISS_ERRSIZE + mcEncoder.BiSS.ZeroBits)))
				+(SDataL >> (BISS_ERRSIZE + mcEncoder.BiSS.ZeroBits))) & mcEncoder.BiSS.DataMask;
			
			if (mcEncoder.BiSS.Single > mcEncoder.BiSS.SingleLatch &&
				mcEncoder.BiSS.Single - mcEncoder.BiSS.SingleLatch > mcEncoder.BiSS.SingleHalf)
				mcEncoder.BiSS.Multi--;
			else if (mcEncoder.BiSS.SingleLatch > mcEncoder.BiSS.Single &&
				mcEncoder.BiSS.SingleLatch - mcEncoder.BiSS.Single > mcEncoder.BiSS.SingleHalf)
				mcEncoder.BiSS.Multi++;

			mcEncoder.BiSS.EncData = (mcEncoder.BiSS.Multi << mcEncoder.BiSS.ValidBits) + mcEncoder.BiSS.Single;
		}
	}

	*pEncPos = mcEncoder.BiSS.EncData;
	return errCode;
}
#endif // #if ENCODER_SEL_BISS_ENABLED > 0