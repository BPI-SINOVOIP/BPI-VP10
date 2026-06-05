/*
 * FreeModbus Libary: A portable Modbus implementation for Modbus ASCII/RTU.
 * FreeModbus Extension: Custom Function Code Support (for Servo Project)
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
 * File: $Id: mbfuncscope.c,v 2.01 2022/05/13 11:09:05 Summer.li: 针对峰岹MCU芯片做相应修改 $
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

/* ----------------------- Other includes ----------------------------------*/
#include "Scope.h"

/* ----------------------- Defines ------------------------------------------*/
#define MB_PDU_FUNC_READ_ADDR_OFF           ( MB_PDU_DATA_OFF )
#define MB_PDU_FUNC_READ_REGCNT_OFF         ( MB_PDU_DATA_OFF + 2 )
#define MB_PDU_FUNC_READ_SIZE               ( 4 )
#define MB_PDU_FUNC_READ_REGCNT_MAX			(0x0002) //( 0x007D )


#if MB_FUNC_READ_SCOPE_ENABLED > 0

eMBException
	eMBFuncReadScopeRegister(UCHAR * pucFrame, USHORT * usLen)
{
	USHORT usRegAddress;
	USHORT usRegCount;
	USHORT usRegLen;
	UCHAR * pucFrameCur;
	USHORT usTemp;

	eMBException eStatus = MB_EX_NONE;
	eMBErrorCode eRegStatus;

	if (*usLen == (MB_PDU_FUNC_READ_SIZE + MB_PDU_SIZE_MIN))
	{
		usRegAddress = (USHORT)(pucFrame[MB_PDU_FUNC_READ_ADDR_OFF] << 8);
		usRegAddress |= (USHORT)(pucFrame[MB_PDU_FUNC_READ_ADDR_OFF + 1]);

		usRegCount = (USHORT)(pucFrame[MB_PDU_FUNC_READ_REGCNT_OFF] << 8);
		usRegCount |= (USHORT)(pucFrame[MB_PDU_FUNC_READ_REGCNT_OFF + 1]);

		/* Check if the number of registers to read is valid. If not
		 * return Modbus illegal data value exception.
		 */
		if ((usRegCount >= 1) && (usRegCount <= S_REG_SCOPE_NREGS))
		{
			/* First byte contains the function code. */
			pucFrameCur = &pucFrame[MB_PDU_DATA_OFF];
			*usLen = MB_PDU_DATA_OFF;

			/* Second word in the response contain the number of bytes. */
			if (Scope_GetDataReadyFlag(usRegAddress))
			{
				usRegLen = usRegCount << 1; 
				*pucFrameCur++ = (UCHAR)(usRegLen >> 8);
				*pucFrameCur++ = (UCHAR)(usRegLen & 0xFF);
				*usLen += 2;
				
//				eStatus = eMBRegScopeCB(pucFrameCur, usRegAddress, usRegCount, TRUE);
				
				if ((usRegAddress >= 0) && (usRegAddress <= S_REG_SCOPE_NREGS))
				{
					if (usRegAddress + usRegCount <= S_REG_SCOPE_NREGS)
					{
						SendFramePointer.Count = 3;
						SendFramePointer.Length[0] = 4; // Header
						SendFramePointer.Length[1] = usRegCount * 2; // Data
						SendFramePointer.Length[2] = 2; // CRC

						SendFramePointer.Addr[0] = pucFrame - 1;
						SendFramePointer.Addr[1] = &usSRegScopeBuf[usRegAddress];
						SendFramePointer.Addr[2] = SendFramePointer.Addr[0] + SendFramePointer.Length[0];
					}
					else
					{
						SendFramePointer.Count = 4;
						SendFramePointer.Length[0] = 4; // Header
						SendFramePointer.Length[1] = (S_REG_SCOPE_NREGS - usRegAddress) * 2; // Data1
						SendFramePointer.Length[2] = (usRegAddress + usRegCount - S_REG_SCOPE_NREGS) * 2; // Data2
						SendFramePointer.Length[3] = 2; // CRC

						SendFramePointer.Addr[0] = pucFrame - 1;
						SendFramePointer.Addr[1] = &usSRegScopeBuf[usRegAddress];
						SendFramePointer.Addr[2] = &usSRegScopeBuf[0];
						SendFramePointer.Addr[3] = SendFramePointer.Addr[0] + SendFramePointer.Length[0];
					}
				}
				else
				{
					eStatus = MB_EX_ILLEGAL_DATA_ADDRESS;
				}
			}
			else
			{
				usRegLen = 2;
				*pucFrameCur++ = (UCHAR)(usRegLen >> 8);
				*pucFrameCur++ = (UCHAR)(usRegLen & 0xFF);
				*usLen += 2;
				
				usTemp = usSRegInBuf[SCOPESTATUS];
				*pucFrameCur++ = (UCHAR)(usTemp >> 8);
				*pucFrameCur++ = (UCHAR)(usTemp & 0xFF);
				*usLen += 2;
				
//				eStatus = eMBRegScopeCB(pucFrameCur, usRegAddress, usRegCount, FALSE);
				
				if ((usRegAddress >= 0) && (usRegAddress <= S_REG_SCOPE_NREGS))
				{
					SendFramePointer.Count = 2;
					SendFramePointer.Length[0] = 6;
					SendFramePointer.Length[1] = 2;

					SendFramePointer.Addr[0] = pucFrame - 1;
					SendFramePointer.Addr[1] = SendFramePointer.Addr[0] + SendFramePointer.Length[0];
				}
				else
				{
					eStatus = MB_EX_ILLEGAL_DATA_ADDRESS;
				}
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


#endif // #if MB_FUNC_READ_SCOPE_ENABLED > 0
