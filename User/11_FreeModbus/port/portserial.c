/*
 * FreeModbus Libary: RT-Thread Port
 * Copyright (C) 2013 Armink <armink.ztl@gmail.com>
 * 
 * Modifications Copyright (C) 2022-2026 Fortior Technology Co., Ltd.
 * Author: Summer.li <summer.li@fortiortech.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * File: $Id: portserial.c,v 1.60 2013/08/13 15:07:05 Armink $
 *		 $Id: portserial.c,v 2.01 2022/05/13 11:09:05 Summer.li: Made corresponding modifications for the Fengyin MCU chip $
 */

#include "port.h"

/* ----------------------- Modbus includes ----------------------------------*/
#include "mb.h"
#include "mbport.h"
#include "UART.h"
#include "GPIO.h"

/* ----------------------- Static variables ---------------------------------*/
PortSerialTypeDef       PortSerial;

/* ----------------------- Defines ------------------------------------------*/
/* serial transmit event */
#define EVENT_SERIAL_TRANS_START    (1<<0)

/* ----------------------- static functions ---------------------------------*/


/* ----------------------- Start implementation -----------------------------*/
void xMBPortSerialInit(void)
{  
#if(MODBUS_UART == 1)
	UART1_Init(); // uart initial in UART.c
#else
    UART2_Init();
#endif
    
#if COMM_SERIAL_RS485_ENABLED
    clr_csr(RTSRS485_GPIO, RTSRS485_PIN);
    set_csr(RTSRS485_OE, RTSRS485_PIN);		// Output enable /* 0: Enable digital output */
#endif
}

void vMBPortSerialEnable(BOOL xRxEnable, BOOL xTxEnable)
{
	PortSerial.RxEnable = xRxEnable;
	PortSerial.TxEnable = xTxEnable;

	if (xTxEnable)
	{
		xMBPortTxDMASwitch();
#if COMM_SERIAL_RS485_ENABLED
		set_csr(RTSRS485_GPIO, RTSRS485_PIN);
#endif
	}
	else
	{
		xMBPortRxDMASwitch();
	
#if COMM_SERIAL_RS485_ENABLED
		Delay_us(30); //Because UART + DMA transmission can cause one byte to enter the DMA interrupt early, add a delay before pulling RE low
		clr_csr(RTSRS485_GPIO, RTSRS485_PIN);
#endif
	}
}

void vMBPortClose(void)
{ 
#if(MODBUS_UART == 1)
	UART1_Close();
#else
    UART2_Close();
#endif
}