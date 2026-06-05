/*
 * Copyright (c) 2025-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : kth71xx.h
 * Author        : Summer
 * Date          : 2025-11-17
 * Description   : File of kth71xx chip communication.
 *
 * Record        :
 * V1.0, 2025-11-17, Summer: Created file
 */


#ifndef __KTH71XX_H
#define __KTH71XX_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "Myproject.h"


#define KTH71_READ_ANGLE                        0x00
#define KTH71_READ_REG                          0x11
#define KTH71_WRITE_REG                         0x33


typedef struct
{
	uint8 SPISel;
	uint8 UnlockFlag;
	uint16 EncCalStart;
	uint16 EncCalState;
	uint16 EncSave;
	uint16 EncRegWrite;
	uint16 EncRegRead;
	uint32 EncCalCounter;
} EncKTHTypedef;


extern EncKTHTypedef EncKTH1;
extern EncKTHTypedef EncKTH2;

uint8_t KTH71_ReadAngle(EncKTHTypedef* p, uint16_t* pAngle);
uint8_t KTH71_ReadReg(EncKTHTypedef* p, uint8_t addr, uint8_t* pRegValue);
uint8_t KTH71_WriteReg(EncKTHTypedef* p, uint8_t addr, uint8_t dataw);
void KTH71_UnlockReg(EncKTHTypedef* p);
void KTH71_LockReg(EncKTHTypedef* p);
void KTH71_WriteRegToMTP(EncKTHTypedef* p);
void KTH71_Init(EncKTHTypedef* p, uint8_t SPISel);
uint8 KTH71_Calibration(EncKTHTypedef* p, uint16 EncCalStart, uint16 EncSave, uint16 EncRegWrite,
	uint16 EncRegRead, uint16 EncRegAddr, uint16 *pEncRegValue);

#ifdef __cplusplus
}
#endif

#endif /* __KTH71XX_H */
