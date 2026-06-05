/*
 * Copyright (c) 2022-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : I2C.h
 * Author        : Fortior Application Team
 * Date          : 2022-09-21
 * Description   : define I2C read and write
 *
 * Record        :
 * V1.0, 2022-09-21, Fortior Application Team: Created file
 */

#ifndef __I2C_H__
#define __I2C_H__

#include "fu7502.h"


typedef struct
{
	uint8 PortSel;
	uint8 Mode;
	uint16 Baud;
	uint8 GCSel;
	uint8 ID;
	uint8 DataDirection;
	uint8 Interrupt;
	uint8 AutoDMA;
	uint8 DMANackIgnore;
} I2CConfiguration;


/***********************I2C´úÂë´¦Àí******************/

#define I2C_Speed_100K				(MCU_CLOCK * 1000 / 100 - 1)
#define I2C_Speed_400K				(MCU_CLOCK * 1000 / 400 - 1)
#define I2C_Speed_1M				(MCU_CLOCK * 1000 / 1000 - 1)

#define Master							(1)
#define Slave							(0)

#define Disable							(0)
#define Enable							(1)

#define InitialPort						(0)
#define TransferPort					(1)

#define	Data_Send						(0)
#define Data_Read						(1)

#define I2C								(0)
#define I2C2							(1)

/*************************************************************************************///External Function
extern void I2C_Init(void);
extern void I2C_Configuration(uint8 I2CSel, I2CConfiguration* Config);
extern bool I2C_Master_WriteBytes(uint8 DevAddr, uint8* pData, uint16 NumByte);
extern bool I2C_Master_WriteBytes_Ext(uint8 DevAddr, uint16 WordAddr, uint8* pData, uint16 NumByte);
extern bool I2C_Master_ReadBytes(uint8 DevAddr, uint8* pData, uint16 NumByte, uint8 isStart, uint8 isEnd);


#endif