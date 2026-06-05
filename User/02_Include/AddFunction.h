/*
 * Copyright (c) 2021-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : AddFunction.h
 * Author        : Summer
 * Date          : 2021-11-13
 * Description   : This file defines some basic function.
 *
 * Record        :
 * V1.0, 2021-11-13, Summer: Created file
 */


#ifndef __AddFunction_H_
#define __AddFunction_H_

/******************************************************************************/
/***************************独立看门狗命令************************************/
#define IWDT_KRCHANGE		0x5555	//修改IWDT_KR寄存器的命令
#define IWDT_OPEN			0xCCCC		//开始启用独立看门狗命令
#define IWDT_SHUT			0x2222		//关闭独立看门狗命令
#define IWDT_FEED			0xAAAA			//独立看门狗重载命令
#define IWDT_RELOAD			0x80		//独立看门狗重载值
/******************************************************************************/

#define	SPIDBG_DMA_CR						(DMA4_CR)	// DMA setting register
#define	SPIDBG_DMA_BA						(DMA4_BA)	// DMA data address register
#define	SPIDBG_DMA_LEN						(DMA4_LEN)	// DMA data length register

#define FLASH_ID_ADDR_START					(0xFFE8 & 0xFFFFFFF8)	// ID存储开始地址
#define FLASH_ID_ADDR_SIZE					(8)						// ID的存储空间(byte)


extern uint16 TestVariable_1;
extern uint16 TestVariable_2;
extern uint16 TestVariable_3;
extern uint32 TestVariable_u32_1;
extern uint32 TestVariable_u32_2;
extern uint32 TestVariable_u32_3;

///* Exported functions ---------------------------------------------------------------------------*/

extern void Test_Buff(void);

extern void IWDT_Init(void);
extern void IWDT_Refresh(void);

extern void SPIDebugSet(void);
extern void SignalDebugSet(void);


extern void Motor_Charge(void);
#endif