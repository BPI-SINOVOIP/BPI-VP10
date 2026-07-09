/*
 * Copyright (c) 2025-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : PIControl.c
 * Author        : wynn.wang
 * Date          : 2025-04-20
 * Description   : Implement core PI controller functions, including parameter initialization, control calculation, integral limiting, etc.
 *				   Position loop P controller, implemented in software
 *				   Speed loop PDFF controller, implemented in hardware
 *				   Current loop PI controller, implemented in hardware
 *				   General PI controller, such as pressure control, implemented in software
 * Record        :
 * V1.0, 2025-04-20, wynn.wang: Initial version, implements basic PI control algorithm
 */


/********************************************************************************
* Header Definition
********************************************************************************/
#include <Myproject.h>


/********************************************************************************
* Macro & Structure Definition
*******************************************************************************/
PIControl PID_Speed __attribute__((section(".pram.data.PID_Speed")));
PIControl PID_Pos;

#if FUNC_FORCECTRL_ENABLED
PIControlSimple PID_Force;
#endif

uint8 KpKiQArray[4] = { 15, 12, 8, 4 }; // Q value selection for speed loop PI


/********************************************************************************
* Internal Routine Prototypes
********************************************************************************/ 

/*---------------------------------------------------------------------------
 * Name		:	PI_Init
 * Input	:	No
 * Output	:	No
 * Description:	PI controller initialization
 *---------------------------------------------------------------------------*/
void PI_Init(void)
{
	PI_Update();  // Update speed loop and position loop PI gains

	// Speed loop PI initialization
#if FUNC_GAINSW_ENABLED
	PID_Speed.pGnSW = GainSW_GetSWVelParam();
#endif //#if FUNC_GAINSW_ENABLED

	set_csr(DRV1_FCR4, PDFF_EN); // Outer loop PDFF enable, 0: outer loop uses PI, 1: outer loop uses PDFF

	NFOC_PDKP = PID_Speed.Kp1 + PID_Speed.KpQSel;
	NFOC_PDKI = PID_Speed.Ki1 + PID_Speed.KiQSel;
	NFOC_PDKF = (((uint32)PID_Speed.Kp1 * (uint32)PID_Speed.Kvf1) >> 16) + PID_Speed.KpQSel;

	NFOC_PDMAX = usSRegHoldBuf[VOUTMAX];
	NFOC_PDMIN = usSRegHoldBuf[VOUTMIN];

	NFOC_PDITMP = 0; // Clear integral term
	NFOC_PDISAT = usSRegHoldBuf[DESATUR]; // Integral saturation value
	NFOC_PDUK = 0; // Clear controller output value

	// Position loop PI initialization
	PID_Pos.ValueMax = usSRegHoldBuf[POUTMAX];
	PID_Pos.ValueMin = usSRegHoldBuf[POUTMIN];

#if FUNC_GAINSW_ENABLED
	PID_Pos.pGnSW = GainSW_GetSWPosParam();
#endif //#if FUNC_GAINSW_ENABLED

#if FUNC_FORCECLOSEDLOOP_ENABLED
	PI_Control_Init(&PID_Force);
#endif
}


/*---------------------------------------------------------------------------
 * Name		:	PI_Clear
 * Input	:	No
 * Output	:	No
 * Description:	Reset PI controller
 *---------------------------------------------------------------------------*/
void PI_Clear(void)
{
	// Clear VelLoop PI, clear relevant hardware registers for speed loop PI
	memset(&NFOC_PDCMD, 0, 11 * 2);

	memset(&PID_Speed, 0, sizeof(PIControl));
	memset(&PID_Pos, 0, sizeof(PIControl));
	
#if FUNC_FORCECLOSEDLOOP_ENABLED
	PI_Control_Clear(&PID_Force);
#endif

	// Clear Current Loop PI
	NFOC_IDREF = 0;
	NFOC_IQREF = 0;

	usSRegInBuf[CMDCUR] = 0;
	usSRegInBuf[MB_IDREF] = 0;
}


/*---------------------------------------------------------------------------
 * Name		:	PI_Spd_Gain_Update
 * Input	:	No
 * Output	:	No
 * Description:	Update speed loop gain from gain switching to hardware registers
 *---------------------------------------------------------------------------*/
void PI_Spd_Gain_Update()
{
	NFOC_PDKP = PID_Speed.Kp + PID_Speed.KpQSel;
	NFOC_PDKI = PID_Speed.Ki + PID_Speed.KiQSel;
	NFOC_PDKF = PID_Speed.Kf + PID_Speed.KpQSel;
}


#if FUNC_FORCECTRL_ENABLED
/*---------------------------------------------------------------------------
 * Name		:	PI_Spd_Clear
 * Input	:	No
 * Output	:	No
 * Description:	Clear integral term of speed loop PI
 *---------------------------------------------------------------------------*/
void PI_Spd_Clear(void)
{
	NFOC_PDITMP = 0;
}

/*---------------------------------------------------------------------------
 * Name		:	PI_Toq_Clear
 * Input	:	No
 * Output	:	No
 * Description:	Clear output of current loop PI
 *---------------------------------------------------------------------------*/
void PI_Toq_Clear(void)
{
	NFOC_DEK = 0;
	NFOC_DEK1 = 0;
	NFOC_DUK = 0;
	NFOC_DUKH = 0;

	NFOC_QEK = 0;
	NFOC_QEK1 = 0;
	NFOC_QUK = 0;
	NFOC_QUKH = 0;
}
#endif // #if FUNC_FORCECTRL_ENABLED


/*---------------------------------------------------------------------------
 * Name		:	PI_Update
 * Input	:	No
 * Output	:	No
 * Description:	Update speed loop and position loop PI gains from host computer
 *---------------------------------------------------------------------------*/
void PI_Update()
{
	if (usSRegHoldBuf[VKP] == 0 || usSRegHoldBuf[VKP2] == 0 ||
		(usSRegHoldBuf[VKP] & 0xC000) == (usSRegHoldBuf[VKP2] & 0xC000))
	{
		PID_Speed.Kp1 = usSRegHoldBuf[VKP] & 0x3FFF;
		PID_Speed.Kp2 = usSRegHoldBuf[VKP2] & 0x3FFF;
		PID_Speed.KpQSel = usSRegHoldBuf[VKP] & 0xC000;
	}

	if (usSRegHoldBuf[VKI] == 0 || usSRegHoldBuf[VKI2] == 0 ||
		(usSRegHoldBuf[VKI] & 0xC000) == (usSRegHoldBuf[VKI2] & 0xC000))
	{
		PID_Speed.Ki1 = usSRegHoldBuf[VKI] & 0x3FFF;
		PID_Speed.Ki2 = usSRegHoldBuf[VKI2] & 0x3FFF;
		PID_Speed.KiQSel = usSRegHoldBuf[VKI] & 0xC000;
	}

	PID_Speed.KpQVal = KpKiQArray[PID_Speed.KpQSel >> 14];
	PID_Speed.KiQVal = KpKiQArray[PID_Speed.KiQSel >> 14];

	PID_Speed.Kvf1 = usSRegHoldBuf[VFR];
	PID_Speed.Kvf2 = usSRegHoldBuf[VFR2];

	PID_Pos.Kp1 = usSRegHoldBuf[PKP];
	PID_Pos.Ki1 = usSRegHoldBuf[PKI];
	PID_Pos.Kp2 = usSRegHoldBuf[PKP2];
	PID_Pos.Ki2 = usSRegHoldBuf[PKI2];
}


/*---------------------------------------------------------------------------
 * Name		:	PI_Pos_realize
 * Input	:	No
 * Output	:	No
 * Description:	Implementation of position loop P controller, U[k] = Kp * E[k] + Speed feedforward
 *---------------------------------------------------------------------------*/
int16 PI_Pos_realize(int32 ErrValue)
{
	int64 temp = 0;
	int32 ValuetempKp = 0;
	int8 KpRank = KP_RANK;
	
#if FUNC_FEEDBACKONLOAD_ENABLED
	if (FEEDBACK_LOAD == Feedback_GetOnLoadFlag())
	{
		// Convert speed command from outer loop to inner loop units
		temp = (int64)ErrValue * PID_Pos.Kp * Feedback_GetLoadToMotorCoef(); // Note overflow
		KpRank += MOTORCOEF;
	}
	else
	{
		temp = (int64)ErrValue * PID_Pos.Kp;
	}
#else
	temp = (int64)ErrValue * PID_Pos.Kp;
#endif

	
	if (temp < 0)
	{
		ValuetempKp = (int32)(-((-(int64)temp) >> KpRank));
	}
	else
	{
		ValuetempKp = (int32)((int64)temp >> KpRank);
	}	
	
	ValuetempKp += (int16)usSRegInBuf[SPEEDFF];
	
	if (ValuetempKp > PID_Pos.ValueMax)
	{
		ValuetempKp = PID_Pos.ValueMax;
	}
	else if (ValuetempKp < PID_Pos.ValueMin)
	{
		ValuetempKp = PID_Pos.ValueMin;
	}

	return (int16)ValuetempKp;
}