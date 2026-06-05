/*
 * Copyright (c) 2024-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : ModeSwitch.c
 * Author        : Victor.jin
 * Date          : 2024-01-18
 * Description   : 模式切换
 *
 * Record        :
 * V1.0, 2024-01-18, Victor.jin: Created file
 */


/********************************************************************************
 * Header Definition
 ********************************************************************************/
#include <Myproject.h>
/********************************************************************************
 * Macro & Structure Definition
 *******************************************************************************/
ModeSWPTypedef ModeSW;


/********************************************************************************
 * Internal Routine Prototypes
 ********************************************************************************/
void ModeSW_Init(void);
void ModeSW_Update(void);
void RunMode_Update(void);



/*---------------------------------------------------------------------------*/
/* Name     :
/* Input    :   NO
/* Output   :   NO
/* Description: usSRegInBuf[CMDCUR]
/*---------------------------------------------------------------------------*/
void ModeSW_Init(void)
{
	ModeSW.FirOnPower = 0;
	ModeSW.SwitchFlag = 0;
	
#if SPECIAL_ELESCREW_ENABLE
	ScrewCtrl.ScrewStep = SCREW_NEAR_STEP;
	ScrewCtrl.ScrewStatus = READY;
	ScrewCtrl.PauseFlag = 0;
#endif
#if FUNC_FORCECTRL_ENABLED
	ForceCtrl_Init();
#endif

	ModeSW_Update();
}


/*---------------------------------------------------------------------------*/
/* Name     :
/* Input    :   NO
/* Output   :   NO
/* Description:
1、主循环函数调用
/*---------------------------------------------------------------------------*/
void ModeSW_Update(void)
{
	switch (usSRegHoldBuf[OPMODESWITCH]) // 运行模式功能码
	{
	case 1: //S-T
		if (GetReg(usSRegInBuf[DIGINSTATUS], INSTATUS_OPMODECHANGE1))
			mcRegParam.WorkMode = VELSERIAL;//VELMOD;
		else
			mcRegParam.WorkMode = CURSERIAL;//CURMOD;
		break;

	case 2: //P-S
		if (GetReg(usSRegInBuf[DIGINSTATUS], INSTATUS_OPMODECHANGE1))
			mcRegParam.WorkMode = POSSERIAL;//POSMOD;
		else
			mcRegParam.WorkMode = VELSERIAL;//VELMOD;
		break;

	case 3: //P-T
		if (GetReg(usSRegInBuf[DIGINSTATUS], INSTATUS_OPMODECHANGE1))
			mcRegParam.WorkMode = POSSERIAL;//POSMOD;
		else
			mcRegParam.WorkMode = CURSERIAL;//CURMOD;
		break;

	case 4: //P-S-T
		if (GetReg(usSRegInBuf[DIGINSTATUS], INSTATUS_OPMODECHANGE1))
			mcRegParam.WorkMode = POSSERIAL;//POSMOD;
		else if (GetReg(usSRegInBuf[DIGINSTATUS], INSTATUS_OPMODECHANGE2))
			mcRegParam.WorkMode = VELSERIAL;//VELMOD;
		else
		{
#if FUNC_FORCECLOSEDLOOP_ENABLED
			if ((usSRegHoldBuf[FCMOD] == FCMODE_CLOSEDLOOP_ONCE) || (usSRegHoldBuf[FCMOD] == FCMODE_CLOSEDLOOP_REPEAT)) // 若在闭环力控，则运行模式为压力闭环模式
				mcRegParam.WorkMode = FRCSERIAL;//CURMOD;
			else
#endif
				mcRegParam.WorkMode = CURSERIAL;//CURMOD;
		}
		break;

	default: //关闭运动模式切换
		mcRegParam.WorkMode = GetReg(usSRegHoldBuf[DRIVEMODE], MODE_WORKMODE3 | MODE_WORKMODE2 | MODE_WORKMODE1 | MODE_WORKMODE0);
		break;
	}



	//判断在模式切换时进行调节器变量清零
	if (ModeSW.FirOnPower == 0)
	{
		ModeSW.RunModLatch = mcRegParam.WorkMode;//上电第一次的模式值

		ModeSW.FirOnPower = 1;
	}
	if ((ModeSW.FirOnPower == 1) && (ModeSW.RunModLatch != mcRegParam.WorkMode))
	{
		if ((mcState == mcRun) && (mcFaultSource == FaultNoSource)) //只有在运行过程中时，而且发生了切换动作，才进行补偿
		{
			if ((ModeSW.RunModLatch == VELSERIAL /*VELMOD*/ ) && (mcRegParam.WorkMode == POSSERIAL /*POSMOD*/ ))						//Spd -> Pos 由速度环向位置环切换时
			{
				ModeSW.SwitchFlag = 1;
			}
			else if ((ModeSW.RunModLatch == CURSERIAL /*CURMOD*/ ) && (mcRegParam.WorkMode == VELSERIAL /*VELMOD*/ ))					//Toq -> Spd
			{
				ModeSW.SwitchFlag = 1;
			}
			else if ((ModeSW.RunModLatch == CURSERIAL /*CURMOD*/ ) && (mcRegParam.WorkMode == POSSERIAL /*POSMOD*/ ))					//Toq -> Pos 由转矩环向位置环切换时
			{
				ModeSW.SwitchFlag = 1;
			}
			else if ((ModeSW.RunModLatch == POSSERIAL /*POSMOD*/ ) && (mcRegParam.WorkMode == VELSERIAL /*VELMOD*/ ))					//Pos -> Spd
			{
				ModeSW.SwitchFlag = 1;
			}
			else if ((ModeSW.RunModLatch == POSSERIAL /*POSMOD*/ ) && (mcRegParam.WorkMode == CURSERIAL /*CURMOD*/ ))					//Pos -> Toq
			{
				ModeSW.SwitchFlag = 1;
			}
			else if ((ModeSW.RunModLatch == VELSERIAL /*VELMOD*/ ) && (mcRegParam.WorkMode == CURSERIAL /*CURMOD*/ ))					//SPD -> TOQ
			{
				ModeSW.SwitchFlag = 1;
			}
#if FUNC_FORCECLOSEDLOOP_ENABLED
			else if ((ModeSW.RunModLatch == CURSERIAL) && (mcRegParam.WorkMode == FRCSERIAL))					//Toq -> Frc
			{
				ModeSW.SwitchFlag = 1;
			}
			else if ((ModeSW.RunModLatch == VELSERIAL) && (mcRegParam.WorkMode == FRCSERIAL))					//Spd -> Frc
			{
				ModeSW.SwitchFlag = 1;
			}
			else if ((ModeSW.RunModLatch == FRCSERIAL) && (mcRegParam.WorkMode == VELSERIAL))					//Frc -> Spd
			{
				ModeSW.SwitchFlag = 1;
			}
			else if ((ModeSW.RunModLatch == FRCSERIAL) && (mcRegParam.WorkMode == POSSERIAL))					//Frc -> Pos
			{
				ModeSW.SwitchFlag = 1;
			}
#endif

#if 1
			usSRegInBuf[CMDVEL] = 0;

			mcFocCtrl.TargetRefFirstFlag = 0; // 计算位置命令的标志位清零
			Motor_Profile_Reset();	// 初始化轨迹规划相关变量

			RunMode_Update();

#endif

		}
		else  //在非RUN模式切换时，不进行补偿，直接将相应调节器清零
		{
			mcProfile.Flag = 0;

			ModeSW.SwitchFlag = 0;
		}

		ModeSW.RunModLatch = mcRegParam.WorkMode;//保存上一次的模式值
	}

}


/*---------------------------------------------------------------------------*/
/* Name     :
/* Input    :   NO
/* Output   :   NO
/* Description:
1、主循环函数调用
/*---------------------------------------------------------------------------*/
void RunMode_Update(void)
{
	if (mcRegParam.WorkMode == CURSERIAL || mcRegParam.WorkMode == CURANALOG || 
		mcRegParam.WorkMode == CURFRF || mcRegParam.WorkMode == CURTUNE)
	{
		mcFocCtrl.CurLoopEnable = 1;
		mcFocCtrl.FrcLoopEnable = 0;
		mcFocCtrl.VelLoopEnable = 0;
		mcFocCtrl.PosLoopEnable = 0;
	}
#if FUNC_FORCECLOSEDLOOP_ENABLED
	else if (mcRegParam.WorkMode == FRCSERIAL)
	{
		mcFocCtrl.CurLoopEnable = 1;
		mcFocCtrl.FrcLoopEnable = 1;
		mcFocCtrl.VelLoopEnable = 0;
		mcFocCtrl.PosLoopEnable = 0;
	}
#endif
	else if (mcRegParam.WorkMode == VELSERIAL || mcRegParam.WorkMode == VELANALOG ||
		mcRegParam.WorkMode == VELFRF)
	{
		mcFocCtrl.CurLoopEnable = 1;
		mcFocCtrl.FrcLoopEnable = 0;
		mcFocCtrl.VelLoopEnable = 1;
		mcFocCtrl.PosLoopEnable = 0;
	}
	else if (mcRegParam.WorkMode == POSSERIAL || mcRegParam.WorkMode == PULSEDIR)
	{
#if FUNC_SOFTCTRL_ENABLED
		if (SC_WorkMode == SC_LOCAL_IMPEDANCE)
		{
			mcFocCtrl.CurLoopEnable = 1;
			mcFocCtrl.FrcLoopEnable = 0;
			mcFocCtrl.VelLoopEnable = 0;
			mcFocCtrl.PosLoopEnable = 1;
		}
		else if (SC_WorkMode == SC_LOCAL_ADMITTANCE)
		{
			mcFocCtrl.CurLoopEnable = 1;
			mcFocCtrl.FrcLoopEnable = 0;
			mcFocCtrl.VelLoopEnable = 1;
			mcFocCtrl.PosLoopEnable = 1;
		}
		else
#endif
		{
			mcFocCtrl.CurLoopEnable = 1;
			mcFocCtrl.FrcLoopEnable = 0;
			mcFocCtrl.VelLoopEnable = 1;
			mcFocCtrl.PosLoopEnable = 1;
		}		
	}
#if EXCTRL_ECAT_ENABLED || EXCTRL_CANOPEN_ENABLED
	else if (mcRegParam.WorkMode == COMM_ECAT)
	{
		switch (usSRegInBuf[FBOPMODE])
		{
		case PROFILE_POSITION_MODE: //pp
		case HOMING_MODE: //hm
		case INTERPOLATION_POSITION_MODE: //ip
		case CYCLIC_SYNC_POSITION_MODE: //csp
			mcFocCtrl.CurLoopEnable = 1;
			mcFocCtrl.VelLoopEnable = 1;
			mcFocCtrl.PosLoopEnable = 1;
			break;
		case PROFILE_VELOCITY_MODE: //pv
		case CYCLIC_SYNC_VELOCITY_MODE: //csv
			mcFocCtrl.CurLoopEnable = 1;
			mcFocCtrl.VelLoopEnable = 1;
			mcFocCtrl.PosLoopEnable = 0;
			break;
		case PROFILE_TORQUE_MODE: //pt
		case CYCLIC_SYNC_TORQUE_MODE: //cst
			mcFocCtrl.CurLoopEnable = 1;
			mcFocCtrl.VelLoopEnable = 0;
			mcFocCtrl.PosLoopEnable = 0;
			break;
		default:
			mcFocCtrl.CurLoopEnable = 0;
			mcFocCtrl.VelLoopEnable = 0;
			mcFocCtrl.PosLoopEnable = 0;
			break;
		}

		mcFocCtrl.FrcLoopEnable = 0;
	}
#endif

	if ((mcFocCtrl.PosLoopEnable == 1)
		&& (mcFocCtrl.VelLoopEnable == 1)
		&& (mcFocCtrl.CurLoopEnable == 1))
	{
		mcFocCtrl.RunMod = POSMOD;
	}
	else if ((mcFocCtrl.PosLoopEnable == 0)
		&& (mcFocCtrl.VelLoopEnable == 1)
		&& (mcFocCtrl.CurLoopEnable == 1))
	{
		mcFocCtrl.RunMod = VELMOD;
	}
	else if ((mcFocCtrl.PosLoopEnable == 0)
		&& (mcFocCtrl.VelLoopEnable == 0)
		&& (mcFocCtrl.CurLoopEnable == 1))
	{
		mcFocCtrl.RunMod = CURMOD;
	}
#if FUNC_SOFTCTRL_ENABLED
	else if ((mcFocCtrl.PosLoopEnable == 1)
		&& (mcFocCtrl.VelLoopEnable == 0)
		&& (mcFocCtrl.CurLoopEnable == 1))
	{
		mcFocCtrl.RunMod = POS_CURMOD;
	}
#endif
	else
	{
		mcFocCtrl.RunMod = NOMOD;
	}
	
	FOC_RunModeUpdate();

	OutputFilter_RunModeUpdate();
}

