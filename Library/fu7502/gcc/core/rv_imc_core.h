/*
 * Copyright (c) 2024-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : rv_imc_core.h
 * Author        : Any Lin
 * Date          : 2024-12-05
 * Description   : define basic function of MCU
 *
 * Record        :
 * V1.0, 2024-12-05, Any Lin: Created file
 */

#ifndef __RV_IMC_CORE_H__
#define __RV_IMC_CORE_H__

#include <stdbool.h>

/******************************************************************************/
/*                                                                            */
/*                          Variable type definition                          */
/*                                                                            */
/******************************************************************************/

typedef unsigned char                   uint8;                                  // 无符号字符型变量
typedef unsigned short                  uint16;                                 // 无符号整型变量
typedef unsigned long                   uint32;                                 // 无符号长整型变量
typedef unsigned long long              uint64;                                 // 无符号64位整型变量
typedef char                            int8;                                   // 有符号字符型变量
typedef short                           int16;                                  // 有符号整型变量
typedef long                            int32;                                  // 有符号长整型变量
typedef long long                       int64;                                  // 有符号64位整型变量
typedef enum{DISABLE = 0, ENABLE}       ebool;
//typedef _Bool                           bool;

/******************************************************************************/
/*                                                                            */
/*                        Function Property Definition                        */
/*                                                                            */
/******************************************************************************/
#define minterrupt                      __attribute__((interrupt ("machine")))

/******************************************************************************/
/*                                                                            */
/*                     CSR operating function definition                      */
/*                                                                            */
/******************************************************************************/
/**
 * 空指令
 */
#define nop()                           ({                            \
                                            __asm__ volatile ("nop"); \
                                        })

/**
 * 待机指令
 */
#define wfi()                           ({                            \
                                            __asm__ volatile ("wfi"); \
                                        })

/**
 * 读取CSR寄存器
 *
 * @param  reg csr寄存器地址
 * @return     csr当前值
 */
#define read_csr(reg)                   ({                                                             \
                                            unsigned long __tmp;                                       \
                                            __asm__ volatile ("csrr %0, %1" : "=r"(__tmp) : "i"(reg)); \
                                            __tmp;                                                     \
                                        })

/**
 * 写入数据到csr寄存器
 *
 * @param reg csr寄存器地址
 * @param val 写入的数据
 */
#define write_csr(reg, val)             do                                                            \
                                        {                                                             \
                                            __asm__ volatile ("csrw %0, %1" : : "i"(reg), "rK"(val)); \
                                        } while (0)

/**
 * csr寄存器指定位置1
 *
 * @param reg csr寄存器地址
 * @param bit 要操作的位
 */
#define set_csr(reg, bit)               do                                                                   \
                                        {                                                                    \
                                            __asm__ volatile ("csrrs zero, %0, %1" : : "i"(reg), "rK"(bit)); \
                                        } while (0)

/**
 * csr寄存器指定位置0
 *
 * @param reg csr寄存器地址
 * @param bit 要操作的位
 */
#define clr_csr(reg, bit)               do                                                                   \
                                        {                                                                    \
                                            __asm__ volatile ("csrrc zero, %0, %1" : : "i"(reg), "rK"(bit)); \
                                        } while (0)

/**
 * 读取CSR寄存器位状态
 *
 * @param  reg csr寄存器地址
 * @return     csr当前值
 */
#define readbit_csr(reg, bit)           ({                                  \
                                            ((read_csr(reg) & (bit)) != 0); \
                                        })

/**
 * csr寄存器指定位取反
 *
 * @param reg csr寄存器地址
 * @param bit 要操作的位
 */
#define xor_csr(reg, bit)               do                                         \
                                        {                                          \
                                            write_csr(reg, read_csr(reg) ^ (bit)); \
                                        } while (0)

/**
 * csr寄存器同时清除和设置一些位
 *
 * @param[in]  reg      csr寄存器地址
 * @param[in]  cbit  要置0的寄存器位
 * @param[in]  sbit  要置1的寄存器位
 */
#define reset_csr(reg, cbit, sbit)      do                                                      \
                                        {                                                       \
                                            write_csr(reg, (read_csr(reg) & ~(cbit)) | (sbit)); \
                                        } while (0)


#endif
