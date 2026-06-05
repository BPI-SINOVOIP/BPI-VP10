/*
 * Copyright (c) 2017-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : FocControl.c
 * Author        : Fortior Application Team
 * Date          : 2017-04-11
 * Description   : define motor contorl parameter
 *
 * Record        :
 * V1.0, 2017-04-11, Fortior Application Team: Created file
 */


/* Includes -------------------------------------------------------------------------------------*/
#include <Myproject.h>
#include "FocControl.h"


/* Private variables ----------------------------------------------------------------------------*/
uint8 mcState = mcReady;
MotStaM McStaSet = { 0 };

/*---------------------------------------------------------------------------*/
/* Name     :   void MC_Control(void)
/* Input    :   NO
/* Output   :   NO
/* Description: 电机状态机函数，包括初始化、寻相、回零、启动、运行、故障等
/*---------------------------------------------------------------------------*/
void MC_Control(void)
{
	if (mcRegParam.FlashCtrl == FLASH_REBOOT_STEP1 && usSRegHoldBuf[FLASHCTRL] == FLASH_REBOOT_STEP2)
	{
		set_csr(RST_CR, SFRST); // 软件复位
	}	
	
	if (mcFaultSource != FaultNoSource && mcState != mcDisable)
	{
		mcState = mcFault;
		if (mcRegParam.FlashCtrl == FLASH_START && usSRegHoldBuf[FLASHCTRL] == FLASH_UPLOAD)
			mcState = mcUpFlash;
		else if (mcRegParam.FlashCtrl == FLASH_START && usSRegHoldBuf[FLASHCTRL] == FLASH_DOWNLOAD)
			mcState = mcDownFlash;
	}
	if (mcState != mcReady && (GetReg(usSRegHoldBuf[DRIVECTRL], CTRL_DISABLE)
		|| GetReg(usSRegInBuf[DIGINSTATUS] & usSRegInBuf[DIGINSTAEN], INSTATUS_EMERGENCYSTOP)))
	{
		if (GetReg(usSRegInBuf[DRIVESTATUS], STATUS_ENABLE) && (mcState != mcDisable || // 如果处于Enable状态
			(mcState == mcDisable && !GetReg(mcRegParam.DriveCtrl, CTRL_DISABLE) && GetReg(usSRegHoldBuf[DRIVECTRL], CTRL_DISABLE))))
		{
			McStaSet.SetFlag.BrakeFlag = 0;
			mcState = mcDisable;
		}
	}

	// Main State Machine
	switch (mcState)
	{
	case mcReady:    // 关闭输出,上电会对电流进行采集校准,当采样校准结束标志置1且启动指令置1后，mcIdle
#if MOTOR_PRECHARGE_ENABLED
		Motor_Charge();
		if (mcFocCtrl.ChargeFinish == 1)
#endif
		{
			UpdateCurrentOffset();
		}
		if (mcCurOffset.OffsetFlag == 1)
		{
			Motor_DisableServo();
			mcState = mcIdle;
		}
		break;

	case mcIdle:
		if (mcRegParam.FlashCtrl == FLASH_START && usSRegHoldBuf[FLASHCTRL] == FLASH_UPLOAD)
			mcState = mcUpFlash;
		else if (mcRegParam.FlashCtrl == FLASH_START && usSRegHoldBuf[FLASHCTRL] == FLASH_DOWNLOAD)
			mcState = mcDownFlash;
		else if ((!GetReg(mcRegParam.DriveCtrl, CTRL_DOPHASEFIND) && GetReg(usSRegHoldBuf[DRIVECTRL], CTRL_DOPHASEFIND)) ||
			(!McStaSet.SetFlag.AutoPhaseFindSetFlag && (GetReg(mcRegParam.DriveMode, MODE_AUTOPHASEFIND) ||
			ReadBit(usSRegHoldBuf[DRIVEMODE], MODE_ENCABS) || usSRegHoldBuf[MOTORCOMMTYPE] == VOICECOIL_MOTOR ||
			((usSRegHoldBuf[ENCTYPE] == ENCODER_SEL_ABZ_HALL || usSRegHoldBuf[ENCTYPE] == ENCODER_SEL_HALLS_ONLY) &&
			(usSRegInBuf[HALLS] > 0 && usSRegInBuf[HALLS] < 7)))))
		{
			McStaSet.SetFlag.ChargeSetFlag = 0;
			McStaSet.SetFlag.PhaseFindSetFlag = 0;
			mcState = mcPhaseFind;
		}
#if FUNC_MOTOREST_ENABLED
		else if (!GetReg(mcRegParam.DriveCtrl, CTRL_DOMOTOREST) && GetReg(usSRegHoldBuf[DRIVECTRL], CTRL_DOMOTOREST))
		{
			McStaSet.SetFlag.IdentifySetFlag = 0;
			mcState = mcMotorIdentify;
		}
#endif // #if FUNC_MOTOREST_ENABLED
#if FUNC_HOME_ENABLED
		else if ((!GetReg(mcRegParam.DriveCtrl, CTRL_DOHOME) && GetReg(usSRegHoldBuf[DRIVECTRL], CTRL_DOHOME)) ||
			(!GetReg(mcRegParam.DigInStatus, INSTATUS_HOMECOMMAND) && GetReg(usSRegInBuf[DIGINSTATUS], INSTATUS_HOMECOMMAND)) ||
			(GetReg(usSRegHoldBuf[DRIVEMODE], MODE_AUTOHOME) && !McStaSet.SetFlag.AutoHomeSetFlag))
		{
			if (GetReg(usSRegInBuf[DRIVESTATUS], STATUS_PHASEFINDSUCCEED))
			{
				McStaSet.SetFlag.ChargeSetFlag = 0;
				Home_Reset();
				mcState = mcHome;
			}
			else
			{
				McStaSet.SetFlag.AutoHomeSetFlag = 1;
				mcFaultSource = FaultNotPhaseFind;
				FaultProcess();
			}
		}
#endif //#if FUNC_HOME_ENABLED
		else if ((!GetReg(mcRegParam.DriveCtrl, CTRL_ENABLE) && GetReg(usSRegHoldBuf[DRIVECTRL], CTRL_ENABLE)) ||
			(!GetReg(mcRegParam.DigInStatus, INSTATUS_ENABLE) && GetReg(usSRegInBuf[DIGINSTATUS], INSTATUS_ENABLE)) ||
			(GetReg(mcRegParam.DriveMode, MODE_AUTOENABLE) && !McStaSet.SetFlag.AutoEnableSetFlag))
		{
			if (GetReg(usSRegInBuf[DRIVESTATUS], STATUS_PHASEFINDSUCCEED) ||
				mcRegParam.WorkMode == CURSERIAL || mcRegParam.WorkMode == CURANALOG || mcRegParam.WorkMode == CURFRF)
			{
				McStaSet.SetFlag.ChargeSetFlag = 0;
				mcFocCtrl.StopFlag = 0;
				mcState = mcStart;
			}
			else
			{
				McStaSet.SetFlag.AutoEnableSetFlag = 1;
				mcFaultSource = FaultNotPhaseFind;
				FaultProcess();
			}
		}
		break;


	case mcPhaseFind:
#if MOTOR_PRECHARGE_ENABLED
		Motor_Charge();
		if (mcFocCtrl.ChargeFinish == 1)
#endif
		{
			Motor_PhaseFind_Init();

			if (mcDoPhaseFind.FinishFlag)
			{
				McStaSet.SetFlag.PhaseFindSetFlag = 0;
				SetReg(usSRegInBuf[DRIVESTATUS], STATUS_PHASEFINDSUCCEED, STATUS_PHASEFINDSUCCEED);
				McStaSet.SetFlag.BrakeFlag = 0;
				mcState = mcDisable; // mcIdle;
			}
		}
		break;

#if FUNC_HOME_ENABLED
	case mcHome:
#if MOTOR_PRECHARGE_ENABLED
		Motor_Charge();
		if (mcFocCtrl.ChargeFinish == 1)
#endif
		{
			Motor_Home();

			if (!GetReg(usSRegHoldBuf[DRIVECTRL], CTRL_DOHOME))
			{
				Home_Reset();
				mcFocCtrl.StopFlag = 1;
				McStaSet.SetFlag.StopSetFlag = 0;
				mcState = mcStop;
			}
			if (mcDoHome.State == HOME_FINISH)
			{
				mcDoHome.State = HOME_IDLE;
				SetReg(usSRegInBuf[DRIVESTATUS], STATUS_HOMECOMPLETE, STATUS_HOMECOMPLETE);
				if ((int16)usSRegHoldBuf[HOMEMETHOD] == NowPositionAsHome && !mcDoHome.EnableStatus)
				{
					mcState = mcIdle;
				}
				else
				{
					McStaSet.SetFlag.AutoEnableSetFlag = 1;
					mcState = mcRun;
				}
			}
#if FUNC_FORCECTRL_ENABLED
			ForceCtrl.PauseFlag = 1; // 回零时暂停力控模式
#endif
#if SPECIAL_ELESCREW_ENABLE
			ScrewCtrl.PauseFlag = 1;
#endif
		}
		
		break;
#endif //#if FUNC_HOME_ENABLED

	case mcStart:
#if MOTOR_PRECHARGE_ENABLED
		Motor_Charge();
		if (mcFocCtrl.ChargeFinish == 1)
#endif
		{
			Motor_Open();
			mcState = mcRun;
		}
		break;


	case mcRun:
		
#if FUNC_FORCECTRL_ENABLED
		if (usSRegHoldBuf[FCMOD]) // 力控模式
		{
			ForceCtrl_RunInit();
		}
		else 
#endif
#if SPECIAL_ELESCREW_ENABLE
		if (usSRegHoldBuf[ESCMOD]) 
		{
			ScrewCtrl_RunInit();
		}
		else                                                                                                                                                                                                                                                                                         
#endif //#if SPECIAL_ELESCREW_ENABLE
		{
			Motor_Run();
		}

		if ((!GetReg(mcRegParam.DigInStatus, INSTATUS_STOPONINPUT) && GetReg(usSRegInBuf[DIGINSTATUS], INSTATUS_STOPONINPUT))
			|| (GetReg(mcRegParam.DigInStatus, INSTATUS_ENABLE) && !GetReg(usSRegInBuf[DIGINSTATUS], INSTATUS_ENABLE)))
		{
			if (!GetReg(mcRegParam.DigInStatus, INSTATUS_STOPONINPUT) && GetReg(usSRegInBuf[DIGINSTATUS], INSTATUS_STOPONINPUT))
			{
				mcFocCtrl.StopFlag = 1;
			}
			mcState = mcStop;
			McStaSet.SetFlag.StopSetFlag = 0;
		}
#if FUNC_HOME_ENABLED
		else if ((!GetReg(mcRegParam.DigInStatus, INSTATUS_HOMECOMMAND) && GetReg(usSRegInBuf[DIGINSTATUS], INSTATUS_HOMECOMMAND)) ||
			(!GetReg(mcRegParam.DriveCtrl, CTRL_DOHOME) && GetReg(usSRegHoldBuf[DRIVECTRL], CTRL_DOHOME)))
		{
			Home_Reset();
			mcState = mcHome;
		}
#endif //#if FUNC_HOME_ENABLED
		break;

	case mcDisable:
#if FUNC_DISMODE_ENABLED
		Do_EmergencyStop();			//执行停机
#else
		Do_DisableServo();
		mcState = mcIdle;
#endif // #if FUNC_DISMODE_ENABLED
		break;

	case mcStop:
		Motor_Stop();
		if (McStaSet.SetFlag.StopSetFlag)
		{
			if (mcFocCtrl.StopFlag == 1)
			{
				mcFocCtrl.StopFlag = 0;
				usSRegHoldBuf[DRIVECTRL] = 0;
				mcState = mcRun;
			}
			else
			{
				McStaSet.SetFlag.BrakeFlag = 0;
				mcState = mcDisable;
			}
		}
		break;
		
#if FUNC_MOTOREST_ENABLED
	case mcMotorIdentify:
		Motor_Identify_Init();

		if (Motor_Identify_GetFinishFlag())
		{
			McStaSet.SetFlag.IdentifySetFlag = 0;
			McStaSet.SetFlag.BrakeFlag = 0;
			mcState = mcDisable; // mcIdle;
		}
		break;
#endif // #if FUNC_MOTOREST_ENABLED

	case mcFault:
		if (!GetReg(mcRegParam.DriveCtrl, CTRL_CLEARERR) && GetReg(usSRegHoldBuf[DRIVECTRL], CTRL_CLEARERR) ||
			(!GetReg(mcRegParam.DigInStatus, INSTATUS_CLEARFAULT) && GetReg(usSRegInBuf[DIGINSTATUS], INSTATUS_CLEARFAULT)))
		{
			FaultClear();
#if EXCTRL_ECAT_ENABLED || EXCTRL_CANOPEN_ENABLED
			CiA402_LocalError_OnceFlag = 0; //此处需要一句，ECAT状态机切换那里也需要一句
#endif
#if FUNC_HOME_ENABLED
			Home_Reset();
#endif //#if FUNC_HOME_ENABLED
			if (mcCurOffset.OffsetFlag == 1)
				mcState = mcIdle;
			else
				mcState = mcReady;
		}	
		break;

	case mcUpFlash:
		Motor_DisableServo();
#if FUNC_EEPROM_ENABLED
		if (UploadDataFromEEPROM())
		{
			SetReg(usSRegInBuf[CONTROLSTATUS], CTSTATUS_FLASHSTATE0 | CTSTATUS_FLASHSTATE1
				| CTSTATUS_FLASHSTATE2, 0x0);
		}
		else
		{
			SetReg(usSRegInBuf[CONTROLSTATUS], CTSTATUS_FLASHSTATE0 | CTSTATUS_FLASHSTATE1
				| CTSTATUS_FLASHSTATE2, 0x7);
		}
#endif //#if FUNC_EEPROM_ENABLED
		mcState = mcIdle;
		break;

	case mcDownFlash:
		Motor_DisableServo();
#if FUNC_EEPROM_ENABLED
		if (DownloadDataToEEPROM())
		{
			SetReg(usSRegInBuf[CONTROLSTATUS], CTSTATUS_FLASHSTATE0 | CTSTATUS_FLASHSTATE1
				| CTSTATUS_FLASHSTATE2, 0x0);
		}	
		else
		{
			SetReg(usSRegInBuf[CONTROLSTATUS], CTSTATUS_FLASHSTATE0 | CTSTATUS_FLASHSTATE1
				| CTSTATUS_FLASHSTATE2, 0x7);
		}
#endif //#if FUNC_EEPROM_ENABLED
		mcState = mcIdle;
		break;
	}
}
