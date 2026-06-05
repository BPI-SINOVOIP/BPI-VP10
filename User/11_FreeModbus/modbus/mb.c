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
 * File: $Id: mb.c,v 1.27 2007/02/18 23:45:41 wolti Exp $
 *		 $Id: mb.c,v 2.01 2022/05/13 11:09:05 Summer.li: 针对峰岹MCU芯片做相应修改 $
 */
#include <Myproject.h>
/* ----------------------- System includes ----------------------------------*/
#include "stdlib.h"
#include "string.h"

/* ----------------------- Platform includes --------------------------------*/
#include "port.h"

/* ----------------------- Modbus includes ----------------------------------*/

#include "mb.h"
#include "mbconfig.h"
#include "mbframe.h"
#include "mbproto.h"
#include "mbfunc.h"

#include "mbport.h"
#if MB_SLAVE_RTU_ENABLED == 1
#include "mbrtu.h"
#endif
#if MB_SLAVE_ASCII_ENABLED == 1
#include "mbascii.h"
#endif
#if MB_SLAVE_TCP_ENABLED == 1
#include "mbtcp.h"
#endif

#ifndef MB_PORT_HAS_CLOSE
#define MB_PORT_HAS_CLOSE 0
#endif

/* ----------------------- Static variables ---------------------------------*/

static UCHAR ucMBAddress;

static enum
{
	STATE_NOT_INITIALIZED,
	STATE_ENABLED,
	STATE_DISABLED,
} eMBState = STATE_NOT_INITIALIZED;



/* An array of Modbus functions handlers which associates Modbus function
 * codes with implementing functions.
 */
static const xMBFunctionHandler xFuncHandlers[MB_FUNC_HANDLERS_MAX] = {
#if MB_FUNC_OTHER_REP_SLAVEID_ENABLED > 0
	{ MB_FUNC_OTHER_REPORT_SLAVEID, eMBFuncReportSlaveID },
#endif
#if MB_FUNC_READ_INPUT_ENABLED > 0
	{ MB_FUNC_READ_INPUT_REGISTER, eMBFuncReadInputRegister },
#endif
#if MB_FUNC_READ_HOLDING_ENABLED > 0
	{ MB_FUNC_READ_HOLDING_REGISTER, eMBFuncReadHoldingRegister },
#endif
#if MB_FUNC_WRITE_MULTIPLE_HOLDING_ENABLED > 0
	{ MB_FUNC_WRITE_MULTIPLE_REGISTERS, eMBFuncWriteMultipleHoldingRegister },
#endif
#if MB_FUNC_WRITE_HOLDING_ENABLED > 0
	{ MB_FUNC_WRITE_REGISTER, eMBFuncWriteHoldingRegister },
#endif
#if MB_FUNC_READWRITE_HOLDING_ENABLED > 0
	{ MB_FUNC_READWRITE_MULTIPLE_REGISTERS, eMBFuncReadWriteMultipleHoldingRegister },
#endif
#if MB_FUNC_READ_COILS_ENABLED > 0
	{ MB_FUNC_READ_COILS, eMBFuncReadCoils },
#endif
#if MB_FUNC_WRITE_COIL_ENABLED > 0
	{ MB_FUNC_WRITE_SINGLE_COIL, eMBFuncWriteCoil },
#endif
#if MB_FUNC_WRITE_MULTIPLE_COILS_ENABLED > 0
	{ MB_FUNC_WRITE_MULTIPLE_COILS, eMBFuncWriteMultipleCoils },
#endif
#if MB_FUNC_READ_DISCRETE_INPUTS_ENABLED > 0
	{ MB_FUNC_READ_DISCRETE_INPUTS, eMBFuncReadDiscreteInputs },
#endif
#if MB_FUNC_READ_SCOPE_ENABLED > 0
	{ MB_FUNC_READ_SCOPE_REGISTER, eMBFuncReadScopeRegister },
#endif
};

/* ----------------------- Start implementation -----------------------------*/
eMBErrorCode
	eMBInit(UCHAR ucSlaveAddress)
{
	eMBErrorCode eStatus = MB_ENOERR;

	/* check preconditions */
	if ((ucSlaveAddress == MB_ADDRESS_BROADCAST) ||
		(ucSlaveAddress < MB_ADDRESS_MIN) || (ucSlaveAddress > MB_ADDRESS_MAX))
	{
		eStatus = MB_EINVAL;
	}
	else
	{
		ucMBAddress = ucSlaveAddress;

		eMBRTUInit();
		
		xMBPortEventInit();
		
		eMBState = STATE_DISABLED;
	}
	return eStatus;
}



eMBErrorCode
	eMBEnable(void)
{
	eMBErrorCode eStatus = MB_ENOERR;

	if (eMBState == STATE_DISABLED)
	{
		/* Activate the protocol stack. */
		eMBRTUStart();
		eMBState = STATE_ENABLED;
	}
	else
	{
		eStatus = MB_EILLSTATE;
	}
	return eStatus;
}

eMBErrorCode
	eMBDisable(void)
{
	eMBErrorCode eStatus;

	if (eMBState == STATE_ENABLED)
	{
		eMBRTUStop();
		eMBState = STATE_DISABLED;
		eStatus = MB_ENOERR;
	}
	else if (eMBState == STATE_DISABLED)
	{
		eStatus = MB_ENOERR;
	}
	else
	{
		eStatus = MB_EILLSTATE;
	}
	return eStatus;
}

eMBErrorCode eMBPoll(void)
{
	static UCHAR * ucMBFrame;
	static UCHAR ucRcvAddress;
	static UCHAR ucFunctionCode;
	static USHORT usLength;
	static eMBException eException;

	int i;
	eMBErrorCode eStatus = MB_ENOERR;
	eMBEventType eEvent;

	/* Check if the protocol stack is ready. */
	if (eMBState != STATE_ENABLED)
	{
		return MB_EILLSTATE;
	}
	
	/* Check if there is a event available. If not return control to caller.
	 * Otherwise we will handle the event. */
	if (xMBPortEventGet(&eEvent) == TRUE)
	{
		switch (eEvent)
		{
		case EV_FRAME_RECEIVED:
			// Function pointer handle sometimes will error:
			// error C212: indirect call: parameters do not fit within registers
			eStatus = eMBRTUReceive(&ucRcvAddress, &ucMBFrame, &usLength);
			if (eStatus == MB_ENOERR)
			{
				/* Check if the frame is for us. If not ignore the frame. */
				if ((ucRcvAddress == ucMBAddress) || (ucRcvAddress == MB_ADDRESS_BROADCAST))
				{
					(void)xMBPortEventPost(EV_EXECUTE);
				}
				else
				{
					xMBRTUReceiveDMAReset();
				}
			}
			else
			{
				xMBRTUReceiveDMAReset();
			}
			break;

		case EV_EXECUTE:
			ucFunctionCode = ucMBFrame[MB_PDU_FUNC_OFF];
			eException = MB_EX_ILLEGAL_FUNCTION;
			for (i = 0; i < MB_FUNC_HANDLERS_MAX; i++)
			{
				if (xFuncHandlers[i].ucFunctionCode == ucFunctionCode)
				{
					eException = xFuncHandlers[i].pxHandler(ucMBFrame, &usLength);
					break;
				}
			}
			/* If the request was not sent to the broadcast address we
			 * return a reply. */
			if (ucRcvAddress != MB_ADDRESS_BROADCAST)
			{
				if (eException != MB_EX_NONE)
				{
					/* An exception occured. Build an error frame. */
					usLength = 2;
					ucMBFrame[0] = (UCHAR)(ucFunctionCode | MB_FUNC_ERROR);
					ucMBFrame[1] = eException;

					eMBRegErrorCB(ucMBFrame);
				}
				eStatus = eMBRTUSend(ucMBAddress, ucMBFrame, usLength);
				if (eStatus == MB_ENOERR) //no error
				{
					xMBRTUTransmitDMAFSM();
				}
				else
				{
					xMBRTUReceiveDMAReset();
				}
			}
			else
			{
				xMBRTUReceiveDMAReset();
			}
			break;

		default:
			break;
		}
	}
	return MB_ENOERR;
}
