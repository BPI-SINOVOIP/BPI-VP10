/*
 * Copyright (c) 2023-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : LED.h
 * Author        : Zougi.Zou
 * Date          : 2023-09-20
 * Description   : Seven-segment display AIP650
 *
 * Record        :
 * V1.0, 2023-09-20, Zougi.Zou: Created file
 */

#ifndef __LED_H__
#define __LED_H__

// Include external header file.
#include "fu7502.h"


//Seven-segment digit addresses
#define	LED_DIG0							(0x68)	//Dig0 digit
#define	LED_DIG1							(0x6A)	//Dig1 digit
#define	LED_DIG2							(0x6C)	//Dig2 digit
#define	LED_DIG3							(0x6E)  //Dig3 digit


//Seven-segment key addresses	KEYx_y	x indicates which section, y indicates which digit of the display
#define KEY1_1								(0x44)
#define KEY1_2								(0x45)
#define KEY1_3								(0x46)
#define KEY1_4								(0x47)

#define KEY2_1								(0x4C)
#define KEY2_2								(0x4D)
#define KEY2_3								(0x4E)
#define KEY2_4								(0x4F)

#define KEY3_1								(0x54)
#define KEY3_2								(0x55)
#define KEY3_3								(0x56)
#define KEY3_4								(0x57)

#define KEY4_1								(0x5C)
#define KEY4_2								(0x5D)
#define KEY4_3								(0x5E)
#define KEY4_4								(0x5F)

#define KEY5_1								(0x64)
#define KEY5_2								(0x65)
#define KEY5_3								(0x66)
#define KEY5_4								(0x67)

#define KEY6_1								(0x6C)
#define KEY6_2								(0x6D)
#define KEY6_3								(0x6E)
#define KEY6_4								(0x6F)

#define KEY7_1								(0x74)
#define KEY7_2								(0x75)
#define KEY7_3								(0x76)
#define KEY7_4								(0x77)


// Seven-segment data command settings
#define LED_CMD_MOD							(0x48)	//Mode command
#define LED_CMD_RD							(0x49)	//Read key data command

// Seven-segment brightness settings
#define LED_LIGHT1							(0x11)	//Brightness level 1
#define LED_LIGHT2							(0x21)	//Brightness level 2
#define LED_LIGHT3							(0x31)	//Brightness level 3
#define LED_LIGHT4							(0x41)	//Brightness level 4
#define LED_LIGHT5							(0x51)	//Brightness level 5
#define LED_LIGHT6							(0x61)	//Brightness level 6
#define LED_LIGHT7							(0x71)	//Brightness level 7
#define LED_LIGHT8							(0x00)	//Brightness level 8

// Seven-segment status display
#define LED_WORKMODE_OFFSET					(0x00)
#define LED_FAULT_OFFSET					(0xFF)
#define LED_PHASEFIND_MODE					(0x07)
#define LED_HOME_MODE						(0x08)

// Seven-segment display update time
#define LED_BLINK_TIME						(600)

// LED lamp blinking
#define Led_OnOff_Freq						(300)       // LED on-off blink time
#define Led_Wait_Time						(1500)      // Wait time after LED blinking finishes


#ifdef ERR_GPIO
#define SetLEDPin       {set_csr(ERR_GPIO, ERR_PIN);;}
#define ResetLEDPin     {clr_csr(ERR_GPIO, ERR_PIN);;}
#define LEDPinONOFF     {xor_csr(ERR_GPIO, ERR_PIN);;}
#endif

// Led Tube
typedef struct
{
	uint8 Status;
	uint8 Status_Pre;
	uint16 TimeCounter;
	uint8 LenCounter;
	uint8 FaultDisplayLen;
	uint8 FaultDisplay[4];
} LedTubeTypeDef;


// Led Diode
typedef struct
{
	uint16 Count;                   // Level toggle count
	uint8 LedTimCot;               // Blink count
	uint8 LedOnOff;
} LedDiodeTypeDef;



extern void LedTube_Init(void);
extern void LedTube_UpdateStatus(void);

extern void LedDiode_Display(void);
extern void LedDiode_OnOff(LedDiodeTypeDef* hLedDisplay, uint8 htime);

#endif