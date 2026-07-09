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
/*---------------------------------------------------------------------------
 * Name		:	BiSS_Encoder_Init
 * Input	:	No
 * Output	:	No
 * Description:	BiSS encoder initialization
 *---------------------------------------------------------------------------*/
void BiSS_Encoder_Init(void)
{
	clr_csr(PH_SEL, DTCT);				// 0: MA-PA10;SL-PA11; 1: MA-PA13;SL-PA14;
	write_csr(BISS_STATE, 0);			// Clear Biss State Register
	write_csr(BISS_CLK_CNT, 7);			// 0 = 12 MHz; 1 = 6 MHz; 2 = 4 MHz; 3 = 3 MHz	//48M clock, 24M/(N+1)
	write_csr(BISS_OVERTIME_CNT, 400);		// OverTime Register: 400 * MA Clk
	write_csr(BISS_DATA_LEN, 30);		// BiSS Data Length
	
	// Absolute encoder auto-trigger cycle selection 00 : every 1 carrier interrupt 01 : every 2 carrier interrupts
	// Absolute encoder auto-trigger cycle selection 10 : every 4 carrier interrupts 11 : every 8 carrier interrupts
#if DRV32K_ENABLE_SWITCH > 0
	clr_csr(DRV1_FCR5, ENCODER_STA_CYCLE1);
	set_csr(DRV1_FCR5, ENCODER_STA_CYCLE0);
#else
	clr_csr(DRV1_FCR5, ENCODER_STA_CYCLE1);
	clr_csr(DRV1_FCR5, ENCODER_STA_CYCLE0);
#endif
}


/*---------------------------------------------------------------------------
 * Name		:	BiSS_Encoder_Enable
 * Input	:	No
 * Output	:	No
 * Description:	BiSS encoder enable
 *---------------------------------------------------------------------------*/
void BiSS_Encoder_Enable(void)
{
	mcEncoder.BiSS.Multi = 0;
	clr_csr(CK_CR, SFCKEN);									// Turn off TMG module clock
	set_csr(CK_CR, BISSCKEN);								// Turn on BiSS module clock

#ifdef SLRE_PIN
	clr_csr(SLRE_GPIO, SLRE_PIN);							// Pull down RE pin of SL
#endif
#ifdef MARE_PIN
	set_csr(MARE_GPIO, MARE_PIN);							// Pull up RE pin of MA
#endif

	set_csr(BISS_STATE, BISS_AUTO_EN);						// Auto-trigger enable
	set_csr(BISS_STATE, BISSEN);
//	set_csr(BISS_STATE, BISSBUSY);							// BiSS Transfer Start+
}


/*---------------------------------------------------------------------------
 * Name		:	BiSS_Encoder_Disable
 * Input	:	No
 * Output	:	No
 * Description:	BiSS encoder disable
 *---------------------------------------------------------------------------*/
void BiSS_Encoder_Disable(void)
{
	clr_csr(CK_CR, BISSCKEN);									// Turn off BiSS module clock
#ifdef SLRE_PIN
	clr_csr(SLRE_GPIO, SLRE_PIN);
#endif
	clr_csr(BISS_STATE, BISSEN);
	clr_csr(BISS_STATE, BISS_AUTO_EN);							// Disable auto-trigger
	clr_csr(BISS_STATE, BISSBUSY);								// BiSS Transfer Start+
}


/*---------------------------------------------------------------------------
 * Name		:	BiSS_Encoder_Update
 * Input	:	No
 * Output	:	No
 * Description:	BiSS encoder parameter update, such as data length and MA frequency
 *---------------------------------------------------------------------------*/
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


/*---------------------------------------------------------------------------
 * Name		:	BiSS_Encoder_GetPos
 * Input	:	*pEncPos - Encoder value
 * Output	:	Encoder error state
 * Description:	Get BiSS encoder value, get biss data and state, then start a new biss request.
 *---------------------------------------------------------------------------*/
uint16 BiSS_Encoder_GetPos(uint32* pEncPos)
{
	uint16 EncState;										// BiSS State
	uint32 SDataL;											// BiSS Data low 32 bit
	uint32 SDataH;											// BiSS Data high 32 bit
	uint16 errCode = 0;	

	EncState = read_csr(BISS_STATE);		// Read BISS_STATE status register
	SDataL = read_csr(BISS_SDATAL);			// Read BISS data
	SDataH = read_csr(BISS_SDATAH);

	if (EncState & BISSENDIF)				// If data transmission complete flag
	{
		write_csr(BISS_STATE, BISSEN);		// Here need to pull high the enable bit in the BISS_STATE register and pull other bits low
		set_csr(BISS_STATE, BISSBUSY);		// BiSS Transfer Start

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