/*
 * Copyright (c) 2023-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : fu7502_flash.h
 * Author        : Any Lin
 * Date          : 2023-12-07
 * Description   : define flash
 *
 * Record        :
 * V1.0, 2023-12-07, Any Lin: Created file
 */

#ifndef __FU7502_FLASH_H__
#define __FU7502_FLASH_H__

/******************************************************************************/// Including Header Files
#include "fu7502.h"
/******************************************************************************/// Define Macro
#define SEC_LEN					(512)		// 扇区
#define PAGE_SEC_SIZE			(8)		// sectors
#define FLASH_LEN				(65536UL)	// flash长度

#define PAGE_LEN		(PAGE_SEC_SIZE * SEC_LEN)	// 页长度


/******************************************************************************/// Define Type
/**
 * @enum 编程命令
 * @brief 列举出Flash的可用模式及命令构成
 */
typedef enum
{
	FLASH_PRG8E = FLAEN,                                 /**< 8字节数据+ECC字节编程 */
	FLASH_PRG1 = FLAEN | FLASIZE | FLAECC,              /**< 1字节数据编程 */
	FLASH_PRGE = FLAEN | FLASIZE,						/**< ECC字节编程 */
	FLASH_SEC_ERS = FLAEN | FLAERS,                        /**< 扇区擦除 */
	FLASH_SEC_PP = FLAEN | FLAPRE,                        /**< 扇区预擦除 */
	FLASH_SEC_M1 = FLAEN | FLAPRE | FLAMARGIN1,           /**< 扇区检查模式1 */
	FLASH_PAGE_ERS = FLAEN | FLAERS | FLAPAGE,              /**< 页擦除 */
	FLASH_PAGE_PP = FLAEN | FLAPRE | FLAPAGE,              /**< 页预擦除 */
	FLASH_PAGE_M1 = FLAEN | FLAPRE | FLAPAGE | FLAMARGIN1, /**< 页检查模式1 */
	FLASH_CHIP_ERS = FLAEN | FLAERS | FLACHIP,              /**< 全片擦除 */
	FLASH_CHIP_PP = FLAEN | FLAPRE | FLACHIP,              /**< 全片预擦除 */
	FLASH_CHIP_M1 = FLAEN | FLAPRE | FLACHIP | FLAMARGIN1, /**< 全片检查模式1 */
	FLASH_PRG8 = FLAEN | FLAECC,                  /**< 8字节数据编程 */  /* factory */
//    FLASH_PRGEM    = FLAEN | FLAECC | FLAECCMANUAL,         /**< ECC字节编程, ECC手动模式 */  /* factory */
} ETypeFlashCmd;

/**
 * @enum 编程结果
 * @brief 列举出Flash操作过程中会出现的各种错误
 */
typedef enum
{
	FLASH_IDLE,       /**< 初始化 */
	FLASH_SUCCESS,    /**< 编程成功 */
	FLASH_ERR_ADDR,   /**< 由于尝试编程非法地址导致的编程错误 */
	FLASH_ERR_CMD,    /**< 由于编程命令错误导致的编程错误 */
	FLASH_ERR_UNLOCK, /**< 由于编程解锁过程中出现的错误 */
	FLASH_FORZEN,     /**< 编程锁被冻结 */
	FLASH_ERROR       /**< 其他问题导致的编程失败 */
} ETypeFlashStatu;

/******************************************************************************/// External Symbols
/******************************************************************************/// External Function
extern ETypeFlashStatu Flash_Ctrl(ETypeFlashCmd eCmd, uint32 ulAddr, uint64 ullDat);
// extern ETypeFlashStatu Flash_PageErase(unsigned short wAddr);
// extern ETypeFlashStatu Flash_SectorErase(unsigned short wAddr);

#endif
