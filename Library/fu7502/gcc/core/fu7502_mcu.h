/*
 * Copyright (c) 2023-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : fu7502_mcu.c
 * Author        : Any Lin
 * Date          : 2023-09-15
 * Description   : define fu7502 MCU register definition
 *
 * Record        :
 * V1.0, 2023-09-15, Any Lin: Created file
 * V1.1, 2024-04-19, Brad Yang: Update definition
 */

#ifndef __FU7502_MCU_H__
#define __FU7502_MCU_H__

/******************************************************************************/
/*                                                                            */
/*                                Description                                 */
/*                                                                            */
/******************************************************************************/
/****************************** Interrupt vector ******************************/
/*
    BISS                ->              31
    CAN                 ->              30
    LIN                 ->              29
    UART2               ->              28
    UART                ->              27
    SPI2                ->              26
    SPI                 ->              25
    I2C                 ->              24
    RTC/MCD/PLL         ->              23
    WWDT                ->              22
    TIMER7              ->              21
    TIMER6              ->              20
    TIMER5              ->              19
    TIMER4              ->              18
    TIMER3              ->              17
    TIMER2              ->              16
    Systick             ->              15
    DMA4/5              ->              14
    DMA2/3              ->              13
    DMA0/1              ->              12
    ADC1/2/3            ->              11
    MEIF/PFCIF          ->              10
    DRV2INT             ->              09
    DRVINT              ->              08
    DRV2PIF             ->              07
    DRVPIF              ->              06
    CMP0/1/2/6/7/8      ->              05
    CMP3/4/5/9/10/11    ->              04
    EXT2                ->              03
    EXT1                ->              02
    EXT0                ->              01
    LVW/TSD/ECC         ->              00
 */
    

/******************************************************************************/
/*                                                                            */
/*                                Base options                                */
/*                                                                            */
/******************************************************************************/
#define MCU_48M_CLOCK                   48000000UL
#define MCU_24M_CLOCK                   24000000UL
/******************************************************************************/
/*                                                                            */
/*                          Registers Bus Definition                          */
/*                                                                            */
/******************************************************************************/
/*************************** Register bus definition **************************/
 #define ROM_BASE                       0x00000000UL
 #define CSR_BASE                       0x00000000UL
 #define SRAM_BASE                      0x40000000UL 
 #define Lock_Byte                      0x6000001cUL
 #define XSFR_BASE                      0x60000000UL

/********************** Register base address definition **********************/
 #define GPIOA_BASE                     (CSR_BASE + 0x0000)
 #define GPIOB_BASE                     (CSR_BASE + 0x0010)
 #define GPIOC_BASE                     (CSR_BASE + 0x0020)
 #define GPIOD_BASE                     (CSR_BASE + 0x0030)
 #define PHSEL_BASE                     (CSR_BASE + 0x0060)
 #define CK_BASE                        (CSR_BASE + 0x0080)
 #define DMA0_BASE                      (CSR_BASE + 0x00A0)
 #define DMA1_BASE                      (CSR_BASE + 0x00B0)
 #define DMA2_BASE                      (CSR_BASE + 0x00C0)
 #define DMA3_BASE                      (CSR_BASE + 0x00D0)
 #define DMA4_BASE                      (CSR_BASE + 0x00E0)
 #define DMA5_BASE                      (CSR_BASE + 0x00F0)
 #define UART1_BASE                     (CSR_BASE + 0x0140)
 #define UART2_BASE                     (CSR_BASE + 0x0150)
 #define I2C1_BASE                      (CSR_BASE + 0x0160)
 #define I2C2_BASE                      (CSR_BASE + 0x0170) 
 #define SPI1_BASE                      (CSR_BASE + 0x0180)
 #define SPI2_BASE                      (CSR_BASE + 0x0190)
 #define LIN_BASE                       (CSR_BASE + 0x01A0)
 #define CAN_BASE                       (CSR_BASE + 0x01C0)
 #define CRC_BASE                       (CSR_BASE + 0x01D8)
 #define TIMER2_BASE                    (CSR_BASE + 0x0210)
 #define TIMER3_BASE                    (CSR_BASE + 0x0220)
 #define TIMER4_BASE                    (CSR_BASE + 0x0230)
 #define TIMER5_BASE                    (CSR_BASE + 0x0240)
 #define TIMER6_BASE                    (CSR_BASE + 0x0250)
 #define TIMER7_BASE                    (CSR_BASE + 0x0260)
 #define TIMER8_BASE                    (CSR_BASE + 0x0270)
 #define STPC0_BASE                     (CSR_BASE + 0x02A0)
 #define STPC1_BASE                     (CSR_BASE + 0x02B0)
 #define IRQ_BASE                       (CSR_BASE + 0x0400)
 #define SYSTICK_BASE                   (CSR_BASE + 0x0440)
 #define RTC_BASE                       (CSR_BASE + 0x0460)
 #define OSC_BASE                       (CSR_BASE + 0x0463)
 #define IWDT_BASE                      (CSR_BASE + 0x0480)
 #define WWDT_BASE                      (CSR_BASE + 0x04A0)
 #define SPECIAL_BASE                   (CSR_BASE + 0x04C0)
 #define SYSTEM_BASE                    (CSR_BASE + 0x04D0)
 #define FLA_BASE                       (CSR_BASE + 0x04E0)
 #define ECC_BASE                       (CSR_BASE + 0x04F0)
 #define CMP_BASE                       (CSR_BASE + 0x0600)
 #define AMP_BASE                       (CSR_BASE + 0x0620)
 #define TEMP_BASE                      (CSR_BASE + 0x0630)
 #define DAC_BASE                       (CSR_BASE + 0x0640)
 #define ADC1_BASE                      (CSR_BASE + 0x0660)
 #define ADC2_BASE                      (CSR_BASE + 0x0670)
 #define ADC3_BASE                      (CSR_BASE + 0x0680)
 #define BISS_BASE                      (CSR_BASE + 0x0700)
 #define CCFG_BASE                      (CSR_BASE + 0x0FF0)

 #define ME_BASE                        (CSR_BASE + 0x0500)
 #define DRV1_BASE                      (CSR_BASE + 0x0540)
 #define DRV2_BASE                      (CSR_BASE + 0x0580)
// #define NFOCCSR_BASE                   (CSR_BASE + 0x0208)
// #define TIME1_BASE                     (CSR_BASE + 0x0210)
// #define FOC_BASE                       (CSR_BASE + 0x0218)
 #define ADC1DR_BASE                    (SRAM_BASE + 0x0040)
 #define ADC2DR_BASE                    (SRAM_BASE + 0x0060)
 #define PFC_BASE                       (CSR_BASE  + 0x05C0)
 #define CAN_TX0BASE                    (SRAM_BASE + 0x00A0)
 #define CAN_TX1BASE                    (SRAM_BASE + 0x00E0)
 #define CAN_TX2BASE                    (SRAM_BASE + 0x0120)
 #define CAN_RX0BASE                    (SRAM_BASE + 0x0160)
 #define CAN_RX1BASE                    (SRAM_BASE + 0x01A8)
 #define CAN_RX2BASE                    (SRAM_BASE + 0x01F0)

/************************** XSFR register definition **************************/

/************************** DSFR register definition **************************/
#define CAN_TX0DA0                      (*(volatile uint32* )(CAN_TX0BASE + 0x000 *4))
#define CAN_TX0DA1                      (*(volatile uint32* )(CAN_TX0BASE + 0x001 *4))
#define CAN_TX0DA2                      (*(volatile uint32* )(CAN_TX0BASE + 0x002 *4))
#define CAN_TX0DA3                      (*(volatile uint32* )(CAN_TX0BASE + 0x003 *4))
#define CAN_TX0DA4                      (*(volatile uint32* )(CAN_TX0BASE + 0x004 *4))
#define CAN_TX0DA5                      (*(volatile uint32* )(CAN_TX0BASE + 0x005 *4))
#define CAN_TX0DA6                      (*(volatile uint32* )(CAN_TX0BASE + 0x006 *4))
#define CAN_TX0DA7                      (*(volatile uint32* )(CAN_TX0BASE + 0x007 *4))
#define CAN_TX0DA8                      (*(volatile uint32* )(CAN_TX0BASE + 0x008 *4))
#define CAN_TX0DA9                      (*(volatile uint32* )(CAN_TX0BASE + 0x009 *4))
#define CAN_TX0DA10                     (*(volatile uint32* )(CAN_TX0BASE + 0x00A *4))
#define CAN_TX0DA11                     (*(volatile uint32* )(CAN_TX0BASE + 0x00B *4))
#define CAN_TX0DA12                     (*(volatile uint32* )(CAN_TX0BASE + 0x00C *4))
#define CAN_TX0DA13                     (*(volatile uint32* )(CAN_TX0BASE + 0x00D *4))
#define CAN_TX0DA14                     (*(volatile uint32* )(CAN_TX0BASE + 0x00E *4))
#define CAN_TX0DA15                     (*(volatile uint32* )(CAN_TX0BASE + 0x00F *4))

#define CAN_TX1DA0                      (*(volatile uint32* )(CAN_TX1BASE + 0x000 *4))
#define CAN_TX1DA1                      (*(volatile uint32* )(CAN_TX1BASE + 0x001 *4))
#define CAN_TX1DA2                      (*(volatile uint32* )(CAN_TX1BASE + 0x002 *4))
#define CAN_TX1DA3                      (*(volatile uint32* )(CAN_TX1BASE + 0x003 *4))
#define CAN_TX1DA4                      (*(volatile uint32* )(CAN_TX1BASE + 0x004 *4))
#define CAN_TX1DA5                      (*(volatile uint32* )(CAN_TX1BASE + 0x005 *4))
#define CAN_TX1DA6                      (*(volatile uint32* )(CAN_TX1BASE + 0x006 *4))
#define CAN_TX1DA7                      (*(volatile uint32* )(CAN_TX1BASE + 0x007 *4))
#define CAN_TX1DA8                      (*(volatile uint32* )(CAN_TX1BASE + 0x008 *4))
#define CAN_TX1DA9                      (*(volatile uint32* )(CAN_TX1BASE + 0x009 *4))
#define CAN_TX1DA10                     (*(volatile uint32* )(CAN_TX1BASE + 0x00A *4))
#define CAN_TX1DA11                     (*(volatile uint32* )(CAN_TX1BASE + 0x00B *4))
#define CAN_TX1DA12                     (*(volatile uint32* )(CAN_TX1BASE + 0x00C *4))
#define CAN_TX1DA13                     (*(volatile uint32* )(CAN_TX1BASE + 0x00D *4))
#define CAN_TX1DA14                     (*(volatile uint32* )(CAN_TX1BASE + 0x00E *4))
#define CAN_TX1DA15                     (*(volatile uint32* )(CAN_TX1BASE + 0x00F *4))

#define CAN_TX2DA0                      (*(volatile uint32* )(CAN_TX2BASE + 0x000 *4))
#define CAN_TX2DA1                      (*(volatile uint32* )(CAN_TX2BASE + 0x001 *4))
#define CAN_TX2DA2                      (*(volatile uint32* )(CAN_TX2BASE + 0x002 *4))
#define CAN_TX2DA3                      (*(volatile uint32* )(CAN_TX2BASE + 0x003 *4))
#define CAN_TX2DA4                      (*(volatile uint32* )(CAN_TX2BASE + 0x004 *4))
#define CAN_TX2DA5                      (*(volatile uint32* )(CAN_TX2BASE + 0x005 *4))
#define CAN_TX2DA6                      (*(volatile uint32* )(CAN_TX2BASE + 0x006 *4))
#define CAN_TX2DA7                      (*(volatile uint32* )(CAN_TX2BASE + 0x007 *4))
#define CAN_TX2DA8                      (*(volatile uint32* )(CAN_TX2BASE + 0x008 *4))
#define CAN_TX2DA9                      (*(volatile uint32* )(CAN_TX2BASE + 0x009 *4))
#define CAN_TX2DA10                     (*(volatile uint32* )(CAN_TX2BASE + 0x00A *4))
#define CAN_TX2DA11                     (*(volatile uint32* )(CAN_TX2BASE + 0x00B *4))
#define CAN_TX2DA12                     (*(volatile uint32* )(CAN_TX2BASE + 0x00C *4))
#define CAN_TX2DA13                     (*(volatile uint32* )(CAN_TX2BASE + 0x00D *4))
#define CAN_TX2DA14                     (*(volatile uint32* )(CAN_TX2BASE + 0x00E *4))
#define CAN_TX2DA15                     (*(volatile uint32* )(CAN_TX2BASE + 0x00F *4))

#define CAN_RX0ID                       (*(volatile uint32* )(CAN_RX0BASE + 0x000 *4))
#define CAN_RX0TD                       (*(volatile uint32* )(CAN_RX0BASE + 0x001 *4))
#define CAN_RX0DA0                      (*(volatile uint32* )(CAN_RX0BASE + 0x002 *4))
#define CAN_RX0DA1                      (*(volatile uint32* )(CAN_RX0BASE + 0x003 *4))
#define CAN_RX0DA2                      (*(volatile uint32* )(CAN_RX0BASE + 0x004 *4))
#define CAN_RX0DA3                      (*(volatile uint32* )(CAN_RX0BASE + 0x005 *4))
#define CAN_RX0DA4                      (*(volatile uint32* )(CAN_RX0BASE + 0x006 *4))
#define CAN_RX0DA5                      (*(volatile uint32* )(CAN_RX0BASE + 0x007 *4))
#define CAN_RX0DA6                      (*(volatile uint32* )(CAN_RX0BASE + 0x008 *4))
#define CAN_RX0DA7                      (*(volatile uint32* )(CAN_RX0BASE + 0x009 *4))
#define CAN_RX0DA8                      (*(volatile uint32* )(CAN_RX0BASE + 0x00A *4))
#define CAN_RX0DA9                      (*(volatile uint32* )(CAN_RX0BASE + 0x00B *4))
#define CAN_RX0DA10                     (*(volatile uint32* )(CAN_RX0BASE + 0x00C *4))
#define CAN_RX0DA11                     (*(volatile uint32* )(CAN_RX0BASE + 0x00D *4))
#define CAN_RX0DA12                     (*(volatile uint32* )(CAN_RX0BASE + 0x00E *4))
#define CAN_RX0DA13                     (*(volatile uint32* )(CAN_RX0BASE + 0x00F *4))
#define CAN_RX0DA14                     (*(volatile uint32* )(CAN_RX0BASE + 0x010 *4))
#define CAN_RX0DA15                     (*(volatile uint32* )(CAN_RX0BASE + 0x011 *4))

#define CAN_RX1ID                       (*(volatile uint32* )(CAN_RX1BASE + 0x000 *4))
#define CAN_RX1TD                       (*(volatile uint32* )(CAN_RX1BASE + 0x001 *4))
#define CAN_RX1DA0                      (*(volatile uint32* )(CAN_RX1BASE + 0x002 *4))
#define CAN_RX1DA1                      (*(volatile uint32* )(CAN_RX1BASE + 0x003 *4))
#define CAN_RX1DA2                      (*(volatile uint32* )(CAN_RX1BASE + 0x004 *4))
#define CAN_RX1DA3                      (*(volatile uint32* )(CAN_RX1BASE + 0x005 *4))
#define CAN_RX1DA4                      (*(volatile uint32* )(CAN_RX1BASE + 0x006 *4))
#define CAN_RX1DA5                      (*(volatile uint32* )(CAN_RX1BASE + 0x007 *4))
#define CAN_RX1DA6                      (*(volatile uint32* )(CAN_RX1BASE + 0x008 *4))
#define CAN_RX1DA7                      (*(volatile uint32* )(CAN_RX1BASE + 0x009 *4))
#define CAN_RX1DA8                      (*(volatile uint32* )(CAN_RX1BASE + 0x00A *4))
#define CAN_RX1DA9                      (*(volatile uint32* )(CAN_RX1BASE + 0x00B *4))
#define CAN_RX1DA10                     (*(volatile uint32* )(CAN_RX1BASE + 0x00C *4))
#define CAN_RX1DA11                     (*(volatile uint32* )(CAN_RX1BASE + 0x00D *4))
#define CAN_RX1DA12                     (*(volatile uint32* )(CAN_RX1BASE + 0x00E *4))
#define CAN_RX1DA13                     (*(volatile uint32* )(CAN_RX1BASE + 0x00F *4))
#define CAN_RX1DA14                     (*(volatile uint32* )(CAN_RX1BASE + 0x010 *4))
#define CAN_RX1DA15                     (*(volatile uint32* )(CAN_RX1BASE + 0x011 *4))

#define CAN_RX2ID                       (*(volatile uint32* )(CAN_RX2BASE + 0x000 *4))
#define CAN_RX2TD                       (*(volatile uint32* )(CAN_RX2BASE + 0x001 *4))
#define CAN_RX2DA0                      (*(volatile uint32* )(CAN_RX2BASE + 0x002 *4))
#define CAN_RX2DA1                      (*(volatile uint32* )(CAN_RX2BASE + 0x003 *4))
#define CAN_RX2DA2                      (*(volatile uint32* )(CAN_RX2BASE + 0x004 *4))
#define CAN_RX2DA3                      (*(volatile uint32* )(CAN_RX2BASE + 0x005 *4))
#define CAN_RX2DA4                      (*(volatile uint32* )(CAN_RX2BASE + 0x006 *4))
#define CAN_RX2DA5                      (*(volatile uint32* )(CAN_RX2BASE + 0x007 *4))
#define CAN_RX2DA6                      (*(volatile uint32* )(CAN_RX2BASE + 0x008 *4))
#define CAN_RX2DA7                      (*(volatile uint32* )(CAN_RX2BASE + 0x009 *4))
#define CAN_RX2DA8                      (*(volatile uint32* )(CAN_RX2BASE + 0x00A *4))
#define CAN_RX2DA9                      (*(volatile uint32* )(CAN_RX2BASE + 0x00B *4))
#define CAN_RX2DA10                     (*(volatile uint32* )(CAN_RX2BASE + 0x00C *4))
#define CAN_RX2DA11                     (*(volatile uint32* )(CAN_RX2BASE + 0x00D *4))
#define CAN_RX2DA12                     (*(volatile uint32* )(CAN_RX2BASE + 0x00E *4))
#define CAN_RX2DA13                     (*(volatile uint32* )(CAN_RX2BASE + 0x00F *4))
#define CAN_RX2DA14                     (*(volatile uint32* )(CAN_RX2BASE + 0x010 *4))
#define CAN_RX2DA15                     (*(volatile uint32* )(CAN_RX2BASE + 0x011 *4))


/******************************************************************************/
/*                                                                            */
/*                            Registers Definition                            */
/*                                                                            */
/******************************************************************************/
/************************** DSFR register definition **************************/
 #define ADC1_DR0                       (*(volatile uint16* )(ADC1DR_BASE + 0x00))
 #define ADC1_DR1                       (*(volatile uint16* )(ADC1DR_BASE + 0x02))
 #define ADC1_DR2                       (*(volatile uint16* )(ADC1DR_BASE + 0x04))
 #define ADC1_DR3                       (*(volatile uint16* )(ADC1DR_BASE + 0x06))
 #define ADC1_DR4                       (*(volatile uint16* )(ADC1DR_BASE + 0x08))
 #define ADC1_DR5                       (*(volatile uint16* )(ADC1DR_BASE + 0x0a))
 #define ADC1_DR6                       (*(volatile uint16* )(ADC1DR_BASE + 0x0c))
 #define ADC1_DR7                       (*(volatile uint16* )(ADC1DR_BASE + 0x0e))
 #define ADC1_DR8                       (*(volatile uint16* )(ADC1DR_BASE + 0x10))
 #define ADC1_DR9                       (*(volatile uint16* )(ADC1DR_BASE + 0x12))
 #define ADC1_DR10                      (*(volatile uint16* )(ADC1DR_BASE + 0x14))
 #define ADC1_DR11                      (*(volatile uint16* )(ADC1DR_BASE + 0x16))
 #define ADC1_DR12                      (*(volatile uint16* )(ADC1DR_BASE + 0x18))
 #define ADC1_DR13                      (*(volatile uint16* )(ADC1DR_BASE + 0x1a))
 #define ADC1_DR14                      (*(volatile uint16* )(ADC1DR_BASE + 0x1c))
 #define ADC1_DR15                      (*(volatile uint16* )(ADC1DR_BASE + 0x1e))

 #define ADC2_DR0                       (*(volatile uint16* )(ADC2DR_BASE + 0x00))
 #define ADC2_DR1                       (*(volatile uint16* )(ADC2DR_BASE + 0x02))
 #define ADC2_DR2                       (*(volatile uint16* )(ADC2DR_BASE + 0x04))
 #define ADC2_DR3                       (*(volatile uint16* )(ADC2DR_BASE + 0x06))
 #define ADC2_DR4                       (*(volatile uint16* )(ADC2DR_BASE + 0x08))
 #define ADC2_DR5                       (*(volatile uint16* )(ADC2DR_BASE + 0x0a))
 #define ADC2_DR6                       (*(volatile uint16* )(ADC2DR_BASE + 0x0c))
 #define ADC2_DR7                       (*(volatile uint16* )(ADC2DR_BASE + 0x0e))
 #define ADC2_DR8                       (*(volatile uint16* )(ADC2DR_BASE + 0x10))
 #define ADC2_DR9                       (*(volatile uint16* )(ADC2DR_BASE + 0x12))
 #define ADC2_DR10                      (*(volatile uint16* )(ADC2DR_BASE + 0x14))
 #define ADC2_DR11                      (*(volatile uint16* )(ADC2DR_BASE + 0x16))
 #define ADC2_DR12                      (*(volatile uint16* )(ADC2DR_BASE + 0x18))
 #define ADC2_DR13                      (*(volatile uint16* )(ADC2DR_BASE + 0x1a))
 #define ADC2_DR14                      (*(volatile uint16* )(ADC2DR_BASE + 0x1c))
 #define ADC2_DR15                      (*(volatile uint16* )(ADC2DR_BASE + 0x1e))
/*************************** CSR register definition **************************/
 #define PA                             (GPIOA_BASE   + 0x00)                   // RV:      00H    PortA寄存器
 #define PA_OE                          (GPIOA_BASE   + 0x01)                   // RV:      00H    PA输出使能寄存器
 #define PA_PU                          (GPIOA_BASE   + 0x02)                   // RV:      00H    PA上拉使能寄存器
 #define PA_PL                          (GPIOA_BASE   + 0x03)                   // RV:      00H    PA下拉使能寄存器
 #define PB                             (GPIOB_BASE   + 0x00)                   // RV:      00H    PortB寄存器
 #define PB_OE                          (GPIOB_BASE   + 0x01)                   // RV:      00H    PB输出使能寄存器
 #define PB_PU                          (GPIOB_BASE   + 0x02)                   // RV:      00H    PB上拉使能寄存器
 #define PB_AN                          (GPIOB_BASE   + 0x03)                   // RV:      00H    PB模拟使能寄存器
 #define PC                             (GPIOC_BASE   + 0x00)                   // RV:      00H    PortC寄存器
 #define PC_OE                          (GPIOC_BASE   + 0x01)                   // RV:      00H    PC输出使能寄存器
 #define PC_PU                          (GPIOC_BASE   + 0x02)                   // RV:      00H    PC上拉使能寄存器
 #define PC_AN                          (GPIOC_BASE   + 0x03)                   // RV:      00H    PC模拟使能寄存器
 #define PD                             (GPIOD_BASE   + 0x00)                   // RV:      00H    PortD寄存器
 #define PD_OE                          (GPIOD_BASE   + 0x01)                   // RV:      00H    PD输出使能寄存器
 #define PD_PU                          (GPIOD_BASE   + 0x02)                   // RV:      00H    PD上拉使能寄存器
 #define PD_AN                          (GPIOD_BASE   + 0x03)                   // RV:      00H    PD模拟使能寄存器
 #define PH_SEL                         (PHSEL_BASE   + 0x00)                   // RV:      00H    端口复用选择寄存器
 #define MIE                            (0x300)                                 // RV:00000000H    机器中断控制寄存器
 #define PIE                            (IRQ_BASE     + 0x00)                   // RV:      00H    挂起中断控制寄存器
 #define EXT0IE                         (IRQ_BASE     + 0x01)                   // RV:      00H    外部中断0使能控制寄存器
 #define EXT1IE                         (IRQ_BASE     + 0x02)                   // RV:      00H    外部中断1使能控制寄存器 
 #define EXT2IE                         (IRQ_BASE     + 0x03)                   // RV:      00H    外部中断2使能控制寄存器
 #define EXT0IF                         (IRQ_BASE     + 0x04)                   // RV:      00H    外部中断0中断标志寄存器
 #define EXT1IF                         (IRQ_BASE     + 0x05)                   // RV:      00H    外部中断1中断标志寄存器
 #define EXT2IF                         (IRQ_BASE     + 0x06)                   // RV:      00H    外部中断2中断标志寄存器
 #define TCON                           (IRQ_BASE     + 0x07)                   // RV:      00H    中断控制寄存器
 #define LVSR                           (IRQ_BASE     + 0x08)                   // RV:      00H    低温/过压状态寄存器
 #define IP0                            (IRQ_BASE     + 0x09)                   // RV:    0000H    中断优先级控制0
 #define IP1                            (IRQ_BASE     + 0x0A)                   // RV:    0000H    中断优先级控制1
 #define IP2                            (IRQ_BASE     + 0x0B)                   // RV:    0000H    中断优先级控制2
 #define IP3                            (IRQ_BASE     + 0x0C)                   // RV:    0000H    中断优先级控制3
 #define IP4                            (IRQ_BASE     + 0x0D)                   // RV:    0000H    中断优先级控制4
 #define IP5                            (IRQ_BASE     + 0x0E)                   // RV:    0000H    中断优先级控制5
 #define IP6                            (IRQ_BASE     + 0x0F)                   // RV:    0000H    中断优先级控制6
 #define IP7                            (IRQ_BASE     + 0x10)                   // RV:    0000H    中断优先级控制7
 #define IP8                            (IRQ_BASE     + 0x11)                   // RV:    0000H    中断优先级控制8
 #define IP9                            (IRQ_BASE     + 0x12)                   // RV:    0000H    中断优先级控制9
 #define IP10                           (IRQ_BASE     + 0x13)                   // RV:    0000H    中断优先级控制10
 #define IP11                           (IRQ_BASE     + 0x14)                   // RV:    0000H    中断优先级控制11
 #define IP12                           (IRQ_BASE     + 0x15)                   // RV:    0000H    中断优先级控制12
 #define IP13                           (IRQ_BASE     + 0x16)                   // RV:    0000H    中断优先级控制13
 #define IP14                           (IRQ_BASE     + 0x17)                   // RV:    0000H    中断优先级控制14
 #define IP15                           (IRQ_BASE     + 0x18)                   // RV:    0000H    中断优先级控制15
 #define IP16                           (IRQ_BASE     + 0x19)                   // RV:    0000H    中断优先级控制16
 #define IP17                           (IRQ_BASE     + 0x1A)                   // RV:    0000H    中断优先级控制17
 #define IP18                           (IRQ_BASE     + 0x1B)                   // RV:    0000H    中断优先级控制18
 #define IP19                           (IRQ_BASE     + 0x1C)                   // RV:    0000H    中断优先级控制19
 #define IP20                           (IRQ_BASE     + 0x1D)                   // RV:    0000H    中断优先级控制20
 #define IP21                           (IRQ_BASE     + 0x1E)                   // RV:    0000H    中断优先级控制21
 #define IP22                           (IRQ_BASE     + 0x1F)                   // RV:    0000H    中断优先级控制22
 #define IP23                           (IRQ_BASE     + 0x20)                   // RV:    0000H    中断优先级控制23
 #define IP24                           (IRQ_BASE     + 0x21)                   // RV:    0000H    中断优先级控制24
 #define IP25                           (IRQ_BASE     + 0x22)                   // RV:    0000H    中断优先级控制25
 #define IP26                           (IRQ_BASE     + 0x23)                   // RV:    0000H    中断优先级控制26
 #define IP27                           (IRQ_BASE     + 0x24)                   // RV:    0000H    中断优先级控制27
 #define IP28                           (IRQ_BASE     + 0x25)                   // RV:    0000H    中断优先级控制28
 #define IP29                           (IRQ_BASE     + 0x26)                   // RV:    0000H    中断优先级控制29
 #define IP30                           (IRQ_BASE     + 0x27)                   // RV:    0000H    中断优先级控制30
 #define IP31                           (IRQ_BASE     + 0x28)                   // RV:    0000H    中断优先级控制31
 #define CFG_KEY                        (SPECIAL_BASE + 0x01)                   // /* factory */
 #define RTC_CR                         (RTC_BASE     + 0x00)                   // RV:    0000H    RTC控制寄存器
 #define RTC_DR                         (RTC_BASE     + 0x01)                   // RV:    FFFFH    RTC计数寄存器
 #define CAL_CR                         (RTC_BASE     + 0x02)                   // RV:      00H    时钟校准寄存器
 #define OSC_CR                         (OSC_BASE     + 0x00)                   // RV:      00H    外部快时钟控制寄存器
 #define OSC_SR                         (OSC_BASE     + 0x01)                   // RV:      00H    外部快时钟状态寄存器
 #define FLA_KEY                        (FLA_BASE     + 0x00)                   // RV:      00H    Flash解锁寄存器
 #define FLA_CR                         (FLA_BASE     + 0x01)                   // RV:    0000H    Flash控制寄存器
 #define FLA_ECC_CR                     (ECC_BASE     + 0x00)                   // RV:    8000H    ECC错误配置寄存器
 #define FLA_ECC_SR                     (ECC_BASE     + 0x01)                   // RV:    0000H    ECC错误状态寄存器
 #define RST_SR                         (SYSTEM_BASE  + 0x00)                   // RV:      xxH    复位状态寄存器
 #define RST_CR                         (SYSTEM_BASE  + 0x01)                   // RV:      xxH    复位控制寄存器
 #define PCON                           (SYSTEM_BASE  + 0x02)                   // RV:      00H    MCU功率控制寄存器
 #define CK_CR                          (CK_BASE      + 0x00)                   // RV:00000000H    时钟控制寄存器
 #define CMP_CR0                        (CMP_BASE     + 0x00)                   // RV:      00H    比较器控制寄存器0
 #define CMP_CR1                        (CMP_BASE     + 0x01)                   // RV:      00H    比较器控制寄存器1
 #define CMP_CR2                        (CMP_BASE     + 0x02)                   // RV:      00H    比较器控制寄存器2
 #define CMP_CR3                        (CMP_BASE     + 0x03)                   // RV:      00H    比较器控制寄存器3
 #define CMP_SR                         (CMP_BASE     + 0x04)                   // RV:      00H    比较器状态寄存器
 #define CMP_IFR                        (CMP_BASE     + 0x05)                   // RV:      00H    比较器中断标志位寄存器    
 #define CMP_SAMR                       (CMP_BASE     + 0x06)                   // RV:      00H    比较器采样配置
 #define CMP_DBR                        (CMP_BASE     + 0x07)                   // RV:      00H    比较器信号配置寄存器   
 #define CMP_CR4                        (CMP_BASE     + 0x08)                   // RV:      00H    比较器控制寄存器4
 #define CMP_CR5                        (CMP_BASE     + 0x09)                   // RV:      00H    比较器控制寄存器5
 #define CMP_CR6                        (CMP_BASE     + 0x0A)                   // RV:      00H    比较器控制寄存器6
 #define EVT_FILT                       (CMP_BASE     + 0x06)                   // RV:    0300H    驱动保护功能寄存器
 #define VREF_VHALF_CR                  (AMP_BASE     + 0x00)                   // RV:    0000H    参考电平控制寄存器
 #define AMP_CR0                        (AMP_BASE     + 0x01)                   // RV:    0000H    运放控制寄存器0
 #define AMP_CR1                        (AMP_BASE     + 0x02)                   // RV:    0000H    运放控制寄存器1
 #define TSD_CR                         (TEMP_BASE    + 0x00)                   // RV:    000DH    TSD控制寄存器
 #define TSEN_DR                        (TEMP_BASE    + 0x01)                   // RV:    0000H    TSENSOR数据寄存器
 #define DAC_CR                         (DAC_BASE     + 0x00)                   // RV:    0000H    DAC控制寄存器
 #define DAC_DR0                        (DAC_BASE     + 0x01)                   // RV:    0000H    DAC0输出数值寄存器0
 #define DAC_DR1                        (DAC_BASE     + 0x02)                   // RV:    0000H    DAC0输出数值寄存器1
 #define DAC_DR2                        (DAC_BASE     + 0x03)                   // RV:    0000H    DAC0输出数值寄存器2
 #define DAC_DR3                        (DAC_BASE     + 0x04)                   // RV:    0000H    DAC0输出数值寄存器3
 #define DAC_DR4                        (DAC_BASE     + 0x05)                   // RV:    0000H    DAC0输出数值寄存器4
 #define ADC1_CR                        (ADC1_BASE    + 0x00)                   // RV:    0000H    ADC控制寄存器
 #define ADC1_MASK                      (ADC1_BASE    + 0x01)                   // RV:    0000H    ADC通道使能寄存器
 #define ADC1_SCYC                      (ADC1_BASE    + 0x02)                   // RV:    3333H    ADC通道采样时间配置寄存器
 #define ADC2_CR                        (ADC2_BASE    + 0x00)                   // RV:    0000H    ADC2控制寄存器
 #define ADC2_MASK                      (ADC2_BASE    + 0x01)                   // RV:    0000H    ADC2通道使能寄存器
 #define ADC2_SCYC                      (ADC2_BASE    + 0x02)                   // RV:    3333H    ADC2通道采样时间配置寄存器
 #define ADC3_CR                        (ADC3_BASE    + 0x00)                   // RV:    0000H    ADC3控制寄存器
 #define ADC3_MASK                      (ADC3_BASE    + 0x01)                   // RV:    0000H    ADC3通道使能寄存器
 #define ADC3_SCYC                      (ADC3_BASE    + 0x02)                   // RV:    0033H    ADC3通道采样时间配置寄存器
 #define ADC3_DR0                       (ADC3_BASE    + 0x03)                   // RV:    0000H    ADC3通道采样数据寄存器0
 #define ADC3_DR1                       (ADC3_BASE    + 0x04)                   // RV:    0000H    ADC3通道采样数据寄存器1
 #define ADC3_DR2                       (ADC3_BASE    + 0x05)                   // RV:    0000H    ADC3通道采样数据寄存器2
 #define DMA0_CR                        (DMA0_BASE    + 0x00)                   // RV:      00H    DMA0控制寄存器
 #define DMA0_LEN                       (DMA0_BASE    + 0x01)                   // RV:      00H    DMA0传输长度配置寄存器
 #define DMA0_BA                        (DMA0_BASE    + 0x02)                   // RV:      00H    DMA0传输地址配置寄存器
 #define DMA1_CR                        (DMA1_BASE    + 0x00)                   // RV:      00H    DMA1控制寄存器
 #define DMA1_LEN                       (DMA1_BASE    + 0x01)                   // RV:      00H    DMA1传输长度配置寄存器
 #define DMA1_BA                        (DMA1_BASE    + 0x02)                   // RV:      00H    DMA1传输地址配置寄存器
 #define DMA2_CR                        (DMA2_BASE    + 0x00)                   // RV:      00H    DMA2控制寄存器
 #define DMA2_LEN                       (DMA2_BASE    + 0x01)                   // RV:      00H    DMA2传输长度配置寄存器
 #define DMA2_BA                        (DMA2_BASE    + 0x02)                   // RV:      00H    DMA2传输地址配置寄存器
 #define DMA3_CR                        (DMA3_BASE    + 0x00)                   // RV:      00H    DMA3控制寄存器
 #define DMA3_LEN                       (DMA3_BASE    + 0x01)                   // RV:      00H    DMA3传输长度配置寄存器
 #define DMA3_BA                        (DMA3_BASE    + 0x02)                   // RV:      00H    DMA3传输地址配置寄存器
 #define DMA4_CR                        (DMA4_BASE    + 0x00)                   // RV:      00H    DMA4控制寄存器
 #define DMA4_LEN                       (DMA4_BASE    + 0x01)                   // RV:      00H    DMA4传输长度配置寄存器
 #define DMA4_BA                        (DMA4_BASE    + 0x02)                   // RV:      00H    DMA4传输地址配置寄存器
 #define DMA5_CR                        (DMA5_BASE    + 0x00)                   // RV:      00H    DMA5控制寄存器
 #define DMA5_LEN                       (DMA5_BASE    + 0x01)                   // RV:      00H    DMA5传输长度配置寄存器
 #define DMA5_BA                        (DMA5_BASE    + 0x02)                   // RV:      00H    DMA5传输地址配置寄存器
 #define UT1_CR0                        (UART1_BASE   + 0x00)                   // RV:      00H    Uart控制寄存器0
 #define UT1_CR1                        (UART1_BASE   + 0x01)                   // RV:      00H    Uart控制寄存器1
 #define UT1_DR                         (UART1_BASE   + 0x02)                   // RV:      00H    UART数据寄存器
 #define UT1_BAUD                       (UART1_BASE   + 0x03)                   // RV:    0000H    UART波特率控制寄存器
 #define SF_CR                          (UART1_BASE   + 0x04)                   // RV:    0000H    编码器串行接口控制寄存器
 #define SF_SR                          (UART1_BASE   + 0x05)                   // RV:    0000H    编码器串行接口状态寄存器
 #define SF_BAUD                        (UART1_BASE   + 0x06)                   // RV:    0000H    编码器串行接口波特率寄存器
 #define UT2_CR0                        (UART2_BASE   + 0x00)                   // RV:    0012H    Uart2控制寄存器0
 #define UT2_CR1                        (UART2_BASE   + 0x01)                   // RV:      00H    Uart2控制寄存器1
 #define UT2_DR                         (UART2_BASE   + 0x02)                   // RV:      00H    Uart2数据寄存器
 #define UT2_BAUD                       (UART2_BASE   + 0x03)                   // RV:    0000H    UART2波特率控制寄存器
 #define I2C1_CR                        (I2C1_BASE    + 0x00)                   // RV:    0000H    I2C控制寄存器
 #define I2C1_ID                        (I2C1_BASE    + 0x01)                   // RV:    0000H    I2C本机地址寄存器
 #define I2C1_DR                        (I2C1_BASE    + 0x02)                   // RV:    0000H    I2C数据寄存器
 #define I2C1_SR                        (I2C1_BASE    + 0x03)                   // RV:    0000H    I2C状态存器
 #define I2C1_BAUD                      (I2C1_BASE    + 0x04)                   // RV:    0000H    I2C2波特率控制寄存器
 #define I2C2_CR                        (I2C2_BASE    + 0x00)                   // RV:    0000H    I2C2控制寄存器
 #define I2C2_ID                        (I2C2_BASE    + 0x01)                   // RV:    0000H    I2C2本机地址寄存器
 #define I2C2_DR                        (I2C2_BASE    + 0x02)                   // RV:    0000H    I2C2数据寄存器
 #define I2C2_SR                        (I2C2_BASE    + 0x03)                   // RV:    0000H    I2C2状态存器
 #define I2C2_BAUD                      (I2C2_BASE    + 0x04)                   // RV:    0000H    I2C2波特率控制寄存器
 #define SPI1_CR                        (SPI1_BASE    + 0x00)                   // RV:      0bH    SPI1控制寄存器
 #define SPI1_SR                        (SPI1_BASE    + 0x01)                   // RV:      02H    SPI1状态寄存器
 #define SPI1_CLK                       (SPI1_BASE    + 0x02)                   // RV:      00H    SPI1时钟寄存器
 #define SPI1_DR                        (SPI1_BASE    + 0x03)                   // RV:      00H    SPI1数据寄存器
 #define SPI2_CR                        (SPI2_BASE    + 0x00)                   // RV:      0bH    SPI2控制寄存器
 #define SPI2_SR                        (SPI2_BASE    + 0x01)                   // RV:      02H    SPI2状态寄存器
 #define SPI2_CLK                       (SPI2_BASE    + 0x02)                   // RV:      00H    SPI2时钟寄存器
 #define SPI2_DR                        (SPI2_BASE    + 0x03)                   // RV:      00H    SPI2数据寄存器
 #define LIN_CR                         (LIN_BASE     + 0x00)                   // RV:      00H    LIN控制寄存器
 #define LIN_SR                         (LIN_BASE     + 0x01)                   // RV:      00H    LIN状态寄存器
 #define LIN_CSR                        (LIN_BASE     + 0x02)                   // RV:      00H    LIN状态控制寄存器
 #define LIN_ID                         (LIN_BASE     + 0x03)                   // RV:      00H    LINID寄存器
 #define LIN_SIZE                       (LIN_BASE     + 0x04)                   // RV:      00H    LIN数据长度寄存器
 #define LIN_BAUD                       (LIN_BASE     + 0x05)                   // RV:      00H    LIN波特率控制寄存器
 #define CAN_CR0                        (CAN_BASE     + 0x00)                   // RV:    0000H    CAN控制寄存器0
 #define CAN_CR1                        (CAN_BASE     + 0x01)                   // RV:    0000H    CAN控制寄存器1
 #define CAN_STS                        (CAN_BASE     + 0x02)                   // RV:    0000H    CAN状态寄存器
 #define CAN_IER                        (CAN_BASE     + 0x03)                   // RV:    0000H    CAN中断控制寄存器
 #define CAN_IFR                        (CAN_BASE     + 0x04)                   // RV:    0000H    CAN中断标志寄存器
 #define CAN_TSPT                       (CAN_BASE     + 0x05)                   // RV:    0000H    CAN报文状态寄存器
 #define CAN_NBTR                       (CAN_BASE     + 0x06)                   // RV:    0000H    CAN常规位时序控制寄存器
 #define CAN_DBTR                       (CAN_BASE     + 0x07)                   // RV:    0000H    CAN数据域位时序控制寄存器
 #define CAN_TDCR                       (CAN_BASE     + 0x08)                   // RV:    0000H    CAN传输延迟控制寄存器
 #define CAN_ACR                        (CAN_BASE     + 0x09)                   // RV:    0000H    CAN过滤器寄存器
 #define CAN_AMR                        (CAN_BASE     + 0x0a)                   // RV:    0000H    CAN过滤器激活寄存器
 #define CAN_ERR                        (CAN_BASE     + 0x0b)                   // RV:    0000H    CAN错误状态寄存器
 #define CAN_ERLIM                      (CAN_BASE     + 0x0c)                   // RV:    0000H    CAN错误预警门限寄存器
 #define CAN_TMSTA                      (CAN_BASE     + 0x0d)                   // RV:    0000H    CAN邮箱状态寄存器
 #define CAN_TMID0                      (CAN_BASE     + 0x0e)                   // RV:    0000H    CAN发送邮箱ID寄存器0
 #define CAN_TMDT0                      (CAN_BASE     + 0x0f)                   // RV:    0000H    CAN发送邮箱配置寄存器0
 #define CAN_TMID1                      (CAN_BASE     + 0x10)                   // RV:    0000H    CAN发送邮箱ID寄存器1
 #define CAN_TMDT1                      (CAN_BASE     + 0x11)                   // RV:    0000H    CAN发送邮箱配置寄存器1
 #define CAN_TMID2                      (CAN_BASE     + 0x12)                   // RV:    0000H    CAN发送邮箱ID寄存器2
 #define CAN_TMDT2                      (CAN_BASE     + 0x13)                   // RV:    0000H    CAN发送邮箱配置寄存器2
 #define TIM2_CR0                       (TIMER2_BASE  + 0x00)                   // RV:    0000H    TIMER2控制寄存器0
 #define TIM2_CR1                       (TIMER2_BASE  + 0x01)                   // RV:    0000H    TIMER2控制寄存器1
 #define TIM2_IER                       (TIMER2_BASE  + 0x02)                   // RV:    0000H    TIMER2中断寄存器
 #define TIM2_SR                        (TIMER2_BASE  + 0x03)                   // RV:    0000H    TIMER2状态寄存器
 #define TIM2_CNTR                      (TIMER2_BASE  + 0x04)                   // RV:    0000H    TIMER2计数值
 #define TIM2_DR                        (TIMER2_BASE  + 0x05)                   // RV:    0000H    TIMER2匹配值
 #define TIM2_ARR                       (TIMER2_BASE  + 0x06)                   // RV:    0000H    TIMER2重载值
 #define TIM2_QEP_MNUM                  (TIMER2_BASE  + 0x07)                   // RV:    0000H    TIMER2脉冲计数值
 #define TIM2_QEP_TNUM                  (TIMER2_BASE  + 0x08)                   // RV:    0000H    TIMER2时钟计数值
 #define TIM2_QEP_TS_EMP                (TIMER2_BASE  + 0x09)                   // RV:    0000H    TIMER2空脉冲计数值
 #define TIM2_QEP_CNTR                  (TIMER2_BASE  + 0x0A)                   // RV:    0000H    TIMER2输出脉冲计数值
 #define TIM2_QEP_ARR                   (TIMER2_BASE  + 0x0B)                   // RV:    0000H    TIMER2输出脉冲比较值
 #define TIM2_CR2                       (TIMER2_BASE  + 0x0C)                   // RV:    0000H    TIMER2控制寄存器2
 #define TIM3_CR0                       (TIMER3_BASE  + 0x00)                   // RV:    0000H    TIMER3控制寄存器0
 #define TIM3_CR1                       (TIMER3_BASE  + 0x01)                   // RV:    0000H    TIMER3控制寄存器1
 #define TIM3_IER                       (TIMER3_BASE  + 0x02)                   // RV:    0000H    TIMER3中断寄存器
 #define TIM3_SR                        (TIMER3_BASE  + 0x03)                   // RV:    0000H    TIMER3状态寄存器
 #define TIM3_CNTR                      (TIMER3_BASE  + 0x04)                   // RV:    0000H    TIMER3计数值
 #define TIM3_DR                        (TIMER3_BASE  + 0x05)                   // RV:    0000H    TIMER3匹配值
 #define TIM3_ARR                       (TIMER3_BASE  + 0x06)                   // RV:    0000H    TIMER3重载值
 #define TIM4_CR0                       (TIMER4_BASE  + 0x00)                   // RV:    0000H    TIMER4控制寄存器0
 #define TIM4_CR1                       (TIMER4_BASE  + 0x01)                   // RV:    0000H    TIMER4控制寄存器1
 #define TIM4_IER                       (TIMER4_BASE  + 0x02)                   // RV:    0000H    TIMER4中断寄存器
 #define TIM4_SR                        (TIMER4_BASE  + 0x03)                   // RV:    0000H    TIMER4状态寄存器
 #define TIM4_CNTR                      (TIMER4_BASE  + 0x04)                   // RV:    0000H    TIMER4计数值
 #define TIM4_DR                        (TIMER4_BASE  + 0x05)                   // RV:    0000H    TIMER4匹配值
 #define TIM4_ARR                       (TIMER4_BASE  + 0x06)                   // RV:    0000H    TIMER4重载值
 #define TIM5_CR0                       (TIMER5_BASE  + 0x00)                   // RV:    0000H    TIMER5控制寄存器0
 #define TIM5_CR1                       (TIMER5_BASE  + 0x01)                   // RV:    0000H    TIMER5控制寄存器1
 #define TIM5_IER                       (TIMER5_BASE  + 0x02)                   // RV:    0000H    TIMER5中断寄存器
 #define TIM5_SR                        (TIMER5_BASE  + 0x03)                   // RV:    0000H    TIMER5状态寄存器
 #define TIM5_CNTR                      (TIMER5_BASE  + 0x04)                   // RV:    0000H    TIMER5计数值
 #define TIM5_DR                        (TIMER5_BASE  + 0x05)                   // RV:    0000H    TIMER5匹配值
 #define TIM5_ARR                       (TIMER5_BASE  + 0x06)                   // RV:    0000H    TIMER5重载值
 #define TIM5_QEP_MNUM                  (TIMER5_BASE  + 0x07)                   // RV:    0000H    TIMER5脉冲计数值
 #define TIM5_QEP_TNUM                  (TIMER5_BASE  + 0x08)                   // RV:    0000H    TIMER5时钟计数值
 #define TIM5_QEP_TS_EMP                (TIMER5_BASE  + 0x09)                   // RV:    0000H    TIMER5空脉冲计数值
 #define TIM5_QEP_CNTR                  (TIMER5_BASE  + 0x0A)                   // RV:    0000H    TIMER5输出脉冲计数值
 #define TIM5_QEP_ARR                   (TIMER5_BASE  + 0x0B)                   // RV:    0000H    TIMER5输出脉冲比较值
 #define TIM5_CR2                       (TIMER5_BASE  + 0x0C)                   // RV:    0000H    TIMER5控制寄存器2
 #define TIM6_CR0                       (TIMER6_BASE  + 0x00)                   // RV:    0000H    TIMER6控制寄存器0
 #define TIM6_CR1                       (TIMER6_BASE  + 0x01)                   // RV:    0000H    TIMER6控制寄存器1
 #define TIM6_IER                       (TIMER6_BASE  + 0x02)                   // RV:    0000H    TIMER6中断寄存器
 #define TIM6_SR                        (TIMER6_BASE  + 0x03)                   // RV:    0000H    TIMER6状态寄存器
 #define TIM6_CNTR                      (TIMER6_BASE  + 0x04)                   // RV:    0000H    TIMER6计数值
 #define TIM6_DR                        (TIMER6_BASE  + 0x05)                   // RV:    0000H    TIMER6匹配值
 #define TIM6_ARR                       (TIMER6_BASE  + 0x06)                   // RV:    0000H    TIMER6重载值
 #define TIM6_QEP_MNUM                  (TIMER6_BASE  + 0x07)                   // RV:    0000H    TIMER6脉冲计数值
 #define TIM6_QEP_TNUM                  (TIMER6_BASE  + 0x08)                   // RV:    0000H    TIMER6时钟计数值
 #define TIM6_QEP_TS_EMP                (TIMER6_BASE  + 0x09)                   // RV:    0000H    TIMER6空脉冲计数值
 #define TIM6_QEP_CNTR                  (TIMER6_BASE  + 0x0A)                   // RV:    0000H    TIMER6输出脉冲计数值
 #define TIM6_QEP_ARR                   (TIMER6_BASE  + 0x0B)                   // RV:    0000H    TIMER6输出脉冲比较值
 #define TIM6_CR2                       (TIMER6_BASE  + 0x0C)                   // RV:    0000H    TIMER6控制寄存器2
 #define TIM7_CR0                       (TIMER7_BASE  + 0x00)                   // RV:    0000H    TIMER7控制寄存器0
 #define TIM7_CR1                       (TIMER7_BASE  + 0x01)                   // RV:    0000H    TIMER7控制寄存器1
 #define TIM7_IER                       (TIMER7_BASE  + 0x02)                   // RV:    0000H    TIMER7中断寄存器
 #define TIM7_SR                        (TIMER7_BASE  + 0x03)                   // RV:    0000H    TIMER7状态寄存器
 #define TIM7_CNTR                      (TIMER7_BASE  + 0x04)                   // RV:    0000H    TIMER7计数值
 #define TIM7_DR                        (TIMER7_BASE  + 0x05)                   // RV:    0000H    TIMER7匹配值
 #define TIM7_ARR                       (TIMER7_BASE  + 0x06)                   // RV:    0000H    TIMER7重载值
 #define TIM8_CR0                       (TIMER8_BASE  + 0x00)                   // RV:    0000H    TIMER8控制寄存器0
 #define TIM8_CR1                       (TIMER8_BASE  + 0x01)                   // RV:    0000H    TIMER8控制寄存器1
 #define TIM8_IER                       (TIMER8_BASE  + 0x02)                   // RV:    0000H    TIMER8中断寄存器
 #define TIM8_SR                        (TIMER8_BASE  + 0x03)                   // RV:    0000H    TIMER8状态寄存器
 #define TIM8_CNTR                      (TIMER8_BASE  + 0x04)                   // RV:    0000H    TIMER8计数值
 #define TIM8_DR                        (TIMER8_BASE  + 0x05)                   // RV:    0000H    TIMER8匹配值
 #define TIM8_ARR                       (TIMER8_BASE  + 0x06)                   // RV:    0000H    TIMER8重载值
 #define STPC0_CR                       (STPC0_BASE   + 0x00)                   // RV:    0000H    探针0控制寄存器
 #define STPC0_SR                       (STPC0_BASE   + 0x01)                   // RV:    0000H    探针0状态寄存器
 #define STRO0_ARR                      (STPC0_BASE   + 0x02)                   // RV:    0000H    探针0的锁存值
 #define PCOM0_ARR                      (STPC0_BASE   + 0x03)                   // RV:    0000H    位置比较0的比较值
 #define STPC1_CR                       (STPC1_BASE   + 0x00)                   // RV:    0000H    探针1控制寄存器
 #define STPC1_SR                       (STPC1_BASE   + 0x01)                   // RV:    0000H    探针1状态寄存器
 #define STRO1_ARR                      (STPC1_BASE   + 0x02)                   // RV:    0000H    探针1的锁存值
 #define PCOM1_ARR                      (STPC1_BASE   + 0x03)                   // RV:    0000H    位置比较1的比较值
 #define SYST_ARR                       (SYSTICK_BASE + 0x00)                   // RV:    0176H    SYSTICK重载值
 #define SYST_SR                        (SYSTICK_BASE + 0x01)                   // RV:    0000H    SYSTICK控制寄存器
 #define IWDT_KR                        (IWDT_BASE    + 0x00)                   // RV:    0000H    看门狗键寄存器
 #define IWDT_REL                       (IWDT_BASE    + 0x01)                   // RV:    0000H    看门狗重载值寄存器
 #define WWDT_CR                        (WWDT_BASE    + 0x00)                   // RV:    0000H    窗口看门狗控制寄存器
 #define WWDT_CFR                       (WWDT_BASE    + 0x01)                   // RV:    0000H    窗口看门狗配置寄存器
 #define WWDT_SR                        (WWDT_BASE    + 0x02)                   // RV:    0000H    窗口看门狗状态寄存器
 #define CRC_DIN                        (CRC_BASE     + 0x00)                   // RV:    0000H    CRC数据输入寄存器
 #define CRC_CR                         (CRC_BASE     + 0x01)                   // RV:    0010H    CRC控制寄存器
 #define CRC_DR                         (CRC_BASE     + 0x02)                   // RV:    0000H    CRC结果输出寄存器
 #define CRC_BEG                        (CRC_BASE     + 0x03)                   // RV:    0000H    CRC自动计算的起始位置
 #define CRC_CNT                        (CRC_BASE     + 0x04)                   // RV:    0000H    CRC块数计数器
 #define CCFG0                          (CCFG_BASE    + 0x0F)                   /* factory */
 #define CCFG1                          (CCFG_BASE    + 0x0E)                   /* factory */
 #define CCFG2                          (CCFG_BASE    + 0x0D)
 #define CCFG3                          (CCFG_BASE    + 0x0C)
 #define TCFG1                          (CCFG_BASE    + 0x09)                   /* factory */
 #define TCFG0                          (CCFG_BASE    + 0x08)                   /* factory */
 #define BCFG7                          (CCFG_BASE    + 0x07)                   /* factory */
 #define BCFG6                          (CCFG_BASE    + 0x06)                   /* factory */ 
 #define BCFG5                          (CCFG_BASE    + 0x05)                   /* factory */
 #define BCFG4                          (CCFG_BASE    + 0x04)                   /* factory */
 #define BCFG3                          (CCFG_BASE    + 0x03)                   /* factory */
 #define BCFG2                          (CCFG_BASE    + 0x02)                   /* factory */
 #define BCFG1                          (CCFG_BASE    + 0x01)                   /* factory */
 #define BCFG0                          (CCFG_BASE    + 0x00)                   /* factory */

 #define ME_CR                          (ME_BASE      + 0x00)                   // RV:    0000H    ME控制寄存器
 #define ME_ST0                         (ME_BASE      + 0x01)                   // RV:    0000H    ME状态匹配0寄存器     /* factory */
 #define ME_ST1                         (ME_BASE      + 0x02)                   // RV:    0000H    ME状态匹配1寄存器      /* factory */
 #define ME_STR                         (ME_BASE      + 0x03)                   // RV:    0000H    ME状态寄存器           /* factory */
 #define ME_IER                         (ME_BASE      + 0x04)                   // RV:      00H    ME中断使能寄存器       /* factory */
 #define ME_IFR                         (ME_BASE      + 0x05)                   // RV:    0000H    ME中断标志寄存器       /* factory */
 #define ME_BF0                         (ME_BASE      + 0x08)                   // RV:    0000H    ME内部BUFFER0寄存器       /* factory */
 #define ME_BF1                         (ME_BASE      + 0x09)                   // RV:    0000H    ME内部BUFFER1寄存器       /* factory */
 #define ME_BF2                         (ME_BASE      + 0x0A)                   // RV:    0000H    ME内部BUFFER2寄存器       /* factory */
 #define ME_BF3                         (ME_BASE      + 0x0B)                   // RV:    0000H    ME内部BUFFER3寄存器       /* factory */
 #define ME_COR                         (ME_BASE      + 0x0C)                   // RV:      00H    ME CORDIC使能寄存器
 #define ME_BF4                         (ME_BASE      + 0x0D)                   // RV:    0000H    ME内部BUFFER4寄存器      /* factory */
 #define ME_BF5                         (ME_BASE      + 0x0E)                   // RV:    0000H    ME内部BUFFER5寄存器      /* factory */


 #define DRV1_CR                        (DRV1_BASE    + 0x00)                   // RV:      00H    DRV1控制寄存器
 #define DRV1_OUT                       (DRV1_BASE    + 0x01)                   // RV:    0000H    DRV1输出寄存器
 #define DRV1_IER                       (DRV1_BASE    + 0x02)                   // RV:      00H    DRV1中断使能寄存器
 #define DRV1_IFR                       (DRV1_BASE    + 0x03)                   // RV:      00H    DRV1中断标志寄存器
 #define DRV1_PER                       (DRV1_BASE    + 0x04)                   // RV:    0000H    DRV1保护使能寄存器
 #define DRV1_PTR                       (DRV1_BASE    + 0x05)                   // RV:    0000H    DRV1保护触发寄存器
 #define DRV1_PSR                       (DRV1_BASE    + 0x06)                   // RV:    0000H    DRV1保护状态寄存器
 #define DRV1_CMR                       (DRV1_BASE    + 0x07)                   // RV:    0000H    DRV1使能和极性寄存器
 #define DRV1_FCR0                      (DRV1_BASE    + 0x08)                   // RV:    0000H    DRV1 FOC控制0寄存器
 #define DRV1_FCR1                      (DRV1_BASE    + 0x09)                   // RV:    0000H    DRV1 FOC控制1寄存器
 #define DRV1_FCR2                      (DRV1_BASE    + 0x0a)                   // RV:    0000H    DRV1 FOC控制2寄存器
 #define DRV1_FCR3                      (DRV1_BASE    + 0x0b)                   // RV:    0000H    DRV1 FOC控制3寄存器
 #define DRV1_FCR4                      (DRV1_BASE    + 0x0c)                   // RV:    0000H    DRV1 FOC控制4寄存器
 #define DRV1_FCR5                      (DRV1_BASE    + 0x0d)                   // RV:    0000H    DRV1 FOC控制5寄存器
 #define DRV1_FCR6                      (DRV1_BASE    + 0x0e)                   // RV:    0000H    DRV1 FOC控制6寄存器
 #define DRV1_FCR7                      (DRV1_BASE    + 0x0f)                   // RV:    0000H    DRV1 FOC控制7寄存器
 #define DRV1_ARR                       (DRV1_BASE    + 0x10)                   // RV:    0000H    DRV1自动重载寄存器
 #define DRV1_DR                        (DRV1_BASE    + 0x11)                   // RV:    0000H    DRV1数据寄存器，一次性控制UVW上下计数共6个寄存器
 #define DRV1_COMR                      (DRV1_BASE    + 0x12)                   // RV:    0000H    DRV1比较寄存器
 #define DRV1_DTR                       (DRV1_BASE    + 0x13)                   // RV:      00H    DRV1死区寄存器
 #define DRV1_CMPU1                     (DRV1_BASE    + 0x14)                   // RV:    0000H    DRV1 U相向上计数DR寄存器
 #define DRV1_CMPD1                     (DRV1_BASE    + 0x15)                   // RV:    0000H    DRV1 U相向下计数DR寄存器
 #define DRV1_CMPU2                     (DRV1_BASE    + 0x16)                   // RV:    0000H    DRV1 V相向上计数DR寄存器
 #define DRV1_CMPD2                     (DRV1_BASE    + 0x17)                   // RV:    0000H    DRV1 V相向下计数DR寄存器
 #define DRV1_CMPU3                     (DRV1_BASE    + 0x18)                   // RV:    0000H    DRV1 W相向上计数DR寄存器
 #define DRV1_CMPD3                     (DRV1_BASE    + 0x19)                   // RV:    0000H    DRV1 W相向下计数DR寄存器
 #define DRV1_CNTR                      (DRV1_BASE    + 0x1a)                   // RV:    0000H    DRV1 计数器
 #define DRV1_TRG1						(DRV1_BASE    + 0x1b)                   // RV:    0000H    DRV1 第1次采样的DR值
 #define DRV1_TRG2						(DRV1_BASE    + 0x1c)                   // RV:    0000H    DRV1 第2次采样的DR值


 #define DRV2_CR                        (DRV2_BASE    + 0x00)                   // RV:      00H    DRV2控制寄存器
 #define DRV2_OUT                       (DRV2_BASE    + 0x01)                   // RV:    0000H    DRV2输出寄存器
 #define DRV2_IER                       (DRV2_BASE    + 0x02)                   // RV:      00H    DRV2中断使能寄存器
 #define DRV2_IFR                       (DRV2_BASE    + 0x03)                   // RV:      00H    DRV2中断标志寄存器
 #define DRV2_PER                       (DRV2_BASE    + 0x04)                   // RV:    0000H    DRV2保护使能寄存器
 #define DRV2_PTR                       (DRV2_BASE    + 0x05)                   // RV:    0000H    DRV2保护触发寄存器
 #define DRV2_PSR                       (DRV2_BASE    + 0x06)                   // RV:    0000H    DRV2保护状态寄存器
 #define DRV2_CMR                       (DRV2_BASE    + 0x07)                   // RV:    0000H    DRV2使能和极性寄存器
 #define DRV2_FCR0                      (DRV2_BASE    + 0x08)                   // RV:    0000H    DRV2 FOC控制0寄存器
 #define DRV2_FCR1                      (DRV2_BASE    + 0x09)                   // RV:    0000H    DRV2 FOC控制1寄存器
 #define DRV2_FCR2                      (DRV2_BASE    + 0x0a)                   // RV:    0000H    DRV2 FOC控制2寄存器
 #define DRV2_ARR                       (DRV2_BASE    + 0x10)                   // RV:    0000H    DRV2自动重载寄存器
 #define DRV2_DR                        (DRV2_BASE    + 0x11)                   // RV:    0000H    DRV2数据寄存器，一次性控制UVW上下计数共6个寄存器
 #define DRV2_COMR                      (DRV2_BASE    + 0x12)                   // RV:    0000H    DRV2比较寄存器
 #define DRV2_DTR                       (DRV2_BASE    + 0x13)                   // RV:      00H    DRV2死区寄存器
 #define DRV2_CMPU1                     (DRV2_BASE    + 0x14)                   // RV:    0000H    DRV2 U相向上计数DR寄存器
 #define DRV2_CMPD1                     (DRV2_BASE    + 0x15)                   // RV:    0000H    DRV2 U相向下计数DR寄存器
 #define DRV2_CMPU2                     (DRV2_BASE    + 0x16)                   // RV:    0000H    DRV2 V相向上计数DR寄存器
 #define DRV2_CMPD2                     (DRV2_BASE    + 0x17)                   // RV:    0000H    DRV2 V相向下计数DR寄存器
 #define DRV2_CMPU3                     (DRV2_BASE    + 0x18)                   // RV:    0000H    DRV2 W相向上计数DR寄存器
 #define DRV2_CMPD3                     (DRV2_BASE    + 0x19)                   // RV:    0000H    DRV2 W相向下计数DR寄存器
 #define DRV2_CNTR                      (DRV2_BASE    + 0x1a)                   // RV:    0000H    DRV2 计数器

 #define BISS_CLK_CNT                   (BISS_BASE + 0x01)                      // RV:      00H    0=6MHz; 1=3MHz; 2=2MHz; 3=1.5MHz;
 #define BISS_OVERTIME_CNT              (BISS_BASE + 0x02)                      // RV:    00FFH    BiSS
 #define BISS_DATA_LEN                  (BISS_BASE + 0x03)                      // RV:      00H    BiSS data length
 #define BISS_STATE                     (BISS_BASE + 0x04)                      // RV:      00H    BiSS state
 #define BISS_SDATAL                    (BISS_BASE + 0x05)                      // RV:00000000H    BiSS data low 32 bit
 #define BISS_SDATAH                    (BISS_BASE + 0x06)                      // RV:00000000H    BiSS data high 32 bit

 #define PFC_CR0                        (PFC_BASE + 0x00)                       // RV:    0000H    PFC控制寄存器0
 #define PFC_CR1                        (PFC_BASE + 0x01)                       // RV:      00H    PFC控制寄存器1
 #define PFC_CR2                        (PFC_BASE + 0x02)                       // RV:    0000H    PFC控制寄存器2
 #define PFC_KM                         (PFC_BASE + 0x03)                       // RV:    0000H    PFC的KM系数
 #define UAC_CSO                        (PFC_BASE + 0x04)                       // RV:    0000H    UAC的采样基准值
 #define IAC1_CSO                       (PFC_BASE + 0x05)                       // RV:    0000H    IAC的采样基准值
 #define IAC2_CSO                       (PFC_BASE + 0x06)                       // RV:    0000H    IAC2的采样基准值
 #define PFC_ARR                        (PFC_BASE + 0x07)                       // RV:    0000H    PFC的计数器重载值
 #define PFC_DR1                        (PFC_BASE + 0x08)                       // RV:    0000H    PFC的计数器比较值
 #define PFC_DR2                        (PFC_BASE + 0x09)                       // RV:    0000H    PFC2的计数器比较值
 #define UDC_ARR                        (PFC_BASE + 0x0a)                       // RV:    0000H    外环执行频率  电压环的执行频率=PFC载波频率/UDC_ARR
 #define PFC_TRGDLY                     (PFC_BASE + 0x0b)                       // RV:    0000H    IAC/IAC2采样延迟
 #define UDC_REF                        (PFC_BASE + 0x0c)                       // RV:    0000H    UDC的PI参考值
 #define UDC_UK                         (PFC_BASE + 0x0d)                       // RV:    0000H    UDC的PI输出值
 #define UDC_KP                         (PFC_BASE + 0x0e)                       // RV:    0000H    UDC的PI的比例参数
 #define UDC_KI                         (PFC_BASE + 0x0f)                       // RV:    0000H    UDC的PI的积分参数
 #define UDC_UKMAX                      (PFC_BASE + 0x10)                       // RV:    0000H    UDC的PI最大输出值
 #define UDC_UKMIN                      (PFC_BASE + 0x11)                       // RV:    0000H    UDC的PI最小输出值
 #define IAC1_REF                       (PFC_BASE + 0x12)                       // RV:    0000H    IAC的PI参考值
 #define IAC1_UK                        (PFC_BASE + 0x13)                       // RV:    0000H    IAC的PI输出值
 #define IAC1_KP                        (PFC_BASE + 0x14)                       // RV:    0000H    IAC的PI的比例参数
 #define IAC1_KI                        (PFC_BASE + 0x15)                       // RV:    0000H    IAC的PI的积分参数
 #define IAC1_UKMAX                     (PFC_BASE + 0x16)                       // RV:    0000H    IAC的PI最大输出值
 #define IAC1_UKMIN                     (PFC_BASE + 0x17)                       // RV:    0000H    IAC的PI最小输出值
 #define IAC2_REF                       (PFC_BASE + 0x18)                       // RV:    0000H    IAC2的PI参考值
 #define IAC2_UK                        (PFC_BASE + 0x19)                       // RV:    0000H    IAC2的PI输出值
 #define IAC2_KP                        (PFC_BASE + 0x1a)                       // RV:    0000H    IAC2的PI的比例参数
 #define IAC2_KI                        (PFC_BASE + 0x1b)                       // RV:    0000H    IAC2的PI的积分参数
 #define IAC2_UKMAX                     (PFC_BASE + 0x1c)                       // RV:    0000H    IAC2的PI最大输出值
 #define IAC2_UKMIN                     (PFC_BASE + 0x1d)                       // RV:    0000H    IAC2的PI最小输出值
 #define PFC_UAC                        (PFC_BASE + 0x1e)                       // RV:    0000H    UAC采样值
 #define PFC_IAC1                       (PFC_BASE + 0x1f)                       // RV:    0000H    IAC采样值
 #define PFC_IAC2                       (PFC_BASE + 0x20)                       // RV:    0000H    IAC2采样值
 #define PFC_UDC                        (PFC_BASE + 0x21)                       // RV:    0000H    UDC采样值
 #define PFC_UAVG                       (PFC_BASE + 0x22)                       // RV:    7FFFH    UAC的平均值
 #define PFC_COM                        (PFC_BASE + 0x23)                       // RV:    0000H    内环前馈补偿值
 #define PFC_KCOM                       (PFC_BASE + 0x24)                       // RV:    0000H    内环前馈补偿系数
 #define PFC_DDCM                       (PFC_BASE + 0x25)                       // RV:    0000H    内环前馈补偿DDCM模式补偿量
 #define PFC_DCCM                       (PFC_BASE + 0x26)                       // RV:    0000H    内环前馈补偿DCCM模式补偿量
 #define PFC_KDDCM                      (PFC_BASE + 0x27)                       // RV:    0000H    DDCM模式补偿量的系数
 #define PFC_DCCMCSO                    (PFC_BASE + 0x28)                       // RV:    0000H    DCCM的调节系数
 #define PFC_KIAC1                      (PFC_BASE + 0x29)                       // RV:    4000H    前馈补偿时IAC采样的校正系数，DDCM时使用
 #define PFC_KIAC2                      (PFC_BASE + 0x2a)                       // RV:    4000H    前馈补偿时IAC2采样的校正系数，DDCM时使用

// #define TIM1_CR0                      (TIME1_BASE   + 0x00)                  // RV:      00H
// #define TIM1_CR1                      (TIME1_BASE   + 0x01)                  // RV:      00H
// #define TIM1_CR2                      (TIME1_BASE   + 0x02)                  // RV:      00H
// #define TIM1_CR3                      (TIME1_BASE   + 0x03)                  // RV:      00H
// #define TIM1_CR4                      (TIME1_BASE   + 0x04)                  // RV:      00H
// #define TIM1_IER                      (TIME1_BASE   + 0x05)                  // RV:      00H
// #define TIM1_SR                       (TIME1_BASE   + 0x06)                  // RV:      00H
// #define TIM1_BCOR                     (TIME1_BASE   + 0x07)                  // RV:    0000H
// #define TIM1_DBR1                     (TIME1_BASE   + 0x09)                  // RV:    0000H
// #define TIM1_DBR2                     (TIME1_BASE   + 0x0a)                  // RV:    0000H
// #define TIM1_DBR3                     (TIME1_BASE   + 0x0b)                  // RV:    0000H
// #define TIM1_DBR4                     (TIME1_BASE   + 0x0c)                  // RV:    0000H
// #define TIM1_DBR5                     (TIME1_BASE   + 0x0d)                  // RV:    0000H
// #define TIM1_DBR6                     (TIME1_BASE   + 0x0e)                  // RV:    0000H
// #define TIM1_DBR7                     (TIME1_BASE   + 0x0f)                  // RV:    0000H
// #define TIM1_BCNTR                    (TIME1_BASE   + 0x10)                  // RV:    0000H
// #define TIM1_BCCR                     (TIME1_BASE   + 0x11)                  // RV:    0000H
// #define TIM1_BARR                     (TIME1_BASE   + 0x12)                  // RV:    0000H
// #define TIM1_RARR                     (TIME1_BASE   + 0x13)                  // RV:    0000H
// #define TIM1_RCNTR                    (TIME1_BASE   + 0x14)                  // RV:    0000H
// #define TIM1_UCOP                     (TIME1_BASE   + 0x15)
// #define TIM1_UFLP                     (TIME1_BASE   + 0x16)
// #define TIM1_URES                     (TIME1_BASE   + 0x17)
// #define TIM1_UIGN                     (TIME1_BASE   + 0x18)
// #define TIM1_KF                       (TIME1_BASE   + 0x19)
// #define TIM1_KR                       (TIME1_BASE   + 0x1a)
// #define TIM1_ITRIP                    (TIME1_BASE   + 0x1b)                   // RV:    0000H
//
/******************************************************************************/
/*                                                                            */
/*                          Registers Bits Definition                         */
/*                                                                            */
/******************************************************************************/

/******************************************************************************/
/*                                    GPIO                                    */
/******************************************************************************/
/********************** Bits definition for PA register *********************/
#define PA15                            0x8000                                  // rw-- 管脚PA15
#define PA14                            0x4000                                  // rw-- 管脚PA14
#define PA13                            0x2000                                  // rw-- 管脚PA13
#define PA12                            0x1000                                  // rw-- 管脚PA12
#define PA11                            0x800                                   // rw-- 管脚PA11
#define PA10                            0x400                                   // rw-- 管脚PA10
#define PA9                             0x200                                   // rw-- 管脚PA9
#define PA8                             0x100                                   // rw-- 管脚PA8
#define PA7                             0x80                                    // rw-- 管脚PA7
#define PA6                             0x40                                    // rw-- 管脚PA6
#define PA5                             0x20                                    // rw-- 管脚PA5
#define PA4                             0x10                                    // rw-- 管脚PA4
#define PA3                             0x08                                    // rw-- 管脚PA3
#define PA2                             0x04                                    // rw-- 管脚PA2
#define PA1                             0x02                                    // rw-- 管脚PA1
#define PA0                             0x01                                    // rw-- 管脚PA0
/********************** Bits definition for PA_OE register *********************/
#define PA15OE                          0x8000                                  // rw-- 管脚PA15输出使能位
#define PA14OE                          0x4000                                  // rw-- 管脚PA14输出使能位
#define PA13OE                          0x2000                                  // rw-- 管脚PA13输出使能位
#define PA12OE                          0x1000                                  // rw-- 管脚PA12输出使能位
#define PA11OE                          0x800                                   // rw-- 管脚PA11输出使能位
#define PA10OE                          0x400                                   // rw-- 管脚PA10输出使能位
#define PA9OE                           0x200                                   // rw-- 管脚PA9输出使能位
#define PA8OE                           0x100                                   // rw-- 管脚PA8输出使能位
#define PA7OE                           0x80                                    // rw-- 管脚PA7输出使能位
#define PA6OE                           0x40                                    // rw-- 管脚PA6输出使能位
#define PA5OE                           0x20                                    // rw-- 管脚PA5输出使能位
#define PA4OE                           0x10                                    // rw-- 管脚PA4输出使能位
#define PA3OE                           0x08                                    // rw-- 管脚PA3输出使能位
#define PA2OE                           0x04                                    // rw-- 管脚PA2输出使能位
#define PA1OE                           0x02                                    // rw-- 管脚PA1输出使能位
#define PA0OE                           0x01                                    // rw-- 管脚PA0输出使能位
/********************** Bits definition for PA_PU register *********************/
#define PA15PU                          0x8000                                  // rw-- 管脚PA15上拉使能位
#define PA14PU                          0x4000                                  // rw-- 管脚PA14上拉使能位
#define PA13PU                          0x2000                                  // rw-- 管脚PA13上拉使能位
#define PA12PU                          0x1000                                  // rw-- 管脚PA12上拉使能位
#define PA11PU                          0x800                                   // rw-- 管脚PA11上拉使能位
#define PA10PU                          0x400                                   // rw-- 管脚PA10上拉使能位
#define PA9PU                           0x200                                   // rw-- 管脚PA9上拉使能位
#define PA8PU                           0x100                                   // rw-- 管脚PA8上拉使能位
#define PA7PU                           0x80                                    // rw-- 管脚PA7上拉使能位
#define PA6PU                           0x40                                    // rw-- 管脚PA6上拉使能位
#define PA5PU                           0x20                                    // rw-- 管脚PA5上拉使能位
#define PA4PU                           0x10                                    // rw-- 管脚PA4上拉使能位
#define PA3PU                           0x08                                    // rw-- 管脚PA3上拉使能位
#define PA2PU                           0x04                                    // rw-- 管脚PA2上拉使能位
#define PA1PU                           0x02                                    // rw-- 管脚PA1上拉使能位
#define PA0PU                           0x01                                    // rw-- 管脚PA0上拉使能位
/********************** Bits definition for PA_PL register *********************/
#define PA15PL                          0x8000                                  // rw-- 管脚PA15下拉使能位
#define PA14PL                          0x4000                                  // rw-- 管脚PA14下拉使能位
#define PA13PL                          0x2000                                  // rw-- 管脚PA13下拉使能位
#define PA12PL                          0x1000                                  // rw-- 管脚PA12下拉使能位
#define PA11PL                          0x800                                   // rw-- 管脚PA11下拉使能位
#define PA10PL                          0x400                                   // rw-- 管脚PA10下拉使能位
#define PA9PL                           0x200                                   // rw-- 管脚PA9下拉使能位
#define PA8PL                           0x100                                   // rw-- 管脚PA8下拉使能位
#define PA7PL                           0x80                                    // rw-- 管脚PA7下拉使能位
#define PA6PL                           0x40                                    // rw-- 管脚PA6下拉使能位
#define PA5PL                           0x20                                    // rw-- 管脚PA5下拉使能位
#define PA4PL                           0x10                                    // rw-- 管脚PA4下拉使能位
#define ODEN1                           0x08                                    // rw-- 
#define ODEN0                           0x04                                    // rw-- 
#define PA1PL                           0x02                                    // rw-- 管脚PA1下拉使能位
#define PA0PL                           0x01                                    // rw-- 管脚PA0下拉使能位

/********************** Bits definition for PB register *********************/
#define PB15                            0x8000                                  // rw-- 管脚PB15
#define PB14                            0x4000                                  // rw-- 管脚PB14
#define PB13                            0x2000                                  // rw-- 管脚PB13
#define PB12                            0x1000                                  // rw-- 管脚PB12
#define PB11                            0x800                                   // rw-- 管脚PB11
#define PB10                            0x400                                   // rw-- 管脚PB10
#define PB9                             0x200                                   // rw-- 管脚PB9
#define PB8                             0x100                                   // rw-- 管脚PB8
#define PB7                             0x80                                    // rw-- 管脚PB7
#define PB6                             0x40                                    // rw-- 管脚PB6
#define PB5                             0x20                                    // rw-- 管脚PB5
#define PB4                             0x10                                    // rw-- 管脚PB4
#define PB3                             0x08                                    // rw-- 管脚PB3
#define PB2                             0x04                                    // rw-- 管脚PB2
#define PB1                             0x02                                    // rw-- 管脚PB1
#define PB0                             0x01                                    // rw-- 管脚PB0
/********************** Bits definition for PB_OE register *********************/
#define PB15OE                          0x8000                                  // rw-- 管脚PB15输出使能位
#define PB14OE                          0x4000                                  // rw-- 管脚PB14输出使能位
#define PB13OE                          0x2000                                  // rw-- 管脚PB13输出使能位
#define PB12OE                          0x1000                                  // rw-- 管脚PB12输出使能位
#define PB11OE                          0x800                                   // rw-- 管脚PB11输出使能位
#define PB10OE                          0x400                                   // rw-- 管脚PB10输出使能位
#define PB9OE                           0x200                                   // rw-- 管脚PB9输出使能位
#define PB8OE                           0x100                                   // rw-- 管脚PB8输出使能位
#define PB7OE                           0x80                                    // rw-- 管脚PB7输出使能位
#define PB6OE                           0x40                                    // rw-- 管脚PB6输出使能位
#define PB5OE                           0x20                                    // rw-- 管脚PB5输出使能位
#define PB4OE                           0x10                                    // rw-- 管脚PB4输出使能位
#define PB3OE                           0x08                                    // rw-- 管脚PB3输出使能位
#define PB2OE                           0x04                                    // rw-- 管脚PB2输出使能位
#define PB1OE                           0x02                                    // rw-- 管脚PB1输出使能位
#define PB0OE                           0x01                                    // rw-- 管脚PB0输出使能位
/********************** Bits definition for PB_PU register *********************/
#define PB15PU                          0x8000                                  // rw-- 管脚PB15上拉使能位
#define PB14PU                          0x4000                                  // rw-- 管脚PB14上拉使能位
#define PB13PU                          0x2000                                  // rw-- 管脚PB13上拉使能位
#define PB12PU                          0x1000                                  // rw-- 管脚PB12上拉使能位
#define PB11PU                          0x800                                   // rw-- 管脚PB11上拉使能位
#define PB10PU                          0x400                                   // rw-- 管脚PB10上拉使能位
#define PB9PU                           0x200                                   // rw-- 管脚PB9上拉使能位
#define PB8PU                           0x100                                   // rw-- 管脚PB8上拉使能位
#define PB7PU                           0x80                                    // rw-- 管脚PB7上拉使能位
#define PB6PU                           0x40                                    // rw-- 管脚PB6上拉使能位
#define PB5PU                           0x20                                    // rw-- 管脚PB5上拉使能位
#define PB4PU                           0x10                                    // rw-- 管脚PB4上拉使能位
#define PB3PU                           0x08                                    // rw-- 管脚PB3上拉使能位
#define PB2PU                           0x04                                    // rw-- 管脚PB2上拉使能位
#define PB1PU                           0x02                                    // rw-- 管脚PB1上拉使能位
#define PB0PU                           0x01                                    // rw-- 管脚PB0上拉使能位
/********************** Bits definition for PB_AN register *********************/
#define PB15AN                          0x8000                                  // rw-- 管脚PB15模拟使能位
#define PB14AN                          0x4000                                  // rw-- 管脚PB14模拟使能位
#define PB13AN                          0x2000                                  // rw-- 管脚PB13模拟使能位
#define PB12AN                          0x1000                                  // rw-- 管脚PB12模拟使能位
#define PB11AN                          0x800                                   // rw-- 管脚PB11模拟使能位
#define PB10AN                          0x400                                   // rw-- 管脚PB10模拟使能位
#define PB9AN                           0x200                                   // rw-- 管脚PB9模拟使能位
#define PB8AN                           0x100                                   // rw-- 管脚PB8模拟使能位
#define PB7AN                           0x80                                    // rw-- 管脚PB7模拟使能位
#define PB6AN                           0x40                                    // rw-- 管脚PB6模拟使能位
#define PB5AN                           0x20                                    // rw-- 管脚PB5模拟使能位
#define PB4AN                           0x10                                    // rw-- 管脚PB4模拟使能位
#define PB3AN                           0x08                                    // rw-- 管脚PB3模拟使能位
#define PB1AN                           0x02                                    // rw-- 管脚PB1模拟使能位
#define PB0AN                           0x01                                    // rw-- 管脚PB0模拟使能位

/********************** Bits definition for PC register *********************/
#define PC15                            0x8000                                  // rw-- 管脚PC15
#define PC14                            0x4000                                  // rw-- 管脚PC14
#define PC13                            0x2000                                  // rw-- 管脚PC13
#define PC12                            0x1000                                  // rw-- 管脚PC12
#define PC11                            0x800                                   // rw-- 管脚PC11
#define PC10                            0x400                                   // rw-- 管脚PC10
#define PC9                             0x200                                   // rw-- 管脚PC9
#define PC8                             0x100                                   // rw-- 管脚PC8
#define PC7                             0x80                                    // rw-- 管脚PC7
#define PC6                             0x40                                    // rw-- 管脚PC6
#define PC5                             0x20                                    // rw-- 管脚PC5
#define PC4                             0x10                                    // rw-- 管脚PC4
#define PC3                             0x08                                    // rw-- 管脚PC3
#define PC2                             0x04                                    // rw-- 管脚PC2
#define PC1                             0x02                                    // rw-- 管脚PC1
#define PC0                             0x01                                    // rw-- 管脚PC0
/********************** Bits definition for PC_OE register *********************/
#define PC15OE                          0x8000                                  // rw-- 管脚PC15输出使能位
#define PC14OE                          0x4000                                  // rw-- 管脚PC14输出使能位
#define PC13OE                          0x2000                                  // rw-- 管脚PC13输出使能位
#define PC12OE                          0x1000                                  // rw-- 管脚PC12输出使能位
#define PC11OE                          0x800                                   // rw-- 管脚PC11输出使能位
#define PC10OE                          0x400                                   // rw-- 管脚PC10输出使能位
#define PC9OE                           0x200                                   // rw-- 管脚PC9输出使能位
#define PC8OE                           0x100                                   // rw-- 管脚PC8输出使能位
#define PC7OE                           0x80                                    // rw-- 管脚PC7输出使能位
#define PC6OE                           0x40                                    // rw-- 管脚PC6输出使能位
#define PC5OE                           0x20                                    // rw-- 管脚PC5输出使能位
#define PC4OE                           0x10                                    // rw-- 管脚PC4输出使能位
#define PC3OE                           0x08                                    // rw-- 管脚PC3输出使能位
#define PC2OE                           0x04                                    // rw-- 管脚PC2输出使能位
#define PC1OE                           0x02                                    // rw-- 管脚PC1输出使能位
#define PC0OE                           0x01                                    // rw-- 管脚PC0输出使能位
/********************** Bits definition for PC_PU register *********************/
#define PC15PU                          0x8000                                  // rw-- 管脚PC15上拉使能位
#define PC14PU                          0x4000                                  // rw-- 管脚PC14上拉使能位
#define PC13PU                          0x2000                                  // rw-- 管脚PC13上拉使能位
#define PC12PU                          0x1000                                  // rw-- 管脚PC12上拉使能位
#define PC11PU                          0x800                                   // rw-- 管脚PC11上拉使能位
#define PC10PU                          0x400                                   // rw-- 管脚PC10上拉使能位
#define PC9PU                           0x200                                   // rw-- 管脚PC9上拉使能位
#define PC8PU                           0x100                                   // rw-- 管脚PC8上拉使能位
#define PC7PU                           0x80                                    // rw-- 管脚PC7上拉使能位
#define PC6PU                           0x40                                    // rw-- 管脚PC6上拉使能位
#define PC5PU                           0x20                                    // rw-- 管脚PC5上拉使能位
#define PC4PU                           0x10                                    // rw-- 管脚PC4上拉使能位
#define PC3PU                           0x08                                    // rw-- 管脚PC3上拉使能位
#define PC2PU                           0x04                                    // rw-- 管脚PC2上拉使能位
#define PC1PU                           0x02                                    // rw-- 管脚PC1上拉使能位
#define PC0PU                           0x01                                    // rw-- 管脚PC0上拉使能位
/********************** Bits definition for PC_AN register *********************/
#define PC15AN                          0x8000                                  // rw-- 管脚PC15模拟使能位
#define PC14AN                          0x4000                                  // rw-- 管脚PC14模拟使能位
#define PC13AN                          0x2000                                  // rw-- 管脚PC13模拟使能位
#define PC12AN                          0x1000                                  // rw-- 管脚PC12模拟使能位
#define PC11AN                          0x800                                   // rw-- 管脚PC11模拟使能位
#define PC10AN                          0x400                                   // rw-- 管脚PC10模拟使能位
#define PC9AN                           0x200                                   // rw-- 管脚PC9模拟使能位
#define PC8AN                           0x100                                   // rw-- 管脚PC8模拟使能位
#define PC7AN                           0x80                                    // rw-- 管脚PC7模拟使能位
#define PC6AN                           0x40                                    // rw-- 管脚PC6模拟使能位
#define PC5AN                           0x20                                    // rw-- 管脚PC5模拟使能位
#define PC4AN                           0x10                                    // rw-- 管脚PC4模拟使能位
#define PC3AN                           0x08                                    // rw-- 管脚PC3模拟使能位
#define PC2AN                           0x04                                    // rw-- 管脚PC1模拟使能位
#define PC1AN                           0x02                                    // rw-- 管脚PC1模拟使能位
#define PC0AN                           0x01                                    // rw-- 管脚PC0模拟使能位

/********************** Bits definition for PD register *********************/
#define PD6                             0x40                                    // rw-- 管脚PD6
#define PD5                             0x20                                    // rw-- 管脚PD5
#define PD4                             0x10                                    // rw-- 管脚PD4
#define PD3                             0x08                                    // rw-- 管脚PD3
#define PD2                             0x04                                    // rw-- 管脚PD2
#define PD1                             0x02                                    // rw-- 管脚PD1
#define PD0                             0x01                                    // rw-- 管脚PD0
/********************** Bits definition for PD_OE register *********************/
#define PD6OE                           0x40                                    // rw-- 管脚PD6输出使能位
#define PD5OE                           0x20                                    // rw-- 管脚PD5输出使能位
#define PD4OE                           0x10                                    // rw-- 管脚PD4输出使能位
#define PD3OE                           0x08                                    // rw-- 管脚PD3输出使能位
#define PD2OE                           0x04                                    // rw-- 管脚PD2输出使能位
#define PD1OE                           0x02                                    // rw-- 管脚PD1输出使能位
#define PD0OE                           0x01                                    // rw-- 管脚PD0输出使能位
/********************** Bits definition for PD_PU register *********************/
#define PD6PU                           0x40                                    // rw-- 管脚PD6上拉使能位
#define PD5PU                           0x20                                    // rw-- 管脚PD5上拉使能位
#define PD4PU                           0x10                                    // rw-- 管脚PD4上拉使能位
#define PD3PU                           0x08                                    // rw-- 管脚PD3上拉使能位
#define PD2PU                           0x04                                    // rw-- 管脚PD2上拉使能位
#define PD1PU                           0x02                                    // rw-- 管脚PD1上拉使能位
#define PD0PU                           0x01                                    // rw-- 管脚PD0上拉使能位
/********************** Bits definition for PD_AN register *********************/
#define PD6AN                           0x40                                    // rw-- 管脚PD6上拉使能位
#define PD5AN                           0x20                                    // rw-- 管脚PD5上拉使能位
#define PD4AN                           0x10                                    // rw-- 管脚PD4上拉使能位
#define PD3AN                           0x08                                    // rw-- 管脚PD3上拉使能位
#define PD2AN                           0x04                                    // rw-- 管脚PD2上拉使能位
#define PD1AN                           0x02                                    // rw-- 管脚PD1上拉使能位
#define PD0AN                           0x01                                    // rw-- 管脚PD0上拉使能位

/********************** Bits definition for Portx register *********************/
#define PIN15                           0x8000                                  // rw-- 管脚xPx15
#define PIN14                           0x4000                                  // rw-- 管脚xPx14
#define PIN13                           0x2000                                  // rw-- 管脚xPx13
#define PIN12                           0x1000                                  // rw-- 管脚xPx12
#define PIN11                           0x800                                   // rw-- 管脚xPx11
#define PIN10                           0x400                                   // rw-- 管脚xPx10
#define PIN9                            0x200                                   // rw-- 管脚xPx9
#define PIN8                            0x100                                   // rw-- 管脚xPx8
#define PIN7                            0x80                                    // rw-- 管脚xPx7
#define PIN6                            0x40                                    // rw-- 管脚xPx6
#define PIN5                            0x20                                    // rw-- 管脚xPx5
#define PIN4                            0x10                                    // rw-- 管脚xPx4
#define PIN3                            0x08                                    // rw-- 管脚xPx3
#define PIN2                            0x04                                    // rw-- 管脚xPx2
#define PIN1                            0x02                                    // rw-- 管脚xPx1
#define PIN0                            0x01                                    // rw-- 管脚xPx0
/********************* Bits definition for PH_SEL register ********************/
#define SFRCT                           0x80000000                              // rw-- 多摩川RE功能转移位
#define T5CT                            0x40000000                              // rw-- Timer5管脚功能转移位
#define T8CT1                           0x20000000                              // rw-- Timer8管脚使能位1
#define T8CT0                           0x10000000                              // rw-- Timer8管脚使能位0
#define DBGCT                           0x8000000                               // rw-- DBG管脚使能
#define DTCT                            0x4000000                               // rw-- DT管脚使能          /* factory */
#define CMPCT                           0x2000000                               // rw-- 比较器管脚使能位
#define MONCT1                          0x1000000                               // rw-- DataMonitor管脚使能位1
#define MONCT0                          0x800000                                // rw-- DataMonitor管脚使能位1
#define SPI2TMOD                        0x400000                                // rw-- SP12MISO高阻态
#define SPI1TMOD                        0x200000                                // rw-- SP11MISO高阻态
#define I2CCT                           0x100000                                // rw-- I2C管脚使能位
#define CANCT                           0x80000                                 // rw-- CAN管脚使能位
#define LINCT                           0x40000                                 // rw-- LIN管脚使能位
#define UT2CT1                          0x20000                                 // rw-- Uart2管脚使能位1
#define UT2CT0                          0x10000                                 // rw-- Uart2管脚使能位0
#define UT1CT1                          0x8000                                  // rw-- Uart1管脚使能位1
#define UT1CT0                          0x4000                                  // rw-- Uart1管脚使能位0
#define T7CT1                           0x2000                                  // rw-- Timer7管脚使能位1
#define T7CT0                           0x1000                                  // rw-- Timer7管脚使能位0
#define T6BCT                           0x800                                   // rw-- Timer6管脚B使能位
#define T6ACT1                          0x400                                   // rw-- Timer6管脚A使能位
#define T6ACT0                          0x200                                   // rw-- Timer6管脚A功能转移位0
#define T5BCT                           0x100                                   // rw-- Timer5管脚B使能位
#define T5ACT                           0x80                                    // rw-- Timer5管脚A使能位
#define T4CT1                           0x40                                    // rw-- Timer4管脚使能位1
#define T4CT0                           0x20                                    // rw-- Timer4管脚使能位0
#define T3CT1                           0x10                                    // rw-- Timer3管脚使能位1
#define T3CT0                           0x08                                    // rw-- Timer3管脚使能位0
#define T2BCT                           0x02                                    // rw-- Timer2管脚B使能位
#define T2ACT                           0x01                                    // rw-- Timer2管脚A使能位

/******************************************************************************/
/*                                     IRQ                                    */
/******************************************************************************/
/********************** Bits definition for MIE register **********************/
 #define IRQ_EN                         0x00000008                              // rw-- 总中断使能位
/********************** Bits definition for PIE register **********************/
 #define RTCIE                          0x10                                    // rw-- RTC中断使能位
 #define TSDIE                          0x08                                    // rw0- TSD中断使能位
 #define EX2                            0x04                                    // rw-- 外部中断2使能位
 #define EX1                            0x02                                    // rw-- 外部中断1使能位
 #define EX0                            0x01                                    // rw-- 外部中断0使能位
/********************* Bits definition for TCON register **********************/
 #define TSDIF                          0x40                                    // rw-- TSD中断标志位
 #define IT21                           0x20                                    // rw-- 外部中断2中断触发电平选择1
 #define IT20                           0x10                                    // rw-- 外部中断2中断触发电平选择0
 #define IT11                           0x08                                    // rw-- 外部中断1中断触发电平选择1
 #define IT10                           0x04                                    // rw-- 外部中断1中断触发电平选择0
 #define IT01                           0x02                                    // rw-- 外部中断0中断触发电平选择1
 #define IT00                           0x01                                    // rw-- 外部中断0中断触发电平选择0
/********************* Bits definition for LVSR register **********************/
 #define TSDF                           0x04                                    // r--- 过温标志位 /* factory */
 #define LVWF                           0x02                                    // r--- VCC低电压预警标志
 #define LVWIF                          0x01                                    // rw0- VCC低电压预警中断标志 
/********************* Bits definition for EX0IE register **********************/
 #define EX0IE15                        0x8000                                  // rw-- PD3端口外部中断0中断使能位
 #define EX0IE14                        0x4000                                  // rw-- PD1端口外部中断0中断使能位
 #define EX0IE13                        0x2000                                  // rw-- PD0端口外部中断0中断使能位
 #define EX0IE12                        0x1000                                  // rw-- PA12端口外部中断0中断使能位
 #define EX0IE11                        0x0800                                  // rw-- PA11端口外部中断0中断使能位
 #define EX0IE10                        0x0400                                  // rw-- PA10端口外部中断0中断使能位
 #define EX0IE9                         0x0200                                  // rw-- PA9端口外部中断0中断使能位
 #define EX0IE8                         0x0100                                  // rw-- PA8端口外部中断0中断使能位
 #define EX0IE7                         0x0080                                  // rw-- PA7端口外部中断0中断使能位
 #define EX0IE6                         0x0040                                  // rw-- PA6端口外部中断0中断使能位
 #define EX0IE5                         0x0020                                  // rw-- PA5端口外部中断0中断使能位
 #define EX0IE4                         0x0010                                  // rw-- PA4端口外部中断0中断使能位
 #define EX0IE3                         0x0008                                  // rw-- PA3端口外部中断0中断使能位
 #define EX0IE2                         0x0004                                  // rw-- PA2端口外部中断0中断使能位
 #define EX0IE1                         0x0002                                  // rw-- PA1端口外部中断0中断使能位
 #define EX0IE0                         0x0001                                  // rw-- PA0端口外部中断0中断使能位
/********************* Bits definition for EX1IE register **********************/
 #define EX1IE15                        0x8000                                  // rw-- PB2端口外部中断1中断使能位
 #define EX1IE14                        0x4000                                  // rw-- PA14端口外部中断1中断使能位
 #define EX1IE13                        0x2000                                  // rw-- PA12端口外部中断1中断使能位
 #define EX1IE12                        0x1000                                  // rw-- PA12端口外部中断1中断使能位
 #define EX1IE11                        0x0800                                  // rw-- PA11端口外部中断1中断使能位
 #define EX1IE10                        0x0400                                  // rw-- PA10端口外部中断1中断使能位
 #define EX1IE9                         0x0200                                  // rw-- PA9端口外部中断1中断使能位
 #define EX1IE8                         0x0100                                  // rw-- PA8端口外部中断1中断使能位
 #define EX1IE7                         0x0080                                  // rw-- PA7端口外部中断1中断使能位
 #define EX1IE6                         0x0040                                  // rw-- PA6端口外部中断1中断使能位
 #define EX1IE5                         0x0020                                  // rw-- PA5端口外部中断1中断使能位
 #define EX1IE4                         0x0010                                  // rw-- PA4端口外部中断1中断使能位
 #define EX1IE3                         0x0008                                  // rw-- PA3端口外部中断1中断使能位
 #define EX1IE2                         0x0004                                  // rw-- PA2端口外部中断1中断使能位
 #define EX1IE1                         0x0002                                  // rw-- PA1端口外部中断1中断使能位
 #define EX1IE0                         0x0001                                  // rw-- PA0端口外部中断1中断使能位
 /********************* Bits definition for EX2IE register **********************/
 #define EX2IE15                        0x8000                                  // rw-- PC7端口外部中断2中断使能位
 #define EX2IE14                        0x4000                                  // rw-- PC6端口外部中断2中断使能位
 #define EX2IE13                        0x2000                                  // rw-- PC5端口外部中断2中断使能位
 #define EX2IE12                        0x1000                                  // rw-- PC4端口外部中断2中断使能位
 #define EX2IE11                        0x0800                                  // rw-- PC3端口外部中断2中断使能位
 #define EX2IE10                        0x0400                                  // rw-- PC2端口外部中断2中断使能位
 #define EX2IE9                         0x0200                                  // rw-- PC1端口外部中断2中断使能位
 #define EX2IE8                         0x0100                                  // rw-- PC0端口外部中断2中断使能位
 #define EX2IE7                         0x0080                                  // rw-- PB7端口外部中断2中断使能位
 #define EX2IE6                         0x0040                                  // rw-- PB6端口外部中断2中断使能位
 #define EX2IE5                         0x0020                                  // rw-- PB5端口外部中断2中断使能位
 #define EX2IE4                         0x0010                                  // rw-- PB4端口外部中断2中断使能位
 #define EX2IE3                         0x0008                                  // rw-- PB3端口外部中断2中断使能位
 #define EX2IE2                         0x0004                                  // rw-- PB2端口外部中断2中断使能位
 #define EX2IE1                         0x0002                                  // rw-- PB1端口外部中断2中断使能位
 #define EX2IE0                         0x0001                                  // rw-- PB0端口外部中断2中断使能位
/********************* Bits definition for EX0IF register **********************/
 #define EX0IF15                        0x8000                                  // rw0- PD3端口外部中断0中断标志位
 #define EX0IF14                        0x4000                                  // rw0- PD1端口外部中断0中断标志位
 #define EX0IF13                        0x2000                                  // rw0- PD0端口外部中断0中断标志位
 #define EX0IF12                        0x1000                                  // rw0- PA12端口外部中断0中断标志位
 #define EX0IF11                        0x0800                                  // rw0- PA11端口外部中断0中断标志位
 #define EX0IF10                        0x0400                                  // rw0- PA10端口外部中断0中断标志位
 #define EX0IF9                         0x0200                                  // rw0- PA9端口外部中断0中断标志位
 #define EX0IF8                         0x0100                                  // rw0- PA8端口外部中断0中断标志位
 #define EX0IF7                         0x0080                                  // rw0- PA7端口外部中断0中断标志位
 #define EX0IF6                         0x0040                                  // rw0- PA6端口外部中断0中断标志位
 #define EX0IF5                         0x0020                                  // rw0- PA5端口外部中断0中断标志位
 #define EX0IF4                         0x0010                                  // rw0- PA4端口外部中断0中断标志位
 #define EX0IF3                         0x0008                                  // rw0- PA3端口外部中断0中断标志位
 #define EX0IF2                         0x0004                                  // rw0- PA2端口外部中断0中断标志位
 #define EX0IF1                         0x0002                                  // rw0- PA1端口外部中断0中断标志位
 #define EX0IF0                         0x0001                                  // rw0- PA0端口外部中断0中断标志位
/********************* Bits definition for EX1IF register **********************/
 #define EX1IF15                        0x8000                                  // rw0- PB2端口外部中断1中断标志位
 #define EX1IF14                        0x4000                                  // rw0- PA14端口外部中断1中断标志位
 #define EX1IF13                        0x2000                                  // rw0- PA12端口外部中断1中断标志位
 #define EX1IF12                        0x1000                                  // rw0- PA12端口外部中断1中断标志位
 #define EX1IF11                        0x0800                                  // rw0- PA11端口外部中断1中断标志位
 #define EX1IF10                        0x0400                                  // rw0- PA10端口外部中断1中断标志位
 #define EX1IF9                         0x0200                                  // rw0- PA9端口外部中断1中断标志位
 #define EX1IF8                         0x0100                                  // rw0- PA8端口外部中断1中断标志位
 #define EX1IF7                         0x0080                                  // rw0- PA7端口外部中断1中断标志位
 #define EX1IF6                         0x0040                                  // rw0- PA6端口外部中断1中断标志位
 #define EX1IF5                         0x0020                                  // rw0- PA5端口外部中断1中断标志位
 #define EX1IF4                         0x0010                                  // rw0- PA4端口外部中断1中断标志位
 #define EX1IF3                         0x0008                                  // rw0- PA3端口外部中断1中断标志位
 #define EX1IF2                         0x0004                                  // rw0- PA2端口外部中断1中断标志位
 #define EX1IF1                         0x0002                                  // rw0- PA1端口外部中断1中断标志位
 #define EX1IF0                         0x0001                                  // rw0- PA0端口外部中断1中断标志位
 /********************* Bits definition for EX2IF register **********************/
 #define EX2IF15                        0x8000                                  // rw0- PC7端口外部中断2中断标志位
 #define EX2IF14                        0x4000                                  // rw0- PC6端口外部中断2中断标志位
 #define EX2IF13                        0x2000                                  // rw0- PC5端口外部中断2中断标志位
 #define EX2IF12                        0x1000                                  // rw0- PC4端口外部中断2中断标志位
 #define EX2IF11                        0x0800                                  // rw0- PC3端口外部中断2中断标志位
 #define EX2IF10                        0x0400                                  // rw0- PC2端口外部中断2中断标志位
 #define EX2IF9                         0x0200                                  // rw0- PC1端口外部中断2中断标志位
 #define EX2IF8                         0x0100                                  // rw0- PC0端口外部中断2中断标志位
 #define EX2IF7                         0x0080                                  // rw0- PB7端口外部中断2中断标志位
 #define EX2IF6                         0x0040                                  // rw0- PB6端口外部中断2中断标志位
 #define EX2IF5                         0x0020                                  // rw0- PB5端口外部中断2中断标志位
 #define EX2IF4                         0x0010                                  // rw0- PB4端口外部中断2中断标志位
 #define EX2IF3                         0x0008                                  // rw0- PB3端口外部中断2中断标志位
 #define EX2IF2                         0x0004                                  // rw0- PB2端口外部中断2中断标志位
 #define EX2IF1                         0x0002                                  // rw0- PB1端口外部中断2中断标志位
 #define EX2IF0                         0x0001                                  // rw0- PB0端口外部中断2中断标志位

/******************************************************************************/
/*                                   Clock                                    */
/******************************************************************************/
/******************** Bits definition for CK_CR register *********************/
 #define TIM8CKEN                       0x80000                                 // rw-- TIM8模块时钟使能
 #define I2C2CKEN                       0x40000                                 // rw-- I2C2模块时钟使能
 #define SFCKEN                         0x20000                                 // rw-- SF模块时钟使能
 #define BISSCKEN                       0x10000                                 // rw-- BiSS模块时钟使能
 #define DRV2CKEN                       0x8000                                  // rw-- DRV2模块时钟使能
 #define DRVCKEN                        0x4000                                  // rw-- DRV模块时钟使能
 #define PFCCKEN                        0x2000                                  // rw-- PFC模块时钟使能
 #define UART2CKEN                      0x1000                                  // rw-- Uart2模块时钟使能
 #define UARTCKEN                       0x800                                   // rw-- Uart模块时钟使能
 #define LINCKEN                        0x400                                   // rw-- LIN模块时钟使能
 #define SPI2CKEN                       0x200                                   // rw-- SPI2模块时钟使能
 #define SPICKEN                        0x100                                   // rw-- SPI模块时钟使能
 #define I2CCKEN                        0x80                                    // rw-- I2C模块时钟使能
 #define CANCKEN                        0x40                                    // rw-- CAN模块时钟使能
 #define T7CKEN                         0x20                                    // rw-- Timer7模块时钟使能
 #define T6CKEN                         0x10                                    // rw-- Timer6模块时钟使能
 #define T5CKEN                         0x08                                    // rw-- Timer5模块时钟使能
 #define T4CKEN                         0x04                                    // rw-- Timer4模块时钟使能
 #define T3CKEN                         0x02                                    // rw-- Timer3模块时钟使能
 #define T2CKEN                         0x01                                    // rw-- Timer2模块时钟使能


/******************************************************************************/


/******************************************************************************/
/*                                   Special                                  */
/******************************************************************************/
/******************** Bits definition for RST_SR register *********************/
 #define RSTPOW                         0x80                                    // r--- 上电复位标志
 #define RSTEXT                         0x40                                    // r--- 外部复位标志
 #define RSTLVD                         0x20                                    // r--- 低压复位标志
 #define RSTEOS                         0x10                                    // r--- 电应力过度复位标志  /* factory */
 #define RSTWDT                         0x08                                    // r--- 看门狗复位标志
 #define RSTFED                         0x04                                    // r--- 代码保护复位
 #define RSTDBG                         0x02                                    // r--- 调试接口复位
 #define SOFTRST                        0x01                                    // r--- 软件复位标志
/******************** Bits definition for RST_CR register *********************/
 #define WKRE                           0x20                                    // rw-- MON唤醒使能
 #define WKPOLAR                        0x10                                    // rw-- MON输入（PA9）唤醒电平
 #define SFRST                          0x02                                    // w1-- 软件复位
 #define RSTCLR                         0x01                                    // w1-- 复位标志清零
/********************** Bits definition for PCON register *********************/
 #define LDOM                           0x04                                    // rw--
 #define STOP                           0x02                                    // rw-- MCU睡眠使能
 #define IDEL                           0x01                                    // rw-- MCU待机使能
/******************* Bits definition for FLA_KEY register **********************/
 #define FLAKSTA1                       0x02                                    // r--- Flash解锁状态位1
 #define FLAKSTA0                       0x01                                    // r--- Flash解锁状态位0
/******************** Bits definition for FLA_CR register *********************/
 #define FLAERR                         0x8000                                  // r--- Flash 操作错误标志位
 #define FLABT2CRCERR                   0x4000                                  // r--- Flash Boot第二份校验错误标志位 /* factory */
 #define FLABT1CRCERR                   0x2000                                  // r--- Flash Boot第一份校验错误标志位 /* factory */
 #define FLAM0ERR                       0x1000                                  // r--- Flash Margin0错误标志位
 #define FLAMARGIN1                     0x0100                                  // rw-- Flash Margin1测试模式使能
 #define FLAECCMANUAL                   0x0080                                  // rw-- Flash ECC手动填写ECC字节使能 /* factory */
 #define FLAECC                         0x0040                                  // rw-- Flash ECC字节编程使能
 #define FLASIZE                        0x0020                                  // rw-- Flash编程长度配置
 #define FLACHIP                        0x0010                                  // rw-- Flash全片操作使能
 #define FLAPAGE                        0x0008                                  // rw-- Flash页操作使能
 #define FLAPRE                         0x0004                                  // rw-- Flash预编程使能
 #define FLAERS                         0x0002                                  // rw-- Flash清除使能
 #define FLAEN                          0x0001                                  // rw-- Flash编程使能

/******************************************************************************/
/*                                    ECC                                     */
/******************************************************************************/
/******************** Bits definition for FLA_ECC_CR register *********************/
 #define ECC_ARR_MASK                   0xf8000000                              // rw-- 多次ECC错误中断触发阈值掩码
 #define ECC_LMERR_CEN                  0x00000100                              // rw-- 取数据发生多位ECC错误计数使能
 #define ECC_LERR_CEN                   0x00000080                              // rw-- 取数据发生一位ECC错误计数使能
 #define ECC_MERR_IE                    0x00000040                              // rw-- 多次ECC错误中断使能
 #define ECC_CMERR_IE                   0x00000008                              // rw-- 取指令发生多位ECC错误中断使能
 #define ECC_CERR_IE                    0x00000004                              // rw-- 取指令发生一位ECC错误中断使能
 #define ECC_LMERR_IE                   0x00000002                              // rw-- 取数据发生多位ECC错误中断使能
 #define ECC_LERR_IE                    0x00000001                              // rw-- 取数据发生一位ECC错误中断使能

/******************** Bits definition for FLA_ECC_SR register *********************/
 #define ECC_CNTR_MASK                  0xf8000000                              // r--- ECC错误累计次数掩码
 #define ECC_MERR_IF                    0x00000040                              // rw0- 多次ECC错误中断标志
 #define ECC_BMERR_IF                   0x00000020                              // rw0- Boot过程中发生多位ECC错误 /* factory */
 #define ECC_BERR_IF                    0x00000010                              // rw0- Boot过程中发生一位ECC错误 /* factory */
 #define ECC_CMERR_IF                   0x00000008                              // rw0- 取指令发生多位ECC错误中断标志
 #define ECC_CERR_IF                    0x00000004                              // rw0- 取指令发生一位ECC错误中断标志
 #define ECC_LMERR_IF                   0x00000002                              // rw0- 取数据发生多位ECC错误中断标志
 #define ECC_LERR_IF                    0x00000001                              // rw0- 取数据发生一位ECC错误中断标志

/******************************************************************************/
/*                                     CMP                                    */
/******************************************************************************/
/******************** Bits definition for CMP_CR0 register ********************/
 #define CMP5IM1                        0x800                                   // rw-- CMP5中断模式配置1
 #define CMP5IM0                        0x400                                   // rw-- CMP5中断模式配置0
 #define CMP4IM1                        0x200                                   // rw-- CMP4中断模式配置1
 #define CMP4IM0                        0x100                                   // rw-- CMP4中断模式配置0
 #define CMP3IM1                        0x80                                    // rw-- CMP3中断模式配置1
 #define CMP3IM0                        0x40                                    // rw-- CMP3中断模式配置0
 #define CMP2IM1                        0x20                                    // rw-- CMP2中断模式配置1
 #define CMP2IM0                        0x10                                    // rw-- CMP2中断模式配置0
 #define CMP1IM1                        0x08                                    // rw-- CMP1中断模式配置1
 #define CMP1IM0                        0x04                                    // rw-- CMP1中断模式配置0
 #define CMP0IM1                        0x02                                    // rw-- CMP0中断模式配置1
 #define CMP0IM0                        0x01                                    // rw-- CMP0中断模式配置0
/******************** Bits definition for CMP_CR1 register ********************/
 #define CMP3P4MFS                      0x1000                                  // rw-- CMP3P/CMP4M功能转移使能
 #define CMP11HYS                       0x800                                   // rw-- CMP11迟滞使能
 #define CMP5HYS                        0x400                                   // rw-- CMP5迟滞使能
 #define CMP11EN                        0x200                                   // rw-- CMP11使能位
 #define CMP5EN                         0x100                                   // rw-- CMP5使能位
 #define CMP4EN                         0x80                                    // rw-- CMP4使能位
 #define CMP3MOD1                       0x40                                    // rw-- CMP3正输入端选择配置1
 #define CMP3MOD0                       0x20                                    // rw-- CMP3正输入端选择配置0
 #define CMP3EN                         0x10                                    // rw-- CMP3使能位
 #define CMP3HYS                        0x08                                    // rw-- CMP3迟滞使能
 #define CMP0HYS1                       0x02                                    // rw-- CMP1迟滞配置1
 #define CMP0HYS0                       0x01                                    // rw-- CMP1迟滞配置0
/******************** Bits definition for CMP_CR2 register ********************/
 #define CMPSAMSEL1                     0x800                                   // rw-- CMP0、CMP1、CMP2和ADC采样延迟配置位1
 #define CMPSAMSEL0                     0x400                                   // rw-- CMP0、CMP1、CMP2和ADC采样延迟配置位0
 #define HALL0EN                        0x100                                   // rw-- HALL0使能位
 #define CMP0FS                         0x80                                    // rw-- 比较器0滤波系数配置
 #define CMP0MOD1                       0x40                                    // rw-- CMP0正输入端选择配置1
 #define CMP0MOD0                       0x20                                    // rw-- CMP0正输入端选择配置0
 #define CMP0SEL1                       0x10                                    // rw-- 比较器0输出选择配置1
 #define CMP0SEL0                       0x08                                    // rw-- 比较器0输出选择配置0
 #define CMP0CKSEL1                     0x04                                    // rw-- CMP0的轮询时间设置1 /* factory */
 #define CMP0CKSEL0                     0x02                                    // rw-- CMP0的轮询时间设置0 /* factory */
 #define CMP0EN                         0x01                                    // rw-- CMP0使能位
/******************** Bits definition for CMP_CR3 register ********************/
 #define CMP5FSEL1                      0x800                                   // rw-- CMP5滤波系数配置1
 #define CMP5FSEL0                      0x400                                   // rw-- CMP5滤波系数配置0
 #define CMP9FSEL1                      0x200                                   // rw-- CMP9滤波系数配置1 
 #define CMP9FSEL0                      0x100                                   // rw-- CMP9滤波系数配置0
 #define CMP3FSEL1                      0x80                                    // rw-- CMP3滤波系数配置1
 #define CMP3FSEL0                      0x40                                    // rw-- CMP3滤波系数配置0
 #define CMP6FSEL2                      0x20                                    // rw-- CMP6滤波系数配置2
 #define CMP6FSEL1                      0x10                                    // rw-- CMP6滤波系数配置1
 #define CMP6FSEL0                      0x08                                    // rw-- CMP6滤波系数配置0
 #define CMP0FSEL2                      0x04                                    // rw-- CMP0滤波系数配置2
 #define CMP0FSEL1                      0x02                                    // rw-- CMP0滤波系数配置1
 #define CMP0FSEL0                      0x01                                    // rw-- CMP0滤波系数配置0
/********************* Bits definition for CMP_SR register ********************/
 #define CMP11OUT                       0x800                                   // r--- CMP11比较结果 
 #define CMP10OUT                       0x400                                   // r--- CMP10比较结果
 #define CMP9OUT                        0x200                                   // r--- CMP9比较结果
 #define CMP8OUT                        0x100                                   // r--- CMP8比较结果
 #define CMP7OUT                        0x80                                    // r--- CMP7比较结果
 #define CMP6OUT                        0x40                                    // r--- CMP6比较结果
 #define CMP5OUT                        0x20                                    // r--- CMP5比较结果
 #define CMP4OUT                        0x10                                    // r--- CMP4比较结果
 #define CMP3OUT                        0x08                                    // r--- CMP3比较结果
 #define CMP2OUT                        0x04                                    // r--- CMP2比较结果
 #define CMP1OUT                        0x02                                    // r--- CMP1比较结果
 #define CMP0OUT                        0x01                                    // r--- CMP0比较结果
/********************* Bits definition for CMP_IFR register ********************/
 #define CMP11IF                        0x800                                   // rw0- CMP11中断标志
 #define CMP10IF                        0x400                                   // rw0- CMP10中断标志
 #define CMP9IF                         0x200                                   // rw0- CMP9中断标志
 #define CMP8IF                         0x100                                   // rw0- CMP8中断标志
 #define CMP7IF                         0x80                                    // rw0- CMP7中断标志
 #define CMP6IF                         0x40                                    // rw0- CMP6中断标志
 #define CMP5IF                         0x20                                    // rw0- CMP5中断标志
 #define CMP4IF                         0x10                                    // rw0- CMP4中断标志
 #define CMP3IF                         0x08                                    // rw0- CMP3中断标志
 #define CMP2IF                         0x04                                    // rw0- CMP2中断标志
 #define CMP1IF                         0x02                                    // rw0- CMP1中断标志
 #define CMP0IF                         0x01                                    // rw0- CMP0中断标志
/********************* Bits definition for CMP_DBR register ********************/
#define DBG2SEL4                       0x4000                                  // rw-- DBG2信号源选择位4
#define DBG2SEL3                       0x2000                                  // rw-- DBG2信号源选择位3
#define DBG2SEL2                       0x1000                                  // rw-- DBG2信号源选择位2
#define DBG2SEL1                       0x800                                   // rw-- DBG2信号源选择位1
#define DBG2SEL0                       0x400                                   // rw-- DBG2信号源选择位0
#define DBG1SEL4                       0x200                                   // rw-- DBG1信号源选择位4
#define DBG1SEL3                       0x100                                   // rw-- DBG1信号源选择位3
#define DBG1SEL2                       0x80                                    // rw-- DBG1信号源选择位2
#define DBG1SEL1                       0x40                                    // rw-- DBG1信号源选择位1
#define DBG1SEL0                       0x20                                    // rw-- DBG1信号源选择位0
#define CMPSEL4                        0x10                                    // rw-- 比较器输出信号源选择位4
#define CMPSEL3                        0x08                                    // rw-- 比较器输出信号源选择位3
#define CMPSEL2                        0x04                                    // rw-- 比较器输出信号源选择位2
#define CMPSEL1                        0x02                                    // rw-- 比较器输出信号源选择位1
#define CMPSEL0                        0x01                                    // rw-- 比较器输出信号源选择位0
/******************** Bits definition for CMP_CR4 register ********************/
 #define CMP11IM1                       0x800                                   // rw-- CMP11中断模式配置1
 #define CMP11IM0                       0x400                                   // rw-- CMP11中断模式配置0
 #define CMP10IM1                       0x200                                   // rw-- CMP10中断模式配置1
 #define CMP10IM0                       0x100                                   // rw-- CMP10中断模式配置0
 #define CMP9IM1                        0x80                                    // rw-- CMP9中断模式配置1
 #define CMP9IM0                        0x40                                    // rw-- CMP9中断模式配置0
 #define CMP8IM1                        0x20                                    // rw-- CMP8中断模式配置1
 #define CMP8IM0                        0x10                                    // rw-- CMP8中断模式配置0
 #define CMP7IM1                        0x08                                    // rw-- CMP7中断模式配置1
 #define CMP7IM0                        0x04                                    // rw-- CMP7中断模式配置0
 #define CMP6IM1                        0x02                                    // rw-- CMP6中断模式配置1
 #define CMP6IM0                        0x01                                    // rw-- CMP6中断模式配置0
/******************** Bits definition for CMP_CR5 register ********************/
 #define CMP9P10MFS                     0x100                                   // rw-- CMP9P/CMP10M功能转移使能
 #define CMP10EN                        0x80                                    // rw-- CMP10使能位
 #define CMP9MOD1                       0x40                                    // rw-- CMP9正输入端选择配置1
 #define CMP9MOD0                       0x20                                    // rw-- CMP9正输入端选择配置0
 #define CMP9EN                         0x10                                    // rw-- CMP9使能位
 #define CMP9HYS                        0x08                                    // rw-- CMP9迟滞使能
 #define STRCT							0x04                                    // rw-- 探针功能转移位: 0-PA14、PA15; 1-PC6、PC7
 #define CMP6HYS1                       0x02                                    // rw-- CMP6迟滞使能1
 #define CMP6HYS0                       0x01                                    // rw-- CMP6迟滞使能0
/******************** Bits definition for CMP_CR6 register *******************/
 #define CMPSAM1EN                      0x800                                   // rw-- CMP6、CMP7和CMP8采样延迟配置位1
 #define CMPSAMN1EN                     0x400                                   // rw-- CMP6、CMP7和CMP8采样延迟配置位0
 #define SFRCT2							0x200                                   // rw-- 多摩川RE功能转移位2
 #define HALL1EN                        0x100                                   // rw-- HALL1使能位
 #define CMP6FS                         0x80                                    // rw-- CMP6滤波系数配置位
 #define CMP6MOD1                       0x40                                    // rw-- CMP6正输入端选择配置1
 #define CMP6MOD0                       0x20                                    // rw-- CMP6正输入端选择配置0
 #define CMP6SEL1                       0x10                                    // rw-- 比较器6输出选择配置1
 #define CMP6SEL0                       0x08                                    // rw-- 比较器6输出选择配置0
 #define CMP6CKSEL1                     0x04                                    // rw-- CMP6轮询时间设置1 /* factory */
 #define CMP6CKSEL0                     0x02                                    // rw-- CMP6轮询时间设置0 /* factory */
 #define CMP6EN                         0x01                                    // rw-- CMP6使能位

/******************************************************************************/
/*                                     AMP                                    */
/******************************************************************************/
/***************** Bits definition for VREF_VHALF_CR register *****************/
 #define VHAFSEL1                       0x200                                   // rw-- VHALF电压选择VREF系数配置1
 #define VHAFSEL0                       0x100                                   // rw-- VHALF电压选择VREF系数配置0
 #define VREFSEL1                       0x80                                    // rw-- VREF电压配置1
 #define VREFSEL0                       0x40                                    // rw-- VREF电压配置0
 #define VREFEN                         0x10                                    // rw-- VREF使能位
 #define VHALFEN                        0x01                                    // rw-- VHALF使能位
/******************** Bits definition for AMP_CR0 register ********************/
 #define AMP56MGND                      0x400                                   // rw-- 运放56负输入端接GND
 #define AMP4MGND                       0x200                                   // rw-- 运放4负输入端接GND
 #define AMP12MGND                      0x100                                   // rw-- 运放12负输入端接GND
 #define AMP0MGND                       0x80                                    // rw-- 运放0负输入端接GND
 #define AMP6EN                         0x40                                    // rw-- AMP6使能位
 #define AMP5EN                         0x20                                    // rw-- AMP5使能位
 #define AMP4EN                         0x10                                    // rw-- AMP4使能位
 #define AMP3EN                         0x08                                    // rw-- AMP3使能位
 #define AMP2EN                         0x04                                    // rw-- AMP2使能位
 #define AMP1EN                         0x02                                    // rw-- AMP1使能位
 #define AMP0EN                         0x01                                    // rw-- AMP0使能位
/******************** Bits definition for AMP_CR1 register ********************/
 #define AMPPH56GAIN2                   0x4000                                  // rw-- 运放56放大倍数配置2
 #define AMPPH56GAIN1                   0x2000                                  // rw-- 运放56放大倍数配置1
 #define AMPPH56GAIN0                   0x1000                                  // rw-- 运放56放大倍数配置0
 #define AMPPH12GAIN2                   0x800                                   // rw-- 运放12放大倍数配置2
 #define AMPPH12GAIN1                   0x400                                   // rw-- 运放12放大倍数配置1
 #define AMPPH12GAIN0                   0x200                                   // rw-- 运放12放大倍数配置0
 #define AMP4GAIN2                      0x100                                   // rw-- 运放4放大倍数配置2
 #define AMP4GAIN1                      0x80                                    // rw-- 运放4放大倍数配置1
 #define AMP4GAIN0                      0x40                                    // rw-- 运放4放大倍数配置0
 #define AMP3GAIN2                      0x20                                    // rw-- 运放3放大倍数配置2
 #define AMP3GAIN1                      0x10                                    // rw-- 运放3放大倍数配置1
 #define AMP3GAIN0                      0x08                                    // rw-- 运放3放大倍数配置0
 #define AMP0GAIN2                      0x04                                    // rw-- 运放0放大倍数配置2
 #define AMP0GAIN1                      0x02                                    // rw-- 运放0放大倍数配置1
 #define AMP0GAIN0                      0x01                                    // rw-- 运放0放大倍数配置0

/******************************************************************************/
/*                                    TEMP                                    */
/******************************************************************************/
/********************* Bits definition for TSD_CR register ********************/
 #define TSD_EN                         0x80                                    // rw-- TSD使能位
 #define TSEN_EN                        0x40                                    // rw-- 温度传感器使能位
 #define TSEN_HYS                       0x20                                    // rw-- 温度传感器输出结果滤波，0-->1个码值，1-->2个码值
 #define TSD_ADJ3					    0x08                                    // rw-- 过温保护温度选择
 #define TSD_ADJ2 					    0x04                                    // rw-- 过温保护温度选择
 #define TSD_ADJ1					    0x02                                    // rw-- 过温保护温度选择
 #define TSD_ADJ0					    0x01                                    // rw-- 过温保护温度选择
 
/******************************************************************************/
/*                                     DAC                                    */
/******************************************************************************/
/********************* Bits definition for DAC_CR register ********************/
#define DAC34MOD                        0x20                                    // rw-- DAC3/DAC4模式配置
#define DACMOD                          0x10                                    // rw-- DAC0/DAC1模式配置
#define DAC34EN                         0x04                                    // rw-- DAC3/DAC4使能位
#define DAC2EN                          0x02                                    // rw-- DAC2使能位
#define DACEN                           0x01                                    // rw-- DAC0/DAC1使能位
/******************************************************************************/
/*                                     ADC                                    */
/******************************************************************************/
/********************* Bits definition for ADCx_CR register *******************/
 #define ADCEN                          0x80                                    // rw-- ADC使能位
 #define ADCBSY                         0x40                                    // rw1- ADC busy标志位
 #define ADCALI                         0x04                                    // rw-- ADC 数据格式选择
 #define ADCIE                          0x02                                    // rw-- ADC 中断使能位
 #define ADCIF                          0x01                                    // rw0- ADC 中断标志位
 /******************** Bits definition for ADC1_SCYC register *******************/
 #define ADC1_SCYC15                    0x8000                                  // rw-- ADC1 CH3/8/9/10/12采样时间配置
 #define ADC1_SCYC14                    0x4000                                  // rw-- ADC1 CH3/8/9/10/12采样时间配置
 #define ADC1_SCYC13                    0x2000                                  // rw-- ADC1 CH3/8/9/10/12采样时间配置
 #define ADC1_SCYC12                    0x1000                                  // rw-- ADC1 CH3/8/9/10/12采样时间配置
 #define ADC1_SCYC11                    0x0800                                  // rw-- ADC1 CH5/6/7采样时间配置3 
 #define ADC1_SCYC10                    0x0400                                  // rw-- ADC1 CH5/6/7采样时间配置2 
 #define ADC1_SCYC9                     0x0200                                  // rw-- ADC1 CH5/6/7采样时间配置1 
 #define ADC1_SCYC8                     0x0100                                  // rw-- ADC1 CH5/6/7采样时间配置0 
 #define ADC1_SCYC7                     0x0080                                  // rw-- ADC1 CH2采样时间配置3 
 #define ADC1_SCYC6                     0x0040                                  // rw-- ADC1 CH2采样时间配置2 
 #define ADC1_SCYC5                     0x0020                                  // rw-- ADC1 CH2采样时间配置1 
 #define ADC1_SCYC4                     0x0010                                  // rw-- ADC1 CH2采样时间配置0 
 #define ADC1_SCYC3                     0x0008                                  // rw-- ADC1 CH0/1/4/11采样时间配置3 
 #define ADC1_SCYC2                     0x0004                                  // rw-- ADC1 CH0/1/4/11采样时间配置2 
 #define ADC1_SCYC1                     0x0002                                  // rw-- ADC1 CH0/1/4/11采样时间配置1 
 #define ADC1_SCYC0                     0x0001                                  // rw-- ADC1 CH0/1/4/11采样时间配置0 
/******************** Bits definition for ADC2_SCYC register *******************/
 #define ADC2_SCYC15                    0x8000                                  // rw-- ADC2 CH3/8/9/10/12/14/15采样时
 #define ADC2_SCYC14                    0x4000                                  // rw-- ADC2 CH3/8/9/10/12/14/15采样时
 #define ADC2_SCYC13                    0x2000                                  // rw-- ADC2 CH3/8/9/10/12/14/15采样时
 #define ADC2_SCYC12                    0x1000                                  // rw-- ADC2 CH3/8/9/10/12/14/15采样时
 #define ADC2_SCYC11                    0x0800                                  // rw-- ADC2 CH5/6/7采样时间配置3 
 #define ADC2_SCYC10                    0x0400                                  // rw-- ADC2 CH5/6/7采样时间配置2 
 #define ADC2_SCYC9                     0x0200                                  // rw-- ADC2 CH5/6/7采样时间配置1 
 #define ADC2_SCYC8                     0x0100                                  // rw-- ADC2 CH5/6/7采样时间配置0 
 #define ADC2_SCYC7                     0x0080                                  // rw-- ADC2 CH2/11采样时间配置3 
 #define ADC2_SCYC6                     0x0040                                  // rw-- ADC2 CH2/11采样时间配置2 
 #define ADC2_SCYC5                     0x0020                                  // rw-- ADC2 CH2/11采样时间配置1 
 #define ADC2_SCYC4                     0x0010                                  // rw-- ADC2 CH2/11采样时间配置0 
 #define ADC2_SCYC3                     0x0008                                  // rw-- ADC2 CH0/1/4/13采样时间配置3 
 #define ADC2_SCYC2                     0x0004                                  // rw-- ADC2 CH0/1/4/13采样时间配置2 
 #define ADC2_SCYC1                     0x0002                                  // rw-- ADC2 CH0/1/4/13采样时间配置1 
 #define ADC2_SCYC0                     0x0001                                  // rw-- ADC2 CH0/1/4/13采样时间配置0 
/******************** Bits definition for ADC3_SCYC register *******************/
 #define ADC3_SCYC7                     0x0080                                  // rw-- ADC3 CH0/2采样时间配置3 
 #define ADC3_SCYC6                     0x0040                                  // rw-- ADC3 CH0/2采样时间配置2 
 #define ADC3_SCYC5                     0x0020                                  // rw-- ADC3 CH0/2采样时间配置1 
 #define ADC3_SCYC4                     0x0010                                  // rw-- ADC3 CH0/2采样时间配置0 
 #define ADC3_SCYC3                     0x0008                                  // rw-- ADC3 CH1采样时间配置3 
 #define ADC3_SCYC2                     0x0004                                  // rw-- ADC3 CH1采样时间配置2 
 #define ADC3_SCYC1                     0x0002                                  // rw-- ADC3 CH1采样时间配置1 
 #define ADC3_SCYC0                     0x0001                                  // rw-- ADC3 CH1采样时间配置0 
/******************** Bits definition for ADCx_MASK register ******************/
 #define CH15EN                         0x8000                                  // rw-- ADCx通道15使能位
 #define CH14EN                         0x4000                                  // rw-- ADCx通道14使能位
 #define CH13EN                         0x2000                                  // rw-- ADCx通道13使能位
 #define CH12EN                         0x1000                                  // rw-- ADCx通道12使能位
 #define CH11EN                         0x0800                                  // rw-- ADCx通道11使能位
 #define CH10EN                         0x0400                                  // rw-- ADCx通道10使能位
 #define CH9EN                          0x0200                                  // rw-- ADCx通道9使能位
 #define CH8EN                          0x0100                                  // rw-- ADCx通道8使能位
 #define CH7EN                          0x0080                                  // rw-- ADCx通道7使能位
 #define CH6EN                          0x0040                                  // rw-- ADCx通道6使能位
 #define CH5EN                          0x0020                                  // rw-- ADCx通道5使能位
 #define CH4EN                          0x0010                                  // rw-- ADCx通道4使能位
 #define CH3EN                          0x0008                                  // rw-- ADCx通道3使能位
 #define CH2EN                          0x0004                                  // rw-- ADCx通道2使能位
 #define CH1EN                          0x0002                                  // rw-- ADCx通道1使能位
 #define CH0EN                          0x0001                                  // rw-- ADCx通道0使能位

/******************************************************************************/
/*                                     DMA                                    */
/******************************************************************************/
/******************** Bits definition for DMAx_CR register ********************/
 #define DMAHIE                         0x1000                                  // rw-- DMA传输半完成中断使能
 #define DMAIE                          0x800                                   // rw-- DMA中断使能
 #define DMACONEN                       0x400                                   // rw-- DMA循环发送功能
 #define DMAEN                          0x200                                   // rw-- DMA模块使能
 #define DMABSY                         0x100                                   // rw1- DMA启动/DMA工作状态
 #define DMACFG4                        0x80                                    // rw-- DMA通道选择4
 #define DMACFG3                        0x40                                    // rw-- DMA通道选择3
 #define DMACFG2                        0x20                                    // rw-- DMA通道选择2
 #define DMACFG1                        0x10                                    // rw-- DMA通道选择1
 #define DMACFG0                        0x08                                    // rw-- DMA通道选择0
 #define ENDIAN                         0x04                                    // rw-- DMA数据大小端模式
 #define DMAHIF                         0x02                                    // rw-- DMA半完成中断标志志位
 #define DMAIF                          0x01                                    // rw-- DMA中断标志位
/******************************************************************************/
/*                                    UART                                    */
/******************************************************************************/
/********************* Bits definition for UTx_CR0 register *********************/
 #define RTO                            0x200                                   // rw0- 接收超时中断
 #define CHKERR                         0x100                                   // r--- 校验错误
 #define UTRB8                          0x80                                    // rw-- Uartx接收第九位
 #define UTMOD1                         0x40                                    // rw-- Uartx模式选择1
 #define UTMOD0                         0x20                                    // rw-- Uartx模式选择0
 #define UTSM2                          0x10                                    // rw-- Uartx多机通讯选择
 #define UTREN                          0x08                                    // rw-- Uartx接收使能
 #define UTEN                           0x04                                    // rw-- Uartx模块使能
 #define UTTI                           0x02                                    // rw-- Uartx发送中断标志位
 #define UTRI                           0x01                                    // rw-- Uartx接收中断标志位
/********************* Bits definition for UTx_CR1 register *********************/
 #define RTOIE                          0x400                                   // rw-- Uartx超时中断使能位
 #define UTIE                           0x200                                   // rw-- Uartx收发中断使能位
 #define BAUDSEL                        0x100                                   // rw-- Uartx波特率倍频
 #define RXINV                          0x80                                    // rw-- Uartx接收反向
 #define TXINV                          0x40                                    // rw-- Uartx发送反向
 #define RTOSEL1                        0x08                                    // rw-- 接收超时挡位选择1
 #define RTOSEL0                        0x04                                    // rw-- 接收超时挡位选择0
 #define CHKMOD1                        0x02                                    // rw-- 00：手动模式TB9=0  01：偶校验
 #define CHKMOD0                        0x01                                    // rw-- 10：奇检验         11：手动模式TB9=1
/******************************************************************************/
/*                                    SF                                      */
/******************************************************************************/
/********************* Bits definition for SF_CR register *********************/
#define SF_AUTO_EN                      0x04                                    // w1-- 串行编码器自动触发使能
#define SEND_REQ                        0x02                                    // w1-- 串行编码器解码发送请求
#define SF_EN                           0x01                                    // rw-- 串行编码器解码使能

/********************* Bits definition for SF_SR register *********************/
#define SF_SUC                          0x20                                    // rw0- 数据接收成功标志，数据接收完且CRCCRC正确
#define SF_DONE                         0x10                                    // rw0- 数据接收完成标志，仅数据接收完成但不知是否有错(如CRC出错也会显示DONE)
#define REQ_OUT                         0x08                                    // rw0- 请求超时错误，发送请求指令后无法回法回
#define REQ_ERR                         0x04                                    // rw0- 请求命令错误，发送和返回的ID不一一样
#define SYN_ERR                         0x02                                    // rw0- 帧同步错误，如未检查到控制字(CF)F)的(Sink Code)
#define CRC_ERR                         0x01                                    // rw0- CRC校验错误

/******************************************************************************/
/*                                   LIN                                      */
/******************************************************************************/
/********************* Bits definition for LIN_CR register *********************/
 #define ManualBaud                     0x80                                    // rw-- LIN手动波特率使能
 #define LINIE                          0x08                                    // rw-- LIN中断使能
 #define CHKMOD                         0x04                                    // rw-- 校验模式选择
 #define LINRW                          0x02                                    // rw-- LIN读写控制
 #define AUTOSIZE                       0x01                                    // rw-- 识别LINID[5:4]自动决定读写长度

/********************* Bits definition for LIN_SR register *********************/   
 #define ERRFRAME                       0x800                                   // r--- LIN形式错误
 #define ERRBIT                         0x400                                   // r--- LIN回读错误
 #define ERRSYNC                        0x200                                   // r--- LIN同步错误
 #define ERRCHK                         0x100                                   // r--- LIN校验错误
 #define ERRPRTY                        0x80                                    // r--- ID错误
 #define ABORT                          0x40                                    // r--- 总线异常
 #define LINACT                         0x20                                    // r--- LIN响应
 #define LINERR                         0x10                                    // rw0- 错误中断标志位
 #define LINWAKEUP                      0x08                                    // rw0- 唤醒中断标志位
 #define LINIDLE                        0x04                                    // rw0- LIN4s总线无报文活动，空闲中断
 #define LINDONE                        0x02                                    // rw0- LIN报文接收发送送完成
 #define LINREQ                         0x01                                    // rw0- LIN收到帧头

/********************* Bits definition for LIN_CSR register *********************/    
 #define LINRDBAKDIS                    0x40                                    // rw-- LIN回读使能禁止
 #define LINSLP                         0x20                                    // rw-- LIN睡眠标志位
 #define TXWAKEUP                       0x08                                    // w1-- LIN唤醒信号发送
 #define LINACK                         0x04                                    // w1-- LIN报文回应
 #define LINSTOP                        0x02                                    // w1-- LIN传输停止
 #define LINEN                          0x01                                    // rw-- LIN模块使能


 /******************************************************************************/
/*                                   CAN                                      */
/******************************************************************************/
/********************* Bits definition for CAN_CR0 register *********************/    
 #define TDCSEL                         0x1000                                  // rw-- 手动/自动延迟补偿选择
 #define TDCEN                          0x800                                   // rw-- 延迟补偿使能
 #define PEX                            0x400                                   // rw-- 协议异常容忍
 #define NISO                           0x200                                   // rw-- CANFD非ISO使能
 #define CFDEN                          0x100                                   // rw-- CANFD使能
 #define CANEN                          0x80                                    // rw-- CAN模块使能
 #define AWU                            0x10                                    // rw-- 自动唤醒模式使能
 #define FILMOD                         0x08                                    // rw-- 过滤模式
 #define SELFTST                        0x04                                    // rw-- 自测模式使能
 #define LISTEN                         0x02                                    // rw-- 监听模式
 #define RSTMOD                         0x01                                    // rw-- 复位模式

/********************* Bits definition for CAN_CR1 register *********************/  
 #define TTCM                           0x4000                                  // rw-- 三选二采样使能 
 #define TSPSC3                         0x2000                                  // rw-- 时间戳时钟分频3 /* factory */ 
 #define TSPSC2                         0x1000                                  // rw-- 时间戳时钟分频2 /* factory */ 
 #define TSPSC1                         0x800                                   // rw-- 时间戳时钟分频1 /* factory */ 
 #define TSPSC0                         0x400                                   // rw-- 时间戳时钟分频0 /* factory */
 #define TSS                            0x200                                   // rw-- 时间戳时钟源 /* factory */
 #define CTTC                           0x100                                   // rw-- 时间触发通信 /* factory */
 #define TMOD                           0x80                                    // rw-- 邮箱发送模式选择
 #define OLREQ                          0x40                                    // rw-- 过载帧发送请求
 #define SLPREQ                         0x20                                    // rw-- 睡眠请求
 #define RSELF                          0x10                                    // rw-- 发送自收使能
 #define RFD                            0x04                                    // w1-- 释放接收缓冲区
 #define NOART                          0x02                                    // rw-- 禁止自动重传使能
 
/********************* Bits definition for CAN_STS register *********************/  
 #define SLPACK                         0x40                                    // r--- 睡眠模式确认
 #define TXING                          0x20                                    // r--- 发送中标志
 #define RXING                          0x10                                    // r--- 接收中标志
 #define FOV                            0x02                                    // r--- FIFO溢出标志
 #define FEMP                           0x01                                    // r--- FIFO空标志

/********************* Bits definition for CAN_IER register *********************/  
 #define TSIE                           0x1000                                  // rw-- 时间戳溢出中断使能 /* factory */
 #define WKUIE                          0x800                                   // rw-- 唤醒中断使能
 #define SLPIE                          0x400                                   // rw-- 睡眠中断使能
 #define OVLIE                          0x200                                   // rw-- 过载中断使能
 #define ERRIE                          0x100                                   // rw-- 错误中断总使能
 #define ETYIE                          0x80                                    // rw-- 错误类型中断使能
 #define BOFIE                          0x40                                    // rw-- 总线关闭中断使能
 #define PERIE                          0x20                                    // rw-- 被动错误中断请求
 #define ERWIE                          0x10                                    // rw-- 错误预警中断使能
 #define OVIE                           0x08                                    // rw-- 溢出中断使能
 #define ABLIE                          0x04                                    // rw-- 仲裁中断使能
 #define TXIE                           0x02                                    // rw-- 发送结束中断使能
 #define RXIE                           0x01                                    // rw-- 接收中断使能

/********************* Bits definition for CAN_IFR register *********************/  
 #define TSIF                           0x100                                   // rw0- 时间戳溢出事件标志位 /* factory */
 #define WKUIF                          0x80                                    // rw0- 唤醒中断事件标志位
 #define SLPIF                          0x40                                    // rw0- 睡眠中断事件标志位
 #define OVLIF                          0x20                                    // rw0- 过载中断事件标志位
 #define ERRIF                          0x10                                    // rw0- 错误中断事件标志位
 #define OVIF                           0x08                                    // rw0- 溢出中断事件标志位
 #define ABLIF                          0x04                                    // rw0- 仲裁丢失中断事件标志位
 #define TXIF                           0x02                                    // rw0- 发送结束中断事件标志位
 #define RXIF                           0x01                                    // r--- 接收中断事件标志位

/********************* Bits definition for CAN_TSPT register *********************/  
 #define RDPTR1                         0x08                                    // r--- 接收报文指针1
 #define RDPTR0                         0x04                                    // r--- 接收报文指针0
 #define MESCNT1                        0x02                                    // r--- 有效报文数1
 #define MESCNT0                        0x01                                    // r--- 有效报文数0

/********************* Bits definition for CAN_ERR register *********************/  
 #define BOFF                           0x04                                    // rw-- 节点总线关闭
 #define PER                            0x02                                    // rw-- 被动错误状态
 #define WER                            0x01                                    // rw-- 错误状态

 /********************* Bits definition for CAN_TMSTA register *********************/  
 #define MSL2                           0x80000000                              // r--- 邮箱2最后发送
 #define MSL1                           0x40000000                              // r--- 邮箱1最后发送
 #define MSL0                           0x20000000                              // r--- 邮箱0最后发送
 #define MNUM1                          0x10000000                              // r--- 下次发送的邮箱号
 #define MNUM0                          0x8000000                               // r--- 下次发送的邮箱号
 #define ME2                            0x4000000                               // r--- 发送邮箱2空
 #define ME1                            0x2000000                               // r--- 发送邮箱1空
 #define ME0                            0x1000000                               // r--- 发送邮箱0空
 #define MSTP2                          0x800000                                // rw-- 邮箱2停止发送
 #define MERR2                          0x80000                                 // rw1- 邮箱2发送错误,写1清0
 #define MAL2                           0x40000                                 // rw1- 邮箱2发送仲裁,写1清0
 #define MOK2                           0x20000                                 // rw1- 邮箱2发送成功,写1清0
 #define MDONE2                         0x10000                                 // rw1- 邮箱2发送完成,写1清0
 #define MSTP1                          0x8000                                  // rw-- 邮箱1停止发送
 #define MERR1                          0x800                                   // rw1- 邮箱1发送错误,写1清0
 #define MAL1                           0x400                                   // rw1- 邮箱1发送仲裁,写1清0
 #define MOK1                           0x200                                   // rw1- 邮箱1发送成功,写1清0
 #define MDONE1                         0x100                                   // rw1- 邮箱1发送完成,写1清0
 #define MSTP0                          0x80                                    // rw-- 邮箱0停止发送
 #define MERR0                          0x08                                    // rw1- 邮箱0发送错误,写1清0
 #define MAL0                           0x04                                    // rw1- 邮箱0发送仲裁,写1清0
 #define MOK0                           0x02                                    // rw1- 邮箱0发送成功,写1清0
 #define MDONE0                         0x01                                    // rw1- 邮箱0发送完成,写1清0

 /********************* Bits definition for CAN_TMIDx register *********************/  
 #define TREQ                           0x01                                    // w1-- 邮箱x发送请求

 /********************* Bits definition for CAN_TMDATx register *********************/  
 #define IDE                            0x100                                   // rw-- 标准帧/扩展帧
 #define RTR                            0x80                                    // rw-- 数据帧/远程帧
 #define FDF                            0x40                                    // rw-- CANFD帧报文
 #define BRS                            0x20                                    // rw-- 变速帧选择
 #define ESI                            0x10                                    // rw-- 错误状态标志
 #define DLC3                           0x08                                    // rw-- DLC3
 #define DLC2                           0x04                                    // rw-- DLC2
 #define DLC1                           0x02                                    // rw-- DLC1
 #define DLC0                           0x01                                    // rw-- DLC0






/******************************************************************************/
/*                                     I2C                                    */
/******************************************************************************/
/******************** Bits definition for I2C_CR register *********************/
 #define I2CEN                          0x80                                    // rw-- I2C模块使能
 #define I2CMS                          0x40                                    // rw-- I2C主机模式选择
 #define E2PRMVDDPD                     0x20                                    // rw-- E2PRMVDD5电源掉电使能,只有I2C1有效
 #define I2CDMANAKIG                    0x10                                    // rw-- DMA无视NACK继续发送
 #define I2CDMASENDAUTO                 0x08                                    // rw-- DMA自动发送第一帧数据
 #define I2CFSEL                        0x02                                    // rw-- I2C滤波选择
 #define I2CIE                          0x01                                    // rw-- I2C中断使能位
/******************** Bits definition for I2C_SR register *********************/
 #define I2CBSY                         0x80                                    // r--- I2C忙状态
 #define DMOD                           0x40                                    // rw-- I2C读写状态
 #define I2CSTA                         0x10                                    // rw-- I2C帧头标志位
 #define I2CSTP                         0x08                                    // rw-- I2C停止标志位
 #define STR                            0x04                                    // rw0- I2C总线挂起标志位
 #define NACK                           0x02                                    // rw-- 接收方向发送反馈
 #define I2CIF                          0x01                                    // r--- I2C中断标志位
/******************** Bits definition for I2C_ID register *********************/
 #define GC                             0x01                                    // rw-- I2CID广播模式

/******************************************************************************/
/*                                     SPIx                                    */
/******************************************************************************/
/******************** Bits definition for SPIx_CR  register *******************/
 #define SAMSEL                         0x200                                   // rw-- SPI沿边采样选择
 #define SCKRQ                          0x100                                   // r0w1 单线主机请求从机数据
 #define CPHA                           0x80                                    // rw-- SPI时钟相位
 #define CPOL                           0x40                                    // rw-- SPI时钟空闲电平
 #define NSSMOD1                        0x20                                    // rw-- SPI模式配置1
 #define NSSMOD0                        0x10                                    // rw-- SPI模式配置0
 #define SLINE                          0x08                                    // rw-- 单双工使能位
 #define SPIIE                          0x04                                    // rw-- SPI中断使能位
 #define SPIMS                          0x02                                    // rw-- SPI主机模式选择 
 #define SPIEN                          0x01                                    // rw-- SPI模块使能位
/******************** Bits definition for SPIx_SR  register ********************/
 #define SLVSEL                         0x200                                   // r--- NSS片选标志位
 #define NSSIN                          0x100                                   // r--- NSS实时信号
 #define SRMT                           0x80                                    // r--- 移位寄存器空标志位
 #define RXBMT                          0x40                                    // r--- 接收缓冲器空标志位
 #define TXBMT                          0x20                                    // r--- 发送缓冲器空标志位
 #define SPIBSY                         0x10                                    // r--- SPI忙状态
 #define SPIIF                          0x08                                    // rw0- SPI中断标志位
 #define WCOL                           0x04                                    // rw0- 写冲突中断事件标志位
 #define MODF                           0x02                                    // rw0- 主机模式错误中断事件标志位
 #define RXOVR                          0x01                                    // rw0- 接收溢出中断事件标志位

/******************************************************************************/
/*                                    BISS                                    */
/******************************************************************************/
/******************* Bits definition for BISS_STATE register *****************/
 #define BISS_AUTO_EN					0x0100                                  // r--- BiSS自动触发使能
 #define BISSEN                         0x0080
 #define BISSWRNERR                     0x0040                                  // r--- BiSS WARN bit
 #define BISSALMERR                     0x0020                                  // r--- BiSS ERR bit
 #define BISSCRCERR                     0x0010                                  // r--- CRC ERROR
 #define BISSOTIF                       0x0008                                  // rw0- Overtime error
 #define BISSENDIF                      0x0004                                  // rw0- Data transfer complete
 #define BISSENDEN                      0x0002                                  // rw-- Interrupt enable
 #define BISSBUSY                       0x0001                                  // rw1- 1 = start biss communication


/******************************************************************************/
/*                                   TIMER2                                   */
/******************************************************************************/
/******************* Bits definition for TIM2_CR0 register ********************/
 #define T2INM2                         0x400                                   // rw-- Timer2滤波系数2
 #define T2INM1                         0x200                                   // rw-- Timer2滤波系数1
 #define T2INM0                         0x100                                   // rw-- Timer2滤波系数0
 #define T2PSC2                         0x80                                    // rw-- Timer2分频系数2
 #define T2PSC1                         0x40                                    // rw-- Timer2分频系数1
 #define T2PSC0                         0x20                                    // rw-- Timer2分频系数0
 #define T2CES                          0x10                                    // rw-- Timer2沿边选择
 #define T2DIRIN                        0x08                                    // rw-- 方向输入极性选择
 #define T2MOD2                         0x04                                    // rw-- Timer2模式选择2
 #define T2MOD1                         0x02                                    // rw-- Timer2模式选择1
 #define T2MOD0                         0x01                                    // rw-- Timer2模式选择0
/******************* Bits definition for TIM2_CR1 register ********************/
 #define T2_CNTR_CLR_EN                 0x100                                   // rw-- QEP加载dr配置
 #define T2OPM                          0x80                                    // rw-- Timer2单次模式使能
 #define T2QEP_IN_CNTR_CLR              0x40                                    // rw-- QEP Z输入清CNTR使能
 #define T2Z_EDGE_SEL                   0x20                                    // rw-- QEP模式沿边选择
 #define T2SS                           0x10                                    // rw-- 步进模式
 #define T2OCM                          0x04                                    // rw-- 输出模式选择
 #define T2_DIR_R                       0x02                                    // r--- QEP&步进电机旋转方向
 #define T2EN                           0x01                                    // rw-- Timer2使能
/******************* Bits definition for TIM2_IER register ********************/
 #define T2IRE                          0x04                                    // rw-- IR中断使能位
 #define T2IPE                          0x02                                    // rw-- IP中断使能位
 #define T2IFE                          0x01                                    // rw-- IF中断使能位
/******************* Bits definition for TIM2_SR register ********************/
 #define T2IR                           0x04                                    // rw0- IR中断标志位
 #define T2IP                           0x02                                    // rw0- IP中断标志位
 #define T2IF                           0x01                                    // rw0- IF中断标志位
/******************* Bits definition for TIM2_CR2 register ********************/
 #define TIM2_B_EDGE_SEL                0x20                                    // rw-- TIM2QEP_B输出极性配置
 #define TIM2_A_EDGE_SEL                0x10                                    // rw-- TIM2QEP_A输出极性配置
 #define TIM2_Z_SEL1                    0x08                                    // rw-- TIM2QEP_Z输出选择1
 #define TIM2_Z_SEL0                    0x04                                    // rw-- TIM2QEP_Z输出选择0
 #define TIM2_AB_SEL1                   0x02                                    // rw-- TIM2QEP_AB输出选择1
 #define TIM2_AB_SEL0                   0x01                                    // rw-- TIM2QEP_AB输出选择0
/******************************************************************************/
/*                                   TIMER3                                   */
/******************************************************************************/
/******************* Bits definition for TIM3_CR0 register ********************/
 #define T3PSC2                         0x80                                    // rw-- Timer3分频系数2
 #define T3PSC1                         0x40                                    // rw-- Timer3分频系数1
 #define T3PSC0                         0x20                                    // rw-- Timer3分频系数0
 #define T3FE1                          0x10                                    // rw-- 滤波选择1
 #define T3FE0                          0x08                                    // rw-- 滤波选择0
 #define T3OCM                          0x04                                    // rw-- 输出模式选择
 #define T3OPM                          0x02                                    // rw-- 单次模式使能
 #define T3MOD                          0x01                                    // rw-- Timer3模式选择
/******************* Bits definition for TIM3_CR1 register ********************/
 #define T3EN                           0x01                                    // rw-- Timer3使能
/******************* Bits definition for TIM3_IER register ********************/
 #define T3IRE                          0x04                                    // rw-- IR中断使能位
 #define T3IPE                          0x02                                    // rw-- IP中断使能位
 #define T3IFE                          0x01                                    // rw-- IF中断使能位
/******************* Bits definition for TIM3_SR register ********************/
 #define T3IR                           0x04                                    // rw0- IR中断标志位
 #define T3IP                           0x02                                    // rw0- IP中断标志位
 #define T3IF                           0x01                                    // rw0- IF中断标志位
/******************************************************************************/
/*                                   TIMER4                                   */
/******************************************************************************/
/******************* Bits definition for TIM4_CR0 register ********************/
 #define T4PSC2                         0x80                                    // rw-- Timer4分频系数2
 #define T4PSC1                         0x40                                    // rw-- Timer4分频系数1
 #define T4PSC0                         0x20                                    // rw-- Timer4分频系数0
 #define T4FE1                          0x10                                    // rw-- 滤波选择1
 #define T4FE0                          0x08                                    // rw-- 滤波选择0
 #define T4OCM                          0x04                                    // rw-- 输出模式选择
 #define T4OPM                          0x02                                    // rw-- 单次模式使能
 #define T4MOD                          0x01                                    // rw-- Timer4模式选择
/******************* Bits definition for TIM4_CR1 register ********************/
 #define T4EN                           0x01                                    // rw-- Timer4使能位
/******************* Bits definition for TIM4_IER register ********************/
 #define T4IRE                          0x04                                    // rw-- IR中断使能位
 #define T4IPE                          0x02                                    // rw-- IP中断使能位
 #define T4IFE                          0x01                                    // rw-- IF中断使能位
/******************* Bits definition for TIM4_SR register ********************/
 #define T4IR                           0x04                                    // rw0- IR中断标志位
 #define T4IP                           0x02                                    // rw0- IP中断标志位
 #define T4IF                           0x01                                    // rw0- IF中断标志位
/******************************************************************************/
/*                                   TIMER5                                   */
/******************************************************************************/
/******************* Bits definition for TIM5_CR0 register ********************/
 #define T5INM2                         0x400                                   // rw-- Timer5滤波系数2
 #define T5INM1                         0x200                                   // rw-- Timer5滤波系数1
 #define T5INM0                         0x100                                   // rw-- Timer5滤波系数0
 #define T5PSC2                         0x80                                    // rw-- Timer5分频系数2
 #define T5PSC1                         0x40                                    // rw-- Timer5分频系数1
 #define T5PSC0                         0x20                                    // rw-- Timer5分频系数0
 #define T5CES                          0x10                                    // rw-- Timer5沿边选择
 #define T5DIRIN                        0x08                                    // rw-- 方向输入极性选择
 #define T5MOD2                         0x04                                    // rw-- Timer5模式选择2
 #define T5MOD1                         0x02                                    // rw-- Timer5模式选择1
 #define T5MOD0                         0x01                                    // rw-- Timer5模式选择0
/******************* Bits definition for TIM5_CR1 register ********************/
 #define T5_CNTR_CLR_EN                 0x100                                   // rw-- QEP加载dr配置
 #define T5OPM                          0x80                                    // rw-- Timer5单次模式使能
 #define T5QEP_IN_CNTR_CLR              0x40                                    // rw-- QEP Z输入清CNTR使能
 #define T5Z_EDGE_SEL                   0x20                                    // rw-- QEP模式沿边选择
 #define T5SS                           0x10                                    // rw-- 步进模式
 #define T5OCM                          0x04                                    // rw-- 输出模式选择
 #define T5_DIR_R                       0x02                                    // r--- QEP&步进电机旋转方向
 #define T5EN                           0x01                                    // rw-- Timer5使能
/******************* Bits definition for TIM5_IER register ********************/
 #define T5IRE                          0x04                                    // rw-- IR中断使能位
 #define T5IPE                          0x02                                    // rw-- IP中断使能位
 #define T5IFE                          0x01                                    // rw-- IF中断使能位
/******************* Bits definition for TIM5_SR register ********************/
 #define T5IR                           0x04                                    // rw0- IR中断标志位
 #define T5IP                           0x02                                    // rw0- IP中断标志位
 #define T5IF                           0x01                                    // rw0- IF中断标志位
 /******************* Bits definition for TIM5_CR2 register ********************/
 #define TIM5_B_EDGE_SEL                0x20                                    // rw-- TIM5QEP_B输出极性配置
 #define TIM5_A_EDGE_SEL                0x10                                    // rw-- TIM5QEP_A输出极性配置
 #define TIM5_Z_SEL1                    0x08                                    // rw-- TIM5QEP_Z输出选择1
 #define TIM5_Z_SEL0                    0x04                                    // rw-- TIM5QEP_Z输出选择0
 #define TIM5_AB_SEL1                   0x02                                    // rw-- TIM5QEP_AB输出选择1
 #define TIM5_AB_SEL0                   0x01                                    // rw-- TIM5QEP_AB输出选择0
/******************************************************************************/
/*                                   TIMER6                                   */
/******************************************************************************/
/******************* Bits definition for TIM6_CR0 register ********************/
 #define T6INM2                         0x400                                   // rw-- Timer6滤波系数2
 #define T6INM1                         0x200                                   // rw-- Timer6滤波系数1
 #define T6INM0                         0x100                                   // rw-- Timer6滤波系数0
 #define T6PSC2                         0x80                                    // rw-- Timer6分频系数2
 #define T6PSC1                         0x40                                    // rw-- Timer6分频系数1
 #define T6PSC0                         0x20                                    // rw-- Timer6分频系数0
 #define T6CES                          0x10                                    // rw-- Timer6沿边选择
 #define T6DIRIN                        0x08                                    // rw-- 方向输入极性选择
 #define T6MOD2                         0x04                                    // rw-- Timer6模式选择2
 #define T6MOD1                         0x02                                    // rw-- Timer6模式选择1
 #define T6MOD0                         0x01                                    // rw-- Timer6模式选择0
/******************* Bits definition for TIM6_CR1 register ********************/
 #define T6_CNTR_CLR_EN                 0x100                                   // rw-- QEP加载dr配置
 #define T6OPM                          0x80                                    // rw-- Timer6单次模式使能位
 #define T6QEP_IN_CNTR_CLR              0x40                                    // rw-- QEP Z输入清CNTR使能
 #define T6Z_EDGE_SEL                   0x20                                    // rw-- QEP模式沿边选择
 #define T6SS                           0x10                                    // rw-- 步进模式
 #define T6OCM                          0x04                                    // rw-- 输出模式选择
 #define T6_DIR_R                       0x02                                    // r--- QEP&步进电机旋转方向
 #define T6EN                           0x01                                    // rw-- Timer6使能
/******************* Bits definition for TIM6_IER register ********************/
 #define T6IRE                          0x04                                    // rw-- IR中断使能位
 #define T6IPE                          0x02                                    // rw-- IP中断使能位
 #define T6IFE                          0x01                                    // rw-- IF中断使能位
/******************* Bits definition for TIM6_SR register ********************/
 #define T6IR                           0x04                                    // rw0- IR中断标志位
 #define T6IP                           0x02                                    // rw0- IP中断标志位
 #define T6IF                           0x01                                    // rw0- IF中断标志位
/******************* Bits definition for TIM6_CR2 register ********************/
 #define TIM6_B_EDGE_SEL                0x20                                    // rw-- TIM6QEP_B输出极性配置
 #define TIM6_A_EDGE_SEL                0x10                                    // rw-- TIM6QEP_A输出极性配置
 #define TIM6_Z_SEL1                    0x08                                    // rw-- TIM6QEP_Z输出选择1
 #define TIM6_Z_SEL0                    0x04                                    // rw-- TIM6QEP_Z输出选择0
 #define TIM6_AB_SEL1                   0x02                                    // rw-- TIM6QEP_AB输出选择1
 #define TIM6_AB_SEL0                   0x01                                    // rw-- TIM6QEP_AB输出选择0
/******************************************************************************/
/*                                   TIMER7                                   */
/******************************************************************************/
/******************* Bits definition for TIM7_CR0 register ********************/
 #define T7PSC2                         0x80                                    // rw-- Timer7分频系数2
 #define T7PSC1                         0x40                                    // rw-- Timer7分频系数1
 #define T7PSC0                         0x20                                    // rw-- Timer7分频系数0
 #define T7FE1                          0x10                                    // rw-- 滤波模式1
 #define T7FE0                          0x08                                    // rw-- 滤波模式0
 #define T7OCM                          0x04                                    // rw-- 输出模式选择
 #define T7OPM                          0x02                                    // rw-- 单次模式使能
 #define T7MOD                          0x01                                    // rw-- Timer7模式选择
/******************* Bits definition for TIM7_CR1 register ********************/
 #define T7EN                           0x01                                    // rw-- Timer7模块使能位
/******************* Bits definition for TIM7_IER register ********************/
 #define T7IRE                          0x04                                    // rw-- IR中断使能位
 #define T7IPE                          0x02                                    // rw-- IP中断使能位
 #define T7IFE                          0x01                                    // rw-- IF中断使能位
/******************* Bits definition for TIM7_SR register ********************/
 #define T7IR                           0x04                                    // rw0- IR中断标志位
 #define T7IP                           0x02                                    // rw0- IP中断标志位
 #define T7IF                           0x01                                    // rw0- IF中断标志位
/******************************************************************************/
/*                                   TIMER8                                   */
/******************************************************************************/
/******************* Bits definition for TIM8_CR0 register ********************/
#define T8PSC2                         0x80                                    // rw-- Timer8分频系数2
#define T8PSC1                         0x40                                    // rw-- Timer8分频系数1
#define T8PSC0                         0x20                                    // rw-- Timer8分频系数0
#define T8FE1                          0x10                                    // rw-- 滤波选择1
#define T8FE0                          0x08                                    // rw-- 滤波选择0
#define T8OCM                          0x04                                    // rw-- 输出模式选择
#define T8OPM                          0x02                                    // rw-- 单次模式使能
#define T8MOD                          0x01                                    // rw-- Timer8模式选择
/******************* Bits definition for TIM8_CR1 register ********************/
#define T8EN                           0x01                                    // rw-- Timer8使能
/******************* Bits definition for TIM8_IER register ********************/
#define T8IRE                          0x04                                    // rw-- IR中断使能位
#define T8IPE                          0x02                                    // rw-- IP中断使能位
#define T8IFE                          0x01                                    // rw-- IF中断使能位
/******************* Bits definition for TIM8_SR register ********************/
#define T8IR                           0x04                                    // rw0- IR中断标志位
#define T8IP                           0x02                                    // rw0- IP中断标志位
#define T8IF                           0x01                                    // rw0- IF中断标志位

/******************************************************************************/
/*                                   STPC                                     */
/******************************************************************************/
/******************* Bits definition for STPCx_CR register ********************/
#define PCOM_IE                        0x40                                    // rw-- 位置比较中断使能
#define PCOM_SEL1                      0x20                                    // rw-- 位置比较配置位1
#define PCOM_SEL0                      0x10                                    // rw-- 位置比较配置位0
#define PCOM_EN                        0x08                                    // rw-- 位置比较使能
#define STRO_IE                        0x04                                    // rw-- 探针中断使能
#define STRO_SEL                       0x02                                    // rw-- 探针触发沿边选择
#define STRO_EN                        0x01                                    // rw-- 探针功能使能
/******************* Bits definition for STPCx_SR register ********************/
#define PCOM_IF                        0x02                                    // rw-- 位置比较中断标志位
#define STRO_IF                        0x01                                    // rw-- 探针中断标志位

/******************************************************************************/
/*                                   SysTick                                  */
/******************************************************************************/
/********************* Bits definition for SYST_SR register *******************/
 #define INTCS_MD1                      0x08                                    // rw-- /* factory */
 #define INTCS_MD0                      0x04                                    // rw-- /* factory */
 #define SYSTIF                         0x02                                    // rw0- Systick中断标志位
 #define SYSTEN                         0x01                                    // rw-- Systick使能位

/******************************************************************************/
/*                                     CAL                                    */
/******************************************************************************/
/********************* Bits definition for CAL_CR register ********************/
 #define CALBSY                         0x8000

/******************************************************************************/
/*                                     RTC                                    */
/******************************************************************************/
/********************* Bits definition for RTC_CR register ********************/
 #define RTCEN                          0x80                                    // rw-- RTC使能
 #define RTCIF                          0x40                                    // rw0- RTC中断标志志位
 #define SCKSEL                         0x20                                    // rw-- 校准慢时钟源选择 /* factory */
 #define ISOSCEN                        0x10                                    // rw-- 内部慢时钟使能
 #define ESCKSEL                        0x02                                    // rw-- 外部慢时钟数字输入PIN选择 /* factory */
 #define ESCKEN                         0x01                                    // rw-- 外部慢时钟数字输入使能  /* factory */

/******************************************************************************/
/*                                     OSC                                    */
/******************************************************************************/
/********************* Bits definition for OSC_CR register ********************/
 #define MCDRET                         0x040                                   // rw1- 尝试退出MCD状态  /* factory */
 #define PLLLIE                         0x020                                   // rw-- PLL丢失中断使能  /* factory */
 #define MCDIE                          0x010                                   // rw-- 时钟缺失中断使能  /* factory */
 #define EFOSCAE                        0x08                                    // rw-- 外部快时钟PIN模拟使能  /* factory */
 #define EFCKEN                         0x04                                    // rw-- 外部快时钟强制使能  /* factory */
 #define IFCKNE                         0x02                                    // rw-- 内部快时钟强制使能  /* factory */
 #define PLLEN                          0x01                                    // rw-- PLL使能  /* factory */
/********************* Bits definition for OSC_SR register ********************/
 #define PLL_LOCK                       0x08                                    // r--- PLL锁相标志  /* factory */
 #define PLLCK_STATUS                   0x04                                    // r--- PLL时钟源选择标志位  /* factory */
 #define PLLLIF                         0x02                                    // rw0- PLL时钟丢失中断标志位  /* factory */
 #define MCDIF                          0x01                                    // rw0- MCD中断标志位  /* factory */

/******************************************************************************/
/*                                     IWDT                                   */
/******************************************************************************/

/******************************************************************************/
/*                                     WWDT                                   */
/******************************************************************************/
/********************* Bits definition for WWDT_CR register ********************/
 #define WWDTSTA                        0x80                                    // rw1- WWDT使能
/********************* Bits definition for WWDT_CFR register *******************/
 #define WWDTIE                         0x200                                   // rw-- WWDT提前唤醒中断使
 #define WWDTPSC1                       0x100                                   // rw-- WWDT计数分频配置1
 #define WWDTPSC0                       0x80                                    // rw-- WWDT计数分频配置0

/********************* Bits definition for WWDT_SR register ********************/
 #define EWIF                           0x01                                    // rw0- WWDT提前唤醒中断标志位


/******************************************************************************/
/*                                     CRC                                    */
/******************************************************************************/
/********************* Bits definition for CRC_CR register ********************/
 #define RESINV                         0x80                                    // rw-- 输出结果翻转
 #define DATINV                         0x40                                    // rw-- 数据输入翻转
 #define CRCSEL                         0x20                                    // rw-- CRC算子选择
 #define CRCDONE                        0x10                                    // r1-- 自动CRC完成标志
 #define CRCDINI                        0x08                                    // w1-- CRC初始化
 #define CRCVAL                         0x04                                    // rw-- CRC初始化的值
 #define AUTOINT                        0x02                                    // w1-- CRC自动计算使能

/******************************************************************************/
/*                                     CCFG                                   */
/******************************************************************************/
/********************* Bits definition for CCFG2 register ********************/
 #define LVWPD                          0x80                                    // rw-- 低压预警使能
 #define LVWIE                          0x40                                    // rw-- 低压预警中断使能
 #define IWDTEN                         0x20                                    // rw-- 独立WDT使能
 #define PLLSRC                         0x02                                    // rw-- PLL时钟源选择
 #define FCKMOD                         0x01                                    // rw-- 系统时钟选择
/********************* Bits definition for CCFG3 register ********************/
 #define EOSSET3                        0x80000                                 // rw-- 电过应力等级设置3
 #define EOSSET2                        0x40000                                 // rw-- 电过应力等级设置2
 #define EOSSET1                        0x20000                                 // rw-- 电过应力等级设置1
 #define EOSSET0                        0x10000                                 // rw-- 电过应力等级设置0
 #define LVRSEL1                        0x8000                                  // rw-- 低电压复位电压选择1
 #define LVRSEL0                        0x4000                                  // rw-- 低电压复位电压选择0 
 #define EOS_RST_EN                     0x800                                   // rw-- EOS电过度应力使能
 #define LVWSEL                         0x100                                   // rw-- VDD5低压预警电压选择
 #define XT_CUR_CFG1                    0x20                                    // rw-- 晶体电路驱动能力配置1
 #define XT_CUR_CFG0                    0x10                                    // rw-- 晶体电路驱动能力配置0
 #define XT_GF_CFG1                     0x08                                    // rw-- 时钟电路毛刺滤波1
 #define XT_GF_CFG0                     0x04                                    // rw-- 时钟电路毛刺滤波0
 #define ECMOD                          0x02                                    // rw-- 外部时钟源选择
 #define PLLFSEL                        0x01                                    // rw-- PLL时钟频率选择


/******************************************************************************/
/*                                   ME                                       */
/******************************************************************************/
/********************* Bits definition for ME_CR register *********************/
 #define CPUMEDIS                       0x8000                                  // rw-- 软件禁止写FOC变量寄存器       /* factory */
 #define CPUBFWE                        0x4000                                  // rw-- CPU写缓存器使能，需要CPUMEDIS为0       /* factory */
 #define UDC_DIS                        0x2000                                  // rw-- 禁止UDC采样，需软件采样UDC填到ME里
 #define DRVSYN_EN                      0x20                                    // rw-- 双电机同步使能
 #define ME_BLK_MD                      0x10                                    // rw-- CPU处于debug停止的时候的处理方式       /* factory */
 #define INTCD                          0x08                                    // rw-- 外部中断1清零DRV计数，用于ETHERCAT同步
 #define TRIG_MD                        0x04                                    // rw-- FOC1双电阻同步采样使能，双电机模式下禁止使用
 #define UDC2_MAEN                      0x02                                    // rw-- FOC2的UDC自动模式使能，用于FOC1和FOC2的母线电压不同的情况
// #define FOCEN                          0x01                                    // rw-- FOC模块总使能，不使能时处于复位状态
/********************* Bits definition for ME_IER register *********************/
 #define NPE1                           0x0008                                  // rw-- 匹配状态1暂停使能       /* factory */
 #define NIE1                           0x0004                                  // rw-- 匹配状态1中断使能       /* factory */
 #define NPE0                           0x0002                                  // rw-- 匹配状态0暂停使能       /* factory */
 #define NIE0                           0x0001                                  // rw-- 匹配状态0中断使能       /* factory */
/********************* Bits definition for ME_IFR register *********************/
 #define NPF1                           0x0200                                  // rw-- 匹配状态1暂停状态       /* factory */
 #define NPF0                           0x0100                                  // rw-- 匹配状态1中断标志       /* factory */
 #define NIF1                           0x0002                                  // rw-- 匹配状态0暂停状态       /* factory */
 #define NIF0                           0x0001                                  // rw-- 匹配状态0中断标志       /* factory */

///****************************************************************************/
/*                                   Driver                                   */
/******************************************************************************/
/********************* Bits definition for DRVx_CR register ********************/
 #define DRV_CNTR_DIR                   0x8000                                  // rw-- drv计数器的计数方向，0-向上
 #define IMM_UPDATE                     0x80                                    // rw-- 占空比立即更新
 #define OCP_MOEMD                      0x40                                    // rw-- 过流保护中断MOE使能（方波驱动时）
 #define MOEMD1                         0x20                                    // rw-- 00：MOE不自动清零  10：MOE自动清0，且在Driver计数器的上溢下溢事件或5.3μs后自动使能MOE（方波驱动时）
 #define MOEMD0                         0x10                                    // rw-- 01：MOE自动清零  11:MOE自动清0，且在Driver计数器的上溢下溢事件或2.6μs后自动使能MOE（方波驱动时）
 #define DRVMD                          0x08                                    // rw-- 0：三角波模式  1：锯齿波模式
 #define DDIR                           0x04                                    // rw-- DRV方向
 #define DRVEN                          0x02                                    // rw-- DRV使能
 #define DRVOE                          0x01                                    // rw-- DRV输出使能
/********************* Bits definition for DRVx_IER register ********************/
 #define CAIE                           0x20                                    // rw-- 计算完成异常中断使能
 #define THIE                           0x10                                    // rw-- 电角度一周中断使能
 #define FGIE                           0x08                                    // rw-- FG中断使能
 #define DCIP                           0x04                                    // rw-- 0: 每个载波周期产生DCIF中断  1：间隔一个载波周期产生DCIF中断
 #define DCIM1                          0x02                                    // rw-- 00：不产生DCIF中断  01：向上计数时产生DCIF中断
 #define DCIM0                          0x01                                    // rw-- 01：向下计数时产生DCIF中断  11: 向上/向下计数时都产生中断
/********************* Bits definition for DRVx_IFR register ********************/
 #define CAIF                           0x20                                    // rw0- 计算完成异常中断标志位
 #define THIF                           0x10                                    // rw0- 电角度179->180产生中断，与FGIF相位不同
 #define FGIF                           0x08                                    // rw0- FG中断标志
 #define DCIF                           0x01                                    // rw0- DRV比较中断标志
/********************* Bits definition for DRVx_PER register ********************/
 #define PER_MD                         0x8000                                  // rw-- 保护灵敏度设置
 #define PL_MD							0x1000                                  // rw-- 新缺相保护使能
 #define LOCK_MD						0x0800                                  // rw-- 伺服堵转使能
 #define LOCK2EN                        0x0400                                  // rw-- 堵转判断2使能
 #define LOCK1EN                        0x0200                                  // rw-- 堵转判断1使能
 #define LOCK0EN                        0x0100                                  // rw-- 堵转判断0使能
 #define ODCIF_EN                       0x080                                   // rw-- 载波中断超时保护使能
 #define OSPD_AUTO                      0x040                                   // rw-- 速度过超自动计算，载波周期计算一次
 #define OVEL_AUTO                      0x020                                   // rw-- 速度超差自动计算，外环周期计算一次
 #define PL_AUTO                        0x010                                   // rw-- 缺相自动计算并触发中断
 #define LOCK_AUTO                      0x08                                    // rw-- 堵转自动计算使能
 #define OUVP_AUTO1                     0x04                                    // rw-- 10：systick计算一次
 #define OUVP_AUTO0                     0x02                                    // rw-- 01：载波周期计算一次
 #define SOCP_AUTO                      0x01                                    // rw-- 软件过流自动计算使能，载波周期计算一次
/********************* Bits definition for DRVx_PTR register ********************/
 #define RAMP_TRG                       0x0200                                  // w1-- 爬坡手动触发
 #define WPI_TRG                        0x0100                                  // w1-- 外环PI计算触发
 #define OSPD_TRG                       0x20                                    // w1-- 速度过超计算触发
 #define OVEL_TRG                       0x10                                    // w1-- 速度超差计算触发
 #define PL_TRG                         0x08                                    // w1-- 缺相计算软件触发，使能后计算一次。如果缺相生效触发中断
 #define LOCK_TRG                       0x04                                    // w1-- 堵转计算触发
 #define OUVP_TRG                       0x02                                    // w1-- 过欠压计算软件触发
 #define SOCP_TRG                       0x01                                    // w1-- 软件过流计算软件触发
/********************* Bits definition for DRV_PSR register ********************/
 #define CBA2                           0x4000                                  // r--- 扇区号
 #define CBA1                           0x2000                                  // r--- 扇区号
 #define CBA0                           0x1000                                  // r--- 扇区号
 #define RIF                            0x100                                   // rw0- 电流基准异常状态，非中断标志
 #define ODCIF_IF						0x80                                    // rw-- 载波中断超时保护使能中断标志
 #define OSPDIF                         0x40                                    // rw0- 速度过超中断标志
 #define OVELIF                         0x20                                    // rw0- 速度超差中断标志
 #define PLIF                           0x10                                    // rw0- 缺相中断标志
 #define LOCKIF                         0x08                                    // rw0- 堵转中断标志
 #define UVPIF                          0x04                                    // rw0- 欠压中断标志
 #define OVPIF                          0x02                                    // rw0- 过压中断标志
 #define SOCPIF                         0x01                                    // rw0- 软件过流中断标志
/******************** Bits definition for DRV_OUT register ********************/
 #define HREV_EN                        0x8000                                  // rw-- 上桥反相使能，根据predriver选择
 #define LREV_EN                        0x4000                                  // rw-- 下桥反相使能，根据predriver选择
 #define MOE                            0x80                                    // rw-- DRV输出总使能
 #define OISWXL                         0x20                                    // rw-- WX相下桥空闲电平
 #define OISWXH                         0x10                                    // rw-- WX相上桥空闲电平
 #define OISVL                          0x08                                    // rw-- V相下桥空闲电平
 #define OISVH                          0x04                                    // rw-- V相上桥空闲电平
 #define OISUL                          0x02                                    // rw-- U相下桥空闲电平
 #define OISUH                          0x01                                    // rw-- U相上桥空闲电平
/******************** Bits definition for DRVx_CMR register ********************/
 #define WHP                            0x0800                                  // rw-- W相上桥极性
 #define WLP                            0x0400                                  // rw-- W相下桥极性
 #define VHP                            0x0200                                  // rw-- V相上桥极性
 #define VLP                            0x0100                                  // rw-- V相下桥极性
 #define UHP                            0x0080                                  // rw-- U相上桥极性
 #define ULP                            0x0040                                  // rw-- U相下桥极性
 #define WHE                            0x0020                                  // rw-- W相上桥使能
 #define WLE                            0x0010                                  // rw-- W相下桥使能
 #define VHE                            0x0008                                  // rw-- V相上桥使能
 #define VLE                            0x0004                                  // rw-- V相下桥使能
 #define UHE                            0x0002                                  // rw-- U相上桥使能
 #define ULE                            0x0001                                  // rw-- U相下桥使能

/******************************************************************************/
/*                                     PFC                                    */
/******************************************************************************/
/******************** Bits definition for PFC_CR0 register ********************/
 #define COM_ST                         0x100                                   // r--- 前馈补偿当前状态  1：dccm 0：ddcm
 #define UAVGSW                         0x80                                    // rw-- 软件启动算UAVG   0：不启动  1：启动  软件写1，下一时刻硬件自动清零，写零无效
 #define COM_DIS                        0x40                                    // rw-- 前馈补偿禁止  1：只计算com，但不应用到输出
 #define PFC_FM                         0x20                                    // rw-- 保护动作选择   0：CMP5/CMP11各自触发对应输出  1:CMP5/CMP11在任意一路保护，两路都停止输出
 #define UAVGCDIS                       0x10                                    // rw-- 硬件自动算UAVG禁止   0：不禁止  1：禁止
 #define PFCOA                          0x08                                    // rw-- 逐波限流恢复使能
 #define IAC2EN                         0x04                                    // rw-- PFC2使能
 #define PFCOE                          0x02                                    // rw-- PFC输出使能,P04/P05
 #define PFCEN                          0x01                                    // rw-- PFC使能
          
/******************** Bits definition for PFC_CR1 register ********************/
 #define UACSAMSEL1                     0x80                                    // rw-- UAC采样分频1 1/2/4/8个载波采样一次
 #define UACSAMSEL0                     0x40                                    // rw-- UAC采样分频0 1/2/4/8个载波采样一次
 #define UTHR                           0x20                                    // rw-- UAC算平均时以多少伏为起始
 #define UCTHR4                         0x10                                    // rw-- UAC的2/3N设置4
 #define UCTHR3                         0x08                                    // rw-- UAC的2/3N设置3
 #define UCTHR2                         0x04                                    // rw-- UAC的2/3N设置2
 #define UCTHR1                         0x02                                    // rw-- UAC的2/3N设置1
 #define UCTHR0                         0x01                                    // rw-- UAC的2/3N设置0
          
/******************** Bits definition for PFC_CR2 register ********************/
 #define PFC_IF                         0x8000                                  // rw0- PFC载波下溢中断标志
 #define IAC_DDCM_DIS                   0x2000                                  // rw-- KIAC模式选择  0：内部计算vo/(vo-vi)*don  1：内部不计算vo/(vo-vi)*don
 #define DDCM_SEL                       0x1000                                  // rw-- PFC_DCCMCS0的效果  0: 偏移，正数为减少  1:缩放，Q15格式
 #define PFC_UDCSEL                     0x800                                   // rw-- PFC_UDC是否滤波  0: NFOC_UDCFLT  1:NFOC_UDC
 #define PFC_IE                         0x400                                   // rw-- PFC载波下溢中断使能
 #define PFC_DR2MD                      0x200                                   // rw-- 使能后，dr2的值跟dr一样
 #define DRMIN_EN                       0x100                                   // rw-- 输出最小占空比限制
 #define PFC_COMMD1                     0x80                                    // rw-- 前馈补偿方式   00：内部算udc_uk/(uavg * uavg)；01: 内部只算udc_uk；1x：软件填kddcm
 #define PFC_COMMD0                     0x40                                    // rw-- 前馈补偿方式   00：内部算udc_uk/(uavg * uavg)；01: 内部只算udc_uk；1x：软件填kddcm
 #define PFC_TRIGMD                     0x20                                    // rw-- IAC/IAC2采样时机选择  0:在高电平末端采 1:在高电平中间采
 #define DRMIN_THR4                     0x10                                    // rw-- 输出最小占空比配置位4
 #define DRMIN_THR3                     0x08                                    // rw-- 输出最小占空比配置位3
 #define DRMIN_THR2                     0x04                                    // rw-- 输出最小占空比配置位2
 #define DRMIN_THR1                     0x02                                    // rw-- 输出最小占空比配置位1
 #define DRMIN_THR0                     0x01                                    // rw-- 输出最小占空比配置位0
 
/******************************************************************************/
/*                                      FOC                                    */
/******************************************************************************/
/******************** Bits definition f or DRV_FCR0 register *******************/
// rw-- 001：est_dis 跳过估算器，从ZALP HA开始计算，用户填NFOC_ZALPHA/ZBETA，MR可以用这个模式
// rw-- 010：zab_dis 跳过估算器到ZALPHA /ZBETA，从EALPHA/EBETA开始计算，用户填EALPHA/EBETA
// rw-- 011：eab_dis 跳过估算器到EALPHA /EBETA，从速度开始计算，用户填NFOC_OEMGA，备选模式，目前没想到能用在哪里
// rw-- 100：ang_dis 跳过估算器到角度的 计算，从电流环开始计算，用户填NFOC_THETA，伺服大部分用这个模式
// rw-- 101：smozab_dis，跳过SMO中估算 电流到ZALPHA，从ZALPHA开始计算，用户填NFOC_ZALPHA/ZBETA
 #define FDIS_MD2                       0x8000                                   // rw-- FDISMD[2]
 #define FDIS_MD1                       0x4000                                   // rw-- FDISMD[1]
 #define FDIS_MD0                       0x2000                                   // rw-- FDISMD[0]
 #define UALBE_SEL                      0x1000                                   // rw-- FOC_UDCALP/UDCBET的计算源选择
 #define LO_EN                          0x0800                                   // rw-- 低速观测器使能
 #define ITPOWMD1                       0x0400                                   // rw-- 功率环计算方式选择配置1
 #define ITPOWMD0                       0x0200                                   // rw-- 功率环计算方式选择配置0
 #define NMFPEN                         0x0100                                   // rw-- AO观测器使能
 #define NVQDIS                         0x0080                                   // rw-- Q轴PI禁止使能
 #define NVDDIS                         0x0040                                   // rw-- D轴PI禁止使能
 #define NOVMDL                         0x0020                                   // rw-- 过调制使能
 #define NCSAMMD3                       0x0010                                   // rw-- 电流采样模式配置3
 #define NCSAMMD2                       0x0008                                   // rw-- 电流采样模式配置2
 #define NCSAMMD1                       0x0004                                   // rw-- 电流采样模式配置1
 #define NCSAMMD0                       0x0002                                   // rw-- 电流采样模式配置0
 #define NCALEN                         0x0001                                   // rw-- FOC计算使能，每个载波进行FOC计算，电流采样，占空比自动更新到DRV
/******************** Bits definition for DRV_FCR1 register *******************/
 #define WPIAUTO1                       0x8000                                   // rw-- SYSTICK计算一次外环
 #define WPIAUTO0                       0x4000                                   // rw-- 载波周期计算一次外环
 #define WPILDEN                        0x2000                                   // rw-- IQREF自动装载使能，IQREF=WUK
 #define FG_MD                          0x1000                                   // rw-- FG计数时钟选择  0：750KHz计数   1：48MHz计数
 #define WPIMD1                         0x0800                                   // rw-- 00:用户手动填WFDB 01:速度环
 #define WPIMD0                         0x0400                                   // rw-- 10:电压环         11:功率环
 #define RAMP_AUTO                      0x0200                                   // rw-- 硬件自动爬坡使能，SYSTICK计算1次
 #define RAMPMD1                        0x0100                                   // rw-- 00：不更新            01：自动更新到WREF
 #define RAMPMD0                        0x0080                                   // rw-- 10：自动更新到IQREF 11：自动更新到UQ[31:16]
 #define OME_STA_EN                     0x0040                                   // rw-- OMEGA启动使能
 #define CT_SEL                         0x0020                                   // rw-- 计算FOC时机 0:电流采样后下次上溢点计算FOC  1:电流采样后立刻计算FOC
 #define ANGMAMD                        0x0010                                   // rw-- 角度手动模式 0: THETA来源于ETHETA 1：THETA来源于软件
 #define OME_ABS_EN                     0x0008                                   // rw-- 估算角度反转使能
 #define FG_IDLE_LEVEL                  0x0004                                   // rw-- FG初始电平
 #define FG_CALEN                       0x0002                                   // rw-- FG计算使能
 #define FG_OE                          0x0001                                   // rw-- FG输出使能
/******************** Bits definition for DRV_FCR2 register *******************/
 #define HFI_ST                         0x8000                                   // rw-- 高频注入时UD状态0：给正的UD  1：给负的UD
 #define OFFSET_EN                      0x4000                                   // rw-- 电流基准自动校准使能
 #define FWEAK_MD                       0x2000                                   // rw-- 弱磁模式：模式0，模式1
 #define FWEAK_EN                       0x1000                                   // rw-- 弱磁使能
 #define HFI_MD1                        0x0800                                   // rw-- 高频注入delta delta ig模式使能
 #define UABC_EN                        0x0400                                   // rw-- 三相电压采样使能
 #define OMESTA_MD                      0x0200                                   // rw-- OMEGA启动切换方式1：新的启动切换方式  0：旧的启动切换方式
 #define NSEG5                          0x0100                                   // rw-- 5段式使能
 #define UQINJ_EN                       0x0080                                   // rw-- UQ注入使能，使能自动更新NFOC_UQCPS
 #define FO_EN                          0x0040                                   // rw-- 磁链观测器使能
 #define HFI_MD                         0x0020                                   // rw-- 高频注入delta delta iq模式使能
 #define HFI_2XMD                       0x0010                                   // rw-- 高频注入2倍频处理使能
 #define OMELD_EN                       0x0008                                   // rw-- 速度选择0：选择估算器的速度进行后续的角度计算  1：选择HFI或LO的速度
 #define HFI_CAL_EN                     0x0004                                   // rw-- 高频注入使能
 #define HFI_TOG_EN                     0x0002                                   // rw-- HFI_ST自动取反使能
 #define IDQ_MD                         0x0001                                   // rw-- ID和IQ模式选择使能，id =（id0 + id1）/ 2，iq =（iq0 + iq1）/ 2
 /******************** Bits definition for DRV_FCR3 register *******************/
 #define EPI_DIS_ONCE                   0x8000                                   // rw-- 估算器PI禁止一次使能      /* factory */
 #define DEL_MD                         0x2000                                   // rw-- 估算DELTHE计算模式  0：atan   1：sin/cos
 #define SMO_MD                         0x1000                                   // rw-- SMO计算模式  0：ZALPHA/ZBETA+EALPHA/EBETA   1：ZALPHA/ZBETA+0
 #define QFAC_SEL4                      0x0800                                   // rw-- iqref滤波器4数据格式选择 0：Q29   1：Q20
 #define QFAC_SEL3                      0x0400                                   // rw-- iqref滤波器3数据格式选择 0：Q29   1：Q20
 #define QFAC_SEL2                      0x0200                                   // rw-- iqref滤波器2数据格式选择 0：Q29   1：Q20
 #define QFAC_SEL1                      0x0100                                   // rw-- iqref滤波器1数据格式选择 0：Q29   1：Q20
 #define IQRF4_EN                       0x0080                                   // rw-- iqref滤波器4使能
 #define IQRF3_EN                       0x0040                                   // rw-- iqref滤波器3使能
 #define IQRF2_EN                       0x0020                                   // rw-- iqref滤波器2使能
 #define IQRF1_EN                       0x0010                                   // rw-- iqref滤波器1使能
 #define IQRF_SEL                       0x0008                                   // rw-- iqref滤波器计算周期选择  0:电流环  1:速度环
 #define IIG_EN                         0x0004                                   // rw-- 屏蔽所有电流采样模式扇区切换时的第一拍电流     /* factory */
 #define DLY_EN                         0x0002                                   // rw-- foc计算延迟使能，配合ct_sel使能使用，一般在高载波时使用
 #define SAMPM_EN                       0x0001                                   // rw-- 采样点手动使能
 /******************** Bits definition for DRV_FCR4 register *******************/
 #define MMT_CAL						0x8000                                   // rw-- M/MT法计算标记  读 0:M/MT计算完成  1:M/MT法计算中  写 0:无意义  1:启动M/MT法计算 （注:该位软件写1，硬件清0）
 #define SF_CAL							0x4000                                   // rw-- 速度反馈滤波器计算标记 读 0:滤波器计算完成 1:滤波器计算中 写 0:无意义 1:启动滤波器计算
 #define WPI_CAL						0x2000                                   // rw-- 外环计算标记(只读) 0:不执行外环计算 1:执行外环计算
 #define SPEED_AUTO						0x1000                                   // rw-- 速度自动计算使能 cal_en=0: 只算MMT和均值滤波 cal_en=1:电流环只算MMT和均值滤波，外环算PDFF
 #define CUR_SAM_EN						0x0800                                   // rw-- 强制电流采样使能，使能后无论是否使能cal_en都进行电流采样 0:不使能 1:使能
 #define IQREF_INV						0x0400                                   // rw-- 四级滤波器输出取反后装载进IQREF 0:不使能 1:使能
 #define PDFF_EN						0x0200                                   // rw-- 外环PDFF使能 0:外环使用PI 1:外环使用PDFF
 #define WPI_CAL_CYCLE1                 0x0100                                   // rw-- 外环计算周期选择(DRV_FCR1[wpi_auto]须配11)  00:每1个MMT计算周期 01:每2个MMT计算周期
 #define WPI_CAL_CYCLE0                 0x0080                                   // rw-- 外环计算周期选择(DRV_FCR1[wpi_auto]须配11)  10:每4个MMT计算周期 11:每8个MMT计算周期
 #define SLF2_EN                        0x0040                                   // rw-- 速度反馈低通滤波器2使能	0:不使能  1:使能
 #define SLF1_EN                        0x0020                                   // rw-- 速度反馈低通滤波器1使能	0:不使能  1:使能
 #define SMF_EN                         0x0010                                   // rw-- 速度反馈均值滤波器使能	0:不使能  1:使能
 #define MMT_CAL_CYCLE1                 0x0008                                   // rw-- M/MT法计算周期选择  00:每1个载波中断 01:每2个载波中断
 #define MMT_CAL_CYCLE0                 0x0004                                   // rw-- M/MT法计算周期选择  10:每4个载波中断 11:每8个载波中断
 #define MMT_SEL                        0x0002                                   // rw-- M/MT法选择  0:M法  1:MT法
 #define UDQ_LPF_EN                     0x0001                                   // rw-- UDQ低通滤波器使能	0:不使能  1:使能
/******************** Bits definition for DRV_FCR5 register *******************/
 #define WPI_SERVO_EN					0x8000                                   // rw-- 伺服外环计算使能(只读) 0:不执行外环计算 1:执行外环计算，每个载波更新，比WPI_CAL更宽，便于软件采
 #define IQRF_UPDATE					0x4000                                   // rw-- 伺服四级滤波器第一级系数更新使能，0:不使能  1:使能
 #define ANGFU_MD1                      0x1000									 //角度融合模式位
 #define ANGFU_MD0                      0x0800									 //角度融合模式位
 #define DTC_EN							0x0400									 //死区补偿使能, 0:不使能, 1:使能
 #define ENCODER_STA_CYCLE1             0x0100                                   // rw-- 绝对式编码器自动触发周期选择  00:每1个载波中断 01:每2个载波中断
 #define ENCODER_STA_CYCLE0             0x0080                                   // rw-- 绝对式编码器自动触发周期选择  10:每4个载波中断 11:每8个载波中断
 #define ANGFU_MAEN                     0X0010									 //角度融合手动模式使能位
 #define ANGFU_EN                       0x0008									 //角度融合使能位#define IDQ_FB_SEL                      0x0004                  //id,iq低通滤波选择位
 #define IDQ_FB_SEL                     0x0004									 //id,iq电流环反馈值选择位
 #define IDQ_LPF_EN                     0x0002									 //id,iq低通滤波使能
 #define LUT_EN							0x0001									 //0:LUT, 1:Cordic

/******************** Bits definition for DRV_FCR6 register *******************/
 #define CVD_SEL                          0x0400                 //复矢量限幅来源选择位
 #define CVD_EN                           0x0200                 //复矢量解耦使能位
 #define ESTU_SEL2                        0x0100                 //估算器Q格式选择2
 #define ESTU_SEL1                        0x0080                 //估算器Q格式选择1
 #define ESTU_SEL0                        0x0040                 //估算器Q格式选择0
 #define ESTID_SEL1                       0x0020                 //估算器ID选择位1
 #define ESTID_SEL0                       0x0010                 //估算器ID选择位0
 #define MFP_MD                           0x0008                 //SMO/AO模式选择位
 #define EST_MD2                          0x0004                 //估算器模式选择位2
 #define EST_MD1                          0x0002                 //估算器模式选择位1
 #define EST_MD0                          0x0001                 //估算器模式选择位0

/******************** Bits definition for DRV_FCR7 register *******************/
 #define CVKP_SEL1						  0x8000                         //解耦控制器KPQ格式选择位1
 #define CVKP_SEL0 						  0x4000                         //解耦控制器KPQ格式选择位0
 #define CVKI1_SEL1 					  0x2000                         //解耦控制器KI1Q格式选择位1
 #define CVKI1_SEL0  					  0x1000                         //解耦控制器KI1Q格式选择位0
 #define CVKI2_SEL1  					  0x0800                         //解耦控制器KI2Q格式选择位1
 #define CVKI2_SEL0 					  0x0400                         //解耦控制器KI2Q格式选择位0
 #define CVKO_SEL1                        0x0200                         //解耦控制器其他系数Q格式选择位1
 #define CVKO_SEL0                        0x0100                         //解耦控制器其他系数Q格式选择位0
 #define CBA_MTSAM2                       0x0004                         //三电阻电流采样通道选择位
 #define CBA_MTSAM1                       0x0002                         //三电阻电流采样通道选择位
 #define CBA_MTSAM0                       0x0001                         //三电阻电流采样通道选择位


 #define NFOC_BASE                      0x30000000
 #define NFOC_I1                        (*(volatile  int16* )(NFOC_BASE + ( 222*2)))    // RV:0000H 第一次采样ADC值      /* factory */
 #define NFOC_I2                        (*(volatile  int16* )(NFOC_BASE + ( 223*2)))    // RV:0000H 第二次采样ADC值      /* factory */
 #define NFOC_IA                        (*(volatile  int16* )(NFOC_BASE + ( 224*2)))    // RV:0000H 计算得到的IA
 #define NFOC_IB                        (*(volatile  int16* )(NFOC_BASE + ( 225*2)))    // RV:0000H 计算得到的IB
 #define NFOC_IC                        (*(volatile  int16* )(NFOC_BASE + ( 226*2)))    // RV:0000H 计算得到的IC
 #define NFOC_ICMAX                     (*(volatile  int16* )(NFOC_BASE + ( 227*2)))    // RV:0000H IC最大值
 #define NFOC_IAMAX                     (*(volatile  int16* )(NFOC_BASE + ( 228*2)))    // RV:0000H IA最大值
 #define NFOC_IBMAX                     (*(volatile  int16* )(NFOC_BASE + ( 229*2)))    // RV:0000H IB最大值
 #define NFOC_IALPHA                    (*(volatile  int16* )(NFOC_BASE + ( 154*2)))    // RV:0000H Clarke变换后的IALPHA
 #define NFOC_IBETA                     (*(volatile  int16* )(NFOC_BASE + ( 155*2)))    // RV:0000H Clarke变换后的IBETA
 #define NFOC_ID                        (*(volatile  int16* )(NFOC_BASE + ( 156*2)))    // RV:0000H Park变换后的ID
 #define NFOC_IQ                        (*(volatile  int16* )(NFOC_BASE + ( 157*2)))    // RV:0000H Park变换后的IQ
 #define NFOC_IDFLT                     (*(volatile  int32* )(NFOC_BASE + ( 158*2)))    // RV:0000H ID滤波值（32位）
 #define NFOC_IDFLTH                    (*(volatile  int16* )(NFOC_BASE + ( 159*2)))    // RV:0000H ID滤波值高16位
 #define NFOC_IQFLT                     (*(volatile  int32* )(NFOC_BASE + ( 170*2)))    // RV:0000H IQ滤波值（32位）
 #define NFOC_IQFLTH                    (*(volatile  int16* )(NFOC_BASE + ( 171*2)))    // RV:0000H IQ滤波值高16位
 #define NFOC_THETA                     (*(volatile  int32* )(NFOC_BASE + ( 172*2)))    // RV:0000H 角度值（32位）
 #define NFOC_THETAL                    (*(volatile  int16* )(NFOC_BASE + ( 172*2)))    // RV:0000H 角度值低16位
 #define NFOC_THETAH                    (*(volatile  int16* )(NFOC_BASE + ( 173*2)))    // RV:0000H 角度值高16位
 #define NFOC_EALPHA                    (*(volatile  int32* )(NFOC_BASE + ( 174*2)))    // RV:0000H 估算器估算反电动势EALPHA（32位）
 #define NFOC_EALPHAH                   (*(volatile  int16* )(NFOC_BASE + ( 175*2)))    // RV:0000H 估算器估算反电动势EALPHA高16位
 #define NFOC_EBETA                     (*(volatile  int32* )(NFOC_BASE + ( 186*2)))    // RV:0000H 估算器估算反电动势EBETA（32位）
 #define NFOC_EBETAH                    (*(volatile  int16* )(NFOC_BASE + ( 187*2)))    // RV:0000H 估算器估算反电动势EBETA高16位
 #define NFOC_ETHETA                    (*(volatile  int32* )(NFOC_BASE + ( 188*2)))    // RV:0000H 估算器估算角度（32位）
 #define NFOC_ETHETAH                   (*(volatile  int16* )(NFOC_BASE + ( 189*2)))    // RV:0000H 估算器角度高16位
 #define NFOC_ZALORG                    (*(volatile  int16* )(NFOC_BASE + ( 190*2)))    // RV:0000H 估算反电动势      /* factory */
 #define NFOC_ZBEORG                    (*(volatile  int16* )(NFOC_BASE + ( 191*2)))    // RV:0000H 估算反电动势      /* factory */
 #define NFOC_EMF                       (*(volatile  int16* )(NFOC_BASE + ( 240*2)))    // RV:0000H EALPHA和EBETA计算幅值（平方和后开方），即估算反电动势幅值
 #define NFOC_ATHETA                    (*(volatile  int16* )(NFOC_BASE + ( 241*2)))    // RV:0000H EALPHA和EBETA计算角度      /* factory */
 #define NFOC_OMECLI                    (*(volatile  int32* )(NFOC_BASE + ( 256*2)))    // RV:0000H Omega启动的实时值（32位）      /* factory */
 #define NFOC_OMECLIL                   (*(volatile  int16* )(NFOC_BASE + ( 256*2)))    // RV:0000H Omega启动的实时值低16位      /* factory */
 #define NFOC_OMECLIH                   (*(volatile  int16* )(NFOC_BASE + ( 257*2)))    // RV:0000H Omega启动的实时值高16位      /* factory */
 #define NFOC_OMEGA                     (*(volatile  int16* )(NFOC_BASE + ( 258*2)))    // RV:0000H 估算OMEGA
   
 #define NFOC_IESTA                     (*(volatile  int16* )(NFOC_BASE + ( 260*2)))    // RV:0000H 估算电流IALPHA
 #define NFOC_IESTB                     (*(volatile  int16* )(NFOC_BASE + ( 261*2)))    // RV:0000H 估算电流IBETA
 #define NFOC_OMEFLT                    (*(volatile  int32* )(NFOC_BASE + ( 262*2)))    // RV:0000H OMEGA一级滤波值（32位）
 #define NFOC_OMEFLTH                   (*(volatile  int16* )(NFOC_BASE + ( 263*2)))    // RV:0000H OMEGA一级滤波值高16位
 #define NFOC_OMEFL2                    (*(volatile  int32* )(NFOC_BASE + ( 264*2)))    // RV:0000H OMEGA二级滤波值（32位）
 #define NFOC_OMEFL2H                   (*(volatile  int16* )(NFOC_BASE + ( 265*2)))    // RV:0000H OMEGA二级滤波值高16位
 #define NFOC_ZALPHA                    (*(volatile  int16* )(NFOC_BASE + ( 266*2)))    // RV:0000H 滤波前的估算反电动势      /* factory */
 #define NFOC_ZBETA                     (*(volatile  int16* )(NFOC_BASE + ( 267*2)))    // RV:0000H 滤波前的估算反电动势      /* factory */
 #define NFOC_KLPF                      (*(volatile  int16* )(NFOC_BASE + ( 268*2)))    // RV:0000H 估算器的低通滤波器系数
 #define NFOC_UDFIN                     (*(volatile  int16* )(NFOC_BASE + ( 270*2)))    // RV:0000H UD最终值
 #define NFOC_UQFIN                     (*(volatile  int16* )(NFOC_BASE + ( 271*2)))    // RV:0000H UQ最终值
 #define NFOC_UALPHA                    (*(volatile  int16* )(NFOC_BASE + ( 272*2)))    // RV:0000H UALPHA
 #define NFOC_UBETA                     (*(volatile  int16* )(NFOC_BASE + ( 273*2)))    // RV:0000H UBETA
 #define NFOC_UALORG                    (*(volatile  int16* )(NFOC_BASE + ( 140*2)))    // RV:0000H UALORG
 #define NFOC_UBEORG                    (*(volatile  int16* )(NFOC_BASE + ( 141*2)))    // RV:0000H UBEORG
 #define NFOC_Y                         (*(volatile  int16* )(NFOC_BASE + ( 274*2)))    // RV:0000H SVPWM计算中间值      /* factory */
 #define NFOC_Z                         (*(volatile  int16* )(NFOC_BASE + ( 275*2)))    // RV:0000H SVPWM计算中间值      /* factory */

 #define NFOC_T1ORG                     (*(volatile  int16* )(NFOC_BASE + (450*2)))     // RV:0000H SVPWM计算中间值      /* factory */
 #define NFOC_T2ORG                     (*(volatile  int16* )(NFOC_BASE + (451*2)))     // RV:0000H SVPWM计算中间值      /* factory */
 #define NFOC_T1RC                      (*(volatile  int16* )(NFOC_BASE + (452*2)))     // RV:0000H SVPWM计算中间值      /* factory */
 #define NFOC_T2RC                      (*(volatile  int16* )(NFOC_BASE + (453*2)))     // RV:0000H SVPWM计算中间值      /* factory */
 #define NFOC_OMUNIT                    (*(volatile  int16* )(NFOC_BASE + (454*2)))     // RV:0000H 过调制放大系数
 #define NFOC_TC                        (*(volatile  int16* )(NFOC_BASE + (456*2)))     // RV:0000H SVPWM计算中间值      /* factory */
 #define NFOC_TB                        (*(volatile  int16* )(NFOC_BASE + (457*2)))     // RV:0000H SVPWM计算中间值      /* factory */
 #define NFOC_TA                        (*(volatile  int16* )(NFOC_BASE + (458*2)))     // RV:0000H SVPWM计算中间值      /* factory */
 #define NFOC_DLYCNT                    (*(volatile  uint16* )(NFOC_BASE  + (459*2)))    // RV:0000H dly_en功能延迟的clk数
 #define NFOC_TAON                      (*(volatile  int16* )(NFOC_BASE + (460*2)))     // RV:0000H SVPWM计算中间值      /* factory */
 #define NFOC_TAOND                     (*(volatile  int16* )(NFOC_BASE + (461*2)))     // RV:0000H SVPWM计算中间值      /* factory */
 #define NFOC_TBON                      (*(volatile  int16* )(NFOC_BASE + (462*2)))     // RV:0000H SVPWM计算中间值      /* factory */
 #define NFOC_TBOND                     (*(volatile  int16* )(NFOC_BASE + (463*2)))     // RV:0000H SVPWM计算中间值      /* factory */
 #define NFOC_TCON                      (*(volatile  int16* )(NFOC_BASE + (464*2)))     // RV:0000H SVPWM计算中间值      /* factory */
 #define NFOC_TCOND                     (*(volatile  int16* )(NFOC_BASE + (465*2)))     // RV:0000H SVPWM计算中间值      /* factory */
 #define NFOC_TADTC                     (*(volatile  int16* )(NFOC_BASE + (466*2)))     // RV:0000H SVPWM计算中间值      /* factory */
 #define NFOC_TADTCD                    (*(volatile  int16* )(NFOC_BASE + (467*2)))     // RV:0000H SVPWM计算中间值      /* factory */
 #define NFOC_TBDTC                     (*(volatile  int16* )(NFOC_BASE + (468*2)))     // RV:0000H SVPWM计算中间值      /* factory */
 #define NFOC_TBDTCD                    (*(volatile  int16* )(NFOC_BASE + (469*2)))     // RV:0000H SVPWM计算中间值      /* factory */
 #define NFOC_TCDTC                     (*(volatile  int16* )(NFOC_BASE + (470*2)))     // RV:0000H SVPWM计算中间值      /* factory */
 #define NFOC_TCDTCD                    (*(volatile  int16* )(NFOC_BASE + (471*2)))     // RV:0000H SVPWM计算中间值      /* factory */

 #define NFOC_DR1                       (*(volatile uint16* )(NFOC_BASE + ( 70*2)))     // RV:0000H SVPWM计算中间值      /* factory */
 #define NFOC_DR1N                      (*(volatile uint16* )(NFOC_BASE + ( 71*2)))     // RV:0000H SVPWM计算中间值      /* factory */
 #define NFOC_DR2                       (*(volatile uint16* )(NFOC_BASE + ( 72*2)))     // RV:0000H SVPWM计算中间值      /* factory */
 #define NFOC_DR2N                      (*(volatile uint16* )(NFOC_BASE + ( 73*2)))     // RV:0000H SVPWM计算中间值      /* factory */
 #define NFOC_DR3                       (*(volatile uint16* )(NFOC_BASE + ( 74*2)))     // RV:0000H SVPWM计算中间值      /* factory */
 #define NFOC_DR3N                      (*(volatile uint16* )(NFOC_BASE + ( 75*2)))     // RV:0000H SVPWM计算中间值      /* factory */
 #define NFOC_DRA                       (*(volatile uint16* )(NFOC_BASE + ( 76*2)))     // RV:0000H SVPWM装载到DRV的值      /* factory */
 #define NFOC_DRAN                      (*(volatile uint16* )(NFOC_BASE + ( 77*2)))     // RV:0000H SVPWM装载到DRV的值      /* factory */
 #define NFOC_DRB                       (*(volatile uint16* )(NFOC_BASE + ( 78*2)))     // RV:0000H SVPWM装载到DRV的值      /* factory */
 #define NFOC_DRBN                      (*(volatile uint16* )(NFOC_BASE + ( 79*2)))     // RV:0000H SVPWM装载到DRV的值      /* factory */
 #define NFOC_DRC                       (*(volatile uint16* )(NFOC_BASE + ( 80*2)))     // RV:0000H SVPWM装载到DRV的值      /* factory */
 #define NFOC_DRCN                      (*(volatile uint16* )(NFOC_BASE + ( 81*2)))     // RV:0000H SVPWM装载到DRV的值      /* factory */
 #define NFOC_UDCALP                    (*(volatile  int16* )(NFOC_BASE + ( 82*2)))     // RV:0000H UDC*UALPHA
 #define NFOC_UDCBET                    (*(volatile  int16* )(NFOC_BASE + ( 83*2)))     // RV:0000H UDC*UBETA
 #define NFOC_MAY1                      (*(volatile  int16* )(NFOC_BASE + ( 84*2)))     // RV:0000H AO观测器相关信号      /* factory */
 #define NFOC_MBY1                      (*(volatile  int16* )(NFOC_BASE + ( 85*2)))     // RV:0000H AO观测器相关信号      /* factory */
 #define NFOC_MAY2                      (*(volatile  int16* )(NFOC_BASE + ( 86*2)))     // RV:0000H AO观测器相关信号      /* factory */
 #define NFOC_MBY2                      (*(volatile  int16* )(NFOC_BASE + ( 87*2)))     // RV:0000H AO观测器相关信号      /* factory */
 #define NFOC_MAY3                      (*(volatile  int16* )(NFOC_BASE + ( 88*2)))     // RV:0000H AO观测器相关信号      /* factory */
 #define NFOC_MBY3                      (*(volatile  int16* )(NFOC_BASE + ( 89*2)))     // RV:0000H AO观测器相关信号      /* factory */
 #define NFOC_MAY4                      (*(volatile  int16* )(NFOC_BASE + ( 90*2)))     // RV:0000H AO观测器相关信号      /* factory */
 #define NFOC_MBY4                      (*(volatile  int16* )(NFOC_BASE + ( 91*2)))     // RV:0000H AO观测器相关信号      /* factory */
 #define NFOC_MAY5                      (*(volatile  int16* )(NFOC_BASE + ( 92*2)))     // RV:0000H AO观测器相关信号      /* factory */
 #define NFOC_MBY5                      (*(volatile  int16* )(NFOC_BASE + ( 93*2)))     // RV:0000H AO观测器相关信号      /* factory */
 #define NFOC_MAU1                      (*(volatile  int16* )(NFOC_BASE + ( 94*2)))     // RV:0000H AO观测器相关信号      /* factory */
 #define NFOC_MBU1                      (*(volatile  int16* )(NFOC_BASE + ( 95*2)))     // RV:0000H AO观测器相关信号      /* factory */
 #define NFOC_MAU2                      (*(volatile  int16* )(NFOC_BASE + ( 96*2)))     // RV:0000H AO观测器相关信号      /* factory */
 #define NFOC_MBU2                      (*(volatile  int16* )(NFOC_BASE + ( 97*2)))     // RV:0000H AO观测器相关信号      /* factory */
 #define NFOC_MAU3                      (*(volatile  int16* )(NFOC_BASE + ( 98*2)))     // RV:0000H AO观测器相关信号      /* factory */
 #define NFOC_MBU3                      (*(volatile  int16* )(NFOC_BASE + ( 99*2)))     // RV:0000H AO观测器相关信号      /* factory */
 #define NFOC_MAU4                      (*(volatile  int16* )(NFOC_BASE + (100*2)))     // RV:0000H AO观测器相关信号      /* factory */
 #define NFOC_MBU4                      (*(volatile  int16* )(NFOC_BASE + (101*2)))     // RV:0000H AO观测器相关信号      /* factory */
    
 #define NFOC_FTCPS                     (*(volatile  int16* )(NFOC_BASE + (102*2)))     // RV:0000H 计算得到的动态补偿角FTCPS = FTCK*OMEFL2*FBASE
 #define NFOC_FTHETA                    (*(volatile  int16* )(NFOC_BASE + (103*2)))     // RV:0000H Feedback给估算器PI的角度
 #define NFOC_IS                        (*(volatile  int16* )(NFOC_BASE + (104*2)))     // RV:0000H IALPHA和IBETA计算幅值（平方和后开方）
 #define NFOC_ITHETA                    (*(volatile  int16* )(NFOC_BASE + (105*2)))     // RV:0000H IALPHA和IBETA计算角度
 #define NFOC_ITFLT                     (*(volatile  int32* )(NFOC_BASE + (106*2)))     // RV:0000H ITRIP滤波后的值（32位）
 #define NFOC_ITFLTH                    (*(volatile  int16* )(NFOC_BASE + (107*2)))     // RV:0000H ITRIP滤波后的值高16位
 #define NFOC_ITRIP                     (*(volatile  int16* )(NFOC_BASE + (108*2)))     // RV:0000H 采样ITRIP，用于功率计算
 #define NFOC_POWER                     (*(volatile  int16* )(NFOC_BASE + (109*2)))     // RV:0000H 功率值
 #define NFOC_US                        (*(volatile  int16* )(NFOC_BASE + (110*2)))     // RV:0000H UALPHA和UBETA计算幅值（平方和后开方）
 #define NFOC_UTHETA                    (*(volatile  int16* )(NFOC_BASE + (111*2)))     // RV:0000H UALPHA和UBETA计算角度
 
 #define NFOC_ID0                       (*(volatile  int16* )(NFOC_BASE + (122*2)))     // RV:0000H 上一次FOC计算的D轴电流
 #define NFOC_IQ0                       (*(volatile  int16* )(NFOC_BASE + (123*2)))     // RV:0000H 上一次FOC计算的Q轴电流
 #define NFOC_DELIAL                    (*(volatile  int16* )(NFOC_BASE + (124*2)))     // RV:0000H 高频电流      /* factory */
 #define NFOC_DELIBE                    (*(volatile  int16* )(NFOC_BASE + (125*2)))     // RV:0000H 高频电流      /* factory */
 #define NFOC_HALPHA                    (*(volatile  int16* )(NFOC_BASE + (126*2)))     // RV:0000H 高频电流包络
 #define NFOC_HBETA                     (*(volatile  int16* )(NFOC_BASE + (127*2)))     // RV:0000H 高频电流包络
 #define NFOC_HS                        (*(volatile  int16* )(NFOC_BASE + (138*2)))     // RV:0000H HALPHA和HBETA计算幅值（平方和后开方）      /* factory */
 #define NFOC_HTHETA                    (*(volatile  int16* )(NFOC_BASE + (139*2)))     // RV:0000H HALPHA和HBETA计算角度      /* factory */
 #define NFOC_DELIQ                     (*(volatile  int16* )(NFOC_BASE + (142*2)))     // RV:0000H 高频注入计算中间值
    
 #define NFOC_HKP                       (*(volatile  int16* )(NFOC_BASE + (112*2)))     // RV:0000H 高频注入PI KP
 #define NFOC_HKI                       (*(volatile  int16* )(NFOC_BASE + (113*2)))     // RV:0000H 高频注入PI KI
 #define NFOC_HMAX                      (*(volatile  int16* )(NFOC_BASE + (114*2)))     // RV:0000H 高频注入PI 上限值
 #define NFOC_HMIN                      (*(volatile  int16* )(NFOC_BASE + (115*2)))     // RV:0000H 高频注入PI 下限值
 #define NFOC_HEK                       (*(volatile  int16* )(NFOC_BASE + (116*2)))     // RV:0000H 高频注入PI EK
 #define NFOC_HEK1                      (*(volatile  int16* )(NFOC_BASE + (117*2)))     // RV:0000H 高频注入PI EK1
 #define NFOC_HUK                       (*(volatile  int32* )(NFOC_BASE + (118*2)))     // RV:0000H 高频注入PI UK（32位）
 #define NFOC_HUKH                      (*(volatile  int16* )(NFOC_BASE + (119*2)))     // RV:0000H 高频注入PI UK高16位
 // #define NFOC_HEXC                      (*(volatile  int16* )(NFOC_BASE + (120*2))   )  // RV:0000H 高频注入PI UK溢出值
    
 #define NFOC_DKP                       (*(volatile  int16* )(NFOC_BASE + (128*2)))     // RV:0000H D轴PI电流环KP
 #define NFOC_DKI                       (*(volatile  int16* )(NFOC_BASE + (129*2)))     // RV:0000H D轴PI电流环KI
 #define NFOC_DMAX                      (*(volatile  int16* )(NFOC_BASE + (130*2)))     // RV:0000H D轴PI电流环上限值
 #define NFOC_DMIN                      (*(volatile  int16* )(NFOC_BASE + (131*2)))     // RV:0000H D轴PI电流环下限值
 #define NFOC_DEK                       (*(volatile  int16* )(NFOC_BASE + (132*2)))     // RV:0000H D轴PI电流环EK
 #define NFOC_DEK1                      (*(volatile  int16* )(NFOC_BASE + (133*2)))     // RV:0000H D轴PI电流环EK1
 #define NFOC_DUK                       (*(volatile  int32* )(NFOC_BASE + (134*2)))     // RV:0000H D轴PI电流环UK（32位）//低16位为复矢量Ukfin - uklimit
 #define NFOC_DUKH                      (*(volatile  int16* )(NFOC_BASE + (135*2)))     // RV:0000H D轴PI电流环UK高16位/复矢量UKLIMIT
 #define NFOC_CVDUK                     (*(volatile  int16* )(NFOC_BASE + (136*2)))     // RV:0000H 复矢量解耦系数D轴UK
 #define NFOC_CVKI2D                    (*(volatile  int16* )(NFOC_BASE + (137*2)))     // RV:0000H 复矢量解耦系数D轴KI2
 // #define NFOC_DEXC                      (*(volatile  int16* )(NFOC_BASE + (136*2)))  // RV:0000H D轴PI电流环UK溢出值
 
 #define NFOC_QKP                       (*(volatile  int16* )(NFOC_BASE + (144*2)))     // RV:0000H Q轴PI电流环KP
 #define NFOC_QKI                       (*(volatile  int16* )(NFOC_BASE + (145*2)))     // RV:0000H Q轴PI电流环KI
 #define NFOC_QMAX                      (*(volatile  int16* )(NFOC_BASE + (146*2)))     // RV:0000H Q轴PI电流环上限值
 #define NFOC_QMIN                      (*(volatile  int16* )(NFOC_BASE + (147*2)))     // RV:0000H Q轴PI电流环下限值
 #define NFOC_QEK                       (*(volatile  int16* )(NFOC_BASE + (148*2)))     // RV:0000H Q轴PI电流环EK
 #define NFOC_QEK1                      (*(volatile  int16* )(NFOC_BASE + (149*2)))     // RV:0000H Q轴PI电流环EK1
 #define NFOC_QUK                       (*(volatile  int32* )(NFOC_BASE + (150*2)))     // RV:0000H Q轴PI电流环UK（32位）/低16位为复矢量Ukfin - uklimit
 #define NFOC_QUKH                      (*(volatile  int16* )(NFOC_BASE + (151*2)))     // RV:0000H Q轴PI电流环UK高16位/复矢量UKLIMIT
 #define NFOC_CVQUK                     (*(volatile  int16* )(NFOC_BASE + (152*2)))     // RV:0000H 复矢量解耦系数q轴UK
 #define NFOC_CVKI2Q                    (*(volatile  int16* )(NFOC_BASE + (153*2)))     // RV:0000H 复矢量解耦系数Q轴KI2
 // #define NFOC_QEXC                      (*(volatile  int16* )(NFOC_BASE + (152*2)))  // RV:0000H Q轴PI电流环UK溢出值

 #define NFOC_CVK1                      (*(volatile  int16* )(NFOC_BASE + (486*2)))     // RV:0000H 复矢量解耦系数
 #define NFOC_CVK2                      (*(volatile  int16* )(NFOC_BASE + (496*2)))     // RV:0000H 复矢量解耦系数
 #define NFOC_CVK3                      (*(volatile  int16* )(NFOC_BASE + (487*2)))     // RV:0000H 复矢量解耦系数
 #define NFOC_CVDK4                     (*(volatile  int16* )(NFOC_BASE + (488*2)))     // RV:0000H 复矢量解耦系数
 #define NFOC_CVQK4                     (*(volatile  int16* )(NFOC_BASE + (489*2)))     // RV:0000H 复矢量解耦系数
 #define NFOC_CVDK5                     (*(volatile  int16* )(NFOC_BASE + (490*2)))     // RV:0000H 复矢量解耦系数
 #define NFOC_CVQK5                     (*(volatile  int16* )(NFOC_BASE + (491*2)))     // RV:0000H 复矢量解耦系数
 #define NFOC_UDCOM                     (*(volatile  int16* )(NFOC_BASE + (492*2)))     // RV:0000H 复矢量解耦系数
 #define NFOC_UDAS                      (*(volatile  int16* )(NFOC_BASE + (493*2)))     // RV:0000H 复矢量解耦系数
 #define NFOC_UQCOM                     (*(volatile  int16* )(NFOC_BASE + (494*2)))     // RV:0000H 复矢量解耦系数
 #define NFOC_UQAS                      (*(volatile  int16* )(NFOC_BASE + (495*2)))     // RV:0000H 复矢量解耦系数
 #define NFOC_UDCLIM                    (*(volatile  int16* )(NFOC_BASE + (497*2)))     // RV:0000H 复矢量解耦系数
 #define NFOC_UDCMAX                    (*(volatile  int16* )(NFOC_BASE + (498 *2)))     // RV:0000H 复矢量解耦系数
 #define NFOC_UDCMIN                    (*(volatile  int16* )(NFOC_BASE + (499 *2)))     // RV:0000H 复矢量解耦系数
 #define NFOC_CVDULO                    (*(volatile  int16* )(NFOC_BASE + (385 *2)))     // RV:0000H 复矢量解耦系数
 #define NFOC_CVQULO                    (*(volatile  int16* )(NFOC_BASE + (405 *2)))     // RV:0000H 复矢量解耦系数
 #define NFOC_DUKF                      (*(volatile  int16* )(NFOC_BASE + (506 *2)))     // RV:0000H 复矢量解耦系数
 #define NFOC_QUKF                      (*(volatile  int16* )(NFOC_BASE + (507 *2)))     // RV:0000H 复矢量解耦系数

 
 #define NFOC_IRLOW                     (*(volatile  int16* )(NFOC_BASE + (8*2)))       // RV:0000H 电流基准下限，超出后报基准异常
 #define NFOC_IRUPP                     (*(volatile  int16* )(NFOC_BASE + (9*2)))       // RV:0000H 电流基准上限，超出后报基准异常
 
 #define NFOC_EKP                       (*(volatile  int16* )(NFOC_BASE + (160*2)))     // RV:0000H 估算器PI电流环KP
 #define NFOC_EKI                       (*(volatile  int16* )(NFOC_BASE + (161*2)))     // RV:0000H 估算器PI电流环KI
 #define NFOC_EMAX                      (*(volatile  int16* )(NFOC_BASE + (162*2)))     // RV:0000H 估算器PI电流环上限值
 #define NFOC_EMIN                      (*(volatile  int16* )(NFOC_BASE + (163*2)))     // RV:0000H 估算器PI电流环下限值
 #define NFOC_EEK                       (*(volatile  int16* )(NFOC_BASE + (164*2)))     // RV:0000H 估算器PI电流环EK
 #define NFOC_EEK1                      (*(volatile  int16* )(NFOC_BASE + (165*2)))     // RV:0000H 估算器PI电流环EK1
 #define NFOC_EUK                       (*(volatile  int32* )(NFOC_BASE + (166*2)))     // RV:0000H 估算器PI电流环UK（32位）
 #define NFOC_EUKH                      (*(volatile  int16* )(NFOC_BASE + (167*2)))     // RV:0000H 估算器PI电流环UK高16位
 // #define NFOC_EEXC                      (*(volatile  int16* )(NFOC_BASE + (168*2)))  // RV:0000H 估算器PI电流环UK溢出值

 #define NFOC_WKP                       (*(volatile  int16* )(NFOC_BASE + (176*2)))     // RV:0000H 外环PI电流环KP
 #define NFOC_WKI                       (*(volatile  int16* )(NFOC_BASE + (177*2)))     // RV:0000H 外环PI电流环KI
 #define NFOC_WMAX                      (*(volatile  int16* )(NFOC_BASE + (178*2)))     // RV:0000H 外环PI电流环上限值
 #define NFOC_WMIN                      (*(volatile  int16* )(NFOC_BASE + (179*2)))     // RV:0000H 外环PI电流环下限值
 #define NFOC_WEK                       (*(volatile  int16* )(NFOC_BASE + (180*2)))     // RV:0000H 外环PI电流环EK
 #define NFOC_WEK1                      (*(volatile  int16* )(NFOC_BASE + (181*2)))     // RV:0000H 外环PI电流环EK1
 #define NFOC_WUK                       (*(volatile  int32* )(NFOC_BASE + (182*2)))     // RV:0000H 外环PI电流环UK（32位）
 #define NFOC_WUKH                      (*(volatile  int16* )(NFOC_BASE + (183*2)))     // RV:0000H 外环PI电流环UK高16位
 // #define NFOC_WEXC                      (*(volatile  int16* )(NFOC_BASE + (184*2)))  // RV:0000H 外环PI电流环UK溢出值
 
 #define NFOC_FWKP                      (*(volatile  int16* )(NFOC_BASE + (192*2)))     // RV:0000H 弱磁PI KP
 #define NFOC_FWKI                      (*(volatile  int16* )(NFOC_BASE + (193*2)))     // RV:0000H 弱磁PI KI
 #define NFOC_FWMAX                     (*(volatile  int16* )(NFOC_BASE + (194*2)))     // RV:0000H 弱磁PI 上限值
 #define NFOC_FWMIN                     (*(volatile  int16* )(NFOC_BASE + (195*2)))     // RV:0000H 弱磁PI 下限值
 #define NFOC_FWEK                      (*(volatile  int16* )(NFOC_BASE + (196*2)))     // RV:0000H 弱磁PI EK
 #define NFOC_FWEK1                     (*(volatile  int16* )(NFOC_BASE + (197*2)))     // RV:0000H 弱磁PI EK1
 #define NFOC_FWUK                      (*(volatile  int32* )(NFOC_BASE + (198*2)))     // RV:0000H 弱磁PI UK（32位）
 #define NFOC_FWUKH                     (*(volatile  int16* )(NFOC_BASE + (199*2)))     // RV:0000H 弱磁PI UK高16位
 #define NFOC_FWEXC                     (*(volatile  int16* )(NFOC_BASE + (200*2)))     // RV:0000H 弱磁PI UK溢出值
 #define NFOC_KUSF                      (*(volatile  int16* )(NFOC_BASE + (201*2)))     // RV:0000H 弱磁计算中US的滤波系数

     
 #define NFOC_OVP                       (*(volatile  int16* )(NFOC_BASE + (10*2)))      // RV:0000H 过压阈值
 #define NFOC_OVPARR                    (*(volatile uint8*  )(NFOC_BASE + (11*2)))      // RV:00H   过压次数目标值（8位）
 #define NFOC_OVPCNT                    (*(volatile uint8*  )(NFOC_BASE + (11*2+1)))    // RV:00H   过压次数计数值（8位）
 #define NFOC_UVP                       (*(volatile  int16* )(NFOC_BASE + (12*2)))      // RV:0000H 欠压阈值
 #define NFOC_UVPARR                    (*(volatile uint8*  )(NFOC_BASE + (13*2)))      // RV:00H   欠压次数目标值（8位）
 #define NFOC_UVPCNT                    (*(volatile uint8*  )(NFOC_BASE + (13*2+1)))    // RV:00H   欠压次数计数值（8位）
 #define NFOC_SOCP                      (*(volatile  int16* )(NFOC_BASE + (14*2)))      // RV:0000H 软件过流阈值
 #define NFOC_SOCPARR                   (*(volatile uint8*  )(NFOC_BASE + (15*2)))      // RV:00H   软件过流次数目标值（8位）
 #define NFOC_SOCPCNT                   (*(volatile uint8*  )(NFOC_BASE + (15*2+1)))    // RV:00H   软件过流次数计数值（8位）

 #define NFOC_LKSMIN                    (*(volatile  int16* )(NFOC_BASE + (16*2)))      // RV:0000H LOCK0对应的最小堵转速度
 #define NFOC_LKSMAX                    (*(volatile  int16* )(NFOC_BASE + (17*2)))      // RV:0000H LOCK1对应的最大堵转速度
 #define NFOC_LOCKK                     (*(volatile  int16* )(NFOC_BASE + (18*2)))      // RV:0000H LOCK2对应的速度和EMF的倍数Q8格式
 #define NFOC_LKARR                     (*(volatile uint16* )(NFOC_BASE + (20*2)))      // RV:0000H 堵转次数目标值
 #define NFOC_LKCNT                     (*(volatile uint16* )(NFOC_BASE + (21*2)))      // RV:0000H 堵转次数计数值，3者共用，一次判断3个都成立只+1

 //伺服堵转检测寄存器，跟原堵转寄存器复用
 #define NFOC_LKSTH						(*(volatile  int16* )(NFOC_BASE + (16*2)))      // RV:0000H 堵转速度阈值，复用NFOC_LKSMIN
 #define NFOC_LKITH                     (*(volatile  int16* )(NFOC_BASE + (17*2)))      // RV:0000H 堵转电流阈值，复用NFOC_LKSMAX

 #define NFOC_NCURR                     (*(volatile  int16* )(NFOC_BASE + (22*2)))      // RV:0000H 缺相检测电流设置
 #define NFOC_PLK                       (*(volatile  int16* )(NFOC_BASE + (23*2)))      // RV:0000H 缺相检测电流倍数系数

 #define NFOC_OVEL                      (*(volatile  int16* )(NFOC_BASE + (62*2)))      // RV:0000H 速度超差保护阈值
 #define NFOC_OVELARR                   (*(volatile uint8*  )(NFOC_BASE + (63*2)))      // RV:00H   速度超差保护次数目标值（8位）
 #define NFOC_OVELCNT                   (*(volatile uint8*  )(NFOC_BASE + (63*2+1)))    // RV:00H   速度超差保护次数计数值（8位）

 #define NFOC_OSPD						(*(volatile  int16* )(NFOC_BASE + (64*2)))      // RV:0000H 速度过超保护阈值
 #define NFOC_OSPDARR                   (*(volatile uint8*  )(NFOC_BASE + (65*2)))      // RV:00H   速度过超保护次数目标值（8位）
 #define NFOC_OSPDCNT                   (*(volatile uint8*  )(NFOC_BASE + (65*2+1)))    // RV:00H   速度过超保护次数计数值（8位）

 #define NFOC_PLTTH                     (*(volatile  int16* )(NFOC_BASE + (19*2)))      // RV:0000H 新缺相保护角度变化阈值
 #define NFOC_PLTHE0                    (*(volatile  int16* )(NFOC_BASE + (22*2)))      // RV:0000H 新缺相保护前一次的角度
 #define NFOC_PLTHEM					(*(volatile  int16* )(NFOC_BASE + (23*2)))      // RV:0000H 新缺相保护角度过零计数
 #define NFOC_PLRTH						(*(volatile  int16* )(NFOC_BASE + (66*2)))      // RV:0000H 新缺相保护电流命令阈值
 #define NFOC_PLITH                     (*(volatile  int16* )(NFOC_BASE + (67*2)))      // RV:0000H 新缺相保护相电流阈值
 #define NFOC_PLTHE1                    (*(volatile  int16* )(NFOC_BASE + (68*2)))      // RV:0000H 新缺相保护角度缓存值（32位）
 
 
 #define NFOC_TS                        (*(volatile  int16* )(NFOC_BASE + (316*2)))     // RV:0000H 单电阻移相/双/三电阻最小采样脉宽[0,32767]
 #define NFOC_NTS                       (*(volatile  int16* )(NFOC_BASE + (317*2)))     // RV:0000H 三电阻脉宽屏蔽/新单电阻最小脉宽[0,1023]
 #define NFOC_TDLY                      (*(volatile  int16* )(NFOC_BASE + (318*2)))     // RV:0000H 电流采样触发时机
 #define NFOC_TDLYD                     (*(volatile  int16* )(NFOC_BASE + (319*2)))     // RV:0000H 单电阻动态前后采样时机
 #define NFOC_ARR                       (*(volatile uint16* )(NFOC_BASE + (320*2)))     // RV:0000H FOC载波频率
 #define NFOC_IDK                       (*(volatile  int16* )(NFOC_BASE + (322*2)))     // RV:0000H ID滤波系数
 #define NFOC_IQK                       (*(volatile  int16* )(NFOC_BASE + (323*2)))     // RV:0000H IQ滤波系数
 #define NFOC_OMEGAK                    (*(volatile  int16* )(NFOC_BASE + (324*2)))     // RV:0000H Omega一级滤波系数
 #define NFOC_OMEK2                     (*(volatile  int16* )(NFOC_BASE + (325*2)))     // RV:0000H Omega二级滤波系数
 #define NFOC_OMEACC                    (*(volatile  int32* )(NFOC_BASE + (202*2)))     // RV:0000H OMEGA启动速度增量
 #define NFOC_OMEEND                    (*(volatile  int32* )(NFOC_BASE + (204*2)))     // RV:0000H OMEGA启动END值
 #define NFOC_OMEENDH                   (*(volatile  int16* )(NFOC_BASE + (205*2)))     // RV:0000H OMEGA启动END值
 #define NFOC_OMEMIN                    (*(volatile  int16* )(NFOC_BASE + (206*2)))     // RV:0000H OMEGA启动切换值
 #define NFOC_FTCK                      (*(volatile  int16* )(NFOC_BASE + (207*2)))     // RV:0000H 反馈角度动态补偿系数
 #define NFOC_FBASE                     (*(volatile  int16* )(NFOC_BASE + (208*2)))     // RV:0000H 速度基准
 #define NFOC_OMEMI2                    (*(volatile  int16* )(NFOC_BASE + (209*2)))     // RV:0000H KLPF对应的最小速度
 #define NFOC_THECOM                    (*(volatile  int16* )(NFOC_BASE + (210*2)))     // RV:0000H 输出角度的静态补偿角
 #define NFOC_FTCOM                     (*(volatile  int16* )(NFOC_BASE + (211*2)))     // RV:0000H 反馈角度的静态补偿角
 #define NFOC_EK1                       (*(volatile  int16* )(NFOC_BASE + (212*2)))     // RV:0000H FOC估算器参数1
 #define NFOC_EK2                       (*(volatile  int16* )(NFOC_BASE + (213*2)))     // RV:0000H FOC估算器参数2
 #define NFOC_EK3                       (*(volatile  int16* )(NFOC_BASE + (214*2)))     // RV:0000H FOC估算器参数3
 #define NFOC_EK4                       (*(volatile  int16* )(NFOC_BASE + (215*2)))     // RV:0000H FOC估算器参数4
 #define NFOC_KSLIDE                    (*(volatile  int16* )(NFOC_BASE + (216*2)))     // RV:0000H SMO系数
 #define NFOC_MAXERR                    (*(volatile  int16* )(NFOC_BASE + (217*2)))     // RV:0000H SMO限幅
 #define NFOC_MERRRE                    (*(volatile  int16* )(NFOC_BASE + (218*2)))     // RV:0000H SMO限幅倒数
 #define NFOC_TDTC                      (*(volatile  int16* )(NFOC_BASE + (219*2)))     // RV:0000H 双/三电阻死区补偿
 #define NFOC_IDREF                     (*(volatile  int16* )(NFOC_BASE + (220*2)))     // RV:0000H 给定D轴值
 #define NFOC_IQREF                     (*(volatile  int16* )(NFOC_BASE + (221*2)))     // RV:0000H 给定Q轴值
 #define NFOC_IAREF                     (*(volatile  int16* )(NFOC_BASE + (4*2)))       // RV:0000H U相电流基准
 #define NFOC_IBREF                     (*(volatile  int16* )(NFOC_BASE + (5*2)))       // RV:0000H V相电流基准
 #define NFOC_ICREF                     (*(volatile  int16* )(NFOC_BASE + (6*2)))       // RV:0000H W相电流基准
 #define NFOC_ITREF                     (*(volatile  int16* )(NFOC_BASE + (7*2)))       // RV:0000H 母线电流基准
 #define NFOC_UDC                       (*(volatile  int16* )(NFOC_BASE + (0*2)))       // RV:0000H 母线电压采样值
 #define NFOC_UDCK                      (*(volatile  int16* )(NFOC_BASE + (1*2)))       // RV:0000H 母线电压采样滤波系数
 #define NFOC_UDCFLT                    (*(volatile  int32* )(NFOC_BASE + (2*2)))       // RV:0000H 母线电压滤波后的值（32位）
 #define NFOC_UDCFLTH                   (*(volatile  int16* )(NFOC_BASE + (3*2)))       // RV:0000H 母线电压滤波后的值高16位
 #define NFOC_UQCPS                     (*(volatile  int16* )(NFOC_BASE + (231*2)))     // RV:0000H D轴的电压补偿值
 #define NFOC_UDCPS                     (*(volatile  int16* )(NFOC_BASE + (230*2)))     // RV:0000H Q轴的电压补偿值
 #define NFOC_WREF                      (*(volatile  int16* )(NFOC_BASE + (232*2)))     // RV:0000H 外环参考值[0~32767]
 #define NFOC_WFDB                      (*(volatile  int16* )(NFOC_BASE + (233*2)))     // RV:0000H 外环反馈值
 #define NFOC_ITK                       (*(volatile  int16* )(NFOC_BASE + (234*2)))     // RV:0000H ITRIP滤波系数
 #define NFOC_POWK                      (*(volatile  int16* )(NFOC_BASE + (235*2)))     // RV:0000H POWER滤波系数（两个8位）POWER = (ITRIP*K1)*(UDC*K2)
 #define NFOC_FGBASE                    (*(volatile  int16* )(NFOC_BASE + (236*2)))     // RV:0000H FG计算速度基准
 
 #define NFOC_UALCPS                    (*(volatile  int16* )(NFOC_BASE + (238*2)))     // RV:0000H UALPHA的电压补偿值
 #define NFOC_UBECPS                    (*(volatile  int16* )(NFOC_BASE + (239*2)))     // RV:0000H UBETA的电压补偿值
 
 #define NFOC_RATAR                     (*(volatile  int16* )(NFOC_BASE + (242*2)))     // RV:0000H 用户填入的爬坡目标值
 #define NFOC_RAOUT                     (*(volatile  int16* )(NFOC_BASE + (243*2)))     // RV:0000H 爬坡后的输出值
 #define NFOC_RAINC                     (*(volatile  int16* )(NFOC_BASE + (244*2)))     // RV:0000H 向上增加的步进值
 #define NFOC_RADEC                     (*(volatile  int16* )(NFOC_BASE + (245*2)))     // RV:0000H 向下减少的步进值
 #define NFOC_LK1                       (*(volatile  int16* )(NFOC_BASE + (246*2)))     // RV:0000H 低速观测器系数
 #define NFOC_LK2                       (*(volatile  int16* )(NFOC_BASE + (247*2)))     // RV:0000H 低速观测器系数
 #define NFOC_LK3                       (*(volatile  int16* )(NFOC_BASE + (248*2)))     // RV:0000H 低速观测器系数
 #define NFOC_LK4                       (*(volatile  int16* )(NFOC_BASE + (249*2)))     // RV:0000H 低速观测器系数
 #define NFOC_LK5                       (*(volatile  int16* )(NFOC_BASE + (250*2)))     // RV:0000H 低速观测器系数
 #define NFOC_LK6                       (*(volatile  int16* )(NFOC_BASE + (251*2)))     // RV:0000H 低速观测器系数
 #define NFOC_LED                       (*(volatile  int16* )(NFOC_BASE + (252*2)))     // RV:0000H 低速观测器系数
 #define NFOC_LEQ                       (*(volatile  int16* )(NFOC_BASE + (253*2)))     // RV:0000H 低速观测器系数
 #define NFOC_LOME                      (*(volatile  int32* )(NFOC_BASE + (254*2)))     // RV:0000H 低速观测器速度
 #define NFOC_LOMEH                     (*(volatile  int16* )(NFOC_BASE + (255*2)))     // RV:0000H 低速观测器速度
 #define NFOC_XALPHA                    (*(volatile  int32* )(NFOC_BASE + (276*2)))     // RV:0000H 磁链观测器计算中间值      /* factory */
 #define NFOC_XALPHAH                   (*(volatile  int16* )(NFOC_BASE + (277*2)))     // RV:0000H 磁链观测器计算中间值      /* factory */
 #define NFOC_XBETA                     (*(volatile  int32* )(NFOC_BASE + (278*2)))     // RV:0000H 磁链观测器计算中间值      /* factory */
 #define NFOC_XBETAH                    (*(volatile  int16* )(NFOC_BASE + (279*2)))     // RV:0000H 磁链观测器计算中间值      /* factory */
 #define NFOC_ETALPHA                   (*(volatile  int16* )(NFOC_BASE + (298*2)))     // RV:0000H 磁链观测器计算中间值      /* factory */
 #define NFOC_ETBETA                    (*(volatile  int16* )(NFOC_BASE + (299*2)))     // RV:0000H 磁链观测器计算中间值      /* factory */
 #define NFOC_UABT                      (*(volatile  int16* )(NFOC_BASE + (280*2)))     // RV:0000H 磁链观测器计算中间值      /* factory */
 #define NFOC_HEK0                      (*(volatile  int16* )(NFOC_BASE + (282*2)))     // RV:0000H 磁链观测器计算中间值
 #define NFOC_PSI                       (*(volatile  int16* )(NFOC_BASE + (283*2)))     // RV:0000H 磁链观测器计算中间值
 #define NFOC_UIK0                      (*(volatile  int16* )(NFOC_BASE + (284*2)))     // RV:0000H UQ补偿的倍频系数
 #define NFOC_UIK1                      (*(volatile  int16* )(NFOC_BASE + (285*2)))     // RV:0000H UQ补偿的倍频系数
 #define NFOC_UIK2                      (*(volatile  int16* )(NFOC_BASE + (286*2)))     // RV:0000H UQ补偿的倍频系数
 #define NFOC_UIK3                      (*(volatile  int16* )(NFOC_BASE + (287*2)))     // RV:0000H UQ补偿的倍频系数
 #define NFOC_UITC0                     (*(volatile  int16* )(NFOC_BASE + (288*2)))     // RV:0000H UQ补偿的角度相移
 #define NFOC_UIUS0                     (*(volatile  int16* )(NFOC_BASE + (289*2)))     // RV:0000H UQ补偿的幅值
 #define NFOC_UITC1                     (*(volatile  int16* )(NFOC_BASE + (290*2)))     // RV:0000H UQ补偿的角度相移
 #define NFOC_UIUS1                     (*(volatile  int16* )(NFOC_BASE + (291*2)))     // RV:0000H UQ补偿的幅值
 #define NFOC_UITC2                     (*(volatile  int16* )(NFOC_BASE + (292*2)))     // RV:0000H UQ补偿的角度相移
 #define NFOC_UIUS2                     (*(volatile  int16* )(NFOC_BASE + (293*2)))     // RV:0000H UQ补偿的幅值
 #define NFOC_UITC3                     (*(volatile  int16* )(NFOC_BASE + (294*2)))     // RV:0000H UQ补偿的角度相移
 #define NFOC_UIUS3                     (*(volatile  int16* )(NFOC_BASE + (295*2)))     // RV:0000H UQ补偿的幅值
 #define NFOC_TRG1                      (*(volatile  int16* )(NFOC_BASE + (296*2)))     // RV:0000H I1采样点对应DR值
 #define NFOC_TRG2                      (*(volatile  int16* )(NFOC_BASE + (297*2)))     // RV:0000H I2采样点对应DR值
    
 #define NFOC_OTHETA                    (*(volatile  int32* )(NFOC_BASE + (300*2)))     // RV:0000H 估算器估算角度（32位）
 #define NFOC_OTHETAH                   (*(volatile  int16* )(NFOC_BASE + (301*2)))     // RV:0000H 估算器角度高16位
  
 #define NFOC_USK                       (*(volatile  int16* )(NFOC_BASE + (302*2)))     // RV:0000H 相电压采样值系数
 #define NFOC_UA                        (*(volatile  int16* )(NFOC_BASE + (303*2)))     // RV:0000H A相电压采样值
 #define NFOC_UB                        (*(volatile  int16* )(NFOC_BASE + (304*2)))     // RV:0000H B相电压采样值
 #define NFOC_UC                        (*(volatile  int16* )(NFOC_BASE + (305*2)))     // RV:0000H C相电压采样值
 #define NFOC_USAL1                     (*(volatile  int16* )(NFOC_BASE + (306*2)))     // RV:0000H UA、UB、UC计算的USALPHA值
 #define NFOC_USBE1                     (*(volatile  int16* )(NFOC_BASE + (307*2)))     // RV:0000H UA、UB、UC计算的USBETA值
  
 #define NFOC_DELOTHE                   (*(volatile  int32* )(NFOC_BASE + (326*2)))     // RV:0000H 估算器估算角度（32位）
 #define NFOC_DELOTHEH                  (*(volatile  int16* )(NFOC_BASE + (327*2)))     // RV:0000H 估算器估算角度
 #define NFOC_DELETHE                   (*(volatile  int32* )(NFOC_BASE + (328*2)))     // RV:0000H 估算器估算角度（32位）
 #define NFOC_DELETHEH                  (*(volatile  int16* )(NFOC_BASE + (329*2)))     // RV:0000H 估算器估算角度
 #define NFOC_IG0                       (*(volatile  int16* )(NFOC_BASE + (310*2)))     // RV:0000H 高频注入计算中间值      /* factory */
 #define NFOC_IF0                       (*(volatile  int16* )(NFOC_BASE + (311*2)))     // RV:0000H 高频注入计算中间值      /* factory */
 #define NFOC_HUCPS                     (*(volatile  int16* )(NFOC_BASE + (312*2)))     // RV:0000H 高频注入计算中间值      /* factory */
 #define NFOC_HCTHE                     (*(volatile  int16* )(NFOC_BASE + (313*2)))     // RV:0000H 高频注入计算中间值      /* factory */
 #define NFOC_FWREF                     (*(volatile  int16* )(NFOC_BASE + (314*2)))     // RV:0000H 弱磁PI给定值
 
 #define NFOC_UDCD                      (*(volatile  int16* )(NFOC_BASE + (330*2)))     // RV:0000H d轴UDC值
 #define NFOC_UDCQ                      (*(volatile  int16* )(NFOC_BASE + (331*2)))     // RV:0000H q轴UDC值
 
 #define NFOC_IQMAX                     (*(volatile uint16* )(NFOC_BASE + (332*2)))     // RV:0000H IQREF最大值
 #define NFOC_IQMIN                     (*(volatile uint16* )(NFOC_BASE + (333*2)))     // RV:0000H IQREF最小值
 
 #define NFOC_WUCPS                     (*(volatile  int16* )(NFOC_BASE + (414*2)))     // RV:0000H 外环补偿值
 #define NFOC_WUFIN                     (*(volatile  int16* )(NFOC_BASE + (415*2)))     // RV:0000H 外环最终值
 #define NFOC_FWIDR                     (*(volatile  int16* )(NFOC_BASE + (446*2)))     // RV:0000H 弱磁MOD1时弱磁的输出
 #define NFOC_CSAM                      (*(volatile  int16* )(NFOC_BASE + (455*2)))     // RV:0000H 用于装载到FOC_CSAM_MD
 #define NFOC_IDRLIM                    (*(volatile  int16* )(NFOC_BASE + (475*2)))     // RV:0000H 弱磁计算中IDREF的限幅值
 #define NFOC_USFLT                     (*(volatile  int32* )(NFOC_BASE + (504*2)))     // RV:0000H NFOCx_US滤波值
 
 #define NFOC_F1LB0                     (*(volatile uint16* )(NFOC_BASE + (334*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC_F1HB0                     (*(volatile uint16* )(NFOC_BASE + (335*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC_F1LB1                     (*(volatile uint16* )(NFOC_BASE + (336*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC_F1LB2                     (*(volatile uint16* )(NFOC_BASE + (337*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC_F1LA1                     (*(volatile uint16* )(NFOC_BASE + (338*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC_F1LA2                     (*(volatile uint16* )(NFOC_BASE + (339*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC_F1HB1                     (*(volatile uint16* )(NFOC_BASE + (340*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC_F1HB2                     (*(volatile uint16* )(NFOC_BASE + (341*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC_F1HA1                     (*(volatile uint16* )(NFOC_BASE + (342*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC_F1HA2                     (*(volatile uint16* )(NFOC_BASE + (343*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC_F1X0                      (*(volatile uint16* )(NFOC_BASE + (344*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC_F1X1                      (*(volatile uint16* )(NFOC_BASE + (346*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC_F1X2                      (*(volatile uint16* )(NFOC_BASE + (347*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC_F1Y1                      (*(volatile uint16* )(NFOC_BASE + (348*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC_F1Y2                      (*(volatile uint16* )(NFOC_BASE + (349*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC_F1Z1                      (*(volatile uint16* )(NFOC_BASE + (350*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC_F1Z2                      (*(volatile uint16* )(NFOC_BASE + (351*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC_F1Y                       (*(volatile uint32* )(NFOC_BASE + (352*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC_F1YH                      (*(volatile uint16* )(NFOC_BASE + (353*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC_F1U1                      (*(volatile uint16* )(NFOC_BASE + (416*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC_F1U2                      (*(volatile uint16* )(NFOC_BASE + (417*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC_F1YG                      (*(volatile uint32* )(NFOC_BASE + (424*2)))     // RV:0000H IQREF滤波器参数      /* factory */
 #define NFOC_F1YD                      (*(volatile uint32* )(NFOC_BASE + (426*2)))     // RV:0000H IQREF滤波器参数      /* factory */
 
 #define NFOC_F2LB0                     (*(volatile uint16* )(NFOC_BASE + (354*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC_F2HB0                     (*(volatile uint16* )(NFOC_BASE + (355*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC_F2LB1                     (*(volatile uint16* )(NFOC_BASE + (356*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC_F2LB2                     (*(volatile uint16* )(NFOC_BASE + (357*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC_F2LA1                     (*(volatile uint16* )(NFOC_BASE + (358*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC_F2LA2                     (*(volatile uint16* )(NFOC_BASE + (359*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC_F2HB1                     (*(volatile uint16* )(NFOC_BASE + (360*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC_F2HB2                     (*(volatile uint16* )(NFOC_BASE + (361*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC_F2HA1                     (*(volatile uint16* )(NFOC_BASE + (362*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC_F2HA2                     (*(volatile uint16* )(NFOC_BASE + (363*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC_F2X0                      (*(volatile uint16* )(NFOC_BASE + (364*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC_F2X1                      (*(volatile uint16* )(NFOC_BASE + (366*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC_F2X2                      (*(volatile uint16* )(NFOC_BASE + (367*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC_F2Y1                      (*(volatile uint16* )(NFOC_BASE + (368*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC_F2Y2                      (*(volatile uint16* )(NFOC_BASE + (369*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC_F2Z1                      (*(volatile uint16* )(NFOC_BASE + (370*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC_F2Z2                      (*(volatile uint16* )(NFOC_BASE + (371*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC_F2Y                       (*(volatile uint32* )(NFOC_BASE + (372*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC_F2YH                      (*(volatile uint16* )(NFOC_BASE + (373*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC_F2U1                      (*(volatile uint16* )(NFOC_BASE + (418*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC_F2U2                      (*(volatile uint16* )(NFOC_BASE + (419*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC_F2YG                      (*(volatile uint32* )(NFOC_BASE + (428*2)))     // RV:0000H IQREF滤波器参数      /* factory */
 #define NFOC_F2YD                      (*(volatile uint32* )(NFOC_BASE + (430*2)))     // RV:0000H IQREF滤波器参数      /* factory */
 
 #define NFOC_F3LB0                     (*(volatile uint16* )(NFOC_BASE + (374*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC_F3HB0                     (*(volatile uint16* )(NFOC_BASE + (375*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC_F3LB1                     (*(volatile uint16* )(NFOC_BASE + (376*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC_F3LB2                     (*(volatile uint16* )(NFOC_BASE + (377*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC_F3LA1                     (*(volatile uint16* )(NFOC_BASE + (378*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC_F3LA2                     (*(volatile uint16* )(NFOC_BASE + (379*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC_F3HB1                     (*(volatile uint16* )(NFOC_BASE + (380*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC_F3HB2                     (*(volatile uint16* )(NFOC_BASE + (381*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC_F3HA1                     (*(volatile uint16* )(NFOC_BASE + (382*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC_F3HA2                     (*(volatile uint16* )(NFOC_BASE + (383*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC_F3X0                      (*(volatile uint16* )(NFOC_BASE + (384*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC_F3X1                      (*(volatile uint16* )(NFOC_BASE + (386*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC_F3X2                      (*(volatile uint16* )(NFOC_BASE + (387*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC_F3Y1                      (*(volatile uint16* )(NFOC_BASE + (388*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC_F3Y2                      (*(volatile uint16* )(NFOC_BASE + (389*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC_F3Z1                      (*(volatile uint16* )(NFOC_BASE + (390*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC_F3Z2                      (*(volatile uint16* )(NFOC_BASE + (391*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC_F3Y                       (*(volatile uint32* )(NFOC_BASE + (392*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC_F3YH                      (*(volatile uint16* )(NFOC_BASE + (393*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC_F3U1                      (*(volatile uint16* )(NFOC_BASE + (420*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC_F3U2                      (*(volatile uint16* )(NFOC_BASE + (421*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC_F3YG                      (*(volatile uint32* )(NFOC_BASE + (432*2)))     // RV:0000H IQREF滤波器参数      /* factory */
 #define NFOC_F3YD                      (*(volatile uint32* )(NFOC_BASE + (434*2)))     // RV:0000H IQREF滤波器参数      /* factory */
 
 #define NFOC_F4LB0                     (*(volatile uint16* )(NFOC_BASE + (394*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC_F4HB0                     (*(volatile uint16* )(NFOC_BASE + (395*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC_F4LB1                     (*(volatile uint16* )(NFOC_BASE + (396*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC_F4LB2                     (*(volatile uint16* )(NFOC_BASE + (397*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC_F4LA1                     (*(volatile uint16* )(NFOC_BASE + (398*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC_F4LA2                     (*(volatile uint16* )(NFOC_BASE + (399*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC_F4HB1                     (*(volatile uint16* )(NFOC_BASE + (400*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC_F4HB2                     (*(volatile uint16* )(NFOC_BASE + (401*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC_F4HA1                     (*(volatile uint16* )(NFOC_BASE + (402*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC_F4HA2                     (*(volatile uint16* )(NFOC_BASE + (403*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC_F4X0                      (*(volatile uint16* )(NFOC_BASE + (404*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC_F4X1                      (*(volatile uint16* )(NFOC_BASE + (406*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC_F4X2                      (*(volatile uint16* )(NFOC_BASE + (407*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC_F4Y1                      (*(volatile uint16* )(NFOC_BASE + (408*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC_F4Y2                      (*(volatile uint16* )(NFOC_BASE + (409*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC_F4Z1                      (*(volatile uint16* )(NFOC_BASE + (410*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC_F4Z2                      (*(volatile uint16* )(NFOC_BASE + (411*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC_F4Y                       (*(volatile uint32* )(NFOC_BASE + (412*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC_F4YH                      (*(volatile uint16* )(NFOC_BASE + (413*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC_F4U1                      (*(volatile uint16* )(NFOC_BASE + (422*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC_F4U2                      (*(volatile uint16* )(NFOC_BASE + (423*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC_F4YG                      (*(volatile uint32* )(NFOC_BASE + (436*2)))     // RV:0000H IQREF滤波器参数      /* factory */
 #define NFOC_F4YD                      (*(volatile uint32* )(NFOC_BASE + (438*2)))     // RV:0000H IQREF滤波器参数      /* factory */

 #define NFOC_FOUT                      (*(volatile  int16* )(NFOC_BASE + (472*2)))     // RV:0000H 四级滤波器输出

 #define NFOC_F1LB0SH                   (*(volatile uint16* )(NFOC_BASE + (476*2)))     // RV:0000H IQREF滤波器参数影子寄存器
 #define NFOC_F1HB0SH					(*(volatile uint16* )(NFOC_BASE + (477*2)))     // RV:0000H IQREF滤波器参数影子寄存器
 #define NFOC_F1LB1SH					(*(volatile uint16* )(NFOC_BASE + (478*2)))     // RV:0000H IQREF滤波器参数影子寄存器
 #define NFOC_F1LB2SH                   (*(volatile uint16* )(NFOC_BASE + (479*2)))     // RV:0000H IQREF滤波器参数影子寄存器
 #define NFOC_F1LA1SH                   (*(volatile uint16* )(NFOC_BASE + (480*2)))     // RV:0000H IQREF滤波器参数影子寄存器
 #define NFOC_F1LA2SH                   (*(volatile uint16* )(NFOC_BASE + (481*2)))     // RV:0000H IQREF滤波器参数影子寄存器
 #define NFOC_F1HB1SH                   (*(volatile uint16* )(NFOC_BASE + (482*2)))     // RV:0000H IQREF滤波器参数影子寄存器
 #define NFOC_F1HB2SH                   (*(volatile uint16* )(NFOC_BASE + (483*2)))     // RV:0000H IQREF滤波器参数影子寄存器
 #define NFOC_F1HA1SH                   (*(volatile uint16* )(NFOC_BASE + (484*2)))     // RV:0000H IQREF滤波器参数影子寄存器
 #define NFOC_F1HA2SH                   (*(volatile uint16* )(NFOC_BASE + (485*2)))     // RV:0000H IQREF滤波器参数影子寄存器
 
 #define NFOC_XI0                       (*(volatile  int16* )(NFOC_BASE + (24*2)))      // RV:0000H CORDIC0 SIN/COS计算的X轴输入
 #define NFOC_YI0                       (*(volatile  int16* )(NFOC_BASE + (25*2)))      // RV:0000H CORDIC0 SIN/COS计算的y轴输入
 #define NFOC_THETA0                    (*(volatile  int16* )(NFOC_BASE + (27*2)))      // RV:0000H CORDIC0 SIN/COS计算的角度输入
 #define NFOC_XO0                       (*(volatile  int16* )(NFOC_BASE + (28*2)))      // RV:0000H CORDIC0 SIN/COS计算的X轴输出
 #define NFOC_YO0                       (*(volatile  int16* )(NFOC_BASE + (29*2)))      // RV:0000H CORDIC0 SIN/COS计算的y轴输出
 #define NFOC_XI1                       (*(volatile  int16* )(NFOC_BASE + (30*2)))      // RV:0000H CORDIC1 SIN/COS计算的X轴输入
 #define NFOC_YI1                       (*(volatile  int16* )(NFOC_BASE + (31*2)))      // RV:0000H CORDIC1 SIN/COS计算的y轴输入
 #define NFOC_THETA1                    (*(volatile  int16* )(NFOC_BASE + (33*2)))      // RV:0000H CORDIC1 SIN/COS计算的角度输入
 #define NFOC_XO1                       (*(volatile  int16* )(NFOC_BASE + (34*2)))      // RV:0000H CORDIC1 SIN/COS计算的X轴输出
 #define NFOC_YO1                       (*(volatile  int16* )(NFOC_BASE + (35*2)))      // RV:0000H CORDIC1 SIN/COS计算的y轴输出
 #define NFOC_XI2                       (*(volatile  int16* )(NFOC_BASE + (36*2)))      // RV:0000H CORDIC2 ATAN计算的X轴输入
 #define NFOC_YI2                       (*(volatile  int16* )(NFOC_BASE + (37*2)))      // RV:0000H CORDIC2 ATAN计算的y轴输入
 #define NFOC_US2                       (*(volatile  int16* )(NFOC_BASE + (38*2)))      // RV:0000H CORDIC2 ATAN计算的幅值输出
 #define NFOC_THETA2                    (*(volatile  int16* )(NFOC_BASE + (39*2)))      // RV:0000H CORDIC2 ATAN计算的角度输出
 #define NFOC_XI3                       (*(volatile  int16* )(NFOC_BASE + (40*2)))      // RV:0000H CORDIC3 ATAN计算的X轴输入
 #define NFOC_YI3                       (*(volatile  int16* )(NFOC_BASE + (41*2)))      // RV:0000H CORDIC3 ATAN计算的y轴输入
 #define NFOC_US3                       (*(volatile  int16* )(NFOC_BASE + (42*2)))      // RV:0000H CORDIC3 ATAN计算的幅值输出
 #define NFOC_THETA3                    (*(volatile  int16* )(NFOC_BASE + (43*2)))      // RV:0000H CORDIC3 ATAN计算的角度输出

 //新增伺服M / MT法功能（DRV_FCR4）和FOC寄存器：
 #define NFOC_MQEP                      (*(volatile  int16* )(NFOC_BASE + (44*2)))     // RV:0000H MMT计算的QEP脉冲数
 #define NFOC_MQEP1                     (*(volatile  int16* )(NFOC_BASE + (45*2)))     // RV:0000H MMT计算的前一次QEP脉冲数
 #define NFOC_MBASE                     (*(volatile  int16* )(NFOC_BASE + (46*2)))     // RV:0000H MMT计算的速度转化系数
 #define NFOC_MSHFT                     (*(volatile  int16* )(NFOC_BASE + (47*2)))     // RV:0000H MMT计算的速度移位值(0~16)
 #define NFOC_MDEL                      (*(volatile  int16* )(NFOC_BASE + (48*2)))     // RV:0000H MMT计算的脉冲数增量

 #define NFOC_MDEL1                     (*(volatile  int16* )(NFOC_BASE + (49*2)))     // RV:0000H MMT计算的前一次脉冲数增量
 #define NFOC_MBLK                      (*(volatile  int16* )(NFOC_BASE + (50*2)))     // RV:0000H MMT计算的空白周期数
 #define NFOC_MBLK1                     (*(volatile  int16* )(NFOC_BASE + (51*2)))     // RV:0000H MMT计算的前一次空白周期数
 #define NFOC_MREM                      (*(volatile  int16* )(NFOC_BASE + (52*2)))     // RV:0000H MMT计算的时钟余数
 #define NFOC_MREM1                     (*(volatile  int16* )(NFOC_BASE + (53*2)))     // RV:0000H MMT计算的前一次时钟余数
 #define NFOC_MARR                      (*(volatile  int16* )(NFOC_BASE + (54*2)))     // RV:0000H MMT计算的单周期时钟计数
 #define NFOC_MCOE                      (*(volatile  int16* )(NFOC_BASE + (55*2)))     // RV:0000H MMT计算中间值
 #define NFOC_MPERD                     (*(volatile  int32* )(NFOC_BASE + (56*2)))     // RV:0000H MMT计算中间值（32位）
 #define NFOC_MPERD1                    (*(volatile  int32* )(NFOC_BASE + (58*2)))     // RV:0000H MMT计算中间值（32位）
 #define NFOC_MOME                      (*(volatile  int16* )(NFOC_BASE + (60*2)))     // RV:0000H MMT计算的速度

 #define NFOC_UDK                       (*(volatile  int16* )(NFOC_BASE + (440*2)))     // RV:0000H UD滤波器系数
 #define NFOC_UQK                       (*(volatile  int16* )(NFOC_BASE + (441*2)))     // RV:0000H UQ滤波器系数
 #define NFOC_UDFLT                     (*(volatile  int32* )(NFOC_BASE + (442*2)))     // RV:0000H UD滤波器输出(32bit)
 #define NFOC_UQFLT                     (*(volatile  int32* )(NFOC_BASE + (444*2)))     // RV:0000H UQ滤波器输出(32bit)
 #define NFOC_UQFLTH                    (*(volatile  int16* )(NFOC_BASE + (445*2)))     // RV:0000H UQ滤波值高16位

 #define NFOC_OSCNT                     (*(volatile  int16* )(NFOC_BASE + (447*2)))     // RV:0000H OFFSET校准计数值
 #define NFOC_OSSUM                     (*(volatile  int32* )(NFOC_BASE + (448*2)))     // RV:0000H OFFSET校准和

 #define NFOC_FFLT						(*(volatile  int16* )(NFOC_BASE + (472*2)))     // RV:0000H 四级滤波器输出
 #define NFOC_FCPS                      (*(volatile  int16* )(NFOC_BASE + (473*2)))     // RV:0000H 四级滤波器输出补偿值
 #define NFOC_IQRORG                    (*(volatile  int16* )(NFOC_BASE + (474*2)))     // RV:0000H 四级滤波器加上补偿和限幅后输出

 
 #define NFOC2_BASE                     0x30010000
 #define NFOC2_I1                       (*(volatile  int16* )(NFOC2_BASE + ( 222*2)))   // RV:0000H 第一次采样ADC值      /* factory */
 #define NFOC2_I2                       (*(volatile  int16* )(NFOC2_BASE + ( 223*2)))   // RV:0000H 第二次采样ADC值      /* factory */
 #define NFOC2_IA                       (*(volatile  int16* )(NFOC2_BASE + ( 224*2)))   // RV:0000H 计算得到的IA
 #define NFOC2_IB                       (*(volatile  int16* )(NFOC2_BASE + ( 225*2)))   // RV:0000H 计算得到的IB
 #define NFOC2_IC                       (*(volatile  int16* )(NFOC2_BASE + ( 226*2)))   // RV:0000H 计算得到的IC
 #define NFOC2_ICMAX                    (*(volatile  int16* )(NFOC2_BASE + ( 227*2)))   // RV:0000H IC最大值
 #define NFOC2_IAMAX                    (*(volatile  int16* )(NFOC2_BASE + ( 228*2)))   // RV:0000H IA最大值
 #define NFOC2_IBMAX                    (*(volatile  int16* )(NFOC2_BASE + ( 229*2)))   // RV:0000H IB最大值
 #define NFOC2_IALPHA                   (*(volatile  int16* )(NFOC2_BASE + ( 154*2)))   // RV:0000H Clarke变换后的IALPHA
 #define NFOC2_IBETA                    (*(volatile  int16* )(NFOC2_BASE + ( 155*2)))   // RV:0000H Clarke变换后的IBETA
 #define NFOC2_ID                       (*(volatile  int16* )(NFOC2_BASE + ( 156*2)))   // RV:0000H Park变换后的ID
 #define NFOC2_IQ                       (*(volatile  int16* )(NFOC2_BASE + ( 157*2)))   // RV:0000H Park变换后的IQ
 #define NFOC2_IDFLT                    (*(volatile  int32* )(NFOC2_BASE + ( 158*2)))   // RV:0000H ID滤波值（32位）
 #define NFOC2_IDFLTH                   (*(volatile  int16* )(NFOC2_BASE + ( 159*2)))   // RV:0000H ID滤波值高16位
 #define NFOC2_IQFLT                    (*(volatile  int32* )(NFOC2_BASE + ( 170*2)))   // RV:0000H IQ滤波值（32位）
 #define NFOC2_IQFLTH                   (*(volatile  int16* )(NFOC2_BASE + ( 171*2)))   // RV:0000H IQ滤波值高16位
 #define NFOC2_THETA                    (*(volatile  int32* )(NFOC2_BASE + ( 172*2)))   // RV:0000H 角度值（32位）
 #define NFOC2_THETAL                   (*(volatile  int16* )(NFOC2_BASE + ( 172*2)))   // RV:0000H 角度值低16位
 #define NFOC2_THETAH                   (*(volatile  int16* )(NFOC2_BASE + ( 173*2)))   // RV:0000H 角度值高16位
 #define NFOC2_EALPHA                   (*(volatile  int32* )(NFOC2_BASE + ( 174*2)))   // RV:0000H 估算器估算反电动势EALPHA（32位）
 #define NFOC2_EALPHAH                  (*(volatile  int16* )(NFOC2_BASE + ( 175*2)))   // RV:0000H 估算器估算反电动势EALPHA高16位
 #define NFOC2_EBETA                    (*(volatile  int32* )(NFOC2_BASE + ( 186*2)))   // RV:0000H 估算器估算反电动势EBETA（32位）
 #define NFOC2_EBETAH                   (*(volatile  int16* )(NFOC2_BASE + ( 187*2)))   // RV:0000H 估算器估算反电动势EBETA高16位
 #define NFOC2_ETHETA                   (*(volatile  int32* )(NFOC2_BASE + ( 188*2)))   // RV:0000H 估算器估算角度（32位）
 #define NFOC2_ETHETAH                  (*(volatile  int16* )(NFOC2_BASE + ( 189*2)))   // RV:0000H 估算器角度高16位
 #define NFOC2_ZALORG                   (*(volatile  int16* )(NFOC2_BASE + ( 190*2)))   // RV:0000H 估算反电动势      /* factory */
 #define NFOC2_ZBEORG                   (*(volatile  int16* )(NFOC2_BASE + ( 191*2)))   // RV:0000H 估算反电动势      /* factory */
 #define NFOC2_EMF                      (*(volatile  int16* )(NFOC2_BASE + ( 240*2)))   // RV:0000H EALPHA和EBETA计算幅值（平方和后开方），即估算反电动势幅值
 #define NFOC2_ATHETA                   (*(volatile  int16* )(NFOC2_BASE + ( 241*2)))   // RV:0000H EALPHA和EBETA计算角度      /* factory */
 #define NFOC2_OMECLI                   (*(volatile  int32* )(NFOC2_BASE + ( 256*2)))   // RV:0000H Omega启动的实时值（32位）      /* factory */
 #define NFOC2_OMECLIL                  (*(volatile  int16* )(NFOC2_BASE + ( 256*2)))   // RV:0000H Omega启动的实时值低16位      /* factory */
 #define NFOC2_OMECLIH                  (*(volatile  int16* )(NFOC2_BASE + ( 257*2)))   // RV:0000H Omega启动的实时值高16位      /* factory */
 #define NFOC2_OMEGA                    (*(volatile  int16* )(NFOC2_BASE + ( 258*2)))   // RV:0000H 估算OMEGA
 
 #define NFOC2_IESTA                    (*(volatile  int16* )(NFOC2_BASE + ( 260*2)))   // RV:0000H 估算电流IALPHA
 #define NFOC2_IESTB                    (*(volatile  int16* )(NFOC2_BASE + ( 261*2)))   // RV:0000H 估算电流IBETA
 #define NFOC2_OMEFLT                   (*(volatile  int32* )(NFOC2_BASE + ( 262*2)))   // RV:0000H OMEGA一级滤波值（32位）
 #define NFOC2_OMEFLTH                  (*(volatile  int16* )(NFOC2_BASE + ( 263*2)))   // RV:0000H OMEGA一级滤波值高16位
 #define NFOC2_OMEFL2                   (*(volatile  int32* )(NFOC2_BASE + ( 264*2)))   // RV:0000H OMEGA二级滤波值（32位）
 #define NFOC2_OMEFL2H                  (*(volatile  int16* )(NFOC2_BASE + ( 265*2)))   // RV:0000H OMEGA二级滤波值高16位
 #define NFOC2_ZALPHA                   (*(volatile  int16* )(NFOC2_BASE + ( 266*2)))   // RV:0000H 滤波前的估算反电动势      /* factory */
 #define NFOC2_ZBETA                    (*(volatile  int16* )(NFOC2_BASE + ( 267*2)))   // RV:0000H 滤波前的估算反电动势      /* factory */
 #define NFOC2_KLPF                     (*(volatile  int16* )(NFOC2_BASE + ( 268*2)))   // RV:0000H 估算器的低通滤波器系数
 #define NFOC2_UDFIN                    (*(volatile  int16* )(NFOC2_BASE + ( 270*2)))   // RV:0000H UD最终值
 #define NFOC2_UQFIN                    (*(volatile  int16* )(NFOC2_BASE + ( 271*2)))   // RV:0000H UQ最终值
 #define NFOC2_UALPHA                   (*(volatile  int16* )(NFOC2_BASE + ( 272*2)))   // RV:0000H UALPHA
 #define NFOC2_UBETA                    (*(volatile  int16* )(NFOC2_BASE + ( 273*2)))   // RV:0000H UBETA
 #define NFOC2_UALORG                   (*(volatile  int16* )(NFOC2_BASE + ( 140*2)))   // RV:0000H UALORG
 #define NFOC2_UBEORG                   (*(volatile  int16* )(NFOC2_BASE + ( 141*2)))   // RV:0000H UBEORG
 #define NFOC2_Y                        (*(volatile  int16* )(NFOC2_BASE + ( 274*2)))   // RV:0000H SVPWM计算中间值      /* factory */
 #define NFOC2_Z                        (*(volatile  int16* )(NFOC2_BASE + ( 275*2)))   // RV:0000H SVPWM计算中间值      /* factory */
 #define NFOC2_T1ORG                    (*(volatile  int16* )(NFOC2_BASE + ( 48*2)))    // RV:0000H SVPWM计算中间值      /* factory */
 #define NFOC2_T2ORG                    (*(volatile  int16* )(NFOC2_BASE + ( 49*2)))    // RV:0000H SVPWM计算中间值      /* factory */
 #define NFOC2_T1RC                     (*(volatile  int16* )(NFOC2_BASE + ( 50*2)))    // RV:0000H SVPWM计算中间值      /* factory */
 #define NFOC2_T2RC                     (*(volatile  int16* )(NFOC2_BASE + ( 51*2)))    // RV:0000H SVPWM计算中间值      /* factory */
 #define NFOC2_OMUNIT                   (*(volatile  int16* )(NFOC2_BASE + ( 52*2)))    // RV:0000H 过调制放大系数
 #define NFOC2_TC                       (*(volatile  int16* )(NFOC2_BASE + ( 54*2)))    // RV:0000H SVPWM计算中间值      /* factory */
 #define NFOC2_TB                       (*(volatile  int16* )(NFOC2_BASE + ( 55*2)))    // RV:0000H SVPWM计算中间值      /* factory */
 #define NFOC2_TA                       (*(volatile  int16* )(NFOC2_BASE + ( 56*2)))    // RV:0000H SVPWM计算中间值      /* factory */
 #define NFOC2_DLYCNT                   (*(volatile  uint16* )(NFOC2_BASE + ( 57*2)))   // RV:0000H dly_en功能延迟的clk数
 #define NFOC2_TAON                     (*(volatile  int16* )(NFOC2_BASE + ( 58*2)))    // RV:0000H SVPWM计算中间值      /* factory */
 #define NFOC2_TAOND                    (*(volatile  int16* )(NFOC2_BASE + ( 59*2)))    // RV:0000H SVPWM计算中间值      /* factory */
 #define NFOC2_TBON                     (*(volatile  int16* )(NFOC2_BASE + ( 60*2)))    // RV:0000H SVPWM计算中间值      /* factory */
 #define NFOC2_TBOND                    (*(volatile  int16* )(NFOC2_BASE + ( 61*2)))    // RV:0000H SVPWM计算中间值      /* factory */
 #define NFOC2_TCON                     (*(volatile  int16* )(NFOC2_BASE + ( 62*2)))    // RV:0000H SVPWM计算中间值      /* factory */
 #define NFOC2_TCOND                    (*(volatile  int16* )(NFOC2_BASE + ( 63*2)))    // RV:0000H SVPWM计算中间值      /* factory */
 #define NFOC2_TADTC                    (*(volatile  int16* )(NFOC2_BASE + ( 64*2)))    // RV:0000H SVPWM计算中间值      /* factory */
 #define NFOC2_TADTCD                   (*(volatile  int16* )(NFOC2_BASE + ( 65*2)))    // RV:0000H SVPWM计算中间值      /* factory */
 #define NFOC2_TBDTC                    (*(volatile  int16* )(NFOC2_BASE + ( 66*2)))    // RV:0000H SVPWM计算中间值      /* factory */
 #define NFOC2_TBDTCD                   (*(volatile  int16* )(NFOC2_BASE + ( 67*2)))    // RV:0000H SVPWM计算中间值      /* factory */
 #define NFOC2_TCDTC                    (*(volatile  int16* )(NFOC2_BASE + ( 68*2)))    // RV:0000H SVPWM计算中间值      /* factory */
 #define NFOC2_TCDTCD                   (*(volatile  int16* )(NFOC2_BASE + ( 69*2)))    // RV:0000H SVPWM计算中间值      /* factory */
 #define NFOC2_DR1                      (*(volatile uint16* )(NFOC2_BASE + ( 70*2)))    // RV:0000H SVPWM计算中间值      /* factory */
 #define NFOC2_DR1N                     (*(volatile uint16* )(NFOC2_BASE + ( 71*2)))    // RV:0000H SVPWM计算中间值      /* factory */
 #define NFOC2_DR2                      (*(volatile uint16* )(NFOC2_BASE + ( 72*2)))    // RV:0000H SVPWM计算中间值      /* factory */
 #define NFOC2_DR2N                     (*(volatile uint16* )(NFOC2_BASE + ( 73*2)))    // RV:0000H SVPWM计算中间值      /* factory */
 #define NFOC2_DR3                      (*(volatile uint16* )(NFOC2_BASE + ( 74*2)))    // RV:0000H SVPWM计算中间值      /* factory */
 #define NFOC2_DR3N                     (*(volatile uint16* )(NFOC2_BASE + ( 75*2)))    // RV:0000H SVPWM计算中间值      /* factory */
 #define NFOC2_DRA                      (*(volatile uint16* )(NFOC2_BASE + ( 76*2)))    // RV:0000H SVPWM装载到DRV的值      /* factory */
 #define NFOC2_DRAN                     (*(volatile uint16* )(NFOC2_BASE + ( 77*2)))    // RV:0000H SVPWM装载到DRV的值      /* factory */
 #define NFOC2_DRB                      (*(volatile uint16* )(NFOC2_BASE + ( 78*2)))    // RV:0000H SVPWM装载到DRV的值      /* factory */
 #define NFOC2_DRBN                     (*(volatile uint16* )(NFOC2_BASE + ( 79*2)))    // RV:0000H SVPWM装载到DRV的值      /* factory */
 #define NFOC2_DRC                      (*(volatile uint16* )(NFOC2_BASE + ( 80*2)))    // RV:0000H SVPWM装载到DRV的值      /* factory */
 #define NFOC2_DRCN                     (*(volatile uint16* )(NFOC2_BASE + ( 81*2)))    // RV:0000H SVPWM装载到DRV的值      /* factory */
 #define NFOC2_UDCALP                   (*(volatile  int16* )(NFOC2_BASE + ( 82*2)))    // RV:0000H UDC*UALPHA
 #define NFOC2_UDCBET                   (*(volatile  int16* )(NFOC2_BASE + ( 83*2)))    // RV:0000H UDC*UBETA
 #define NFOC2_MAY1                     (*(volatile  int16* )(NFOC2_BASE + ( 84*2)))    // RV:0000H AO观测器相关信号      /* factory */
 #define NFOC2_MBY1                     (*(volatile  int16* )(NFOC2_BASE + ( 85*2)))    // RV:0000H AO观测器相关信号      /* factory */
 #define NFOC2_MAY2                     (*(volatile  int16* )(NFOC2_BASE + ( 86*2)))    // RV:0000H AO观测器相关信号      /* factory */
 #define NFOC2_MBY2                     (*(volatile  int16* )(NFOC2_BASE + ( 87*2)))    // RV:0000H AO观测器相关信号      /* factory */
 #define NFOC2_MAY3                     (*(volatile  int16* )(NFOC2_BASE + ( 88*2)))    // RV:0000H AO观测器相关信号      /* factory */
 #define NFOC2_MBY3                     (*(volatile  int16* )(NFOC2_BASE + ( 89*2)))    // RV:0000H AO观测器相关信号      /* factory */
 #define NFOC2_MAY4                     (*(volatile  int16* )(NFOC2_BASE + ( 90*2)))    // RV:0000H AO观测器相关信号      /* factory */
 #define NFOC2_MBY4                     (*(volatile  int16* )(NFOC2_BASE + ( 91*2)))    // RV:0000H AO观测器相关信号      /* factory */
 #define NFOC2_MAY5                     (*(volatile  int16* )(NFOC2_BASE + ( 92*2)))    // RV:0000H AO观测器相关信号      /* factory */
 #define NFOC2_MBY5                     (*(volatile  int16* )(NFOC2_BASE + ( 93*2)))    // RV:0000H AO观测器相关信号      /* factory */
 #define NFOC2_MAU1                     (*(volatile  int16* )(NFOC2_BASE + ( 94*2)))    // RV:0000H AO观测器相关信号      /* factory */
 #define NFOC2_MBU1                     (*(volatile  int16* )(NFOC2_BASE + ( 95*2)))    // RV:0000H AO观测器相关信号      /* factory */
 #define NFOC2_MAU2                     (*(volatile  int16* )(NFOC2_BASE + ( 96*2)))    // RV:0000H AO观测器相关信号      /* factory */
 #define NFOC2_MBU2                     (*(volatile  int16* )(NFOC2_BASE + ( 97*2)))    // RV:0000H AO观测器相关信号      /* factory */
 #define NFOC2_MAU3                     (*(volatile  int16* )(NFOC2_BASE + ( 98*2)))    // RV:0000H AO观测器相关信号      /* factory */
 #define NFOC2_MBU3                     (*(volatile  int16* )(NFOC2_BASE + ( 99*2)))    // RV:0000H AO观测器相关信号      /* factory */
 #define NFOC2_MAU4                     (*(volatile  int16* )(NFOC2_BASE + (100*2)))    // RV:0000H AO观测器相关信号      /* factory */
 #define NFOC2_MBU4                     (*(volatile  int16* )(NFOC2_BASE + (101*2)))    // RV:0000H AO观测器相关信号      /* factory */
 #define NFOC2_FTCPS                    (*(volatile  int16* )(NFOC2_BASE + (102*2)))    // RV:0000H 计算得到的动态补偿角FTCPS = FTCK*OMEFL2*FBASE
 #define NFOC2_FTHETA                   (*(volatile  int16* )(NFOC2_BASE + (103*2)))    // RV:0000H Feedback给估算器PI的角度
 #define NFOC2_IS                       (*(volatile  int16* )(NFOC2_BASE + (104*2)))    // RV:0000H IALPHA和IBETA计算幅值（平方和后开方）
 #define NFOC2_ITHETA                   (*(volatile  int16* )(NFOC2_BASE + (105*2)))    // RV:0000H IALPHA和IBETA计算角度
 #define NFOC2_ITFLT                    (*(volatile  int32* )(NFOC2_BASE + (106*2)))    // RV:0000H ITRIP滤波后的值（32位）
 #define NFOC2_ITFLTH                   (*(volatile  int16* )(NFOC2_BASE + (107*2)))    // RV:0000H ITRIP滤波后的值高16位
 #define NFOC2_ITRIP                    (*(volatile  int16* )(NFOC2_BASE + (108*2)))    // RV:0000H 采样ITRIP，用于功率计算
 #define NFOC2_POWER                    (*(volatile  int16* )(NFOC2_BASE + (109*2)))    // RV:0000H 功率值
 #define NFOC2_US                       (*(volatile  int16* )(NFOC2_BASE + (110*2)))    // RV:0000H UALPHA和UBETA计算幅值（平方和后开方）
 #define NFOC2_UTHETA                   (*(volatile  int16* )(NFOC2_BASE + (111*2)))    // RV:0000H UALPHA和UBETA计算角度
 
 #define NFOC2_ID0                      (*(volatile  int16* )(NFOC2_BASE + (122*2)))    // RV:0000H 上一次FOC计算的D轴电流
 #define NFOC2_IQ0                      (*(volatile  int16* )(NFOC2_BASE + (123*2)))    // RV:0000H 上一次FOC计算的Q轴电流
 #define NFOC2_DELIAL                   (*(volatile  int16* )(NFOC2_BASE + (124*2)))    // RV:0000H 高频电流      /* factory */
 #define NFOC2_DELIBE                   (*(volatile  int16* )(NFOC2_BASE + (125*2)))    // RV:0000H 高频电流      /* factory */
 #define NFOC2_HALPHA                   (*(volatile  int16* )(NFOC2_BASE + (126*2)))    // RV:0000H 高频电流包络
 #define NFOC2_HBETA                    (*(volatile  int16* )(NFOC2_BASE + (127*2)))    // RV:0000H 高频电流包络
 #define NFOC2_HS                       (*(volatile  int16* )(NFOC2_BASE + (138*2)))    // RV:0000H HALPHA和HBETA计算幅值（平方和后开方）      /* factory */
 #define NFOC2_HTHETA                   (*(volatile  int16* )(NFOC2_BASE + (139*2)))    // RV:0000H HALPHA和HBETA计算角度      /* factory */
 #define NFOC2_DELIQ                    (*(volatile  int16* )(NFOC2_BASE + (142*2)))    // RV:0000H 高频注入计算中间值
 
 #define NFOC2_HKP                      (*(volatile  int16* )(NFOC2_BASE + (112*2)))    // RV:0000H 高频注入PI KP
 #define NFOC2_HKI                      (*(volatile  int16* )(NFOC2_BASE + (113*2)))    // RV:0000H 高频注入PI KI
 #define NFOC2_HMAX                     (*(volatile  int16* )(NFOC2_BASE + (114*2)))    // RV:0000H 高频注入PI 上限值
 #define NFOC2_HMIN                     (*(volatile  int16* )(NFOC2_BASE + (115*2)))    // RV:0000H 高频注入PI 下限值
 #define NFOC2_HEK                      (*(volatile  int16* )(NFOC2_BASE + (116*2)))    // RV:0000H 高频注入PI EK
 #define NFOC2_HEK1                     (*(volatile  int16* )(NFOC2_BASE + (117*2)))    // RV:0000H 高频注入PI EK1
 #define NFOC2_HUK                      (*(volatile  int32* )(NFOC2_BASE + (118*2)))    // RV:0000H 高频注入PI UK（32位）
 #define NFOC2_HUKH                     (*(volatile  int16* )(NFOC2_BASE + (119*2)))    // RV:0000H 高频注入PI UK高16位
 #define NFOC2_DKP                      (*(volatile  int16* )(NFOC2_BASE + (128*2)))    // RV:0000H D轴PI电流环KP
 #define NFOC2_DKI                      (*(volatile  int16* )(NFOC2_BASE + (129*2)))    // RV:0000H D轴PI电流环KI
 #define NFOC2_DMAX                     (*(volatile  int16* )(NFOC2_BASE + (130*2)))    // RV:0000H D轴PI电流环上限值
 #define NFOC2_DMIN                     (*(volatile  int16* )(NFOC2_BASE + (131*2)))    // RV:0000H D轴PI电流环下限值
 #define NFOC2_DEK                      (*(volatile  int16* )(NFOC2_BASE + (132*2)))    // RV:0000H D轴PI电流环EK
 #define NFOC2_DEK1                     (*(volatile  int16* )(NFOC2_BASE + (133*2)))    // RV:0000H D轴PI电流环EK1
 #define NFOC2_DUK                      (*(volatile  int32* )(NFOC2_BASE + (134*2)))    // RV:0000H D轴PI电流环UK（32位）
 #define NFOC2_DUKH                     (*(volatile  int16* )(NFOC2_BASE + (135*2)))    // RV:0000H D轴PI电流环UK高16位
 // #define NFOC2_DEXC                    (*(volatile  int16* )(NFOC2_BASE + (136*2)))  // RV:0000H D轴PI电流环UK溢出值
 #define NFOC2_QKP                      (*(volatile  int16* )(NFOC2_BASE + (144*2)))    // RV:0000H Q轴PI电流环KP
 #define NFOC2_QKI                      (*(volatile  int16* )(NFOC2_BASE + (145*2)))    // RV:0000H Q轴PI电流环KI
 #define NFOC2_QMAX                     (*(volatile  int16* )(NFOC2_BASE + (146*2)))    // RV:0000H Q轴PI电流环上限值
 #define NFOC2_QMIN                     (*(volatile  int16* )(NFOC2_BASE + (147*2)))    // RV:0000H Q轴PI电流环下限值
 #define NFOC2_QEK                      (*(volatile  int16* )(NFOC2_BASE + (148*2)))    // RV:0000H Q轴PI电流环EK
 #define NFOC2_QEK1                     (*(volatile  int16* )(NFOC2_BASE + (149*2)))    // RV:0000H Q轴PI电流环EK1
 #define NFOC2_QUK                      (*(volatile  int32* )(NFOC2_BASE + (150*2)))    // RV:0000H Q轴PI电流环UK（32位）
 #define NFOC2_QUKH                     (*(volatile  int16* )(NFOC2_BASE + (151*2)))    // RV:0000H Q轴PI电流环UK高16位
 // #define NFOC2_QEXC                      (*(volatile  int16* )(NFOC2_BASE + (152*2)))  // RV:0000H Q轴PI电流环UK溢出值
  
 #define NFOC2_IRLOW                    (*(volatile  int16* )(NFOC2_BASE + (8*2)))      // RV:0000H 电流基准下限，超出后报基准异常
 #define NFOC2_IRUPP                    (*(volatile  int16* )(NFOC2_BASE + (9*2)))      // RV:0000H 电流基准上限，超出后报基准异常
  
 #define NFOC2_EKP                      (*(volatile  int16* )(NFOC2_BASE + (160*2)))    // RV:0000H 估算器PI电流环KP
 #define NFOC2_EKI                      (*(volatile  int16* )(NFOC2_BASE + (161*2)))    // RV:0000H 估算器PI电流环KI
 #define NFOC2_EMAX                     (*(volatile  int16* )(NFOC2_BASE + (162*2)))    // RV:0000H 估算器PI电流环上限值
 #define NFOC2_EMIN                     (*(volatile  int16* )(NFOC2_BASE + (163*2)))    // RV:0000H 估算器PI电流环下限值
 #define NFOC2_EEK                      (*(volatile  int16* )(NFOC2_BASE + (164*2)))    // RV:0000H 估算器PI电流环EK
 #define NFOC2_EEK1                     (*(volatile  int16* )(NFOC2_BASE + (165*2)))    // RV:0000H 估算器PI电流环EK1
 #define NFOC2_EUK                      (*(volatile  int32* )(NFOC2_BASE + (166*2)))    // RV:0000H 估算器PI电流环UK（32位）
 #define NFOC2_EUKH                     (*(volatile  int16* )(NFOC2_BASE + (167*2)))    // RV:0000H 估算器PI电流环UK高16位
 // #define NFOC2_EEXC                     (*(volatile  int16* )(NFOC2_BASE + (168*2)))  // RV:0000H 估算器PI电流环UK溢出值
 
 #define NFOC2_LKSMIN                   (*(volatile  int16* )(NFOC2_BASE + (16*2)))     // RV:0000H LOCK0对应的最小堵转速度
 #define NFOC2_LKSMAX                   (*(volatile  int16* )(NFOC2_BASE + (17*2)))     // RV:0000H LOCK1对应的最大堵转速度
 #define NFOC2_LOCKK                    (*(volatile  int16* )(NFOC2_BASE + (18*2)))     // RV:0000H LOCK2对应的速度和EMF的倍数Q8格式
 #define NFOC2_LKARR                    (*(volatile uint16* )(NFOC2_BASE + (20*2)))     // RV:0000H 堵转次数目标值
 #define NFOC2_LKCNT                    (*(volatile uint16* )(NFOC2_BASE + (21*2)))     // RV:0000H 堵转次数计数值，3者共用，一次判断3个都成立只+1
     
 #define NFOC2_WKP                      (*(volatile  int16* )(NFOC2_BASE + (176*2)))     // RV:0000H 外环PI电流环KP
 #define NFOC2_WKI                      (*(volatile  int16* )(NFOC2_BASE + (177*2)))     // RV:0000H 外环PI电流环KI
 #define NFOC2_WMAX                     (*(volatile  int16* )(NFOC2_BASE + (178*2)))     // RV:0000H 外环PI电流环上限值
 #define NFOC2_WMIN                     (*(volatile  int16* )(NFOC2_BASE + (179*2)))     // RV:0000H 外环PI电流环下限值
 #define NFOC2_WEK                      (*(volatile  int16* )(NFOC2_BASE + (180*2)))     // RV:0000H 外环PI电流环EK
 #define NFOC2_WEK1                     (*(volatile  int16* )(NFOC2_BASE + (181*2)))     // RV:0000H 外环PI电流环EK1
 #define NFOC2_WUK                      (*(volatile  int32* )(NFOC2_BASE + (182*2)))     // RV:0000H 外环PI电流环UK（32位）
 #define NFOC2_WUKH                     (*(volatile  int16* )(NFOC2_BASE + (183*2)))     // RV:0000H 外环PI电流环UK高16位
 // #define NFOC2_WEXC                     (*(volatile  int16* )(NFOC2_BASE + (184*2)))  // RV:0000H 外环PI电流环UK溢出值
 
 #define NFOC2_FWKP                     (*(volatile  int16* )(NFOC2_BASE + (192*2)))     // RV:0000H 弱磁PI KP
 #define NFOC2_FWKI                     (*(volatile  int16* )(NFOC2_BASE + (193*2)))     // RV:0000H 弱磁PI KI
 #define NFOC2_FWMAX                    (*(volatile  int16* )(NFOC2_BASE + (194*2)))     // RV:0000H 弱磁PI 上限值
 #define NFOC2_FWMIN                    (*(volatile  int16* )(NFOC2_BASE + (195*2)))     // RV:0000H 弱磁PI 下限值
 #define NFOC2_FWEK                     (*(volatile  int16* )(NFOC2_BASE + (196*2)))     // RV:0000H 弱磁PI EK
 #define NFOC2_FWEK1                    (*(volatile  int16* )(NFOC2_BASE + (197*2)))     // RV:0000H 弱磁PI EK1
 #define NFOC2_FWUK                     (*(volatile  int32* )(NFOC2_BASE + (198*2)))     // RV:0000H 弱磁PI UK（32位）
 #define NFOC2_FWUKH                    (*(volatile  int16* )(NFOC2_BASE + (199*2)))     // RV:0000H 弱磁PI UK高16位
 // #define NFOC2_FWEXC                      (*(volatile  int16* )(NFOC2_BASE + (200*2)))  // RV:0000H 弱磁PI UK溢出值
 
 #define NFOC2_OVP                      (*(volatile  int16* )(NFOC2_BASE + (10*2)))      // RV:0000H 过压阈值
 #define NFOC2_OVPARR                   (*(volatile uint8*  )(NFOC2_BASE + (11*2)))      // RV:00H   过压次数目标值（8位）
 #define NFOC2_OVPCNT                   (*(volatile uint8*  )(NFOC2_BASE + (11*2+1)))    // RV:00H   过压次数计数值（8位）
 #define NFOC2_UVP                      (*(volatile  int16* )(NFOC2_BASE + (12*2)))      // RV:0000H 欠压阈值
 #define NFOC2_UVPARR                   (*(volatile uint8*  )(NFOC2_BASE + (13*2)))      // RV:00H   欠压次数目标值（8位）
 #define NFOC2_UVPCNT                   (*(volatile uint8*  )(NFOC2_BASE + (13*2+1)))    // RV:00H   欠压次数计数值（8位）
 #define NFOC2_SOCP                     (*(volatile  int16* )(NFOC2_BASE + (14*2)))      // RV:0000H 软件过流阈值
 #define NFOC2_SOCPARR                  (*(volatile uint8*  )(NFOC2_BASE + (15*2)))      // RV:00H   软件过流次数目标值（8位）
 #define NFOC2_SOCPCNT                  (*(volatile uint8*  )(NFOC2_BASE + (15*2+1)))    // RV:00H   软件过流次数计数值（8位）
 
 #define NFOC2_TS                       (*(volatile  int16* )(NFOC2_BASE + (316*2)))     // RV:0000H 单电阻移相/双/三电阻最小采样脉宽[0,32767]
 #define NFOC2_NTS                      (*(volatile  int16* )(NFOC2_BASE + (317*2)))     // RV:0000H 三电阻脉宽屏蔽/新单电阻最小脉宽[0,1023]
 #define NFOC2_TDLY                     (*(volatile  int16* )(NFOC2_BASE + (318*2)))     // RV:0000H 电流采样触发时机
 #define NFOC2_TDLYD                    (*(volatile  int16* )(NFOC2_BASE + (319*2)))     // RV:0000H 单电阻动态前后采样时机
 #define NFOC2_ARR                      (*(volatile uint16* )(NFOC2_BASE + (320*2)))     // RV:0000H FOC载波频率
 #define NFOC2_IDK                      (*(volatile  int16* )(NFOC2_BASE + (322*2)))     // RV:0000H ID滤波系数
 #define NFOC2_IQK                      (*(volatile  int16* )(NFOC2_BASE + (323*2)))     // RV:0000H IQ滤波系数
 #define NFOC2_OMEGAK                   (*(volatile  int16* )(NFOC2_BASE + (324*2)))     // RV:0000H Omega一级滤波系数
 #define NFOC2_OMEK2                    (*(volatile  int16* )(NFOC2_BASE + (325*2)))     // RV:0000H Omega二级滤波系数
 #define NFOC2_OMEACC                   (*(volatile  int32* )(NFOC2_BASE + (202*2)))     // RV:0000H OMEGA启动速度增量
 #define NFOC2_OMEEND                   (*(volatile  int32* )(NFOC2_BASE + (204*2)))     // RV:0000H OMEGA启动END值
 #define NFOC2_OMEENDH                  (*(volatile  int16* )(NFOC2_BASE + (205*2)))     // RV:0000H OMEGA启动END值
 #define NFOC2_OMEMIN                   (*(volatile  int16* )(NFOC2_BASE + (206*2)))     // RV:0000H OMEGA启动切换值
 #define NFOC2_FTCK                     (*(volatile  int16* )(NFOC2_BASE + (207*2)))     // RV:0000H 反馈角度动态补偿系数
 #define NFOC2_FBASE                    (*(volatile  int16* )(NFOC2_BASE + (208*2)))     // RV:0000H 速度基准
 #define NFOC2_OMEMI2                   (*(volatile  int16* )(NFOC2_BASE + (209*2)))     // RV:0000H KLPF对应的最小速度
 #define NFOC2_THECOM                   (*(volatile  int16* )(NFOC2_BASE + (210*2)))     // RV:0000H 输出角度的静态补偿角
 #define NFOC2_FTCOM                    (*(volatile  int16* )(NFOC2_BASE + (211*2)))     // RV:0000H 反馈角度的静态补偿角
 #define NFOC2_EK1                      (*(volatile  int16* )(NFOC2_BASE + (212*2)))     // RV:0000H FOC估算器参数1
 #define NFOC2_EK2                      (*(volatile  int16* )(NFOC2_BASE + (213*2)))     // RV:0000H FOC估算器参数3
 #define NFOC2_EK3                      (*(volatile  int16* )(NFOC2_BASE + (214*2)))     // RV:0000H FOC估算器参数2
 #define NFOC2_EK4                      (*(volatile  int16* )(NFOC2_BASE + (215*2)))     // RV:0000H FOC估算器参数4
 #define NFOC2_KSLIDE                   (*(volatile  int16* )(NFOC2_BASE + (216*2)))     // RV:0000H SMO系数
 #define NFOC2_MAXERR                   (*(volatile  int16* )(NFOC2_BASE + (217*2)))     // RV:0000H SMO限幅
 #define NFOC2_MERRRE                   (*(volatile  int16* )(NFOC2_BASE + (218*2)))     // RV:0000H SMO限幅倒数
 #define NFOC2_TDTC                     (*(volatile  int16* )(NFOC2_BASE + (219*2)))     // RV:0000H 双/三电阻死区补偿
 #define NFOC2_IDREF                    (*(volatile  int16* )(NFOC2_BASE + (220*2)))     // RV:0000H 给定D轴值
 #define NFOC2_IQREF                    (*(volatile  int16* )(NFOC2_BASE + (221*2)))     // RV:0000H 给定Q轴值
 #define NFOC2_IAREF                    (*(volatile  int16* )(NFOC2_BASE + (4*2)))       // RV:0000H U相电流基准
 #define NFOC2_IBREF                    (*(volatile  int16* )(NFOC2_BASE + (5*2)))       // RV:0000H V相电流基准
 #define NFOC2_ICREF                    (*(volatile  int16* )(NFOC2_BASE + (6*2)))       // RV:0000H W相电流基准
 #define NFOC2_ITREF                    (*(volatile  int16* )(NFOC2_BASE + (7*2)))       // RV:0000H 母线电流基准
 #define NFOC2_UDC                      (*(volatile  int16* )(NFOC2_BASE + (0*2)))       // RV:0000H 母线电压采样值
 #define NFOC2_UDCK                     (*(volatile  int16* )(NFOC2_BASE + (1*2)))       // RV:0000H 母线电压采样滤波系数
 #define NFOC2_UDCFLT                   (*(volatile  int32* )(NFOC2_BASE + (2*2)))       // RV:0000H 母线电压滤波后的值（32位）
 #define NFOC2_UDCFLTH                  (*(volatile  int16* )(NFOC2_BASE + (3*2)))       // RV:0000H 母线电压滤波后的值高16位
 #define NFOC2_UQCPS                    (*(volatile  int16* )(NFOC2_BASE + (231*2)))     // RV:0000H D轴的电压补偿值
 #define NFOC2_UDCPS                    (*(volatile  int16* )(NFOC2_BASE + (230*2)))     // RV:0000H Q轴的电压补偿值
 #define NFOC2_WREF                     (*(volatile  int16* )(NFOC2_BASE + (232*2)))     // RV:0000H 外环参考值[0~32767]
 #define NFOC2_WFDB                     (*(volatile  int16* )(NFOC2_BASE + (233*2)))     // RV:0000H 外环反馈值
 #define NFOC2_ITK                      (*(volatile  int16* )(NFOC2_BASE + (234*2)))     // RV:0000H ITRIP滤波系数
 #define NFOC2_POWK                     (*(volatile  int16* )(NFOC2_BASE + (235*2)))     // RV:0000H POWER滤波系数（两个8位）POWER = (ITRIP*K1)*(UDC*K2)
 #define NFOC2_FGBASE                   (*(volatile  int16* )(NFOC2_BASE + (236*2)))     // RV:0000H FG计算速度基准
 
 #define NFOC2_UALCPS                   (*(volatile  int16* )(NFOC2_BASE + (238*2)))     // RV:0000H UALPHA的电压补偿值
 #define NFOC2_UBECPS                   (*(volatile  int16* )(NFOC2_BASE + (239*2)))     // RV:0000H UBETA的电压补偿值
 #define NFOC2_NCURR                    (*(volatile  int16* )(NFOC2_BASE + (22*2)))      // RV:0000H 缺相检测电流设置
 #define NFOC2_PLK                      (*(volatile  int16* )(NFOC2_BASE + (23*2)))      // RV:0000H 缺相检测电流倍数系数
 
 #define NFOC2_RATAR                    (*(volatile  int16* )(NFOC2_BASE + (242*2)))     // RV:0000H 用户填入的爬坡目标值
 #define NFOC2_RAOUT                    (*(volatile  int16* )(NFOC2_BASE + (243*2)))     // RV:0000H 爬坡后的输出值
 #define NFOC2_RAINC                    (*(volatile  int16* )(NFOC2_BASE + (244*2)))     // RV:0000H 向上增加的步进值
 #define NFOC2_RADEC                    (*(volatile  int16* )(NFOC2_BASE + (245*2)))     // RV:0000H 向下减少的步进值
 #define NFOC2_LK1                      (*(volatile  int16* )(NFOC2_BASE + (246*2)))     // RV:0000H 低速观测器系数
 #define NFOC2_LK2                      (*(volatile  int16* )(NFOC2_BASE + (247*2)))     // RV:0000H 低速观测器系数
 #define NFOC2_LK3                      (*(volatile  int16* )(NFOC2_BASE + (248*2)))     // RV:0000H 低速观测器系数
 #define NFOC2_LK4                      (*(volatile  int16* )(NFOC2_BASE + (249*2)))     // RV:0000H 低速观测器系数   
 #define NFOC2_LK5                      (*(volatile  int16* )(NFOC2_BASE + (250*2)))     // RV:0000H 低速观测器系数   
 #define NFOC2_LK6                      (*(volatile  int16* )(NFOC2_BASE + (251*2)))     // RV:0000H 低速观测器系数   
 #define NFOC2_LED                      (*(volatile  int16* )(NFOC2_BASE + (252*2)))     // RV:0000H 低速观测器系数
 #define NFOC2_LEQ                      (*(volatile  int16* )(NFOC2_BASE + (253*2)))     // RV:0000H 低速观测器系数
 #define NFOC2_LOME                     (*(volatile  int32* )(NFOC2_BASE + (254*2)))     // RV:0000H 低速观测器速度
 #define NFOC2_LOMEH                    (*(volatile  int16* )(NFOC2_BASE + (255*2)))     // RV:0000H 低速观测器速度
 #define NFOC2_XALPHA                   (*(volatile  int32* )(NFOC2_BASE + (276*2)))     // RV:0000H 磁链观测器计算中间值      /* factory */
 #define NFOC2_XALPHAH                  (*(volatile  int16* )(NFOC2_BASE + (277*2)))     // RV:0000H 磁链观测器计算中间值      /* factory */
 #define NFOC2_XBETA                    (*(volatile  int32* )(NFOC2_BASE + (278*2)))     // RV:0000H 磁链观测器计算中间值      /* factory */
 #define NFOC2_XBETAH                   (*(volatile  int16* )(NFOC2_BASE + (279*2)))     // RV:0000H 磁链观测器计算中间值      /* factory */
 #define NFOC2_ETALPHA                  (*(volatile  int16* )(NFOC2_BASE + (298*2)))     // RV:0000H 磁链观测器计算中间值      /* factory */
 #define NFOC2_ETBETA                   (*(volatile  int16* )(NFOC2_BASE + (299*2)))     // RV:0000H 磁链观测器计算中间值      /* factory */
 #define NFOC2_UABT                     (*(volatile  int16* )(NFOC2_BASE + (280*2)))     // RV:0000H 磁链观测器计算中间值      /* factory */
 #define NFOC2_HEK0                     (*(volatile  int16* )(NFOC2_BASE + (282*2)))     // RV:0000H 磁链观测器计算中间值
 #define NFOC2_PSI                      (*(volatile  int16* )(NFOC2_BASE + (283*2)))     // RV:0000H 磁链观测器计算中间值
 #define NFOC2_UIK0                     (*(volatile  int16* )(NFOC2_BASE + (284*2)))     // RV:0000H UQ补偿的倍频系数
 #define NFOC2_UIK1                     (*(volatile  int16* )(NFOC2_BASE + (285*2)))     // RV:0000H UQ补偿的倍频系数
 #define NFOC2_UIK2                     (*(volatile  int16* )(NFOC2_BASE + (286*2)))     // RV:0000H UQ补偿的倍频系数
 #define NFOC2_UIK3                     (*(volatile  int16* )(NFOC2_BASE + (287*2)))     // RV:0000H UQ补偿的倍频系数
 #define NFOC2_UITC0                    (*(volatile  int16* )(NFOC2_BASE + (288*2)))     // RV:0000H UQ补偿的角度相移
 #define NFOC2_UIUS0                    (*(volatile  int16* )(NFOC2_BASE + (289*2)))     // RV:0000H UQ补偿的幅值
 #define NFOC2_UITC1                    (*(volatile  int16* )(NFOC2_BASE + (290*2)))     // RV:0000H UQ补偿的角度相移
 #define NFOC2_UIUS1                    (*(volatile  int16* )(NFOC2_BASE + (291*2)))     // RV:0000H UQ补偿的幅值
 #define NFOC2_UITC2                    (*(volatile  int16* )(NFOC2_BASE + (292*2)))     // RV:0000H UQ补偿的角度相移
 #define NFOC2_UIUS2                    (*(volatile  int16* )(NFOC2_BASE + (293*2)))     // RV:0000H UQ补偿的幅值
 #define NFOC2_UITC3                    (*(volatile  int16* )(NFOC2_BASE + (294*2)))     // RV:0000H UQ补偿的角度相移
 #define NFOC2_UIUS3                    (*(volatile  int16* )(NFOC2_BASE + (295*2)))     // RV:0000H UQ补偿的幅值
 #define NFOC2_TRG1                     (*(volatile  int16* )(NFOC2_BASE + (296*2)))     // RV:0000H I1采样点对应DR值
 #define NFOC2_TRG2                     (*(volatile  int16* )(NFOC2_BASE + (297*2)))     // RV:0000H I2采样点对应DR值
 
 #define NFOC2_OTHETA                   (*(volatile  int32* )(NFOC2_BASE + (300*2)))     // RV:0000H 估算器估算角度（32位）
 #define NFOC2_OTHETAH                  (*(volatile  int16* )(NFOC2_BASE + (301*2)))     // RV:0000H 估算器角度高16位
 
 #define NFOC2_USK                      (*(volatile  int16* )(NFOC2_BASE + (302*2)))     // RV:0000H 相电压采样值系数
 #define NFOC2_UA                       (*(volatile  int16* )(NFOC2_BASE + (303*2)))     // RV:0000H A相电压采样值
 #define NFOC2_UB                       (*(volatile  int16* )(NFOC2_BASE + (304*2)))     // RV:0000H B相电压采样值
 #define NFOC2_UC                       (*(volatile  int16* )(NFOC2_BASE + (305*2)))     // RV:0000H C相电压采样值
 #define NFOC2_USAL1                    (*(volatile  int16* )(NFOC2_BASE + (306*2)))     // RV:0000H UA、UB、UC计算的USALPHA值
 #define NFOC2_USBE1                    (*(volatile  int16* )(NFOC2_BASE + (307*2)))     // RV:0000H UA、UB、UC计算的USBETA值
 
 
 #define NFOC2_DELOTHE                  (*(volatile  int32* )(NFOC2_BASE + (326*2)))     // RV:0000H 估算器估算角度（32位）
 #define NFOC2_DELOTHEH                 (*(volatile  int16* )(NFOC2_BASE + (327*2)))     // RV:0000H 估算器估算角度
 #define NFOC2_DELETHE                  (*(volatile  int32* )(NFOC2_BASE + (328*2)))     // RV:0000H 估算器估算角度（32位）
 #define NFOC2_DELETHEH                 (*(volatile  int16* )(NFOC2_BASE + (329*2)))     // RV:0000H 估算器估算角度
 #define NFOC2_IG0                      (*(volatile  int16* )(NFOC2_BASE + (310*2)))     // RV:0000H 高频注入计算中间值      /* factory */
 #define NFOC2_IF0                      (*(volatile  int16* )(NFOC2_BASE + (311*2)))     // RV:0000H 高频注入计算中间值      /* factory */
 #define NFOC2_HUCPS                    (*(volatile  int16* )(NFOC2_BASE + (312*2)))     // RV:0000H 高频注入计算中间值      /* factory */
 #define NFOC2_HCTHE                    (*(volatile  int16* )(NFOC2_BASE + (313*2)))     // RV:0000H 高频注入计算中间值      /* factory */
 #define NFOC2_FWREF                    (*(volatile  int16* )(NFOC2_BASE + (314*2)))     // RV:0000H 弱磁PI给定值
 #define NFOC2_UDCD                     (*(volatile  int16* )(NFOC2_BASE + (330*2)))     // RV:0000H d轴UDC值
 #define NFOC2_UDCQ                     (*(volatile  int16* )(NFOC2_BASE + (331*2)))     // RV:0000H q轴UDC值
 
 #define NFOC2_IQMAX                    (*(volatile uint16* )(NFOC2_BASE + (332*2)))     // RV:0000H IQREF最大值
 #define NFOC2_IQMIN                    (*(volatile uint16* )(NFOC2_BASE + (333*2)))     // RV:0000H IQREF最小值
 
 #define NFOC2_WUCPS                    (*(volatile  int16* )(NFOC2_BASE + (414*2)))     // RV:0000H 外环补偿值
 #define NFOC2_WUFIN                    (*(volatile  int16* )(NFOC2_BASE + (415*2)))     // RV:0000H 外环最终值
 
 #define NFOC2_OSCNT                    (*(volatile  int16* )(NFOC2_BASE + (447*2)))     // RV:0000H OFFSET校准计数值
 #define NFOC2_OSSUM                    (*(volatile  int32* )(NFOC2_BASE + (448*2)))     // RV:0000H OFFSET校准和

 #define NFOC2_F1LB0                    (*(volatile uint16* )(NFOC2_BASE + (334*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC2_F1HB0                    (*(volatile uint16* )(NFOC2_BASE + (335*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC2_F1LB1                    (*(volatile uint16* )(NFOC2_BASE + (336*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC2_F1LB2                    (*(volatile uint16* )(NFOC2_BASE + (337*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC2_F1LA1                    (*(volatile uint16* )(NFOC2_BASE + (338*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC2_F1LA2                    (*(volatile uint16* )(NFOC2_BASE + (339*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC2_F1HB1                    (*(volatile uint16* )(NFOC2_BASE + (340*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC2_F1HB2                    (*(volatile uint16* )(NFOC2_BASE + (341*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC2_F1HA1                    (*(volatile uint16* )(NFOC2_BASE + (342*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC2_F1HA2                    (*(volatile uint16* )(NFOC2_BASE + (343*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC2_F1X0                     (*(volatile uint16* )(NFOC2_BASE + (344*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC2_F1X1                     (*(volatile uint16* )(NFOC2_BASE + (346*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC2_F1X2                     (*(volatile uint16* )(NFOC2_BASE + (347*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC2_F1Y1                     (*(volatile uint16* )(NFOC2_BASE + (348*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC2_F1Y2                     (*(volatile uint16* )(NFOC2_BASE + (349*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC2_F1Z1                     (*(volatile uint16* )(NFOC2_BASE + (350*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC2_F1Z2                     (*(volatile uint16* )(NFOC2_BASE + (351*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC2_F1Y                      (*(volatile uint32* )(NFOC2_BASE + (352*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC2_F1YH                     (*(volatile uint16* )(NFOC2_BASE + (353*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC2_F1U1                     (*(volatile uint16* )(NFOC2_BASE + (416*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC2_F1U2                     (*(volatile uint16* )(NFOC2_BASE + (417*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC2_F1YG                     (*(volatile uint32* )(NFOC2_BASE + (424*2)))     // RV:0000H IQREF滤波器参数      /* factory */
 #define NFOC2_F1YD                     (*(volatile uint32* )(NFOC2_BASE + (426*2)))     // RV:0000H IQREF滤波器参数      /* factory */

 #define NFOC2_F2LB0                    (*(volatile uint16* )(NFOC2_BASE + (354*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC2_F2HB0                    (*(volatile uint16* )(NFOC2_BASE + (355*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC2_F2LB1                    (*(volatile uint16* )(NFOC2_BASE + (356*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC2_F2LB2                    (*(volatile uint16* )(NFOC2_BASE + (357*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC2_F2LA1                    (*(volatile uint16* )(NFOC2_BASE + (358*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC2_F2LA2                    (*(volatile uint16* )(NFOC2_BASE + (359*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC2_F2HB1                    (*(volatile uint16* )(NFOC2_BASE + (360*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC2_F2HB2                    (*(volatile uint16* )(NFOC2_BASE + (361*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC2_F2HA1                    (*(volatile uint16* )(NFOC2_BASE + (362*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC2_F2HA2                    (*(volatile uint16* )(NFOC2_BASE + (363*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC2_F2X0                     (*(volatile uint16* )(NFOC2_BASE + (364*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC2_F2X1                     (*(volatile uint16* )(NFOC2_BASE + (366*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC2_F2X2                     (*(volatile uint16* )(NFOC2_BASE + (367*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC2_F2Y1                     (*(volatile uint16* )(NFOC2_BASE + (368*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC2_F2Y2                     (*(volatile uint16* )(NFOC2_BASE + (369*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC2_F2Z1                     (*(volatile uint16* )(NFOC2_BASE + (370*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC2_F2Z2                     (*(volatile uint16* )(NFOC2_BASE + (371*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC2_F2HY                     (*(volatile uint32* )(NFOC2_BASE + (372*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC2_F2U1                     (*(volatile uint16* )(NFOC2_BASE + (418*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC2_F2U2                     (*(volatile uint16* )(NFOC2_BASE + (419*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC2_F2YG                     (*(volatile uint32* )(NFOC2_BASE + (428*2)))     // RV:0000H IQREF滤波器参数      /* factory */
 #define NFOC2_F2YD                     (*(volatile uint32* )(NFOC2_BASE + (430*2)))     // RV:0000H IQREF滤波器参数      /* factory */
 
 #define NFOC2_F3LB0                    (*(volatile uint16* )(NFOC2_BASE + (374*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC2_F3HB0                    (*(volatile uint16* )(NFOC2_BASE + (375*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC2_F3LB1                    (*(volatile uint16* )(NFOC2_BASE + (376*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC2_F3LB2                    (*(volatile uint16* )(NFOC2_BASE + (377*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC2_F3LA1                    (*(volatile uint16* )(NFOC2_BASE + (378*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC2_F3LA2                    (*(volatile uint16* )(NFOC2_BASE + (379*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC2_F3HB1                    (*(volatile uint16* )(NFOC2_BASE + (380*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC2_F3HB2                    (*(volatile uint16* )(NFOC2_BASE + (381*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC2_F3HA1                    (*(volatile uint16* )(NFOC2_BASE + (382*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC2_F3HA2                    (*(volatile uint16* )(NFOC2_BASE + (383*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC2_F3X0                     (*(volatile uint16* )(NFOC2_BASE + (384*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC2_F3X1                     (*(volatile uint16* )(NFOC2_BASE + (386*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC2_F3X2                     (*(volatile uint16* )(NFOC2_BASE + (387*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC2_F3Y1                     (*(volatile uint16* )(NFOC2_BASE + (388*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC2_F3Y2                     (*(volatile uint16* )(NFOC2_BASE + (389*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC2_F3Z1                     (*(volatile uint16* )(NFOC2_BASE + (390*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC2_F3Z2                     (*(volatile uint16* )(NFOC2_BASE + (391*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC2_F3HY                     (*(volatile uint32* )(NFOC2_BASE + (392*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC2_F3U1                     (*(volatile uint16* )(NFOC2_BASE + (420*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC2_F3U2                     (*(volatile uint16* )(NFOC2_BASE + (421*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC2_F3YG                     (*(volatile uint32* )(NFOC2_BASE + (432*2)))     // RV:0000H IQREF滤波器参数      /* factory */
 #define NFOC2_F3YD                     (*(volatile uint32* )(NFOC2_BASE + (434*2)))     // RV:0000H IQREF滤波器参数      /* factory */
 
 #define NFOC2_F4LB0                    (*(volatile uint16* )(NFOC2_BASE + (394*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC2_F4HB0                    (*(volatile uint16* )(NFOC2_BASE + (395*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC2_F4LB1                    (*(volatile uint16* )(NFOC2_BASE + (396*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC2_F4LB2                    (*(volatile uint16* )(NFOC2_BASE + (397*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC2_F4LA1                    (*(volatile uint16* )(NFOC2_BASE + (398*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC2_F4LA2                    (*(volatile uint16* )(NFOC2_BASE + (399*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC2_F4HB1                    (*(volatile uint16* )(NFOC2_BASE + (400*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC2_F4HB2                    (*(volatile uint16* )(NFOC2_BASE + (401*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC2_F4HA1                    (*(volatile uint16* )(NFOC2_BASE + (402*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC2_F4HA2                    (*(volatile uint16* )(NFOC2_BASE + (403*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC2_F4X0                     (*(volatile uint16* )(NFOC2_BASE + (404*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC2_F4X1                     (*(volatile uint16* )(NFOC2_BASE + (406*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC2_F4X2                     (*(volatile uint16* )(NFOC2_BASE + (407*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC2_F4Y1                     (*(volatile uint16* )(NFOC2_BASE + (408*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC2_F4Y2                     (*(volatile uint16* )(NFOC2_BASE + (409*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC2_F4Z1                     (*(volatile uint16* )(NFOC2_BASE + (410*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC2_F4Z2                     (*(volatile uint16* )(NFOC2_BASE + (411*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC2_F4HY                     (*(volatile uint32* )(NFOC2_BASE + (412*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC2_F4U1                     (*(volatile uint16* )(NFOC2_BASE + (422*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC2_F4U2                     (*(volatile uint16* )(NFOC2_BASE + (423*2)))     // RV:0000H IQREF滤波器参数
 #define NFOC2_F4YG                     (*(volatile uint32* )(NFOC2_BASE + (436*2)))     // RV:0000H IQREF滤波器参数      /* factory */
 #define NFOC2_F4YD                     (*(volatile uint32* )(NFOC2_BASE + (438*2)))     // RV:0000H IQREF滤波器参数      /* factory */

 #define NFOC2_XI0                      (*(volatile  int16* )(NFOC2_BASE + (24*2)))     // RV:0000H CORDIC4 SIN/COS计算的X轴输入
 #define NFOC2_YI0                      (*(volatile  int16* )(NFOC2_BASE + (25*2)))     // RV:0000H CORDIC4 SIN/COS计算的y轴输入
 #define NFOC2_THETA0                   (*(volatile  int16* )(NFOC2_BASE + (27*2)))     // RV:0000H CORDIC4 SIN/COS计算的角度输入
 #define NFOC2_XO0                      (*(volatile  int16* )(NFOC2_BASE + (28*2)))     // RV:0000H CORDIC4 SIN/COS计算的X轴输出
 #define NFOC2_YO0                      (*(volatile  int16* )(NFOC2_BASE + (29*2)))     // RV:0000H CORDIC4 SIN/COS计算的y轴输出
 #define NFOC2_XI1                      (*(volatile  int16* )(NFOC2_BASE + (30*2)))     // RV:0000H CORDIC5 SIN/COS计算的X轴输入
 #define NFOC2_YI1                      (*(volatile  int16* )(NFOC2_BASE + (31*2)))     // RV:0000H CORDIC5 SIN/COS计算的y轴输入
 #define NFOC2_THETA1                   (*(volatile  int16* )(NFOC2_BASE + (33*2)))     // RV:0000H CORDIC5 SIN/COS计算的角度输入
 #define NFOC2_XO51                     (*(volatile  int16* )(NFOC2_BASE + (34*2)))     // RV:0000H CORDIC5 SIN/COS计算的X轴输出
 #define NFOC2_YO1                      (*(volatile  int16* )(NFOC2_BASE + (35*2)))     // RV:0000H CORDIC5 SIN/COS计算的y轴输出
 #define NFOC2_XI2                      (*(volatile  int16* )(NFOC2_BASE + (36*2)))     // RV:0000H CORDIC6 ATAN计算的X轴输入
 #define NFOC2_YI2                      (*(volatile  int16* )(NFOC2_BASE + (37*2)))     // RV:0000H CORDIC6 ATAN计算的y轴输入
 #define NFOC2_US2                      (*(volatile  int16* )(NFOC2_BASE + (38*2)))     // RV:0000H CORDIC6 ATAN计算的幅值输出
 #define NFOC2_THETA2                   (*(volatile  int16* )(NFOC2_BASE + (39*2)))     // RV:0000H CORDIC6 ATAN计算的角度输出
 #define NFOC2_XI3                      (*(volatile  int16* )(NFOC2_BASE + (40*2)))     // RV:0000H CORDIC7 ATAN计算的X轴输入
 #define NFOC2_YI3                      (*(volatile  int16* )(NFOC2_BASE + (41*2)))     // RV:0000H CORDIC7 ATAN计算的y轴输入
 #define NFOC2_US3                      (*(volatile  int16* )(NFOC2_BASE + (42*2)))     // RV:0000H CORDIC7 ATAN计算的幅值输出
 #define NFOC2_THETA3                   (*(volatile  int16* )(NFOC2_BASE + (43*2)))     // RV:0000H CORDIC7 ATAN计算的角度输出

 #define NFOC_PDCMD						(*(volatile  int16* )(NFOC2_BASE + (228*2)))     // RV:0000H PDFF设定目标值
 #define NFOC_PDACT						(*(volatile  int16* )(NFOC2_BASE + (229*2)))     // RV:0000H PDFF设定反馈值
 #define NFOC_PDKP						(*(volatile  int16* )(NFOC2_BASE + (230*2)))     // RV:0000H PDFF系数KP
 #define NFOC_PDKI						(*(volatile  int16* )(NFOC2_BASE + (231*2)))     // RV:0000H PDFF系数KI
 #define NFOC_PDKF						(*(volatile  int16* )(NFOC2_BASE + (232*2)))     // RV:0000H PDFF系数KF
 #define NFOC_PDISAT					(*(volatile  int16* )(NFOC2_BASE + (233*2)))     // RV:0000H PDFF积分上限值
 #define NFOC_PDITMP					(*(volatile  int32* )(NFOC2_BASE + (234*2)))     // RV:0000H PDFF积分值(32bit)
 #define NFOC_PDMAX						(*(volatile  int16* )(NFOC2_BASE + (236*2)))     // RV:0000H PDFF输出限幅最大值
 #define NFOC_PDMIN						(*(volatile  int16* )(NFOC2_BASE + (237*2)))     // RV:0000H PDFF输出限幅最小值
 #define NFOC_PDUK						(*(volatile  int16* )(NFOC2_BASE + (238*2)))     // RV:0000H PDFF输出

 #define NFOC_SFIN                      (*(volatile  int16* )(NFOC2_BASE + (240*2)))     // RV:0000H 速度滤波器输入
 #define NFOC_SFOUT						(*(volatile  int16* )(NFOC2_BASE + (241*2)))     // RV:0000H 速度滤波器输出

 #define NFOC_SLF1IN					(*(volatile  int16* )(NFOC2_BASE + (242*2)))     // RV:0000H 低通滤波器1输入
 #define NFOC_SLF1K						(*(volatile  int16* )(NFOC2_BASE + (243*2)))     // RV:0000H 低通滤波器1系数
 #define NFOC_SLFLT1                    (*(volatile  int32* )(NFOC2_BASE + (244*2)))     // RV:0000H 低通滤波器1输出(32bit)
 #define NFOC_SLF2IN					(*(volatile  int16* )(NFOC2_BASE + (246*2)))     // RV:0000H 低通滤波器2输入
 #define NFOC_SLF2K						(*(volatile  int16* )(NFOC2_BASE + (247*2)))     // RV:0000H 低通滤波器2系数
 #define NFOC_SLFLT2                    (*(volatile  int32* )(NFOC2_BASE + (248*2)))     // RV:0000H 低通滤波器2输出(32bit)


 #define NFOC_SMFPNT                    (*(volatile  uint8* )(NFOC2_BASE + (250*2)))     // RV:00H 滑动均值滤波器缓存索引（8bit）
 #define NFOC_SMFSIZE                   (*(volatile  uint8* )(NFOC2_BASE + (250*2+1)))   // RV:00H 滑动均值滤波器大小（0~8）
 #define NFOC_SMFIN                     (*(volatile  int16* )(NFOC2_BASE + (251*2)))     // RV:0000H 滑动均值滤波器输入
 #define NFOC_SMFSUM                    (*(volatile  int32* )(NFOC2_BASE + (252*2)))     // RV:0000H 滑动均值滤波器和（32bit）
 #define NFOC_SMFREM                    (*(volatile  int16* )(NFOC2_BASE + (254*2)))     // RV:0000H 滑动均值滤波器余数
 #define NFOC_SMFOUT                    (*(volatile  int16* )(NFOC2_BASE + (255*2)))     // RV:0000H 滑动均值滤波器输出
 #define NFOC_SMFARR0                   (*(volatile  int16* )(NFOC2_BASE + (256*2)))     // RV:0000H 滑动均值滤波器缓存0
 #define NFOC_SMFARR255                 (*(volatile  int16* )(NFOC2_BASE + (511*2)))     // RV:0000H 滑动均值滤波器缓存255
 

#endif
