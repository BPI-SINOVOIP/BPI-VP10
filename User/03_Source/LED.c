/*
 * Copyright (c) 2023-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : LED.c
 * Author        : Zougi.Zou
 * Date          : 2023-09-20
 * Description   : 数码管显示 AIP650
 *
 * Record        :
 * V1.0, 2023-09-20, Zougi.Zou: Created file
 */

#include <Myproject.h>

LedTubeTypeDef mcLedTube;
const uint8 Digital_Table[16] = {	//数码管的段码
	0x3F,  // 0
	0x06,  // 1
	0x5B,  // 2
	0x4F,  // 3
	0x66,  // 4
	0x6D,  // 5
	0x7D,  // 6
	0x07,  // 7
	0x7F,  // 8
	0x6F,  // 9
	0x77,  // A
	0x7C,  // B
	0x39,  // C
	0x5E,  // D
	0x79,  // E
	0x71,  // F
//	0x3D,  // G
//	0x76,  // H
//	0x10,  // I
//	0x0E,  // J
//	0x7A,  // K
//	0x38,  // L
//	0x55,  // M
//	0x54,  // N
//	0x5C,  // O
//	0x73,  // P
//	0x67,  // Q
//	0x50,  // R
//	0x64,  // S
//	0x78,  // T
//	0x80,  //.
//	0x00   //'null '
};

#if FUNC_LED_DIODE_ENABLED
LedDiodeTypeDef mcLedDiode = { 0 };
#endif // #if FUNC_LED_DIODE_ENABLED

/*---------------------------------------------------------------------------*/
/* Name		:	void LedTube_Init(void)
/* Input	:	NO
/* Output	:	NO
/* Description:	Initial Led Register.
/*---------------------------------------------------------------------------*/
void LedTube_Init(void)
{
	uint8 temp = LED_LIGHT5;
	I2C_Master_WriteBytes(LED_CMD_MOD, &temp, 1);	//数码管开，7级显示亮度
}


/*---------------------------------------------------------------------------*/
/* Name		:	void LedTube_UpdateStatus(void)
/* Input	:	NO
/* Output	:	NO
/* Description:	Update Led tube Status.
/*---------------------------------------------------------------------------*/
void LedTube_UpdateStatus(void)
{
	uint8 temp = 0, temp1 = 0;
	if (mcFaultSource == FaultNoSource)
	{
		if (mcState == mcPhaseFind)
			mcLedTube.Status = LED_PHASEFIND_MODE;
		else if (mcState == mcHome)
			mcLedTube.Status = LED_HOME_MODE;
		else
			mcLedTube.Status = mcRegParam.WorkMode + LED_WORKMODE_OFFSET;
		
		mcLedTube.Status = Digital_Table[mcLedTube.Status];
		if (GetReg(usSRegInBuf[DRIVESTATUS], STATUS_ENABLE) == STATUS_ENABLE)
			mcLedTube.Status |= 0x80;
		else
			mcLedTube.Status &= 0x7F;
	}
	else
	{
		mcLedTube.Status_Pre = LED_FAULT_OFFSET;

		mcLedTube.FaultDisplay[0] = Digital_Table[0x0F];
		mcLedTube.FaultDisplay[1] = Digital_Table[(mcFaultSource >> 8) & 0x0F];
		temp = (mcFaultSource & 0xFF) / 10;
		temp1 = (mcFaultSource & 0xFF) % 10;
		if (temp != 0)
		{
			mcLedTube.FaultDisplay[2] = Digital_Table[temp];
			mcLedTube.FaultDisplay[3] = Digital_Table[temp1];
			mcLedTube.FaultDisplayLen = 4;
		}	
		else
		{
			mcLedTube.FaultDisplay[2] = Digital_Table[temp1];
			mcLedTube.FaultDisplayLen = 3;
		}
	}

	if (mcFaultSource == FaultNoSource)
	{
		if (mcLedTube.Status_Pre != mcLedTube.Status)
		{
			I2C_Master_WriteBytes(LED_DIG0, &mcLedTube.Status, 1);
			mcLedTube.Status_Pre = mcLedTube.Status;
		}
	}
	else
	{
		if (mcLedTube.TimeCounter < LED_BLINK_TIME)
		{
			mcLedTube.TimeCounter++;
		}
		else
		{
			mcLedTube.TimeCounter = 0;
			mcLedTube.LenCounter++;
			if (mcLedTube.LenCounter >= mcLedTube.FaultDisplayLen)
				mcLedTube.LenCounter = 0;
			I2C_Master_WriteBytes(LED_DIG0, &mcLedTube.FaultDisplay[mcLedTube.LenCounter], 1);
		}
		
	}
}



#if FUNC_LED_DIODE_ENABLED
/*---------------------------------------------------------------------------*/
/* Name		:	void LedDiode_Display(void)
/* Input	:	NO
/* Output	:	NO
/* Description:	LED灯显示
/*---------------------------------------------------------------------------*/
void LedDiode_Display(void)
{
	switch (mcFaultSource)
	{
	case FaultNoSource:
		ResetLEDPin;
		memset(&mcLedDiode, 0, sizeof(LedDiodeTypeDef));
		break;
	default:
		LedDiode_OnOff(&mcLedDiode, mcFaultSourceSize[(mcFaultSource - 0xA00) >> 8] + (mcFaultSource & 0xFF));
		break;
	}

}

/*---------------------------------------------------------------------------*/
/* Name		:	void LedDiode_OnOff(void)
/* Input	:	NO
/* Output	:	NO
/* Description:	LED灯的闪烁
/*---------------------------------------------------------------------------*/
void LedDiode_OnOff(LedDiodeTypeDef* hLedDisplay, uint8 htime)
{
	if (hLedDisplay->LedTimCot < 2 *htime)
	{
		if (hLedDisplay->Count < Led_OnOff_Freq)
		{
			hLedDisplay->Count++;
		}
		else
		{
			hLedDisplay->Count = 0;
			//			LEDPinONOFF;
			hLedDisplay->LedOnOff = 1 - hLedDisplay->LedOnOff;
			if (hLedDisplay->LedOnOff)
			{
				SetLEDPin;
			}
			else
			{
				ResetLEDPin;
			}
			hLedDisplay->LedTimCot++;
		}
	}
	else
	{
		if (hLedDisplay->Count < Led_Wait_Time)
		{
			hLedDisplay->Count++;
		}
		else
		{
			hLedDisplay->LedTimCot = 0;
			hLedDisplay->Count = 0;
			hLedDisplay->LedOnOff = 0;
		}
		ResetLEDPin;
	}
}
#endif // #if FUNC_LED_DIODE_ENABLED