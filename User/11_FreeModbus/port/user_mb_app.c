/*
 * FreeModbus Libary: user callback functions and buffer define in slave mode
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
 * File: $Id: user_mb_app.c,v 1.60 2013/11/23 11:49:05 Armink $
 *		 $Id: user_mb_app.c,v 2.01 2022/05/13 11:09:05 Summer.li: 针对峰岹MCU芯片做相应修改 $
 */

#include "user_mb_app.h"
#include <Myproject.h>


SendFramePointerTypeDef SendFramePointer;

//Slave mode:InputRegister variables
USHORT usSRegInBuf[S_REG_INPUT_NREGS] = { 0 };
USHORT const usSRegInStartArray[S_REG_INPUT_INDEX_MAX + 1] = {
	S_REG_INPUT_START_STATUS,
	S_REG_INPUT_START_VERSION,
	S_REG_INPUT_START_CONTROLLER,
	S_REG_INPUT_START_DIGITAL,
	S_REG_INPUT_START_OTHERS,
	S_REG_INPUT_START_PROTECT,
	S_REG_INPUT_START_TEST,
	S_REG_INPUT_SIZE_TOTAL
};

//Slave mode:HoldingRegister variables
USHORT usSRegHoldBuf[S_REG_HOLDING_NREGS] = { 0 };
USHORT const usSRegHoldStartArray[S_REG_HOLDING_INDEX_MAX + 1] = {
	S_REG_HOLDING_START_CTRL,
	S_REG_HOLDING_START_COMMUNICATION,
	S_REG_HOLDING_START_DRIVER,
	S_REG_HOLDING_START_MOTOR,
	S_REG_HOLDING_START_FEEDBACK,
	S_REG_HOLDING_START_CONTROLLER,
	S_REG_HOLDING_START_OUTFILT,
	S_REG_HOLDING_START_LIMIT,
	S_REG_HOLDING_START_MOTION,
	S_REG_HOLDING_START_FORCECTRL,
	S_REG_HOLDING_START_DIGITAL,
	S_REG_HOLDING_START_ANALOG,
	S_REG_HOLDING_START_TEST,
	S_REG_HOLDING_START_ERRCOR,
	S_REG_HOLDING_SIZE_TOTAL
};

USHORT usSRegScopeBuf[S_REG_SCOPE_NREGS] = { 0 };

//USHORT   code  usSRegHoldBuf_Flash[S_REG_HOLDING_NREGS] _at_ (0x7000);


/**
 * Modbus slave input register callback function.
 *
 * @param pucRegBuffer input register buffer
 * @param usAddress input register address
 * @param usNRegs input register number
 *
 * @return result
 */
eMBErrorCode eMBRegInputCB(UCHAR * pucRegBuffer, UCHAR usAddressH, UCHAR usAddressL, USHORT usNRegs)
{
	eMBErrorCode eStatus = MB_ENOERR;
	USHORT iRegIndex;
	USHORT * pusRegInputBuf;

	pusRegInputBuf = usSRegInBuf;

	if (usAddressH < S_REG_INPUT_INDEX_MAX)
	{
		iRegIndex = (USHORT)(usSRegInStartArray[usAddressH] + usAddressL);
		if (iRegIndex + usNRegs <= usSRegInStartArray[usAddressH + 1])
		{
			// set SendFramePointer
			SendFramePointer.Count = 1;
			SendFramePointer.Length[0] = (usNRegs << 1) + 5;
			SendFramePointer.Addr[0] = pucRegBuffer - 3;

			while (usNRegs > 0)
			{
				*pucRegBuffer++ = (UCHAR)(pusRegInputBuf[iRegIndex] >> 8);
				*pucRegBuffer++ = (UCHAR)(pusRegInputBuf[iRegIndex] & 0xFF);
				iRegIndex++;
				usNRegs--;
			}
		}
		else
		{
			eStatus = MB_ENOREG;
		}
	}
	else
	{
		eStatus = MB_ENOREG;
	}
	return eStatus;
}


/**
 * Modbus slave holding register callback function.
 *
 * @param pucRegBuffer holding register buffer
 * @param usAddress holding register address
 * @param usNRegs holding register number
 * @param eMode read or write
 *
 * @return result
 */
eMBErrorCode eMBRegHoldingCB(UCHAR * pucRegBuffer, UCHAR usAddressH, UCHAR usAddressL,
	USHORT usNRegs, eMBRegisterMode eMode)
{
	eMBErrorCode eStatus = MB_ENOERR;
	USHORT iRegIndex;
	USHORT * pusRegHoldingBuf;

	pusRegHoldingBuf = usSRegHoldBuf;

	if (usAddressH < S_REG_HOLDING_INDEX_MAX)
	{
		iRegIndex = (USHORT)(usSRegHoldStartArray[usAddressH] + usAddressL);
		if (iRegIndex + usNRegs <= usSRegHoldStartArray[usAddressH + 1])
		{
			switch (eMode)
			{
				/* read current register values from the protocol stack. */
			case MB_REG_READ:
				// set SendFramePointer
				SendFramePointer.Count = 1;
				SendFramePointer.Length[0] = usNRegs * 2 + 5;
				SendFramePointer.Addr[0] = pucRegBuffer - 3;

				while (usNRegs > 0)
				{
					*pucRegBuffer++ = (UCHAR)(pusRegHoldingBuf[iRegIndex] >> 8);
					*pucRegBuffer++ = (UCHAR)(pusRegHoldingBuf[iRegIndex] & 0xFF);
					iRegIndex++;
					usNRegs--;
				}
				break;

				/* write current register values with new values from the protocol stack. */
			case MB_REG_WRITE:
				// set SendFramePointer
				SendFramePointer.Count = 1;
				SendFramePointer.Length[0] = 8;
				SendFramePointer.Addr[0] = pucRegBuffer - 4;

				while (usNRegs > 0)
				{
					pusRegHoldingBuf[iRegIndex] = (USHORT)(*pucRegBuffer++) << 8;
					pusRegHoldingBuf[iRegIndex] |= *pucRegBuffer++;
					iRegIndex++;
					usNRegs--;
				}
				break;
			}
		}
		else
		{
			eStatus = MB_ENOREG;
		}
	}
	else
	{
		eStatus = MB_ENOREG;
	}
	return eStatus;
}

/**
 * Modbus slave scope register callback function.
 *
 * @param pucRegBuffer scope register buffer
 * @param usAddress scope register address
 * @param usNRegs scope register number
 * @param bIsData true - return scope data; false - return scope status
 *
 * @return result
 */
eMBErrorCode eMBRegScopeCB(UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNRegs, BOOL bIsData)
{
	eMBErrorCode eStatus = MB_ENOERR;

	if ((usAddress >= 0) && (usAddress <= S_REG_SCOPE_NREGS))
	{
		if (bIsData) // return scope data
		{
			// set SendFramePointer
			if (usAddress + usNRegs <= S_REG_SCOPE_NREGS)
			{
				SendFramePointer.Count = 3;
				SendFramePointer.Length[0] = 4; // Header
				SendFramePointer.Length[1] = usNRegs * 2; // Data
				SendFramePointer.Length[2] = 2; // CRC

				SendFramePointer.Addr[0] = pucRegBuffer - SendFramePointer.Length[0];
				SendFramePointer.Addr[1] = &usSRegScopeBuf[usAddress];
				SendFramePointer.Addr[2] = SendFramePointer.Addr[0] + SendFramePointer.Length[0];
			}
			else
			{
				SendFramePointer.Count = 4;
				SendFramePointer.Length[0] = 4; // Header
				SendFramePointer.Length[1] = (S_REG_SCOPE_NREGS - usAddress) * 2; // Data1
				SendFramePointer.Length[2] = (usAddress + usNRegs - S_REG_SCOPE_NREGS) * 2; // Data2
				SendFramePointer.Length[3] = 2; // CRC

				SendFramePointer.Addr[0] = pucRegBuffer - SendFramePointer.Length[0];
				SendFramePointer.Addr[1] = &usSRegScopeBuf[usAddress];
				SendFramePointer.Addr[2] = &usSRegScopeBuf[0];
				SendFramePointer.Addr[3] = SendFramePointer.Addr[0] + SendFramePointer.Length[0];
			}
		}
		else // return scope status
		{
			// set SendFramePointer
			SendFramePointer.Count = 2;
			SendFramePointer.Length[0] = 4 + (usNRegs << 1);
			SendFramePointer.Length[1] = 2;

			SendFramePointer.Addr[0] = pucRegBuffer - 4;
			SendFramePointer.Addr[1] = SendFramePointer.Addr[0] + SendFramePointer.Length[0];
		}
	}
	else
	{
		eStatus = MB_ENOREG;
	}

	return eStatus;
}


/**
 * Modbus slave error register callback function.
 *
 * @param pucRegBuffer error register buffer
 *
 * @return result
 */
eMBErrorCode eMBRegErrorCB(UCHAR * pucRegBuffer)
{
	eMBErrorCode eStatus = MB_ENOERR;

	// set SendFramePointer
	SendFramePointer.Count = 1;
	SendFramePointer.Length[0] = 5;
	SendFramePointer.Addr[0] = pucRegBuffer - 1;

	return eStatus;
}

/**
 * Modbus slave coils callback function.
 *
 * @param pucRegBuffer coils buffer
 * @param usAddress coils address
 * @param usNCoils coils number
 * @param eMode read or write
 *
 * @return result
 */
//eMBErrorCode eMBRegCoilsCB(UCHAR * pucRegBuffer, USHORT usAddress,
//        USHORT usNCoils, eMBRegisterMode eMode)
//{
//    eMBErrorCode    eStatus = MB_ENOERR;
//    USHORT          iRegIndex , iRegBitIndex , iNReg;
//    UCHAR *         pucCoilBuf;
//    USHORT          COIL_START;
//    USHORT          COIL_NCOILS;
//    USHORT          usCoilStart;
//    iNReg =  usNCoils / 8 + 1;
//
//    pucCoilBuf = ucSCoilBuf;
//    COIL_START = S_COIL_START;
//    COIL_NCOILS = S_COIL_NCOILS;
//    usCoilStart = usSCoilStart;
//
//    /* it already plus one in modbus function method. */
//    usAddress--;
//
//    if( ( usAddress >= COIL_START ) &&
//        ( usAddress + usNCoils <= COIL_START + COIL_NCOILS ) )
//    {
//        iRegIndex = (USHORT) (usAddress - usCoilStart) / 8;
//        iRegBitIndex = (USHORT) (usAddress - usCoilStart) % 8;
//        switch ( eMode )
//        {
//        /* read current coil values from the protocol stack. */
//        case MB_REG_READ:
//            while (iNReg > 0)
//            {
//                *pucRegBuffer++ = xMBUtilGetBits(&pucCoilBuf[iRegIndex++],
//                        iRegBitIndex, 8);
//                iNReg--;
//            }
//            pucRegBuffer--;
//            /* last coils */
//            usNCoils = usNCoils % 8;
//            /* filling zero to high bit */
//            *pucRegBuffer = *pucRegBuffer << (8 - usNCoils);
//            *pucRegBuffer = *pucRegBuffer >> (8 - usNCoils);
//            break;
//
//            /* write current coil values with new values from the protocol stack. */
//        case MB_REG_WRITE:
//            while (iNReg > 1)
//            {
//                xMBUtilSetBits(&pucCoilBuf[iRegIndex++], iRegBitIndex, 8,
//                        *pucRegBuffer++);
//                iNReg--;
//            }
//            /* last coils */
//            usNCoils = usNCoils % 8;
//            /* xMBUtilSetBits has bug when ucNBits is zero */
//            if (usNCoils != 0)
//            {
//                xMBUtilSetBits(&pucCoilBuf[iRegIndex++], iRegBitIndex, usNCoils,
//                        *pucRegBuffer++);
//            }
//            break;
//        }
//    }
//    else
//    {
//        eStatus = MB_ENOREG;
//    }
//    return eStatus;
//}
//
/**
 * Modbus slave discrete callback function.
 *
 * @param pucRegBuffer discrete buffer
 * @param usAddress discrete address
 * @param usNDiscrete discrete number
 *
 * @return result
 */
//eMBErrorCode eMBRegDiscreteCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNDiscrete )
//{
//    eMBErrorCode    eStatus = MB_ENOERR;
//    USHORT          iRegIndex , iRegBitIndex , iNReg;
//    UCHAR *         pucDiscreteInputBuf;
//    USHORT          DISCRETE_INPUT_START;
//    USHORT          DISCRETE_INPUT_NDISCRETES;
//    USHORT          usDiscreteInputStart;
//    iNReg =  usNDiscrete / 8 + 1;
//
//    pucDiscreteInputBuf = ucSDiscInBuf;
//    DISCRETE_INPUT_START = S_DISCRETE_INPUT_START;
//    DISCRETE_INPUT_NDISCRETES = S_DISCRETE_INPUT_NDISCRETES;
//    usDiscreteInputStart = usSDiscInStart;
//
//    /* it already plus one in modbus function method. */
//    usAddress--;
//
//    if ((usAddress >= DISCRETE_INPUT_START)
//            && (usAddress + usNDiscrete    <= DISCRETE_INPUT_START + DISCRETE_INPUT_NDISCRETES))
//    {
//        iRegIndex = (USHORT) (usAddress - usDiscreteInputStart) / 8;
//        iRegBitIndex = (USHORT) (usAddress - usDiscreteInputStart) % 8;
//
//        while (iNReg > 0)
//        {
//            *pucRegBuffer++ = xMBUtilGetBits(&pucDiscreteInputBuf[iRegIndex++],
//                    iRegBitIndex, 8);
//            iNReg--;
//        }
//        pucRegBuffer--;
//        /* last discrete */
//        usNDiscrete = usNDiscrete % 8;
//        /* filling zero to high bit */
//        *pucRegBuffer = *pucRegBuffer << (8 - usNDiscrete);
//        *pucRegBuffer = *pucRegBuffer >> (8 - usNDiscrete);
//    }
//    else
//    {
//        eStatus = MB_ENOREG;
//    }
//
//    return eStatus;
//}
//
