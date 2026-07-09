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
 * File: $Id: mbfuncinput.c,v 1.10 2007/09/12 10:15:56 wolti Exp $
 *		 $Id: mbfuncinput.c,v 2.01 2022/05/13 11:09:05 Summer.li: Made corresponding modifications for Fengyin MCU chips $
 */

/* ----------------------- System includes ----------------------------------*/
#include "stdlib.h"
#include "string.h"

/* ----------------------- Platform includes --------------------------------*/
#include "port.h"

/* ----------------------- Modbus includes ----------------------------------*/
#include "mb.h"
#include "mbframe.h"
#include "mbproto.h"
#include "mbconfig.h"
#include "user_mb_app.h"

/* ----------------------- Defines ------------------------------------------*/
#define MB_PDU_FUNC_READ_ADDR_OFF           ( MB_PDU_DATA_OFF )
#define MB_PDU_FUNC_READ_REGCNT_OFF         ( MB_PDU_DATA_OFF + 2 )
#define MB_PDU_FUNC_READ_SIZE               ( 4 )
#define MB_PDU_FUNC_READ_REGCNT_MAX			(0x0002) //( 0x007D )



/* ----------------------- Start implementation -----------------------------*/
#if MB_FUNC_READ_INPUT_ENABLED > 0

eMBException
eMBFuncReadInputRegister( UCHAR * pucFrame, USHORT * usLen )
{
	USHORT usAddressH, usAddressL;
    USHORT usRegCount;
    USHORT iRegIndex;
    UCHAR * pucFrameCur;

    eMBException    eStatus = MB_EX_NONE;

    if( *usLen == ( MB_PDU_FUNC_READ_SIZE + MB_PDU_SIZE_MIN ) )
    {
    	usAddressH = pucFrame[MB_PDU_FUNC_READ_ADDR_OFF];
    	usAddressL = pucFrame[MB_PDU_FUNC_READ_ADDR_OFF + 1];
    	
        usRegCount = ( USHORT )( pucFrame[MB_PDU_FUNC_READ_REGCNT_OFF] << 8 );
        usRegCount |= ( USHORT )( pucFrame[MB_PDU_FUNC_READ_REGCNT_OFF + 1] );

        /* Check if the number of registers to read is valid. If not
         * return Modbus illegal data value exception.
         */
        if( ( usRegCount >= 1 )
            && ( usRegCount <= MB_PDU_FUNC_READ_REGCNT_MAX ) )
        {
            /* Second byte in the response contain the number of bytes. */
        	pucFrameCur = &pucFrame[MB_PDU_DATA_OFF];
        	*pucFrameCur++ = (UCHAR)(usRegCount << 1);
            *usLen = 2 + (usRegCount << 1);

//            eStatus =
//                eMBRegInputCB(&pucFrame[MB_PDU_FUNC_READRLY_DATA_OFF], usRegAddressH, usRegAddressL, usRegCount );

            if (usAddressH < S_REG_INPUT_INDEX_MAX)
            {
            	iRegIndex = (USHORT)(usSRegInStartArray[usAddressH] + usAddressL);
            	if (iRegIndex + usRegCount <= usSRegInStartArray[usAddressH + 1])
            	{
            		SendFramePointer.Count = 1;
            		SendFramePointer.Length[0] = (usRegCount << 1) + 5;
            		SendFramePointer.Addr[0] = pucFrame - 1;

            		while (usRegCount > 0)
            		{
            			*pucFrameCur++ = (UCHAR)(usSRegInBuf[iRegIndex] >> 8);
            			*pucFrameCur++ = (UCHAR)(usSRegInBuf[iRegIndex] & 0xFF);
            			iRegIndex++;
            			usRegCount--;
            		}
            	}
            	else
            	{
            		eStatus = MB_EX_ILLEGAL_DATA_ADDRESS;
            	}
            }
            else
            {
            	eStatus = MB_EX_ILLEGAL_DATA_ADDRESS;
            }
        }
        else
        {
            eStatus = MB_EX_ILLEGAL_DATA_VALUE;
        }
    }
    else
    {
        /* Can't be a valid read input register request because the length
         * is incorrect. */
        eStatus = MB_EX_ILLEGAL_DATA_VALUE;
    }
    return eStatus;
}

#endif