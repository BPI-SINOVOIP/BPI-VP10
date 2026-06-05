/*
 * FreeModbus Libary: A portable Modbus implementation for Modbus ASCII/RTU.
 * FreeModbus Extension: Custom Function Code Support (for Servo Project)
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
 * File: $Id: portdma.c,v 2.01 2022/05/13 11:09:05 Summer.li: 针对峰岹MCU芯片做相应修改 $
 */

#include "port.h"

/* ----------------------- Modbus includes ----------------------------------*/
#include "mb.h"
#include "mbport.h"
#include <Myproject.h>


/* ----------------------- Static variables ---------------------------------*/
//PortSerialTypeDef       PortSerial;
unsigned char* RxAddr;
char RxLen;

/* ----------------------- Defines ------------------------------------------*/


/* ----------------------- static functions ---------------------------------*/



/* ----------------------- Start implementation -----------------------------*/
void xMBPortRxDMAInit(unsigned char* ulAddr, char cLen)
{
#if(MODBUS_UART == 1)
	SetPipe_DMA0(DMA_Uart1_Read);
#else
	SetPipe_DMA0(DMA_Uart2_Read); // receive data
#endif
	SetDataPackage_DMA0(ulAddr, cLen);
	SetIRQ_DMA0(1);
	RxAddr = ulAddr;
	RxLen = cLen;
}


/*
 * Reset DMA when receive error exist.
 */
void xMBPortRxDMAReset(void)
{
#if(MODBUS_UART == 1)
	clr_csr(UT1_CR0, UTTI); // 清标志位
	clr_csr(UT1_CR0, UTRI);
#else
	clr_csr(UT2_CR0, UTTI); // 清标志位
	clr_csr(UT2_CR0, UTRI);
#endif
#if COMM_SERIAL_RS485_ENABLED
	clr_csr(RTSRS485_GPIO, RTSRS485_PIN);
#endif
	Switch_DMA0();
	Reset_DMA0();
}


void xMBPortTxDMAStart(unsigned char* ulAddr, char cLen)
{
#if(MODBUS_UART == 1)
	clr_csr(UT1_CR0, UTTI); // 清标志位
#else
	clr_csr(UT2_CR0, UTTI); // 清标志位
#endif
	
	SetDataPackage_DMA0(ulAddr, cLen);
	Switch_DMA0();
}

void xMBPortRxDMASwitch(void)
{
#if(MODBUS_UART == 1)
	clr_csr(UT1_CR0, UTRI);
#else
	clr_csr(UT2_CR0, UTRI);
#endif

#if(MODBUS_UART == 1)
	SetPipe_DMA0(DMA_Uart1_Read);
#else
	SetPipe_DMA0(DMA_Uart2_Read); // receive data
#endif
	SetDataPackage_DMA0(RxAddr, RxLen);
	Switch_DMA0();
}

void xMBPortTxDMASwitch(void)
{
	Close_DMA0();
#if(MODBUS_UART == 1)
	SetPipe_DMA0(DMA_Uart1_Send);
#else
	SetPipe_DMA0(DMA_Uart2_Send); // transmit data
#endif
}
