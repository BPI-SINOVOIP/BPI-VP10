/*
 * Copyright (c) 2022-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : Encoder.c
 * Author        : Victor Jin
 * Date          : 2022-09-21
 * Description   : Encoder decoding function.
 *
 * Record        :
 * V1.0, 2022-09-21, Victor Jin: Created file
 */


#include <Myproject.h>
#include <Encoder.h>

Encoder_TypeDef mcEncoder;

/*=================================================================================
    Function Name	:	Encoder_Init(void)
    Description		:	编码器初始化函数，包括根据不同编码器类型自动选择初始化语句
	Parameter		:	None.
=================================================================================*/
void Encoder_Init(void)
{
	memset(&mcEncoder, 0, sizeof(Encoder_TypeDef));

#if ENCODER_SEL_ABZ_ENABLED > 0 || FUNC_PROBE_ENABLED > 0 || FUNC_PCOM_ENABLED > 0
	Timer2_Init(); // QEP增量编码器 ABZ+绝对值+霍尔（主）
	Timer5_Init(); // QEP增量编码器 ABZ+霍尔（副）
#endif

#if ENCODER_SEL_HALL_ENABLED > 0
	HallPinInit();
#endif

#if ENCODER_SEL_TMG_ENABLED > 0
	TMG_Encoder_Init();
#endif

#if ENCODER_SEL_BISS_ENABLED > 0
	BiSS_Encoder_Init();
#endif
	
#if ENCODER_SEL_SPI_ENABLED > 0
	SPI_Encoder_Init();
#endif
	
#if ENCODER_SEL_SPI2_ENABLED > 0
	SPI2_Encoder_Init();
#endif

#if ENCODER_SEL_PWM_ENABLED > 0
	PWM_Encoder_Init();
#endif
	
#ifdef SLRE_PIN
	set_csr(SLRE_OE, SLRE_PIN);
	clr_csr(SLRE_PU, SLRE_PIN);							// 关闭上拉
#endif
#ifdef MARE_PIN
	set_csr(MARE_OE, MARE_PIN);
	clr_csr(MARE_PU, MARE_PIN);							// 关闭上拉
#endif
	
	// 根据当前编码器类型做使能
	Encoder_Switch();
}


/*=================================================================================
    Function Name	:	Encoder_Switch(void)
    Description		:	编码器使能函数，根据不同编码器类型自动选择使能去使能语句
	Parameter		:	None.
=================================================================================*/
void Encoder_Switch(void)
{
#if ENCODER_SEL_ABZ_ENABLED > 0
	if (mcEncoder.TypeSelect == ENCODER_SEL_ABZ ||
		mcEncoder.TypeSelect == ENCODER_SEL_ABZ_HALL) // QEP增量编码器
	{
		Timer2_Enable();
#ifdef SLRE_PIN
		clr_csr(SLRE_GPIO, SLRE_PIN);							// 拉低SL的RE脚
#endif
#ifdef MARE_PIN
		clr_csr(MARE_GPIO, MARE_PIN);							// 拉低MA的RE脚
#endif
		
		if (mcEncoder.LoadTypeSelect != ENCODER2_SEL_ABZ &&
			mcEncoder.LoadTypeSelect != ENCODER2_SEL_ABZ_HALL) // QEP增量编码器
		{
			Timer5_Disable();
		}
	}
	else if (mcEncoder.TypeSelect == ENCODER2_SEL_ABZ ||
		mcEncoder.TypeSelect == ENCODER2_SEL_ABZ_HALL) // QEP增量编码器
	{
		Timer5_Enable();
		
		if (mcEncoder.LoadTypeSelect != ENCODER_SEL_ABZ &&
			mcEncoder.LoadTypeSelect != ENCODER_SEL_ABZ_HALL) // QEP增量编码器
		{
			Timer2_Disable();
		}
	}
	else
	{
		if (mcEncoder.LoadTypeSelect == ENCODER2_SEL_ABZ ||
			mcEncoder.LoadTypeSelect == ENCODER2_SEL_ABZ_HALL) // QEP增量编码器
		{
			Timer2_Disable();
		}
		else if (mcEncoder.LoadTypeSelect == ENCODER_SEL_ABZ ||
			mcEncoder.LoadTypeSelect == ENCODER_SEL_ABZ_HALL) // QEP增量编码器
		{
			Timer5_Disable();
		}
		else
		{
			Timer2_Disable();
			Timer5_Disable();
		}
	}
#endif

#if ENCODER_SEL_TMG_ENABLED > 0
	if (mcEncoder.TypeSelect == ENCODER_SEL_TMG_ABS_SIN || // TMG单圈绝对值解码
		mcEncoder.TypeSelect == ENCODER_SEL_TMG_ABS_MUL || // TMG多圈绝对值解码
		mcEncoder.TypeSelect == ENCODER_SEL_TMG_INC)// TMG增量式解码
	{
		TMG_Encoder_Enable();
	}
	else
	{
		TMG_Encoder_Disable();
	}
#endif

#if ENCODER_SEL_BISS_ENABLED > 0
	if (mcEncoder.TypeSelect == ENCODER_SEL_BISS)// BiSS编码器
	{
		memset(&mcEncoder.BiSS, 0, sizeof(BiSS_TypeDef));
		BiSS_Encoder_Enable();
	}
	else
	{
		BiSS_Encoder_Disable();
	}
#endif
	
#if ENCODER_SEL_SPI_ENABLED > 0
	if (mcEncoder.TypeSelect == ENCODER_SEL_ABS_CUSTOM1)// SPI编码器
	{
		SPI_Encoder_Enable(ENCSEL_MOTOR);
	}
	else
	{
		if (mcEncoder.LoadTypeSelect != ENCODER_SEL_ABS_CUSTOM1)
			SPI_Encoder_Disable();
	}
#endif
	
#if ENCODER_SEL_SPI2_ENABLED > 0
	if (mcEncoder.TypeSelect == ENCODER_SEL_ABS_CUSTOM2)// SPI2编码器
	{
		SPI2_Encoder_Enable(ENCSEL_MOTOR);
	}
	else
	{
		if (mcEncoder.LoadTypeSelect != ENCODER_SEL_ABS_CUSTOM2)
			SPI2_Encoder_Disable();
	}
#endif
}
/*=================================================================================
    Function Name	:	
    Description		:	
	Parameter		:	None.
=================================================================================*/
void Encoder_Switch_LoadSide(void)
{
#if ENCODER_SEL_ABZ_ENABLED > 0
	if (mcEncoder.LoadTypeSelect == ENCODER2_SEL_ABZ ||
		mcEncoder.LoadTypeSelect == ENCODER2_SEL_ABZ_HALL) // QEP增量编码器
	{
		Timer5_Enable();
		
		if (mcEncoder.TypeSelect != ENCODER_SEL_ABZ &&
			mcEncoder.TypeSelect != ENCODER_SEL_ABZ_HALL) // QEP增量编码器
		{
			Timer2_Disable();
		}
	}
	else if (mcEncoder.LoadTypeSelect == ENCODER_SEL_ABZ ||
		mcEncoder.LoadTypeSelect == ENCODER_SEL_ABZ_HALL) // QEP增量编码器
	{
		Timer2_Enable();
#ifdef SLRE_PIN
		clr_csr(SLRE_GPIO, SLRE_PIN);							// 拉低SL的RE脚
#endif
#ifdef MARE_PIN
		clr_csr(MARE_GPIO, MARE_PIN);							// 拉低MA的RE脚
#endif

		if (mcEncoder.TypeSelect != ENCODER2_SEL_ABZ &&
			mcEncoder.TypeSelect != ENCODER2_SEL_ABZ_HALL) // QEP增量编码器
		{
			Timer5_Disable();
		}

	}
	else
	{
		if (mcEncoder.TypeSelect == ENCODER2_SEL_ABZ ||
			mcEncoder.TypeSelect == ENCODER2_SEL_ABZ_HALL) // QEP增量编码器
		{
			Timer2_Disable();
		}
		else if (mcEncoder.TypeSelect == ENCODER_SEL_ABZ ||
			mcEncoder.TypeSelect == ENCODER_SEL_ABZ_HALL) // QEP增量编码器
		{
			Timer5_Disable();
		}
		else
		{
			Timer2_Disable();
			Timer5_Disable();
		}
	}
#endif
	
#if ENCODER_SEL_SPI_ENABLED > 0
	if (mcEncoder.LoadTypeSelect == ENCODER_SEL_ABS_CUSTOM1)// SPI编码器
	{
		SPI_Encoder_Enable(ENCSEL_LOAD);
	}
	else
	{
		if (mcEncoder.TypeSelect != ENCODER_SEL_ABS_CUSTOM1)
			SPI_Encoder_Disable();
	}
#endif
	
#if ENCODER_SEL_SPI2_ENABLED > 0
	if (mcEncoder.LoadTypeSelect == ENCODER_SEL_ABS_CUSTOM2)// SPI2编码器
	{
		SPI2_Encoder_Enable(ENCSEL_LOAD);
	}
	else
	{
		if (mcEncoder.TypeSelect != ENCODER_SEL_ABS_CUSTOM2)
			SPI2_Encoder_Disable();
	}
#endif

#if ENCODER_SEL_PWM_ENABLED > 0
	if (mcEncoder.LoadTypeSelect == ENCODER_SEL_ABS_CUSTOM1)// PWM编码器
	{
		PWM_Encoder_Enable();
	}
	else
	{
		PWM_Encoder_Disable();
	}
#endif

}
/*=================================================================================
Function Name	:	Encoder_Update(void)
Description		:	Encoder update data length function
Parameter		:	None.
=================================================================================*/
void Encoder_Update(void)
{
	uint32 EncoderComp_DelayTs = 0;
		
	if (mcEncoder.TypeSelect != (int16)usSRegHoldBuf[ENCTYPE])
	{
		mcEncoder.TypeSelect = (int16)usSRegHoldBuf[ENCTYPE];  // Motor-Side encoder type
		Encoder_Switch();
	}

	
	if (mcEncoder.LoadTypeSelect != (int16)usSRegHoldBuf[SFBENCTYPE])
	{
		mcEncoder.LoadTypeSelect = (int16)usSRegHoldBuf[SFBENCTYPE];  // Load-Side encoder type
		Encoder_Switch_LoadSide();
	}
	
	switch (mcEncoder.TypeSelect)
	{
#if ENCODER_SEL_ABZ_ENABLED > 0
	case ENCODER_SEL_ABZ: // QEP增量编码器
	case ENCODER_SEL_ABZ_HALL:
		if ((uint16)mcEncoder.AqbFilt != usSRegHoldBuf[AQBFILT])
		{
			mcEncoder.AqbFilt = usSRegHoldBuf[AQBFILT];
			Timer2_Filter_Update(usSRegHoldBuf[AQBFILT]);
		}
		EncoderComp_DelayTs = ELEANG_DELAYTS;
		// M/MT法选择  0:M法  1:MT法
		if (GetReg(usSRegHoldBuf[DRIVESWITCH], SW_MTMODE))
		{
			set_csr(DRV1_FCR4, MMT_SEL);			
		}
		else
		{
			clr_csr(DRV1_FCR4, MMT_SEL);
		}
		break;
#endif

#if ENCODER_SEL_TMG_ENABLED > 0
	case ENCODER_SEL_TMG_ABS_SIN: // TMG单圈绝对值解码
	case ENCODER_SEL_TMG_ABS_MUL: // TMG多圈绝对值解码
	case ENCODER_SEL_TMG_INC: // TMG增量式解码
		TMG_Encoder_Update();
		clr_csr(DRV1_FCR4, MMT_SEL);			// M/MT法选择  0:M法  1:MT法
		break;
#endif

#if ENCODER_SEL_BISS_ENABLED > 0
	case ENCODER_SEL_BISS: // BiSS编码器
		BiSS_Encoder_Update();
		EncoderComp_DelayTs = (ELEANG_DELAYTS + BISS_DELAYTS) >> 5;
		clr_csr(DRV1_FCR4, MMT_SEL);			// M/MT法选择  0:M法  1:MT法
		break;
#endif
		
#if ENCODER_SEL_SPI_ENABLED > 0
	case ENCODER_SEL_ABS_CUSTOM1: // SPI编码器
		SPI_Encoder_Update();
		EncoderComp_DelayTs = ELEANG_DELAYTS; // (ELEANG_DELAYTS + BISS_DELAYTS) >> 5;
		clr_csr(DRV1_FCR4, MMT_SEL);			// M/MT法选择  0:M法  1:MT法
		break;
#endif
		
#if ENCODER_SEL_SPI2_ENABLED > 0
	case ENCODER_SEL_ABS_CUSTOM2: // SPI2编码器
		SPI2_Encoder_Update();
		EncoderComp_DelayTs = ELEANG_DELAYTS; // (ELEANG_DELAYTS + BISS_DELAYTS) >> 5;
		clr_csr(DRV1_FCR4, MMT_SEL);			// M/MT法选择  0:M法  1:MT法
		break;
#endif
		
//#if ENCODER_SEL_PWM_ENABLED > 0
//	case ENCODER_SEL_ABS_CUSTOM1: // SPI编码器
//		PWM_Encoder_Update();
//		EncoderComp_DelayTs = ELEANG_DELAYTS; // (ELEANG_DELAYTS + BISS_DELAYTS) >> 5;
//		clr_csr(DRV1_FCR4, MMT_SEL);			// M/MT法选择  0:M法  1:MT法
//		break;
//#endif

	default:
		EncoderComp_DelayTs = 0;
		clr_csr(DRV1_FCR4, MMT_SEL);			// M/MT法选择  0:M法  1:MT法
		break;
	}
	
#if FUNC_ENCODERCOMP_ENABLED
	if (GetReg(usSRegHoldBuf[DRIVEMODE], MODE_MOTORTYPE)) // Rotary Motor
	{
		mcEncoder.DelayComCoef = (uint64)(1 << (2 + ENCCOMP_SHIFT)) * 3 * (uint32)usSRegHoldBuf[MOTORMAXSPEED] * EncoderComp_DelayTs * (uint32)usSRegHoldBuf[POLES] / 1000000;
	}
	else
	{
		mcEncoder.DelayComCoef = (uint64)(1 << (2 + ENCCOMP_SHIFT)) * (uint32)usSRegHoldBuf[MOTORMAXSPEED] * EncoderComp_DelayTs / 1000
			/ (((int32)usSRegHoldBuf[PITCH_H] << 16) | (uint16)usSRegHoldBuf[PITCH_L]);
	}

	mcEncoder.ValueMax = ((uint32)10 << 14) / (uint32)usSRegHoldBuf[MOTORMAXSPEED];
#endif

}


/*=================================================================================
Function Name	:	Encoder_GetPos(void)
Description		:	编码器获取读数函数，根据不同编码器类型自动选择使能去使能语句
Parameter		:	*pEncPos - return Encoder value
					*pEncMulti - High 32 bits
					*pEncDiff - return Encoder difference value of adjacent time
					*pErrCode - return Encoder error
=================================================================================*/
void Encoder_GetPos(int32* pEncPos, int32* pEncMulti, int16* pEncDiff, uint16* pErrCode)
{
	int32 EncDiff;										    // 前后两个时刻的编码器差值

	mcEncoder.EncPosLatch = mcEncoder.EncPos;
	
	switch (mcEncoder.TypeSelect)
	{
#if ENCODER_SEL_ABZ_ENABLED > 0
	case ENCODER_SEL_ABZ: // QEP增量编码器
	case ENCODER_SEL_ABZ_HALL:
		mcEncoder.EncPos = read_csr(TIM2_QEP_MNUM);
		mcEncoder.ErrCode = 0;
		break;
	case ENCODER2_SEL_ABZ: // QEP增量编码器
	case ENCODER2_SEL_ABZ_HALL:
		mcEncoder.EncPos = read_csr(TIM5_QEP_MNUM);
		mcEncoder.ErrCode = 0;
		break;
#endif

#if ENCODER_SEL_TMG_ENABLED > 0
	case ENCODER_SEL_TMG_ABS_SIN: // TMG单圈绝对值解码
		mcEncoder.ErrCode = TMG_Encoder_GetSingleAbsPos(&mcEncoder.EncPos);
		break;

	case ENCODER_SEL_TMG_ABS_MUL: // TMG多圈绝对值解码
		if (mcEncoder.TMG.ClearMultiFlag == 0)
		{
			mcEncoder.ErrCode = TMG_Encoder_GetMultiAbsPos(&mcEncoder.EncPos);
		}
		else
		{
			TMG_Encoder_Reset(ID_C);
			mcEncoder.TMG.ClearMultiCounter++;
			if (mcEncoder.TMG.ClearMultiCounter == 16)
			{
				mcEncoder.TMG.ClearMultiCounter = 0;
				mcEncoder.TMG.ClearMultiFlag = 0;
			}
		}
		break;

	case ENCODER_SEL_TMG_INC: // TMG增量式解码
		mcEncoder.ErrCode = TMG_Encoder_GetSingleAbsPos(&mcEncoder.EncPos);
		break;
#endif

#if ENCODER_SEL_BISS_ENABLED > 0
	case ENCODER_SEL_BISS: // BiSS编码器
		mcEncoder.ErrCode = BiSS_Encoder_GetPos(&mcEncoder.EncPos);
		break;
#endif
		
#if ENCODER_SEL_HALLSONLY_ENABLED > 0
	case ENCODER_SEL_HALLS_ONLY: // 纯霍尔
		mcEncoder.EncPos = UpdateHallsOnlyAngle();
		mcEncoder.ErrCode = 0;
		break;
#endif
	
#if ENCODER_SEL_SPI_ENABLED > 0
	case ENCODER_SEL_ABS_CUSTOM1: // SPI编码器
		mcEncoder.ErrCode = SPI_Encoder_GetPos(&mcEncoder.EncPos);
		break;
#endif
		
#if ENCODER_SEL_SPI2_ENABLED > 0
	case ENCODER_SEL_ABS_CUSTOM2: // SPI2编码器
		mcEncoder.ErrCode = SPI2_Encoder_GetPos(&mcEncoder.EncPos);
		break;
#endif
		
	default:
		mcEncoder.EncPos = 0;
		mcEncoder.ErrCode = 0;
		break;
	}

	// 外环编码器更新位置
	switch (mcEncoder.LoadTypeSelect)
	{
#if ENCODER_SEL_ABZ_ENABLED > 0
	case ENCODER_SEL_ABZ: // QEP增量编码器
	case ENCODER_SEL_ABZ_HALL:
		mcEncoder.LoadQepPos = read_csr(TIM2_QEP_MNUM);
		usSRegInBuf[SFBENCERR] = 0;
		break;
	case ENCODER2_SEL_ABZ: // QEP增量编码器
	case ENCODER2_SEL_ABZ_HALL:
		mcEncoder.LoadQepPos = read_csr(TIM5_QEP_MNUM);
		usSRegInBuf[SFBENCERR] = 0;
		break;
#endif
	
#if ENCODER_SEL_SPI_ENABLED > 0
	case ENCODER_SEL_ABS_CUSTOM1: // SPI编码器
		usSRegInBuf[SFBENCERR] = SPI_Encoder_GetPos(&mcEncoder.LoadQepPos);
		break;
#endif
		
#if ENCODER_SEL_SPI2_ENABLED > 0
	case ENCODER_SEL_ABS_CUSTOM2: // SPI编码器
		usSRegInBuf[SFBENCERR] = SPI2_Encoder_GetPos(&mcEncoder.LoadQepPos);
		break;
#endif
		
#if ENCODER_SEL_PWM_ENABLED > 0
	case ENCODER_SEL_ABS_CUSTOM1: // PWM编码器
		usSRegInBuf[SFBENCERR] = PWM_Encoder_GetPos(&mcEncoder.LoadQepPos);
		break;
#endif
		
	default:
		mcEncoder.LoadQepPos = 0;
		usSRegInBuf[SFBENCERR] = 0;
		break;
	}
	
#if ENCODER_SEL_TMG_ENABLED > 0
	// 多摩川电机刚上电时忽略报错
	if (mcEncoder.TMG.TmgTimeOutFlag < 5000 && (mcEncoder.TypeSelect == ENCODER_SEL_TMG_ABS_SIN || 
		mcEncoder.TypeSelect == ENCODER_SEL_TMG_ABS_MUL || mcEncoder.TypeSelect == ENCODER_SEL_TMG_INC))
	{
		mcEncoder.ErrCode = 0;
		mcEncoder.TMG.TmgTimeOutFlag++;
	}
#endif
	
	EncDiff = mcEncoder.EncPos - mcEncoder.EncPosLatch;

	// turn encoder data to 64 bit
	if (*((uint32*) & usSRegHoldBuf[ELECANGMW_L]) != 0 && mcEncoder.TypeSelect != ENCODER_SEL_HALLS_ONLY)
	{
		if (mcEncoder.EncPos > mcEncoder.EncPosLatch && EncDiff < 0)
			mcEncoder.MultiHigh--;
		else if (mcEncoder.EncPosLatch > mcEncoder.EncPos && EncDiff > 0)
			mcEncoder.MultiHigh++;
	}

	*pEncPos = mcEncoder.EncPos;
	*pEncMulti = mcEncoder.MultiHigh;
	*pEncDiff = (int16)EncDiff;
	*pErrCode = mcEncoder.ErrCode;
}
