/*
 * Copyright (c) 2022-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : DMA.h
 * Author        : Fortior Application Team
 * Date          : 2022-09-21
 * Description   : define DMA
 *
 * Record        :
 * V1.0, 2022-09-21, Fortior Application Team: Created file
 */


#ifndef __DMA_H__
#define __DMA_H__

/*************************************************************************************/
#define Wait_DMA0       while (readbit_csr(DMA0_CR, DMABSY))
#define Wait_DMA1       while (readbit_csr(DMA1_CR, DMABSY))

#define DMA_MAXLEN		(64)


//#define DMA_Uart2_Read		DMACFG2 | DMACFG1
//#define DMA_Uart2_Send		DMACFG2 | DMACFG1 | DMACFG0
//#define DMA_SF_Read			DMACFG4 | DMACFG3 | DMACFG1 | DMACFG0
//#define DMA_SPI1_Read		DMACFG2
//#define DMA_SPI1_Send		DMACFG2 | DMACFG0
//#define DMA_CRC_Send		DMACFG4 | DMACFG3 |	0	 |	  0	   | DMACFG0
//#define DMA_MON_Send		DMACFG4 | DMACFG3 |	0	 | DMACFG1 | DMACFG0


#define DMA_Uart1_Read		( 0		|	  0	   |	0    |	  0	   |	0	)
#define DMA_Uart1_Send		( 0		|	  0	   |	0	 |	  0	   | DMACFG0 )
#define DMA_Uart2_Read		( 0		|	  0	   |	0	 | DMACFG1 |	0	)
#define DMA_Uart2_Send		( 0		|	  0	   |	0	 | DMACFG1 | DMACFG0)
#define DMA_SF_Read			( 0		|	  0	   | DMACFG2 |	  0	   |	0	)
#define DMA_SF_Send			( 0		|	  0	   | DMACFG2 |	  0	   | DMACFG0)
#define DMA_SPI1_Read		( 0		|	  0	   | DMACFG2 | DMACFG1 |	0	)
#define DMA_SPI1_Send		( 0		|	  0	   | DMACFG2 | DMACFG1 | DMACFG0)
#define DMA_SPI2_Read		( 0		| DMACFG3 |	0	 |	  0	   |	0	)
#define DMA_SPI2_Send		( 0		| DMACFG3 |	0	 |	  0	   | DMACFG0)
#define DMA_I2C1_Read		( 0		| DMACFG3 |	0	 | DMACFG1 |	0	)
#define DMA_I2C1_Send		( 0		| DMACFG3 |	0	 | DMACFG1 | DMACFG0)
#define DMA_I2C2_Read		( 0		| DMACFG3 | DMACFG2 |    0    |	0	)
#define DMA_I2C2_Send		( 0		| DMACFG3 | DMACFG2 |    0    | DMACFG0)
#define DMA_LIN_Read		( 0		| DMACFG3 | DMACFG2 | DMACFG1 |	0	)
#define DMA_LIN_Send		( 0		| DMACFG3 | DMACFG2 | DMACFG1 | DMACFG0)
#define DMA_T2DR_Read		( DMACFG4 |	  0	   |	0    |	  0	   |	0	)
#define DMA_T2DR_Send		( DMACFG4 |	  0	   |	0	 |	  0    | DMACFG0)
#define DMA_T2ARR_Read		( DMACFG4 |	  0	   |    0	 | DMACFG1 |	0	)
#define DMA_T2ARR_Send		( DMACFG4 |	  0    |    0	 | DMACFG1 | DMACFG0)
#define DMA_T5DR_Read		( DMACFG4 |	  0	   | DMACFG2 |	  0	   |	0	)
#define DMA_T5DR_Send		( DMACFG4 |    0    | DMACFG2 |    0	   | DMACFG0)
#define DMA_T5ARR_Read		( DMACFG4 |    0    | DMACFG2 | DMACFG1 |	0	)
#define DMA_T5ARR_Send		( DMACFG4 |    0    | DMACFG2 | DMACFG1 | DMACFG0)
#define DMA_CRC_Read		( DMACFG4 | DMACFG3 |	0	 |	  0	   |	0	)
#define DMA_CRC_Send		( DMACFG4 | DMACFG3 |	0	 |	  0	   | DMACFG0)
#define DMA_MON_Send		( DMACFG4 | DMACFG3 |	0	 | DMACFG1 | DMACFG0)
//
typedef enum
{
    DMA_IRQ_L0 = 0,
    DMA_IRQ_L1 = 0x40,
    DMA_IRQ_L2 = 0x80,
    DMA_IRQ_L3 = 0xc0
}eType_DMA_IRQ;



/******************************************************************************///Function Subject
extern void SetPipe_DMA0(uint16 ePipe);
extern void SetPipe_DMA1(uint16 ePipe);
extern void SetDataPackage_DMA0(unsigned char* ulAddr, char cLen);
extern void SetDataPackage_DMA1(unsigned char* ulAddr, char cLen);
extern void SetIRQ_DMA0(bool eIRQ);
extern void SetIRQ_DMA1(bool eIRQ);
extern void Switch_DMA0(void);
extern void Switch_DMA1(void);
extern void Close_DMA0(void);
extern void Reset_DMA0(void);
extern void Set_DBG_DMA(void);

#endif