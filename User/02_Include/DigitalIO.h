/*
 * Copyright (c) 2021-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : DigitalIO.h
 * Author        : Summer
 * Date          : 2021-11-13
 * Description   : This file define some function for Digital IO.
 *
 * Record        :
 * V1.0, 2021-11-13, Summer: Created file
 */

#ifndef __DIGITALIO_H_
#define __DIGITALIO_H_

#include "Parameter.h"

/*==================================================================================================*/
/***************************************        MACRO         ***************************************/
/*==================================================================================================*/

#define INMODE_HANDLERS_MAX    (12)
#define OUTMODE_HANDLERS_MAX   (6)


// Definition of register DIGINSTATUS
#define INSTATUS_OPMODECHANGE2						   0x0400          // Operation Mode Change 2 Switch
#define INSTATUS_OPMODECHANGE1                         0x0200          // Operation Mode Change 1 Switch
#define INSTATUS_GAINSWITCH                            0x0100          // Gain Switch
#define INSTATUS_HOMESWITCH                            0x0080          // home Switch
#define INSTATUS_NEGALIMITSWITCH                       0x0040          // home Negative Limit Switch
#define INSTATUS_POSILIMITSWITCH                       0x0020          // home Positive Limit Switch
#define INSTATUS_HOMECOMMAND                           0x0010          // home begin
#define INSTATUS_STOPONINPUT                           0x0008          // decelerate to velocity zero
#define INSTATUS_EMERGENCYSTOP                         0x0004          // Emergency stop, activates Active Disable
#define INSTATUS_CLEARFAULT                            0x0002          // clear fault
#define INSTATUS_ENABLE                                0x0001          // enable position loop


typedef enum {
    IO_LOW  = 0,
    IO_HIGH = 1,
} IOStatus_t;


// define INMODE function table
typedef enum
{
	INMODE_IDLE,                 // do nothing
	INMODE_ENABLE,               // enable motor
	INMODE_CLEARFAULT,           // clear fault
	INMODE_EMERGENCYSTOP,        // Emergency stop, activates Active Disable
	INMODE_STOPONINPUT,          // decelerate to velocity zero
	INMODE_HOMECOMMAND,          // home begin
	INMODE_POSILIMITSWITCH,      // home Positive Limit Switch
	INMODE_NEGALIMITSWITCH,      // home Negative Limit Switch
	INMODE_HOMESWITCH,           // home Switch
	INMODE_GAINSWITCH,           // gain Switch
	INMODE_OPMODECHANGE1,         // Operation mode change while drive enabled 1
	INMODE_OPMODECHANGE2,         // Operation mode change while drive enabled 2
	INMODE_JOGPOSDIRSPD1,        // JOG motor to positive direction at speed JOGSPD1
	INMODE_JOGNEGDIRSPD1,        // JOG motor to negative direction at speed -JOGSPD1
	INMODE_JOGPOSDIRSPD2,        // JOG motor to positive direction at speed JOGSPD2
	INMODE_JOGNEGDIRSPD2,        // JOG motor to negative direction at speed JOGSPD2
} InMode_Table;


// define OUTMODE function table
typedef enum
{
	OUTMODE_IDLE,                   // do nothing
	OUTMODE_ENABLE,                 // enable motor
	OUTMODE_FAULT,                  // clear fault
	OUTMODE_HOMECOMPLETE,           // home complete
	OUTMODE_PHASEFINDSUCCEED,       // phase find succeed
} OutMode_Table;



typedef         void( *pxInModeHandler ) ( uint8 DigInput );


extern pxInModeHandler        pxInModeHandlers[INMODE_HANDLERS_MAX];


extern void UpdateDigitalIO(void);
extern void eInModeIdle(uint8 DigInput);
extern void eInModeEnable(uint8 DigInput);
extern void eInModeClearFault(uint8 DigInput);
extern void eInModeEmergencyStop(uint8 DigInput);
extern void eInModeStopOnInput(uint8 DigInput);
extern void eInModeHomeCommand(uint8 DigInput);
extern void eInModePosiLimitSwitch(uint8 DigInput);
extern void eInModeNegaLimitSwitch(uint8 DigInput);
extern void eInModeHomeSwitch(uint8 DigInput);
extern void eInModeGainSwitch(uint8 DigInput);
extern void eInModeOpModeChange1(uint8 DigInput);
extern void eInModeOpModeChange2(uint8 DigInput);
extern void eInModeJogPosDirSpd1(uint8 DigInput);
extern void eInModeJogNegDirSpd1(uint8 DigInput);
extern void eInModeJogPosDirSpd2(uint8 DigInput);
extern void eInModeJogNegDirSpd2(uint8 DigInput);

#endif