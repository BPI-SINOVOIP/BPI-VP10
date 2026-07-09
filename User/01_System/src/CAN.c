/*
 * Copyright (c) 2022-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : CAN.c
 * Author        : Fortior Application Team
 * Date          : 2022-09-21
 * Description   : define CAN
 *
 * Record        :
 * V1.0, 2022-09-21, Fortior Application Team: Created file
 */

//Header File
#include "fu7502.h"
#include "can.h"
#include <Myproject.h>


const uint8 CanDLCTable[7] = {12, 16, 20, 24, 32, 48, 64};


void CAN_Setting(uint16 bitRate)
{
	CANStruct CAN_Init_Setting;
	
	/*Enable CAN module*/
	clr_csr(CAN_CR0, CANEN);
	
#if (CANTX_GPIO == PA && CANTX_PIN == PIN0)
	clr_csr(PH_SEL, CANCT);
#else
	set_csr(PH_SEL, CANCT);  	//Function remap: 0-->PA0:CTX, PA1:CRX; 1-->PA5:CTX, PA4:CRX
#endif
	
	/*Whether to enable CANFD*/
	CAN_Init_Setting.CAN_FD		= 1;
	CAN_Init_Setting.CAN_ISO	= 0; // 0-ISO; 1- BOSCH
	CAN_Init_Setting.CAN_CFDPEX = 1;
	//If CANFD is enabled, secondary filtering and data phase baud rate must be set
	
	/*CANFD timestamp related settings*/
	CAN_Init_Setting.CAN_MailMod		= 0;
	CAN_Init_Setting.CAN_TimeTrigger	= 0;
	CAN_Init_Setting.CAN_TimeSource		= 0;
	CAN_Init_Setting.CAN_TimeFrequency  = 0;
	
	/*CANFD nominal baud rate: 48M/(34+11+3)=1M, sample point: (34+1+1)/[(34+1)+(11+1)+1] = 75%*/
	CAN_Init_Setting.CAN_NData_BRP = bitRate;	//Baud rate divider
	CAN_Init_Setting.CAN_NData_Seg1 = 34;		//SEG1valid range: 0-63
	CAN_Init_Setting.CAN_NData_Seg2 = 11;		//SEG2valid range: 0-31
	CAN_Init_Setting.CAN_NData_RESYN = 6;		//Resynchronization width: SJW

	/*CANFD data phase baud rate: 48M/(7+2+3)=4M, sample point: (7+1+1)/[(7+1)+(2+1)+1] = 75%*/
	CAN_Init_Setting.CAN_Data_BRP = 0;			//dataBaud rate divider
	CAN_Init_Setting.CAN_Data_Seg1 = 7;			//SEG1valid range: 0-31
	CAN_Init_Setting.CAN_Data_Seg2 = 2;			//SEG1valid range: 0-15
	CAN_Init_Setting.CAN_Data_RESYN = 1;		//Resynchronization width: SJW

	/*CANFD data phase secondary sampling settings*/ 
	CAN_Init_Setting.CAN_TDCEnable = 1;			//0:Disable 1: Enable delay capture
	CAN_Init_Setting.CAN_TTCM = 1;				//
	CAN_Init_Setting.CAN_TDC_SEL = 0;			//0:software config+auto capture 1: software config
	CAN_Init_Setting.CAN_SSPDIS = 0;			//0:Secondary sampling enable 1: secondary sampling Disable
	CAN_Init_Setting.CAN_TDC_SSPoffset = 6;

	/*CANFD interrupt enable settings*/
	CAN_Init_Setting.CAN_ERR_Enable = RXIE | TXIE; // ETYIE | BOFIE | PERIE | ERWIE | OVLIE | ABLIE | ERRIE | SLPIE | WKUIE | OVIE | RXIE | TXIE;	//

	/*Listen/self-test switches*/
	clr_csr(CAN_CR0, SELFTST);
	clr_csr(CAN_CR0, LISTEN);
	
	/*In reset mode, CANcontroller in reset state, cannot receive or send messages.toCAN_CR0[RSTMOD]clear‘0’to enter reset mode*/
//	clr_csr(CAN_CR0, RSTMOD);

	/*CAN filter and mask settings*/
	CAN_Filter();

	/*CAN setup and enable*/
	CAN_Init(&CAN_Init_Setting);
	
	memset(&CAN_RX0ID, 0, 18 * 4);
	memset(&CAN_RX1ID, 0, 18 * 4);
	memset(&CAN_RX2ID, 0, 18 * 4);
	
	/*When bus activity is detected, hardware auto-CAN_CR1[SLEEP]clear‘0’to wake upCAN*/
	clr_csr(CAN_CR0, AWU); // 0:Disable auto wakeup mode
//	set_csr(CAN_CR0, SELFTST);
	/*CR1 register can only be set after CAN is enabled*/
	
	clr_csr(CAN_CR1, NOART); // 1:Disable auto-retransmit
	
	write_csr(IP30, CAN_INT_PRI);		// Interrupt priority level
}

void CAN_Enable()
{
	set_csr(CAN_CR0, CANEN);
}


void CAN_Disable()
{
	clr_csr(CAN_CR0, CANEN);
}

void CAN_Init(CANStruct* CAN_Setting)
{
	/*Clear registers to 0 to avoid misoperation*/
	write_csr(CAN_NBTR, 0);
	write_csr(CAN_DBTR, 0);
	write_csr(CAN_TDCR, 0);
	write_csr(CAN_CR0 , 0);
	write_csr(CAN_IER , 0);
	
	/*Baud rate and secondary filtering settings*/
	write_csr(CAN_NBTR, (uint32)CAN_Setting->CAN_NData_Seg2 << 24 | (uint32)CAN_Setting->CAN_NData_Seg1 << 16 |
		(uint32)CAN_Setting->CAN_NData_BRP | (uint32)CAN_Setting->CAN_NData_RESYN << 11);
	write_csr(CAN_DBTR, (uint32)CAN_Setting->CAN_Data_Seg2 << 24 | (uint32)CAN_Setting->CAN_Data_Seg1 << 16 | 
		(uint32)CAN_Setting->CAN_Data_BRP | (uint32)CAN_Setting->CAN_Data_RESYN << 11);
	write_csr(CAN_TDCR, (uint32)CAN_Setting->CAN_TDC_SSPoffset);

	/*CAN error switch settings*/
	write_csr(CAN_IER  , (uint32)CAN_Setting->CAN_ERR_Enable);
	
	/*CANFD and related function settings*/
	write_csr(CAN_CR0  , (uint32)CAN_Setting->CAN_TDC_SEL << 12 | (uint32)CAN_Setting->CAN_SSPDIS << 13 | (uint32)CAN_Setting->CAN_TDCEnable << 11 | (uint32)CAN_Setting->CAN_FD << 8 | (uint32)CAN_Setting->CAN_ISO << 9 | (uint32)CAN_Setting->CAN_CFDPEX << 10);
	
	/*Enable CAN module*/
	set_csr(CAN_CR0, CANEN);
	/*Mailbox and timestamp settings*/
	set_csr(CAN_CR1, (uint32)CAN_Setting->CAN_TTCM << 14 | (uint32)CAN_Setting->CAN_MailMod << 7 | (uint32)CAN_Setting->CAN_TimeTrigger << 8 | (uint32)CAN_Setting->CAN_TimeSource << 9 | (uint32)CAN_Setting->CAN_TimeFrequency << 10);

}


void CAN_Filter(void)
{
	uint8   IDE_FIL;
	uint8   CAN_IDE;
	uint8   CAN_RTR;
	uint32  EXTID1;
	uint32  EXTID2;
	uint32  STDID1;
	uint32  STDID2;
	uint8   Data0;
	uint8   Data1;

/**********************************Filter mode*********************************/
/*****Variable: FIL_SIN: 0: dual filter mode, 1: single filter mode*****************/
/*****Variable: ID_MOD: 0: filter standard frames, 1: filter extended frames*******************/
#define     FIL_SIN    1
#define     ID_MOD     0

	IDE_FIL=0;																						//selectFilter mode: 1: Filter extended frames, 0: Filter standard frames

#if FIL_SIN																							//Single Filter mode
	set_csr(CAN_CR0, FILMOD);
	#if ID_MOD																							//Filter extended frames
		
		EXTID1=0x1FFFFFFF;																				//0-0x1FFF
		CAN_IDE=1;																						//Filter extended frames
		CAN_RTR=1;																						//Filter remote frames
		
		write_csr(CAN_ACR , ((((EXTID1 << 1)&0xFF)<<24)|(((EXTID1 >> 7 )&0xFF)<<16)|((((EXTID1 >> 18)&0xE0)| (CAN_IDE<<3) | (CAN_RTR<<4) | ((EXTID1 >> 15) & 0x07))<<8)| (EXTID1 >> 21)));
		write_csr(CAN_AMR , (((0xFF)<<24)|((0xFF)<<16)|((0xFF)<<8)|(0xFF)));
		
	#else																										//Filter standard frames

		STDID1 =0x7FF;																				//0-0x7FF
		CAN_IDE = 1;																					//Filter extended frames
		CAN_RTR = 0;																					//Filter remote frames
		Data0   = 0xFF;  								//Filter byte 0 content											//Filter first byte
		Data1   = 0xFF;									//Filter byte 1 content											//Filter second byte
		write_csr(CAN_ACR ,((Data1<<24)|(Data0<<16)|(((((STDID1 << 5) & 0xE0)| (CAN_IDE<<3) | (CAN_RTR<<4)))<<8)| (STDID1 >> 3)) );
		write_csr(CAN_AMR , (((0xFF)<<24)|((0xFF)<<16)|((0xFF)<<8) | (0xFF)) );

	#endif

#else																							//Dual Filter mode
		clr_csr(CAN_CR0, FILMOD);
	#if ID_MOD																							//Filter extended frames
		
		EXTID1=0x1FFFFFFF;																		//0-0x1FFF8000, only EXTID1[15]-[28] can be changed
		EXTID2=0x1FFFFFFF;																		//0-0x1FFF8000, only EXTID1[15]-[28] can be changed
		CAN_IDE=1;																						//Filter extended frames
		CAN_RTR=1;																						//Filter remote frames
				
		write_csr(CAN_ACR , ((((EXTID2 >> 18)&0xE0)| (CAN_IDE<<3) | (CAN_RTR<<4) | ((EXTID2 >> 15) & 0x07)<<24)|(( EXTID2 >> 21)<<16)|((((EXTID1 >> 18)&0xE0)| (CAN_IDE<<3) | (CAN_RTR<<4) | ((EXTID2 >> 15) & 0x07))<<8)| (EXTID1 >> 21)));
		write_csr(CAN_AMR , (((0xFF)<<24)|((0xFF)<<16)|((0xFF)<<8)|(0xFF)));

	#else																										//Filter standard frames

		STDID1 = 0x7FF;																				//0-0x7FF
		STDID2 = 0x7FF;																				//0-0x7FF
		CAN_IDE = 1;																					//Filter extended frames
		CAN_RTR = 1;																					//Filter remote frames

		write_csr(CAN_ACR , 0x00000000);
		write_csr(CAN_AMR , (((0xFF)<<24)|((0xFF)<<16)|((0xFF)<<8)|(0xFF)));

	#endif
#endif
}

uint8 GetCanLength(CAN_TxRxHeaderTypeDef* TxHeader)
{
	uint8 length = 0;
	if (TxHeader->dlc <= 8)
	{
		length = TxHeader->dlc;
	}
	else
	{
		if ((TxHeader->frame & FDF) == FDF_CANFD)
		{
			length = CanDLCTable[TxHeader->dlc - 9];
		}
		else
		{
			length = 8;
		}
	}
	return length;
}

uint8 GetCanDLC(CAN_TxRxHeaderTypeDef* TxHeader)
{
	uint8 dlc = 0, i;
	if (TxHeader->length <= 8)
	{
		dlc = TxHeader->length;
	}
	else
	{
		if ((TxHeader->frame & FDF) == FDF_CANFD)
		{
			for (i = 0; i < 7; i++)
			{
				if (TxHeader->length <= CanDLCTable[i])
				{
					dlc = i + 9;
					break;
				}
			}
		}
		else
		{
			dlc = 8;
		}
	}
	return dlc;
}

uint8 CAN_Send(CAN_TxRxHeaderTypeDef* TxHeader, uint8* TxData)
{
	uint8 transmit_mailbox = 255;
	uint16 tryCounter = 0; // Query counter
	
	/* Select an empty transmit mailbox */
	/* Check each transmit mailbox; if empty, record the mailbox number, otherwise check the next one;
	if all mailboxes are non-empty, assign CAN_TxStatus_NoMailBox, indicating no empty mailbox */
	while (1)
	{
		if (read_csr(CAN_TMSTA) & (ME0 | ME1 | ME2))
		{
			if (readbit_csr(CAN_TMSTA, ME0))
			{
				transmit_mailbox = 0;
			}
			else if (readbit_csr(CAN_TMSTA, ME1))
			{
				transmit_mailbox = 1;
			}
			else if (readbit_csr(CAN_TMSTA, ME2))
			{
				transmit_mailbox = 2;
			}
			break;
		}
		
		if (tryCounter++ >= 500) // No empty mailbox
		{
			return transmit_mailbox;
		}
	}

	/*If an empty mailbox exists, start setting the transmit message struct*/
	uint32 canid = (TxHeader->frame & IDE) == 0 ? (TxHeader->ident << 21) : (TxHeader->ident << 3);
	TxHeader->dlc = GetCanDLC(TxHeader);
	switch (transmit_mailbox)
	{
		case 0x00:
			write_csr(CAN_TMDT0, TxHeader->frame | TxHeader->dlc);
			write_csr(CAN_TMID0, canid);
			memcpy(&CAN_TX0DA0, TxData, TxHeader->length);
			set_csr(CAN_TMID0, TREQ);	
			break;
			
		case 0x01:
			write_csr(CAN_TMDT1, TxHeader->frame | TxHeader->dlc);
			write_csr(CAN_TMID1, canid);
			memcpy(&CAN_TX1DA0, TxData, TxHeader->length);
			set_csr(CAN_TMID1, TREQ);
			break;
			
		case 0x02:
			write_csr(CAN_TMDT2, TxHeader->frame | TxHeader->dlc);
			write_csr(CAN_TMID2, canid);
			memcpy(&CAN_TX2DA0, TxData, TxHeader->length);
			set_csr(CAN_TMID2, TREQ);
			break;
			
		default:
			break;
	}
	
	return transmit_mailbox;
}


void CAN_Receive(CAN_TxRxHeaderTypeDef* RxHeader, uint8* RxData)
{
	uint32 rdptr = read_csr(CAN_TSPT) & (RDPTR1 | RDPTR0);
	uint32 canid = 0;

	switch (rdptr)
	{
		case (0) :
			RxHeader->dlc = (uint8)CAN_RX0TD & 0x0F;
			RxHeader->frame = (uint16)(CAN_RX0TD & 0xFFF0);
			canid = CAN_RX0ID;
			RxHeader->length = GetCanLength(RxHeader);
			memcpy(RxData, &CAN_RX0DA0, RxHeader->length);
			
			set_csr(CAN_CR1, RFD); // Release receive buffer
			break;

		case (RDPTR0):
			RxHeader->dlc = (uint8)CAN_RX1TD & 0x0F;
			RxHeader->frame = (uint16)(CAN_RX1TD & 0xFFF0);
			canid = CAN_RX1ID;
			RxHeader->length = GetCanLength(RxHeader);
			memcpy(RxData, &CAN_RX1DA0, RxHeader->length);
			
			set_csr(CAN_CR1, RFD);
			break;
			
		case (RDPTR1):
			RxHeader->dlc = (uint8)CAN_RX2TD & 0x0F;
			RxHeader->frame = (uint16)(CAN_RX2TD & 0xFFF0);
			canid = CAN_RX2ID;
			RxHeader->length = GetCanLength(RxHeader);
			memcpy(RxData, &CAN_RX2DA0, RxHeader->length);
			
			set_csr(CAN_CR1, RFD);
			break;
			
		default:
			break;
	}
	
	RxHeader->ident = (RxHeader->frame & IDE) == IDE_EXT ? canid >> 3 : canid >> 21;
}
