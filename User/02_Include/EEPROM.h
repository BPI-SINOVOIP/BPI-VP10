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


#define	EEPROM_DEV_ADDR						(0xA0)					// IIC写入时的地址字节数据

#define CHECK_KEY1							(0X55)
#define CHECK_KEY2							(0XAA)
#define CHECK_ADDR							(16380)

#define EEPROM_ERR_ADDR_START				(0x0000)				// 故障存储开始地址
#define EEPROM_ERR_ADDR_SIZE				((MAXERRHIST << 2))     // 报错历史的存储空间(byte)

#define EEPROM_PARAM_ADDR_START				(0x0040)				// Holding Register存储开始地址
#define EEPROM_PARAM_ADDR_SIZE				(S_REG_HOLDING_NREGS << 1)     // Holding Register的存储空间(byte)

#define EEPROM_ID_ADDR_START				(0x003E)				// ID存储开始地址
#define EEPROM_ID_ADDR_SIZE					(2)						// ID的存储空间(byte)

#define EEPROM_PNUM_ADDR_START				(0x07C0)				// 每组参数个数的存储开始地址
#define EEPROM_PNUM_ADDR_SIZE				(64)					// 每组参数个数的存储空间(byte)

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