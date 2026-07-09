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

typedef unsigned char                   uint8;                                  // Unsigned character-type variable
typedef unsigned short                  uint16;                                 // Unsigned integer-type variable
typedef unsigned long                   uint32;                                 // Unsigned long integer-type variable
typedef unsigned long long              uint64;                                 // Unsigned 64-bit integer-type variable
typedef char                            int8;                                   // Signed character-type variable
typedef short                           int16;                                  // Signed integer-type variable
typedef long                            int32;                                  // Signed long integer-type variable
typedef long long                       int64;                                  // Signed 64-bit integer-type variable
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
 * NOP instruction
 */
#define nop()                           ({                            \
                                            __asm__ volatile ("nop"); \
                                        })

/**
 * Wait-for-interrupt instruction
 */
#define wfi()                           ({                            \
                                            __asm__ volatile ("wfi"); \
                                        })

/**
 * Read CSR register
 *
 * @param  reg CSR register address
 * @return     current CSR value
 */
#define read_csr(reg)                   ({                                                             \
                                            unsigned long __tmp;                                       \
                                            __asm__ volatile ("csrr %0, %1" : "=r"(__tmp) : "i"(reg)); \
                                            __tmp;                                                     \
                                        })

/**
 * Write data to CSR register
 *
 * @param reg CSR register address
 * @param val data to write
 */
#define write_csr(reg, val)             do                                                            \
                                        {                                                             \
                                            __asm__ volatile ("csrw %0, %1" : : "i"(reg), "rK"(val)); \
                                        } while (0)

/**
 * Set specified bit(s) in CSR register
 *
 * @param reg CSR register address
 * @param bit bit(s) to operate
 */
#define set_csr(reg, bit)               do                                                                   \
                                        {                                                                    \
                                            __asm__ volatile ("csrrs zero, %0, %1" : : "i"(reg), "rK"(bit)); \
                                        } while (0)

/**
 * Clear specified bit(s) in CSR register
 *
 * @param reg CSR register address
 * @param bit bit(s) to operate
 */
#define clr_csr(reg, bit)               do                                                                   \
                                        {                                                                    \
                                            __asm__ volatile ("csrrc zero, %0, %1" : : "i"(reg), "rK"(bit)); \
                                        } while (0)

/**
 * Read status of bit(s) in CSR register
 *
 * @param  reg CSR register address
 * @return     whether the specified bit(s) are set
 */
#define readbit_csr(reg, bit)           ({                                  \
                                            ((read_csr(reg) & (bit)) != 0); \
                                        })

/**
 * Toggle specified bit(s) in CSR register
 *
 * @param reg CSR register address
 * @param bit bit(s) to operate
 */
#define xor_csr(reg, bit)               do                                         \
                                        {                                          \
                                            write_csr(reg, read_csr(reg) ^ (bit)); \
                                        } while (0)

/**
 * Clear and set specified bits in CSR register simultaneously
 *
 * @param[in]  reg      CSR register address
 * @param[in]  cbit     register bits to clear (set to 0)
 * @param[in]  sbit     register bits to set (set to 1)
 */
#define reset_csr(reg, cbit, sbit)      do                                                      \
                                        {                                                       \
                                            write_csr(reg, (read_csr(reg) & ~(cbit)) | (sbit)); \
                                        } while (0)


#endif