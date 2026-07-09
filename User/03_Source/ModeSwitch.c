/*
 * Copyright (c) 2024-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : ModeSwitch.c
 * Author        : Victor.jin
 * Date          : 2024-01-18
 * Description   : Mode switching
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


 /*---------------------------------------------------------------------------
  * Name		:	ModeSW_Init
  * Input	:	No
  * Output	:	No
  * Description:	Mode switch initialization
  *---------------------------------------------------------------------------*/
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


 /*---------------------------------------------------------------------------
  * Name		:	ModeSW_Update
  * Input	:	No
  * Output	:	No
  * Description:	Mode switch updates working mode (WorkMode)
  *---------------------------------------------------------------------------*/
void ModeSW_Update(void)
{
	switch (usSRegHoldBuf[OPMODESWITCH]) // Run mode function code
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
			if ((usSRegHoldBuf[FCMOD] == FCMODE_CLOSEDLOOP_ONCE) || (usSRegHoldBuf[FCMOD] == FCMODE_CLOSEDLOOP_REPEAT)) // If in closed-loop force control, the run mode is force-closed-loop mode
				mcRegParam.WorkMode = FRCSERIAL;//CURMOD;
			else
#endif
				mcRegParam.WorkMode = CURSERIAL;//CURMOD;
		}
		break;

	default: // Motion mode switching disabled
		mcRegParam.WorkMode = GetReg(usSRegHoldBuf[DRIVEMODE], MODE_WORKMODE3 | MODE_WORKMODE2 | MODE_WORKMODE1 | MODE_WORKMODE0);
		break;
	}



	// Decide whether to clear controller variables during mode switching
	if (ModeSW.FirOnPower == 0)
	{
		ModeSW.RunModLatch = mcRegParam.WorkMode;// Mode value at first power-on

		ModeSW.FirOnPower = 1;
	}
	if ((ModeSW.FirOnPower == 1) && (ModeSW.RunModLatch != mcRegParam.WorkMode))
	{
		if ((mcState == mcRun) && (mcFaultSource == FaultNoSource)) // Compensation is performed only during RUN state when a switch occurs
		{
			if ((ModeSW.RunModLatch == VELSERIAL /*VELMOD*/ ) && (mcRegParam.WorkMode == POSSERIAL /*POSMOD*/ ))						//Spd -> Pos
			{
				ModeSW.SwitchFlag = 1;
			}
			else if ((ModeSW.RunModLatch == CURSERIAL /*CURMOD*/ ) && (mcRegParam.WorkMode == VELSERIAL /*VELMOD*/ ))					//Toq -> Spd
			{
				ModeSW.SwitchFlag = 1;
			}
			else if ((ModeSW.RunModLatch == CURSERIAL /*CURMOD*/ ) && (mcRegParam.WorkMode == POSSERIAL /*POSMOD*/ ))					//Toq -> Pos
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

			usSRegInBuf[CMDVEL] = 0;

			mcFocCtrl.TargetRefFirstFlag = 0; // Clear flag for position command computation
			Motor_Profile_Reset();	// Reset trajectory planning related variables

			RunMode_Update();
		}
		else  // When switching in non-RUN mode, no compensation; clear the corresponding regulators directly
		{
			mcProfile.Flag = 0;

			ModeSW.SwitchFlag = 0;
		}

		ModeSW.RunModLatch = mcRegParam.WorkMode;// Save the previous mode value
	}

}


 /*---------------------------------------------------------------------------
  * Name		:	RunMode_Update
  * Input	:	No
  * Output	:	No
  * Description:	Enable corresponding loops according to current work mode and update run mode RunMod
  *---------------------------------------------------------------------------*/
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