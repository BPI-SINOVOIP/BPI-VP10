/*
 * Copyright (c) 2022-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : EncTMG.c
 * Author        : Victor Jin
 * Date          : 2022-09-21
 * Description   : TMG Encoder decoding function.
 *
 * Record        :
 * V1.0, 2022-09-21, Victor Jin: Created file
 */


#include <Myproject.h>
#include <Encoder.h>

#if ENCODER_SEL_TMG_ENABLED > 0
/*=================================================================================
	Function Name	:	TMG_Encoder_Init(void)
	Description		:	TMG initial function
	Parameter		:	None.
=================================================================================*/
void TMG_Encoder_Init(void)
{
#if (SLRE_GPIO == PA && SLRE_PIN == PIN13)
	clr_csr(CMP_CR6, SFRCT2);	// 多摩川RE功能转移位: 00-PA12; 01-PA13
	set_csr(PH_SEL, SFRCT);		// 多摩川RE功能转移位: 10-PC0;  11-PA13
#elif (SLRE_GPIO == PC && SLRE_PIN == PIN0)
	set_csr(CMP_CR6, SFRCT2);	// 多摩川RE功能转移位: 00-PA12; 01-PA13
	clr_csr(PH_SEL, SFRCT);		// 多摩川RE功能转移位: 10-PC0;  11-PA13
#else
	clr_csr(CMP_CR6, SFRCT2);	// 多摩川RE功能转移位: 00-PA12; 01-PA13
	clr_csr(PH_SEL, SFRCT);		// 多摩川RE功能转移位: 10-PC0;  11-PA13
#endif 
	/****************************************************************
	初始化程序先发送一次Request，后面的中断都是先收状态标志位再发，
	在中断空闲时间用DMA接收数据避免中断中等待
	*****************************************************************/
	// buff的32位数据格式为 00(保留)+xx(EE内容)+xx(EE地址)+IDC_Code (其中EE内容和地址仅在ID等于6或D时有效)
	mcEncoder.TMG.TxRx_XRAM_Buf[0] = ID_0;
	write_csr(REG_DMA_BA, mcEncoder.TMG.TxRx_XRAM_Buf);			// DMA通道XRAM首地址配置
	write_csr(REG_DMA_CR, DMA_SF_Read);
	clr_csr(REG_DMA_CR, DMAEN);									// DMA使能
	clr_csr(REG_DMA_CR, DMAIE);									// DMA中断使能

	clr_csr(SF_CR, SF_EN);										// 相关模块使能
	clr_csr(SF_CR, SEND_REQ);									// 启动发送请求指令

	// 绝对式编码器自动触发周期选择 00 :每1个载波中断 01 :每2个载波中断
	// 绝对式编码器自动触发周期选择 10 :每4个载波中断 11 :每8个载波中断
#if DRV32K_ENABLE_SWITCH > 0
	clr_csr(DRV1_FCR5, ENCODER_STA_CYCLE1);
	set_csr(DRV1_FCR5, ENCODER_STA_CYCLE0);
#else
	clr_csr(DRV1_FCR5, ENCODER_STA_CYCLE1);
	clr_csr(DRV1_FCR5, ENCODER_STA_CYCLE0);
#endif
	
	write_csr(SF_BAUD, 0x0012); // 编码器串行接口波特率寄存器
}

/*=================================================================================
	Function Name	:	TMG_Encoder_Enable(void)
	Description		:	TMG enable function
	Parameter		:	None.
=================================================================================*/
void TMG_Encoder_Enable(void)
{
	mcEncoder.TMG.Multi = 0;
	clr_csr(CK_CR, BISSCKEN);								// 关闭BiSS模块时钟
	set_csr(CK_CR, SFCKEN);									// 打开TMG模块时钟
	
#ifdef MARE_PIN
	set_csr(MARE_GPIO, MARE_PIN);							// 拉高MA的RE脚
#endif

	if (mcEncoder.TypeSelect == ENCODER_SEL_TMG_ABS_SIN || mcEncoder.TypeSelect == ENCODER_SEL_TMG_ABS_MUL)
		mcEncoder.TMG.TxRx_XRAM_Buf[0] = ID_3;	
	else
		mcEncoder.TMG.TxRx_XRAM_Buf[0] = ID_0;
	set_csr(REG_DMA_CR, DMAEN);								// DMA使能
	set_csr(SF_CR, SF_EN);									// 相关模块使能
	set_csr(SF_CR, SF_AUTO_EN);								// 自动触发使能
}

/*=================================================================================
	Function Name	:	TMG_Encoder_Disable(void)
	Description		:	TMG disable function
	Parameter		:	None.
=================================================================================*/
void TMG_Encoder_Disable(void)
{
	clr_csr(CK_CR, SFCKEN);									// 关闭TMG模块时钟
	clr_csr(REG_DMA_CR, DMAEN);								// DMA去使能
	clr_csr(SF_CR, SF_AUTO_EN);								// 关闭自动触发使能
	clr_csr(SF_CR, SF_EN);									// 相关模块去使能
}


/*=================================================================================
Function Name	:	TMG_Encoder_Update(void)
Description		:	TMG update data length function
Parameter		:	None.
=================================================================================*/
void TMG_Encoder_Update(void)
{
	if (mcEncoder.TMG.ValidBits != usSRegHoldBuf[ENCVALIDBITS])
	{
		mcEncoder.TMG.ValidBits = usSRegHoldBuf[ENCVALIDBITS];
		mcEncoder.TMG.SingleHalf = 1 << (mcEncoder.TMG.ValidBits - 1);
	}
	mcEncoder.TMG.ZeroBits = usSRegHoldBuf[ENCZEROBITS];

	// Clear Multiturn value and error
	if (!GetReg(mcRegParam.DriveCtrl, CTRL_CLEARENC) && GetReg(usSRegHoldBuf[DRIVECTRL], CTRL_CLEARENC))
		mcEncoder.TMG.ClearMultiFlag = 1;
}


/*=================================================================================
    Function Name	:	TMG_Encoder_GetMultiAbsPos(void)
    Description		:	读单圈绝对值 + ENID + 多圈圈数 + ALMC(Encoder Err) (ID_3) 
						返回信息最全，所耗时间也最长，
						其中ALMC只有ID_3下才返回，是对SF(状态字)里故障码的详细解释
						带电插编码器ALMC会产生Err，故带电更换编码器类型后最好rst一次
	Parameter		:	None.
=================================================================================*/
uint16 TMG_Encoder_GetMultiAbsPos(uint32* pEncPos)
{
	uint8 EncStatus, EncError;
	uint32 EncSingle, EncMulti;
	uint16 CommStatus;
	uint16 errCode = 0;

	/* 等待data */
	CommStatus = read_csr(SF_SR);
//	ControlField = mcEncoder.TMG.TxRx_XRAM_Buf[0] & 0x000000ff;				// TMG返回的控制字CF
	EncStatus = (mcEncoder.TMG.TxRx_XRAM_Buf[0] & 0x0000ff00) >> 8;			// TMG返回的状态字SF
	EncSingle = (mcEncoder.TMG.TxRx_XRAM_Buf[0] & 0xffff0000) >> 16;		// TMG单圈绝对位置
	EncSingle += (mcEncoder.TMG.TxRx_XRAM_Buf[1] & 0x000000ff) << 16;
	EncMulti = (mcEncoder.TMG.TxRx_XRAM_Buf[1] & 0xffff0000) >> 16;			// TMG多圈值
	EncError = (mcEncoder.TMG.TxRx_XRAM_Buf[2] & 0x0000ff00) >> 8;			// TMG详细故障码解释 (仅ID_3下才有此信息)

	mcEncoder.EncLoopTime = 1;
	if (CommStatus & SF_DONE) // 成功接收编码器完成	
	{
		mcEncoder.TMG.TxRx_XRAM_Buf[0] = ID_3;		//读单圈绝对值 + ENID + 多圈圈数 + ALMC (Encoder Err)
		if (CommStatus & SF_SUC)	// 成功接收到编码器返回数据
		{
			mcEncoder.TMG.EncData = (EncMulti << mcEncoder.TMG.ValidBits) +
				(EncSingle >> mcEncoder.TMG.ZeroBits);	// 多圈绝对位置

			errCode = ((EncStatus & 0xC0) << 2) + EncError;
			mcEncoder.EncLoopTime = 0;
			clr_csr(SF_SR, SF_SUC);	//清接收成功标志位
		}
		else	// 未成功接收到编码器返回数据 - 通讯故障
		{
			// 检测CRC校验错误/帧同步错误/请求命令错误/请求超时错误
			errCode = (CommStatus << TMG_ERRSHIFT) & TMG_ERRMASK;
		}
		clr_csr(SF_SR, SF_DONE);	//清接收完成标志位
	}
	else	// 未成功接收到编码器返回数据 - 通讯故障
	{
		// 检测CRC校验错误/帧同步错误/请求命令错误/请求超时错误
		errCode = (CommStatus << TMG_ERRSHIFT) & TMG_ERRMASK;
	}
	
	*pEncPos = mcEncoder.TMG.EncData;
	return errCode;
}



/*=================================================================================
    Function Name	:	TMG_Encoder_GetSingleAbsPos(void)
    Description		:	读取单圈绝对值(ID_0) 只返回单圈绝对值和状态字等
	Parameter		:	None.
=================================================================================*/
uint16 TMG_Encoder_GetSingleAbsPos(uint32* pEncPos)
{
	uint8 EncStatus;
	uint32 EncSingle;
	uint16 CommStatus;
	uint16 errCode = 0;

	/* 等待data */
	CommStatus = read_csr(SF_SR);
//	mcEncoder.TMG.CF = mcEncoder.TMG.TxRx_XRAM_Buf[0] & 0x000000ff;			// TMG返回的控制字CF
	EncStatus = (mcEncoder.TMG.TxRx_XRAM_Buf[0] & 0x0000ff00) >> 8;		// TMG返回的状态字SF
	EncSingle = (mcEncoder.TMG.TxRx_XRAM_Buf[0] & 0xffff0000) >> 16;		// TMG单圈绝对位置
	EncSingle += (mcEncoder.TMG.TxRx_XRAM_Buf[1] & 0x000000ff) << 16;
	
	mcEncoder.EncLoopTime = 1;
	if (CommStatus & SF_DONE)
	{
		mcEncoder.TMG.TxRx_XRAM_Buf[0] = ID_0;		// 读单圈绝对值
		if (CommStatus & SF_SUC)	// 成功接收到编码器返回数据
		{
			mcEncoder.EncLoopTime = 0;
			mcEncoder.TMG.SingleLatch = mcEncoder.TMG.Single;
			mcEncoder.TMG.Single = EncSingle >> mcEncoder.TMG.ZeroBits;
			
			if (mcEncoder.TMG.Single > mcEncoder.TMG.SingleLatch &&
				mcEncoder.TMG.Single - mcEncoder.TMG.SingleLatch > mcEncoder.TMG.SingleHalf)
				mcEncoder.TMG.Multi--;
			else if (mcEncoder.TMG.SingleLatch > mcEncoder.TMG.Single &&
				mcEncoder.TMG.SingleLatch - mcEncoder.TMG.Single > mcEncoder.TMG.SingleHalf)
				mcEncoder.TMG.Multi++;

			mcEncoder.TMG.EncData = (mcEncoder.TMG.Multi << mcEncoder.TMG.ValidBits) + mcEncoder.TMG.Single;
			
			errCode = ((EncStatus & 0xC0) << 2) | ((EncStatus & 0x10) >> 2)
				|((EncStatus & 0x20) >> 4); // ca01 + ea01

			clr_csr(SF_SR, SF_SUC);	//清接收成功标志位
		}
		else	// 未成功接收到编码器返回数据 - 通讯故障
		{
			// 检测CRC校验错误/帧同步错误/请求命令错误/请求超时错误
			errCode = (CommStatus << TMG_ERRSHIFT) & TMG_ERRMASK;	
		}
		clr_csr(SF_SR, SF_DONE);	//清接收完成标志位
	}
	else	// 未成功接收到编码器返回数据 - 通讯故障
	{
		// 检测CRC校验错误/帧同步错误/请求命令错误/请求超时错误
		errCode = (CommStatus << TMG_ERRSHIFT) & TMG_ERRMASK;
	}
	
	*pEncPos = mcEncoder.TMG.EncData;
	return errCode;
}



/*=================================================================================
    Function Name	:	TMG_Encoder_GetMultiTurns(void)
    Description		:	读取多圈圈数值(ID_1) 只返回多圈数值和状态字等
	Parameter		:	None.
=================================================================================*/
uint16 TMG_Encoder_GetMultiTurns(uint32* pEncMulti)
{
	uint8 EncStatus;
	uint32 EncMulti;
	uint16 CommStatus;
	uint16 errCode = 0;

	/* 等待data */
	CommStatus = read_csr(SF_SR);
//	mcEncoder.TMG.CF = mcEncoder.TMG.TxRx_XRAM_Buf[0] & 0x000000ff;			// TMG返回的控制字CF
	EncStatus = (mcEncoder.TMG.TxRx_XRAM_Buf[0] & 0x0000ff00) >> 8;		// TMG返回的状态字SF
	EncMulti = (mcEncoder.TMG.TxRx_XRAM_Buf[0] & 0xffff0000) >> 16; // TMG多圈圈数数值

	mcEncoder.EncLoopTime = 1;
	if (CommStatus & SF_DONE)
	{
		mcEncoder.TMG.TxRx_XRAM_Buf[0] = ID_1;		// 读单圈绝对值
		if (CommStatus & SF_SUC)	// 成功接收到编码器返回数据
		{
			mcEncoder.EncLoopTime = 0;
			errCode = ((EncStatus & 0xC0) << 2) | ((EncStatus & 0x10) >> 2)
				|((EncStatus & 0x20) >> 4); // ca01 + ea01

			clr_csr(SF_SR, SF_SUC);	//清接收成功标志位
		}
		else // 未成功接收到编码器返回数据 - 通讯故障
		{
			// 检测CRC校验错误/帧同步错误/请求命令错误/请求超时错误
			errCode = (CommStatus << TMG_ERRSHIFT) & TMG_ERRMASK;
		}
		clr_csr(SF_SR, SF_DONE);	//清接收完成标志位
	}
	else	// 未成功接收到编码器返回数据 - 通讯故障
	{
		// 检测CRC校验错误/帧同步错误/请求命令错误/请求超时错误
		errCode = (CommStatus << TMG_ERRSHIFT) & TMG_ERRMASK;
	}

	*pEncMulti = EncMulti;
	return errCode;
}



/*=================================================================================
    Function Name	:	TMG_Encoder_Reset(uint8 Reset_ID)
    Description		:	编码器故障、单圈位置、多圈数值复位
						轴静止时传输10次此函数且间隔40us以上方能reset完成
	Parameter		:	Reset_ID
					 	ID_7 - 复位所有编码器故障
						ID_8 - 复位单圈绝对位置数值到0
						ID_C - 复位多圈圈数值(不复位单圈绝对值) + 所有编码器故障
=================================================================================*/
uint16 TMG_Encoder_Reset(uint8 Reset_ID)
{
	uint8 EncStatus;
	uint16 CommStatus;
	uint16 errCode = 0;

	/* 等待data */
	CommStatus = read_csr(SF_SR);
//	mcEncoder.TMG.CF = mcEncoder.TMG.TxRx_XRAM_Buf[0] & 0x000000ff;			// TMG返回的控制字CF
	EncStatus = (mcEncoder.TMG.TxRx_XRAM_Buf[0] & 0x0000ff00) >> 8;		// TMG返回的状态字SF
//	EncSingle = (mcEncoder.TMG.TxRx_XRAM_Buf[0] & 0xffff0000) >> 16;		// TMG单圈绝对位置
//	EncSingle += (mcEncoder.TMG.TxRx_XRAM_Buf[1] & 0x000000ff) << 16;
	
	mcEncoder.EncLoopTime = 1;
	if (CommStatus & SF_DONE)
	{
		mcEncoder.TMG.TxRx_XRAM_Buf[0] = Reset_ID;
		if (CommStatus & SF_SUC)	// 成功接收到编码器返回数据
		{
			mcEncoder.EncLoopTime = 0;
			errCode = ((EncStatus & 0xC0) << 2) | ((EncStatus & 0x10) >> 2)
				|((EncStatus & 0x20) >> 4); // ca01 + ea01

			clr_csr(SF_SR, SF_SUC);	//清接收成功标志位
		}
		else	// 未成功接收到编码器返回数据 - 通讯故障
		{
			// 检测CRC校验错误/帧同步错误/请求命令错误/请求超时错误
			errCode = (CommStatus << TMG_ERRSHIFT) & TMG_ERRMASK;
		}
		clr_csr(SF_SR, SF_DONE);	//清接收完成标志位
	}
	else	// 未成功接收到编码器返回数据 - 通讯故障
	{
		// 检测CRC校验错误/帧同步错误/请求命令错误/请求超时错误
		errCode = (CommStatus << TMG_ERRSHIFT) & TMG_ERRMASK;
	}
	
	return errCode;
}



/*=================================================================================
    Function Name	:	TMG_Encoder_ReadEEPROM(uint8 AddressField)
    Description		:	读取编码器内部自带EEPROM数值(ID_D)
	Parameter		:	AddressField - 准备读取的地址(ADF)
						实测17bit绝对值编码器可读地址范围为0~79，
						超过此范围则返回ID_3的数据，同时报请求命令错故障
=================================================================================*/
uint16 TMG_Encoder_ReadEEPROM(uint8 AddressField)
{
	uint16 CommStatus;
	uint16 errCode = 0;

	/* 等待data */
	CommStatus = read_csr(SF_SR);
//	mcEncoder.TMG.CF = mcEncoder.TMG.TxRx_XRAM_Buf[0] & 0x000000ff;			// TMG返回的控制字CF
//	mcEncoder.TMG.ADF = (mcEncoder.TMG.TxRx_XRAM_Buf[0] & 0x0000ff00) >> 8;		// TMG EEPROM读操作请求的地址字 Address field
//	mcEncoder.TMG.EDF = (mcEncoder.TMG.TxRx_XRAM_Buf[0] & 0x00ff0000) >> 16;	// TMG EEPROM读操作返回的数据字 EEPROM field

	mcEncoder.EncLoopTime = 1;
	if (CommStatus & SF_DONE)
	{
		// 读TMG编码器内置EEPROM, buff的32位数据格式为 00(保留)+xx(EE内容)+xx(EE地址)+IDC_Code (其中EE内容和地址仅在ID等于6或D时有效)
		mcEncoder.TMG.TxRx_XRAM_Buf[0] = AddressField << 8 | ID_D;
		if (CommStatus & SF_SUC)	// 成功接收到编码器返回数据
		{
			mcEncoder.EncLoopTime = 0;
			errCode = 0;	// 通讯成功则清通讯故障
			clr_csr(SF_SR, SF_SUC);	//清接收成功标志位
		}
		else	// 未成功接收到编码器返回数据 - 通讯故障
		{
			// 检测CRC校验错误/帧同步错误/请求命令错误/请求超时错误
			errCode = (CommStatus << TMG_ERRSHIFT) & TMG_ERRMASK;
		}
		clr_csr(SF_SR, SF_DONE);	//清接收完成标志位
	}
	else	// 未成功接收到编码器返回数据 - 通讯故障
	{
		// 检测CRC校验错误/帧同步错误/请求命令错误/请求超时错误
		errCode = (CommStatus << TMG_ERRSHIFT) & TMG_ERRMASK;
	}
	
	return errCode;
}



/*=================================================================================
    Function Name	:	TMG_Encoder_WriteEEPROM(uint8 AddressField, uint8 EepromField)
    Description		:	写编码器内部自带EEPROM(ID_6)
	Parameter		:	AddressField - 准备写的地址(ADF)
						EepromField  - 准备写的内容(EDF)
						注意！写eeprom需要一定的时间，故在发送完写请求后返回的数据
						可能因为ADF的busy位使读出的EDF为0，所以通常在发送完写请求后
						再发送读请求，以确保写eeprom操作完成.
=================================================================================*/
uint16 TMG_Encoder_WriteEEPROM(uint8 AddressField, uint8 EepromField)
{
	uint16 CommStatus;
	uint16 errCode = 0;

	/* 等待data */
	CommStatus = read_csr(SF_SR);		// 调试用，打印TMG外设状态寄存器
//	mcEncoder.TMG.CF = mcEncoder.TMG.TxRx_XRAM_Buf[0] & 0x000000ff;			// TMG返回的控制字CF
//	mcEncoder.TMG.ADF = (mcEncoder.TMG.TxRx_XRAM_Buf[0] & 0x0000ff00) >> 8;		// TMG EEPROM读操作请求的地址字 Address field
//	mcEncoder.TMG.EDF = (mcEncoder.TMG.TxRx_XRAM_Buf[0] & 0x00ff0000) >> 16;	// TMG EEPROM读操作返回的数据字 EEPROM field

	
	mcEncoder.EncLoopTime = 1;
	if (CommStatus & SF_DONE)
	{
		// 读TMG编码器内置EEPROM, buff的32位数据格式为 00(保留)+xx(EE内容)+xx(EE地址)+IDC_Code (其中EE内容和地址仅在ID等于6或D时有效)
		mcEncoder.TMG.TxRx_XRAM_Buf[0] = EepromField << 16 | AddressField << 8 | ID_6;
		if (CommStatus & SF_SUC)	// 成功接收到编码器返回数据
		{
			mcEncoder.EncLoopTime = 0;
			errCode = 0;	// 通讯成功则清通讯故障
			clr_csr(SF_SR, SF_SUC);	//清接收成功标志位
		}
		else	// 未成功接收到编码器返回数据 - 通讯故障
		{
			// 检测CRC校验错误/帧同步错误/请求命令错误/请求超时错误
			errCode = (CommStatus << TMG_ERRSHIFT) & TMG_ERRMASK;
		}
		clr_csr(SF_SR, SF_DONE);	//清接收完成标志位
	}
	else	// 未成功接收到编码器返回数据 - 通讯故障
	{
		// 检测CRC校验错误/帧同步错误/请求命令错误/请求超时错误
		errCode = (CommStatus << TMG_ERRSHIFT) & TMG_ERRMASK;
	}

	return errCode;
}
#endif
