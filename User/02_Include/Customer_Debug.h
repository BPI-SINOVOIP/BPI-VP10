/*
 * Copyright (c) 2021-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : Customer_Debug.h
 * Author        : Summer
 * Date          : 2021-11-13
 * Description   : This file contains SPI debug configuration.
 *
 * Record        :
 * V1.0, 2021-11-13, Summer: Created file
 */

#ifndef __CUSTOMER_DEBUG_H__
#define __CUSTOMER_DEBUG_H__

#include "fu7502.h"
#include "Parameter.h"

/*************************************************************************************///External Function

// 硬件DBG的参数首地址
 #define HARD_SPIDATA   &NFOC_THETA//(FOC_THETA + 0x70000000)//&ADC_DR0

  // GPA1  DBG1信号配置
 #define GPA1_DISABLE                   0x00													// 禁能GP01的DBG信号
 #define GPA1_ADCTrigger                DBG1SEL0												// ADC trigger信号
 #define GPA1_ADC2Trigger		        DBG1SEL1												// ADC2 trigger信号
 #define GPA1_PFCTrigger                DBG1SEL1 | DBG1SEL0										// ADC3 trigger信号
 #define GPA1_CMP012_SAM_ON             DBG1SEL2												// CMP012的ON采样窗口
 #define GPA1_CMP012_SAM_OFF            DBG1SEL2 | DBG1SEL0										// CMP012的OFF采样窗口
 #define GPA1_CMP678_SAM_ON             DBG1SEL2 | DBG1SEL1										// CMP678的ON采样窗口
 #define GPA1_CMP678_SAM_OFF            DBG1SEL2 | DBG1SEL1 | DBG1SEL0							// CMP678的OFF采样窗口
 #define GPA1_CMP123_SAM_ONOFF          DBG1SEL3												// CMP012的ON/OFF采样窗口
 #define GPA1_CMP678_SAM_ONOFF          DBG1SEL3 | DBG1SEL0										// CMP678的ON/OFF采样窗口
 #define GPA1_ME_BUSY			        DBG1SEL3 | DBG1SEL2										// FOC1和FOC2计算状态
 #define GPA1_CUR_LP_BUSY		        DBG1SEL3 | DBG1SEL2 | DBG1SEL0							// 电流环计算状态
 #define GPA1_FOC2_BUSY			        DBG1SEL3 | DBG1SEL2 | DBG1SEL1							// FOC2计算状态
 #define GPA1_DRV_CNTR_DIR1		        DBG1SEL4			                       				// DIVER1计数方向
 #define GPA1_OVERFLOW1	                DBG1SEL4 | DBG1SEL0										// DIVER1上溢点
 #define GPA1_UNDERFLOW1                DBG1SEL4 | DBG1SEL1										// DIVER1下溢点
 #define GPA1_OMEGA_STA_FLAG1           DBG1SEL4 | DBG1SEL1 | DBG1SEL0							// OMEGA1启动状态
 #define GPA1_HFI_ST1	                DBG1SEL4 | DBG1SEL2										// 高频注入相关信号1
 #define GPA1_WPI_CAL1	                DBG1SEL4 | DBG1SEL2 | DBG1SEL0							// 外环计算状态1
 #define GPA1_MMT_CAL1	                DBG1SEL4 | DBG1SEL2 | DBG1SEL1							// 伺服相关信号
 #define GPA1_SF_CAL1	                DBG1SEL4 | DBG1SEL2 | DBG1SEL1 | DBG1SEL0				// 伺服相关信号
 #define GPA1_DRV_CNTR_DIR2		        DBG1SEL4 | DBG1SEL3										// DIVER2计数方向
 #define GPA1_OVERFLOW2	                DBG1SEL4 | DBG1SEL3 | DBG1SEL0							// DIVER2上溢点
 #define GPA1_UNDERFLOW2                DBG1SEL4 | DBG1SEL3 | DBG1SEL1							// DIVER2下溢点
 #define GPA1_OMEGA_STA_FLAG2           DBG1SEL4 | DBG1SEL3 | DBG1SEL1 | DBG1SEL0				// OMEGA2启动状态
 #define GPA1_HFI_ST2	                DBG1SEL4 | DBG1SEL3 | DBG1SEL2							// 高频注入相关信号2
 #define GPA1_WPI_CAL2	                DBG1SEL4 | DBG1SEL3 | DBG1SEL2 | DBG1SEL0				// 外环计算状态2
 #define GPA1_MMT_CAL2	                DBG1SEL4 | DBG1SEL3 | DBG1SEL2 | DBG1SEL1				// 伺服相关信号
 #define GPA1_SF_CAL2	                DBG1SEL4 | DBG1SEL3 | DBG1SEL2 | DBG1SEL1 | DBG1SEL0	// 伺服相关信号	
	
 #define GPA1_DBG_Conf                  (GPA1_DISABLE)						// GPA1信号选择

  // GPB0  DBG2信号配置
 #define GPB0_DISABLE                   0x00				                                    // 禁能GP01的DBG信号
 #define GPB0_ADCTrigger                DBG2SEL0				                                // ADC trigger信号
 #define GPB0_ADC2Trigger		        DBG2SEL1				                                // ADC2 trigger信号
 #define GPB0_PFCTrigger                DBG2SEL1 | DBG2SEL0					                    // ADC3 trigger信号
 #define GPB0_CMP012_SAM_ON             DBG2SEL2												// CMP012的ON采样窗口
 #define GPB0_CMP012_SAM_OFF            DBG2SEL2 | DBG2SEL0										// CMP012的OFF采样窗口
 #define GPB0_CMP678_SAM_ON             DBG2SEL2 | DBG2SEL1										// CMP678的ON采样窗口
 #define GPB0_CMP678_SAM_OFF            DBG2SEL2 | DBG2SEL1 | DBG2SEL0							// CMP678的OFF采样窗口
 #define GPB0_CMP123_SAM_ONOFF          DBG2SEL3												// CMP012的ON/OFF采样窗口
 #define GPB0_CMP678_SAM_ONOFF          DBG2SEL3 | DBG2SEL0										// CMP678的ON/OFF采样窗口
 #define GPB0_ME_BUSY			        DBG2SEL3 | DBG2SEL2										// FOC1和FOC2计算状态
 #define GPB0_CUR_LP_BUSY		        DBG2SEL3 | DBG2SEL2 | DBG2SEL0							// 电流环计算状态
 #define GPB0_FOC2_BUSY			        DBG2SEL3 | DBG2SEL2 | DBG2SEL1							// FOC2计算状态
 #define GPB0_DRV_CNTR_DIR1		        DBG2SEL4			                       				// DIVER1计数方向
 #define GPB0_OVERFLOW1	                DBG2SEL4 | DBG2SEL0										// DIVER1上溢点
 #define GPB0_UNDERFLOW1                DBG2SEL4 | DBG2SEL1										// DIVER1下溢点
 #define GPB0_OMEGA_STA_FLAG1           DBG2SEL4 | DBG2SEL1 | DBG2SEL0							// OMEGA1启动状态
 #define GPB0_HFI_ST1	                DBG2SEL4 | DBG2SEL2										// 高频注入相关信号1
 #define GPB0_WPI_CAL1	                DBG2SEL4 | DBG2SEL2 | DBG2SEL0							// 外环计算状态1
 #define GPB0_MMT_CAL1	                DBG2SEL4 | DBG2SEL2 | DBG2SEL1							// 伺服相关信号
 #define GPB0_SF_CAL1	                DBG2SEL4 | DBG2SEL2 | DBG2SEL1 | DBG2SEL0				// 伺服相关信号
 #define GPB0_DRV_CNTR_DIR2		        DBG2SEL4 | DBG2SEL3										// DIVER2计数方向
 #define GPB0_OVERFLOW2	                DBG2SEL4 | DBG2SEL3 | DBG2SEL0							// DIVER2上溢点
 #define GPB0_UNDERFLOW2                DBG2SEL4 | DBG2SEL3 | DBG2SEL1							// DIVER2下溢点
 #define GPB0_OMEGA_STA_FLAG2           DBG2SEL4 | DBG2SEL3 | DBG2SEL1 | DBG2SEL0				// OMEGA2启动状态
 #define GPB0_HFI_ST2	                DBG2SEL4 | DBG2SEL3 | DBG2SEL2							// 高频注入相关信号2
 #define GPB0_WPI_CAL2	                DBG2SEL4 | DBG2SEL3 | DBG2SEL2 | DBG2SEL0				// 外环计算状态2
 #define GPB0_MMT_CAL2	                DBG2SEL4 | DBG2SEL3 | DBG2SEL2 | DBG2SEL1				// 伺服相关信号
 #define GPB0_SF_CAL2	                DBG2SEL4 | DBG2SEL3 | DBG2SEL2 | DBG2SEL1 | DBG2SEL0	// 伺服相关信号		
	
 #define GPB0_DBG_Conf                  (GPB0_DISABLE)											// GPB0信号选择

 // GPAx CMP输出信号配置
 #define GPAx_DISABLE                   0x00				                                    // 禁能GPAx的比较器信号输出
 #define GPAx_CMP0_SAM                  CMPSEL0					                                // CMP0_OUT的采样结果
 #define GPAx_CMP1_SAM                  CMPSEL1					                                // CMP1_OUT的采样结果
 #define GPAx_CMP2_SAM                  CMPSEL1 | CMPSEL0				                        // CMP2_OUT的采样结果
 #define GPAx_CMP3_FLT                  CMPSEL2					                                // CMP3_OUT的滤波信号（采样结果）
 #define GPAx_CMP4_FLT                  CMPSEL2 | CMPSEL0				                        // CMP4_OUT的滤波信号（采样结果）
 #define GPAx_CMP5_FLT                  CMPSEL2 | CMPSEL1				                        // CMP5_OUT的滤波信号（采样结果）
 #define GPAx_CMP6_SAM                  CMPSEL2 | CMPSEL1 | CMPSEL0					            // CMP6_OUT的采样结果
 #define GPAx_CMP7_SAM                  CMPSEL3										            // CMP7_OUT的采样结果
 #define GPAx_CMP8_SAM                  CMPSEL3 | CMPSEL0										// CMP8_OUT的采样结果
 #define GPAx_CMP9_FLT                  CMPSEL3 | CMPSEL1										// CMP9_OUT的滤波信号（采样结果）
 #define GPAx_CMP10_FLT                 CMPSEL3 | CMPSEL1 | CMPSEL0								// CMP10_OUT的滤波信号（采样结果）
 #define GPAx_CMP11_FLT                 CMPSEL3 | CMPSEL2										// CMP11_OUT的滤波信号（采样结果）
 #define GPAx_CMP0_OUT                  CMPSEL4 | CMPSEL0		                                // CMP0_OUT的原始信号
 #define GPAx_CMP1_OUT                  CMPSEL4 | CMPSEL1		                                // CMP1_OUT的原始信号
 #define GPAx_CMP2_OUT                  CMPSEL4 | CMPSEL1 | CMPSEL0		                        // CMP2_OUT的原始信号
 #define GPAx_CMP3_OUT                  CMPSEL4 | CMPSEL2				                        // CMP3_OUT的原始信号
 #define GPAx_CMP4_OUT                  CMPSEL4 | CMPSEL2 | CMPSEL0								// CMP4_OUT的原始信号
 #define GPAx_CMP5_OUT                  CMPSEL4 | CMPSEL2 | CMPSEL1								// CMP5_OUT的原始信号
 #define GPAx_CMP6_OUT                  CMPSEL4 | CMPSEL2 | CMPSEL1 | CMPSEL0		            // CMP6_OUT的原始信号
 #define GPAx_CMP7_OUT					CMPSEL4 | CMPSEL3										// CMP7_OUT的原始信号
 #define GPAx_CMP8_OUT                  CMPSEL4 | CMPSEL3 | CMPSEL0								// CMP8_OUT的原始信号
 #define GPAx_CMP9_OUT                  CMPSEL4 | CMPSEL3 | CMPSEL1								// CMP9_OUT的原始信号
 #define GPAx_CMP10_OUT                 CMPSEL4 | CMPSEL3 | CMPSEL1 | CMPSEL0					// CMP10_OUT的原始信号
 #define GPAx_CMP11_OUT                 CMPSEL4 | CMPSEL3 | CMPSEL2								// CMP11_OUT的原始信号
// #define GPAx_CMPOX                     CMPSEL2 | CMPSEL1 | CMPSEL0				             // 输出ADC结果比较信号(BLDC)Omega启动状态(FOC)

 #define GPAx_DBG_Conf                  (GPAx_DISABLE)					                            // GPAx信号选择  输出引脚默认PA7，也可配置


#if TEST_SPIDEBUG_SW_ENABLED
extern unsigned short spidebug[4];
#endif

#endif
