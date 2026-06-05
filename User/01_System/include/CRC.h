/*
 * Copyright (c) 2022-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : CRC.h
 * Author        : Fortior Application Team
 * Date          : 2022-09-21
 * Description   : define CRC
 *
 * Record        :
 * V1.0, 2022-09-21, Fortior Application Team: Created file
 */

#ifndef __CRC_H__
#define __CRC_H__

#include "fu7502.h"

/*************************************************************************************///External Function
extern unsigned short CRC_Check(unsigned char start_sector, unsigned char offset_sector);
extern uint8 CalCRC8(uint8* pbuf, uint8 buflen, uint8 xorVal);

#endif