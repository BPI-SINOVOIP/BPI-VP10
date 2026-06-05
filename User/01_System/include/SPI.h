/*
 * Copyright (c) 2022-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : SPI.h
 * Author        : Fortior Application Team
 * Date          : 2022-09-21
 * Description   : define SPI
 *
 * Record        :
 * V1.0, 2022-09-21, Fortior Application Team: Created file
 */

#ifndef __SPI_H__
#define __SPI_H__

#include "fu7502.h"

#define SEL_SPI1							(0)
#define SEL_SPI2							(1)

#define SELECT_SPI			clr_csr(SPI1_CR, NSSMOD0)
#define DESELECT_SPI		set_csr(SPI1_CR, NSSMOD0)

#ifdef NSS2_PIN
#define SELECT_SPI2			clr_csr(NSS2_GPIO, NSS2_PIN)
#define DESELECT_SPI2		set_csr(NSS2_GPIO, NSS2_PIN)
#else
#define SELECT_SPI2			clr_csr(SPI2_CR, NSSMOD0)
#define DESELECT_SPI2		set_csr(SPI2_CR, NSSMOD0)
#endif

/*************************************************************************************///External Function
extern void SPI1_Init(void);
extern void SPI2_Init(void);
extern void SPI_ECAT_Init(void);
extern uint8 WR_CMD(uint8 cmd);
extern uint8 WR_CMD2(uint8 cmd);
extern uint8 SPI_Transmit(uint8 SPISel, uint8* pTxData, uint8 txLen, uint8 Timeout);
extern uint8 SPI_Receive(uint8 SPISel, uint8* pRxData, uint8 rxLen, uint8 Timeout);
extern void SPI_TransmitReceive(uint8 SPISel, uint8 * pTxData, uint8 * pRxData, uint8 txLen, uint8 rxLen);

#endif
