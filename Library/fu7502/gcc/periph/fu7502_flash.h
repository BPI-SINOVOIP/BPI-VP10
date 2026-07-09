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
#define SEC_LEN					(512)		// Sector
#define PAGE_SEC_SIZE			(8)		// sectors
#define FLASH_LEN				(65536UL)	// flash length

#define PAGE_LEN		(PAGE_SEC_SIZE * SEC_LEN)	// Page length


/******************************************************************************/// Define Type
/**
 * @enum Programming commands
 * @brief Lists the available modes and command composition of the Flash
 */
typedef enum
{
	FLASH_PRG8E = FLAEN,                                 /**< 8-byte data + ECC byte programming */
	FLASH_PRG1 = FLAEN | FLASIZE | FLAECC,              /**< 1-byte data programming */
	FLASH_PRGE = FLAEN | FLASIZE,						/**< ECC byte programming */
	FLASH_SEC_ERS = FLAEN | FLAERS,                        /**< Sector erase */
	FLASH_SEC_PP = FLAEN | FLAPRE,                        /**< Sector pre-erase */
	FLASH_SEC_M1 = FLAEN | FLAPRE | FLAMARGIN1,           /**< Sector check mode 1 */
	FLASH_PAGE_ERS = FLAEN | FLAERS | FLAPAGE,              /**< Page erase */
	FLASH_PAGE_PP = FLAEN | FLAPRE | FLAPAGE,              /**< Page pre-erase */
	FLASH_PAGE_M1 = FLAEN | FLAPRE | FLAPAGE | FLAMARGIN1, /**< Page check mode 1 */
	FLASH_CHIP_ERS = FLAEN | FLAERS | FLACHIP,              /**< Chip erase */
	FLASH_CHIP_PP = FLAEN | FLAPRE | FLACHIP,              /**< Chip pre-erase */
	FLASH_CHIP_M1 = FLAEN | FLAPRE | FLACHIP | FLAMARGIN1, /**< Chip check mode 1 */
	FLASH_PRG8 = FLAEN | FLAECC,                  /**< 8-byte data programming */  /* factory */
//    FLASH_PRGEM    = FLAEN | FLAECC | FLAECCMANUAL,         /**< ECC byte programming, ECC manual mode */  /* factory */
} ETypeFlashCmd;

/**
 * @enum Programming results
 * @brief Lists various errors that may occur during Flash operations
 */
typedef enum
{
	FLASH_IDLE,       /**< Initialization */
	FLASH_SUCCESS,    /**< Programming successful */
	FLASH_ERR_ADDR,   /**< Programming error due to attempt to program an illegal address */
	FLASH_ERR_CMD,    /**< Programming error caused by incorrect programming command */
	FLASH_ERR_UNLOCK, /**< Error occurred during programming unlock process */
	FLASH_FORZEN,     /**< Programming lock is frozen */
	FLASH_ERROR       /**< Programming failed due to other issues */
} ETypeFlashStatu;

/******************************************************************************/// External Symbols
/******************************************************************************/// External Function
extern ETypeFlashStatu Flash_Ctrl(ETypeFlashCmd eCmd, uint32 ulAddr, uint64 ullDat);
// extern ETypeFlashStatu Flash_PageErase(unsigned short wAddr);
// extern ETypeFlashStatu Flash_SectorErase(unsigned short wAddr);

#endif