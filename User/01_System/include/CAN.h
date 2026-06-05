/*
 * Copyright (c) 2022-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : CAN.h
 * Author        : Fortior Application Team
 * Date          : 2022-09-21
 * Description   : define CAN
 *
 * Record        :
 * V1.0, 2022-09-21, Fortior Application Team: Created file
 */

//Header File
#ifndef __CAN_H__
#define __CAN_H__
#include "fu7502.h"
/* 
               RXD|--------|RXD                 |CANH--------|CANH                  RXD|--------|RXD
CAN controler     |        |    CAN transcevier |            |      CAN transcevier    |        |     FUXXXX CAN controler
               TXD|--------|TXD                 |CANL--------|CANL                  TXD|--------|TXD
*/


/* IDEs */
#define IDE_STD					(0)   // 标准格式(11位)
#define IDE_EXT                 (IDE) // 扩展格式(29位)

/* RTRs */
#define RTR_DAT					(0)   // 数据帧
#define RTR_RMT					(RTR) // 远程帧(节点守护)

/* FDF */
#define FDF_CAN					(0)   // 常规帧(标准帧或扩展帧）
#define FDF_CANFD               (FDF) // CANFD 帧

/* BRS */
#define BRS_Disable				(0)   // 不转换速率
#define BRS_Enable				(BRS) // 转换可变速率

/* DLCs */
#define DLC_0                   (0)
#define DLC_1                   (1)
#define DLC_2                   (2)
#define DLC_3                   (3)
#define DLC_4                   (4)
#define DLC_5                   (5)
#define DLC_6                   (6)
#define DLC_7                   (7)
#define DLC_8                   (8)
#define DLC_12                  (9)
#define DLC_16                  (10)
#define DLC_20                  (11)
#define DLC_24                  (12)
#define DLC_32                  (13)
#define DLC_48                  (14)
#define DLC_64                  (15)

typedef struct {
	uint8	CAN_CFDPEX;		//FD模式下是否接收正常CAN报文
	uint8	CAN_ISO;		//是否开启ISO
	uint8	CAN_FD;			//CANFD模式使能

	/*CANFD非数据域波特率设置*/
	uint16	CAN_NData_BRP;
	uint8	CAN_NData_Seg1;
	uint8	CAN_NData_Seg2;
	uint8	CAN_NData_RESYN;
	
	/*CANFD数据域波特率设置*/
	uint16	CAN_Data_BRP;
	uint8	CAN_Data_Seg1;
	uint8	CAN_Data_Seg2;
	uint8	CAN_Data_RESYN;
	
	/*CANFD数据域二次采样设置*/
	uint8 CAN_TDCEnable;
	uint8 CAN_TTCM;
	uint8 CAN_TDC_SEL;
	uint8 CAN_SSPDIS;
	uint8 CAN_TDC_SSPoffset;
	
	/*CANFD邮箱及时间戳设置*/
	uint8	CAN_MailMod;
	uint8	CAN_TimeTrigger;
	uint8	CAN_TimeSource;
	uint8	CAN_TimeFrequency;
	
	uint16	CAN_ERR_Enable;
} CANStruct;

typedef struct {
	uint32 ident;  /*!< Standard identifier */
	uint8 dlc;     /*!< Data length */
	uint8 length;     /*!< Data actual length */
	uint16 frame;  /*!< Frame */ // IDE | RTR | FDF | BRS | ESI
} CAN_TxRxHeaderTypeDef;


extern void CAN_Setting(uint16 bitRate);
extern void CAN_Init(CANStruct* CAN_Setting);
extern void CAN_Filter(void);
extern void CAN_Receive(CAN_TxRxHeaderTypeDef* RxHeader, uint8* RxData);
extern uint8 CAN_Send(CAN_TxRxHeaderTypeDef* TxHeader, uint8* TxData);
extern void CAN_Enable();
extern void CAN_Disable();

#endif