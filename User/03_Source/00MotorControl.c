/*
 * Copyright (c) 2023-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : MotorControl.c
 * Author        : Summer
 * Date          : 2023-05-11
 * Description   : Carrier interrupt and position loop interrupt functions
 *
 * Record        :
 * V1.0, 2023-05-11, Summer: Created file
 */



/********************************************************************************
 * Header Definition
 ********************************************************************************/

#include <Myproject.h>


/********************************************************************************
 * Macro & Structure Definition
 *******************************************************************************/


/********************************************************************************
 * Internal Routine Prototypes
 ********************************************************************************/
void ServoControl_Isr(void);
void PosControl_Isr(void);
void DeltaTargetRefCalc(void);


/*---------------------------------------------------------------------------
 * Name		:	ServoControl_Isr
 * Input	:	No
 * Output	:	No
 * Description:	Carrier interrupt, including reading encoder values, updating electrical angle, speed command update, and current command update
 *---------------------------------------------------------------------------*/
void ServoControl_Isr(void)
{
#if DRV32K_ENABLE_SWITCH
	// 32K current loop modified to comparison value trigger point operation mode
	mcFocCtrl.DrvComrVal = 1 - mcFocCtrl.DrvComrVal; // The initial value is 0, Drv initialization first trigger is down-counting, so the first time entering here it switches to up-counting trigger
	if (mcFocCtrl.DrvComrVal)
	{
		clr_csr(DRV1_IER, DCIM1);				// 01: Up direction
		set_csr(DRV1_IER, DCIM0);
		write_csr(DRV1_COMR, PWM_VALUE_UPLOAD);		// The next interrupt trigger condition is up-counting direction and COMR=0
	}
	else
	{
		set_csr(DRV1_IER, DCIM1);				// 10: Down direction
		clr_csr(DRV1_IER, DCIM0);
		write_csr(DRV1_COMR, PWM_VALUE_DOWNLOAD);	// The next interrupt trigger condition is down-counting direction and COMR=ARR
	}
#endif // #if DRV32K_ENABLE_SWITCH

	// get encoder value at the very beginnig, to make sure velocity is correct.
	Encoder_GetPos(&mcFocCtrl.QepPos, &mcFocCtrl.QepPosMulti, &mcFocCtrl.QepPosDiff, &usSRegInBuf[ENCODERERR]);

	if (mcFocCtrl.AngDir)
	{
		mcFocCtrl.ActPos = -mcFocCtrl.QepPos; // Display position
	}
	else
	{
		mcFocCtrl.ActPos = mcFocCtrl.QepPos;
	}

	NFOC_OMEFLTH = usSRegInBuf[ACTVEL];

	NFOC_MQEP = mcFocCtrl.ActPos;
	NFOC_MBLK = read_csr(TIM2_QEP_TS_EMP);
	NFOC_MREM = read_csr(TIM2_QEP_TNUM);

	NFOC_PDCMD = usSRegInBuf[CMDVEL]; // Speed command


#if FUNC_FEEDBACKONLOAD_ENABLED
	if (mcFocCtrl.LoadAngDir)
	{
		mcFocCtrl.ActLoadPos = -mcEncoder.LoadQepPos; // Outer loop position
	}
	else
	{
		mcFocCtrl.ActLoadPos = mcEncoder.LoadQepPos;
	}

	usSRegInBuf[SFBACTPOSRAW_H] = mcFocCtrl.ActLoadPos >> 16;
	usSRegInBuf[SFBACTPOSRAW_L] = mcFocCtrl.ActLoadPos & 0xFFFF;
#endif

	// Analog speed & analog current & serial pressure loop mode
#if EXCTRL_ANALOG_ENABLED
	if ((mcRegParam.WorkMode == VELANALOG
		|| mcRegParam.WorkMode == CURANALOG
#if FUNC_FORCECLOSEDLOOP_ENABLED
		|| mcRegParam.WorkMode == FRCSERIAL	//Pressure loop debugging
		|| (usSRegHoldBuf[FCMOD] == FCMODE_CLOSEDLOOP_ONCE)	//Closed-loop force control single execution
		|| (usSRegHoldBuf[FCMOD] == FCMODE_CLOSEDLOOP_REPEAT)	//Closed-loop force control repeated execution
#endif
		) && (mcState == mcRun || mcState == mcIdle))
	{
		Motor_AnalogIn_Handler();
	}
#endif // #if EXCTRL_ANALOG_ENABLED

	/////////**************** Calculation of ElecAng 1.9 us ****************/////////
#if MOTOR_VCM_ENABLED
	if (usSRegHoldBuf[MOTORCOMMTYPE] != VOICECOIL_MOTOR)
#endif
	{
#if ENCODER_SEL_HALLSONLY_ENABLED > 0
		if (usSRegHoldBuf[ENCTYPE] == ENCODER_SEL_HALLS_ONLY)
		{
			mcElecAng.FOCTheta = GetHallsOnlyElecAngle();
		}
		else
#endif
		{
			mcElecAng.FOCTheta = ElecAngCal_realize(mcFocCtrl.QepPos, mcFocCtrl.QepPosMulti) 
				- usSRegInBuf[ELECANGOFFSET];

#if ENCODER_SEL_HALL_ENABLED
			UpdateHallTheta_Isr();
#endif // #if ENCODER_SEL_HALL_ENABLED
		}

#if FUNC_ENCODERCOMP_ENABLED
		if (ABS(usSRegInBuf[ACTVEL]) > mcEncoder.ValueMax)
		{
			mcEncoder.EleAngComp = (int16)((uint64)mcEncoder.DelayComCoef * ABS((int16)usSRegInBuf[ACTVEL]) >> ENCCOMP_SHIFT);
		}
		else
		{
			mcEncoder.EleAngComp = 0;
		}
#else
		mcEncoder.EleAngComp = 0;
#endif

		if (!mcElecAng.FOCThetaFlag)
			NFOC_THETAH = mcElecAng.FOCTheta + mcEncoder.EleAngComp;

		usSRegInBuf[ELECANG] = NFOC_THETAH;

}
	/////////**************** Calculation of ElecAng end ****************/////////

#if DEADTIME_COMPENSATE_ENABLED // Dead time compensation
	DeadTimeCompensationController(NFOC_THETAH, NFOC_IDFLTH, NFOC_IQFLTH);
#endif

	if (readbit_csr(DRV1_FCR5, WPI_SERVO_EN)) // Align with the hardware velocity loop calculation
	{
		mcFocCtrl.VelCnt = 0;
	}

	if (++mcFocCtrl.VelCnt >= (uint16)DRIVERINT_FREQUENCY / ((uint16)POSCTRL_FREQUENCY << 1))
	{
		mcFocCtrl.VelCnt = 0;

		mcFocCtrl.VelLoopTime = 1; // Update velocity loop command flag

		Timer3_Enable();  // Start Pos Loop Interrupt

		mcFocCtrl.Timer1msCount++;
		if (mcFocCtrl.Timer1msCount >= ((uint16)POSCTRL_FREQUENCY << 1))
		{
			TimerFlag_1ms = 1; // Flag to start 1ms calculation in mainloop
			mcFocCtrl.Timer1msCount = 0;
		}
	}

	///////////**************** VelLoop Controller ****************/////////
	if (mcFocCtrl.VelLoopTime)	 // VelLoop: 8kHz
	{
		mcFocCtrl.VelLoopTime = 0;

#if FUNC_SOFTCTRL_ENABLED
		if ((mcFocCtrl.VelLoopEnable) || FieldSoftControl_GetSwToPosFlag())
#else
		if (mcFocCtrl.VelLoopEnable)
#endif
		{
#if FUNC_DISMODE_ENABLED
			if (mcEmergencyStop.DecStopFlag)
			{
				usSRegInBuf[CMDVEL] = RampStop_realize();
			}
			else
#endif // #if FUNC_DISMODE_ENABLED
			// SerialIn Vel & PV
			if (((mcRegParam.WorkMode == VELSERIAL) && (mcSigGen.Status != MS_SUSPEND) && (mcSigGen.Status != MS_READY))
#if EXCTRL_ECAT_ENABLED || EXCTRL_CANOPEN_ENABLED
				|| (usSRegInBuf[FBOPMODE] == PROFILE_VELOCITY_MODE)
#endif
				)
			{
				usSRegInBuf[CMDVEL] = Motor_SerialIn_Handler();
#if SPECIAL_ELESCREW_ENABLE
				ScrewCtrl.SerialInStatus = mcSigGen.Status;
#endif
			}

#if EXCTRL_ECAT_ENABLED || EXCTRL_CANOPEN_ENABLED
			// CSV
			else if (usSRegInBuf[FBOPMODE] == CYCLIC_SYNC_VELOCITY_MODE)
			{
				usSRegInBuf[CMDVEL] = (int16)CiA402_TargetVelocity; // Velocity command source is ECAT
			}
#endif

			// Gain switching
#if FUNC_GAINSW_ENABLED
			GainSwitching_realize(&PID_Speed, GNSWCTRL_SPD);
#else
			GetGnFir(&PID_Speed);
#endif //#if FUNC_GAINSW_ENABLED

			PI_Spd_Gain_Update(); // Velocity loop gain update

			// Torque feedforward
#if FUNC_TOQFF_ENABLED
			usSRegInBuf[ACCFF] = ToqFF_realize();
			NFOC_WUCPS = usSRegInBuf[ACCFF];
#endif //#if FUNC_TOQFF_ENABLED

#if FUNC_FIELDWEAKEN_ENABLED
			FieldWeakenGetIdRefAndIqRef();
#endif
			usSRegInBuf[CMDCUR] = NFOC_WUFIN;
		}
		else
		{
			usSRegInBuf[CMDVEL] = 0;
		}
#if FUNC_SOFTCTRL_ENABLED
		FieldSoftControl_AccActCalc();
#endif
	}


#if FUNC_FORCECLOSEDLOOP_ENABLED
	if (mcFocCtrl.FrcLoopEnable)
	{
		// SerialIn ForceCloseLoop
		if ((mcRegParam.WorkMode == FRCSERIAL) && (mcSigGen.Status != MS_SUSPEND) && (mcSigGen.Status != MS_READY))
		{
			if (ForceCtrl.Status == FC_TOQ_HOLDING)
			{
				usSRegInBuf[CMDFRC] = Motor_SerialIn_Handler();
			}
			else
			{
				usSRegInBuf[CMDFRC] = 0;
			}
		}
		else
		{
			usSRegInBuf[CMDFRC] = 0;
		}

		ForceCtrl.FrcFdb = (int16)usSRegInBuf[ACTFRC] - ForceCtrl.FrcAdjustComp;

		mcFocCtrl.mcIqRef = PI_Control_realize(&PID_Force, (int16)usSRegInBuf[CMDFRC], (int16)ForceCtrl.FrcFdb);

		usSRegInBuf[CMDCUR] = mcFocCtrl.mcIqRef;
	}
	else
	{
		usSRegInBuf[CMDFRC] = 0;
	}
#endif

	///////**************** Cur Loop Enable ****************/////////
	if (mcFocCtrl.CurLoopEnable)
	{
		mcFocCtrl.focIqRef = 0; // Clear Q-axis compensation
#if FUNC_MOTOREST_ENABLED
		if ((mcState == mcMotorIdentify) && (McStaSet.SetFlag.IdentifySetFlag == 1))
		{
			Motor_Identify_realize_Isr();
		}
		else
#endif
		{
			// SerialIn Current
			if (((mcRegParam.WorkMode == CURSERIAL) && (mcSigGen.Status != MS_SUSPEND) && (mcSigGen.Status != MS_READY))
#if EXCTRL_ECAT_ENABLED || EXCTRL_CANOPEN_ENABLED
				|| (usSRegInBuf[FBOPMODE] == PROFILE_TORQUE_MODE)
#endif
				)
			{
				usSRegInBuf[CMDCUR] = Motor_SerialIn_Handler();
			}

else if (mcRegParam.WorkMode == VELFRF || mcRegParam.WorkMode == CURFRF)
			{
				mcFocCtrl.focIqRef = Motor_SerialIn_Handler();
			}
#if FUNC_CURTUNE_ENABLED
			else if (mcRegParam.WorkMode == CURTUNE)
			{
				Motor_TuningSignal_Handler(&usSRegInBuf[MB_IDREF], &mcFocCtrl.focIqRef);
			}
#endif

#if EXCTRL_ECAT_ENABLED || EXCTRL_CANOPEN_ENABLED
			// CST
			else if (usSRegInBuf[FBOPMODE] == CYCLIC_SYNC_TORQUE_MODE)
			{
				usSRegInBuf[CMDCUR] = CiA402_TargetTorque; // Torque command originates from ECAT
			}
#endif
		}


		if (mcFocCtrl.EAngDir)
		{
			usSRegInBuf[ACTCUR] = -NFOC_IQ;
		}
		else
		{
			usSRegInBuf[ACTCUR] = NFOC_IQ;
		}

		if (mcFocCtrl.RunMod == CURMOD)
		{
			NFOC_F1X0 = usSRegInBuf[CMDCUR];
		}
#if FUNC_SOFTCTRL_ENABLED
		else if (mcFocCtrl.RunMod == POS_CURMOD)
		{
			int16 temp = FieldSoftControl_TiffCalc();
			if (FieldSoftControl_GetSwToPosDoneFlag() == 0)
			{
				usSRegInBuf[CMDCUR] = temp;
			}
			NFOC_F1X0 = usSRegInBuf[CMDCUR];
		}
#endif


#if FUNC_FRICOMP_ENABLED
		// Friction compensation
		mcFocCtrl.focIqRef += FricCmp_realize();
#endif

		usSRegInBuf[CURFF] = mcFocCtrl.focIqRef;
		NFOC_FCPS = mcFocCtrl.focIqRef;

		NFOC_IDREF = usSRegInBuf[MB_IDREF];
		usSRegInBuf[MB_IQREF] = NFOC_IQRORG;


#if OPENLOOP_ENABLE_TEST
		if (mcState == mcRun)
		{
			// Testing drive part and current sampling part: current loop open-loop
			mcElecAng.FOCThetaFlag = 1;
			NFOC_THETAH = usSRegHoldBuf[RESERVED3];

			NFOC_DUKH = usSRegHoldBuf[RESERVED1];
			NFOC_QUKH = usSRegHoldBuf[RESERVED2];
		}
#endif // #if OPENLOOP_ENABLE_TEST
	}
	else
	{
		usSRegInBuf[CMDCUR] = 0;
	}

	mcFocCtrl.ActualAngleRaw = mcFocCtrl.ActPos - mcFocCtrl.QepThetaOffset;
	usSRegInBuf[ACTPOSRAW_H] = mcFocCtrl.ActualAngleRaw >> 16;
	usSRegInBuf[ACTPOSRAW_L] = mcFocCtrl.ActualAngleRaw & 0xFFFF;

#if FUNC_PROBE_ENABLED > 0 || FUNC_PCOM_ENABLED > 0
	ProbePCOM_realize(mcFocCtrl.ActualAngle, 1 - mcEncoder.EncLoopTime);
#endif

#if SPECIAL_ELESCREW_ENABLE
	ScrewCtrl_Sample();
#endif

	usSRegInBuf[QEPPOS_H] = mcFocCtrl.QepPos >> 16;
	usSRegInBuf[QEPPOS_L] = mcFocCtrl.QepPos & 0xFFFF;
	usSRegInBuf[ACTVEL] = NFOC_SFOUT;
	usSRegInBuf[VELERR] = usSRegInBuf[CMDVEL] - usSRegInBuf[ACTVEL];
	usSRegInBuf[VELCTRLOUT] = NFOC_FFLT;

	usSRegInBuf[SCOPESTATUS] = Scope_DoSample(&usSRegInBuf[SCOPETRIGSTA]);
}



/*---------------------------------------------------------------------------
 * Name		:	PosControl_Isr
 * Input	:	No
 * Output	:	No
 * Description:	Position loop interrupt, including position command update and position loop controller
 *---------------------------------------------------------------------------*/
void PosControl_Isr(void)
{
	mcFocCtrl.PosLoopTimeLatch = mcFocCtrl.PosLoopTime; // To prevent PosLoopTime from being modified by EXTERN1_INT

#if EXCTRL_ENCOUT_ENABLED
	FreqDiv_Handler();
#endif // #if EXCTRL_ENCOUT_ENABLED


	if (!mcFocCtrl.PosLoopTime)
	{
		mcFocCtrl.PosLoopTime = 1;

		// Serial position & ECAT PP mode
		if ((mcRegParam.WorkMode == POSSERIAL)
#if EXCTRL_ECAT_ENABLED || EXCTRL_CANOPEN_ENABLED
			|| (usSRegInBuf[FBOPMODE] == PROFILE_POSITION_MODE) ||
			(usSRegInBuf[FBOPMODE] == HOMING_MODE)
#endif
			)
		{
#if FUNC_FORCECTRL_ENABLED
			if (usSRegHoldBuf[FCMOD]) // Force control mode
			{
				mcFocCtrl.TargetAngle = Motor_Profile_Move();
			}
			else
#elif SPECIAL_ELESCREW_ENABLE
			if (usSRegHoldBuf[ESCMOD]) // Electric screwdriver mode
			{
				mcFocCtrl.TargetAngle = Motor_Profile_Move();
			}
			else
#endif //#if FUNC_FORCECTRL_ENABLED
			{
				mcFocCtrl.TargetAngle = Motor_Profile_Move();
			}
		}

		// Pulse direction
#if EXCTRL_PULSE_ENABLED
		else if (mcRegParam.WorkMode == PULSEDIR)
		{
			mcFocCtrl.TargetAngle = Motor_Pulse_Handler();
		}

#endif // #if EXCTRL_PULSE_ENABLED

		// CSP
#if EXCTRL_ECAT_ENABLED || EXCTRL_CANOPEN_ENABLED || COMM_CAN_PDO_ENABLED
		else if (usSRegInBuf[FBOPMODE] == CYCLIC_SYNC_POSITION_MODE ||
			usSRegInBuf[FBOPMODE] == CYCLIC_SYNC_VELOCITY_MODE ||
			usSRegInBuf[FBOPMODE] == CYCLIC_SYNC_TORQUE_MODE)
		{
			mcFocCtrl.TargetAngle = ECATCSP_PosCmd();
		}
#endif // #if EXCTRL_ECAT_ENABLED || EXCTRL_CANOPEN_ENABLED

#if COMM_CAN_PDO_ENABLED
		else if (usSRegInBuf[FBOPMODE] == INTERPOLATION_POSITION_MODE)
		{
			mcFocCtrl.TargetAngle = DynTrap_Demo_Next();
		}
#endif // #if COMM_CAN_PDO_ENABLED

		usSRegInBuf[CMDPOSRAW_H] = mcFocCtrl.TargetAngle >> 16;
		usSRegInBuf[CMDPOSRAW_L] = mcFocCtrl.TargetAngle & 0xFFFF;
	}
	else if (mcFocCtrl.PosLoopTime) // PosLoop: 4kHz
	{
		mcFocCtrl.PosLoopTime = 0;

#if FUNC_ERRORCORRECTION_ENABLED
#if FUNC_FEEDBACKONLOAD_ENABLED
		if (FEEDBACK_MOTOR == Feedback_GetOnLoadFlag())
		{
			mcFocCtrl.ActualAngle = ErrorCorrection_realize(mcFocCtrl.ActualAngleRaw);
			mcEncoder.LoadEncPos = mcFocCtrl.ActLoadPos;
		}
		else
#endif
		{
			mcFocCtrl.ActualAngle = mcFocCtrl.ActualAngleRaw;
			mcEncoder.LoadEncPos = ErrorCorrection_realize(mcFocCtrl.ActLoadPos);
		}
#else
		mcFocCtrl.ActualAngle = mcFocCtrl.ActualAngleRaw;
		mcEncoder.LoadEncPos = mcFocCtrl.ActLoadPos;
#endif

#if FUNC_GAINSW_ENABLED
		GainSW_Demo_realize();
#endif //#if FUNC_GAINSW_ENABLED

#if FUNC_FEEDBACKONLOAD_ENABLED
		FeedBackOnLoad_Update();  // Full closed-loop update parameters
		*((int32*) & usSRegInBuf[LOADVEL_L]) = LoadPosFdbCalc_realize();
#endif

#if FUNC_CURRENTBACK_ENABLED
		CurrBackProtect_realize(&MotorCurrBack);
#endif

		if (mcFocCtrl.PosLoopEnable)
		{
			DeltaTargetRefCalc();

#if FUNC_TOQFF_ENABLED
			SpdErrCal_realize();
#else
			usSRegInBuf[PTPVCMD] = mcFocCtrl.TargetRef;
#endif //#if FUNC_TOQFF_ENABLED

			// Speed feedforward
#if FUNC_SPDFF_ENABLED
			usSRegInBuf[SPEEDFF] = SpdFF_realize((int16)mcFocCtrl.TargetRef);
#endif //#if FUNC_SPDFF_ENABLED

			// Position command filtering
#if EXCTRL_ECAT_ENABLED || EXCTRL_CANOPEN_ENABLED
			if (usSRegInBuf[FBOPMODE] != CYCLIC_SYNC_POSITION_MODE)
#endif
			{
#if FUNC_INPUTFILT_ENABLED
				mcFocCtrl.TargetRef = InputPosFilter_realize(mcFocCtrl.TargetRef, &InFilt1PosRef);
#if FUNC_DUALFILT_POSREF
				mcFocCtrl.TargetRef = InputPosFilter_realize(mcFocCtrl.TargetRef, &InFilt2PosRef);
#endif //#if FUNC_DUALFILT_POSREF
#endif //#if FUNC_INPUTFILT_ENABLED
			}

			// End-of-arm vibration suppression
#if FUNC_NTF_ENABLED
			if (mcState == mcRun)
				mcFocCtrl.TargetRef = NTF_realize(mcFocCtrl.TargetRef);
#endif //#if FUNC_NTF_ENABLED

			mcFocCtrl.TargetAngleSum += mcFocCtrl.TargetRef;

			mcFocCtrl.TargetAngleFilt = mcFocCtrl.TargetAngleSum;

#if FUNC_FEEDBACKONLOAD_ENABLED
			mcFocCtrl.ThetaErr = PosErrCalc_realize();
#else
			mcFocCtrl.ThetaErr = mcFocCtrl.TargetAngleFilt - mcFocCtrl.ActualAngle;
#endif


			// Gain switching
#if FUNC_GAINSW_ENABLED
			GainSwitching_realize(&PID_Pos, GNSWCTRL_POS);
#else
			GetGnFir(&PID_Pos);
#endif //#if FUNC_GAINSW_ENABLED

#if FUNC_SOFTCTRL_ENABLED
			if ((SC_WorkMode != SC_MODE_OFF)
				&& (FieldSoftControl_GetSwToPosDoneFlag() == 0))
			{
				usSRegInBuf[CMDVEL] = FieldSoftControl_realize(mcFocCtrl.ThetaErr);
			}
			else
			{
				usSRegInBuf[CMDVEL] = PI_Pos_realize(mcFocCtrl.ThetaErr);
			}
#else
			usSRegInBuf[CMDVEL] = PI_Pos_realize(mcFocCtrl.ThetaErr);
#endif

		}
		else
		{
			usSRegInBuf[PTPVCMD] = 0;
		}
		usSRegInBuf[CMDPOS_H] = mcFocCtrl.TargetAngleFilt >> 16;
		usSRegInBuf[CMDPOS_L] = mcFocCtrl.TargetAngleFilt & 0xFFFF;
		usSRegInBuf[ACTPOS_H] = mcFocCtrl.ActualAngle >> 16;
		usSRegInBuf[ACTPOS_L] = mcFocCtrl.ActualAngle & 0xFFFF;
		usSRegInBuf[POSERR_H] = mcFocCtrl.ThetaErr >> 16;
		usSRegInBuf[POSERR_L] = mcFocCtrl.ThetaErr & 0xFFFF;
		usSRegInBuf[SFBACTPOS_H] = mcEncoder.LoadEncPos >> 16;
		usSRegInBuf[SFBACTPOS_L] = mcEncoder.LoadEncPos & 0xFFFF;
	}


#if FUNC_INERTIA_ENABLED
	// Inertia identification
	if (mcFocCtrl.VelLoopEnable)
	{
		usSRegInBuf[LMJRSTATUS] = InFricId_realize((uint32*) & usSRegInBuf[LMJRRESULT_L]);
	}
#endif //#if FUNC_INERTIA_ENABLED



#if EXCTRL_ECAT_ENABLED

if (SYNC0_Flag == 1 && mcRegParam.WorkMode == COMM_ECAT)
	{
#if ECAT_SPI_DMA_ISR_ENABLED
		PDI_Step_Isr();
#else
		PDI_Isr();
		SYNC0_Flag = 0;
#endif
	}
#endif //#if EXCTRL_ECAT_ENABLED


}



/*---------------------------------------------------------------------------
 * Name		:	DeltaTargetRefCalc
 * Input	:	No
 * Output	:	No
 * Description:	Calculate position command increment
 *---------------------------------------------------------------------------*/
void DeltaTargetRefCalc(void)
{
	if (mcFocCtrl.TargetRefFirstFlag == 0)
	{
		if (mcFocCtrl.ModeSwitchFlag == 1)
		{
			mcFocCtrl.TargetAngle = mcProfile.StartingAngle;
			mcFocCtrl.ModeSwitchFlag = 0;
		}

		mcFocCtrl.TargetRefFirstFlag = 1;
		mcFocCtrl.TargetAngleLatch = mcFocCtrl.TargetAngle;
		mcFocCtrl.TargetAngleSum = mcFocCtrl.TargetAngle;
		mcFocCtrl.TargetRef = 0;
	}
	else
	{
		mcFocCtrl.TargetRef = mcFocCtrl.TargetAngle - mcFocCtrl.TargetAngleLatch;
		mcFocCtrl.TargetAngleLatch = mcFocCtrl.TargetAngle;
	}

}