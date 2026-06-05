/*
 * Copyright (c) 2021-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : Parameter.h
 * Author        : Summer
 * Date          : 2021-11-13
 * Description   : This file contains all Servo Controller Configuration Defines.
 *
 * Record        :
 * V1.0, 2021-11-13, Summer: Created file
 */


#ifndef __PARAMETER_H_
#define __PARAMETER_H_

/*-----------------------------------------------------------------------------------------
------
------	Servo Controller Configuration Defines
------
-----------------------------------------------------------------------------------------*/
/* 硬件平台选择开关--------------------------------------------------------------------*/
#define HARDWARE_HIGHVOL_SWITCH					( 5 )
#define HARDWARE_LOWVOL_SWITCH					( 6 ) // 通用低压板
#define HARDWARE_FPGA_HIGHVOL_SWITCH			( 7 )
#define HARDWARE_FPGA_LOWVOL_SWITCH				( 8 )
#define HARDWARE_LOWVOL_ARM_SWITCH				( 9 )  // 机器人手臂电机
#define HARDWARE_LOWVOL_DELTAROBOT_SWITCH		( 11 ) // 蜘蛛手

/*! \brief Hardware select version */
#define HARDWARE_VERSION						(HARDWARE_LOWVOL_DELTAROBOT_SWITCH)


/* 功能开关--------------------------------------------------------------------*/
/*! \brief If motor current double sample is enabled. 电流双采样功能开关 */
#define DOUBLESAMP_ENABLE_SWITCH				( 0 & (HARDWARE_VERSION == HARDWARE_FPGA_HIGHVOL_SWITCH || HARDWARE_VERSION == HARDWARE_HIGHVOL_SWITCH))

/*! \brief If 32kHz driver Interrupt is enabled. */
#define DRV32K_ENABLE_SWITCH					( 1 & DOUBLESAMP_ENABLE_SWITCH)

/*! \brief If Voice coil motor is supported. */
#define MOTOR_VCM_ENABLED						( 0 )


/* ----------------------- External controller ------------------------------------------*/
/*! \brief If EtherCAT is enabled. */
#define EXCTRL_ECAT_ENABLED						( 0 )
	
/*! \brief If CanOpen is enabled. */
#define EXCTRL_CANOPEN_ENABLED					( 0 & (1 - EXCTRL_ECAT_ENABLED) )

/*! \brief If Pulse and Direction is enabled. */
#define EXCTRL_PULSE_ENABLED					( 1 )

/*! \brief If Analog Input is enabled. */
#define EXCTRL_ANALOG_ENABLED					( 1 & (1 - FUNC_FORCECTRL_ENABLED) )

/*! \brief If Encoder output is enabled. */
#define EXCTRL_ENCOUT_ENABLED					( 0 )


/* ----------------------- Communication ------------------------------------------*/
/*! \brief If connect with ServoStudio using UART is enabled. */
#define COMM_UART_ENABLED						( 1 )

/*! \brief If connect with ServoStudio using CAN is enabled. */
#define COMM_CAN_ENABLED						( 0 )

/*! \brief If CAN Slave PDO support is enabled. */
#define COMM_CAN_PDO_ENABLED                    ( 0 & COMM_CAN_ENABLED )

/*! \brief If connect with ServoStudio using CAN is enabled. */
#define COMM_UART_RS485_ENABLED					(HARDWARE_VERSION == HARDWARE_LOWVOL_DELTAROBOT_SWITCH)


/* ----------------------- Encoder ------------------------------------------*/
/*! \brief If A Qaud B is enabled. */
#define ENCODER_SEL_ABZ_ENABLED					( 1 )

/*! \brief If Hall encoder is enabled. */
#define ENCODER_SEL_HALL_ENABLED				( 1 )

/*! \brief If TMG encoder is enabled. */
#define ENCODER_SEL_TMG_ENABLED					( 1 )

/*! \brief If BiSS encoder is enabled. */
#define ENCODER_SEL_BISS_ENABLED				( 1 )

/*! \brief If SPI encoder is enabled. */
#define ENCODER_SEL_SPI_ENABLED					( 0 )

/*! \brief If SPI2 encoder is enabled. */
#define ENCODER_SEL_SPI2_ENABLED				( 0 )

/*! \brief If PWM encoder is enabled. */
#define ENCODER_SEL_PWM_ENABLED					( 0 )

/*! \brief If Halls-Only encoder is enabled. not work. */
#define ENCODER_SEL_HALLSONLY_ENABLED			( 0 & ENCODER_SEL_HALL_ENABLED)

/*! \brief If encoder calibration is enabled. */
#define ENCODER_CALIBRATE_ENABLED				( 0 )


/* ----------------------- EtherCAT Function ------------------------------------------*/
/*! \brief If EtherCAT Home is enabled. */
#define ECAT_HOME_ENABLED						( 1 & EXCTRL_ECAT_ENABLED & FUNC_HOME_ENABLED )

/*! \brief If EtherCAT Touch Probe is enabled. */
#define ECAT_PROBE_ENABLED						( 1 & EXCTRL_ECAT_ENABLED & FUNC_PROBE_ENABLED )


/* ----------------------- Hardware Peripheral Function ------------------------------------------*/
/*! \brief If EEPROM save error history and parameter table is enabled. */
#define FUNC_EEPROM_ENABLED						( 1 )

/*! \brief If SOFT_EEPROM save error history and parameter table is enabled. */
#define FUNC_SOFT_EEPROM_ENABLED				( 0 & FUNC_EEPROM_ENABLED )

/*! \brief If EEPROM size is 1Kbit to 16 Kbit. */
#define FUNC_EEPROM_24C16B_SWITCH				(HARDWARE_VERSION != HARDWARE_FPGA_HIGHVOL_SWITCH && HARDWARE_VERSION != HARDWARE_FPGA_LOWVOL_SWITCH)

/*! \brief If LED digital tube is enabled. 数码管显示 */
#define FUNC_LED_TUBE_ENABLED					( 0 )

/*! \brief If LED diode is enabled. */
#define FUNC_LED_DIODE_ENABLED					( 1 )

/*! \brief If STO is enabled. */
#define FUNC_STO_ENABLED						(HARDWARE_VERSION == HARDWARE_FPGA_HIGHVOL_SWITCH || HARDWARE_VERSION == HARDWARE_HIGHVOL_SWITCH)

/*! \brief If regeneration is enabled. */
#define FUNC_REGENERATION_ENABLED				( 0 )

/*! \brief If Touch Probe 1 is enabled. */
#define FUNC_PROBE1_ENABLED						( 0 )

/*! \brief If both Touch 2 Input is enabled. */
#define FUNC_PROBE2_ENABLED						( 0 )

/*! \brief If Position Compare Output is enabled. */
#define FUNC_PCOM_ENABLED						( 0 )


/* ----------------------- Software Function ------------------------------------------*/
/*! \brief If home is enabled. */
#define FUNC_HOME_ENABLED						( 1 )

/*! \brief If inertia estimation is enabled. */
#define FUNC_INERTIA_ENABLED					( 0 )

/*! \brief If motor parameter estimation is enabled. */
#define FUNC_MOTOREST_ENABLED					( 0 )

/*! \brief If current loop tuning is enabled. */
#define FUNC_CURTUNE_ENABLED					( 0 )

/*! \brief If Sweep analysis is enabled. */
#define FUNC_SWEEP_ENABLED						( 0 )

/*! \brief If gain switch is enabled. */
#define FUNC_GAINSW_ENABLED						( 0 )

/*! \brief If vibration suppression is enabled. */
#define FUNC_NTF_ENABLED						( 0 )

/*! \brief If position input filter is enabled. */
#define FUNC_INPUTFILT_ENABLED					( 1 )

/*! \brief If dual position feedback filter is enabled. */
#define FUNC_DUALFILT_POSREF					( 1 )

/*! \brief If Speed Feedforward is enabled. */
#define FUNC_SPDFF_ENABLED						( 1 )

/*! \brief If Torque Feedforward is enabled. */
#define FUNC_TOQFF_ENABLED						( 1 )

/*! \brief If Force Control is enabled. */
#define FUNC_FORCECTRL_ENABLED					( 0 )

/*! \brief If Closed Loop Force Control is enabled. */
#define FUNC_FORCECLOSEDLOOP_ENABLED			( 0 & FUNC_FORCECTRL_ENABLED)

/*! \brief If Elec Screw Control is enabled. */
#define SPECIAL_ELESCREW_ENABLE                 ( 0 & (1 - FUNC_FORCECTRL_ENABLED) )

/*! \brief If Friction Compensation is enabled. */
#define FUNC_FRICOMP_ENABLED					( 0 )

/*! \brief If High Function Mode is enabled. */
#define FUNC_HIGHMODE_ENABLED				    ( 0 )

/*! \brief If Duty Cycle Update Now is enabled. */
#define FUNC_DUTYUPDATENOW_ENABLED				( 0 | FUNC_HIGHMODE_ENABLED)

/*! \brief If Deadtime compensation is enabled. */
#define DEADTIME_COMPENSATE_ENABLED				( 0 )

/*! \brief If Encoder Comp is enabled. */
#define FUNC_ENCODERCOMP_ENABLED				( 1 )

/*! \brief If FeedBack On Load is enabled. */
#define FUNC_FEEDBACKONLOAD_ENABLED				( 0 )

/*! \brief If FieldWeaken On Load is enabled. */
#define FUNC_FIELDWEAKEN_ENABLED				( 0 & (1 - MOTOR_VCM_ENABLED))
	
/*! \brief If Disable mode is enabled. */
#define FUNC_DISMODE_ENABLED					( 0 )

/*! \brief If Error_Correction is enabled. */
#define FUNC_ERRORCORRECTION_ENABLED			( 0 )

/*! \brief If Soft Control is enabled. */
#define FUNC_SOFTCTRL_ENABLED					( 0 )

/*! \brief If CurrentBack Protect is enabled. */
#define FUNC_CURRENTBACK_ENABLED				( 0 )

/*! \brief If Gantry Control is enabled. */
#define FUNC_GANTRY_ENABLED				        ( 0 )

/* ----------------------- Test Function ------------------------------------------*/
/*! \brief If Current open loop is enabled. */
#define OPENLOOP_ENABLE_TEST					( 0 )

/*! \brief If TEST_PIN output is enabled. */
#define TESTPIN_ENABLED							( 0 )

/*! \brief If debug using UART is enabled. */
#define DEBUG_UART_ENABLED						( 0 & (1 - COMM_UART_ENABLED) )

/*! \brief If Signal Debug is enabled. */
#define TEST_SIGNALDEBUG_ENABLED				( 0 & (1 - (FUNC_LED_TUBE_ENABLED || FUNC_EEPROM_ENABLED)) )

/*! \brief If SPI debug SW is enabled. */
#define TEST_SPIDEBUG_SW_ENABLED				( 0 & (1 - FUNC_REGENERATION_ENABLED) )

/*! \brief If SPI debug HW is enabled. */
#define TEST_SPIDEBUG_HW_ENABLED				( 0 & (1 - FUNC_REGENERATION_ENABLED) )


/* ----------------------- Hardware Configuration ------------------------------------------*/
/*! \brief If precharge is needed before sampling current is enabled. 预充电*/
#define MOTOR_PRECHARGE_ENABLED					(HARDWARE_VERSION == HARDWARE_HIGHVOL_SWITCH)

/*! \brief If Temperature source is KNTC0603. 驱动器/主控NTC温度测量*/
#define TEMPSRC_KNTC_ENABLED					(HARDWARE_VERSION != HARDWARE_LOWVOL_ARM_SWITCH)

/*! \brief If using hardware to calculate IAIB offset is supported. ADC偏置计算*/
#define ADCOFFSET_HARDWARE_ENABLED				(0 & (HARDWARE_VERSION != HARDWARE_LOWVOL_DELTAROBOT_SWITCH))

#endif