/*
 * Copyright (c) 2023-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : MotorControl.c
 * Author        : Summer
 * Date          : 2023-05-11
 * Description   : 载波中断和位置环中断函数
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


/*---------------------------------------------------------------------------*/
/* Name		:	void ServoControl_Isr(void)
/* Input	:	NO
/* Output	:	NO
/* Description:	Servo Control Interrupt, MMT, Filer, PDFF are done in hardware.
/*---------------------------------------------------------------------------*/
void ServoControl_Isr(void)
{
#if DRV32K_ENABLE_SWITCH
	// 32K电流环改比较值触发点操作方式
	mcFocCtrl.DrvComrVal = 1 - mcFocCtrl.DrvComrVal; // 初始值为0，Drv初始化第一次为下降计数触发，故此处进来第一次切换成上升计数触发
	if (mcFocCtrl.DrvComrVal)
	{
		clr_csr(DRV1_IER, DCIM1);				// 01：上升方向
		set_csr(DRV1_IER, DCIM0);
		write_csr(DRV1_COMR, PWM_VALUE_UPLOAD);		// 下次触发中断条件为 上升计数方向且COMR=0时
	}
	else
	{
		set_csr(DRV1_IER, DCIM1);				// 10：下降方向
		clr_csr(DRV1_IER, DCIM0);
		write_csr(DRV1_COMR, PWM_VALUE_DOWNLOAD);	// 下次触发中断条件为 下降计数方向且COMR=ARR时
	}
#endif // #if DRV32K_ENABLE_SWITCH

	// get encoder value at the very beginnig, to make sure velocity is correct.
	Encoder_GetPos(&mcFocCtrl.QepPos, &mcFocCtrl.QepPosMulti, &QEP.MT_Qep_Margin, &usSRegInBuf[ENCODERERR]);

	if (mcFocCtrl.AngDir)
	{
		mcFocCtrl.ActPos = -mcFocCtrl.QepPos; // 显示位置
	}
	else
	{
		mcFocCtrl.ActPos = mcFocCtrl.QepPos;
	}

	NFOC_OMEFLTH = usSRegInBuf[ACTVEL];

	NFOC_MQEP = mcFocCtrl.ActPos;
	NFOC_MBLK = read_csr(TIM2_QEP_TS_EMP);
	NFOC_MREM = read_csr(TIM2_QEP_TNUM);

	NFOC_PDCMD = usSRegInBuf[CMDVEL]; // 速度指令
	NFOC_WUCPS = usSRegInBuf[ACCFF]; // 转矩前馈


#if FUNC_FEEDBACKONLOAD_ENABLED
	if (mcFocCtrl.LoadAngDir)
	{
		mcFocCtrl.ActLoadPos = -mcEncoder.LoadQepPos; // 显示位置
	}
	else
	{
		mcFocCtrl.ActLoadPos = mcEncoder.LoadQepPos;
	}

	if (mcFocCtrl.MultiOffsetFirstFlag == 0) // 为了让mcFocCtrl.ActLoadPos的初始值在一圈内
	{
		mcFocCtrl.ActLoadPos = mcFocCtrl.ActLoadPos - mcFocCtrl.QEPLoadThetaOffset;
		if (++mcFocCtrl.MultiOffsetFirstCounter > 160)
		{
			mcFocCtrl.MultiOffsetFirstFlag = 1;
			mcFocCtrl.QEPLoadMultiOffset = mcFocCtrl.ActLoadPos & (~(*((int32*) & usSRegHoldBuf[SFBENCRES_L]) - 1));
			mcFocCtrl.ActLoadPos -= mcFocCtrl.QEPLoadMultiOffset;
		}
	}
	else
	{
		mcFocCtrl.ActLoadPos = mcFocCtrl.ActLoadPos - mcFocCtrl.QEPLoadThetaOffset - mcFocCtrl.QEPLoadMultiOffset;
	}

	usSRegInBuf[SFBACTPOSRAW_H] = mcFocCtrl.ActLoadPos >> 16;
	usSRegInBuf[SFBACTPOSRAW_L] = mcFocCtrl.ActLoadPos & 0xFFFF;
#endif

	// 模拟速度 & 模拟电流 & 串行压力环模式
#if EXCTRL_ANALOG_ENABLED
	if ((mcRegParam.WorkMode == VELANALOG
		|| mcRegParam.WorkMode == CURANALOG
#if FUNC_FORCECLOSEDLOOP_ENABLED
		|| mcRegParam.WorkMode == FRCSERIAL	//压力环调试
		|| (usSRegHoldBuf[FCMOD] == FCMODE_CLOSEDLOOP_ONCE)	//闭环力控单次执行
		|| (usSRegHoldBuf[FCMOD] == FCMODE_CLOSEDLOOP_REPEAT)	//闭环力控重复执行
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

#if DEADTIME_COMPENSATE_ENABLED // 死区补偿
	DeadTimeCompensationController(NFOC_THETAH, NFOC_IDFLTH, NFOC_IQFLTH);
#endif

	if (readbit_csr(DRV1_FCR5, WPI_SERVO_EN)) // 跟硬件速度环的计算做个对齐
		mcFocCtrl.VelCnt = 0;

#if EXCTRL_ENCOUT_ENABLED
	QEP.MT_Act_Margin = NFOC_MDEL;
	QEP.MT_Qep_Margin_Sum += NFOC_MDEL;
#endif // #if EXCTRL_ENCOUT_ENABLED

//#if FUNC_FEEDBACKONLOAD_ENABLED  // 全闭环更新参数
//	FeedBackOnLoad_Demo_Update();
//#endif

	///////**************** Start Vel Loop 860ns ****************/////////
	if (++mcFocCtrl.VelCnt >= (uint16)DRIVERINT_FREQUENCY / ((uint16)POSCTRL_FREQUENCY << 1))
	{
		mcFocCtrl.VelCnt = 0;

		mcFocCtrl.VelLoopTime = 1;

#if EXCTRL_ENCOUT_ENABLED
		QEP.MT_Qep_Margin_Delta = QEP.MT_Qep_Margin_Sum;	// 计算外环周期两拍之间脉冲数差值

		QEP.MT_Qep_Margin_Sum = 0;
#endif // #if EXCTRL_ENCOUT_ENABLED

		Timer3_Enable();

		mcFocCtrl.Timer1msCount++;
		if (mcFocCtrl.Timer1msCount >= ((uint16)POSCTRL_FREQUENCY << 1))	// 1ms一次mainloop
		{
			TimerFlag_1ms = 1;
			mcFocCtrl.Timer1msCount = 0;
		}
	}

	///////**************** Start Vel Loop End ****************/////////

	///////////**************** VelLoop PI Controller ****************/////////
	// Here the satuation of VelErr should be deal with.
	if (mcFocCtrl.VelLoopTime)	 // VelLoop: 8kHz
	{
		mcFocCtrl.VelLoopTime = 0;

#if FUNC_SOFTCTRL_ENABLED
		if ((mcFocCtrl.VelLoopEnable) || FieldSoftControl_GetSwToPosFlag())
#else
			if (mcFocCtrl.VelLoopEnable)
#endif
			{
	///////**************** Update MT ActVel end ****************/////////
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
						usSRegInBuf[CMDVEL] = (int16)CiA402_TargetVelocity; // 速度指令来源于ECAT
					}
#endif

			//增益切换
#if FUNC_GAINSW_ENABLED
					GainSwitching_realize(&PID_Speed, GNSWCTRL_SPD);
#else
					GetGnFir(&PID_Speed);
#endif //#if FUNC_GAINSW_ENABLED

					Hard_PI_Gain_Update();

			//转矩前馈
#if FUNC_TOQFF_ENABLED
					usSRegInBuf[ACCFF] = ToqFF_realize();
//			NFOC_WUCPS = usSRegInBuf[ACCFF];  // 挪到前面
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

	///////**************** Cur Loop Enable 1.08us ****************/////////
	if (mcFocCtrl.CurLoopEnable)
	{
		mcFocCtrl.focIqRef = 0; // 清零Q轴补偿
#if FUNC_MOTOREST_ENABLED
		if ((mcState == mcMotorIdentify) && (McStaSet.SetFlag.IdentifySetFlag == 1))
		{
			Motor_Inductance_Identify_realize_Isr();
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
				usSRegInBuf[CMDCUR] = CiA402_TargetTorque; // 力矩指令来源于ECAT
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
		// 摩擦力补偿
		mcFocCtrl.focIqRef += FricCmp_realize();
#endif

		usSRegInBuf[CURFF] = mcFocCtrl.focIqRef;
		NFOC_FCPS = mcFocCtrl.focIqRef;

		NFOC_IDREF = usSRegInBuf[MB_IDREF];
		usSRegInBuf[MB_IQREF] = NFOC_IQRORG;


#if OPENLOOP_ENABLE_TEST
		if (mcState == mcRun)
		{
			// 测试驱动部分和电流采样部分: 电流环开环
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

	mcFocCtrl.ActualAngleRaw = mcFocCtrl.ActPos - mcFocCtrl.QEPThetaOffset;
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



/*---------------------------------------------------------------------------*/
/* Name		:	void PosControl_Isr(void)
/* Input	:	NO
/* Output	:	NO
/* Description:	Position Loop Control Interrupt.
/*---------------------------------------------------------------------------*/
void PosControl_Isr(void)
{
	mcFocCtrl.PosLoopTimeLatch = mcFocCtrl.PosLoopTime; // 以防PosLoopTime被EXTERN1_INT修改

#if EXCTRL_ENCOUT_ENABLED
	FreqDiv_Handler();
#endif // #if EXCTRL_ENCOUT_ENABLED


	if (!mcFocCtrl.PosLoopTime)
	{
		mcFocCtrl.PosLoopTime = 1;

//		CANSpec_cycle_process();
		// 串行位置 & ECAT PP模式
		if ((mcRegParam.WorkMode == POSSERIAL)
#if EXCTRL_ECAT_ENABLED || EXCTRL_CANOPEN_ENABLED
			|| (usSRegInBuf[FBOPMODE] == PROFILE_POSITION_MODE) ||
			(usSRegInBuf[FBOPMODE] == HOMING_MODE)
#endif
			)
		{
#if FUNC_FORCECTRL_ENABLED
			if (usSRegHoldBuf[FCMOD]) // 力控模式
			{
				mcFocCtrl.TargetAngle = Motor_Profile_Move();
			}
			else
#elif SPECIAL_ELESCREW_ENABLE
				if (usSRegHoldBuf[ESCMOD]) // 电批模式
				{
					mcFocCtrl.TargetAngle = Motor_Profile_Move();
				}
				else
#endif //#if FUNC_FORCECTRL_ENABLED
				{
					mcFocCtrl.TargetAngle = Motor_Profile_Move();
				}
		}

		// 脉冲方向
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
		FeedBackOnLoad_Update();  // 全闭环更新参数
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
#endif //#if FUNC_TOQFF_ENABLED

			//速度前馈
#if FUNC_SPDFF_ENABLED
			usSRegInBuf[SPEEDFF] = SpdFF_realize((int16)mcFocCtrl.TargetRef);
#endif //#if FUNC_SPDFF_ENABLED

			//位置指令滤波
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

			//末端抖动抑制
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


			//增益切换
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
	//惯量辨识
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



//	usSRegInBuf[SCOPESTATUS] = Scope_DoSample(&usSRegInBuf[SCOPETRIGSTA]);
}



/*---------------------------------------------------------------------------*/
/* Name		:	DeltaTargetRefCalc
/* Input	:	NO
/* Output	:	NO
/* Description:	
/*---------------------------------------------------------------------------*/
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