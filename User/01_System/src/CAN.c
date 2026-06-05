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
	
	/*使能CAN模块*/
	clr_csr(CAN_CR0, CANEN);
	
#if (CANTX_GPIO == PA && CANTX_PIN == PIN0)
	clr_csr(PH_SEL, CANCT);
#else
	set_csr(PH_SEL, CANCT);  	//功能转移，0-->PA0:CTX, PA1:CRX; 1-->PA5:CTX, PA4:CRX
#endif
	
	/*是否开启CANFD*/
	CAN_Init_Setting.CAN_FD		= 1;
	CAN_Init_Setting.CAN_ISO	= 0; // 0-ISO; 1- BOSCH
	CAN_Init_Setting.CAN_CFDPEX = 1;
	//若开启CANFD，需要设置二次滤波及数据域波特率
	
	/*CANFD时间戳相关设置*/
	CAN_Init_Setting.CAN_MailMod		= 0;
	CAN_Init_Setting.CAN_TimeTrigger	= 0;
	CAN_Init_Setting.CAN_TimeSource		= 0;
	CAN_Init_Setting.CAN_TimeFrequency  = 0;
	
	/*CANFD非数据域波特率设置, 48M/(34+11+3)=1M, 采样点:(34+1+1)/[(34+1)+(11+1)+1] = 75%*/
	CAN_Init_Setting.CAN_NData_BRP = bitRate;	//波特率分频系数
	CAN_Init_Setting.CAN_NData_Seg1 = 34;		//SEG1取值范围：0-63
	CAN_Init_Setting.CAN_NData_Seg2 = 11;		//SEG2取值范围：0-31
	CAN_Init_Setting.CAN_NData_RESYN = 6;		//重同步宽度: SJW

	/*CANFD数据域域波特率设置, 48M/(7+2+3)=4M, 采样点:(7+1+1)/[(7+1)+(2+1)+1] = 75%*/
	CAN_Init_Setting.CAN_Data_BRP = 0;			//数据波特率分频系数
	CAN_Init_Setting.CAN_Data_Seg1 = 7;			//SEG1取值范围：0-31
	CAN_Init_Setting.CAN_Data_Seg2 = 2;			//SEG1取值范围：0-15
	CAN_Init_Setting.CAN_Data_RESYN = 1;		//重同步宽度: SJW

	/*CANFD数据域二次采样设置*/ 
	CAN_Init_Setting.CAN_TDCEnable = 1;			//0:不使能 1：使能延时捕获
	CAN_Init_Setting.CAN_TTCM = 1;				//
	CAN_Init_Setting.CAN_TDC_SEL = 0;			//0:软件配置+自动捕获 1：软件配置
	CAN_Init_Setting.CAN_SSPDIS = 0;			//0:二次采样使能 1：二次采样不使能
	CAN_Init_Setting.CAN_TDC_SSPoffset = 6;

	/*CANFD中断使能设置*/
	CAN_Init_Setting.CAN_ERR_Enable = RXIE | TXIE; // ETYIE | BOFIE | PERIE | ERWIE | OVLIE | ABLIE | ERRIE | SLPIE | WKUIE | OVIE | RXIE | TXIE;	//

	/*监听自测开关*/
	clr_csr(CAN_CR0, SELFTST);
	clr_csr(CAN_CR0, LISTEN);
	
	/*在复位模式下，CAN控制器处于复位状态，不可以接收或发送报文。对CAN_CR0[RSTMOD]清‘0’以进入复位模式*/
//	clr_csr(CAN_CR0, RSTMOD);

	/*CAN滤波及屏蔽设置*/
	CAN_Filter();

	/*CAN设置及使能*/
	CAN_Init(&CAN_Init_Setting);
	
	memset(&CAN_RX0ID, 0, 18 * 4);
	memset(&CAN_RX1ID, 0, 18 * 4);
	memset(&CAN_RX2ID, 0, 18 * 4);
	
	/*当检测到总线活动后，硬件自动对CAN_CR1[SLEEP]清‘0’来唤醒CAN*/
	clr_csr(CAN_CR0, AWU); // 0:不使能自动唤醒模式
//	set_csr(CAN_CR0, SELFTST);
	/*CR1寄存器只在CAN使能后才能设置*/
	
	clr_csr(CAN_CR1, NOART); // 1:禁止自动重传
	
	write_csr(IP30, CAN_INT_PRI);		// 中断优先级别
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
	/*寄存器清0，避免误操作*/
	write_csr(CAN_NBTR, 0);
	write_csr(CAN_DBTR, 0);
	write_csr(CAN_TDCR, 0);
	write_csr(CAN_CR0 , 0);
	write_csr(CAN_IER , 0);
	
	/*波特率及二次滤波设置*/
	write_csr(CAN_NBTR, (uint32)CAN_Setting->CAN_NData_Seg2 << 24 | (uint32)CAN_Setting->CAN_NData_Seg1 << 16 |
		(uint32)CAN_Setting->CAN_NData_BRP | (uint32)CAN_Setting->CAN_NData_RESYN << 11);
	write_csr(CAN_DBTR, (uint32)CAN_Setting->CAN_Data_Seg2 << 24 | (uint32)CAN_Setting->CAN_Data_Seg1 << 16 | 
		(uint32)CAN_Setting->CAN_Data_BRP | (uint32)CAN_Setting->CAN_Data_RESYN << 11);
	write_csr(CAN_TDCR, (uint32)CAN_Setting->CAN_TDC_SSPoffset);

	/*CAN 错误开关设置*/
	write_csr(CAN_IER  , (uint32)CAN_Setting->CAN_ERR_Enable);
	
	/*CANFD及相关功能设置设置*/
	write_csr(CAN_CR0  , (uint32)CAN_Setting->CAN_TDC_SEL << 12 | (uint32)CAN_Setting->CAN_SSPDIS << 13 | (uint32)CAN_Setting->CAN_TDCEnable << 11 | (uint32)CAN_Setting->CAN_FD << 8 | (uint32)CAN_Setting->CAN_ISO << 9 | (uint32)CAN_Setting->CAN_CFDPEX << 10);
	
	/*使能CAN模块*/
	set_csr(CAN_CR0, CANEN);
	/*邮箱及时间戳设置*/
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

/**********************************过滤模式*********************************/
/*****变量说明：FIL_SIN：0：双过滤器模式			1：单过滤器模式*****************/
/*****变量说明：ID_MOD ：0：过滤标准帧				1：过滤扩展帧*******************/
#define     FIL_SIN    1
#define     ID_MOD     0

	IDE_FIL=0;																						//选择过滤模式：1：过滤扩展帧 0：过滤标准帧

#if FIL_SIN																							//单过滤模式
	set_csr(CAN_CR0, FILMOD);
	#if ID_MOD																							//过滤扩展帧
		
		EXTID1=0x1FFFFFFF;																				//0-0x1FFF
		CAN_IDE=1;																						//过滤扩展帧
		CAN_RTR=1;																						//过滤远程帧
		
		write_csr(CAN_ACR , ((((EXTID1 << 1)&0xFF)<<24)|(((EXTID1 >> 7 )&0xFF)<<16)|((((EXTID1 >> 18)&0xE0)| (CAN_IDE<<3) | (CAN_RTR<<4) | ((EXTID1 >> 15) & 0x07))<<8)| (EXTID1 >> 21)));
		write_csr(CAN_AMR , (((0xFF)<<24)|((0xFF)<<16)|((0xFF)<<8)|(0xFF)));
		
	#else																										//过滤标准帧

		STDID1 =0x7FF;																				//0-0x7FF
		CAN_IDE = 1;																					//过滤扩展帧
		CAN_RTR = 0;																					//过滤远程帧
		Data0   = 0xFF;  								//过滤字节0内容											//过滤第一字节
		Data1   = 0xFF;									//过滤字节1内容											//过滤第二字节
		write_csr(CAN_ACR ,((Data1<<24)|(Data0<<16)|(((((STDID1 << 5) & 0xE0)| (CAN_IDE<<3) | (CAN_RTR<<4)))<<8)| (STDID1 >> 3)) );
		write_csr(CAN_AMR , (((0xFF)<<24)|((0xFF)<<16)|((0xFF)<<8) | (0xFF)) );

	#endif

#else																							//双过滤模式
		clr_csr(CAN_CR0, FILMOD);
	#if ID_MOD																							//过滤扩展帧
		
		EXTID1=0x1FFFFFFF;																		//0-0x1FFF8000，只可更改EXTID1[15]-[28]
		EXTID2=0x1FFFFFFF;																		//0-0x1FFF8000，只可更改EXTID1[15]-[28]
		CAN_IDE=1;																						//过滤扩展帧
		CAN_RTR=1;																						//过滤远程帧
				
		write_csr(CAN_ACR , ((((EXTID2 >> 18)&0xE0)| (CAN_IDE<<3) | (CAN_RTR<<4) | ((EXTID2 >> 15) & 0x07)<<24)|(( EXTID2 >> 21)<<16)|((((EXTID1 >> 18)&0xE0)| (CAN_IDE<<3) | (CAN_RTR<<4) | ((EXTID2 >> 15) & 0x07))<<8)| (EXTID1 >> 21)));
		write_csr(CAN_AMR , (((0xFF)<<24)|((0xFF)<<16)|((0xFF)<<8)|(0xFF)));

	#else																										//过滤标准帧

		STDID1 = 0x7FF;																				//0-0x7FF
		STDID2 = 0x7FF;																				//0-0x7FF
		CAN_IDE = 1;																					//过滤扩展帧
		CAN_RTR = 1;																					//过滤远程帧

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
	uint16 tryCounter = 0; // 查询计数
	
	/* 选择一个空的发送邮箱 */
	/* 逐个检查发送邮箱是否为空，为空则记录邮箱号，否则检查下一个；
	如果所有邮箱都非空，则给邮箱号赋值CAN_TxStatus_NoMailBox，表示没有非空邮箱 */
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
		
		if (tryCounter++ >= 500) // 没有空邮箱
		{
			return transmit_mailbox;
		}
	}

	/*如果存在空邮箱，开始设置发送消息结构体*/
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
			
			set_csr(CAN_CR1, RFD); // 释放接收缓冲区
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
