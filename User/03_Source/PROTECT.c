/*
 * Copyright (c) 2021-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : PROTECT.c
 * Author        : Summer
 * Date          : 2021-11-13
 * Description   : define some protect function.
 *
 * Record        :
 * V1.0, 2021-11-13, Summer: Created file
 */


/********************************************************************************
* Header Definition
********************************************************************************/
#include <Myproject.h>
#include "PROTECT.h"

/********************************************************************************
* Macro & Structure Definition
*******************************************************************************/
CurrentVarible mcCurVarible __attribute__((section(".pram.data.mcCurVarible"))) = { 0 };
FaultVarible mcFaultDect __attribute__((section(".pram.data.mcFaultDect"))) = { 0 };
uint16 mcFaultSource = FaultNoSource;
uint16 mcWarnSource = FaultNoSource;
uint8 mcFaultSourceSize[3] = { 0, 22, 31 };


const uint16 EncErrParaArray[ENCERRARRAYSIZE][2] = {
#if ENCODER_SEL_BISS_ENABLED
	{ FaultBiSSErr, FAULT_BISS_ERR },
	{ FaultBiSSWarn, FAULT_BISS_WARN },
	{ FaultEncCRC, FAULT_ENC_CRC },
	{ FaultEncTimeOut, FAULT_ENC_OT },
#endif // #if ENCODER_SEL_BISS_ENABLED

#if ENCODER_SEL_TMG_ENABLED
	{ FaultEncCRC, FAULT_REG_CRCERR },
	{ FaultEncComError, FAULT_ENC_PARERR | FAULT_ENC_DELERR | FAULT_REG_SYNERR | FAULT_REG_REQERR },
	{ FaultEncBatteryErr, FAULT_ENC_BE },
	{ FaultEncBatteryWarn, FAULT_ENC_BA },
	{ FaultEncInternal, FAULT_REG_INTERR | FAULT_ENC_OS | FAULT_ENC_FS | FAULT_ENC_CE
		| FAULT_ENC_OF | FAULT_ENC_OH | FAULT_ENC_ME },
	{ FaultEncTimeOut, FAULT_REG_ROTERR },
#endif // #if ENCODER_SEL_TMG_ENABLED
};

const uint8 EncErrFlagArray[ENCERRARRAYSIZE] = {
#if ENCODER_SEL_BISS_ENABLED
	FLAGBIT_BISSERR,
	FLAGBIT_BISSWARN,
	FLAGBIT_ENCCRC,
	FLAGBIT_ENCOT,
#endif // #if ENCODER_SEL_BISS_ENABLED

#if ENCODER_SEL_TMG_ENABLED
	FLAGBIT_ENCCRC,
	FLAGBIT_ENCCOM,
	FLAGBIT_BATERR,
	FLAGBIT_BATWARN,
	FLAGBIT_ENCINT,
	FLAGBIT_ENCOT,
#endif // #if ENCODER_SEL_TMG_ENABLED
};



/********************************************************************************
* Internal Routine Prototypes
********************************************************************************/

/*---------------------------------------------------------------------------*/
/* Name		:	void Fault_Detection(void)
/* Input	:	NO
/* Output	:	NO
/* Description:	保护函数，因保护的时间响应不会很高，采用分段处理，每5个定时器中断执行一次对应的保护
常见保护有过欠压、过温、堵转、启动、缺相等保护，调试时，可根据需求，一个个的调试加入。
/*---------------------------------------------------------------------------*/
void Fault_Detection(void)
{

#if FUNC_STO_ENABLED
	Fault_STO(&mcFaultDect);
#endif

#if ((HardwareCurrent_Protect == Hardware_FO_Protect) || (HardwareCurrent_Protect == Hardware_FO_CMP_Protect))
	Fault_HardOvercurrent(&mcFaultDect);	// 硬件峰值电流过流
#endif

	Fault_PeakOvercurrent(&mcCurVarible);	// 软件峰值电流过流

#if FUNC_CURRENTBACK_ENABLED
	Fault_FoldBackCurrent(&mcFaultDect);    // 电流折返：过载保护
#else
	Fault_RMSOvercurrent(&mcCurVarible);	// RMS过流
#endif

	Fault_OverPosErr(&mcFaultDect);		// 位置超差错误

	Fault_OverVelErr(&mcFaultDect);		// 速度超差错误

	Fault_OverSpeed(&mcFaultDect);			// 速度过超错误

	Fault_OverUnderVoltage(&mcFaultDect);	// 过欠压保护

	Fault_OverTemperature(&mcFaultDect);	// 过温

	Fault_PhaseLoss(&mcFaultDect);			// 缺相

	Fault_Stall(&mcFaultDect);				// 堵转

	Fault_ParamError(&mcFaultDect);			//参数错误

	Fault_Encoder(&mcFaultDect);			// 编码器错误

#if FUNC_FEEDBACKONLOAD_ENABLED
	Fault_MixErrOver(&mcFaultDect);         // 混合偏差过大报警
#endif

#if ENCODER_SEL_HALL_ENABLED
	Fault_Hall(&mcFaultDect);				// Hall错误
#endif

#if EXCTRL_ENCOUT_ENABLED
	Fault_EncOutFreqTooHigh(&mcFaultDect); // 分频输出频率过高错误
#endif

	Fault_MainIntPeriodTimeOut(&mcFaultDect); // 载波中断周期过长错误

	Fault_ExceedPositionLimit(&mcFaultDect); // 超出位置限位


	// 设置报错标志位
	if (mcFaultSource != FaultNoSource)
	{
		FaultProcess();
		SetReg(usSRegInBuf[DRIVESTATUS], STATUS_FAULT, STATUS_FAULT);
	}
	else
	{
		SetReg(usSRegInBuf[DRIVESTATUS], STATUS_FAULT, 0);
	}

	// 如果只有warning，没有error，个别警告如FLAG_ECAT、FLAG_CUROFF会清不掉
	if (GetReg(usSRegHoldBuf[DRIVECTRL], CTRL_CLEARERR) || GetReg(usSRegInBuf[DIGINSTATUS], INSTATUS_CLEARFAULT))
	{
		usSRegInBuf[WARNSTATUS0] = 0;
		usSRegInBuf[WARNSTATUS1] = 0;
	}

	if (usSRegInBuf[WARNSTATUS0] != 0 || usSRegInBuf[WARNSTATUS1] != 0)
	{
		SetReg(usSRegInBuf[DRIVESTATUS], STATUS_WARNING, STATUS_WARNING);
	}
	else
	{
		SetReg(usSRegInBuf[DRIVESTATUS], STATUS_WARNING, 0);
		mcWarnSource = FaultNoSource;
	}
}


/*---------------------------------------------------------------------------*/
/* Name		:	void FaultProcess(void)
/* Input	:	NO
/* Output	:	NO
/* Description:	保护处理函数，关闭FOC输出，同时将状态变为mcFault
/*---------------------------------------------------------------------------*/
void FaultProcess(void)
{
	uint8 i = 0;
	uint16* pErrorStatus = &usSRegInBuf[ERRORSTATUS0];
	
	if (GetReg(usSRegInBuf[DRIVESTATUS], STATUS_ENABLE))
	{
		if (mcFaultSource == FaultHardOVCurrent || mcFaultSource == FaultPeakOVCurrent \
			|| mcFaultSource == FaultRMSOVCurrent || mcFaultSource == FaultOverVoltage)
		{
			clr_csr(DRV1_CR, DRVOE);			// Driver输出使能	0-->Disable		1-->Enable
			clr_csr(DRV1_OUT, MOE);		//主输出使能，用于选择三相上下桥信号来源
			clr_csr(DRV1_FCR0, NCALEN);	// 关FOC计算使能
			McStaSet.SetFlag.BrakeFlag = 0;
			mcState = mcDisable;
		}
		else
		{
			if (mcState != mcDisable && mcState != mcFault) // 避免重复请求停车
			{
				McStaSet.SetFlag.BrakeFlag = 0;
				mcState = mcDisable;
			}
		}
	}
	
	if (mcFaultSource != FaultNoSource)
	{
		for (i = 0; i < 3; i++)
		{
			if (*pErrorStatus == FaultNoSource)
			{
				*pErrorStatus = mcFaultSource;
				Fault_AddErrorHistory(mcFaultSource);
				break;
			}
			else if (i < 2 && *pErrorStatus == mcFaultSource) 
			{
				break; // do nothing
			} 
			pErrorStatus++;
		}
	}
}



/*---------------------------------------------------------------------------*/
/* Name		:	void FaultClear(void)
/* Input	:	NO
/* Output	:	NO
/* Description:	清除报错
/*---------------------------------------------------------------------------*/
void FaultClear(void)
{
	mcFaultSource = FaultNoSource;
	mcWarnSource = FaultNoSource;
	usSRegInBuf[WARNSTATUS0] = 0;
	usSRegInBuf[WARNSTATUS1] = 0;

	usSRegInBuf[ERRORSTATUS0] = FaultNoSource;
	usSRegInBuf[ERRORSTATUS1] = FaultNoSource;
	usSRegInBuf[ERRORSTATUS2] = FaultNoSource;
}


/*---------------------------------------------------------------------------*/
/* Name		:	void Fault_AddErrorHistory(void)
/* Input	:	NO
/* Output	:	NO
/* Description:	将报错加载到报错历史列表里。
/*---------------------------------------------------------------------------*/
void Fault_AddErrorHistory(uint16 FaultSrc)
{
	uint16 currentTime = 0, currentPointer = 0;
	
	if (mcFaultDect.ErrorHistPointer >= MAXERRHISTPOINTER)
		mcFaultDect.ErrorHistPointer = 0;
	
	currentTime = mcFaultDect.ErrorHistFlag + (mcFaultDect.CurrentMinute & 0x7FFF);
	currentPointer = mcFaultDect.ErrorHistPointer;

	*(mcFaultDect.pErrorHist + (mcFaultDect.ErrorHistPointer++)) = currentTime;
	*(mcFaultDect.pErrorHist + (mcFaultDect.ErrorHistPointer++)) = FaultSrc;

	mcFaultDect.ErrorHistFlag = 0x8000 - mcFaultDect.ErrorHistFlag;

#if FUNC_EEPROM_ENABLED
	if (!EEPROM_WriteBytes(EEPROM_ERR_ADDR_START + (currentPointer << 1), 
		(uint8*)(mcFaultDect.pErrorHist + currentPointer), 4));
	{
		// EEPROM write error
	}
#endif //#if FUNC_EEPROM_ENABLED
}

/*****************************************************************************
 * Function:	void	Fault_OverVoltage(mcFaultVarible *h_Fault)
 * Description:	更新下一个报错的ErrorHistPointer和ErrorHistFlag
 * Parameter:		 mcFaultVarible *h_Fault
 * Return:			 no
 *****************************************************************************/
void Fault_UploadErrCode()
{
	uint8 counter = 0;
	uint16 faultFlag, faultFlagPre, faultSrc, faultSrcPre;
	uint16* pFaultHist = &usSRegInBuf[ERRORTIME0];
	
	if (!mcFaultDect.ErrorHistFirstFlag) // 程序运行后第一次加载
	{
#if FUNC_EEPROM_ENABLED
		if (!EEPROM_ReadBytes(EEPROM_ERR_ADDR_START, (uint8*) pFaultHist, EEPROM_ERR_ADDR_SIZE))
		{
			// EEPROM read error
		}
		else
#endif //#if FUNC_EEPROM_ENABLED
		
		{
			faultFlagPre = (*(pFaultHist + (MAXERRHIST << 1) - 2)) & 0x8000;
			faultFlag = (*pFaultHist) & 0x8000;
			faultSrcPre = (*(pFaultHist + (MAXERRHIST << 1) - 1));
			faultSrc = *(pFaultHist + 1);

			
			if (faultSrc == FaultNoSource)
			{
				mcFaultDect.ErrorHistPointer = 0;
				mcFaultDect.ErrorHistFlag = faultFlag;
			}
			else if (faultSrc != FaultNoSource && faultSrcPre != FaultNoSource && faultFlag == faultFlagPre)
			{
				mcFaultDect.ErrorHistPointer = 0;
				mcFaultDect.ErrorHistFlag = 0x8000 - faultFlagPre;
			}
			else
			{
				pFaultHist = pFaultHist + 2;
				for (counter = 1; counter < MAXERRHIST; counter++)
				{
					faultFlagPre = faultFlag;
					faultFlag = (*pFaultHist) & 0x8000;
					faultSrcPre = faultSrc;
					faultSrc = *(pFaultHist + 1);
					pFaultHist = pFaultHist + 2;

					if (faultSrc == FaultNoSource && faultFlag == 0)
					{
						mcFaultDect.ErrorHistPointer = counter << 1;
						mcFaultDect.ErrorHistFlag = faultFlag;
						break;
					}
					else if (faultSrc != FaultNoSource && faultSrcPre != FaultNoSource && faultFlag == faultFlagPre)
					{
						mcFaultDect.ErrorHistPointer = counter << 1;
						mcFaultDect.ErrorHistFlag = 0x8000 - faultFlagPre;
						break;
					}
				}
			}
		}
		mcFaultDect.ErrorHistFirstFlag = 1;
	}
}

/*****************************************************************************
 * Function:	void	Fault_OverUnderVoltage(mcFaultVarible *h_Fault)
 * Description:	 过欠压保护函数：母线电压大于过压保护值时，
 * 计数器加一，计数器值超过20次，判断为过压保护，关闭输出;反之，计数器慢慢减
 * Parameter:		 mcFaultVarible *h_Fault
 * Return:			 no
 *****************************************************************************/
void Fault_OverUnderVoltage(FaultVarible* h_Fault)
{
#if PROT_OUVP_HARDWARE_ENABLED
	NFOC_OVP = usSRegHoldBuf[OVERVOLTAGE];    // 过压保护阈值
	if (usSRegHoldBuf[OVERVOLTIME] > 255)
		NFOC_OVPARR = 255;
	else
		NFOC_OVPARR = usSRegHoldBuf[OVERVOLTIME]; // 过压保护计数目标值

	NFOC_UVP = usSRegHoldBuf[UNDERVOLTAGE];    // 欠压保护阈值
	if (usSRegHoldBuf[UNDERVOLTIME] > 255)
		NFOC_UVPARR = 255;
	else
		NFOC_UVPARR = usSRegHoldBuf[UNDERVOLTIME]; // 欠压保护计数目标值

	set_csr(DRV1_PTR, OUVP_TRG);
	
#else	
	//过压保护
	//母线电压大于过压保护值时，计数，超过50次，判断为过压保护，关闭输出;反之，计数器慢慢减
	if (usSRegInBuf[BUSVOLTAGE] > usSRegHoldBuf[OVERVOLTAGE])
	{
		h_Fault->OverVoltDetecCnt++;
		if (h_Fault->OverVoltDetecCnt > usSRegHoldBuf[OVERVOLTIME])
		{
			h_Fault->OverVoltDetecCnt = 0;
			mcFaultSource = FaultOverVoltage;
			FaultProcess();
		}
	}
	else
	{
		if (h_Fault->OverVoltDetecCnt > 0)
		{
			h_Fault->OverVoltDetecCnt--;
		}
	}
	
	//欠压保护
	//母线电压大于欠压保护值时，计数，超过50次，判断为欠压保护，关闭输出;反之，计数器慢慢减
	if (usSRegInBuf[BUSVOLTAGE] < usSRegHoldBuf[UNDERVOLTAGE])
	{
		h_Fault->UnderVoltDetecCnt++;

		if (h_Fault->UnderVoltDetecCnt > usSRegHoldBuf[UNDERVOLTIME])//检测50ms
		{
			h_Fault->UnderVoltDetecCnt = 0;
			mcFaultSource = FaultUnderVoltage;
			FaultProcess();
		}
	}
	else
	{
		if (h_Fault->UnderVoltDetecCnt > 0)
		{
			h_Fault->UnderVoltDetecCnt--;
		}
	}
#endif // #if PROT_OUVP_HARDWARE_ENABLED
}



/*****************************************************************************
 * Function:		 void Fault_PeakOvercurrent(CurrentVarible *h_Cur)
 * Description:	 电机运行或者启动时，当三相中某一相最大值大于OverCurrentValue，则OverCurCnt加1。
 连续累加3次，判断为软件过流保护。执行时间约30.4us。
 * Parameter:		 mcFaultVarible *h_Fault
 * Return:			 no
 *****************************************************************************/
void Fault_PeakOvercurrent(CurrentVarible* h_Cur)
{
	uint32 Cnt;
	int16 Abs_peak = ABS(MIN(usSRegHoldBuf[DRIVERPEAKCUR], usSRegHoldBuf[PEAKCURRENT]));
	
	if (mcFocCtrl.CurLoopEnable == 1)						// check over current in rum and open mode
	{
		h_Cur->Abs_ia = ABS((int16) usSRegInBuf[MB_IA]);
		h_Cur->Abs_ib = ABS((int16) usSRegInBuf[MB_IB]);
		h_Cur->Abs_ic = ABS((int16) usSRegInBuf[MB_IC]);

		// Peak over current error detection
		if ((h_Cur->Abs_ia >= Abs_peak) || (h_Cur->Abs_ib >= Abs_peak)
			|| (h_Cur->Abs_ic >= Abs_peak))
		{
			h_Cur->OverCurCnt++;
			if (h_Cur->OverCurCnt >= usSRegHoldBuf[PEAKCURTIME])
			{
				h_Cur->OverCurCnt = 0;
				mcFaultSource = FaultPeakOVCurrent;
				FaultProcess();
			}
		}
		else
		{
			if (h_Cur->OverCurCnt > 0)
				h_Cur->OverCurCnt--;
		}
	}
	
	
#if PROT_SOCP_HARDWARE_ENABLED
	Abs_peak = ABS(MIN(usSRegHoldBuf[DRIVERPEAKCUR], usSRegHoldBuf[HARDCURRENT]));
	NFOC_SOCP = Abs_peak;// 过流保护阈值
	NFOC_SOCPARR = 5;
	
//	if (h_Cur->PeakCurLatch != usSRegHoldBuf[PEAKCURTIME])
//	{
//		h_Cur->PeakCurLatch = usSRegHoldBuf[PEAKCURTIME];
//		Cnt = (uint32)usSRegHoldBuf[PEAKCURTIME] * DRIVERINT_FREQUENCY;
//		if (Cnt > 255)
//		{
//			NFOC_SOCPARR = 255;// 过流保护计数目标值
//			h_Cur->PeakCurArr = (Cnt >> 8) & 0xFFFFFF;
//		}
//		else
//		{
//			NFOC_SOCPARR = Cnt & 0xFF;// 过流保护计数目标值
//			h_Cur->PeakCurArr = 0;
//		}
//		mcCurVarible.PeakCurCnt = 0;
//	}

#endif // #if PROT_SOCP_HARDWARE_ENABLED
}


/*****************************************************************************
 * Function:		 void Fault_RMSOvercurrent(CurrentVarible *h_Cur)
 * Description:	 电机运行或者启动时，当三相中某一相累加和大于RMSSoftCurrentValue，则
 *               判断为软件RMS过流保护。累加次数为RMSCURTIME。
 * Parameter:		 mcFaultVarible *h_Fault
 * Return:			 no
 *****************************************************************************/
void Fault_RMSOvercurrent(CurrentVarible* h_Cur)
{
	if (mcFocCtrl.CurLoopEnable == 1)						// check over current in rum and open mode
	{
		h_Cur->RMSSumThreshold = ((uint32)usSRegHoldBuf[RMSCURRENT] * 10) >> 3;
		h_Cur->RMSSumThreshold = h_Cur->RMSSumThreshold * usSRegHoldBuf[RMSCURTIME];
		// RMS over current error detection
		if (h_Cur->RMSCurCnt > usSRegHoldBuf[RMSCURTIME])
		{
			if ((h_Cur->Sum_ia > h_Cur->RMSSumThreshold) || (h_Cur->Sum_ib > h_Cur->RMSSumThreshold)
				|| (h_Cur->Sum_ic > h_Cur->RMSSumThreshold))
			{
				mcFaultSource = FaultRMSOVCurrent;
				FaultProcess();
			}
			h_Cur->RMSCurCnt = 0;
			h_Cur->Sum_ia = 0;
			h_Cur->Sum_ib = 0;
			h_Cur->Sum_ic = 0;
		}
		else
		{
			h_Cur->RMSCurCnt++;
			h_Cur->Sum_ia += h_Cur->Abs_ia;
			h_Cur->Sum_ib += h_Cur->Abs_ib;
			h_Cur->Sum_ic += h_Cur->Abs_ic;
		}
	}
}


#if FUNC_CURRENTBACK_ENABLED
/*****************************************************************************
 * Function:
 * Description:
 * Parameter:
 * Return:			 no
 *****************************************************************************/
void Fault_FoldBackCurrent(FaultVarible* h_Fault)
{
	uint8 faultFlag = CurrBackProtect_Fault(&MotorCurrBack);
	uint8 warnFlag = CurrBackProtect_Warn(&MotorCurrBack);
		
	if (1 == warnFlag)
	{
		Fault_Handler(FaultFoldBackCurrent, FLAG_FOLDBACK);
	}
	
	if (1 == faultFlag)
	{
		mcFaultSource = FaultFoldBackCurrent;
		FaultProcess();
	}
}
#endif

#if FUNC_FEEDBACKONLOAD_ENABLED
/*****************************************************************************
 * Function:
 * Description:
 * Parameter:
 * Return:			 no
 *****************************************************************************/
void Fault_MixErrOver(FaultVarible* h_Fault)
{
	*((int32*) &usSRegInBuf[MIXPOSERR_L]) = FeedBackMixErrCheck();
	
	if (1 == Feedback_GetMixErrOverFlag())
	{
		mcFaultSource = FaultMixErrOver;
		FaultProcess();
	}
}
#endif

/*****************************************************************************
 * Function:		 void Fault_OverSpeed()
 * Description:	 Checks over-speed error
 * Parameter:
 * Return:			 no
 *****************************************************************************/
void Fault_OverSpeed(FaultVarible* h_Fault)
{
#if PROT_OSPD_HARDWARE_ENABLED
	NFOC_OSPD = usSRegHoldBuf[OVERSPEED];    // 速度超差保护阈值
	if (usSRegHoldBuf[OVERSPEEDTIME] > 255)
		NFOC_OSPDARR = 255;
	else
		NFOC_OSPDARR = usSRegHoldBuf[OVERSPEEDTIME]; // 速度超差目标值
	
#else

#endif // #if PROT_OSPD_HARDWARE_ENABLED
}


/*****************************************************************************
 * Function:		 void Fault_OverPosErr()
 * Description:	 Checks Position Following error
 * Parameter:
 * Return:			 no
 *****************************************************************************/
void Fault_OverPosErr(FaultVarible* h_Fault)
{
	if (mcFocCtrl.PosLoopEnable == 1)     // check in position loop
	{// Position Following error detection
#if FUNC_HOME_ENABLED
		if (mcDoHome.SkipFaultOverPosErr == 0)
#endif //#if FUNC_HOME_ENABLED
		{
			if (ABS(mcFocCtrl.ThetaErr) >= (((int32)usSRegHoldBuf[PEMAX_H] << 16) | usSRegHoldBuf[PEMAX_L]))
			{
				h_Fault->OverPosErrCnt++;
				if (h_Fault->OverPosErrCnt >= usSRegHoldBuf[PEMAXTIME])
				{
					h_Fault->OverPosErrCnt = 0;
					mcFaultSource = FaultOverPosErr;
					FaultProcess();
				}
			}
			else
			{
				if (h_Fault->OverPosErrCnt > 0)
					h_Fault->OverPosErrCnt--;
			}
		}
	}
}

/*****************************************************************************
 * Function:	 void Fault_OverVelErr()
 * Description:	 Checks Velocity Following error
 * Parameter:
 * Return:		 no
 *****************************************************************************/
void Fault_OverVelErr(FaultVarible* h_Fault)
{
#if PROT_OVEL_HARDWARE_ENABLED
#if FUNC_HOME_ENABLED
	if (mcDoHome.SkipFaultOverPosErr == 0)
#endif //#if FUNC_HOME_ENABLED
	{
		set_csr(DRV1_PER, OVEL_AUTO); // 每个载波周期自动使能一次速度超差计算
		
		NFOC_OVEL = usSRegHoldBuf[VEMAX];    // 速度超差保护阈值
		if (usSRegHoldBuf[VEMAXTIME] > 255)
			NFOC_OVELARR = 255;
		else
			NFOC_OVELARR = usSRegHoldBuf[VEMAXTIME]; // 速度超差目标值
	}
#if FUNC_HOME_ENABLED
	else
	{
		clr_csr(DRV1_PER, OVEL_AUTO);
	}
#endif //#if FUNC_HOME_ENABLED
#else

#endif // #if PROT_OVEL_HARDWARE_ENABLED
}

/*****************************************************************************
 * Function:		 void	Fault_PhaseLoss(mcFaultVarible *h_Fault)
 * Description:	 缺相保护函数，当电机运行状态下，10ms取三相电流的最大值，
 1.5s判断各相电流最大值，若存在两相电流值大于一定值，而第三相电流值却非常小，则判断为缺相保护，电机停机；
 * Parameter:		 mcFaultVarible *h_Fault
 * Return:			 no
 *****************************************************************************/
void Fault_PhaseLoss(FaultVarible* h_Fault)
{
#if PROT_PLOSS_HARDWARE_ENABLED
	NFOC_PLTTH = usSRegHoldBuf[PHASELOSSANGLE]; // 缺相保护角度变化阈值
	NFOC_PLRTH = usSRegHoldBuf[PHASELOSSCMDCUR]; // 缺相保护电流命令阈值
	NFOC_PLITH = usSRegHoldBuf[PHASELOSSACTCUR]; // 缺相保护相电流阈值
#else

#endif
	
}


/*****************************************************************************
 * Function:	void	Fault_Stall(mcFaultVarible *h_Fault)
 * Description:	堵转保护函数，A stall condition occurs when [I > MICONT] and [I > 0.9×ILIM] and [V <
 *				STALLVEL]. A stall fault occurs whenever the duration of a stall condition exceeds STALLTIME.
 * Parameter:	mcFaultVarible *h_Fault
 * Return:		no
 *****************************************************************************/
void Fault_Stall(FaultVarible* h_Fault)
{
#if PROT_STALL_HARDWARE_ENABLED
	
	NFOC_LKSTH = usSRegHoldBuf[STALLVEL];    // 堵转保护速度阈值
	NFOC_LKITH = usSRegHoldBuf[STALLCUR]; // 堵转保护电流阈值
	NFOC_LKARR = usSRegHoldBuf[STALLTIME]; // 堵转保护目标值
#else

#endif
}

/*****************************************************************************
 * Function:		 void	Fault_OverTemperature(mcFaultVarible *h_Fault)
 * Description:	 过温保护函数，电机在运行状态，读取AD值，超过额定限幅的时候保护
 * Parameter:		 mcFaultVarible *h_Fault
 * Return:			 no
 *****************************************************************************/
void Fault_OverTemperature(FaultVarible* h_Fault)
{
	if (usSRegInBuf[DRIVETEMP] > ((uint32)usSRegHoldBuf[DRIVETHERMTRIP] * 3) >> 1)
	{
		h_Fault->DriveThermCnt = 0;
		mcFaultSource = FaultOverTemp;
		FaultProcess();
	}
	
	if (usSRegInBuf[DRIVETEMP] > usSRegHoldBuf[DRIVETHERMTRIP])
	{
		h_Fault->DriveThermCnt++;
		if (h_Fault->DriveThermCnt >= usSRegHoldBuf[THERMTIME])
		{
			h_Fault->DriveThermCnt = 0;
			mcFaultSource = FaultOverTemp;
			FaultProcess();
		}
	}
	else
	{
		if (h_Fault->DriveThermCnt > 0)
			h_Fault->DriveThermCnt--;
	}
}


/*****************************************************************************
 * Function:		 void	Fault_STO(mcFaultVarible *h_Fault)
 * Description:	 判断是否处于STO状态
 * Parameter:		 mcFaultVarible *h_Fault
 * Return:			 no
 *****************************************************************************/
void Fault_STO(FaultVarible* h_Fault)
{
#ifdef STO_PIN
	if (readbit_csr(STO_GPIO, STO_PIN))
	{
		Fault_Handler(FaultSTO, FLAG_STOERR);
	}
	else
	{
		Fault_Handler(FaultNoSource, FLAG_STOERR);
	}
#endif
}


/*****************************************************************************
 * Function:		 void	Fault_CurrentOffset()
 * Description:	 判断电流偏置是否异常
 * Parameter:		 no
 * Return:			 no
 *****************************************************************************/
void Fault_CurrentOffset()
{
#if (HW_ADC_SYNC == ADCSAM_SYNC)
	if (readbit_csr(DRV1_PSR, RIF) || readbit_csr(DRV2_PSR, RIF))
#else
	if (readbit_csr(DRV1_PSR, RIF))
#endif
	{
		Fault_Handler(FaultCurrentOffset, FLAG_CUROFF);
	}
	else
	{
		Fault_Handler(FaultNoSource, FLAG_CUROFF);
	}
}

#if ((HardwareCurrent_Protect == Hardware_FO_Protect) || (HardwareCurrent_Protect == Hardware_FO_CMP_Protect))
/*****************************************************************************
 * Function:	void Fault_HardOvercurrent(mcFaultVarible *h_Fault)
 * Description:	判断硬件是否过流，作为外部中断判断过流的二次备份
 * Parameter:	mcFaultVarible *h_Fault
 * Return:		no
 *****************************************************************************/
void Fault_HardOvercurrent(FaultVarible* h_Fault)
{
	if (!readbit_csr(HOV_GPIO, HOV_PIN))
//	if (mcFocCtrl.CurLoopEnable == 1 && !readbit_csr(HOV_GPIO, HOV_PIN)) // FO信号刚上电时异常，需避开
	{
		Fault_Handler(FaultHardOVCurrent, FLAG_HARDOVC);
	}
	else
	{
		Fault_Handler(FaultNoSource, FLAG_HARDOVC);
	}
}
#endif

/*****************************************************************************
 * Function:	void Fault_ParamError(FaultVarible* h_Fault)
 * Description:	判断参数错误
 * Parameter:	no
 * Return:		no
 *****************************************************************************/
void Fault_ParamError(FaultVarible* h_Fault)
{
	if (usSRegHoldBuf[POLES] == 0
		|| (usSRegHoldBuf[PITCH_H] == 0 && usSRegHoldBuf[PITCH_L] == 0)
		|| (((int32)(usSRegHoldBuf[POSLIMPOS_H] << 16) | usSRegHoldBuf[POSLIMPOS_L]) < ((int32)(usSRegHoldBuf[POSLIMNEG_H] << 16) | usSRegHoldBuf[POSLIMNEG_L]))
		|| (usSRegHoldBuf[OVERVOLTAGE] < usSRegHoldBuf[UNDERVOLTAGE]))
	{
		Fault_Handler(FaultParamError, FLAG_PARAMERR);
	}
	else
	{
		Fault_Handler(FaultNoSource, FLAG_PARAMERR);
	}
}

/*****************************************************************************
 * Function:	void	Fault_Encoder(mcFaultVarible *h_Fault)
 * Description:	判断编码器是否报错
 * Parameter:	mcFaultVarible *h_Fault
 * Return:		no
 *****************************************************************************/
void Fault_Encoder(FaultVarible* h_Fault)
{
	uint16 EncErr = usSRegInBuf[ENCODERERR];
	
#if ENCODER_SEL_BISS_ENABLED || ENCODER_SEL_TMG_ENABLED

	int16 i, istart, iend;

#if ENCODER_SEL_BISS_ENABLED && ENCODER_SEL_TMG_ENABLED
	if (mcEncoder.TypeSelect == ENCODER_SEL_BISS)
	{
		istart = BISSERRSIZE - 1;
		iend = 0;
	}
	else
	{
		istart = ENCERRARRAYSIZE - 1;
		iend = BISSERRSIZE;
	}
#elif ENCODER_SEL_BISS_ENABLED || ENCODER_SEL_TMG_ENABLED
	istart = ENCERRARRAYSIZE - 1;
	iend = 0;
#else
	istart = -1;
	iend = 0;
#endif

	for (i = istart; i >= iend; i--)
	{
		if (GetReg(EncErr, EncErrParaArray[i][1]))
		{
			Fault_Handler(EncErrParaArray[i][0], ((uint32)1 << EncErrFlagArray[i]));
		}
		else
		{
			Fault_Handler(FaultNoSource, ((uint32)1 << EncErrFlagArray[i]));
		}
	}
#endif // #if ENCODER_SEL_BISS_ENABLED || ENCODER_SEL_TMG_ENABLED

#if ENCODER_SEL_SPI_ENABLED || ENCODER_SEL_SPI2_ENABLED
	if (EncErr != 0)
	{
		if (GetReg(EncErr, FAULT_ENC_CRC)) // CRC错误
		{
			Fault_Handler(FaultEncCRC, FLAG_ENCCRC);
		}
		else
		{
			Fault_Handler(FaultNoSource, FLAG_ENCCRC);
		}
		
		if (GetReg(EncErr, ~(uint16)FAULT_ENC_CRC)) // 其他报错
		{
			Fault_Handler(FaultEncInternal, FLAG_ENCINT);
		}
		else
		{
			Fault_Handler(FaultNoSource, FLAG_ENCINT);
		}
	}
	
	EncErr = usSRegInBuf[SFBENCERR]; // 负载侧编码器
	if (EncErr != 0)
	{
		if (GetReg(EncErr, FAULT_ENC_CRC)) // CRC错误
		{
			Fault_Handler(FaultSFBEncCRC, FLAG_SFBENCCRC);
		}
		else
		{
			Fault_Handler(FaultNoSource, FLAG_SFBENCCRC);
		}

		if (GetReg(EncErr, ~(uint16)FAULT_ENC_CRC)) // 其他报错
		{
			Fault_Handler(FaultSFBEncInternal, FLAG_SFBENCINT);
		}
		else
		{
			Fault_Handler(FaultNoSource, FLAG_SFBENCINT);
		}
	}
#endif
}


/*****************************************************************************
 * Function:	void	Fault_Hall(mcFaultVarible *h_Fault)
 * Description:	判断Hall是否有效
 * Parameter:	mcFaultVarible *h_Fault
 * Return:		no
 *****************************************************************************/
void Fault_Hall(FaultVarible* h_Fault)
{
	if ((usSRegHoldBuf[ENCTYPE] == ENCODER_SEL_ABZ_HALL || usSRegHoldBuf[ENCTYPE] == ENCODER_SEL_HALLS_ONLY) &&
		GetReg(usSRegHoldBuf[HALLMODE], HALLMODE_LEARNOK) &&
		(usSRegInBuf[HALLS] == 0 || usSRegInBuf[HALLS] == 7))
	{
		h_Fault->HallCnt++;
		if (h_Fault->HallCnt >= usSRegHoldBuf[HALLINVALIDTIME])
		{
			h_Fault->HallCnt = 0;
			Fault_Handler(FaultHallsInvalid, FLAG_HALLERR);
		}
	}
	else
	{
		if (h_Fault->HallCnt > 0)
			h_Fault->HallCnt--;
		else
			Fault_Handler(FaultNoSource, FLAG_HALLERR);
	}
}


/*****************************************************************************
 * Function:	void	Fault_EncOutFreqTooHigh(mcFaultVarible *h_Fault)
 * Description:	判断分频输出频率是否过高
 * Parameter:	mcFaultVarible *h_Fault
 * Return:		no
 *****************************************************************************/
#if EXCTRL_ENCOUT_ENABLED
void Fault_EncOutFreqTooHigh(FaultVarible* h_Fault)
{
	if ( (FreqDiv.OUT_SourceSel != 0) && (ABS((int32)FreqDiv.OUT_PulseDelta) > ((uint32)usSRegHoldBuf[ENCOUTMAX]/ ENCOUT_FREQUENCY)) )
	{
		mcFaultSource = FaultEncOutFreqTooHigh;
		FaultProcess();
	}
}
#endif // #if EXCTRL_ENCOUT_ENABLED

/*****************************************************************************
 * Function:	void	Fault_MainIntPeriodTimeOut(mcFaultVarible *h_Fault)
 * Description:	判断载波中断周期是否过长
 * Parameter:	mcFaultVarible *h_Fault
 * Return:		no
 *****************************************************************************/
void Fault_MainIntPeriodTimeOut(FaultVarible* h_Fault)
{
#if !PROT_CARINTOT_HARDWARE_ENABLED

#endif
}

/*****************************************************************************
 * Function:	void	Fault_AuxIntDelayTimeOut()
 * Description:	判断子中断延时是否过长
 * Parameter:	mcFaultVarible *h_Fault
 * Return:		no
 *****************************************************************************/
void Fault_AuxIntDelayTimeOut()
{
	if (read_csr(TIM3_CNTR) > usSRegHoldBuf[AUXINTDELAY])
	{
		Fault_Handler(FaultAuxIntDelayTimeOut, FLAG_AUXINTOT);
	}
	else
	{
		Fault_Handler(FaultNoSource, FLAG_AUXINTOT);
	}
}


/*****************************************************************************
 * Function:	void	Fault_ExceedPositionLimit(mcFaultVarible *h_Fault)
 * Description:	超出正负限位
 * Parameter:	mcFaultVarible *h_Fault
 * Return:		no
 *****************************************************************************/
void Fault_ExceedPositionLimit(FaultVarible* h_Fault)
{
	int32 actPos;
	
#if FUNC_FEEDBACKONLOAD_ENABLED
	if (usSRegHoldBuf[POSLIMMODE] && ((FEEDBACK_LOAD == Feedback_GetOnLoadFlag() && mcFocCtrl.MultiOffsetFirstFlag == 1)
		|| GetReg(usSRegInBuf[DRIVESTATUS], STATUS_HOMECOMPLETE)))
#else
	if (usSRegHoldBuf[POSLIMMODE] && GetReg(usSRegInBuf[DRIVESTATUS], STATUS_HOMECOMPLETE))
#endif
	{
#if FUNC_FEEDBACKONLOAD_ENABLED
		if (FEEDBACK_LOAD == Feedback_GetOnLoadFlag())
			actPos = (int32)(usSRegInBuf[SFBACTPOS_H] << 16) | usSRegInBuf[SFBACTPOS_L];
		else
			actPos = (int32)(usSRegInBuf[ACTPOS_H] << 16) | usSRegInBuf[ACTPOS_L];
#else
		actPos = (int32)(usSRegInBuf[ACTPOS_H] << 16) | usSRegInBuf[ACTPOS_L];
#endif
		
		if (ReadBit(usSRegInBuf[DIGINSTATUS] & usSRegInBuf[DIGINSTAEN], INSTATUS_POSILIMITSWITCH) || 
			actPos > ((int32)(usSRegHoldBuf[POSLIMPOS_H] << 16) | usSRegHoldBuf[POSLIMPOS_L]))
		{
			if (h_Fault->PosLmtPosCnt++ >= 5)
			{
				h_Fault->PosLmtPosCnt = 0;
				Fault_Handler(FaultPositiveLimit, FLAG_POSLIM);
			}
			return;
		}
		else
		{
			h_Fault->PosLmtPosCnt = 0;
			Fault_Handler(FaultNoSource, FLAG_POSLIM);
		}
		
		if (ReadBit(usSRegInBuf[DIGINSTATUS] & usSRegInBuf[DIGINSTAEN], INSTATUS_NEGALIMITSWITCH) ||
			actPos < ((int32)(usSRegHoldBuf[POSLIMNEG_H] << 16) | usSRegHoldBuf[POSLIMNEG_L]))
		{
			if (h_Fault->PosLmtNegCnt++ >= 5)
			{
				h_Fault->PosLmtNegCnt = 0;
				Fault_Handler(FaultNegativeLimit, FLAG_NEGLIM);
			}
		}
		else
		{
			h_Fault->PosLmtNegCnt = 0;
			Fault_Handler(FaultNoSource, FLAG_NEGLIM);
		}
	}
}

/*****************************************************************************
 * Function:	void Fault_Handler(uint16 FaultSource, uint16 FaultMask)
 * Description:	 将相应报错或者警告寄存器置位
 * Parameter:	FaultSource-报错编码
 *				FaultMask-报错警告掩码
 * Return:		no
 *****************************************************************************/
void Fault_Handler(uint16 FaultSrc, uint32 FaultMask)
{
	uint32* pFaultMask = &usSRegHoldBuf[FAULTMASK0];
	uint32* pWarnStatus = &usSRegInBuf[WARNSTATUS0];
	if (FaultSrc != FaultNoSource)
	{
		if (GetReg(*pFaultMask, FaultMask))
		{
			mcFaultSource = FaultSrc;
			FaultProcess();
		}
		else
		{
			mcWarnSource = FaultSrc;
			SetBit(*pWarnStatus, FaultMask);
		}
	}
	else
	{
		ClrBit(*pWarnStatus, FaultMask);
	}
}

/*****************************************************************************
 * Function:	void Fault_TimeCount()
 * Description:	报错时间计数, 放在1ms里面
 * Parameter:	no
 * Return:		no
 *****************************************************************************/
void Fault_TimeCount()
{
	mcFaultDect.CurrentTimeCount++;
	if (mcFaultDect.CurrentTimeCount > 60000)  // 1 minute
	{
		mcFaultDect.CurrentTimeCount = 0;
		mcFaultDect.CurrentMinute++;
		usSRegInBuf[CURRENTTIME] = mcFaultDect.CurrentMinute;
	}
}

