/*
 * Copyright (c) 2022-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : GPIO.h
 * Author        : Fortior Application Team
 * Date          : 2022-09-21
 * Description   : define GPIO
 *
 * Record        :
 * V1.0, 2022-09-21, Fortior Application Team: Created file
 */

#ifndef __GPIO_H__
#define __GPIO_H__

#include "fu7502.h"
#include "Parameter.h"

/*==================================================================================================*/
/***************************************        MACRO         ***************************************/
/*==================================================================================================*/
/* 数字输入数量 */
#if (HARDWARE_VERSION == HARDWARE_LOWVOL_DELTAROBOT_SWITCH)
#define DIGITAL_INPUT_MAX				(1)
#elif(HARDWARE_VERSION == HARDWARE_LOWVOL_ARM_SWITCH)
#define DIGITAL_INPUT_MAX				(0)
#else
#define DIGITAL_INPUT_MAX				(8)
#endif

/* 数字输出数量 */
#if (HARDWARE_VERSION == HARDWARE_FPGA_HIGHVOL_SWITCH || HARDWARE_VERSION == HARDWARE_HIGHVOL_SWITCH)
#define DIGITAL_OUTPUT_MAX				(6)
#elif(HARDWARE_VERSION == HARDWARE_LOWVOL_DELTAROBOT_SWITCH)
#define DIGITAL_OUTPUT_MAX				(1)
#elif(HARDWARE_VERSION == HARDWARE_LOWVOL_ARM_SWITCH)
#define DIGITAL_OUTPUT_MAX				(2)
#else
#define DIGITAL_OUTPUT_MAX				(4)
#endif


#if (HARDWARE_VERSION == HARDWARE_FPGA_HIGHVOL_SWITCH || HARDWARE_VERSION == HARDWARE_FPGA_LOWVOL_SWITCH)
/* ------ Digital Input ------ */
#define IN1_GPIO        (PC)
#define IN1_PIN         (PIN1)
#define IN1_OE			(PC_OE)
#define IN1_PU			(PC_PU)

#define IN2_GPIO        (PC)
#define IN2_PIN         (PIN2)
#define IN2_OE			(PC_OE)
#define IN2_PU			(PC_PU)

#define IN3_GPIO        (PC)
#define IN3_PIN         (PIN4)
#define IN3_OE			(PC_OE)
#define IN3_PU			(PC_PU)

#define IN4_GPIO        (PC)
#define IN4_PIN         (PIN5)
#define IN4_OE			(PC_OE)
#define IN4_PU			(PC_PU)

#define IN5_GPIO        (PC)
#define IN5_PIN         (PIN6)
#define IN5_OE			(PC_OE)
#define IN5_PU			(PC_PU)

#define IN6_GPIO        (PC)
#define IN6_PIN         (PIN7)
#define IN6_OE			(PC_OE)
#define IN6_PU			(PC_PU)

#define IN7_GPIO        (PC)
#define IN7_PIN         (PIN8)
#define IN7_OE			(PC_OE)
#define IN7_PU			(PC_PU)

#define IN8_GPIO        (PC)
#define IN8_PIN         (PIN15)
#define IN8_OE			(PC_OE)
#define IN8_PU			(PC_PU)


/* ------ Digital Output ------ */
#define OUT1_GPIO		(PD)
#define OUT1_PIN        (PIN3)
#define OUT1_OE			(PD_OE)

#define OUT2_GPIO		(PD)
#define OUT2_PIN        (PIN4)
#define OUT2_OE			(PD_OE)

#define OUT3_GPIO		(PA)
#define OUT3_PIN        (PIN9)
#define OUT3_OE			(PA_OE)

#define OUT4_GPIO		(PA)
#define OUT4_PIN        (PIN15)
#define OUT4_OE			(PA_OE)

#define OUT5_GPIO		(PA)
#define OUT5_PIN        (PIN14)
#define OUT5_OE			(PA_OE)

#define OUT6_GPIO		(PA)
#define OUT6_PIN        (PIN13)
#define OUT6_OE			(PA_OE)


/* ------ Test Output ------ */
#define TEST_GPIO       (PB)
#define TEST_PIN        (PIN8)
#define TEST_OE			(PB_OE)

#define TEST_GPIO1      (PB)
#define TEST_PIN1       (PIN6)
#define TEST_OE1		(PB_OE)

#define TEST_GPIO2      (PB)
#define TEST_PIN2       (PIN7)
#define TEST_OE2		(PB_OE)

/* ------ Encoder Pins ------ */
#define SLRE_GPIO		(PA)
#define SLRE_PIN		(PIN12)
#define SLRE_OE			(PA_OE)
#define SLRE_PU			(PA_PU)

#define MARE_GPIO		(PC)
#define MARE_PIN		(PIN11)
#define MARE_OE			(PC_OE)
#define MARE_PU			(PC_PU)

/* ------ I2C Pins ------ */
#define SCL_GPIO		(PA)
#define SCL_PIN			(PIN1)
#define SCL_OE			(PA_OE)

/* ------ STO Pins ------ */
#define STO_GPIO        (PC)
#define STO_PIN         (PIN3)
#define STO_OE			(PC_OE)
#define STO_PU			(PC_PU)

/* ------ other Pins ------ */
#define FAN_GPIO        (PD)
#define FAN_PIN         (PIN1)
#define FAN_OE			(PD_OE)
#define FAN_PU			(PD_PU)

#define HOV_GPIO        (PD)
#define HOV_PIN         (PIN0)  // Hardware overcurrent
#define HOV_OE			(PD_OE)
#define HOV_PU			(PD_PU)

#define RELAY_GPIO      (PB)
#define RELAY_PIN       (PIN9)
#define RELAY_OE		(PB_OE)

#define ERR_GPIO        (PC)
#define ERR_PIN         (PIN13)
#define ERR_OE			(PC_OE)

#elif (HARDWARE_VERSION == HARDWARE_HIGHVOL_SWITCH)

/* ------ Digital Input ------ */
#define IN1_GPIO        (PC)
#define IN1_PIN         (PIN4)
#define IN1_OE			(PC_OE)
#define IN1_PU			(PC_PU)

#define IN2_GPIO        (PC)
#define IN2_PIN         (PIN5)
#define IN2_OE			(PC_OE)
#define IN2_PU			(PC_PU)

#define IN3_GPIO        (PC)
#define IN3_PIN         (PIN6)
#define IN3_OE			(PC_OE)
#define IN3_PU			(PC_PU)

#define IN4_GPIO        (PC)
#define IN4_PIN         (PIN7)
#define IN4_OE			(PC_OE)
#define IN4_PU			(PC_PU)

#define IN5_GPIO        (PC)
#define IN5_PIN         (PIN8)
#define IN5_OE			(PC_OE)
#define IN5_PU			(PC_PU)

#define IN6_GPIO        (PC)
#define IN6_PIN         (PIN9)
#define IN6_OE			(PC_OE)
#define IN6_PU			(PC_PU)

#define IN7_GPIO        (PA)
#define IN7_PIN         (PIN13)
#define IN7_OE			(PA_OE)
#define IN7_PU			(PA_PU)

#define IN8_GPIO        (PA)
#define IN8_PIN         (PIN14)
#define IN8_OE			(PA_OE)
#define IN8_PU			(PA_PU)


/* ------ Digital Output ------ */
#define OUT1_GPIO		(PC)
#define OUT1_PIN        (PIN1)
#define OUT1_OE			(PC_OE)

#define OUT2_GPIO		(PC)
#define OUT2_PIN        (PIN0)
#define OUT2_OE			(PC_OE)

#define OUT3_GPIO		(PD)
#define OUT3_PIN        (PIN0)
#define OUT3_OE			(PD_OE)

#define OUT4_GPIO		(PD)
#define OUT4_PIN        (PIN1)
#define OUT4_OE			(PD_OE)

#define OUT5_GPIO		(PD)
#define OUT5_PIN        (PIN3)
#define OUT5_OE			(PD_OE)

#define OUT6_GPIO		(PC)
#define OUT6_PIN        (PIN10)
#define OUT6_OE			(PC_OE)

/* ------ Test Output ------ */
#define TEST_GPIO       (PA)
#define TEST_PIN        (PIN15)
#define TEST_OE			(PA_OE)

#define TEST_GPIO1      (PC)
#define TEST_PIN1       (PIN11)
#define TEST_OE1		(PC_OE)

#define TEST_GPIO2      (PC)
#define TEST_PIN2       (PIN15)
#define TEST_OE2		(PC_OE)

/* ------ Encoder Pins ------ */
#define SLRE_GPIO		(PA)
#define SLRE_PIN		(PIN12)
#define SLRE_OE			(PA_OE)
#define SLRE_PU			(PA_PU)

#define MARE_GPIO		(PC)
#define MARE_PIN		(PIN11)
#define MARE_OE			(PC_OE)
#define MARE_PU			(PC_PU)

/* ------ I2C Pins ------ */
#define SCL_GPIO		(PA)
#define SCL_PIN			(PIN1)
#define SCL_OE			(PA_OE)

/* ------ STO Pins ------ */
#define STO_GPIO        (PC)
#define STO_PIN         (PIN3)
#define STO_OE			(PC_OE)
#define STO_PU			(PC_PU)

/* ------ other Pins ------ */
#define FAN_GPIO        (PB)
#define FAN_PIN         (PIN8)
#define FAN_OE			(PB_OE)

#define HOV_GPIO        (PC)
#define HOV_PIN         (PIN2)  // Hardware overcurrent
#define HOV_OE			(PC_OE)
#define HOV_PU			(PC_PU)

#define RELAY_GPIO      (PB)
#define RELAY_PIN       (PIN9)
#define RELAY_OE		(PB_OE)

#define ERR_GPIO        (PC)
#define ERR_PIN         (PIN13)
#define ERR_OE			(PC_OE)

#elif(HARDWARE_VERSION == HARDWARE_LOWVOL_DELTAROBOT_SWITCH)
/* ------ Digital Input ------ */
#define IN1_GPIO        (PC)
#define IN1_PIN         (PIN4)
#define IN1_OE			(PC_OE)
#define IN1_PU			(PC_PU)

/* ------ Digital Output ------ */
#define OUT1_GPIO		(PC)
#define OUT1_PIN        (PIN2)
#define OUT1_OE			(PC_OE)

/* ------ Test Output ------ */
#define TEST_GPIO       (PA)
#define TEST_PIN        (PIN13)
#define TEST_OE			(PA_OE)

#define TEST_GPIO1      (PA)
#define TEST_PIN1       (PIN14)
#define TEST_OE1		(PA_OE)

#define TEST_GPIO2      (PC)
#define TEST_PIN2       (PIN5)
#define TEST_OE2		(PC_OE)

/* ------ Encoder Pins ------ */
#define SLRE_GPIO		(PA)
#define SLRE_PIN		(PIN13)
#define SLRE_OE			(PA_OE)
#define SLRE_PU			(PA_PU)

#define MARE_GPIO		(PD)
#define MARE_PIN		(PIN6)
#define MARE_OE			(PD_OE)
#define MARE_PU			(PD_PU)

/* ------ RS485 RE Pins ------ */
#define RTSRS485_GPIO	( PC )
#define RTSRS485_PIN	( PIN15 )
#define RTSRS485_OE		( PC_OE )

/* ------ I2C Pins ------ */
#define SCL_GPIO		(PA)
#define SCL_PIN			(PIN1)
#define SCL_OE			(PA_OE)

/* ------ other Pins ------ */
#define ERR_GPIO        (PC)
#define ERR_PIN         (PIN14)
#define ERR_OE			(PC_OE)

#define PWD_GPIO        (PC)
#define PWD_PIN         (PIN13)
#define PWD_OE			(PC_OE)

#elif(HARDWARE_VERSION == HARDWARE_LOWVOL_ARM_SWITCH)
/* ------ Digital Input ------ */

/* ------ Digital Output ------ */
#define OUT1_GPIO		(PA)
#define OUT1_PIN        (PIN9)
#define OUT1_OE			(PA_OE)

#define OUT2_GPIO		(PD)
#define OUT2_PIN        (PIN0)
#define OUT2_OE			(PD_OE)

/* ------ Test Output ------ */
#define TEST_GPIO       (PC)
#define TEST_PIN        (PIN0)
#define TEST_OE			(PC_OE)

#define TEST_GPIO1      (PC)
#define TEST_PIN1       (PIN1)
#define TEST_OE1		(PC_OE)

#define TEST_GPIO2      (PC)
#define TEST_PIN2       (PIN4)
#define TEST_OE2		(PC_OE)

/* ------ CAN Pins ------ */

/* ------ Encoder Pins ------ */
#define NSS2_GPIO		(PA)
#define NSS2_PIN		(PIN13)
#define NSS2_OE			(PA_OE)
#define NSS2_PU			(PA_PU)

/* ------ I2C Pins ------ */
#define SCL_GPIO		(PA)
#define SCL_PIN			(PIN14)
#define SCL_OE			(PA_OE)

#define SDA_GPIO		(PA)
#define SDA_PIN			(PIN15)
#define SDA_OE			(PA_OE)
#define SDA_PU			(PA_PU)

/* ------ CAN Pins ------ */
#define CANTX_GPIO		(PA)
#define CANTX_PIN       (PIN0)

#else // if(HARDWARE_VERSION == HARDWARE_LOWVOL_SWITCH)
/* ------ Digital Input ------ */
#define IN1_GPIO        (PC)
#define IN1_PIN         (PIN4)
#define IN1_OE			(PC_OE)
#define IN1_PU			(PC_PU)

#define IN2_GPIO        (PC)
#define IN2_PIN         (PIN5)
#define IN2_OE			(PC_OE)
#define IN2_PU			(PC_PU)

#define IN3_GPIO        (PC)
#define IN3_PIN         (PIN6)
#define IN3_OE			(PC_OE)
#define IN3_PU			(PC_PU)

#define IN4_GPIO        (PC)
#define IN4_PIN         (PIN7)
#define IN4_OE			(PC_OE)
#define IN4_PU			(PC_PU)

#define IN5_GPIO        (PC)
#define IN5_PIN         (PIN8)
#define IN5_OE			(PC_OE)
#define IN5_PU			(PC_PU)

#define IN6_GPIO        (PA)
#define IN6_PIN         (PIN13)
#define IN6_OE			(PA_OE)
#define IN6_PU			(PA_PU)

#define IN7_GPIO        (PA)
#define IN7_PIN         (PIN14)
#define IN7_OE			(PA_OE)
#define IN7_PU			(PA_PU)

#define IN8_GPIO        (PA)
#define IN8_PIN         (PIN15)
#define IN8_OE			(PA_OE)
#define IN8_PU			(PA_PU)

/* ------ Digital Output ------ */
#define OUT1_GPIO		(PD)
#define OUT1_PIN        (PIN3)
#define OUT1_OE			(PD_OE)

#define OUT2_GPIO		(PD)
#define OUT2_PIN        (PIN0)
#define OUT2_OE			(PD_OE)

#define OUT3_GPIO		(PC)
#define OUT3_PIN        (PIN1)
#define OUT3_OE			(PC_OE)

#define OUT4_GPIO		(PC)
#define OUT4_PIN        (PIN2)
#define OUT4_OE			(PC_OE)

/* ------ Test Output ------ */
#define TEST_GPIO       (PA)
#define TEST_PIN        (PIN13)
#define TEST_OE			(PA_OE)

#define TEST_GPIO1      (PA)
#define TEST_PIN1       (PIN14)
#define TEST_OE1		(PA_OE)

#define TEST_GPIO2      (PC)
#define TEST_PIN2       (PIN5)
#define TEST_OE2		(PC_OE)

/* ------ Encoder Pins ------ */
#define SLRE_GPIO		(PA)
#define SLRE_PIN		(PIN12)
#define SLRE_OE			(PA_OE)
#define SLRE_PU			(PA_PU)

#define MARE_GPIO		(PD)
#define MARE_PIN		(PIN6)
#define MARE_OE			(PD_OE)
#define MARE_PU			(PD_PU)

/* ------ I2C Pins ------ */
#define SCL_GPIO		(PA)
#define SCL_PIN			(PIN1)
#define SCL_OE			(PA_OE)

/* ------ other Pins ------ */
#define ERR_GPIO        (PC)
#define ERR_PIN         (PIN15)
#define ERR_OE			(PC_OE)


#endif 



#define VOT_GPIO        (PA)
#define VOT_PIN         (PIN2)  // over temperature



/*************************************************************************************///External Function
extern void GPIO_Init(void);
extern void GPIO_PU_Init(void);
extern void EXTI0_Init(void);
extern void EXTI1_Init(void);
extern void EXTI1_Clear(void);
extern void EXTI2_Init(void);
extern void Delay_ms(int8 ms);
extern void Delay_us(int8 us);

#endif