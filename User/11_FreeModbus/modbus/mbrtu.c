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
 * File: $Id: mbrtu.c,v 1.18 2007/09/12 10:15:56 wolti Exp $
 *		 $Id: mbrtu.c,v 2.01 2022/05/13 11:09:05 Summer.li: 针对峰岹MCU芯片做相应修改 $
 */

/* ----------------------- System includes ----------------------------------*/
#include "stdlib.h"
#include "string.h"

/* ----------------------- Platform includes --------------------------------*/
#include "port.h"

/* ----------------------- Modbus includes ----------------------------------*/
#include "mb.h"
#include "mbrtu.h"
#include "mbframe.h"

#include "mbcrc.h"
#include "mbport.h"

#include <Myproject.h>

/* ----------------------- Defines ------------------------------------------*/
#define MB_SER_PDU_SIZE_MIN     4       /*!< Minimum size of a Modbus RTU frame. */
#define MB_SER_PDU_SIZE_MAX     22      /*!< Maximum size of a Modbus RTU frame. */
#define MB_SER_PDU_SIZE_CRC     2       /*!< Size of CRC field in PDU. */
#define MB_SER_PDU_ADDR_OFF     0       /*!< Offset of slave address in Ser-PDU. */
#define MB_SER_PDU_PDU_OFF      1       /*!< Offset of Modbus-PDU in Ser-PDU. */
#define MB_SER_PDU_FUNC_OFF     1       /*!< Offset of Modbus-Func in Ser-PDU. */
#define MB_STOP_STREAM_SIZE     50      /*!< Bytes send to stop the data stream. */
#define MB_RCV_BUFFFER_SIZE     8       /*!< Size of DMA receive buffer. */

/* ----------------------- Type definitions ---------------------------------*/
typedef enum
{
	STATE_RX_INIT,              /*!< Receiver is in initial state. */
	STATE_RX_IDLE,              /*!< Receiver is in idle state. */
	STATE_RX_RCV,               /*!< Frame is beeing received. */
	STATE_RX_ERROR              /*!< If the frame is invalid. */
} eMBRcvState;

typedef enum
{
	STATE_TX_IDLE,              /*!< Transmitter is in idle state. */
	STATE_TX_XMIT               /*!< Transmitter is in transfer state. */
} eMBSndState;

/* ----------------------- Static variables ---------------------------------*/
static volatile eMBSndState eSndState;
static volatile eMBRcvState eRcvState;

volatile UCHAR ucRTUBuf[MB_SER_PDU_SIZE_MAX];

static volatile USHORT usSndAddrCount = 0;
static volatile USHORT usSndOffsetCount = 0;

static UCHAR ucRxDMABuf[MB_RCV_BUFFFER_SIZE];

/* ----------------------- Start implementation -----------------------------*/
void
	eMBRTUInit(void)
{
	ENTER_CRITICAL_SECTION();

	/* Modbus RTU uses 8 Databits. */ 
	xMBPortSerialInit();
	xMBPortRxDMAInit(ucRxDMABuf, MB_RCV_BUFFFER_SIZE);
	usMBCRCInit();

	EXIT_CRITICAL_SECTION();

}

void
	eMBRTUStart(void)
{
	ENTER_CRITICAL_SECTION();
	/* Initially the receiver is in the state STATE_RX_INIT. we start
	 * the timer and if no character is received within t3.5 we change
	 * to STATE_RX_IDLE. This makes sure that we delay startup of the
	 * modbus protocol stack until the bus is free.
	 */
	eRcvState = STATE_RX_INIT;
	vMBPortSerialEnable(TRUE, FALSE);

	EXIT_CRITICAL_SECTION();
}

void
	eMBRTUStop(void)
{
	ENTER_CRITICAL_SECTION();
	vMBPortSerialEnable(FALSE, FALSE);
	EXIT_CRITICAL_SECTION();
}

eMBErrorCode
	eMBRTUReceive(UCHAR * pucRcvAddress, UCHAR * *pucFrame, USHORT * pusLength)
{
	eMBErrorCode eStatus = MB_ENOERR;

	ENTER_CRITICAL_SECTION();

	if (usMBCRC16((UCHAR *) ucRTUBuf, MB_RCV_BUFFFER_SIZE) == 0)
	{
		/* Save the address field. All frames are passed to the upper layed
		 * and the decision if a frame is used is done there.
		 */
		*pucRcvAddress = ucRTUBuf[MB_SER_PDU_ADDR_OFF];

		/* Total length of Modbus-PDU is Modbus-Serial-Line-PDU minus
		 * size of address field and CRC checksum.
		 */
		*pusLength = (USHORT)(MB_RCV_BUFFFER_SIZE - MB_SER_PDU_PDU_OFF - MB_SER_PDU_SIZE_CRC);

		/* Return the start of the Modbus PDU to the caller. */
		*pucFrame = (UCHAR *) & ucRTUBuf[MB_SER_PDU_PDU_OFF];
	}
	else
	{
		eStatus = MB_EIO;
	}

	EXIT_CRITICAL_SECTION();
	return eStatus;
}

eMBErrorCode
	eMBRTUSend(UCHAR ucSlaveAddress, const UCHAR * pucFrame, USHORT usLength)
{
	eMBErrorCode eStatus = MB_ENOERR;
	UCHAR * pucSndBufferCur;
	USHORT usSndBufferCount;
	USHORT usCRC16;

	ENTER_CRITICAL_SECTION();

	/* Check if the receiver is still in idle state. If not we where to
	 * slow with processing the received frame and the master sent another
	 * frame on the network. We have to abort sending the frame.
	 */
	if (eRcvState == STATE_RX_IDLE)
	{
		/* First byte before the Modbus-PDU is the slave address. */
		pucSndBufferCur = (UCHAR *) pucFrame - 1;
		usSndBufferCount = 1;

		/* Now copy the Modbus-PDU into the Modbus-Serial-Line-PDU. */
		pucSndBufferCur[MB_SER_PDU_ADDR_OFF] = ucSlaveAddress;
		usSndBufferCount += usLength;

		/* Calculate CRC16 checksum for Modbus-Serial-Line-PDU. */
		if(pucSndBufferCur[MB_SER_PDU_FUNC_OFF] == MB_FUNC_READ_SCOPE_REGISTER)
			usCRC16 = usMBCRCSum(SendFramePointer);
		else
			usCRC16 = usMBCRC16((UCHAR *) pucSndBufferCur, usSndBufferCount);
				
		pucSndBufferCur[usSndBufferCount++] = (UCHAR)(usCRC16 & 0xFF);
		pucSndBufferCur[usSndBufferCount++] = (UCHAR)(usCRC16 >> 8);

		/* Activate the transmitter. */
		eSndState = STATE_TX_XMIT;
		vMBPortSerialEnable(FALSE, TRUE);
	}
	else
	{
		eStatus = MB_EIO;
	}
	EXIT_CRITICAL_SECTION();
	return eStatus;
}


// Receive data with DMA
void xMBRTUReceiveDMAFSM(void)
{
// 760 ns
//	ucRTUBuf[0] = ucRxDMABuf[0];
//	ucRTUBuf[1] = ucRxDMABuf[1];
//	ucRTUBuf[2] = ucRxDMABuf[2];
//	ucRTUBuf[3] = ucRxDMABuf[3];
//	ucRTUBuf[4] = ucRxDMABuf[4];
//	ucRTUBuf[5] = ucRxDMABuf[5];
//	ucRTUBuf[6] = ucRxDMABuf[6];
//	ucRTUBuf[7] = ucRxDMABuf[7];

	memcpy(ucRTUBuf, ucRxDMABuf, MB_RCV_BUFFFER_SIZE); // 1160 ns
	
	xMBPortEventPost(EV_FRAME_RECEIVED);
	eRcvState = STATE_RX_IDLE;
}

// Receive data with DMA
void xMBRTUReceiveDMAReset(void)
{
	xMBPortRxDMAReset();
}

void xMBRTUTransmitDMAFSM(void)
{
	USHORT IncLen = 0;

	//    assert_param( eRcvState == STATE_RX_IDLE );
	switch (eSndState)
	{
	case STATE_TX_XMIT:
		if (usSndOffsetCount >= SendFramePointer.Length[usSndAddrCount])
		{
			usSndOffsetCount = 0;
			usSndAddrCount++;
		}
		if (usSndAddrCount < SendFramePointer.Count)
		{
			IncLen = SendFramePointer.Length[usSndAddrCount] - usSndOffsetCount;
			if (IncLen > DMA_MAXLEN)
				IncLen = DMA_MAXLEN;

			usSndOffsetCount += IncLen;
			xMBPortTxDMAStart(SendFramePointer.Addr[usSndAddrCount] + usSndOffsetCount - IncLen, IncLen);
		}
		else
		{
			usSndAddrCount = 0;
			usSndOffsetCount = 0;
//			xMBPortEventPost(EV_FRAME_SENT);
			/* Disable transmitter. This prevents another transmit buffer
			 * empty interrupt. */
			vMBPortSerialEnable(TRUE, FALSE);
			eSndState = STATE_TX_IDLE;
		}
		break;
		/* We should not get a transmitter event if the transmitter is in idle state.  */
	default: // case STATE_TX_IDLE:
		/* enable receiver/disable transmitter. */
		usSndAddrCount = 0;
		usSndOffsetCount = 0;
		vMBPortSerialEnable(TRUE, FALSE);
		break;
	}
}