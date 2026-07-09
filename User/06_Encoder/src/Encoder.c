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


/*---------------------------------------------------------------------------
 * Name		:	Encoder_Init
 * Input	:	No
 * Output	:	No
 * Description:	Encoder initialization function
 *---------------------------------------------------------------------------*/
void Encoder_Init(void)
{
	memset(&mcEncoder, 0, sizeof(Encoder_TypeDef));

#if ENCODER_SEL_ABZ_ENABLED > 0 || FUNC_PROBE_ENABLED > 0 || FUNC_PCOM_ENABLED > 0
	Timer2_Init(); // QEP incremental encoder ABZ + absolute + Hall (primary)
	Timer5_Init(); // QEP incremental encoder ABZ + Hall (secondary)
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
	clr_csr(SLRE_PU, SLRE_PIN);							// Disable pull-up
#endif
#ifdef MARE_PIN
	set_csr(MARE_OE, MARE_PIN);
	clr_csr(MARE_PU, MARE_PIN);							// Disable pull-up
#endif
	
	// Enable based on current encoder type
	Encoder_Switch();
}


/*---------------------------------------------------------------------------
 * Name		:	Encoder_Switch
 * Input	:	No
 * Output	:	No
 * Description:	Encoder enable function: automatically enables or disables based on the encoder type
 *---------------------------------------------------------------------------*/
void Encoder_Switch(void)
{
#if ENCODER_SEL_ABZ_ENABLED > 0
	if (mcEncoder.TypeSelect == ENCODER_SEL_ABZ ||
		mcEncoder.TypeSelect == ENCODER_SEL_ABZ_HALL) // QEP incremental encoder
	{
		Timer2_Enable();
#ifdef SLRE_PIN
		clr_csr(SLRE_GPIO, SLRE_PIN);							// Pull SL's RE pin low
#endif
#ifdef MARE_PIN
		clr_csr(MARE_GPIO, MARE_PIN);							// Pull MA's RE pin low
#endif
		
		if (mcEncoder.LoadTypeSelect != ENCODER2_SEL_ABZ &&
			mcEncoder.LoadTypeSelect != ENCODER2_SEL_ABZ_HALL) // QEP incremental encoder
		{
			Timer5_Disable();
		}
	}
	else if (mcEncoder.TypeSelect == ENCODER2_SEL_ABZ ||
		mcEncoder.TypeSelect == ENCODER2_SEL_ABZ_HALL) // QEP incremental encoder
	{
		Timer5_Enable();
		
		if (mcEncoder.LoadTypeSelect != ENCODER_SEL_ABZ &&
			mcEncoder.LoadTypeSelect != ENCODER_SEL_ABZ_HALL) // QEP incremental encoder
		{
			Timer2_Disable();
		}
	}
	else
	{
		if (mcEncoder.LoadTypeSelect == ENCODER2_SEL_ABZ ||
			mcEncoder.LoadTypeSelect == ENCODER2_SEL_ABZ_HALL) // QEP incremental encoder
		{
			Timer2_Disable();
		}
		else if (mcEncoder.LoadTypeSelect == ENCODER_SEL_ABZ ||
			mcEncoder.LoadTypeSelect == ENCODER_SEL_ABZ_HALL) // QEP incremental encoder
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
	if (mcEncoder.TypeSelect == ENCODER_SEL_TMG_ABS_SIN || // TMG single-turn absolute decoding
		mcEncoder.TypeSelect == ENCODER_SEL_TMG_ABS_MUL || // TMG multi-turn absolute decoding
		mcEncoder.TypeSelect == ENCODER_SEL_TMG_INC)// TMG incremental decoding
	{
		TMG_Encoder_Enable();
	}
	else
	{
		TMG_Encoder_Disable();
	}
#endif

#if ENCODER_SEL_BISS_ENABLED > 0
	if (mcEncoder.TypeSelect == ENCODER_SEL_BISS)// BiSS encoder
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
	if (mcEncoder.TypeSelect == ENCODER_SEL_ABS_CUSTOM1)// SPI encoder
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
	if (mcEncoder.TypeSelect == ENCODER_SEL_ABS_CUSTOM2)// SPI2 encoder
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

/*---------------------------------------------------------------------------
 * Name		:	Encoder_Switch
 * Input	:	No
 * Output	:	No
 * Description:	Output-side encoder enable function; automatically selects enable/disable based on encoder type
 *---------------------------------------------------------------------------*/
void Encoder_Switch_LoadSide(void)
{
#if ENCODER_SEL_ABZ_ENABLED > 0
	if (mcEncoder.LoadTypeSelect == ENCODER2_SEL_ABZ ||
		mcEncoder.LoadTypeSelect == ENCODER2_SEL_ABZ_HALL) // QEP incremental encoder
	{
		Timer5_Enable();
		
		if (mcEncoder.TypeSelect != ENCODER_SEL_ABZ &&
			mcEncoder.TypeSelect != ENCODER_SEL_ABZ_HALL) // QEP incremental encoder
		{
			Timer2_Disable();
		}
	}
	else if (mcEncoder.LoadTypeSelect == ENCODER_SEL_ABZ ||
		mcEncoder.LoadTypeSelect == ENCODER_SEL_ABZ_HALL) // QEP incremental encoder
	{
		Timer2_Enable();
#ifdef SLRE_PIN
		clr_csr(SLRE_GPIO, SLRE_PIN);							// Pull SL's RE pin low
#endif
#ifdef MARE_PIN
		clr_csr(MARE_GPIO, MARE_PIN);							// Pull MA's RE pin low
#endif

		if (mcEncoder.TypeSelect != ENCODER2_SEL_ABZ &&
			mcEncoder.TypeSelect != ENCODER2_SEL_ABZ_HALL) // QEP incremental encoder
		{
			Timer5_Disable();
		}

	}
	else
	{
		if (mcEncoder.TypeSelect == ENCODER2_SEL_ABZ ||
			mcEncoder.TypeSelect == ENCODER2_SEL_ABZ_HALL) // QEP incremental encoder
		{
			Timer2_Disable();
		}
		else if (mcEncoder.TypeSelect == ENCODER_SEL_ABZ ||
			mcEncoder.TypeSelect == ENCODER_SEL_ABZ_HALL) // QEP incremental encoder
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
	if (mcEncoder.LoadTypeSelect == ENCODER_SEL_ABS_CUSTOM1)// SPI encoder
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
	if (mcEncoder.LoadTypeSelect == ENCODER_SEL_ABS_CUSTOM2)// SPI2 encoder
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
	if (mcEncoder.LoadTypeSelect == ENCODER_SEL_ABS_CUSTOM1)// PWM encoder
	{
		PWM_Encoder_Enable();
	}
	else
	{
		PWM_Encoder_Disable();
	}
#endif

}

/*---------------------------------------------------------------------------
 * Name		:	Encoder_Update
 * Input	:	No
 * Output	:	No
 * Description:	Encoder parameter updates, such as type, clock frequency, resolution, filtering, etc.
 *---------------------------------------------------------------------------*/
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
	case ENCODER_SEL_ABZ: // QEP incremental encoder
	case ENCODER_SEL_ABZ_HALL:
		if ((uint16)mcEncoder.AqbFilt != usSRegHoldBuf[AQBFILT])
		{
			mcEncoder.AqbFilt = usSRegHoldBuf[AQBFILT];
			Timer2_Filter_Update(usSRegHoldBuf[AQBFILT]);
		}
		EncoderComp_DelayTs = ELEANG_DELAYTS;
		// M/MT method selection  0:M method  1:MT method
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
	case ENCODER_SEL_TMG_ABS_SIN: // TMG single-turn absolute decoding
	case ENCODER_SEL_TMG_ABS_MUL: // TMG multi-turn absolute decoding
	case ENCODER_SEL_TMG_INC: // TMG incremental decoding
		TMG_Encoder_Update();
		clr_csr(DRV1_FCR4, MMT_SEL);			// M/MT method selection  0:M method  1:MT method
		break;
#endif

#if ENCODER_SEL_BISS_ENABLED > 0
	case ENCODER_SEL_BISS: // BiSS encoder
		BiSS_Encoder_Update();
		EncoderComp_DelayTs = (ELEANG_DELAYTS + BISS_DELAYTS) >> 5;
		clr_csr(DRV1_FCR4, MMT_SEL);			// M/MT method selection  0:M method  1:MT method
		break;
#endif
		
#if ENCODER_SEL_SPI_ENABLED > 0
	case ENCODER_SEL_ABS_CUSTOM1: // SPI encoder
		SPI_Encoder_Update();
		EncoderComp_DelayTs = ELEANG_DELAYTS; // (ELEANG_DELAYTS + BISS_DELAYTS) >> 5;
		clr_csr(DRV1_FCR4, MMT_SEL);			// M/MT method selection  0:M method  1:MT method
		break;
#endif
		
#if ENCODER_SEL_SPI2_ENABLED > 0
	case ENCODER_SEL_ABS_CUSTOM2: // SPI2 encoder
		SPI2_Encoder_Update();
		EncoderComp_DelayTs = ELEANG_DELAYTS; // (ELEANG_DELAYTS + BISS_DELAYTS) >> 5;
		clr_csr(DRV1_FCR4, MMT_SEL);			// M/MT method selection  0:M method  1:MT method
		break;
#endif
		
//#if ENCODER_SEL_PWM_ENABLED > 0
//	case ENCODER_SEL_ABS_CUSTOM1: // PWM encoder
//		PWM_Encoder_Update();
//		EncoderComp_DelayTs = ELEANG_DELAYTS; // (ELEANG_DELAYTS + BISS_DELAYTS) >> 5;
//		clr_csr(DRV1_FCR4, MMT_SEL);			// M/MT method selection  0:M method  1:MT method
//		break;
//#endif

	default:
		EncoderComp_DelayTs = 0;
		clr_csr(DRV1_FCR4, MMT_SEL);			// M/MT method selection  0:M method  1:MT method
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


/*---------------------------------------------------------------------------
 * Name		:	Encoder_Update
 * Input	:	*pEncPos - Encoder value, 32 bit
				*pEncMulti - Encoder multiturn value, 32 bits
				*pEncDiff - return Encoder difference value of adjacent time
				*pErrCode - return Encoder error
 * Output	:	No
 * Description:	Get encoder readings
 *---------------------------------------------------------------------------*/
void Encoder_GetPos(int32* pEncPos, int32* pEncMulti, int16* pEncDiff, uint16* pErrCode)
{
	int32 EncDiff;										    // Encoder difference between two consecutive times

	mcEncoder.EncPosLatch = mcEncoder.EncPos;
	
	switch (mcEncoder.TypeSelect)
	{
#if ENCODER_SEL_ABZ_ENABLED > 0
	case ENCODER_SEL_ABZ: // QEP incremental encoder
	case ENCODER_SEL_ABZ_HALL:
		mcEncoder.EncPos = read_csr(TIM2_QEP_MNUM);
		mcEncoder.ErrCode = 0;
		break;
	case ENCODER2_SEL_ABZ: // QEP incremental encoder
	case ENCODER2_SEL_ABZ_HALL:
		mcEncoder.EncPos = read_csr(TIM5_QEP_MNUM);
		mcEncoder.ErrCode = 0;
		break;
#endif

#if ENCODER_SEL_TMG_ENABLED > 0
	case ENCODER_SEL_TMG_ABS_SIN: // TMG single-turn absolute decoding
		mcEncoder.ErrCode = TMG_Encoder_GetSingleAbsPos(&mcEncoder.EncPos);
		break;

	case ENCODER_SEL_TMG_ABS_MUL: // TMG multi-turn absolute decoding
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

	case ENCODER_SEL_TMG_INC: // TMG incremental decoding
		mcEncoder.ErrCode = TMG_Encoder_GetSingleAbsPos(&mcEncoder.EncPos);
		break;
#endif

#if ENCODER_SEL_BISS_ENABLED > 0
	case ENCODER_SEL_BISS: // BiSS encoder
		mcEncoder.ErrCode = BiSS_Encoder_GetPos(&mcEncoder.EncPos);
		break;
#endif
		
#if ENCODER_SEL_HALLSONLY_ENABLED > 0

case ENCODER_SEL_HALLS_ONLY: // Halls-only
		mcEncoder.EncPos = UpdateHallsOnlyAngle();
		mcEncoder.ErrCode = 0;
		break;
#endif
	
#if ENCODER_SEL_SPI_ENABLED > 0
	case ENCODER_SEL_ABS_CUSTOM1: // SPI encoder
		mcEncoder.ErrCode = SPI_Encoder_GetPos(&mcEncoder.EncPos);
		break;
#endif
		
#if ENCODER_SEL_SPI2_ENABLED > 0
	case ENCODER_SEL_ABS_CUSTOM2: // SPI2 encoder
		mcEncoder.ErrCode = SPI2_Encoder_GetPos(&mcEncoder.EncPos);
		break;
#endif
		
	default:
		mcEncoder.EncPos = 0;
		mcEncoder.ErrCode = 0;
		break;
	}

	// Outer-loop encoder update position
	switch (mcEncoder.LoadTypeSelect)
	{
#if ENCODER_SEL_ABZ_ENABLED > 0
	case ENCODER_SEL_ABZ: // QEP incremental encoder
	case ENCODER_SEL_ABZ_HALL:
		mcEncoder.LoadQepPos = read_csr(TIM2_QEP_MNUM);
		usSRegInBuf[SFBENCERR] = 0;
		break;
	case ENCODER2_SEL_ABZ: // QEP incremental encoder
	case ENCODER2_SEL_ABZ_HALL:
		mcEncoder.LoadQepPos = read_csr(TIM5_QEP_MNUM);
		usSRegInBuf[SFBENCERR] = 0;
		break;
#endif
	
#if ENCODER_SEL_SPI_ENABLED > 0
	case ENCODER_SEL_ABS_CUSTOM1: // SPI encoder
		usSRegInBuf[SFBENCERR] = SPI_Encoder_GetPos(&mcEncoder.LoadQepPos);
		break;
#endif
		
#if ENCODER_SEL_SPI2_ENABLED > 0
	case ENCODER_SEL_ABS_CUSTOM2: // SPI encoder
		usSRegInBuf[SFBENCERR] = SPI2_Encoder_GetPos(&mcEncoder.LoadQepPos);
		break;
#endif
		
#if ENCODER_SEL_PWM_ENABLED > 0
	case ENCODER_SEL_ABS_CUSTOM1: // PWM encoder
		usSRegInBuf[SFBENCERR] = PWM_Encoder_GetPos(&mcEncoder.LoadQepPos);
		break;
#endif
		
	default:
		mcEncoder.LoadQepPos = 0;
		usSRegInBuf[SFBENCERR] = 0;
		break;
	}
	
#if ENCODER_SEL_TMG_ENABLED > 0
	// Ignore errors when Tamagawa motor is just powered on
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