/*
 * FreeModbus Libary: A portable Modbus implementation for Modbus ASCII/RTU.
 * Copyright (c) 2006-2018 Christian Walter <cwalter@embedded-solutions.at>
 * All rights reserved.
 *
 * Modifications Copyright (C) 2022-2026 Fortior Technology Co., Ltd.
 * Author: Summer.li <summer.li@fortiortech.com>
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * File: $Id: mbport.h,v 1.17 2006/12/07 22:10:34 wolti Exp $
 *            mbport.h,v 1.60 2013/08/17 11:42:56 Armink Add Master Functions  $
 *		 $Id: mbport.h,v 2.01 2022/05/13 11:09:05 Summer.li: 针对峰岹MCU芯片做相应修改 $
 */

#ifndef _MB_PORT_H
#define _MB_PORT_H

#ifdef __cplusplus
PR_BEGIN_EXTERN_C
#endif

#include "Parameter.h"

/*! \brief If connect with ServoStudio using CAN is enabled. */
#define COMM_SERIAL_RS485_ENABLED				(COMM_UART_RS485_ENABLED)
  
// 选择UART1或者UART2          
#define MODBUS_UART								( 2 )


	/* ----------------------- Defines ------------------------------------------*/

	/* ----------------------- Type definitions ---------------------------------*/

	typedef enum
{
	EV_READY = 1 << 0,         /*!< Startup finished. */
		EV_FRAME_RECEIVED = 1 << 1,         /*!< Frame received. */
		EV_EXECUTE = 1 << 2,         /*!< Execute function. */
		EV_FRAME_SENT = 1 << 3          /*!< Frame sent. */
} eMBEventType;

typedef enum
{
	EV_MASTER_READY = 1 << 0,  /*!< Startup finished. */
		EV_MASTER_FRAME_RECEIVED = 1 << 1,  /*!< Frame received. */
		EV_MASTER_EXECUTE = 1 << 2,  /*!< Execute function. */
		EV_MASTER_FRAME_SENT = 1 << 3,  /*!< Frame sent. */
		EV_MASTER_ERROR_PROCESS = 1 << 4,  /*!< Frame error process. */
		EV_MASTER_PROCESS_SUCESS = 1 << 5,  /*!< Request process success. */
		EV_MASTER_ERROR_RESPOND_TIMEOUT = 1 << 6,  /*!< Request respond timeout. */
		EV_MASTER_ERROR_RECEIVE_DATA = 1 << 7,  /*!< Request receive data error. */
		EV_MASTER_ERROR_EXECUTE_FUNCTION = 1 << 8,  /*!< Request execute function error. */
} eMBMasterEventType;

typedef enum
{
	EV_ERROR_RESPOND_TIMEOUT,         /*!< Slave respond timeout. */
		EV_ERROR_RECEIVE_DATA,            /*!< Receive frame data erroe. */
		EV_ERROR_EXECUTE_FUNCTION,        /*!< Execute function error. */
} eMBMasterErrorEventType;

/*! \ingroup modbus
 * \brief Parity used for characters in serial mode.
 *
 * The parity which should be applied to the characters sent over the serial
 * link. Please note that this values are actually passed to the porting
 * layer and therefore not all parity modes might be available.
 */
typedef enum
{
	MB_PAR_NONE,                /*!< No parity. */
		MB_PAR_ODD,                 /*!< Odd parity. */
		MB_PAR_EVEN                 /*!< Even parity. */
} eMBParity;

/* ----------------------- Supporting functions -----------------------------*/
void xMBPortEventInit(void);

void xMBPortEventPost(eMBEventType eEvent);

BOOL xMBPortEventGet( /*@out@ */ eMBEventType* eEvent);


/* ----------------------- Serial port functions ----------------------------*/

void xMBPortSerialInit(void);

void vMBPortClose(void);

void xMBPortSerialClose(void);

void vMBPortSerialEnable(BOOL xRxEnable, BOOL xTxEnable);

//
/* ----------------------- DMA functions ----------------------------*/
void xMBPortRxDMAInit(unsigned char* ulAddr, char cLen);

void xMBPortRxDMAReset(void);

void xMBPortTxDMAStart(unsigned char* ulAddr, char cLen);

void xMBPortRxDMASwitch(void);
	
void xMBPortTxDMASwitch(void);


/* ----------------------- Callback for the protocol stack ------------------*/



#ifdef __cplusplus
PR_END_EXTERN_C
#endif
#endif
