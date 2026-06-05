/*
 * Copyright (c) 2023-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : LED.h
 * Author        : Zougi.Zou
 * Date          : 2023-09-20
 * Description   : 数码管显示 AIP650
 *
 * Record        :
 * V1.0, 2023-09-20, Zougi.Zou: Created file
 */

#ifndef __LED_H__
#define __LED_H__

// Include external header file.
#include "fu7502.h"


//数码管位地址
#define	LED_DIG0							(0x68)	//Dig0位
#define	LED_DIG1							(0x6A)	//Dig1位
#define	LED_DIG2							(0x6C)	//Dig2位
#define	LED_DIG3							(0x6E)  //Dig3位


//数码管按键地址	KEYx_y	x指哪一段，y指哪一位数码管
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


// 数码管数据命令设置
#define LED_CMD_MOD							(0x48)	//模式命令
#define LED_CMD_RD							(0x49)	//读按键数据命令

// 数码管辉度设置
#define LED_LIGHT1							(0x11)	//1级亮度
#define LED_LIGHT2							(0x21)	//2级亮度
#define LED_LIGHT3							(0x31)	//3级亮度
#define LED_LIGHT4							(0x41)	//4级亮度
#define LED_LIGHT5							(0x51)	//5级亮度
#define LED_LIGHT6							(0x61)	//6级亮度
#define LED_LIGHT7							(0x71)	//7级亮度
#define LED_LIGHT8							(0x00)	//8级亮度

// 数码管状态显示
#define LED_WORKMODE_OFFSET					(0x00)
#define LED_FAULT_OFFSET					(0xFF)
#define LED_PHASEFIND_MODE					(0x07)
#define LED_HOME_MODE						(0x08)

// 数码管显示更新时间
#define LED_BLINK_TIME						(600)

// LED灯闪烁
#define Led_OnOff_Freq						(300)       // Led display on-off frequency
#define Led_Wait_Time						(1500)


#ifdef ERR_GPIO
#define SetLEDPin       {set_csr(ERR_GPIO, ERR_PIN);}
#define ResetLEDPin     {clr_csr(ERR_GPIO, ERR_PIN);}
#define LEDPinONOFF     {xor_csr(ERR_GPIO, ERR_PIN);}
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
	uint16 Count;                   // 电平翻转计数
	uint8 LedTimCot;               // 闪灯次数计数
	uint8 LedOnOff;
} LedDiodeTypeDef;



extern void LedTube_Init(void);
extern void LedTube_UpdateStatus(void);

extern void LedDiode_Display(void);
extern void LedDiode_OnOff(LedDiodeTypeDef* hLedDisplay, uint8 htime);

#endif