/*
 * Copyright (c) 2021-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : Customer.h
 * Author        : Summer
 * Date          : 2021-11-13
 * Description   : This file contains all the common data types used for Motor Control.
 *
 * Record        :
 * V1.0, 2021-11-13, Summer: Created file
 */


/* Define to prevent recursive inclusion --------------------------------------------------------*/
#ifndef __CUSTOMER_H_
#define __CUSTOMER_H_

#include "Parameter.h"


/************************* Firmware Version *****************************************/
#define FIRMWAREVERSION_I				(2026052918)


/*************************Chip Parameter Values*****************************************/
/*CPU and PWM Parameter*/
#define FREQ_24M						(24)                                     
#define FREQ_48M						(48)                                     
#define MCU_CLOCK						(FREQ_48M)                               // (MHz) Main clock frequency

#define PWM_FREQUENCY					(16)                                     // (kHz) PWM carrier frequency

/*Submodule Operating Frequency*/
#define DRIVERINT_FREQUENCY				((uint16)PWM_FREQUENCY << DRV32K_ENABLE_SWITCH)				// Carrier interrupt frequency
#define CURCTRL_FREQUENCY				((uint16)PWM_FREQUENCY << DOUBLESAMP_ENABLE_SWITCH)			// (kHz) Curloop control frequency	16K
#define VELCTRL_FREQUENCY				((uint16)PWM_FREQUENCY >> 1)				// (kHz) Velloop control frequency	8K
#define POSCTRL_FREQUENCY				((uint16)PWM_FREQUENCY >> 2)             // (kHz) Posloop control frequency	4K
#define PROFILE_FREQUENCY				(POSCTRL_FREQUENCY * 1000)               // 4000(Hz)
#define VELFILE_FREQUENCY				(VELCTRL_FREQUENCY * 1000)               // 8000(Hz)
#define CURFILE_FREQUENCY				(DRIVERINT_FREQUENCY * 1000)             // 16000(Hz)

#define SERIAL_CURRENT_FREQUENCY		(DRIVERINT_FREQUENCY)					// (kHz) Serial Trap Current frequency
#define SERIAL_VELOCITY_FREQUENCY		(VELCTRL_FREQUENCY)						// (kHz) Serial Trap Velocity frequency
#define ANALOG_CURRENT_FREQUENCY		(DRIVERINT_FREQUENCY)					// (kHz) Analog Current frequency
#define ANALOG_VELOCITY_FREQUENCY		(DRIVERINT_FREQUENCY)					// (kHz) Analog Velocity frequency

#define SCOPE_FREQUENCY					(DRIVERINT_FREQUENCY)					// (kHz) Scope frequency
#define OUTFILT_FREQUENCY				(CURCTRL_FREQUENCY)						// (kHz) Output filter frequency
#define VELFEB_FREQUENCY				(DRIVERINT_FREQUENCY)					// (kHz) Velocity feedback filter frequency
#define POSREF_FREQUENCY				(POSCTRL_FREQUENCY)						// (kHz) Position reference filter frequency

#define ENCOUT_FREQUENCY				(VELCTRL_FREQUENCY)						// (kHz) Encoder Output Update frequency

#define VELCTRL_TS						(uint16)(MCU_CLOCK * 1000 / DRIVERINT_FREQUENCY) 
#define MAXFREQOUT						(uint16)(MCU_CLOCK * 1000 / ENCOUT_FREQUENCY) // (count) Max frequency divider pulse output

#define ENCABS_TS						(uint16)(MCU_CLOCK * 1000 / PWM_FREQUENCY) // (count) ABS Encoder update period

#define ENCCOMP_SHIFT					(30) 
#define CURFILE_TIMES					(uint32)(1000 / CURCTRL_FREQUENCY)            // Unit: us
#define ELEANG_DELAYTS					(uint32)(0.2f * CURFILE_TIMES)               // ABZ encoder delay 1.5Ts
#define BISS_DELAYTS					(63)

#define PWM_CYCLE						(1000.0 / PWM_FREQUENCY)                      // Period us
#define PWM_VALUE_LOAD					(uint16)(MCU_CLOCK * 500 / PWM_FREQUENCY)     // PWM timer reload value

#define PWM_OFFSET						(uint16)(MCU_CLOCK * 6)						  // Time advance of carrier interrupt over current sampling, us
#define PWM_VALUE_DOWNLOAD				(PWM_OFFSET)
#define PWM_VALUE_UPLOAD				(PWM_VALUE_LOAD - PWM_OFFSET)


/*deadtime Parameter*/
#define PWM_DEADTIME					(0.8)										// (us) Dead time
#define DT_TIME                         (0.0)										// Dead time compensation (us), for dual/triple resistor, recommended 1/2 dead time

#define PWM_LOAD_DEADTIME				(uint16)(PWM_DEADTIME * MCU_CLOCK)          // Dead time setting value
#define PWM_DT_LOAD                     (uint32)(65535.0 * DT_TIME / PWM_CYCLE / 16)       // Dead time compensation value


/*************************PCB Hardware Parameters*****************************************/
/* Driver chip type */
#define HIGH_LEVEL						(0)                                     // Active high drive
#define LOW_LEVEL						(1)                                     // Active low drive
#define UP_H_DOWN_L						(2)                                     // Upper arm active high, lower arm active low
#define UP_L_DOWN_H						(3)                                     // Upper arm active low, lower arm active high
#if (HARDWARE_VERSION == HARDWARE_LOWVOL_ARM_SWITCH) // FD6187
#define HW_PWM_LEVEL_MODE				(UP_H_DOWN_L)
#define HW_PWM_IDLELEVEL				(0x2A)
#else // FD6288
#define HW_PWM_LEVEL_MODE				(HIGH_LEVEL)
#define HW_PWM_IDLELEVEL				(0x00)
#endif


/* UVW upper/lower arm polarity */
#define UVWPOL_NORMAL                   (0xA0)									// Normal
#define UVWPOL_INVERT					(0xB0)									// Inverted
#if (HARDWARE_VERSION == HARDWARE_HIGHVOL_SWITCH)
#define HW_UVW_POLARITY                 (UVWPOL_INVERT)
#else
#define HW_UVW_POLARITY					(UVWPOL_NORMAL)
#endif


/* SVPWM mode */
#define SVPWM_5_SEGMENT                 (0xA0)									// 5-segment SVPWM
#define SVPWM_7_SEGMENT					(0xB0)									// 7-segment SVPWM
#define HW_SVPWM_MODE                   (SVPWM_7_SEGMENT)


/* Current sampling mode */
#define SINGLE_RESISTOR					(0)										// Single-resistor Current sampling mode
#define DOUBLE_RESISTOR					(1)										// Dual-resistor Current sampling mode
#define THREE_RESISTOR					(2)										// Triple-resistor Current sampling mode
#define SINGLE_RESISTOR_NEW				(3)										// Single-resistor Current sampling mode
#define HW_ADC_RESISTOR_MODE			(DOUBLE_RESISTOR)


/* Dual ADC simultaneous sampling */
#define ADCSAM_SYNC                     (0xA0)									// Dual ADC simultaneous sampling
#define ADCSAM_ASYNC                    (0xB0)									// Dual ADC sequential sampling
#if (HARDWARE_VERSION == HARDWARE_FPGA_HIGHVOL_SWITCH || HARDWARE_VERSION == HARDWARE_FPGA_LOWVOL_SWITCH)
#define HW_ADC_SYNC                     (ADCSAM_ASYNC)
#else
#define HW_ADC_SYNC						(ADCSAM_SYNC)
#endif


/* Current sampling offset calibration */
#define CALIB_POWUP						(0)										// Power-up calibration
#define CALIB_START						(1)										// Startup calibration
#define HW_ADC_CALIB_MODE				(CALIB_POWUP)


/* ADC reference voltage configuration */
#define VREF3_0                         (0xA0)									// Reference voltage set to 3.0V
#define VREF4_0                         (0xB0)									// Reference voltage set to 4.0V
#define VREF4_5                         (0xC0)									// Reference voltage set to 4.5V
#define VREF5_0                         (0xD0)									// Reference voltage set to 5.0V
#define HW_ADC_VREF						(VREF5_0)								// (V) ADC reference voltage


/* Op-amp selection */
#define AMP_ONCHIP                      (0xA0)									// External op-amp
#define AMP_OUTSIDE						(0xB0)									// Internal op-amp
#if (HARDWARE_VERSION == HARDWARE_FPGA_HIGHVOL_SWITCH || HARDWARE_VERSION == HARDWARE_FPGA_LOWVOL_SWITCH)
#define HW_AMP_SEL                      (AMP_OUTSIDE)
#else
#define HW_AMP_SEL						(AMP_ONCHIP)
#endif


/* Op-amp gain mode selection */
#define AMP_NOMAL                       (0xA0)									// External amplification
#define AMP_PGA_DUAL                    (0xB0)									// Internal PGA dual-ended differential input
#if (HARDWARE_VERSION == HARDWARE_LOWVOL_ARM_SWITCH)
#define HW_AMP_MODE                     (AMP_PGA_DUAL)
#else
#define HW_AMP_MODE                     (AMP_NOMAL)
#endif


/* Internal PGA gain selection */
#define AMP4x                           (4)
#define AMP8x                           (8)
#define AMP16x                          (16)
#define AMP20x                          (20)
#define HW_AMP_GAIN                     (AMP8x) 


/* VREF output enable */
#define VREF_OUT_EN                     (1)									   // VREF output enable


/* VHALF output enable */
#if (HARDWARE_VERSION == HARDWARE_HIGHVOL_SWITCH)
#define VHALF_OUT_EN                    (0)									   // VHALF output disabled
#else
#define VHALF_OUT_EN                    (1)									   // VHALF output enable
#endif


/* Hardware overcurrent protection mode */
#define Hardware_FO_Protect				(1)                                     // Hardware FO overcurrent protection, for IPM with FO
#define Hardware_CMP_Protect			(2)                                     // Hardware CMP overcurrent protection, for MOSFET
#define Hardware_FO_CMP_Protect			(3)										// Both CMP and FO hardware overcurrent protection enabled
#define Hardware_Protect_Disable		(4)										// Hardware overcurrent protection disabled, for testing
#if (HARDWARE_VERSION == HARDWARE_FPGA_HIGHVOL_SWITCH || HARDWARE_VERSION == HARDWARE_HIGHVOL_SWITCH)
#define HardwareCurrent_Protect			(Hardware_FO_Protect)				   // Hardware overcurrent protection implementation
#else
#define HardwareCurrent_Protect			(Hardware_CMP_Protect)				   // Hardware overcurrent protection implementation
#endif


/* Hardware FO external interrupt source */
#define Hardware_FO_EXTI0				(0)                                    // External interrupt 0
#define Hardware_FO_EXTI2				(2)                                    // External interrupt 2
#if (HARDWARE_VERSION == HARDWARE_HIGHVOL_SWITCH)
#define Hardware_FO_SRC					(Hardware_FO_EXTI2)
#else
#define Hardware_FO_SRC					(Hardware_FO_EXTI0)
#endif


/* Hardware overcurrent compare value source */
#define Compare_DAC						(0)                                     // DAC sets hardware overcurrent threshold
#define Compare_Hardware				(1)                                     // Hardware sets overcurrent threshold
#define Compare_Source					(Compare_DAC)                      	    // Source of hardware overcurrent threshold


/* Hardware overcurrent comparator input mode selection */
#define Single_Input					(0)                                     // Single comparator input mode
#define Double_Input					(1)                                     // Dual comparator input mode
#define Three_Input						(2)                                     // Dual comparator input mode
#define Compare_InputMode				(Single_Input)                      	// Hardware overcurrent comparator input mode selection


/*ITRIP & POWER calculation mode*/
#define DIS_IT_POW						(0)                                   // Do not calculate IT, POW
#define EX_IT_POW						(1)                                   // External itrip, calculate POW
#define IN_IT_POW						(2)                                   // Internal itrip=us*is, calculate POW
#define IS_IT_POW						(3)                                   // Internal itrip=is, calculate POW
#define IT_POW_MD						(IS_IT_POW)


/* Over-modulation */
#define OVMDL_EN						(0)									   // Over-modulation enable


/* SPI encoder type selection */
#define ENCSPI_KTH						(0)                                     // Kuntai (KTH)
#define ENCSPI_MT						(1)                                     // MagnTek (MT)
#if (HARDWARE_VERSION == HARDWARE_LOWVOL_ARM_SWITCH)
#define ENCSPI_Source					(ENCSPI_KTH)                            // SPI1 encoder type
#define ENCSPI2_Source					(ENCSPI_KTH)                            // SPI2 encoder type
#else
#define ENCSPI_Source					(ENCSPI_MT)                             // SPI1 encoder type
#define ENCSPI2_Source					(ENCSPI_KTH)                            // SPI2 encoder type
#endif


/*CAN communication type*/
#define CANSPEC_LITTLE_ENDIAN			(0)		                             // Little-endian
#define CANSPEC_BIG_ENDIAN				(1)									 // Big-endian
#if (HARDWARE_VERSION == HARDWARE_LOWVOL_ARM_SWITCH)
#define CANSPEC_ENDIAN					(CANSPEC_LITTLE_ENDIAN)
#else
#define CANSPEC_ENDIAN					(CANSPEC_BIG_ENDIAN)
#endif


/*************************Constant Definitions*****************************************/
/*motor commutation type*/
#define BRUSHLESS_MOTOR					(0)
#define VOICECOIL_MOTOR					(1)

/*Operation mode*/
#define VELSERIAL						(0)
#define VELANALOG						(1)
#define CURSERIAL						(2)
#define CURANALOG						(3)
#define PULSEDIR						(4)
#define POSSERIAL						(5)
#define COMM_ECAT						(6)			// including CANOPEN
#define FRCSERIAL						(7)
#define VELFRF							(8)
#define CURFRF							(9)
#define CURTUNE							(10)

/*Controller mode*/
#define NOMOD							(0)
#define CURMOD							(1)
#define VELMOD							(2)
#define POSMOD							(4)
#define POS_CURMOD						(5)

/*Flash Operation*/
#define FLASH_START						(0xE8E8)     // flash idle
#define FLASH_UPLOAD					(0x5A5A)     // upload parameter from flash
#define FLASH_DOWNLOAD					(0xA5A5)     // download Holding register to flash

#define FLASH_REBOOT_STEP1				(0x158A)     // reboot step1, for app to bootloader
#define FLASH_REBOOT_STEP2				(0x79E6)     // reboot step2

/*Regenerative braking duty cycle setting*/
#define MAXREGENDUTY					(16384)

/*Power-up wait time*/
#define SYSTEM_POWERUP_TIME				(200)       // Power-up wait time, ms

/*Precharge time*/
#define CHARGE_TIME                     (300)       // (ms) Lower arm precharge time

/*Math constants*/
#define _PI                             (3.1415926)
#define _2PI                            (3.1415926*2.0)


/* Unit Conversion ---------------------------------------------------------------------------------*/
#define I_Value(Value)					(Value * usSRegHoldBuf[CURCOE]) // (A) -> count
#define Vol_Value(Value)				(((int32)(Value * usSRegHoldBuf[VOLGAIN]) / usSRegHoldBuf[VOLDEN]) + usSRegHoldBuf[VOLOFFSET]) // (V) -> count
#define Spd_Value(Value)				(((int32)Value << 14) / usSRegHoldBuf[MOTORMAXSPEED]) // (mm/s) -> count

#endif
