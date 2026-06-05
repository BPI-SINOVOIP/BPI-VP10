/*
 * Copyright (c) 2022-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : UART.h
 * Author        : Fortior Application Team
 * Date          : 2022-09-21
 * Description   : define UART
 *
 * Record        :
 * V1.0, 2022-09-21, Fortior Application Team: Created file
 */

#ifndef __UART_H__
#define __UART_H__

#include "fu7502.h"

#define BUFFLEN        (32)
#define UARTDATALEN    (8)
#define UARTHEADLEN    (5)

typedef struct
{
	unsigned char Length;
	unsigned char CheckSum;
	unsigned char CheckSumInit;
	unsigned char T_DATA[BUFFLEN];
} TypeDef_Uart;

extern TypeDef_Uart UART_ANO;

/*************************************************************************************///External Function
extern void UART1_Init(void);
extern void UART1_Close(void);
extern void UART1_Clear(void);
extern void UART2_Init(void);
extern void UART2_Close(void);
extern void UART2_Clear(void);
extern void PutByte(char c);
extern void GetByte(char* c);
extern void UART2_UpdateBaud(uint16 Baud);
extern void UART_ANODubugerBuffConfig(void);
extern void UART_ANODubugerBuffInit(void);
extern void UART_ANODubugerBuffData(void);
extern void SendDataByUart();

#endif