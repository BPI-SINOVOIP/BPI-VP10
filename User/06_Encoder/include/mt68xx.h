/*
 * Copyright (c) 2025-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : mt68xx.h
 * Author        : Summer
 * Date          : 2025-11-17
 * Description   : File of MT68xx chip communication.
 *
 * Record        :
 * V1.0, 2025-11-17, Summer: Created file
 */

#ifndef __MT68XX_H
#define __MT68XX_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "Myproject.h"


#define MT68_READ_ANGLE                        ( 0x0A )
#define MT68_READ_REG                          ( 0x03 )
#define MT68_WRITE_REG                         ( 0x06 )
#define MT68_WRITE_MTP                         ( 0x0C )

typedef struct
{
	uint8 SPISel;
	uint16 EncCalStart;
	uint16 EncCalState;
	uint16 EncSave;
	uint16 EncRegWrite;
	uint16 EncRegRead;
	uint32 EncCalCounter;
} EncMTTypedef;


extern EncMTTypedef EncMT1;
extern EncMTTypedef EncMT2;

uint8_t MT68_ReadAngle(EncMTTypedef* p, uint32_t * pAngle);
void MT68_ReadReg(EncMTTypedef* p, uint16_t addr, uint8_t * pRegValue);
void MT68_WriteReg(EncMTTypedef* p, uint16_t addr, uint8_t data);
uint8_t MT68_WriteRegToMTP(EncMTTypedef* p);
void MT68_Init(EncMTTypedef* p, uint8_t SPISel);
uint8 MT68_Calibration(EncMTTypedef* p, uint16 EncCalStart, uint16 EncSave, uint16 EncRegWrite,
	uint16 EncRegRead, uint16 EncRegAddr, uint16* pEncRegValue);

#ifdef __cplusplus
}
#endif

#endif /* __MT68XX_H */
