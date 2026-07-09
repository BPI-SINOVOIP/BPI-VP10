/*
 * Copyright (c) 2023-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : EEPROM.h
 * Author        : Zougi.Zou
 * Date          : 2023-09-20
 * Description   : EEPROM read and write
 *
 * Record        :
 * V1.0, 2023-09-20, Zougi.Zou: Created file
 */

#ifndef __EEPROM_H__
#define __EEPROM_H__

// Include external header file.
#include "fu7502.h"


#define	EEPROM_DEV_ADDR						(0xA0)					// Address byte used for I2C writes

#define CHECK_KEY1							(0X55)
#define CHECK_KEY2							(0XAA)
#define CHECK_ADDR							(16380)

#define EEPROM_ERR_ADDR_START				(0x0000)				// Fault storage start address
#define EEPROM_ERR_ADDR_SIZE				((MAXERRHIST << 2))     // Error history storage space (bytes)

#define EEPROM_PARAM_ADDR_START				(0x0040)				// Holding Register storage start address
#define EEPROM_PARAM_ADDR_SIZE				(S_REG_HOLDING_NREGS << 1)     // Holding Register storage space (bytes)

#define EEPROM_ID_ADDR_START				(0x003E)				// ID storage start address
#define EEPROM_ID_ADDR_SIZE					(2)						// ID storage space (bytes)

#define EEPROM_PNUM_ADDR_START				(0x07C0)				// Start address for storing the number of parameters per group
#define EEPROM_PNUM_ADDR_SIZE				(64)					// Storage space for parameter count per group (bytes)


#define FLASH_ID_ADDR_START					(0xFFE8 & 0xFFFFFFF8)	// ID storage start address
#define FLASH_ID_ADDR_SIZE					(8)						// ID storage space (bytes)

// EEPROM
typedef struct
{
	uint16 WordAddr;
} FaultHistStoreTypeDef;




extern bool DownloadDataToEEPROM(void);
extern bool UploadDataFromEEPROM(void);
extern bool EEPROM_WriteBytes(uint16 WordAddr, uint8* pData, uint16 NumByte);
extern bool EEPROM_ReadBytes(uint16 WordAddr, uint8* pData, uint16 NumByte);
extern bool EEPROM_ReadRegister(uint16 WordAddr, uint16* pData, uint16* pRegStartNew, uint16* pRegStartOld);
extern bool EEPROM_Check(void);

#endif