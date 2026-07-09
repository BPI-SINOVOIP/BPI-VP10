/*
 * Copyright (c) 2021-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : AddFunction.h
 * Author        : Summer
 * Date          : 2021-11-13
 * Description   : This file defines some basic functions.
 *
 * Record        :
 * V1.0, 2021-11-13, Summer: Created file
 */


#ifndef __AddFunction_H_
#define __AddFunction_H_


/***************************Independent Watchdog Commands************************************/
#define IWDT_KRCHANGE						(0x5555)	//Command to modify IWDT_KR register
#define IWDT_OPEN							(0xCCCC)	//Command to enable independent watchdog
#define IWDT_SHUT							(0x2222)	//Command to disable independent watchdog
#define IWDT_FEED							(0xAAAA)	//Independent watchdog reload command
#define IWDT_RELOAD							(0x80)		//Independent watchdog reload value

/***************************SPI Debug DMA************************************/
#define	SPIDBG_DMA_CR						(DMA4_CR)	// DMA setting register
#define	SPIDBG_DMA_BA						(DMA4_BA)	// DMA data address register
#define	SPIDBG_DMA_LEN						(DMA4_LEN)	// DMA data length register


/***************************Debug Signal Settings************************************/
// Start address of hardware DBG parameters
#define HARD_SPIDATA					(&NFOC_THETA)

// GPA1  DBG1 signal configuration
#define GPA1_DISABLE					0x00													// Disable DBG signal of GP01
#define GPA1_ADCTrigger					DBG1SEL0												// ADC trigger signal
#define GPA1_ADC2Trigger		        DBG1SEL1												// ADC2 trigger signal
#define GPA1_PFCTrigger					DBG1SEL1 | DBG1SEL0										// ADC3 trigger signal
#define GPA1_CMP012_SAM_ON				DBG1SEL2												// ON sampling window of CMP012
#define GPA1_CMP012_SAM_OFF				DBG1SEL2 | DBG1SEL0										// OFF sampling window of CMP012
#define GPA1_CMP678_SAM_ON				DBG1SEL2 | DBG1SEL1										// ON sampling window of CMP678
#define GPA1_CMP678_SAM_OFF				DBG1SEL2 | DBG1SEL1 | DBG1SEL0							// OFF sampling window of CMP678
#define GPA1_CMP123_SAM_ONOFF			DBG1SEL3												// ON/OFF sampling window of CMP012
#define GPA1_CMP678_SAM_ONOFF			DBG1SEL3 | DBG1SEL0										// ON/OFF sampling window of CMP678
#define GPA1_ME_BUSY			        DBG1SEL3 | DBG1SEL2										// FOC1 and FOC2 calculation status
#define GPA1_CUR_LP_BUSY		        DBG1SEL3 | DBG1SEL2 | DBG1SEL0							// Current loop calculation status
#define GPA1_FOC2_BUSY			        DBG1SEL3 | DBG1SEL2 | DBG1SEL1							// FOC2 calculation status
#define GPA1_DRV_CNTR_DIR1		        DBG1SEL4			                       				// DIVER1 counting direction
#define GPA1_OVERFLOW1	                DBG1SEL4 | DBG1SEL0										// DIVER1 overflow point
#define GPA1_UNDERFLOW1					DBG1SEL4 | DBG1SEL1										// DIVER1 underflow point
#define GPA1_OMEGA_STA_FLAG1			DBG1SEL4 | DBG1SEL1 | DBG1SEL0							// OMEGA1 startup status
#define GPA1_HFI_ST1	                DBG1SEL4 | DBG1SEL2										// High frequency injection related signal 1
#define GPA1_WPI_CAL1	                DBG1SEL4 | DBG1SEL2 | DBG1SEL0							// Outer loop calculation status 1
#define GPA1_MMT_CAL1	                DBG1SEL4 | DBG1SEL2 | DBG1SEL1							// Servo related signals
#define GPA1_SF_CAL1	                DBG1SEL4 | DBG1SEL2 | DBG1SEL1 | DBG1SEL0				// Servo related signals
#define GPA1_DRV_CNTR_DIR2		        DBG1SEL4 | DBG1SEL3										// DIVER2 counting direction
#define GPA1_OVERFLOW2	                DBG1SEL4 | DBG1SEL3 | DBG1SEL0							// DIVER2 overflow point
#define GPA1_UNDERFLOW2					DBG1SEL4 | DBG1SEL3 | DBG1SEL1							// DIVER2 underflow point
#define GPA1_OMEGA_STA_FLAG2			DBG1SEL4 | DBG1SEL3 | DBG1SEL1 | DBG1SEL0				// OMEGA2 startup status
#define GPA1_HFI_ST2	                DBG1SEL4 | DBG1SEL3 | DBG1SEL2							// High frequency injection related signal 2
#define GPA1_WPI_CAL2	                DBG1SEL4 | DBG1SEL3 | DBG1SEL2 | DBG1SEL0				// Outer loop calculation status 2
#define GPA1_MMT_CAL2	                DBG1SEL4 | DBG1SEL3 | DBG1SEL2 | DBG1SEL1				// Servo related signals
#define GPA1_SF_CAL2	                DBG1SEL4 | DBG1SEL3 | DBG1SEL2 | DBG1SEL1 | DBG1SEL0	// Servo related signals

#define GPA1_DBG_Conf                  (GPA1_DISABLE)						// GPA1 signal selection

// GPB0  DBG2 signal configuration
#define GPB0_DISABLE					0x00				                                    // Disable DBG signal of GP01
#define GPB0_ADCTrigger					DBG2SEL0				                                // ADC trigger signal
#define GPB0_ADC2Trigger		        DBG2SEL1				                                // ADC2 trigger signal
#define GPB0_PFCTrigger					DBG2SEL1 | DBG2SEL0					                    // ADC3 trigger signal
#define GPB0_CMP012_SAM_ON				DBG2SEL2												// ON sampling window of CMP012
#define GPB0_CMP012_SAM_OFF				DBG2SEL2 | DBG2SEL0										// OFF sampling window of CMP012
#define GPB0_CMP678_SAM_ON				DBG2SEL2 | DBG2SEL1										// ON sampling window of CMP678
#define GPB0_CMP678_SAM_OFF				DBG2SEL2 | DBG2SEL1 | DBG2SEL0							// OFF sampling window of CMP678
#define GPB0_CMP123_SAM_ONOFF			DBG2SEL3												// ON/OFF sampling window of CMP012
#define GPB0_CMP678_SAM_ONOFF			DBG2SEL3 | DBG2SEL0										// ON/OFF sampling window of CMP678
#define GPB0_ME_BUSY			        DBG2SEL3 | DBG2SEL2										// FOC1 and FOC2 calculation status
#define GPB0_CUR_LP_BUSY		        DBG2SEL3 | DBG2SEL2 | DBG2SEL0							// Current loop calculation status
#define GPB0_FOC2_BUSY			        DBG2SEL3 | DBG2SEL2 | DBG2SEL1							// FOC2 calculation status
#define GPB0_DRV_CNTR_DIR1		        DBG2SEL4			                       				// DIVER1 counting direction
#define GPB0_OVERFLOW1	                DBG2SEL4 | DBG2SEL0										// DIVER1 overflow point
#define GPB0_UNDERFLOW1					DBG2SEL4 | DBG2SEL1										// DIVER1 underflow point
#define GPB0_OMEGA_STA_FLAG1			DBG2SEL4 | DBG2SEL1 | DBG2SEL0							// OMEGA1 startup status
#define GPB0_HFI_ST1	                DBG2SEL4 | DBG2SEL2										// High frequency injection related signal 1
#define GPB0_WPI_CAL1	                DBG2SEL4 | DBG2SEL2 | DBG2SEL0							// Outer loop calculation status 1
#define GPB0_MMT_CAL1	                DBG2SEL4 | DBG2SEL2 | DBG2SEL1							// Servo related signals
#define GPB0_SF_CAL1	                DBG2SEL4 | DBG2SEL2 | DBG2SEL1 | DBG2SEL0				// Servo related signals
#define GPB0_DRV_CNTR_DIR2		        DBG2SEL4 | DBG2SEL3										// DIVER2 counting direction
#define GPB0_OVERFLOW2	                DBG2SEL4 | DBG2SEL3 | DBG2SEL0							// DIVER2 overflow point
#define GPB0_UNDERFLOW2					DBG2SEL4 | DBG2SEL3 | DBG2SEL1							// DIVER2 underflow point
#define GPB0_OMEGA_STA_FLAG2			DBG2SEL4 | DBG2SEL3 | DBG2SEL1 | DBG2SEL0				// OMEGA2 startup status
#define GPB0_HFI_ST2	                DBG2SEL4 | DBG2SEL3 | DBG2SEL2							// High frequency injection related signal 2
#define GPB0_WPI_CAL2	                DBG2SEL4 | DBG2SEL3 | DBG2SEL2 | DBG2SEL0				// Outer loop calculation status 2
#define GPB0_MMT_CAL2	                DBG2SEL4 | DBG2SEL3 | DBG2SEL2 | DBG2SEL1				// Servo related signals
#define GPB0_SF_CAL2	                DBG2SEL4 | DBG2SEL3 | DBG2SEL2 | DBG2SEL1 | DBG2SEL0	// Servo related signals

#define GPB0_DBG_Conf                  (GPB0_DISABLE)											// GPB0 signal selection

// GPAx CMP output signal configuration
#define GPAx_DISABLE					0x00														// Disable comparator signal output of GPAx
#define GPAx_CMP0_SAM					CMPSEL0					                                // Sampling result of CMP0_OUT
#define GPAx_CMP1_SAM					CMPSEL1					                                // Sampling result of CMP1_OUT
#define GPAx_CMP2_SAM					CMPSEL1 | CMPSEL0				                        // Sampling result of CMP2_OUT
#define GPAx_CMP3_FLT					CMPSEL2					                                // Filtered signal (sampling result) of CMP3_OUT
#define GPAx_CMP4_FLT					CMPSEL2 | CMPSEL0				                        // Filtered signal (sampling result) of CMP4_OUT
#define GPAx_CMP5_FLT					CMPSEL2 | CMPSEL1				                        // Filtered signal (sampling result) of CMP5_OUT
#define GPAx_CMP6_SAM					CMPSEL2 | CMPSEL1 | CMPSEL0					            // Sampling result of CMP6_OUT
#define GPAx_CMP7_SAM					CMPSEL3										            // Sampling result of CMP7_OUT
#define GPAx_CMP8_SAM					CMPSEL3 | CMPSEL0										// Sampling result of CMP8_OUT
#define GPAx_CMP9_FLT					CMPSEL3 | CMPSEL1										// Filtered signal (sampling result) of CMP9_OUT
#define GPAx_CMP10_FLT					CMPSEL3 | CMPSEL1 | CMPSEL0								// Filtered signal (sampling result) of CMP10_OUT
#define GPAx_CMP11_FLT					CMPSEL3 | CMPSEL2										// Filtered signal (sampling result) of CMP11_OUT
#define GPAx_CMP0_OUT					CMPSEL4 | CMPSEL0		                                // Raw signal of CMP0_OUT
#define GPAx_CMP1_OUT					CMPSEL4 | CMPSEL1		                                // Raw signal of CMP1_OUT
#define GPAx_CMP2_OUT					CMPSEL4 | CMPSEL1 | CMPSEL0		                        // Raw signal of CMP2_OUT
#define GPAx_CMP3_OUT					CMPSEL4 | CMPSEL2				                        // Raw signal of CMP3_OUT
#define GPAx_CMP4_OUT					CMPSEL4 | CMPSEL2 | CMPSEL0								// Raw signal of CMP4_OUT
#define GPAx_CMP5_OUT					CMPSEL4 | CMPSEL2 | CMPSEL1								// Raw signal of CMP5_OUT
#define GPAx_CMP6_OUT					CMPSEL4 | CMPSEL2 | CMPSEL1 | CMPSEL0		            // Raw signal of CMP6_OUT
#define GPAx_CMP7_OUT					CMPSEL4 | CMPSEL3										// Raw signal of CMP7_OUT
#define GPAx_CMP8_OUT					CMPSEL4 | CMPSEL3 | CMPSEL0								// Raw signal of CMP8_OUT
#define GPAx_CMP9_OUT					CMPSEL4 | CMPSEL3 | CMPSEL1								// Raw signal of CMP9_OUT
#define GPAx_CMP10_OUT					CMPSEL4 | CMPSEL3 | CMPSEL1 | CMPSEL0					// Raw signal of CMP10_OUT
#define GPAx_CMP11_OUT					CMPSEL4 | CMPSEL3 | CMPSEL2								// Raw signal of CMP11_OUT
// #define GPAx_CMPOX                     CMPSEL2 | CMPSEL1 | CMPSEL0				            // Output ADC result comparison signal (BLDC) Omega startup status (FOC)

#define GPAx_DBG_Conf                  (GPAx_DISABLE)					                        // GPAx signal selection


#if TEST_SPIDEBUG_SW_ENABLED
extern unsigned short spidebug[4];
#endif


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