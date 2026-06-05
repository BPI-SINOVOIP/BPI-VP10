/*
 * Copyright (c) 2022-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : Encoder.h
 * Author        : Summer
 * Date          : 2022-09-21
 * Description   : Encoder decoding function header file.
 *
 * Record        :
 * V1.0, 2022-09-21, Summer: Created file
 */

#ifndef __ENCODER_H__
#define __ENCODER_H__

#include "fu7502.h"
#include "Parameter.h"

/*==================================================================================================*/
/***************************************        MACRO         ***************************************/
/*==================================================================================================*/
/* ------ Encoder Type ------ */
#define ENCODER_SEL_NOMODE              (-1)        // Not Valid
#define ENCODER_SEL_ABZ					(0)			// ABZ Incremental Encoder
#define ENCODER_SEL_ABZ_HALL			(1)			// ABZ Incremental Encoder + Hall
#define ENCODER_SEL_TMG_ABS_SIN			(2)			// TMG Absolute Encoder: SingleTurn
#define ENCODER_SEL_TMG_ABS_MUL			(3)			// TMG Absolute Encoder: MultiTurn
#define ENCODER_SEL_TMG_INC				(4)			// TMG Incremental Encoder
#define ENCODER_SEL_BISS				(5)			// BISS Encoder
#define ENCODER_SEL_HALLS_ONLY			(6)			// Hall Encoder
#define ENCODER2_SEL_ABZ				(7)			// ABZ Incremental Encoder2
#define ENCODER2_SEL_ABZ_HALL			(8)			// ABZ Incremental Encoder2 + Hall
#define ENCODER_SEL_ABS_CUSTOM1			(9)			// Custom Abs encoder, such as SPI Encoder KTH7111
#define ENCODER_SEL_ABS_CUSTOM2			(10)		// Custom encoder, such as SPI Encoder MT6835



// Definition of register ENCCALSTATUS
#define	ENCSEL_MOTOR					( 0 )			// 电机侧编码器
#define	ENCSEL_LOAD						( 1 )			// 输出侧编码器


/* ------ TMG ENCODER ------ */
#if ENCODER_SEL_TMG_ENABLED > 0
/* Hardware - DMA definition */
#define	REG_DMA_CR						(DMA1_CR)	// DMA setting register
#define	REG_DMA_BA						(DMA1_BA)	// DMA data address register

/* Request Data ID code */
#define	ID_0							(0x00<<3)	// Read ABS (Absolute data in one revolution)
#define	ID_1							(0x01<<3)	// Read ABM (Multi-turn data)
#define	ID_2							(0x02<<3)	// Read ENID (EncoderID, fixed,  e.g. 17H == 23bit resolution in one revolution)
#define	ID_3							(0x03<<3)	// Read ABS + ENID + ABM + ALMC (Encoder Err)
#define	ID_6							(0x06<<3)	// Writing to EEPROM
#define	ID_D							(0x0D<<3)	// Readout from EEPROM
#define	ID_7							(0x07<<3)	// Reset of all error
#define	ID_8							(0x08<<3)	// Reset of one revolution data
#define	ID_C							(0x0C<<3)	// Reset of multi-turn data and all error

/* Encoder Err code */
#define	FAULT_ENC_OS					(0x0001)			// 0 编码器故障 -	    Over Speed (OS)
#define	FAULT_ENC_FS					(0x0002)			// 1 编码器故障 -       Full Absolute Status (FS)
#define	FAULT_ENC_CE					(0x0004)			// 2 编码器故障 - (ea0) Counting Error (CE)
#define	FAULT_ENC_OF					(0x0008)			// 3 编码器故障 -       Counter Overflow (OF)
#define	FAULT_ENC_OH					(0x0010)			// 4 编码器故障 - (ea1) Overheat (OH)
#define	FAULT_ENC_ME					(0x0020)			// 5 编码器故障 - (ea1) Multiturn Error (ME)
#define	FAULT_ENC_BE					(0x0040)			// 6 编码器故障 - (ea1) Battery Error (BE)
#define	FAULT_ENC_BA					(0x0080)			// 7 编码器故障 - (ea1) Battery Alarm (BA)

#define	FAULT_ENC_PARERR				(0x0100)			// 8 编码器故障 - (ca0) Parity error in Request frame
#define	FAULT_ENC_DELERR				(0x0200)			// 9 编码器故障 - (ca1) Delimiter error in Request frame

#define	FAULT_REG_CRCERR				(0x0400)			// 10 通讯故障  - CRC校验错误
#define	FAULT_REG_SYNERR				(0x0800)			// 11 通讯故障  - 帧同步错误 (如未检查到控制字(CF)的(Sink Code))
#define	FAULT_REG_REQERR				(0x1000)			// 12 通讯故障  - 请求命令错误 (发送和返回的ID不一样)
#define	FAULT_REG_ROTERR				(0x2000)			// 13 通讯故障  - 请求超时错误 (发送请求指令后无返回)
#define	FAULT_REG_INTERR				(0x4000)			// 14 编码器内部故障 - (ea1)

#define TMG_OVER_NOCOMERR				(SF_SUC + SF_DONE)		// transmit finish and no com error in TAAWA_SR
#define TMG_ERRMASK						(0x3C00)		// Error Mask of TAAWA_SR in mcEncoder.ErrCode
#define TMG_ERRSHIFT					(0x0A)			// Error shift in mcEncoder.ErrCode

#endif


/* ------ BISS ENCODER ------ */
#define	FAULT_ENC_OT					(0x0001)			// 0 编码器故障 - 超时
#define	FAULT_ENC_CRC					(0x0002)			// 1 编码器故障 - CRC校验错误
#define	FAULT_BISS_ERR					(0x0004)			// 2 编码器故障 - BiSS帧的报错
#define	FAULT_BISS_WARN					(0x0008)			// 3 编码器故障 - BiSS帧的警告

#define BISS_ERRSIZE					(2)			// BISS Error Size
#define BISS_ERRMASK					(0x78)		// Error Mask in BISS_STATE
#define BISS_CRCTOUTMASK				(0x18)		// Error Mask of CRC and Timeout in BISS_STATE
#define BISS_ERRSHIFT					(0x03)		// Error shift in BISS_STATE


/* ------ SPI ENCODER ------ */
#if ENCODER_SEL_SPI_ENABLED > 0
/*! \brief If Encoder SPI DMA transfer is enabled. */
#define ENC_SPI_DMA_ENABLED				( 1 )

#if (ENCSPI_Source == ENCSPI_KTH)
#define ENC_SPI_LEN						( 4 )
#else // #if (ENCSPI_Source == ENCSPI_MT)
#define ENC_SPI_LEN						( 6 )
#endif

#define	ENCSPI1_RD_DMA_CR				(DMA2_CR)	// DMA setting register
#define	ENCSPI1_RD_DMA_BA				(DMA2_BA)	// DMA data address register
#define	ENCSPI1_RD_DMA_LEN				(DMA2_LEN)	// DMA data length register
#define	ENCSPI1_WR_DMA_CR				(DMA3_CR)	// DMA setting register
#define	ENCSPI1_WR_DMA_BA				(DMA3_BA)	// DMA data address register
#define	ENCSPI1_WR_DMA_LEN				(DMA3_LEN)	// DMA data length register
#endif

/* ------ SPI ENCODER ------ */
#if ENCODER_SEL_SPI2_ENABLED > 0
/*! \brief If Encoder SPI DMA transfer is enabled. */
#define ENC_SPI2_DMA_ENABLED			( 1 )

#if (ENCSPI2_Source == ENCSPI_KTH)
#define ENC_SPI2_LEN					( 4 )
#else // #if (ENCSPI2_Source == ENCSPI_MT)
#define ENC_SPI2_LEN					( 6 )
#endif

#define	ENCSPI2_RD_DMA_CR				(DMA1_CR)	// DMA setting register
#define	ENCSPI2_RD_DMA_BA				(DMA1_BA)	// DMA data address register
#define	ENCSPI2_RD_DMA_LEN				(DMA1_LEN)	// DMA data length register
#define	ENCSPI2_WR_DMA_CR				(DMA4_CR)	// DMA setting register
#define	ENCSPI2_WR_DMA_BA				(DMA4_BA)	// DMA data address register
#define	ENCSPI2_WR_DMA_LEN				(DMA4_LEN)	// DMA data length register
#endif


// Definition of register ENCCALCTRL
#define	ENCCAL_START					(0x0001)			// 上升沿：电机侧编码器开始标定
#define	ENCCAL_SAVE						(0x0002)			// 上升沿：电机侧编码器保存标定结果到编码器芯片MTP
#define	ENCREG_WRITE					(0x0004)			// 上升沿：电机侧编码器写寄存器
#define	ENCREG_READ						(0x0008)			// 上升沿：电机侧编码器读寄存器
#define	SFBENCCAL_START					(0x0100)			// 上升沿：输出侧编码器开始标定
#define	SFBENCCAL_SAVE					(0x0200)			// 上升沿：输出侧编码器保存标定结果到编码器芯片MTP
#define	SFBENCREG_WRITE					(0x0400)			// 上升沿：输出侧编码器写寄存器
#define	SFBENCREG_READ					(0x0800)			// 上升沿：输出侧编码器读寄存器


// Definition of register ENCCALSTATUS
#define	ENCCALSTA_IDLE					( 0 )			// 未开始标定
#define	ENCCALSTA_DOING					( 1 )			// 标定进行中
#define	ENCCALSTA_FAIL					( 2 )			// 标定失败
#define	ENCCALSTA_FINISH				( 3 )			// 标定完成/成功


/*==================================================================================================*/
/*************************************** Variable Declaration ***************************************/
/*==================================================================================================*/

/* ------ TMG ENCODER ------ */
#if ENCODER_SEL_TMG_ENABLED > 0
typedef struct
{
	uint32 TxRx_XRAM_Buf[3];								// TMG协议用于收发的XRAM缓存（12byte的地址空间）
	uint8 ClearMultiFlag;									// Clear Multiturn flag
	uint8 ClearMultiCounter;								// Clear Multiturn Counter
	uint16 TmgTimeOutFlag;
	
	uint32 EncData;											// 编码器位置值(累加成32位)
	uint32 Single;											// 编码器位置值(一般<32位)
	uint32 SingleLatch;										// 编码器位置值上一拍
	int32  Multi;											// 编码器位置值高位
	uint32 SingleHalf;										// 编码器值有效数据位分辨率的一半
	uint32 DataMask;										// Data mask of valid bits
	uint16 ValidBits;										// valid data bits
	uint16 ZeroBits;										// zero bits length
} TMG_TypeDef;
#endif

/* ------ BISS ENCODER ------ */
#if ENCODER_SEL_BISS_ENABLED > 0
typedef struct
{
	uint16 ClockFreq;										// BiSS Clock frequency
	
	uint32 EncData;											// 编码器位置值(累加成32位)
	uint32 Single;											// 编码器位置值(一般<32位)
	uint32 SingleLatch;										// 编码器位置值上一拍
	int32 Multi;											// 编码器位置值高位
	uint32 SingleHalf;										// 编码器值有效数据位分辨率的一半
	uint32 DataMask;										// Data mask of valid bits
	uint16 DataBits;										// BiSS SCD data bits (error not included)
	uint16 ValidBits;										// BiSS valid data bits
	uint16 ZeroBits;										// BiSS zero bits length
} BiSS_TypeDef;
#endif

/* ------ SPI ENCODER ------ */
#if ENCODER_SEL_SPI_ENABLED > 0 || ENCODER_SEL_SPI2_ENABLED > 0
typedef struct
{
	uint16 EncSel;											// Motor side or load side
	uint16 DataBits;										// SPI SCD data bits (error not included)
	uint16 ValidBits;										// SPI valid data bits
	uint16 ZeroBits;										// SPI zero bits length
	uint32 EncData;											// 编码器位置值(累加成32位)
	uint32 Single;											// 编码器位置值(一般<32位)
	uint32 SingleLatch;										// 编码器位置值上一拍
	int32  Multi;											// 编码器位置值高位
	uint32 SingleHalf;										// 编码器值有效数据位分辨率的一半
	uint32 DataMask;										// Data mask of valid bits
	uint8 FirstFlag;										// 
} Enc_SPI_TypeDef;
#endif

/* ------ PWM ENCODER ------ */
#if ENCODER_SEL_PWM_ENABLED > 0
typedef struct
{
	uint32 EncData;											// 编码器位置值(累加成32位)
	uint32 Single;											// 编码器位置值(一般<32位)
	uint32 SingleLatch;										// 编码器位置值上一拍
	int32 Multi;											// 编码器位置值高位
	uint32 SingleHalf;										// 编码器值有效数据位分辨率的一半
	uint32 DataMask;										// Data mask of valid bits
	uint16 ValidBits;										// PWM valid data bits
} Enc_PWM_TypeDef;
#endif

/* ------ ALL ENCODER ------ */
typedef struct
{
	uint8 EncLoopTime;
	uint8 SpdRank;
	uint16 ErrCode;											// 编码器总故障码
	uint16 TypeSelect;										// 编码器类型选择
	uint16 LoadTypeSelect;								    // 输出侧编码器类型选择
	
	uint32 EncPos;											// 编码器位置值(低32位)
	uint32 LoadEncPos;                                      // 外部编码器位置值(低32位)
	uint32 LoadQepPos;										// 输出侧编码器位置值
	uint32 EncPosLatch;										// 编码器位置值上一拍

	int32 MultiHigh;										// 编码器位置值(高32位)
	
	uint64 DelayComCoef;                                    // 编码器延迟补偿系数
	uint32 ValueMax;
	int16 EleAngComp;                                       // 编码器补偿值,Q10格式

#if ENCODER_SEL_ABZ_ENABLED > 0
	uint8 AqbFilt;											// AQB编码器滤波系数
#endif
	
#if ENCODER_SEL_TMG_ENABLED > 0
	TMG_TypeDef TMG;
#endif
#if ENCODER_SEL_BISS_ENABLED > 0
	BiSS_TypeDef BiSS;
#endif
	
#if ENCODER_SEL_SPI_ENABLED > 0
	Enc_SPI_TypeDef SPI;
#endif
	
#if ENCODER_SEL_SPI2_ENABLED > 0
	Enc_SPI_TypeDef SPI2;
#endif
	
#if ENCODER_SEL_PWM_ENABLED > 0
	Enc_PWM_TypeDef PWM;
#endif
} Encoder_TypeDef;

extern Encoder_TypeDef mcEncoder;



/*==================================================================================================*/
/*************************************** Funciton Declaration ***************************************/
/*==================================================================================================*/
extern void Encoder_Init(void);
extern void Encoder_Switch(void);
extern void Encoder_Switch_LoadSide(void);
extern void Encoder_Update(void);
extern void Encoder_GetPos(int32* pEncPos, int32* pEncMulti, int16* pEncDiff, uint16* pErrCode);

/* ------ TMG ENCODER ------ */
#if ENCODER_SEL_TMG_ENABLED > 0
extern void TMG_Encoder_Init(void);
extern void TMG_Encoder_Enable(void);
extern void TMG_Encoder_Disable(void);
extern void TMG_Encoder_Update(void);
extern uint16 TMG_Encoder_GetMultiAbsPos(uint32 *pEncPos);									// ID 3		读多圈位置
extern uint16 TMG_Encoder_GetSingleAbsPos(uint32* pEncPos);									// ID 0		读单圈位置
extern uint16 TMG_Encoder_GetMultiTurns(uint32* pEncMulti);									// ID 1		读多圈圈数值

extern uint16 TMG_Encoder_Reset(uint8 Reset_ID);									// ID 7 8 C	复位操作(3种)

extern uint16 TMG_Encoder_ReadEEPROM(uint8 AddressField);						// ID D		读EEPROM
extern uint16 TMG_Encoder_WriteEEPROM(uint8 AddressField, uint8 EepromField);	// ID 6		写EEPROM
#endif

/* ------ BISS ENCODER ------ */
#if ENCODER_SEL_BISS_ENABLED > 0
extern void BiSS_Encoder_Init(void);
extern void BiSS_Encoder_Enable(void);
extern void BiSS_Encoder_Disable(void);
extern void BiSS_Encoder_Update(void);
extern uint16 BiSS_Encoder_GetPos(uint32* pEncPos);
#endif

/* ------ SPI ENCODER ------ */
#if ENCODER_SEL_SPI_ENABLED > 0
extern void SPI_Encoder_Init(void);
extern void SPI_Encoder_Enable(uint8 EncSel);
extern void SPI_Encoder_Disable(void);
extern void SPI_Encoder_Update(void);
extern void SPI_Encoder_Calibration(void);
extern uint16 SPI_Encoder_GetPos(uint32* pEncPos);
#endif

/* ------ SPI ENCODER ------ */
#if ENCODER_SEL_SPI2_ENABLED > 0
extern void SPI2_Encoder_Init(void);
extern void SPI2_Encoder_Enable(uint8 EncSel);
extern void SPI2_Encoder_Disable(void);
extern void SPI2_Encoder_Update(void);
extern void SPI2_Encoder_Calibration(void);
extern uint16 SPI2_Encoder_GetPos(uint32* pEncPos);
#endif

/* ------ PWM ENCODER ------ */
#if ENCODER_SEL_PWM_ENABLED > 0
extern void PWM_Encoder_Init(void);
extern void PWM_Encoder_Enable(void);
extern void PWM_Encoder_Disable(void);
extern void PWM_Encoder_Update(void);
extern uint16 PWM_Encoder_GetPos(uint32* pEncPos);
#endif

#endif
