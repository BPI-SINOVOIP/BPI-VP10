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
 * @brief      Flash操作
 *			   该函数为Flash操作的硬件抽象函数, 用户仅需向该函数传入编程操作命令, 编程地址,
 *			   编程内容即可, Flash编程的传入参数检查和完整操作过程都由该函数完成
 * @param[in]  eCmd     操作命令
 * @param[in]  ulAddr   编程地址
 * @param[in]  vpDat    编程内容地址
 * @return     Flash操作结果
 */
ETypeFlashStatu Flash_Ctrl(ETypeFlashCmd eCmd, uint32 ulAddr, uint64 ullDat)
{

	uint8 ucKey1 = 0x5a;
	uint8 ucKey2 = 0x1f;
	uint32* ulpAddr;


	// 编程命令检查
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

	// 编程地址检查
	// if ((ulAddr & 0x00ffffff) >= SEC_LADDR) return FLASH_ERR_ADDR;
	// if (!(eCmd & FLASIZE)) ulAddr &= 0xfffffff8;
	ulpAddr = (uint32*) ulAddr;
	//
	// 编程锁冻结检查
	if (read_csr(FLA_KEY) == 0x06) return FLASH_FORZEN;

	// 编程命令写入
	write_csr(FLA_CR, eCmd);

	// 编程锁解除
	write_csr(FLA_KEY, ucKey1);
	write_csr(FLA_KEY, ucKey2);
	if (read_csr(FLA_KEY) != 0x03) return FLASH_ERR_UNLOCK;

	// 触发编程执行
	if (eCmd & FLASIZE)
	{
		*(uint8*) ulpAddr = (uint8)ullDat;
	}
	else
	{
		*ulpAddr = ullDat;
		*(ulpAddr + 1) = ullDat >> 32;
	}

	// 编程命令写入
	write_csr(FLA_CR, eCmd);

	// 编程结果检查
	if ((eCmd & FLAMARGIN1) && readbit_csr(FLA_CR, FLAM0ERR)) return FLASH_ERROR;
	if (readbit_csr(FLA_CR, FLAERR)) return FLASH_ERROR;

	return FLASH_SUCCESS;
}

