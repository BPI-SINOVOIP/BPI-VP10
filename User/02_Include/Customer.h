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


/*************************固件版本*****************************************/
#define FIRMWAREVERSION_I				(2026051418)


/*************************芯片参数值*****************************************/
/*CPU and PWM Parameter*/
#define FREQ_24M						(24)                                     
#define FREQ_48M						(48)                                     
#define MCU_CLOCK						(FREQ_48M)                               // (MHz) 主频

#define PWM_FREQUENCY					(16)                                     // (kHz) PWM载波频率

/*子模块工作频率*/
#define DRIVERINT_FREQUENCY				((uint16)PWM_FREQUENCY << DRV32K_ENABLE_SWITCH)				// 载波中断频率
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
#define MAXFREQOUT						(uint16)(MCU_CLOCK * 1000 / ENCOUT_FREQUENCY) // (count) 最大分频脉冲输出

#define ENCABS_TS						(uint16)(MCU_CLOCK * 1000 / PWM_FREQUENCY) // (count) ABS Encoder update period

#define ENCCOMP_SHIFT					(30) 
#define CURFILE_TIMES					(uint32)(1000 / CURCTRL_FREQUENCY)            // 单位：us
#define ELEANG_DELAYTS					(uint32)(0.2f * CURFILE_TIMES)               // ABZ编码器延时1.5Ts
#define BISS_DELAYTS					(63)

#define PWM_CYCLE						(1000.0 / PWM_FREQUENCY)                      // 周期us
#define PWM_VALUE_LOAD					(uint16)(MCU_CLOCK * 500 / PWM_FREQUENCY)     // PWM 定时器重载值

#define PWM_OFFSET						(uint16)(MCU_CLOCK * 6)						  // 进载波中断比电流采样提前的时间, us
#define PWM_VALUE_DOWNLOAD				(PWM_OFFSET)
#define PWM_VALUE_UPLOAD				(PWM_VALUE_LOAD - PWM_OFFSET)


/*deadtime Parameter*/
#define PWM_DEADTIME					(0.8)										// (us) 死区时间
#define DT_TIME                         (0.0)										// 死区补偿时间(us)，适用于双电阻和三电阻，建议值是1/2死区时间

#define PWM_LOAD_DEADTIME				(uint16)(PWM_DEADTIME * MCU_CLOCK)             // 死区设置值
#define PWM_DT_LOAD                     (uint32)(65535.0 * DT_TIME / PWM_CYCLE / 16)       // 死区补偿值


/*************************PCB板硬件参数*****************************************/
/* 驱动芯片类型 */
#define HIGH_LEVEL						(0)                                     // 驱动高电平有效
#define LOW_LEVEL						(1)                                     // 驱动低电平有效
#define UP_H_DOWN_L						(2)                                     // 上桥臂高电平有效，下桥臂低电平有效
#define UP_L_DOWN_H						(3)                                     // 上桥臂低电平有效，下桥臂高电平有效
#if (HARDWARE_VERSION == HARDWARE_LOWVOL_ARM_SWITCH) // FD6187
#define HW_PWM_LEVEL_MODE				(UP_H_DOWN_L)
#define HW_PWM_IDLELEVEL				(0x2A)
#else // FD6288
#define HW_PWM_LEVEL_MODE				(HIGH_LEVEL)
#define HW_PWM_IDLELEVEL				(0x00)
#endif


/* UVW上下管极性 */
#define UVWPOL_NORMAL                   (0xA0)									// 正常
#define UVWPOL_INVERT					(0xB0)									// 取反
#if (HARDWARE_VERSION == HARDWARE_HIGHVOL_SWITCH)
#define HW_UVW_POLARITY                 (UVWPOL_INVERT)
#else
#define HW_UVW_POLARITY					(UVWPOL_NORMAL)
#endif


/* SVPWM mode */
#define SVPWM_5_SEGMENT                 (0xA0)									// 五段式SVPWM
#define SVPWM_7_SEGMENT					(0xB0)									// 七段式SVPWM
#define HW_SVPWM_MODE                   (SVPWM_7_SEGMENT)


/* 电流采样模式 */
#define SINGLE_RESISTOR					(0)										// 单电阻电流采样模式
#define DOUBLE_RESISTOR					(1)										// 双电阻电流采样模式
#define THREE_RESISTOR					(2)										// 三电阻电流采样模式
#define SINGLE_RESISTOR_NEW				(3)										// 单电阻电流采样模式
#define HW_ADC_RESISTOR_MODE			(DOUBLE_RESISTOR)


/* 双ADC同时采样 */
#define ADCSAM_SYNC                     (0xA0)									// 双ADC同时采样
#define ADCSAM_ASYNC                    (0xB0)									// 双ADC先后采样
#if (HARDWARE_VERSION == HARDWARE_FPGA_HIGHVOL_SWITCH || HARDWARE_VERSION == HARDWARE_FPGA_LOWVOL_SWITCH)
#define HW_ADC_SYNC                     (ADCSAM_ASYNC)
#else
#define HW_ADC_SYNC						(ADCSAM_SYNC)
#endif


/* 电流采样偏置校正 */
#define CALIB_POWUP						(0)										// 上电校准
#define CALIB_START						(1)										// 启动校准
#define HW_ADC_CALIB_MODE				(CALIB_POWUP)


/* ADC参考电压配置 */
#define VREF3_0                         (0xA0)									// 参考电压设置为3.0V
#define VREF4_0                         (0xB0)									// 参考电压设置为4.0V
#define VREF4_5                         (0xC0)									// 参考电压设置为4.5V
#define VREF5_0                         (0xD0)									// 参考电压设置为5.0V
#define HW_ADC_VREF						(VREF5_0)								// (V) ADC参考电压


/* 运放选择 */
#define AMP_ONCHIP                      (0xA0)									// 外部运放
#define AMP_OUTSIDE						(0xB0)									// 内部运放
#if (HARDWARE_VERSION == HARDWARE_FPGA_HIGHVOL_SWITCH || HARDWARE_VERSION == HARDWARE_FPGA_LOWVOL_SWITCH)
#define HW_AMP_SEL                      (AMP_OUTSIDE)
#else
#define HW_AMP_SEL						(AMP_ONCHIP)
#endif

/* 运放放大模式选择 */
#define AMP_NOMAL                       (0xA0)									// 外部放大
#define AMP_PGA_DUAL                    (0xB0)									// 内部PGA 双端差分输入
#if (HARDWARE_VERSION == HARDWARE_LOWVOL_ARM_SWITCH)
#define HW_AMP_MODE                     (AMP_PGA_DUAL)
#else
#define HW_AMP_MODE                     (AMP_NOMAL)
#endif


/* 内部PGA放大倍数选择 */
#define AMP4x                           (4)
#define AMP8x                           (8)
#define AMP16x                          (16)
#define AMP20x                          (20)
#define HW_AMP_GAIN                     (AMP8x) 


/* 基准电压VREF对外输出使能 */
#define VREF_OUT_EN                     (1)									   // 基准电压VREF对外输出使能


/* VHALF输出使能 */
#if (HARDWARE_VERSION == HARDWARE_HIGHVOL_SWITCH)
#define VHALF_OUT_EN                    (0)									   // VHALF不输出
#else
#define VHALF_OUT_EN                    (1)									   // VHALF输出使能
#endif


/* 硬件过流保护方式 */
#define Hardware_FO_Protect				(1)                                     // 硬件FO过流保护使能，适用于IPM有FO保护的场合
#define Hardware_CMP_Protect			(2)                                     // 硬件CMP比较过流保护使能，适用于MOS管应用场合
#define Hardware_FO_CMP_Protect			(3)                                     // 硬件CMP比较和FO过流保护都使能
#define Hardware_Protect_Disable		(4)                                     // 硬件过流保护禁止，用于测试
#if (HARDWARE_VERSION == HARDWARE_FPGA_HIGHVOL_SWITCH || HARDWARE_VERSION == HARDWARE_HIGHVOL_SWITCH)
#define HardwareCurrent_Protect			(Hardware_FO_Protect)				   // 硬件过流保护实现方式
#else
#define HardwareCurrent_Protect			(Hardware_CMP_Protect)				   // 硬件过流保护实现方式
#endif


/* 硬件过流FO外部中断来源 */
#define Hardware_FO_EXTI0				(0)                                    // 外部中断0
#define Hardware_FO_EXTI2				(2)                                    // 外部中断2
#if (HARDWARE_VERSION == HARDWARE_HIGHVOL_SWITCH)
#define Hardware_FO_SRC					(Hardware_FO_EXTI2)
#else
#define Hardware_FO_SRC					(Hardware_FO_EXTI0)
#endif


/* 硬件过流保护比较值来源 */
#define Compare_DAC						(0)                                     // DAC设置硬件过流值
#define Compare_Hardware				(1)                                     // 硬件设置硬件过流值
#define Compare_Source					(Compare_DAC)                      	    // 硬件过流值的来源


/* 硬件过流保护比较器输入模式选择 */
#define Single_Input					(0)                                     // 单比较器输入模式
#define Double_Input					(1)                                     // 双比较器输入模式
#define Three_Input						(2)                                     // 双比较器输入模式
#define Compare_InputMode				(Single_Input)                      	// 硬件过流保护比较器输入模式选择


/*ITRIP&POWER计算模式*/
#define DIS_IT_POW						(0)                                   // 不计算IT、POW
#define EX_IT_POW						(1)                                   // 外部得到itrip，计算POW
#define IN_IT_POW						(2)                                   // 内部计算itrip=us*is，计算POW
#define IS_IT_POW						(3)                                   // 内部计算itrip=is，计算POW
#define IT_POW_MD						(IS_IT_POW)


/* SPI编码器类型选择 */
#define ENCSPI_KTH						(0)                                     // 昆泰芯
#define ENCSPI_MT						(1)                                     // 麦歌恩
#if (HARDWARE_VERSION == HARDWARE_LOWVOL_ARM_SWITCH)
#define ENCSPI_Source					(ENCSPI_KTH)                            // SPI1的编码器类型
#define ENCSPI2_Source					(ENCSPI_KTH)                            // SPI2的编码器类型
#else
#define ENCSPI_Source					(ENCSPI_MT)                             // SPI1的编码器类型
#define ENCSPI2_Source					(ENCSPI_KTH)                            // SPI2的编码器类型
#endif


/*CAN通信类型*/
#define CANSPEC_LITTLE_ENDIAN			(0)		                             // 小端
#define CANSPEC_BIG_ENDIAN				(1)									 // 大端
#if (HARDWARE_VERSION == HARDWARE_LOWVOL_ARM_SWITCH)
#define CANSPEC_ENDIAN					(CANSPEC_LITTLE_ENDIAN)
#else
#define CANSPEC_ENDIAN					(CANSPEC_BIG_ENDIAN)
#endif


/*************************一些常量定义*****************************************/
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

/*再生制动占空比设置*/
#define MAXREGENDUTY					(16384)

/*上电等待时间*/
#define SYSTEM_POWERUP_TIME				(200)       // 上电等待时间，ms

/*预充电时间*/
#define CHARGE_TIME                     (300)       // (ms) 下桥预充电时间

/*数学常量*/
#define _PI                             (3.1415926)
#define _2PI                            (3.1415926*2.0)


/* Unit Conversion ---------------------------------------------------------------------------------*/
#define I_Value(Value)					(Value * usSRegHoldBuf[CURCOE]) // (A) -> count
#define Vol_Value(Value)				(((int32)(Value * usSRegHoldBuf[VOLGAIN]) / usSRegHoldBuf[VOLDEN]) + usSRegHoldBuf[VOLOFFSET]) // (V) -> count
#define Spd_Value(Value)				(((int32)Value << 14) / usSRegHoldBuf[MOTORMAXSPEED]) // (mm/s) -> count

#endif
