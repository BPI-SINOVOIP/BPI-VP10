/*
 * Copyright (c) 2023-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : fu7502_flash.c
 * Author        : Any Lin
 * Date          : 2023-12-07
 * Description   : define flash
 *
 * Record        :
 * V1.0, 2023-12-07, Any Lin: Created file
 */

/******************************************************************************///Including Header Files
#include "fu7502.h"
#include "fu7502_flash.h"
#include "stdbool.h"
/******************************************************************************///Define Macro
#define SEC_LADDR                       (((FLASH_LEN / SEC_LEN) - 1) * SEC_LEN) + ROM_BASE
#define PAGE_LADDR                      ((PAGE_SEC_SIZE - 1) * PAGE_LEN) + ROM_BASE
#define LADDR_MASK                      0x00ffffff
/******************************************************************************///Define Global Symbols
/******************************************************************************///Function Subject

/**
 * @brief      Flash operation
 *			   This function is the hardware abstraction for Flash operations, users only need to pass the programming command, programming address,
 *			   and programming data to this function. Parameter validation for Flash programming and the complete operation process are handled by this function
 * @param[in]  eCmd     operation command
 * @param[in]  ulAddr   programming address
 * @param[in]  vpDat    address of programming data
 * @return     Flash operation result
 */
ETypeFlashStatu Flash_Ctrl(ETypeFlashCmd eCmd, uint32 ulAddr, uint64 ullDat)
{

	uint8 ucKey1 = 0x5a;
	uint8 ucKey2 = 0x1f;
	uint32* ulpAddr;


	// Programming command check
	switch (eCmd)
	{
	case FLASH_PRG8E:
	case FLASH_PRG1:
	case FLASH_PRGE:
	case FLASH_SEC_ERS:
	case FLASH_SEC_PP:
	case FLASH_SEC_M1:
	case FLASH_PAGE_ERS:
	case FLASH_PAGE_PP:
	case FLASH_PAGE_M1:
	case FLASH_CHIP_ERS:
	case FLASH_CHIP_PP:
	case FLASH_CHIP_M1:
	case FLASH_PRG8: /* factory */
		//	case FLASH_PRGEM:    /* factory */
		break;
	default: return FLASH_ERR_CMD;
	}

	// Programming address check
	// if ((ulAddr & 0x00ffffff) >= SEC_LADDR) return FLASH_ERR_ADDR;
	// if (!(eCmd & FLASIZE)) ulAddr &= 0xfffffff8;
	ulpAddr = (uint32*) ulAddr;
	//
	// Check if programming lock is frozen
	if (read_csr(FLA_KEY) == 0x06) return FLASH_FORZEN;

	// Write programming command
	write_csr(FLA_CR, eCmd);

	// Unlock programming lock
	write_csr(FLA_KEY, ucKey1);
	write_csr(FLA_KEY, ucKey2);
	if (read_csr(FLA_KEY) != 0x03) return FLASH_ERR_UNLOCK;

	// Trigger programming execution
	if (eCmd & FLASIZE)
	{
		*(uint8*) ulpAddr = (uint8)ullDat;
	}
	else
	{
		*ulpAddr = ullDat;
		*(ulpAddr + 1) = ullDat >> 32;
	}

	// Write programming command
	write_csr(FLA_CR, eCmd);

	// Check programming result
	if ((eCmd & FLAMARGIN1) && readbit_csr(FLA_CR, FLAM0ERR)) return FLASH_ERROR;
	if (readbit_csr(FLA_CR, FLAERR)) return FLASH_ERROR;

	return FLASH_SUCCESS;
}