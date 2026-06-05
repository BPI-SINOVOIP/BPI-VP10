/*
 * Copyright (c) 2025-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : EmergencyStop.c
 * Author        : Zougi.Zou
 * Date          : 2025-4-24
 * Description   : Emergency Stop Function
 *
 * Record        :
 * V1.0, 2025-4-24, Zougi.Zou: Created file
 */

/********************************************************************************
* Header Definition
********************************************************************************/
#include <Myproject.h>

#if FUNC_DISMODE_ENABLED

/********************************************************************************
* Macro & Structure Definition
*******************************************************************************/
EmergencyStopTypeDef mcEmergencyStop = {0};


/********************************************************************************
* Internal Routine Prototypes
********************************************************************************/

/*---------------------------------------------------------------------------*/
/* Name		:	void Do_EmergencyStop(void)
/* Input	:	NO
/* Output	:	NO
/* Description:	停车方式.
/*---------------------------------------------------------------------------*/
void Do_EmergencyStop(void)
{	
	if (McStaSet.SetFlag.BrakeFlag == 0)
	{
		McStaSet.SetFlag.BrakeFlag = 1;
		
		if (mcFaultSource == FaultHardOVCurrent || mcFaultSource == FaultPeakOVCurrent \
			|| mcFaultSource == FaultRMSOVCurrent || mcFaultSource == FaultOverVoltage)
		{
			mcEmergencyStop.State = EMER_DISABLE;
		}
		else if (mcEmergencyStop.State == EMER_IDLE)
		{
			if (mcFocCtrl.RunMod == CURMOD || GetReg(usSRegHoldBuf[DISMODE], DISSTOPMODE) == DISSTOP_COAST)
			{
				mcEmergencyStop.State = EMER_DISABLE;
			}
			else
			{
				mcEmergencyStop.State = EMER_DEC;
			}
		}
		else if(mcEmergencyStop.State == EMER_DEC || (mcEmergencyStop.State == EMER_STOP && mcEmergencyStop.StateLatch != EMER_DISABLE))
		{
			mcEmergencyStop.State = EMER_DISABLE;
		}
	}
	
	switch (mcEmergencyStop.State)
	{
	case EMER_DEC:     // 开始减速
		RampStop_Init();
		mcEmergencyStop.DisSpeed = usSRegHoldBuf[DISSPEED];
		mcEmergencyStop.TimeCounter = usSRegHoldBuf[DISTIME];
		mcEmergencyStop.TimeOutCounter = usSRegHoldBuf[DISTIMEOUT];
		mcEmergencyStop.StateLatch = mcEmergencyStop.State;
		mcEmergencyStop.State = EMER_STOP;
		break;
		
	case EMER_STOP:     // 减速到DISSPEED且维持一段时间
		if (ABS((int16)usSRegInBuf[ACTVEL]) <= mcEmergencyStop.DisSpeed || mcEmergencyStop.TimeOutCounter == 0)
		{
			if (mcEmergencyStop.TimeCounter == 0 || mcEmergencyStop.TimeOutCounter == 0)
			{
				if (mcEmergencyStop.StateLatch == EMER_DEC)
				{
					mcEmergencyStop.State = EMER_DISABLE;
				}	
				else
				{
					mcEmergencyStop.StartBrakeFlag = 0;
					clr_csr(DRV1_CR, DRVOE);			// Driver输出使能	0-->Disable		1-->Enable
					clr_csr(DRV1_OUT, MOE);		//关闭主输出使能(DB无效)
					mcEmergencyStop.State = EMER_FINISH;
				}
			}
		}
		else
		{
			mcEmergencyStop.TimeCounter = usSRegHoldBuf[DISTIME];
		}
		break;

	case EMER_DISABLE:     // 关掉通电、开启DB
		Do_DisableServo();
		
		if (GetReg(usSRegHoldBuf[DISMODE], DYNBRKMODE) == DYNBRK_ALWAYS || 
			(GetReg(usSRegHoldBuf[DISMODE], DYNBRKMODE) == DYNBRK_FAULT && mcFaultSource != FaultNoSource))
		{
			Motor_DynamicBrake_Init();
		} 

		if (mcFocCtrl.RunMod == CURMOD || GetReg(usSRegHoldBuf[DISMODE], DISSTOPMODE) == DISSTOP_COAST)
		{
			mcEmergencyStop.DisSpeed = usSRegHoldBuf[DISSPEED];
			mcEmergencyStop.TimeCounter = usSRegHoldBuf[DISTIME];
			mcEmergencyStop.TimeOutCounter = usSRegHoldBuf[DISTIMEOUT];
		}
		else // 斜坡/零速停机不用再次确认降速到期望值
		{
			mcEmergencyStop.DisSpeed = usSRegHoldBuf[DISSPEED] >> 3;
			mcEmergencyStop.TimeCounter = 5;
			mcEmergencyStop.TimeOutCounter = 200;
		}
		mcEmergencyStop.StateLatch = mcEmergencyStop.State;
		mcEmergencyStop.State = EMER_STOP;
		break;

		
	case EMER_IDLE:
	case EMER_FINISH:     // 跳出mcState = mcDisable状态
		if (mcFaultSource != FaultNoSource)
		{
			mcState = mcFault;
		}
		else
		{
			mcState = mcIdle;
		}
		mcEmergencyStop.State = EMER_IDLE;
		break;

	default:
		break;
	}
}
	

/*---------------------------------------------------------------------------*/
/* Name		:	void Motor_DynamicBrake_Init(void)
/* Input	:	NO
/* Output	:	NO
/* Description:	动态制动初始化
/*---------------------------------------------------------------------------*/
void Motor_DynamicBrake_Init(void)
{
	mcEmergencyStop.BrakeArrMax = read_csr(DRV1_ARR) + 1;
	mcEmergencyStop.BrakeArr = mcEmergencyStop.BrakeArrMax >> 1;
	
	clr_csr(DRV1_CR, DRVOE);			// Driver输出使能	0-->Disable		1-->Enable
	clr_csr(DRV1_OUT, MOE);		//主输出使能，用于选择三相上下桥信号来源
	clr_csr(DRV1_FCR0, NCALEN);	// 关FOC计算使能

	write_csr(DRV1_DR, mcEmergencyStop.BrakeArr);		//三相PWM占空比设定值
	write_csr(DRV1_CMR, 0x0015);					// 上管全关，下管全开

	set_csr(DRV1_OUT, MOE);
	set_csr(DRV1_CR, DRVOE);			// Driver输出使能	0-->Disable		1-->Enable
	
	if ((int16)usSRegHoldBuf[STOPCURRENT] > 0)
		mcEmergencyStop.StartBrakeFlag = 1;
}


/*---------------------------------------------------------------------------*/
/* Name		:	void Motor_DynamicBrake_realize(void)
/* Input	:	NO
/* Output	:	NO
/* Description:	动态制动，根据电流值修改占空比
/*---------------------------------------------------------------------------*/
void Motor_DynamicBrake_realize(void)
{
	if (mcEmergencyStop.StartBrakeFlag == 1)
	{
		int16 maxIaIb = MAX(ABS((int16)usSRegInBuf[MB_IA]), ABS((int16)usSRegInBuf[MB_IB]));
		//计算ARR值，更改占空比
		mcEmergencyStop.BrakeArr += ((int16)usSRegHoldBuf[STOPCURRENT] - maxIaIb) >> 6;
		
		if (mcEmergencyStop.BrakeArr > mcEmergencyStop.BrakeArrMax)
			mcEmergencyStop.BrakeArr = mcEmergencyStop.BrakeArrMax;
		else if (mcEmergencyStop.BrakeArr < 1)
			mcEmergencyStop.BrakeArr = 1;
		
		write_csr(DRV1_DR, mcEmergencyStop.BrakeArr);		//三相PWM占空比设定值	
	}
}


/*---------------------------------------------------------------------------*/
/* Name		:	void RampStop_Init(void)
/* Input	:	NO
/* Output	:	NO
/* Description:	减速停机初始化
/*---------------------------------------------------------------------------*/
void RampStop_Init(void)
{
	mcEmergencyStop.VelInc = (int32)usSRegHoldBuf[DISDEC];
	if (mcEmergencyStop.VelInc < 1)
		mcEmergencyStop.VelInc = 1;
	
	NFOC_IQMAX = (int16)usSRegHoldBuf[STOPCURLIM];
	NFOC_IQMIN = -(int16)usSRegHoldBuf[STOPCURLIM];

	mcEmergencyStop.StartStopFlag = 1;
	mcFocCtrl.FrcLoopEnable = 0;
	mcFocCtrl.PosLoopEnable = 0;
	mcEmergencyStop.DecStopFlag = 1;
}

/*---------------------------------------------------------------------------*/
/* Name		:	void RampStop_realize(void)
/* Input	:	NO
/* Output	:	NO
/* Description:	减速停机(在中断里执行)
/*---------------------------------------------------------------------------*/
int16 RampStop_realize(void)
{
	int32 temp;
	if (mcEmergencyStop.StartStopFlag == 1)
	{
		mcEmergencyStop.StartStopFlag = 0;
		if (GetReg(usSRegHoldBuf[DISMODE], DISSTOPMODE) == DISSTOP_RAMP)
		{
			mcEmergencyStop.VelValue = ((int32)(int16) usSRegInBuf[CMDVEL]) << DISDECSCALE;
			if (usSRegHoldBuf[DISDECTIME] > 0)
			{
				temp = ABS(mcEmergencyStop.VelValue) / VELCTRL_FREQUENCY / usSRegHoldBuf[DISDECTIME];
				if (mcEmergencyStop.VelInc < temp)
					mcEmergencyStop.VelInc = temp;
			}			
		}
		else
		{
			mcEmergencyStop.VelValue = 0;
		}
	}
	
	if (mcEmergencyStop.VelValue > 0)
	{
		mcEmergencyStop.VelValue -= mcEmergencyStop.VelInc;
		if (mcEmergencyStop.VelValue < 0)
		{
			mcEmergencyStop.VelValue = 0;
		}
	}
	else if(mcEmergencyStop.VelValue < 0)
	{
		mcEmergencyStop.VelValue += mcEmergencyStop.VelInc;
		if (mcEmergencyStop.VelValue > 0)
		{
			mcEmergencyStop.VelValue = 0;
		}
	}

	return (int16)(mcEmergencyStop.VelValue >> DISDECSCALE);
}


/*---------------------------------------------------------------------------*/
/* Name		:	void EmergencyStop_TimeCount(void)
/* Input	:	NO
/* Output	:	NO
/* Description:	停机的时间判断，放在1ms循环里
/*---------------------------------------------------------------------------*/
void EmergencyStop_TimeCount(void)
{
	if (mcEmergencyStop.TimeCounter > 0)
		mcEmergencyStop.TimeCounter--;   //停机静止计数器
	
	if (mcEmergencyStop.TimeOutCounter > 0)
		mcEmergencyStop.TimeOutCounter--;   //停机超时计数器
	
	Motor_DynamicBrake_realize();
}

#endif // #if FUNC_DISMODE_ENABLED


/*---------------------------------------------------------------------------*/
/* Name		:	void Do_DisableServo(void)
/* Input	:	NO
/* Output	:	NO
/* Description:	电机关掉通电.
/*---------------------------------------------------------------------------*/
void Do_DisableServo(void)
{
	Motor_DisableServo();
	
#if FUNC_DISMODE_ENABLED
	mcEmergencyStop.StartStopFlag = 0;
	mcEmergencyStop.DecStopFlag = 0;
#endif // #if FUNC_DISMODE_ENABLED
	
	if (mcRegParam.WorkMode == COMM_ECAT)
	{
		// 用于ECAT通讯时，控制伺服的边沿变量的清零
		ClrBit(usSRegHoldBuf[DRIVECTRL], CTRL_DISABLE);
		ClrBit(usSRegHoldBuf[DRIVECTRL], CTRL_ENABLE);
		ClrBit(usSRegHoldBuf[PROFILECTRL], PROF_MOTIONEN);
	}
#if FUNC_HOME_ENABLED
	Home_Reset();
#endif //#if FUNC_HOME_ENABLED
}