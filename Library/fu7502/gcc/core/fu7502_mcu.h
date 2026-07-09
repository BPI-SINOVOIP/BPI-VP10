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
 #define PA                             (GPIOA_BASE   + 0x00)                   // RV:      00H    PortA register
 #define PA_OE                          (GPIOA_BASE   + 0x01)                   // RV:      00H    PA output enable register
 #define PA_PU                          (GPIOA_BASE   + 0x02)                   // RV:      00H    PA pull-up enable register
 #define PA_PL                          (GPIOA_BASE   + 0x03)                   // RV:      00H    PA pull-down enable register
 #define PB                             (GPIOB_BASE   + 0x00)                   // RV:      00H    PortB register
 #define PB_OE                          (GPIOB_BASE   + 0x01)                   // RV:      00H    PB output enable register
 #define PB_PU                          (GPIOB_BASE   + 0x02)                   // RV:      00H    PB pull-up enable register
 #define PB_AN                          (GPIOB_BASE   + 0x03)                   // RV:      00H    PB analog enable register
 #define PC                             (GPIOC_BASE   + 0x00)                   // RV:      00H    PortC register
 #define PC_OE                          (GPIOC_BASE   + 0x01)                   // RV:      00H    PC output enable register
 #define PC_PU                          (GPIOC_BASE   + 0x02)                   // RV:      00H    PC pull-up enable register
 #define PC_AN                          (GPIOC_BASE   + 0x03)                   // RV:      00H    PC analog enable register
 #define PD                             (GPIOD_BASE   + 0x00)                   // RV:      00H    PortD register
 #define PD_OE                          (GPIOD_BASE   + 0x01)                   // RV:      00H    PD output enable register
 #define PD_PU                          (GPIOD_BASE   + 0x02)                   // RV:      00H    PD pull-up enable register
 #define PD_AN                          (GPIOD_BASE   + 0x03)                   // RV:      00H    PD analog enable register
 #define PH_SEL                         (PHSEL_BASE   + 0x00)                   // RV:      00H    Port mux select register
 #define MIE                            (0x300)                                 // RV:00000000H    Machine interrupt control register
 #define PIE                            (IRQ_BASE     + 0x00)                   // RV:      00H    Pending interrupt control register
 #define EXT0IE                         (IRQ_BASE     + 0x01)                   // RV:      00H    External interrupt 0 enable control register
 #define EXT1IE                         (IRQ_BASE     + 0x02)                   // RV:      00H    External interrupt 1 enable control register 
 #define EXT2IE                         (IRQ_BASE     + 0x03)                   // RV:      00H    External interrupt 2 enable control register
 #define EXT0IF                         (IRQ_BASE     + 0x04)                   // RV:      00H    External interrupt 0 flag register
 #define EXT1IF                         (IRQ_BASE     + 0x05)                   // RV:      00H    External interrupt 1 flag register
 #define EXT2IF                         (IRQ_BASE     + 0x06)                   // RV:      00H    External interrupt 2 flag register
 #define TCON                           (IRQ_BASE     + 0x07)                   // RV:      00H    Interrupt control register
 #define LVSR                           (IRQ_BASE     + 0x08)                   // RV:      00H    Low-temp/overvoltage status register
 #define IP0                            (IRQ_BASE     + 0x09)                   // RV:    0000H    Interrupt priority control0
 #define IP1                            (IRQ_BASE     + 0x0A)                   // RV:    0000H    Interrupt priority control1
 #define IP2                            (IRQ_BASE     + 0x0B)                   // RV:    0000H    Interrupt priority control2
 #define IP3                            (IRQ_BASE     + 0x0C)                   // RV:    0000H    Interrupt priority control3
 #define IP4                            (IRQ_BASE     + 0x0D)                   // RV:    0000H    Interrupt priority control4
 #define IP5                            (IRQ_BASE     + 0x0E)                   // RV:    0000H    Interrupt priority control5
 #define IP6                            (IRQ_BASE     + 0x0F)                   // RV:    0000H    Interrupt priority control6
 #define IP7                            (IRQ_BASE     + 0x10)                   // RV:    0000H    Interrupt priority control7
 #define IP8                            (IRQ_BASE     + 0x11)                   // RV:    0000H    Interrupt priority control8
 #define IP9                            (IRQ_BASE     + 0x12)                   // RV:    0000H    Interrupt priority control9
 #define IP10                           (IRQ_BASE     + 0x13)                   // RV:    0000H    Interrupt priority control10
 #define IP11                           (IRQ_BASE     + 0x14)                   // RV:    0000H    Interrupt priority control11
 #define IP12                           (IRQ_BASE     + 0x15)                   // RV:    0000H    Interrupt priority control12
 #define IP13                           (IRQ_BASE     + 0x16)                   // RV:    0000H    Interrupt priority control13
 #define IP14                           (IRQ_BASE     + 0x17)                   // RV:    0000H    Interrupt priority control14
 #define IP15                           (IRQ_BASE     + 0x18)                   // RV:    0000H    Interrupt priority control15
 #define IP16                           (IRQ_BASE     + 0x19)                   // RV:    0000H    Interrupt priority control16
 #define IP17                           (IRQ_BASE     + 0x1A)                   // RV:    0000H    Interrupt priority control17
 #define IP18                           (IRQ_BASE     + 0x1B)                   // RV:    0000H    Interrupt priority control18
 #define IP19                           (IRQ_BASE     + 0x1C)                   // RV:    0000H    Interrupt priority control19
 #define IP20                           (IRQ_BASE     + 0x1D)                   // RV:    0000H    Interrupt priority control20
 #define IP21                           (IRQ_BASE     + 0x1E)                   // RV:    0000H    Interrupt priority control21
 #define IP22                           (IRQ_BASE     + 0x1F)                   // RV:    0000H    Interrupt priority control22
 #define IP23                           (IRQ_BASE     + 0x20)                   // RV:    0000H    Interrupt priority control23
 #define IP24                           (IRQ_BASE     + 0x21)                   // RV:    0000H    Interrupt priority control24
 #define IP25                           (IRQ_BASE     + 0x22)                   // RV:    0000H    Interrupt priority control25
 #define IP26                           (IRQ_BASE     + 0x23)                   // RV:    0000H    Interrupt priority control26
 #define IP27                           (IRQ_BASE     + 0x24)                   // RV:    0000H    Interrupt priority control27
 #define IP28                           (IRQ_BASE     + 0x25)                   // RV:    0000H    Interrupt priority control28
 #define IP29                           (IRQ_BASE     + 0x26)                   // RV:    0000H    Interrupt priority control29
 #define IP30                           (IRQ_BASE     + 0x27)                   // RV:    0000H    Interrupt priority control30
 #define IP31                           (IRQ_BASE     + 0x28)                   // RV:    0000H    Interrupt priority control31
 #define CFG_KEY                        (SPECIAL_BASE + 0x01)                   // /* factory */
 #define RTC_CR                         (RTC_BASE     + 0x00)                   // RV:    0000H    RTC control register
 #define RTC_DR                         (RTC_BASE     + 0x01)                   // RV:    FFFFH    RTC count register
 #define CAL_CR                         (RTC_BASE     + 0x02)                   // RV:      00H    Clock calibration register
 #define OSC_CR                         (OSC_BASE     + 0x00)                   // RV:      00H    External fast clock control register
 #define OSC_SR                         (OSC_BASE     + 0x01)                   // RV:      00H    External fast clock status register
 #define FLA_KEY                        (FLA_BASE     + 0x00)                   // RV:      00H    Flash unlock register
 #define FLA_CR                         (FLA_BASE     + 0x01)                   // RV:    0000H    Flash control register
 #define FLA_ECC_CR                     (ECC_BASE     + 0x00)                   // RV:    8000H    ECC error configuration register
 #define FLA_ECC_SR                     (ECC_BASE     + 0x01)                   // RV:    0000H    ECC error status register
 #define RST_SR                         (SYSTEM_BASE  + 0x00)                   // RV:      xxH    Reset status register
 #define RST_CR                         (SYSTEM_BASE  + 0x01)                   // RV:      xxH    Reset control register
 #define PCON                           (SYSTEM_BASE  + 0x02)                   // RV:      00H    MCU power control register
 #define CK_CR                          (CK_BASE      + 0x00)                   // RV:00000000H    Clock control register
 #define CMP_CR0                        (CMP_BASE     + 0x00)                   // RV:      00H    Comparator control register0
 #define CMP_CR1                        (CMP_BASE     + 0x01)                   // RV:      00H    Comparator control register1
 #define CMP_CR2                        (CMP_BASE     + 0x02)                   // RV:      00H    Comparator control register2
 #define CMP_CR3                        (CMP_BASE     + 0x03)                   // RV:      00H    Comparator control register3
 #define CMP_SR                         (CMP_BASE     + 0x04)                   // RV:      00H    Comparator status register
 #define CMP_IFR                        (CMP_BASE     + 0x05)                   // RV:      00H    Comparator interrupt flag register    
 #define CMP_SAMR                       (CMP_BASE     + 0x06)                   // RV:      00H    Comparator sampling configuration
 #define CMP_DBR                        (CMP_BASE     + 0x07)                   // RV:      00H    Comparator signal configuration register   
 #define CMP_CR4                        (CMP_BASE     + 0x08)                   // RV:      00H    Comparator control register4
 #define CMP_CR5                        (CMP_BASE     + 0x09)                   // RV:      00H    Comparator control register5
 #define CMP_CR6                        (CMP_BASE     + 0x0A)                   // RV:      00H    Comparator control register6
 #define EVT_FILT                       (CMP_BASE     + 0x06)                   // RV:    0300H    Drive protection function register
 #define VREF_VHALF_CR                  (AMP_BASE     + 0x00)                   // RV:    0000H    Reference level control register
 #define AMP_CR0                        (AMP_BASE     + 0x01)                   // RV:    0000H    Op-amp control register0
 #define AMP_CR1                        (AMP_BASE     + 0x02)                   // RV:    0000H    Op-amp control register1
 #define TSD_CR                         (TEMP_BASE    + 0x00)                   // RV:    000DH    TSD control register
 #define TSEN_DR                        (TEMP_BASE    + 0x01)                   // RV:    0000H    TSENSOR data register
 #define DAC_CR                         (DAC_BASE     + 0x00)                   // RV:    0000H    DAC control register
 #define DAC_DR0                        (DAC_BASE     + 0x01)                   // RV:    0000H    DAC0 output value register0
 #define DAC_DR1                        (DAC_BASE     + 0x02)                   // RV:    0000H    DAC0 output value register1
 #define DAC_DR2                        (DAC_BASE     + 0x03)                   // RV:    0000H    DAC0 output value register2
 #define DAC_DR3                        (DAC_BASE     + 0x04)                   // RV:    0000H    DAC0 output value register3
 #define DAC_DR4                        (DAC_BASE     + 0x05)                   // RV:    0000H    DAC0 output value register4
 #define ADC1_CR                        (ADC1_BASE    + 0x00)                   // RV:    0000H    ADC control register
 #define ADC1_MASK                      (ADC1_BASE    + 0x01)                   // RV:    0000H    ADC channel enable register
 #define ADC1_SCYC                      (ADC1_BASE    + 0x02)                   // RV:    3333H    ADC channel sample time config register
 #define ADC2_CR                        (ADC2_BASE    + 0x00)                   // RV:    0000H    ADC2 control register
 #define ADC2_MASK                      (ADC2_BASE    + 0x01)                   // RV:    0000H    ADC2 channel enable register
 #define ADC2_SCYC                      (ADC2_BASE    + 0x02)                   // RV:    3333H    ADC2 channel sample time config register
 #define ADC3_CR                        (ADC3_BASE    + 0x00)                   // RV:    0000H    ADC3 control register
 #define ADC3_MASK                      (ADC3_BASE    + 0x01)                   // RV:    0000H    ADC3 channel enable register
 #define ADC3_SCYC                      (ADC3_BASE    + 0x02)                   // RV:    0033H    ADC3 channel sample time config register
 #define ADC3_DR0                       (ADC3_BASE    + 0x03)                   // RV:    0000H    ADC3 channel sample data register0
 #define ADC3_DR1                       (ADC3_BASE    + 0x04)                   // RV:    0000H    ADC3 channel sample data register1
 #define ADC3_DR2                       (ADC3_BASE    + 0x05)                   // RV:    0000H    ADC3 channel sample data register2
 #define DMA0_CR                        (DMA0_BASE    + 0x00)                   // RV:      00H    DMA0control register
 #define DMA0_LEN                       (DMA0_BASE    + 0x01)                   // RV:      00H    DMA0transfer length config register
 #define DMA0_BA                        (DMA0_BASE    + 0x02)                   // RV:      00H    DMA0transfer address config register
 #define DMA1_CR                        (DMA1_BASE    + 0x00)                   // RV:      00H    DMA1control register
 #define DMA1_LEN                       (DMA1_BASE    + 0x01)                   // RV:      00H    DMA1transfer length config register
 #define DMA1_BA                        (DMA1_BASE    + 0x02)                   // RV:      00H    DMA1transfer address config register
 #define DMA2_CR                        (DMA2_BASE    + 0x00)                   // RV:      00H    DMA2control register
 #define DMA2_LEN                       (DMA2_BASE    + 0x01)                   // RV:      00H    DMA2transfer length config register
 #define DMA2_BA                        (DMA2_BASE    + 0x02)                   // RV:      00H    DMA2transfer address config register
 #define DMA3_CR                        (DMA3_BASE    + 0x00)                   // RV:      00H    DMA3control register
 #define DMA3_LEN                       (DMA3_BASE    + 0x01)                   // RV:      00H    DMA3transfer length config register
 #define DMA3_BA                        (DMA3_BASE    + 0x02)                   // RV:      00H    DMA3transfer address config register
 #define DMA4_CR                        (DMA4_BASE    + 0x00)                   // RV:      00H    DMA4control register
 #define DMA4_LEN                       (DMA4_BASE    + 0x01)                   // RV:      00H    DMA4transfer length config register
 #define DMA4_BA                        (DMA4_BASE    + 0x02)                   // RV:      00H    DMA4transfer address config register
 #define DMA5_CR                        (DMA5_BASE    + 0x00)                   // RV:      00H    DMA5control register
 #define DMA5_LEN                       (DMA5_BASE    + 0x01)                   // RV:      00H    DMA5transfer length config register
 #define DMA5_BA                        (DMA5_BASE    + 0x02)                   // RV:      00H    DMA5transfer address config register
 #define UT1_CR0                        (UART1_BASE   + 0x00)                   // RV:      00H    Uartcontrol register0
 #define UT1_CR1                        (UART1_BASE   + 0x01)                   // RV:      00H    Uartcontrol register1
 #define UT1_DR                         (UART1_BASE   + 0x02)                   // RV:      00H    UART data register
 #define UT1_BAUD                       (UART1_BASE   + 0x03)                   // RV:    0000H    UARTbaud ratecontrol register
 #define SF_CR                          (UART1_BASE   + 0x04)                   // RV:    0000H    encoder serial interfacecontrol register
 #define SF_SR                          (UART1_BASE   + 0x05)                   // RV:    0000H    Encoder serial interface status register
 #define SF_BAUD                        (UART1_BASE   + 0x06)                   // RV:    0000H    Encoder serial interface baud rate register
 #define UT2_CR0                        (UART2_BASE   + 0x00)                   // RV:    0012H    Uart2control register0
 #define UT2_CR1                        (UART2_BASE   + 0x01)                   // RV:      00H    Uart2control register1
 #define UT2_DR                         (UART2_BASE   + 0x02)                   // RV:      00H    Uart2 data register
 #define UT2_BAUD                       (UART2_BASE   + 0x03)                   // RV:    0000H    UART2baud ratecontrol register
 #define I2C1_CR                        (I2C1_BASE    + 0x00)                   // RV:    0000H    I2Ccontrol register
 #define I2C1_ID                        (I2C1_BASE    + 0x01)                   // RV:    0000H    I2C local address register
 #define I2C1_DR                        (I2C1_BASE    + 0x02)                   // RV:    0000H    I2C data register
 #define I2C1_SR                        (I2C1_BASE    + 0x03)                   // RV:    0000H    I2C status register
 #define I2C1_BAUD                      (I2C1_BASE    + 0x04)                   // RV:    0000H    I2C2baud ratecontrol register
 #define I2C2_CR                        (I2C2_BASE    + 0x00)                   // RV:    0000H    I2C2control register
 #define I2C2_ID                        (I2C2_BASE    + 0x01)                   // RV:    0000H    I2C2 local address register
 #define I2C2_DR                        (I2C2_BASE    + 0x02)                   // RV:    0000H    I2C2 data register
 #define I2C2_SR                        (I2C2_BASE    + 0x03)                   // RV:    0000H    I2C2 status register
 #define I2C2_BAUD                      (I2C2_BASE    + 0x04)                   // RV:    0000H    I2C2baud ratecontrol register
 #define SPI1_CR                        (SPI1_BASE    + 0x00)                   // RV:      0bH    SPI1control register
 #define SPI1_SR                        (SPI1_BASE    + 0x01)                   // RV:      02H    SPI1 status register
 #define SPI1_CLK                       (SPI1_BASE    + 0x02)                   // RV:      00H    SPI1 clock register
 #define SPI1_DR                        (SPI1_BASE    + 0x03)                   // RV:      00H    SPI1 data register
 #define SPI2_CR                        (SPI2_BASE    + 0x00)                   // RV:      0bH    SPI2control register
 #define SPI2_SR                        (SPI2_BASE    + 0x01)                   // RV:      02H    SPI2 status register
 #define SPI2_CLK                       (SPI2_BASE    + 0x02)                   // RV:      00H    SPI2 clock register
 #define SPI2_DR                        (SPI2_BASE    + 0x03)                   // RV:      00H    SPI2 data register
 #define LIN_CR                         (LIN_BASE     + 0x00)                   // RV:      00H    LINcontrol register
 #define LIN_SR                         (LIN_BASE     + 0x01)                   // RV:      00H    LIN status register
 #define LIN_CSR                        (LIN_BASE     + 0x02)                   // RV:      00H    LINstatuscontrol register
 #define LIN_ID                         (LIN_BASE     + 0x03)                   // RV:      00H    LINID register
 #define LIN_SIZE                       (LIN_BASE     + 0x04)                   // RV:      00H    LIN data length register
 #define LIN_BAUD                       (LIN_BASE     + 0x05)                   // RV:      00H    LINbaud ratecontrol register
 #define CAN_CR0                        (CAN_BASE     + 0x00)                   // RV:    0000H    CANcontrol register0
 #define CAN_CR1                        (CAN_BASE     + 0x01)                   // RV:    0000H    CANcontrol register1
 #define CAN_STS                        (CAN_BASE     + 0x02)                   // RV:    0000H    CAN status register
 #define CAN_IER                        (CAN_BASE     + 0x03)                   // RV:    0000H    CANInterrupt control register
 #define CAN_IFR                        (CAN_BASE     + 0x04)                   // RV:    0000H    CAN interrupt flag register
 #define CAN_TSPT                       (CAN_BASE     + 0x05)                   // RV:    0000H    CAN message status register
 #define CAN_NBTR                       (CAN_BASE     + 0x06)                   // RV:    0000H    CANnominalbittimingcontrol register
 #define CAN_DBTR                       (CAN_BASE     + 0x07)                   // RV:    0000H    CANdata phasebittimingcontrol register
 #define CAN_TDCR                       (CAN_BASE     + 0x08)                   // RV:    0000H    CANtransmission delaycontrol register
 #define CAN_ACR                        (CAN_BASE     + 0x09)                   // RV:    0000H    CAN filter register
 #define CAN_AMR                        (CAN_BASE     + 0x0a)                   // RV:    0000H    CAN filter activation register
 #define CAN_ERR                        (CAN_BASE     + 0x0b)                   // RV:    0000H    CAN error status register
 #define CAN_ERLIM                      (CAN_BASE     + 0x0c)                   // RV:    0000H    CAN error warning limit register
 #define CAN_TMSTA                      (CAN_BASE     + 0x0d)                   // RV:    0000H    CAN mailbox status register
 #define CAN_TMID0                      (CAN_BASE     + 0x0e)                   // RV:    0000H    CAN transmit mailbox ID register0
 #define CAN_TMDT0                      (CAN_BASE     + 0x0f)                   // RV:    0000H    CAN transmit mailbox config register0
 #define CAN_TMID1                      (CAN_BASE     + 0x10)                   // RV:    0000H    CAN transmit mailbox ID register1
 #define CAN_TMDT1                      (CAN_BASE     + 0x11)                   // RV:    0000H    CAN transmit mailbox config register1
 #define CAN_TMID2                      (CAN_BASE     + 0x12)                   // RV:    0000H    CAN transmit mailbox ID register2
 #define CAN_TMDT2                      (CAN_BASE     + 0x13)                   // RV:    0000H    CAN transmit mailbox config register2
 #define TIM2_CR0                       (TIMER2_BASE  + 0x00)                   // RV:    0000H    TIMER2control register0
 #define TIM2_CR1                       (TIMER2_BASE  + 0x01)                   // RV:    0000H    TIMER2control register1
 #define TIM2_IER                       (TIMER2_BASE  + 0x02)                   // RV:    0000H    TIMER2interrupt register
 #define TIM2_SR                        (TIMER2_BASE  + 0x03)                   // RV:    0000H    TIMER2status register
 #define TIM2_CNTR                      (TIMER2_BASE  + 0x04)                   // RV:    0000H    TIMER2count value
 #define TIM2_DR                        (TIMER2_BASE  + 0x05)                   // RV:    0000H    TIMER2match value
 #define TIM2_ARR                       (TIMER2_BASE  + 0x06)                   // RV:    0000H    TIMER2reload value
 #define TIM2_QEP_MNUM                  (TIMER2_BASE  + 0x07)                   // RV:    0000H    TIMER2pulsecount value
 #define TIM2_QEP_TNUM                  (TIMER2_BASE  + 0x08)                   // RV:    0000H    TIMER2clockcount value
 #define TIM2_QEP_TS_EMP                (TIMER2_BASE  + 0x09)                   // RV:    0000H    TIMER2empty pulsecount value
 #define TIM2_QEP_CNTR                  (TIMER2_BASE  + 0x0A)                   // RV:    0000H    TIMER2outputpulsecount value
 #define TIM2_QEP_ARR                   (TIMER2_BASE  + 0x0B)                   // RV:    0000H    TIMER2output pulse compare value
 #define TIM2_CR2                       (TIMER2_BASE  + 0x0C)                   // RV:    0000H    TIMER2control register2
 #define TIM3_CR0                       (TIMER3_BASE  + 0x00)                   // RV:    0000H    TIMER3control register0
 #define TIM3_CR1                       (TIMER3_BASE  + 0x01)                   // RV:    0000H    TIMER3control register1
 #define TIM3_IER                       (TIMER3_BASE  + 0x02)                   // RV:    0000H    TIMER3interrupt register
 #define TIM3_SR                        (TIMER3_BASE  + 0x03)                   // RV:    0000H    TIMER3status register
 #define TIM3_CNTR                      (TIMER3_BASE  + 0x04)                   // RV:    0000H    TIMER3count value
 #define TIM3_DR                        (TIMER3_BASE  + 0x05)                   // RV:    0000H    TIMER3match value
 #define TIM3_ARR                       (TIMER3_BASE  + 0x06)                   // RV:    0000H    TIMER3reload value
 #define TIM4_CR0                       (TIMER4_BASE  + 0x00)                   // RV:    0000H    TIMER4control register0
 #define TIM4_CR1                       (TIMER4_BASE  + 0x01)                   // RV:    0000H    TIMER4control register1
 #define TIM4_IER                       (TIMER4_BASE  + 0x02)                   // RV:    0000H    TIMER4interrupt register
 #define TIM4_SR                        (TIMER4_BASE  + 0x03)                   // RV:    0000H    TIMER4status register
 #define TIM4_CNTR                      (TIMER4_BASE  + 0x04)                   // RV:    0000H    TIMER4count value
 #define TIM4_DR                        (TIMER4_BASE  + 0x05)                   // RV:    0000H    TIMER4match value
 #define TIM4_ARR                       (TIMER4_BASE  + 0x06)                   // RV:    0000H    TIMER4reload value
 #define TIM5_CR0                       (TIMER5_BASE  + 0x00)                   // RV:    0000H    TIMER5control register0
 #define TIM5_CR1                       (TIMER5_BASE  + 0x01)                   // RV:    0000H    TIMER5control register1
 #define TIM5_IER                       (TIMER5_BASE  + 0x02)                   // RV:    0000H    TIMER5interrupt register
 #define TIM5_SR                        (TIMER5_BASE  + 0x03)                   // RV:    0000H    TIMER5status register
 #define TIM5_CNTR                      (TIMER5_BASE  + 0x04)                   // RV:    0000H    TIMER5count value
 #define TIM5_DR                        (TIMER5_BASE  + 0x05)                   // RV:    0000H    TIMER5match value
 #define TIM5_ARR                       (TIMER5_BASE  + 0x06)                   // RV:    0000H    TIMER5reload value
 #define TIM5_QEP_MNUM                  (TIMER5_BASE  + 0x07)                   // RV:    0000H    TIMER5pulsecount value
 #define TIM5_QEP_TNUM                  (TIMER5_BASE  + 0x08)                   // RV:    0000H    TIMER5clockcount value
 #define TIM5_QEP_TS_EMP                (TIMER5_BASE  + 0x09)                   // RV:    0000H    TIMER5empty pulsecount value
 #define TIM5_QEP_CNTR                  (TIMER5_BASE  + 0x0A)                   // RV:    0000H    TIMER5outputpulsecount value
 #define TIM5_QEP_ARR                   (TIMER5_BASE  + 0x0B)                   // RV:    0000H    TIMER5output pulse compare value
 #define TIM5_CR2                       (TIMER5_BASE  + 0x0C)                   // RV:    0000H    TIMER5control register2
 #define TIM6_CR0                       (TIMER6_BASE  + 0x00)                   // RV:    0000H    TIMER6control register0
 #define TIM6_CR1                       (TIMER6_BASE  + 0x01)                   // RV:    0000H    TIMER6control register1
 #define TIM6_IER                       (TIMER6_BASE  + 0x02)                   // RV:    0000H    TIMER6interrupt register
 #define TIM6_SR                        (TIMER6_BASE  + 0x03)                   // RV:    0000H    TIMER6status register
 #define TIM6_CNTR                      (TIMER6_BASE  + 0x04)                   // RV:    0000H    TIMER6count value
 #define TIM6_DR                        (TIMER6_BASE  + 0x05)                   // RV:    0000H    TIMER6match value
 #define TIM6_ARR                       (TIMER6_BASE  + 0x06)                   // RV:    0000H    TIMER6reload value
 #define TIM6_QEP_MNUM                  (TIMER6_BASE  + 0x07)                   // RV:    0000H    TIMER6pulsecount value
 #define TIM6_QEP_TNUM                  (TIMER6_BASE  + 0x08)                   // RV:    0000H    TIMER6clockcount value
 #define TIM6_QEP_TS_EMP                (TIMER6_BASE  + 0x09)                   // RV:    0000H    TIMER6empty pulsecount value
 #define TIM6_QEP_CNTR                  (TIMER6_BASE  + 0x0A)                   // RV:    0000H    TIMER6outputpulsecount value
 #define TIM6_QEP_ARR                   (TIMER6_BASE  + 0x0B)                   // RV:    0000H    TIMER6output pulse compare value
 #define TIM6_CR2                       (TIMER6_BASE  + 0x0C)                   // RV:    0000H    TIMER6control register2
 #define TIM7_CR0                       (TIMER7_BASE  + 0x00)                   // RV:    0000H    TIMER7control register0
 #define TIM7_CR1                       (TIMER7_BASE  + 0x01)                   // RV:    0000H    TIMER7control register1
 #define TIM7_IER                       (TIMER7_BASE  + 0x02)                   // RV:    0000H    TIMER7interrupt register
 #define TIM7_SR                        (TIMER7_BASE  + 0x03)                   // RV:    0000H    TIMER7status register
 #define TIM7_CNTR                      (TIMER7_BASE  + 0x04)                   // RV:    0000H    TIMER7count value
 #define TIM7_DR                        (TIMER7_BASE  + 0x05)                   // RV:    0000H    TIMER7match value
 #define TIM7_ARR                       (TIMER7_BASE  + 0x06)                   // RV:    0000H    TIMER7reload value
 #define TIM8_CR0                       (TIMER8_BASE  + 0x00)                   // RV:    0000H    TIMER8control register0
 #define TIM8_CR1                       (TIMER8_BASE  + 0x01)                   // RV:    0000H    TIMER8control register1
 #define TIM8_IER                       (TIMER8_BASE  + 0x02)                   // RV:    0000H    TIMER8interrupt register
 #define TIM8_SR                        (TIMER8_BASE  + 0x03)                   // RV:    0000H    TIMER8status register
 #define TIM8_CNTR                      (TIMER8_BASE  + 0x04)                   // RV:    0000H    TIMER8count value
 #define TIM8_DR                        (TIMER8_BASE  + 0x05)                   // RV:    0000H    TIMER8match value
 #define TIM8_ARR                       (TIMER8_BASE  + 0x06)                   // RV:    0000H    TIMER8reload value
 #define STPC0_CR                       (STPC0_BASE   + 0x00)                   // RV:    0000H    Probe0control register
 #define STPC0_SR                       (STPC0_BASE   + 0x01)                   // RV:    0000H    Probe0status register
 #define STRO0_ARR                      (STPC0_BASE   + 0x02)                   // RV:    0000H    Probe0latch value
 #define PCOM0_ARR                      (STPC0_BASE   + 0x03)                   // RV:    0000H    Position compare 0 comparison value
 #define STPC1_CR                       (STPC1_BASE   + 0x00)                   // RV:    0000H    Probe1control register
 #define STPC1_SR                       (STPC1_BASE   + 0x01)                   // RV:    0000H    Probe1status register
 #define STRO1_ARR                      (STPC1_BASE   + 0x02)                   // RV:    0000H    Probe1latch value
 #define PCOM1_ARR                      (STPC1_BASE   + 0x03)                   // RV:    0000H    Position compare 1 comparison value
 #define SYST_ARR                       (SYSTICK_BASE + 0x00)                   // RV:    0176H    SYSTICKreload value
 #define SYST_SR                        (SYSTICK_BASE + 0x01)                   // RV:    0000H    SYSTICKcontrol register
 #define IWDT_KR                        (IWDT_BASE    + 0x00)                   // RV:    0000H    Watchdog key register
 #define IWDT_REL                       (IWDT_BASE    + 0x01)                   // RV:    0000H    watchdogreload valueregister
 #define WWDT_CR                        (WWDT_BASE    + 0x00)                   // RV:    0000H    windowwatchdogcontrol register
 #define WWDT_CFR                       (WWDT_BASE    + 0x01)                   // RV:    0000H    Window watchdog configuration register
 #define WWDT_SR                        (WWDT_BASE    + 0x02)                   // RV:    0000H    windowwatchdogstatus register
 #define CRC_DIN                        (CRC_BASE     + 0x00)                   // RV:    0000H    CRC data input register
 #define CRC_CR                         (CRC_BASE     + 0x01)                   // RV:    0010H    CRCcontrol register
 #define CRC_DR                         (CRC_BASE     + 0x02)                   // RV:    0000H    CRC result output register
 #define CRC_BEG                        (CRC_BASE     + 0x03)                   // RV:    0000H    CRC auto-calc start address
 #define CRC_CNT                        (CRC_BASE     + 0x04)                   // RV:    0000H    CRC block count register
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

 #define ME_CR                          (ME_BASE      + 0x00)                   // RV:    0000H    MEcontrol register
 #define ME_ST0                         (ME_BASE      + 0x01)                   // RV:    0000H    ME state match 0 register     /* factory */
 #define ME_ST1                         (ME_BASE      + 0x02)                   // RV:    0000H    ME state match 1 register      /* factory */
 #define ME_STR                         (ME_BASE      + 0x03)                   // RV:    0000H    MEstatus register           /* factory */
 #define ME_IER                         (ME_BASE      + 0x04)                   // RV:      00H    ME interrupt enable register       /* factory */
 #define ME_IFR                         (ME_BASE      + 0x05)                   // RV:    0000H    ME interrupt flag register       /* factory */
 #define ME_BF0                         (ME_BASE      + 0x08)                   // RV:    0000H    ME internal BUFFER0register       /* factory */
 #define ME_BF1                         (ME_BASE      + 0x09)                   // RV:    0000H    ME internal BUFFER1register       /* factory */
 #define ME_BF2                         (ME_BASE      + 0x0A)                   // RV:    0000H    ME internal BUFFER2register       /* factory */
 #define ME_BF3                         (ME_BASE      + 0x0B)                   // RV:    0000H    ME internal BUFFER3register       /* factory */
 #define ME_COR                         (ME_BASE      + 0x0C)                   // RV:      00H    ME CORDIC enable register
 #define ME_BF4                         (ME_BASE      + 0x0D)                   // RV:    0000H    ME internal BUFFER4register      /* factory */
 #define ME_BF5                         (ME_BASE      + 0x0E)                   // RV:    0000H    ME internal BUFFER5register      /* factory */


 #define DRV1_CR                        (DRV1_BASE    + 0x00)                   // RV:      00H    DRV1control register
 #define DRV1_OUT                       (DRV1_BASE    + 0x01)                   // RV:    0000H    DRV1 output register
 #define DRV1_IER                       (DRV1_BASE    + 0x02)                   // RV:      00H    DRV1 interrupt enable register
 #define DRV1_IFR                       (DRV1_BASE    + 0x03)                   // RV:      00H    DRV1 interrupt flag register
 #define DRV1_PER                       (DRV1_BASE    + 0x04)                   // RV:    0000H    DRV1 protection enable register
 #define DRV1_PTR                       (DRV1_BASE    + 0x05)                   // RV:    0000H    DRV1 protection trigger register
 #define DRV1_PSR                       (DRV1_BASE    + 0x06)                   // RV:    0000H    DRV1protectionstatus register
 #define DRV1_CMR                       (DRV1_BASE    + 0x07)                   // RV:    0000H    DRV1 enable and polarity register
 #define DRV1_FCR0                      (DRV1_BASE    + 0x08)                   // RV:    0000H    DRV1 FOC control0register
 #define DRV1_FCR1                      (DRV1_BASE    + 0x09)                   // RV:    0000H    DRV1 FOC control1register
 #define DRV1_FCR2                      (DRV1_BASE    + 0x0a)                   // RV:    0000H    DRV1 FOC control2register
 #define DRV1_FCR3                      (DRV1_BASE    + 0x0b)                   // RV:    0000H    DRV1 FOC control3register
 #define DRV1_FCR4                      (DRV1_BASE    + 0x0c)                   // RV:    0000H    DRV1 FOC control4register
 #define DRV1_FCR5                      (DRV1_BASE    + 0x0d)                   // RV:    0000H    DRV1 FOC control5register
 #define DRV1_FCR6                      (DRV1_BASE    + 0x0e)                   // RV:    0000H    DRV1 FOC control6register
 #define DRV1_FCR7                      (DRV1_BASE    + 0x0f)                   // RV:    0000H    DRV1 FOC control7register
 #define DRV1_ARR                       (DRV1_BASE    + 0x10)                   // RV:    0000H    DRV1 auto-reload register
 #define DRV1_DR                        (DRV1_BASE    + 0x11)                   // RV:    0000H    DRV1 data register, controls 6 registers (UVW up/down count) at once
 #define DRV1_COMR                      (DRV1_BASE    + 0x12)                   // RV:    0000H    DRV1 compare register
 #define DRV1_DTR                       (DRV1_BASE    + 0x13)                   // RV:      00H    DRV1 dead-time register
 #define DRV1_CMPU1                     (DRV1_BASE    + 0x14)                   // RV:    0000H    DRV1 U-phase up-count DR register
 #define DRV1_CMPD1                     (DRV1_BASE    + 0x15)                   // RV:    0000H    DRV1 U-phase down-count DR register
 #define DRV1_CMPU2                     (DRV1_BASE    + 0x16)                   // RV:    0000H    DRV1 V-phase up-count DR register
 #define DRV1_CMPD2                     (DRV1_BASE    + 0x17)                   // RV:    0000H    DRV1 V-phase down-count DR register
 #define DRV1_CMPU3                     (DRV1_BASE    + 0x18)                   // RV:    0000H    DRV1 W-phase up-count DR register
 #define DRV1_CMPD3                     (DRV1_BASE    + 0x19)                   // RV:    0000H    DRV1 W-phase down-count DR register
 #define DRV1_CNTR                      (DRV1_BASE    + 0x1a)                   // RV:    0000H    DRV1 counter
 #define DRV1_TRG1						(DRV1_BASE    + 0x1b)                   // RV:    0000H    DRV1 1st sample DR value
 #define DRV1_TRG2						(DRV1_BASE    + 0x1c)                   // RV:    0000H    DRV1 2nd sample DR value


 #define DRV2_CR                        (DRV2_BASE    + 0x00)                   // RV:      00H    DRV2control register
 #define DRV2_OUT                       (DRV2_BASE    + 0x01)                   // RV:    0000H    DRV2 output register
 #define DRV2_IER                       (DRV2_BASE    + 0x02)                   // RV:      00H    DRV2 interrupt enable register
 #define DRV2_IFR                       (DRV2_BASE    + 0x03)                   // RV:      00H    DRV2 interrupt flag register
 #define DRV2_PER                       (DRV2_BASE    + 0x04)                   // RV:    0000H    DRV2 protection enable register
 #define DRV2_PTR                       (DRV2_BASE    + 0x05)                   // RV:    0000H    DRV2 protection trigger register
 #define DRV2_PSR                       (DRV2_BASE    + 0x06)                   // RV:    0000H    DRV2protectionstatus register
 #define DRV2_CMR                       (DRV2_BASE    + 0x07)                   // RV:    0000H    DRV2 enable and polarity register
 #define DRV2_FCR0                      (DRV2_BASE    + 0x08)                   // RV:    0000H    DRV2 FOC control0register
 #define DRV2_FCR1                      (DRV2_BASE    + 0x09)                   // RV:    0000H    DRV2 FOC control1register
 #define DRV2_FCR2                      (DRV2_BASE    + 0x0a)                   // RV:    0000H    DRV2 FOC control2register
 #define DRV2_ARR                       (DRV2_BASE    + 0x10)                   // RV:    0000H    DRV2 auto-reload register
 #define DRV2_DR                        (DRV2_BASE    + 0x11)                   // RV:    0000H    DRV2 data register, controls 6 registers (UVW up/down count) at once
 #define DRV2_COMR                      (DRV2_BASE    + 0x12)                   // RV:    0000H    DRV2 compare register
 #define DRV2_DTR                       (DRV2_BASE    + 0x13)                   // RV:      00H    DRV2 dead-time register
 #define DRV2_CMPU1                     (DRV2_BASE    + 0x14)                   // RV:    0000H    DRV2 U-phase up-count DR register
 #define DRV2_CMPD1                     (DRV2_BASE    + 0x15)                   // RV:    0000H    DRV2 U-phase down-count DR register
 #define DRV2_CMPU2                     (DRV2_BASE    + 0x16)                   // RV:    0000H    DRV2 V-phase up-count DR register
 #define DRV2_CMPD2                     (DRV2_BASE    + 0x17)                   // RV:    0000H    DRV2 V-phase down-count DR register
 #define DRV2_CMPU3                     (DRV2_BASE    + 0x18)                   // RV:    0000H    DRV2 W-phase up-count DR register
 #define DRV2_CMPD3                     (DRV2_BASE    + 0x19)                   // RV:    0000H    DRV2 W-phase down-count DR register
 #define DRV2_CNTR                      (DRV2_BASE    + 0x1a)                   // RV:    0000H    DRV2 counter

 #define BISS_CLK_CNT                   (BISS_BASE + 0x01)                      // RV:      00H    0=6MHz; 1=3MHz; 2=2MHz; 3=1.5MHz;
 #define BISS_OVERTIME_CNT              (BISS_BASE + 0x02)                      // RV:    00FFH    BiSS
 #define BISS_DATA_LEN                  (BISS_BASE + 0x03)                      // RV:      00H    BiSS data length
 #define BISS_STATE                     (BISS_BASE + 0x04)                      // RV:      00H    BiSS state
 #define BISS_SDATAL                    (BISS_BASE + 0x05)                      // RV:00000000H    BiSS data low 32 bit
 #define BISS_SDATAH                    (BISS_BASE + 0x06)                      // RV:00000000H    BiSS data high 32 bit

 #define PFC_CR0                        (PFC_BASE + 0x00)                       // RV:    0000H    PFCcontrol register0
 #define PFC_CR1                        (PFC_BASE + 0x01)                       // RV:      00H    PFCcontrol register1
 #define PFC_CR2                        (PFC_BASE + 0x02)                       // RV:    0000H    PFCcontrol register2
 #define PFC_KM                         (PFC_BASE + 0x03)                       // RV:    0000H    PFC KM coefficient
 #define UAC_CSO                        (PFC_BASE + 0x04)                       // RV:    0000H    UAC sampling reference value
 #define IAC1_CSO                       (PFC_BASE + 0x05)                       // RV:    0000H    IAC sampling reference value
 #define IAC2_CSO                       (PFC_BASE + 0x06)                       // RV:    0000H    IAC2 sampling reference value
 #define PFC_ARR                        (PFC_BASE + 0x07)                       // RV:    0000H    PFCcounterreload value
 #define PFC_DR1                        (PFC_BASE + 0x08)                       // RV:    0000H    PFC counter compare value
 #define PFC_DR2                        (PFC_BASE + 0x09)                       // RV:    0000H    PFC2 counter compare value
 #define UDC_ARR                        (PFC_BASE + 0x0a)                       // RV:    0000H    Outer loop execution frequency; voltage loop frequency = PFC carrier frequency / UDC_ARR
 #define PFC_TRGDLY                     (PFC_BASE + 0x0b)                       // RV:    0000H    IAC/IAC2 sampling delay
 #define UDC_REF                        (PFC_BASE + 0x0c)                       // RV:    0000H    UDC PI reference value
 #define UDC_UK                         (PFC_BASE + 0x0d)                       // RV:    0000H    UDC PI output value
 #define UDC_KP                         (PFC_BASE + 0x0e)                       // RV:    0000H    UDC PI proportional parameter
 #define UDC_KI                         (PFC_BASE + 0x0f)                       // RV:    0000H    UDC PI integral parameter
 #define UDC_UKMAX                      (PFC_BASE + 0x10)                       // RV:    0000H    UDC PI maximum output value
 #define UDC_UKMIN                      (PFC_BASE + 0x11)                       // RV:    0000H    UDC PI minimum output value
 #define IAC1_REF                       (PFC_BASE + 0x12)                       // RV:    0000H    IAC PI reference value
 #define IAC1_UK                        (PFC_BASE + 0x13)                       // RV:    0000H    IAC PI output value
 #define IAC1_KP                        (PFC_BASE + 0x14)                       // RV:    0000H    IAC PI proportional parameter
 #define IAC1_KI                        (PFC_BASE + 0x15)                       // RV:    0000H    IAC PI integral parameter
 #define IAC1_UKMAX                     (PFC_BASE + 0x16)                       // RV:    0000H    IAC PI maximum output value
 #define IAC1_UKMIN                     (PFC_BASE + 0x17)                       // RV:    0000H    IAC PI minimum output value
 #define IAC2_REF                       (PFC_BASE + 0x18)                       // RV:    0000H    IAC2 PI reference value
 #define IAC2_UK                        (PFC_BASE + 0x19)                       // RV:    0000H    IAC2 PI output value
 #define IAC2_KP                        (PFC_BASE + 0x1a)                       // RV:    0000H    IAC2 PI proportional parameter
 #define IAC2_KI                        (PFC_BASE + 0x1b)                       // RV:    0000H    IAC2 PI integral parameter
 #define IAC2_UKMAX                     (PFC_BASE + 0x1c)                       // RV:    0000H    IAC2 PI maximum output value
 #define IAC2_UKMIN                     (PFC_BASE + 0x1d)                       // RV:    0000H    IAC2 PI minimum output value
 #define PFC_UAC                        (PFC_BASE + 0x1e)                       // RV:    0000H    UAC sample value
 #define PFC_IAC1                       (PFC_BASE + 0x1f)                       // RV:    0000H    IAC sample value
 #define PFC_IAC2                       (PFC_BASE + 0x20)                       // RV:    0000H    IAC2 sample value
 #define PFC_UDC                        (PFC_BASE + 0x21)                       // RV:    0000H    UDC sample value
 #define PFC_UAVG                       (PFC_BASE + 0x22)                       // RV:    7FFFH    UAC average value
 #define PFC_COM                        (PFC_BASE + 0x23)                       // RV:    0000H    Inner loop feedforward compensation value
 #define PFC_KCOM                       (PFC_BASE + 0x24)                       // RV:    0000H    Inner loop feedforward compensation coefficient
 #define PFC_DDCM                       (PFC_BASE + 0x25)                       // RV:    0000H    Inner loop feedforward DDCM mode compensation amount
 #define PFC_DCCM                       (PFC_BASE + 0x26)                       // RV:    0000H    Inner loop feedforward DCCM mode compensation amount
 #define PFC_KDDCM                      (PFC_BASE + 0x27)                       // RV:    0000H    DDCM mode compensation coefficient
 #define PFC_DCCMCSO                    (PFC_BASE + 0x28)                       // RV:    0000H    DCCM adjustment coefficient
 #define PFC_KIAC1                      (PFC_BASE + 0x29)                       // RV:    4000H    IAC sampling correction coefficient for feedforward compensation, used in DDCM
 #define PFC_KIAC2                      (PFC_BASE + 0x2a)                       // RV:    4000H    IAC2 sampling correction coefficient for feedforward compensation, used in DDCM

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
#define PA15                            0x8000                                  // rw-- pin PA15
#define PA14                            0x4000                                  // rw-- pin PA14
#define PA13                            0x2000                                  // rw-- pin PA13
#define PA12                            0x1000                                  // rw-- pin PA12
#define PA11                            0x800                                   // rw-- pin PA11
#define PA10                            0x400                                   // rw-- pin PA10
#define PA9                             0x200                                   // rw-- pin PA9
#define PA8                             0x100                                   // rw-- pin PA8
#define PA7                             0x80                                    // rw-- pin PA7
#define PA6                             0x40                                    // rw-- pin PA6
#define PA5                             0x20                                    // rw-- pin PA5
#define PA4                             0x10                                    // rw-- pin PA4
#define PA3                             0x08                                    // rw-- pin PA3
#define PA2                             0x04                                    // rw-- pin PA2
#define PA1                             0x02                                    // rw-- pin PA1
#define PA0                             0x01                                    // rw-- pin PA0
/********************** Bits definition for PA_OE register *********************/
#define PA15OE                          0x8000                                  // rw-- pin PA15 output enable bit
#define PA14OE                          0x4000                                  // rw-- pin PA14 output enable bit
#define PA13OE                          0x2000                                  // rw-- pin PA13 output enable bit
#define PA12OE                          0x1000                                  // rw-- pin PA12 output enable bit
#define PA11OE                          0x800                                   // rw-- pin PA11 output enable bit
#define PA10OE                          0x400                                   // rw-- pin PA10 output enable bit
#define PA9OE                           0x200                                   // rw-- pin PA9 output enable bit
#define PA8OE                           0x100                                   // rw-- pin PA8 output enable bit
#define PA7OE                           0x80                                    // rw-- pin PA7 output enable bit
#define PA6OE                           0x40                                    // rw-- pin PA6 output enable bit
#define PA5OE                           0x20                                    // rw-- pin PA5 output enable bit
#define PA4OE                           0x10                                    // rw-- pin PA4 output enable bit
#define PA3OE                           0x08                                    // rw-- pin PA3 output enable bit
#define PA2OE                           0x04                                    // rw-- pin PA2 output enable bit
#define PA1OE                           0x02                                    // rw-- pin PA1 output enable bit
#define PA0OE                           0x01                                    // rw-- pin PA0 output enable bit
/********************** Bits definition for PA_PU register *********************/
#define PA15PU                          0x8000                                  // rw-- pin PA15pull-up enable bit
#define PA14PU                          0x4000                                  // rw-- pin PA14pull-up enable bit
#define PA13PU                          0x2000                                  // rw-- pin PA13pull-up enable bit
#define PA12PU                          0x1000                                  // rw-- pin PA12pull-up enable bit
#define PA11PU                          0x800                                   // rw-- pin PA11pull-up enable bit
#define PA10PU                          0x400                                   // rw-- pin PA10pull-up enable bit
#define PA9PU                           0x200                                   // rw-- pin PA9pull-up enable bit
#define PA8PU                           0x100                                   // rw-- pin PA8pull-up enable bit
#define PA7PU                           0x80                                    // rw-- pin PA7pull-up enable bit
#define PA6PU                           0x40                                    // rw-- pin PA6pull-up enable bit
#define PA5PU                           0x20                                    // rw-- pin PA5pull-up enable bit
#define PA4PU                           0x10                                    // rw-- pin PA4pull-up enable bit
#define PA3PU                           0x08                                    // rw-- pin PA3pull-up enable bit
#define PA2PU                           0x04                                    // rw-- pin PA2pull-up enable bit
#define PA1PU                           0x02                                    // rw-- pin PA1pull-up enable bit
#define PA0PU                           0x01                                    // rw-- pin PA0pull-up enable bit
/********************** Bits definition for PA_PL register *********************/
#define PA15PL                          0x8000                                  // rw-- pin PA15pull-down enable bit
#define PA14PL                          0x4000                                  // rw-- pin PA14pull-down enable bit
#define PA13PL                          0x2000                                  // rw-- pin PA13pull-down enable bit
#define PA12PL                          0x1000                                  // rw-- pin PA12pull-down enable bit
#define PA11PL                          0x800                                   // rw-- pin PA11pull-down enable bit
#define PA10PL                          0x400                                   // rw-- pin PA10pull-down enable bit
#define PA9PL                           0x200                                   // rw-- pin PA9pull-down enable bit
#define PA8PL                           0x100                                   // rw-- pin PA8pull-down enable bit
#define PA7PL                           0x80                                    // rw-- pin PA7pull-down enable bit
#define PA6PL                           0x40                                    // rw-- pin PA6pull-down enable bit
#define PA5PL                           0x20                                    // rw-- pin PA5pull-down enable bit
#define PA4PL                           0x10                                    // rw-- pin PA4pull-down enable bit
#define ODEN1                           0x08                                    // rw-- 
#define ODEN0                           0x04                                    // rw-- 
#define PA1PL                           0x02                                    // rw-- pin PA1pull-down enable bit
#define PA0PL                           0x01                                    // rw-- pin PA0pull-down enable bit

/********************** Bits definition for PB register *********************/
#define PB15                            0x8000                                  // rw-- pin PB15
#define PB14                            0x4000                                  // rw-- pin PB14
#define PB13                            0x2000                                  // rw-- pin PB13
#define PB12                            0x1000                                  // rw-- pin PB12
#define PB11                            0x800                                   // rw-- pin PB11
#define PB10                            0x400                                   // rw-- pin PB10
#define PB9                             0x200                                   // rw-- pin PB9
#define PB8                             0x100                                   // rw-- pin PB8
#define PB7                             0x80                                    // rw-- pin PB7
#define PB6                             0x40                                    // rw-- pin PB6
#define PB5                             0x20                                    // rw-- pin PB5
#define PB4                             0x10                                    // rw-- pin PB4
#define PB3                             0x08                                    // rw-- pin PB3
#define PB2                             0x04                                    // rw-- pin PB2
#define PB1                             0x02                                    // rw-- pin PB1
#define PB0                             0x01                                    // rw-- pin PB0
/********************** Bits definition for PB_OE register *********************/
#define PB15OE                          0x8000                                  // rw-- pin PB15 output enable bit
#define PB14OE                          0x4000                                  // rw-- pin PB14 output enable bit
#define PB13OE                          0x2000                                  // rw-- pin PB13 output enable bit
#define PB12OE                          0x1000                                  // rw-- pin PB12 output enable bit
#define PB11OE                          0x800                                   // rw-- pin PB11 output enable bit
#define PB10OE                          0x400                                   // rw-- pin PB10 output enable bit
#define PB9OE                           0x200                                   // rw-- pin PB9 output enable bit
#define PB8OE                           0x100                                   // rw-- pin PB8 output enable bit
#define PB7OE                           0x80                                    // rw-- pin PB7 output enable bit
#define PB6OE                           0x40                                    // rw-- pin PB6 output enable bit
#define PB5OE                           0x20                                    // rw-- pin PB5 output enable bit
#define PB4OE                           0x10                                    // rw-- pin PB4 output enable bit
#define PB3OE                           0x08                                    // rw-- pin PB3 output enable bit
#define PB2OE                           0x04                                    // rw-- pin PB2 output enable bit
#define PB1OE                           0x02                                    // rw-- pin PB1 output enable bit
#define PB0OE                           0x01                                    // rw-- pin PB0 output enable bit
/********************** Bits definition for PB_PU register *********************/
#define PB15PU                          0x8000                                  // rw-- pin PB15pull-up enable bit
#define PB14PU                          0x4000                                  // rw-- pin PB14pull-up enable bit
#define PB13PU                          0x2000                                  // rw-- pin PB13pull-up enable bit
#define PB12PU                          0x1000                                  // rw-- pin PB12pull-up enable bit
#define PB11PU                          0x800                                   // rw-- pin PB11pull-up enable bit
#define PB10PU                          0x400                                   // rw-- pin PB10pull-up enable bit
#define PB9PU                           0x200                                   // rw-- pin PB9pull-up enable bit
#define PB8PU                           0x100                                   // rw-- pin PB8pull-up enable bit
#define PB7PU                           0x80                                    // rw-- pin PB7pull-up enable bit
#define PB6PU                           0x40                                    // rw-- pin PB6pull-up enable bit
#define PB5PU                           0x20                                    // rw-- pin PB5pull-up enable bit
#define PB4PU                           0x10                                    // rw-- pin PB4pull-up enable bit
#define PB3PU                           0x08                                    // rw-- pin PB3pull-up enable bit
#define PB2PU                           0x04                                    // rw-- pin PB2pull-up enable bit
#define PB1PU                           0x02                                    // rw-- pin PB1pull-up enable bit
#define PB0PU                           0x01                                    // rw-- pin PB0pull-up enable bit
/********************** Bits definition for PB_AN register *********************/
#define PB15AN                          0x8000                                  // rw-- pin PB15analog enable bit
#define PB14AN                          0x4000                                  // rw-- pin PB14analog enable bit
#define PB13AN                          0x2000                                  // rw-- pin PB13analog enable bit
#define PB12AN                          0x1000                                  // rw-- pin PB12analog enable bit
#define PB11AN                          0x800                                   // rw-- pin PB11analog enable bit
#define PB10AN                          0x400                                   // rw-- pin PB10analog enable bit
#define PB9AN                           0x200                                   // rw-- pin PB9analog enable bit
#define PB8AN                           0x100                                   // rw-- pin PB8analog enable bit
#define PB7AN                           0x80                                    // rw-- pin PB7analog enable bit
#define PB6AN                           0x40                                    // rw-- pin PB6analog enable bit
#define PB5AN                           0x20                                    // rw-- pin PB5analog enable bit
#define PB4AN                           0x10                                    // rw-- pin PB4analog enable bit
#define PB3AN                           0x08                                    // rw-- pin PB3analog enable bit
#define PB1AN                           0x02                                    // rw-- pin PB1analog enable bit
#define PB0AN                           0x01                                    // rw-- pin PB0analog enable bit

/********************** Bits definition for PC register *********************/
#define PC15                            0x8000                                  // rw-- pin PC15
#define PC14                            0x4000                                  // rw-- pin PC14
#define PC13                            0x2000                                  // rw-- pin PC13
#define PC12                            0x1000                                  // rw-- pin PC12
#define PC11                            0x800                                   // rw-- pin PC11
#define PC10                            0x400                                   // rw-- pin PC10
#define PC9                             0x200                                   // rw-- pin PC9
#define PC8                             0x100                                   // rw-- pin PC8
#define PC7                             0x80                                    // rw-- pin PC7
#define PC6                             0x40                                    // rw-- pin PC6
#define PC5                             0x20                                    // rw-- pin PC5
#define PC4                             0x10                                    // rw-- pin PC4
#define PC3                             0x08                                    // rw-- pin PC3
#define PC2                             0x04                                    // rw-- pin PC2
#define PC1                             0x02                                    // rw-- pin PC1
#define PC0                             0x01                                    // rw-- pin PC0
/********************** Bits definition for PC_OE register *********************/
#define PC15OE                          0x8000                                  // rw-- pin PC15 output enable bit
#define PC14OE                          0x4000                                  // rw-- pin PC14 output enable bit
#define PC13OE                          0x2000                                  // rw-- pin PC13 output enable bit
#define PC12OE                          0x1000                                  // rw-- pin PC12 output enable bit
#define PC11OE                          0x800                                   // rw-- pin PC11 output enable bit
#define PC10OE                          0x400                                   // rw-- pin PC10 output enable bit
#define PC9OE                           0x200                                   // rw-- pin PC9 output enable bit
#define PC8OE                           0x100                                   // rw-- pin PC8 output enable bit
#define PC7OE                           0x80                                    // rw-- pin PC7 output enable bit
#define PC6OE                           0x40                                    // rw-- pin PC6 output enable bit
#define PC5OE                           0x20                                    // rw-- pin PC5 output enable bit
#define PC4OE                           0x10                                    // rw-- pin PC4 output enable bit
#define PC3OE                           0x08                                    // rw-- pin PC3 output enable bit
#define PC2OE                           0x04                                    // rw-- pin PC2 output enable bit
#define PC1OE                           0x02                                    // rw-- pin PC1 output enable bit
#define PC0OE                           0x01                                    // rw-- pin PC0 output enable bit
/********************** Bits definition for PC_PU register *********************/
#define PC15PU                          0x8000                                  // rw-- pin PC15pull-up enable bit
#define PC14PU                          0x4000                                  // rw-- pin PC14pull-up enable bit
#define PC13PU                          0x2000                                  // rw-- pin PC13pull-up enable bit
#define PC12PU                          0x1000                                  // rw-- pin PC12pull-up enable bit
#define PC11PU                          0x800                                   // rw-- pin PC11pull-up enable bit
#define PC10PU                          0x400                                   // rw-- pin PC10pull-up enable bit
#define PC9PU                           0x200                                   // rw-- pin PC9pull-up enable bit
#define PC8PU                           0x100                                   // rw-- pin PC8pull-up enable bit
#define PC7PU                           0x80                                    // rw-- pin PC7pull-up enable bit
#define PC6PU                           0x40                                    // rw-- pin PC6pull-up enable bit
#define PC5PU                           0x20                                    // rw-- pin PC5pull-up enable bit
#define PC4PU                           0x10                                    // rw-- pin PC4pull-up enable bit
#define PC3PU                           0x08                                    // rw-- pin PC3pull-up enable bit
#define PC2PU                           0x04                                    // rw-- pin PC2pull-up enable bit
#define PC1PU                           0x02                                    // rw-- pin PC1pull-up enable bit
#define PC0PU                           0x01                                    // rw-- pin PC0pull-up enable bit
/********************** Bits definition for PC_AN register *********************/
#define PC15AN                          0x8000                                  // rw-- pin PC15analog enable bit
#define PC14AN                          0x4000                                  // rw-- pin PC14analog enable bit
#define PC13AN                          0x2000                                  // rw-- pin PC13analog enable bit
#define PC12AN                          0x1000                                  // rw-- pin PC12analog enable bit
#define PC11AN                          0x800                                   // rw-- pin PC11analog enable bit
#define PC10AN                          0x400                                   // rw-- pin PC10analog enable bit
#define PC9AN                           0x200                                   // rw-- pin PC9analog enable bit
#define PC8AN                           0x100                                   // rw-- pin PC8analog enable bit
#define PC7AN                           0x80                                    // rw-- pin PC7analog enable bit
#define PC6AN                           0x40                                    // rw-- pin PC6analog enable bit
#define PC5AN                           0x20                                    // rw-- pin PC5analog enable bit
#define PC4AN                           0x10                                    // rw-- pin PC4analog enable bit
#define PC3AN                           0x08                                    // rw-- pin PC3analog enable bit
#define PC2AN                           0x04                                    // rw-- pin PC1analog enable bit
#define PC1AN                           0x02                                    // rw-- pin PC1analog enable bit
#define PC0AN                           0x01                                    // rw-- pin PC0analog enable bit

/********************** Bits definition for PD register *********************/
#define PD6                             0x40                                    // rw-- pin PD6
#define PD5                             0x20                                    // rw-- pin PD5
#define PD4                             0x10                                    // rw-- pin PD4
#define PD3                             0x08                                    // rw-- pin PD3
#define PD2                             0x04                                    // rw-- pin PD2
#define PD1                             0x02                                    // rw-- pin PD1
#define PD0                             0x01                                    // rw-- pin PD0
/********************** Bits definition for PD_OE register *********************/
#define PD6OE                           0x40                                    // rw-- pin PD6 output enable bit
#define PD5OE                           0x20                                    // rw-- pin PD5 output enable bit
#define PD4OE                           0x10                                    // rw-- pin PD4 output enable bit
#define PD3OE                           0x08                                    // rw-- pin PD3 output enable bit
#define PD2OE                           0x04                                    // rw-- pin PD2 output enable bit
#define PD1OE                           0x02                                    // rw-- pin PD1 output enable bit
#define PD0OE                           0x01                                    // rw-- pin PD0 output enable bit
/********************** Bits definition for PD_PU register *********************/
#define PD6PU                           0x40                                    // rw-- pin PD6pull-up enable bit
#define PD5PU                           0x20                                    // rw-- pin PD5pull-up enable bit
#define PD4PU                           0x10                                    // rw-- pin PD4pull-up enable bit
#define PD3PU                           0x08                                    // rw-- pin PD3pull-up enable bit
#define PD2PU                           0x04                                    // rw-- pin PD2pull-up enable bit
#define PD1PU                           0x02                                    // rw-- pin PD1pull-up enable bit
#define PD0PU                           0x01                                    // rw-- pin PD0pull-up enable bit
/********************** Bits definition for PD_AN register *********************/
#define PD6AN                           0x40                                    // rw-- pin PD6pull-up enable bit
#define PD5AN                           0x20                                    // rw-- pin PD5pull-up enable bit
#define PD4AN                           0x10                                    // rw-- pin PD4pull-up enable bit
#define PD3AN                           0x08                                    // rw-- pin PD3pull-up enable bit
#define PD2AN                           0x04                                    // rw-- pin PD2pull-up enable bit
#define PD1AN                           0x02                                    // rw-- pin PD1pull-up enable bit
#define PD0AN                           0x01                                    // rw-- pin PD0pull-up enable bit

/********************** Bits definition for Portx register *********************/
#define PIN15                           0x8000                                  // rw-- pin xPx15
#define PIN14                           0x4000                                  // rw-- pin xPx14
#define PIN13                           0x2000                                  // rw-- pin xPx13
#define PIN12                           0x1000                                  // rw-- pin xPx12
#define PIN11                           0x800                                   // rw-- pin xPx11
#define PIN10                           0x400                                   // rw-- pin xPx10
#define PIN9                            0x200                                   // rw-- pin xPx9
#define PIN8                            0x100                                   // rw-- pin xPx8
#define PIN7                            0x80                                    // rw-- pin xPx7
#define PIN6                            0x40                                    // rw-- pin xPx6
#define PIN5                            0x20                                    // rw-- pin xPx5
#define PIN4                            0x10                                    // rw-- pin xPx4
#define PIN3                            0x08                                    // rw-- pin xPx3
#define PIN2                            0x04                                    // rw-- pin xPx2
#define PIN1                            0x02                                    // rw-- pin xPx1
#define PIN0                            0x01                                    // rw-- pin xPx0
/********************* Bits definition for PH_SEL register ********************/
#define SFRCT                           0x80000000                              // rw-- Tamagawa RE function remap bit
#define T5CT                            0x40000000                              // rw-- Timer5 pin function remap bit
#define T8CT1                           0x20000000                              // rw-- Timer8 pin enable bit 1
#define T8CT0                           0x10000000                              // rw-- Timer8 pin enable bit 0
#define DBGCT                           0x8000000                               // rw-- DBG pin enable
#define DTCT                            0x4000000                               // rw-- DT pin enable          /* factory */
#define CMPCT                           0x2000000                               // rw-- Comparator pin enable bit
#define MONCT1                          0x1000000                               // rw-- DataMonitor pin enable bit 1
#define MONCT0                          0x800000                                // rw-- DataMonitor pin enable bit 1
#define SPI2TMOD                        0x400000                                // rw-- SPI2MISO high-impedance
#define SPI1TMOD                        0x200000                                // rw-- SPI1MISO high-impedance
#define I2CCT                           0x100000                                // rw-- I2C pin enable bit
#define CANCT                           0x80000                                 // rw-- CAN pin enable bit
#define LINCT                           0x40000                                 // rw-- LIN pin enable bit
#define UT2CT1                          0x20000                                 // rw-- Uart2 pin enable bit 1
#define UT2CT0                          0x10000                                 // rw-- Uart2 pin enable bit 0
#define UT1CT1                          0x8000                                  // rw-- Uart1 pin enable bit 1
#define UT1CT0                          0x4000                                  // rw-- Uart1 pin enable bit 0
#define T7CT1                           0x2000                                  // rw-- Timer7 pin enable bit 1
#define T7CT0                           0x1000                                  // rw-- Timer7 pin enable bit 0
#define T6BCT                           0x800                                   // rw-- Timer6 pin B enable bit
#define T6ACT1                          0x400                                   // rw-- Timer6 pin A enable bit
#define T6ACT0                          0x200                                   // rw-- Timer6 pin A function remap bit 0
#define T5BCT                           0x100                                   // rw-- Timer5 pin B enable bit
#define T5ACT                           0x80                                    // rw-- Timer5 pin A enable bit
#define T4CT1                           0x40                                    // rw-- Timer4 pin enable bit 1
#define T4CT0                           0x20                                    // rw-- Timer4 pin enable bit 0
#define T3CT1                           0x10                                    // rw-- Timer3 pin enable bit 1
#define T3CT0                           0x08                                    // rw-- Timer3 pin enable bit 0
#define SPICT                           0x04                                    // rw-- SPI function remap
#define T2BCT                           0x02                                    // rw-- Timer2 pin B enable bit
#define T2ACT                           0x01                                    // rw-- Timer2 pin A enable bit

/******************************************************************************/
/*                                     IRQ                                    */
/******************************************************************************/
/********************** Bits definition for MIE register **********************/
 #define IRQ_EN                         0x00000008                              // rw-- Global interrupt enable bit
/********************** Bits definition for PIE register **********************/
 #define RTCIE                          0x10                                    // rw-- RTC interrupt enable bit
 #define TSDIE                          0x08                                    // rw0- TSD interrupt enable bit
 #define EX2                            0x04                                    // rw-- External interrupt 2 enable bit
 #define EX1                            0x02                                    // rw-- External interrupt 1 enable bit
 #define EX0                            0x01                                    // rw-- External interrupt 0 enable bit
/********************* Bits definition for TCON register **********************/
 #define TSDIF                          0x40                                    // rw-- TSD interrupt flag
 #define IT21                           0x20                                    // rw-- External interrupt 2 trigger level select1
 #define IT20                           0x10                                    // rw-- External interrupt 2 trigger level select0
 #define IT11                           0x08                                    // rw-- External interrupt 1 trigger level select1
 #define IT10                           0x04                                    // rw-- External interrupt 1 trigger level select0
 #define IT01                           0x02                                    // rw-- External interrupt 0 trigger level select1
 #define IT00                           0x01                                    // rw-- External interrupt 0 trigger level select0
/********************* Bits definition for LVSR register **********************/
 #define TSDF                           0x04                                    // r--- Over-temperature flag /* factory */
 #define LVWF                           0x02                                    // r--- VCC low voltage warning flag
 #define LVWIF                          0x01                                    // rw0- VCC low voltage warning interrupt flag 
/********************* Bits definition for EX0IE register **********************/
 #define EX0IE15                        0x8000                                  // rw-- PD3port external interrupt0interrupt enable bit
 #define EX0IE14                        0x4000                                  // rw-- PD1port external interrupt0interrupt enable bit
 #define EX0IE13                        0x2000                                  // rw-- PD0port external interrupt0interrupt enable bit
 #define EX0IE12                        0x1000                                  // rw-- PA12port external interrupt0interrupt enable bit
 #define EX0IE11                        0x0800                                  // rw-- PA11port external interrupt0interrupt enable bit
 #define EX0IE10                        0x0400                                  // rw-- PA10port external interrupt0interrupt enable bit
 #define EX0IE9                         0x0200                                  // rw-- PA9port external interrupt0interrupt enable bit
 #define EX0IE8                         0x0100                                  // rw-- PA8port external interrupt0interrupt enable bit
 #define EX0IE7                         0x0080                                  // rw-- PA7port external interrupt0interrupt enable bit
 #define EX0IE6                         0x0040                                  // rw-- PA6port external interrupt0interrupt enable bit
 #define EX0IE5                         0x0020                                  // rw-- PA5port external interrupt0interrupt enable bit
 #define EX0IE4                         0x0010                                  // rw-- PA4port external interrupt0interrupt enable bit
 #define EX0IE3                         0x0008                                  // rw-- PA3port external interrupt0interrupt enable bit
 #define EX0IE2                         0x0004                                  // rw-- PA2port external interrupt0interrupt enable bit
 #define EX0IE1                         0x0002                                  // rw-- PA1port external interrupt0interrupt enable bit
 #define EX0IE0                         0x0001                                  // rw-- PA0port external interrupt0interrupt enable bit
/********************* Bits definition for EX1IE register **********************/
 #define EX1IE15                        0x8000                                  // rw-- PB2port external interrupt1interrupt enable bit
 #define EX1IE14                        0x4000                                  // rw-- PA14port external interrupt1interrupt enable bit
 #define EX1IE13                        0x2000                                  // rw-- PA12port external interrupt1interrupt enable bit
 #define EX1IE12                        0x1000                                  // rw-- PA12port external interrupt1interrupt enable bit
 #define EX1IE11                        0x0800                                  // rw-- PA11port external interrupt1interrupt enable bit
 #define EX1IE10                        0x0400                                  // rw-- PA10port external interrupt1interrupt enable bit
 #define EX1IE9                         0x0200                                  // rw-- PA9port external interrupt1interrupt enable bit
 #define EX1IE8                         0x0100                                  // rw-- PA8port external interrupt1interrupt enable bit
 #define EX1IE7                         0x0080                                  // rw-- PA7port external interrupt1interrupt enable bit
 #define EX1IE6                         0x0040                                  // rw-- PA6port external interrupt1interrupt enable bit
 #define EX1IE5                         0x0020                                  // rw-- PA5port external interrupt1interrupt enable bit
 #define EX1IE4                         0x0010                                  // rw-- PA4port external interrupt1interrupt enable bit
 #define EX1IE3                         0x0008                                  // rw-- PA3port external interrupt1interrupt enable bit
 #define EX1IE2                         0x0004                                  // rw-- PA2port external interrupt1interrupt enable bit
 #define EX1IE1                         0x0002                                  // rw-- PA1port external interrupt1interrupt enable bit
 #define EX1IE0                         0x0001                                  // rw-- PA0port external interrupt1interrupt enable bit
 /********************* Bits definition for EX2IE register **********************/
 #define EX2IE15                        0x8000                                  // rw-- PC7port external interrupt2interrupt enable bit
 #define EX2IE14                        0x4000                                  // rw-- PC6port external interrupt2interrupt enable bit
 #define EX2IE13                        0x2000                                  // rw-- PC5port external interrupt2interrupt enable bit
 #define EX2IE12                        0x1000                                  // rw-- PC4port external interrupt2interrupt enable bit
 #define EX2IE11                        0x0800                                  // rw-- PC3port external interrupt2interrupt enable bit
 #define EX2IE10                        0x0400                                  // rw-- PC2port external interrupt2interrupt enable bit
 #define EX2IE9                         0x0200                                  // rw-- PC1port external interrupt2interrupt enable bit
 #define EX2IE8                         0x0100                                  // rw-- PC0port external interrupt2interrupt enable bit
 #define EX2IE7                         0x0080                                  // rw-- PB7port external interrupt2interrupt enable bit
 #define EX2IE6                         0x0040                                  // rw-- PB6port external interrupt2interrupt enable bit
 #define EX2IE5                         0x0020                                  // rw-- PB5port external interrupt2interrupt enable bit
 #define EX2IE4                         0x0010                                  // rw-- PB4port external interrupt2interrupt enable bit
 #define EX2IE3                         0x0008                                  // rw-- PB3port external interrupt2interrupt enable bit
 #define EX2IE2                         0x0004                                  // rw-- PB2port external interrupt2interrupt enable bit
 #define EX2IE1                         0x0002                                  // rw-- PB1port external interrupt2interrupt enable bit
 #define EX2IE0                         0x0001                                  // rw-- PB0port external interrupt2interrupt enable bit
/********************* Bits definition for EX0IF register **********************/
 #define EX0IF15                        0x8000                                  // rw0- PD3port external interrupt0interrupt flag
 #define EX0IF14                        0x4000                                  // rw0- PD1port external interrupt0interrupt flag
 #define EX0IF13                        0x2000                                  // rw0- PD0port external interrupt0interrupt flag
 #define EX0IF12                        0x1000                                  // rw0- PA12port external interrupt0interrupt flag
 #define EX0IF11                        0x0800                                  // rw0- PA11port external interrupt0interrupt flag
 #define EX0IF10                        0x0400                                  // rw0- PA10port external interrupt0interrupt flag
 #define EX0IF9                         0x0200                                  // rw0- PA9port external interrupt0interrupt flag
 #define EX0IF8                         0x0100                                  // rw0- PA8port external interrupt0interrupt flag
 #define EX0IF7                         0x0080                                  // rw0- PA7port external interrupt0interrupt flag
 #define EX0IF6                         0x0040                                  // rw0- PA6port external interrupt0interrupt flag
 #define EX0IF5                         0x0020                                  // rw0- PA5port external interrupt0interrupt flag
 #define EX0IF4                         0x0010                                  // rw0- PA4port external interrupt0interrupt flag
 #define EX0IF3                         0x0008                                  // rw0- PA3port external interrupt0interrupt flag
 #define EX0IF2                         0x0004                                  // rw0- PA2port external interrupt0interrupt flag
 #define EX0IF1                         0x0002                                  // rw0- PA1port external interrupt0interrupt flag
 #define EX0IF0                         0x0001                                  // rw0- PA0port external interrupt0interrupt flag
/********************* Bits definition for EX1IF register **********************/
 #define EX1IF15                        0x8000                                  // rw0- PB2port external interrupt1interrupt flag
 #define EX1IF14                        0x4000                                  // rw0- PA14port external interrupt1interrupt flag
 #define EX1IF13                        0x2000                                  // rw0- PA12port external interrupt1interrupt flag
 #define EX1IF12                        0x1000                                  // rw0- PA12port external interrupt1interrupt flag
 #define EX1IF11                        0x0800                                  // rw0- PA11port external interrupt1interrupt flag
 #define EX1IF10                        0x0400                                  // rw0- PA10port external interrupt1interrupt flag
 #define EX1IF9                         0x0200                                  // rw0- PA9port external interrupt1interrupt flag
 #define EX1IF8                         0x0100                                  // rw0- PA8port external interrupt1interrupt flag
 #define EX1IF7                         0x0080                                  // rw0- PA7port external interrupt1interrupt flag
 #define EX1IF6                         0x0040                                  // rw0- PA6port external interrupt1interrupt flag
 #define EX1IF5                         0x0020                                  // rw0- PA5port external interrupt1interrupt flag
 #define EX1IF4                         0x0010                                  // rw0- PA4port external interrupt1interrupt flag
 #define EX1IF3                         0x0008                                  // rw0- PA3port external interrupt1interrupt flag
 #define EX1IF2                         0x0004                                  // rw0- PA2port external interrupt1interrupt flag
 #define EX1IF1                         0x0002                                  // rw0- PA1port external interrupt1interrupt flag
 #define EX1IF0                         0x0001                                  // rw0- PA0port external interrupt1interrupt flag
 /********************* Bits definition for EX2IF register **********************/
 #define EX2IF15                        0x8000                                  // rw0- PC7port external interrupt2interrupt flag
 #define EX2IF14                        0x4000                                  // rw0- PC6port external interrupt2interrupt flag
 #define EX2IF13                        0x2000                                  // rw0- PC5port external interrupt2interrupt flag
 #define EX2IF12                        0x1000                                  // rw0- PC4port external interrupt2interrupt flag
 #define EX2IF11                        0x0800                                  // rw0- PC3port external interrupt2interrupt flag
 #define EX2IF10                        0x0400                                  // rw0- PC2port external interrupt2interrupt flag
 #define EX2IF9                         0x0200                                  // rw0- PC1port external interrupt2interrupt flag
 #define EX2IF8                         0x0100                                  // rw0- PC0port external interrupt2interrupt flag
 #define EX2IF7                         0x0080                                  // rw0- PB7port external interrupt2interrupt flag
 #define EX2IF6                         0x0040                                  // rw0- PB6port external interrupt2interrupt flag
 #define EX2IF5                         0x0020                                  // rw0- PB5port external interrupt2interrupt flag
 #define EX2IF4                         0x0010                                  // rw0- PB4port external interrupt2interrupt flag
 #define EX2IF3                         0x0008                                  // rw0- PB3port external interrupt2interrupt flag
 #define EX2IF2                         0x0004                                  // rw0- PB2port external interrupt2interrupt flag
 #define EX2IF1                         0x0002                                  // rw0- PB1port external interrupt2interrupt flag
 #define EX2IF0                         0x0001                                  // rw0- PB0port external interrupt2interrupt flag

/******************************************************************************/
/*                                   Clock                                    */
/******************************************************************************/
/******************** Bits definition for CK_CR register *********************/
 #define TIM8CKEN                       0x80000                                 // rw-- TIM8 module clock enable
 #define I2C2CKEN                       0x40000                                 // rw-- I2C2 module clock enable
 #define SFCKEN                         0x20000                                 // rw-- SF module clock enable
 #define BISSCKEN                       0x10000                                 // rw-- BiSS module clock enable
 #define DRV2CKEN                       0x8000                                  // rw-- DRV2 module clock enable
 #define DRVCKEN                        0x4000                                  // rw-- DRV module clock enable
 #define PFCCKEN                        0x2000                                  // rw-- PFC module clock enable
 #define UART2CKEN                      0x1000                                  // rw-- Uart2 module clock enable
 #define UARTCKEN                       0x800                                   // rw-- Uart module clock enable
 #define LINCKEN                        0x400                                   // rw-- LIN module clock enable
 #define SPI2CKEN                       0x200                                   // rw-- SPI2 module clock enable
 #define SPICKEN                        0x100                                   // rw-- SPI module clock enable
 #define I2CCKEN                        0x80                                    // rw-- I2C module clock enable
 #define CANCKEN                        0x40                                    // rw-- CAN module clock enable
 #define T7CKEN                         0x20                                    // rw-- Timer7 module clock enable
 #define T6CKEN                         0x10                                    // rw-- Timer6 module clock enable
 #define T5CKEN                         0x08                                    // rw-- Timer5 module clock enable
 #define T4CKEN                         0x04                                    // rw-- Timer4 module clock enable
 #define T3CKEN                         0x02                                    // rw-- Timer3 module clock enable
 #define T2CKEN                         0x01                                    // rw-- Timer2 module clock enable


/******************************************************************************/


/******************************************************************************/
/*                                   Special                                  */
/******************************************************************************/
/******************** Bits definition for RST_SR register *********************/
 #define RSTPOW                         0x80                                    // r--- Power-on reset flag
 #define RSTEXT                         0x40                                    // r--- External reset flag
 #define RSTLVD                         0x20                                    // r--- Low voltage reset flag
 #define RSTEOS                         0x10                                    // r--- Electrical stress over-reset flag  /* factory */
 #define RSTWDT                         0x08                                    // r--- Watchdog reset flag
 #define RSTFED                         0x04                                    // r--- Code protection reset
 #define RSTDBG                         0x02                                    // r--- Debug interface reset
 #define SOFTRST                        0x01                                    // r--- Software reset flag
/******************** Bits definition for RST_CR register *********************/
 #define WKRE                           0x20                                    // rw-- MON wakeup enable
 #define WKPOLAR                        0x10                                    // rw-- MON input (PA9) wakeup level
 #define SFRST                          0x02                                    // w1-- Software reset
 #define RSTCLR                         0x01                                    // w1-- Reset flag clear
/********************** Bits definition for PCON register *********************/
 #define LDOM                           0x04                                    // rw--
 #define STOP                           0x02                                    // rw-- MCU sleep enable
 #define IDEL                           0x01                                    // rw-- MCU standby enable
/******************* Bits definition for FLA_KEY register **********************/
 #define FLAKSTA1                       0x02                                    // r--- Flash unlock status bit 1
 #define FLAKSTA0                       0x01                                    // r--- Flash unlock status bit 0
/******************** Bits definition for FLA_CR register *********************/
 #define FLAERR                         0x8000                                  // r--- Flash operation error flag
 #define FLABT2CRCERR                   0x4000                                  // r--- Flash Boot second checksum error flag /* factory */
 #define FLABT1CRCERR                   0x2000                                  // r--- Flash Boot first checksum error flag /* factory */
 #define FLAM0ERR                       0x1000                                  // r--- Flash Margin0 error flag
 #define FLAMARGIN1                     0x0100                                  // rw-- Flash Margin1 test mode enable
 #define FLAECCMANUAL                   0x0080                                  // rw-- Flash ECC manual byte fill enable /* factory */
 #define FLAECC                         0x0040                                  // rw-- Flash ECC byte programming enable
 #define FLASIZE                        0x0020                                  // rw-- Flash programming length configuration
 #define FLACHIP                        0x0010                                  // rw-- Flash full-chip operation enable
 #define FLAPAGE                        0x0008                                  // rw-- Flash page operation enable
 #define FLAPRE                         0x0004                                  // rw-- Flash pre-programming enable
 #define FLAERS                         0x0002                                  // rw-- Flash erase enable
 #define FLAEN                          0x0001                                  // rw-- Flash programming enable

/******************************************************************************/
/*                                    ECC                                     */
/******************************************************************************/
/******************** Bits definition for FLA_ECC_CR register *********************/
 #define ECC_ARR_MASK                   0xf8000000                              // rw-- Multi-ECC error interrupt trigger threshold mask
 #define ECC_LMERR_CEN                  0x00000100                              // rw-- Multi-bit ECC error count enable on data fetch
 #define ECC_LERR_CEN                   0x00000080                              // rw-- Single-bit ECC error count enable on data fetch
 #define ECC_MERR_IE                    0x00000040                              // rw-- Multi-ECC error interrupt enable
 #define ECC_CMERR_IE                   0x00000008                              // rw-- Multi-bit ECC error interrupt enable on instruction fetch
 #define ECC_CERR_IE                    0x00000004                              // rw-- Single-bit ECC error interrupt enable on instruction fetch
 #define ECC_LMERR_IE                   0x00000002                              // rw-- Multi-bit ECC error interrupt enable on data fetch
 #define ECC_LERR_IE                    0x00000001                              // rw-- Single-bit ECC error interrupt enable on data fetch

/******************** Bits definition for FLA_ECC_SR register *********************/
 #define ECC_CNTR_MASK                  0xf8000000                              // r--- ECC error accumulated count mask
 #define ECC_MERR_IF                    0x00000040                              // rw0- Multi-ECC error interrupt flag
 #define ECC_BMERR_IF                   0x00000020                              // rw0- Multi-bit ECC error during boot /* factory */
 #define ECC_BERR_IF                    0x00000010                              // rw0- Single-bit ECC error during boot /* factory */
 #define ECC_CMERR_IF                   0x00000008                              // rw0- Multi-bit ECC error interrupt flag on instruction fetch
 #define ECC_CERR_IF                    0x00000004                              // rw0- Single-bit ECC error interrupt flag on instruction fetch
 #define ECC_LMERR_IF                   0x00000002                              // rw0- Multi-bit ECC error interrupt flag on data fetch
 #define ECC_LERR_IF                    0x00000001                              // rw0- Single-bit ECC error interrupt flag on data fetch

/******************************************************************************/
/*                                     CMP                                    */
/******************************************************************************/
/******************** Bits definition for CMP_CR0 register ********************/
 #define CMP5IM1                        0x800                                   // rw-- CMP5Interrupt mode config1
 #define CMP5IM0                        0x400                                   // rw-- CMP5Interrupt mode config0
 #define CMP4IM1                        0x200                                   // rw-- CMP4Interrupt mode config1
 #define CMP4IM0                        0x100                                   // rw-- CMP4Interrupt mode config0
 #define CMP3IM1                        0x80                                    // rw-- CMP3Interrupt mode config1
 #define CMP3IM0                        0x40                                    // rw-- CMP3Interrupt mode config0
 #define CMP2IM1                        0x20                                    // rw-- CMP2Interrupt mode config1
 #define CMP2IM0                        0x10                                    // rw-- CMP2Interrupt mode config0
 #define CMP1IM1                        0x08                                    // rw-- CMP1Interrupt mode config1
 #define CMP1IM0                        0x04                                    // rw-- CMP1Interrupt mode config0
 #define CMP0IM1                        0x02                                    // rw-- CMP0Interrupt mode config1
 #define CMP0IM0                        0x01                                    // rw-- CMP0Interrupt mode config0
/******************** Bits definition for CMP_CR1 register ********************/
 #define CMP3P4MFS                      0x1000                                  // rw-- CMP3P/CMP4MFunction remap enable
 #define CMP11HYS                       0x800                                   // rw-- CMP11Hysteresis enable
 #define CMP5HYS                        0x400                                   // rw-- CMP5Hysteresis enable
 #define CMP11EN                        0x200                                   // rw-- CMP11enable bit
 #define CMP5EN                         0x100                                   // rw-- CMP5enable bit
 #define CMP4EN                         0x80                                    // rw-- CMP4enable bit
 #define CMP3MOD1                       0x40                                    // rw-- CMP3Positive input select config1
 #define CMP3MOD0                       0x20                                    // rw-- CMP3Positive input select config0
 #define CMP3EN                         0x10                                    // rw-- CMP3enable bit
 #define CMP3HYS                        0x08                                    // rw-- CMP3Hysteresis enable
 #define I2CCT2                         0x04                                    // rw-- I2Cfunction remap2
 #define CMP0HYS1                       0x02                                    // rw-- CMP1Hysteresis config1
 #define CMP0HYS0                       0x01                                    // rw-- CMP1Hysteresis config0
/******************** Bits definition for CMP_CR2 register ********************/
 #define CMPSAMSEL1                     0x800                                   // rw-- CMP0, CMP1, CMP2 and ADC sample delay config bit1
 #define CMPSAMSEL0                     0x400                                   // rw-- CMP0, CMP1, CMP2 and ADC sample delay config bit0
 #define HALL0EN                        0x100                                   // rw-- HALL0enable bit
 #define CMP0FS                         0x80                                    // rw-- Comparator 0 filter coefficient config
 #define CMP0MOD1                       0x40                                    // rw-- CMP0Positive input select config1
 #define CMP0MOD0                       0x20                                    // rw-- CMP0Positive input select config0
 #define CMP0SEL1                       0x10                                    // rw-- Comparator 0 output select config1
 #define CMP0SEL0                       0x08                                    // rw-- Comparator 0 output select config0
 #define CMP0CKSEL1                     0x04                                    // rw-- CMP0polling time setting1 /* factory */
 #define CMP0CKSEL0                     0x02                                    // rw-- CMP0polling time setting0 /* factory */
 #define CMP0EN                         0x01                                    // rw-- CMP0enable bit
/******************** Bits definition for CMP_CR3 register ********************/
 #define CMP5FSEL1                      0x800                                   // rw-- CMP5Filter coefficient config1
 #define CMP5FSEL0                      0x400                                   // rw-- CMP5Filter coefficient config0
 #define CMP9FSEL1                      0x200                                   // rw-- CMP9Filter coefficient config1 
 #define CMP9FSEL0                      0x100                                   // rw-- CMP9Filter coefficient config0
 #define CMP3FSEL1                      0x80                                    // rw-- CMP3Filter coefficient config1
 #define CMP3FSEL0                      0x40                                    // rw-- CMP3Filter coefficient config0
 #define CMP6FSEL2                      0x20                                    // rw-- CMP6Filter coefficient config2
 #define CMP6FSEL1                      0x10                                    // rw-- CMP6Filter coefficient config1
 #define CMP6FSEL0                      0x08                                    // rw-- CMP6Filter coefficient config0
 #define CMP0FSEL2                      0x04                                    // rw-- CMP0Filter coefficient config2
 #define CMP0FSEL1                      0x02                                    // rw-- CMP0Filter coefficient config1
 #define CMP0FSEL0                      0x01                                    // rw-- CMP0Filter coefficient config0
/********************* Bits definition for CMP_SR register ********************/
 #define CMP11OUT                       0x800                                   // r--- CMP11compare result 
 #define CMP10OUT                       0x400                                   // r--- CMP10compare result
 #define CMP9OUT                        0x200                                   // r--- CMP9compare result
 #define CMP8OUT                        0x100                                   // r--- CMP8compare result
 #define CMP7OUT                        0x80                                    // r--- CMP7compare result
 #define CMP6OUT                        0x40                                    // r--- CMP6compare result
 #define CMP5OUT                        0x20                                    // r--- CMP5compare result
 #define CMP4OUT                        0x10                                    // r--- CMP4compare result
 #define CMP3OUT                        0x08                                    // r--- CMP3compare result
 #define CMP2OUT                        0x04                                    // r--- CMP2compare result
 #define CMP1OUT                        0x02                                    // r--- CMP1compare result
 #define CMP0OUT                        0x01                                    // r--- CMP0compare result
/********************* Bits definition for CMP_IFR register ********************/
 #define CMP11IF                        0x800                                   // rw0- CMP11interrupt flag
 #define CMP10IF                        0x400                                   // rw0- CMP10interrupt flag
 #define CMP9IF                         0x200                                   // rw0- CMP9interrupt flag
 #define CMP8IF                         0x100                                   // rw0- CMP8interrupt flag
 #define CMP7IF                         0x80                                    // rw0- CMP7interrupt flag
 #define CMP6IF                         0x40                                    // rw0- CMP6interrupt flag
 #define CMP5IF                         0x20                                    // rw0- CMP5interrupt flag
 #define CMP4IF                         0x10                                    // rw0- CMP4interrupt flag
 #define CMP3IF                         0x08                                    // rw0- CMP3interrupt flag
 #define CMP2IF                         0x04                                    // rw0- CMP2interrupt flag
 #define CMP1IF                         0x02                                    // rw0- CMP1interrupt flag
 #define CMP0IF                         0x01                                    // rw0- CMP0interrupt flag
/********************* Bits definition for CMP_DBR register ********************/
#define DBG2SEL4                       0x4000                                  // rw-- DBG2Signal source select bit4
#define DBG2SEL3                       0x2000                                  // rw-- DBG2Signal source select bit3
#define DBG2SEL2                       0x1000                                  // rw-- DBG2Signal source select bit2
#define DBG2SEL1                       0x800                                   // rw-- DBG2Signal source select bit1
#define DBG2SEL0                       0x400                                   // rw-- DBG2Signal source select bit0
#define DBG1SEL4                       0x200                                   // rw-- DBG1Signal source select bit4
#define DBG1SEL3                       0x100                                   // rw-- DBG1Signal source select bit3
#define DBG1SEL2                       0x80                                    // rw-- DBG1Signal source select bit2
#define DBG1SEL1                       0x40                                    // rw-- DBG1Signal source select bit1
#define DBG1SEL0                       0x20                                    // rw-- DBG1Signal source select bit0
#define CMPSEL4                        0x10                                    // rw-- comparatoroutputSignal source select bit4
#define CMPSEL3                        0x08                                    // rw-- comparatoroutputSignal source select bit3
#define CMPSEL2                        0x04                                    // rw-- comparatoroutputSignal source select bit2
#define CMPSEL1                        0x02                                    // rw-- comparatoroutputSignal source select bit1
#define CMPSEL0                        0x01                                    // rw-- comparatoroutputSignal source select bit0
/******************** Bits definition for CMP_CR4 register ********************/
 #define CMP11IM1                       0x800                                   // rw-- CMP11Interrupt mode config1
 #define CMP11IM0                       0x400                                   // rw-- CMP11Interrupt mode config0
 #define CMP10IM1                       0x200                                   // rw-- CMP10Interrupt mode config1
 #define CMP10IM0                       0x100                                   // rw-- CMP10Interrupt mode config0
 #define CMP9IM1                        0x80                                    // rw-- CMP9Interrupt mode config1
 #define CMP9IM0                        0x40                                    // rw-- CMP9Interrupt mode config0
 #define CMP8IM1                        0x20                                    // rw-- CMP8Interrupt mode config1
 #define CMP8IM0                        0x10                                    // rw-- CMP8Interrupt mode config0
 #define CMP7IM1                        0x08                                    // rw-- CMP7Interrupt mode config1
 #define CMP7IM0                        0x04                                    // rw-- CMP7Interrupt mode config0
 #define CMP6IM1                        0x02                                    // rw-- CMP6Interrupt mode config1
 #define CMP6IM0                        0x01                                    // rw-- CMP6Interrupt mode config0
/******************** Bits definition for CMP_CR5 register ********************/
 #define CMP9P10MFS                     0x100                                   // rw-- CMP9P/CMP10MFunction remap enable
 #define CMP10EN                        0x80                                    // rw-- CMP10enable bit
 #define CMP9MOD1                       0x40                                    // rw-- CMP9Positive input select config1
 #define CMP9MOD0                       0x20                                    // rw-- CMP9Positive input select config0
 #define CMP9EN                         0x10                                    // rw-- CMP9enable bit
 #define CMP9HYS                        0x08                                    // rw-- CMP9Hysteresis enable
 #define STRCT							0x04                                    // rw-- Probefunction remapbit: 0-PA14, PA15; 1-PC6, PC7
 #define CMP6HYS1                       0x02                                    // rw-- CMP6Hysteresis enable1
 #define CMP6HYS0                       0x01                                    // rw-- CMP6Hysteresis enable0
/******************** Bits definition for CMP_CR6 register *******************/
 #define CMPSAM1EN                      0x800                                   // rw-- CMP6, CMP7 and CMP8sampling delayconfigbit1
 #define CMPSAMN1EN                     0x400                                   // rw-- CMP6, CMP7 and CMP8sampling delayconfigbit0
 #define SFRCT2							0x200                                   // rw-- Tamagawa RE function remap bit 2
 #define HALL1EN                        0x100                                   // rw-- HALL1enable bit
 #define CMP6FS                         0x80                                    // rw-- CMP6Filter coefficient configbit
 #define CMP6MOD1                       0x40                                    // rw-- CMP6Positive input select config1
 #define CMP6MOD0                       0x20                                    // rw-- CMP6Positive input select config0
 #define CMP6SEL1                       0x10                                    // rw-- comparator6outputselectconfig1
 #define CMP6SEL0                       0x08                                    // rw-- comparator6outputselectconfig0
 #define CMP6CKSEL1                     0x04                                    // rw-- CMP6polling time setting1 /* factory */
 #define CMP6CKSEL0                     0x02                                    // rw-- CMP6polling time setting0 /* factory */
 #define CMP6EN                         0x01                                    // rw-- CMP6enable bit

/******************************************************************************/
/*                                     AMP                                    */
/******************************************************************************/
/***************** Bits definition for VREF_VHALF_CR register *****************/
 #define VHAFSEL1                       0x200                                   // rw-- VHALFvoltage selectVREFcoefficient config1
 #define VHAFSEL0                       0x100                                   // rw-- VHALFvoltage selectVREFcoefficient config0
 #define VREFSEL1                       0x80                                    // rw-- VREFvoltage config1
 #define VREFSEL0                       0x40                                    // rw-- VREFvoltage config0
 #define VREFEN                         0x10                                    // rw-- VREFenable bit
 #define VHALFEN                        0x01                                    // rw-- VHALFenable bit
/******************** Bits definition for AMP_CR0 register ********************/
 #define AMP56MGND                      0x400                                   // rw-- Op-amp56negative input to GND
 #define AMP4MGND                       0x200                                   // rw-- Op-amp4negative input to GND
 #define AMP12MGND                      0x100                                   // rw-- Op-amp12negative input to GND
 #define AMP0MGND                       0x80                                    // rw-- Op-amp0negative input to GND
 #define AMP6EN                         0x40                                    // rw-- AMP6enable bit
 #define AMP5EN                         0x20                                    // rw-- AMP5enable bit
 #define AMP4EN                         0x10                                    // rw-- AMP4enable bit
 #define AMP3EN                         0x08                                    // rw-- AMP3enable bit
 #define AMP2EN                         0x04                                    // rw-- AMP2enable bit
 #define AMP1EN                         0x02                                    // rw-- AMP1enable bit
 #define AMP0EN                         0x01                                    // rw-- AMP0enable bit
/******************** Bits definition for AMP_CR1 register ********************/
 #define AMPPH56GAIN2                   0x4000                                  // rw-- Op-amp56Gain config2
 #define AMPPH56GAIN1                   0x2000                                  // rw-- Op-amp56Gain config1
 #define AMPPH56GAIN0                   0x1000                                  // rw-- Op-amp56Gain config0
 #define AMPPH12GAIN2                   0x800                                   // rw-- Op-amp12Gain config2
 #define AMPPH12GAIN1                   0x400                                   // rw-- Op-amp12Gain config1
 #define AMPPH12GAIN0                   0x200                                   // rw-- Op-amp12Gain config0
 #define AMP4GAIN2                      0x100                                   // rw-- Op-amp4Gain config2
 #define AMP4GAIN1                      0x80                                    // rw-- Op-amp4Gain config1
 #define AMP4GAIN0                      0x40                                    // rw-- Op-amp4Gain config0
 #define AMP3GAIN2                      0x20                                    // rw-- Op-amp3Gain config2
 #define AMP3GAIN1                      0x10                                    // rw-- Op-amp3Gain config1
 #define AMP3GAIN0                      0x08                                    // rw-- Op-amp3Gain config0
 #define AMP0GAIN2                      0x04                                    // rw-- Op-amp0Gain config2
 #define AMP0GAIN1                      0x02                                    // rw-- Op-amp0Gain config1
 #define AMP0GAIN0                      0x01                                    // rw-- Op-amp0Gain config0

/******************************************************************************/
/*                                    TEMP                                    */
/******************************************************************************/
/********************* Bits definition for TSD_CR register ********************/
 #define TSD_EN                         0x80                                    // rw-- TSDenable bit
 #define TSEN_EN                        0x40                                    // rw-- temperature sensorenable bit
 #define TSEN_HYS                       0x20                                    // rw-- Temperature sensor output filter: 0-->1 code value, 1-->2 code values
 #define TSD_ADJ3					    0x08                                    // rw-- Over-temperature protection temperature select
 #define TSD_ADJ2 					    0x04                                    // rw-- Over-temperature protection temperature select
 #define TSD_ADJ1					    0x02                                    // rw-- Over-temperature protection temperature select
 #define TSD_ADJ0					    0x01                                    // rw-- Over-temperature protection temperature select
 
/******************************************************************************/
/*                                     DAC                                    */
/******************************************************************************/
/********************* Bits definition for DAC_CR register ********************/
#define DAC34MOD                        0x20                                    // rw-- DAC3/DAC4 mode config
#define DACMOD                          0x10                                    // rw-- DAC0/DAC1 mode config
#define DAC34EN                         0x04                                    // rw-- DAC3/DAC4enable bit
#define DAC2EN                          0x02                                    // rw-- DAC2enable bit
#define DACEN                           0x01                                    // rw-- DAC0/DAC1enable bit
/******************************************************************************/
/*                                     ADC                                    */
/******************************************************************************/
/********************* Bits definition for ADCx_CR register *******************/
 #define ADCEN                          0x80                                    // rw-- ADCenable bit
 #define ADCBSY                         0x40                                    // rw1- ADC busy flag
 #define ADCALI                         0x04                                    // rw-- ADC data format select
 #define ADCIE                          0x02                                    // rw-- ADC interrupt enable bit
 #define ADCIF                          0x01                                    // rw0- ADC interrupt flag
 /******************** Bits definition for ADC1_SCYC register *******************/
 #define ADC1_SCYC15                    0x8000                                  // rw-- ADC1 CH3/8/9/10/12sample time config
 #define ADC1_SCYC14                    0x4000                                  // rw-- ADC1 CH3/8/9/10/12sample time config
 #define ADC1_SCYC13                    0x2000                                  // rw-- ADC1 CH3/8/9/10/12sample time config
 #define ADC1_SCYC12                    0x1000                                  // rw-- ADC1 CH3/8/9/10/12sample time config
 #define ADC1_SCYC11                    0x0800                                  // rw-- ADC1 CH5/6/7sample time config3 
 #define ADC1_SCYC10                    0x0400                                  // rw-- ADC1 CH5/6/7sample time config2 
 #define ADC1_SCYC9                     0x0200                                  // rw-- ADC1 CH5/6/7sample time config1 
 #define ADC1_SCYC8                     0x0100                                  // rw-- ADC1 CH5/6/7sample time config0 
 #define ADC1_SCYC7                     0x0080                                  // rw-- ADC1 CH2sample time config3 
 #define ADC1_SCYC6                     0x0040                                  // rw-- ADC1 CH2sample time config2 
 #define ADC1_SCYC5                     0x0020                                  // rw-- ADC1 CH2sample time config1 
 #define ADC1_SCYC4                     0x0010                                  // rw-- ADC1 CH2sample time config0 
 #define ADC1_SCYC3                     0x0008                                  // rw-- ADC1 CH0/1/4/11sample time config3 
 #define ADC1_SCYC2                     0x0004                                  // rw-- ADC1 CH0/1/4/11sample time config2 
 #define ADC1_SCYC1                     0x0002                                  // rw-- ADC1 CH0/1/4/11sample time config1 
 #define ADC1_SCYC0                     0x0001                                  // rw-- ADC1 CH0/1/4/11sample time config0 
/******************** Bits definition for ADC2_SCYC register *******************/
 #define ADC2_SCYC15                    0x8000                                  // rw-- ADC2 CH3/8/9/10/12/14/15sample
 #define ADC2_SCYC14                    0x4000                                  // rw-- ADC2 CH3/8/9/10/12/14/15sample
 #define ADC2_SCYC13                    0x2000                                  // rw-- ADC2 CH3/8/9/10/12/14/15sample
 #define ADC2_SCYC12                    0x1000                                  // rw-- ADC2 CH3/8/9/10/12/14/15sample
 #define ADC2_SCYC11                    0x0800                                  // rw-- ADC2 CH5/6/7sample time config3 
 #define ADC2_SCYC10                    0x0400                                  // rw-- ADC2 CH5/6/7sample time config2 
 #define ADC2_SCYC9                     0x0200                                  // rw-- ADC2 CH5/6/7sample time config1 
 #define ADC2_SCYC8                     0x0100                                  // rw-- ADC2 CH5/6/7sample time config0 
 #define ADC2_SCYC7                     0x0080                                  // rw-- ADC2 CH2/11sample time config3 
 #define ADC2_SCYC6                     0x0040                                  // rw-- ADC2 CH2/11sample time config2 
 #define ADC2_SCYC5                     0x0020                                  // rw-- ADC2 CH2/11sample time config1 
 #define ADC2_SCYC4                     0x0010                                  // rw-- ADC2 CH2/11sample time config0 
 #define ADC2_SCYC3                     0x0008                                  // rw-- ADC2 CH0/1/4/13sample time config3 
 #define ADC2_SCYC2                     0x0004                                  // rw-- ADC2 CH0/1/4/13sample time config2 
 #define ADC2_SCYC1                     0x0002                                  // rw-- ADC2 CH0/1/4/13sample time config1 
 #define ADC2_SCYC0                     0x0001                                  // rw-- ADC2 CH0/1/4/13sample time config0 
/******************** Bits definition for ADC3_SCYC register *******************/
 #define ADC3_SCYC7                     0x0080                                  // rw-- ADC3 CH0/2sample time config3 
 #define ADC3_SCYC6                     0x0040                                  // rw-- ADC3 CH0/2sample time config2 
 #define ADC3_SCYC5                     0x0020                                  // rw-- ADC3 CH0/2sample time config1 
 #define ADC3_SCYC4                     0x0010                                  // rw-- ADC3 CH0/2sample time config0 
 #define ADC3_SCYC3                     0x0008                                  // rw-- ADC3 CH1sample time config3 
 #define ADC3_SCYC2                     0x0004                                  // rw-- ADC3 CH1sample time config2 
 #define ADC3_SCYC1                     0x0002                                  // rw-- ADC3 CH1sample time config1 
 #define ADC3_SCYC0                     0x0001                                  // rw-- ADC3 CH1sample time config0 
/******************** Bits definition for ADCx_MASK register ******************/
 #define CH15EN                         0x8000                                  // rw-- ADCxchannel15enable bit
 #define CH14EN                         0x4000                                  // rw-- ADCxchannel14enable bit
 #define CH13EN                         0x2000                                  // rw-- ADCxchannel13enable bit
 #define CH12EN                         0x1000                                  // rw-- ADCxchannel12enable bit
 #define CH11EN                         0x0800                                  // rw-- ADCxchannel11enable bit
 #define CH10EN                         0x0400                                  // rw-- ADCxchannel10enable bit
 #define CH9EN                          0x0200                                  // rw-- ADCxchannel9enable bit
 #define CH8EN                          0x0100                                  // rw-- ADCxchannel8enable bit
 #define CH7EN                          0x0080                                  // rw-- ADCxchannel7enable bit
 #define CH6EN                          0x0040                                  // rw-- ADCxchannel6enable bit
 #define CH5EN                          0x0020                                  // rw-- ADCxchannel5enable bit
 #define CH4EN                          0x0010                                  // rw-- ADCxchannel4enable bit
 #define CH3EN                          0x0008                                  // rw-- ADCxchannel3enable bit
 #define CH2EN                          0x0004                                  // rw-- ADCxchannel2enable bit
 #define CH1EN                          0x0002                                  // rw-- ADCxchannel1enable bit
 #define CH0EN                          0x0001                                  // rw-- ADCxchannel0enable bit

/******************************************************************************/
/*                                     DMA                                    */
/******************************************************************************/
/******************** Bits definition for DMAx_CR register ********************/
 #define DMAHIE                         0x1000                                  // rw-- DMA transfer half-complete interrupt enable
 #define DMAIE                          0x800                                   // rw-- DMA interrupt enable
 #define DMACONEN                       0x400                                   // rw-- DMA circular send function
 #define DMAEN                          0x200                                   // rw-- DMA module enable
 #define DMABSY                         0x100                                   // rw1- DMA start/DMA working status
 #define DMACFG4                        0x80                                    // rw-- DMAchannelselect4
 #define DMACFG3                        0x40                                    // rw-- DMAchannelselect3
 #define DMACFG2                        0x20                                    // rw-- DMAchannelselect2
 #define DMACFG1                        0x10                                    // rw-- DMAchannelselect1
 #define DMACFG0                        0x08                                    // rw-- DMAchannelselect0
 #define ENDIAN                         0x04                                    // rw-- DMA data endian mode
 #define DMAHIF                         0x02                                    // rw-- DMAhalf-completeinterrupt flag
 #define DMAIF                          0x01                                    // rw-- DMAinterrupt flag
/******************************************************************************/
/*                                    UART                                    */
/******************************************************************************/
/********************* Bits definition for UTx_CR0 register *********************/
 #define RTO                            0x200                                   // rw0- Receive timeout interrupt
 #define CHKERR                         0x100                                   // r--- Parity error
 #define UTRB8                          0x80                                    // rw-- Uartx receive 9th bit
 #define UTMOD1                         0x40                                    // rw-- Uartx mode select1
 #define UTMOD0                         0x20                                    // rw-- Uartx mode select0
 #define UTSM2                          0x10                                    // rw-- Uartx multi-processor communication select
 #define UTREN                          0x08                                    // rw-- Uartx receive enable
 #define UTEN                           0x04                                    // rw-- Uartx module enable
 #define UTTI                           0x02                                    // rw-- Uartxtransmitinterrupt flag
 #define UTRI                           0x01                                    // rw-- Uartxreceiveinterrupt flag
/********************* Bits definition for UTx_CR1 register *********************/
 #define RTOIE                          0x400                                   // rw-- Uartxtimeoutinterrupt enable bit
 #define UTIE                           0x200                                   // rw-- UartxTX/RXinterrupt enable bit
 #define BAUDSEL                        0x100                                   // rw-- Uartx baud rate doubler
 #define RXINV                          0x80                                    // rw-- Uartx receive invert
 #define TXINV                          0x40                                    // rw-- Uartx transmit invert
 #define RTOSEL1                        0x08                                    // rw-- Receive timeout range select1
 #define RTOSEL0                        0x04                                    // rw-- Receive timeout range select0
 #define CHKMOD1                        0x02                                    // rw-- 00: Manual mode TB9=0  01: even parity
 #define CHKMOD0                        0x01                                    // rw-- 10: Odd parity        11: manual mode TB9=1
/******************************************************************************/
/*                                    SF                                      */
/******************************************************************************/
/********************* Bits definition for SF_CR register *********************/
#define SF_AUTO_EN                      0x04                                    // w1-- Serial encoder auto-trigger enable
#define SEND_REQ                        0x02                                    // w1-- Serial encoder decode send request
#define SF_EN                           0x01                                    // rw-- Serial encoder decode enable

/********************* Bits definition for SF_SR register *********************/
#define SF_SUC                          0x20                                    // rw0- Data receive success flag, data received and CRC correct
#define SF_DONE                         0x10                                    // rw0- Data receive complete flag, only indicates completion, may have errors (e.g. CRC error also shows DONE)
#define REQ_OUT                         0x08                                    // rw0- Request timeout error, no response after sending request
#define REQ_ERR                         0x04                                    // rw0- Request command error, sent and returned IDs do not match
#define SYN_ERR                         0x02                                    // rw0- Frame sync error, e.g. no Sink Code in control word detected
#define CRC_ERR                         0x01                                    // rw0- CRCParity error

/******************************************************************************/
/*                                   LIN                                      */
/******************************************************************************/
/********************* Bits definition for LIN_CR register *********************/
 #define ManualBaud                     0x80                                    // rw-- LIN manual baud rate enable
 #define LINIE                          0x08                                    // rw-- LIN interrupt enable
 #define CHKMOD                         0x04                                    // rw-- Checksum mode select
 #define LINRW                          0x02                                    // rw-- LIN read/write control
 #define AUTOSIZE                       0x01                                    // rw-- Recognize LINID[5:4] to auto-decide read/write length

/********************* Bits definition for LIN_SR register *********************/   
 #define ERRFRAME                       0x800                                   // r--- LIN format error
 #define ERRBIT                         0x400                                   // r--- LIN loopback error
 #define ERRSYNC                        0x200                                   // r--- LIN sync error
 #define ERRCHK                         0x100                                   // r--- LINParity error
 #define ERRPRTY                        0x80                                    // r--- ID error
 #define ABORT                          0x40                                    // r--- Bus abnormal
 #define LINACT                         0x20                                    // r--- LIN response
 #define LINERR                         0x10                                    // rw0- errorinterrupt flag
 #define LINWAKEUP                      0x08                                    // rw0- wakeupinterrupt flag
 #define LINIDLE                        0x04                                    // rw0- LIN 4s bus inactivity, idle interrupt
 #define LINDONE                        0x02                                    // rw0- LIN message receive/transmit complete
 #define LINREQ                         0x01                                    // rw0- LIN received frame header

/********************* Bits definition for LIN_CSR register *********************/    
 #define LINRDBAKDIS                    0x40                                    // rw-- LIN loopback enable/disable
 #define LINSLP                         0x20                                    // rw-- LIN sleep flag
 #define TXWAKEUP                       0x08                                    // w1-- LIN wakeup signal send
 #define LINACK                         0x04                                    // w1-- LIN message response
 #define LINSTOP                        0x02                                    // w1-- LIN transfer stop
 #define LINEN                          0x01                                    // rw-- LINmodule enable


 /******************************************************************************/
/*                                   CAN                                      */
/******************************************************************************/
/********************* Bits definition for CAN_CR0 register *********************/    
 #define TDCSEL                         0x1000                                  // rw-- Manual/auto delay compensation select
 #define TDCEN                          0x800                                   // rw-- Delay compensation enable
 #define PEX                            0x400                                   // rw-- Protocol exception tolerance
 #define NISO                           0x200                                   // rw-- CANFD non-ISO enable
 #define CFDEN                          0x100                                   // rw-- CANFD enable
 #define CANEN                          0x80                                    // rw-- CAN module enable
 #define AWU                            0x10                                    // rw-- Auto wakeup mode enable
 #define FILMOD                         0x08                                    // rw-- Filter mode
 #define SELFTST                        0x04                                    // rw-- Self-test mode enable
 #define LISTEN                         0x02                                    // rw-- Listen mode
 #define RSTMOD                         0x01                                    // rw-- Reset mode

/********************* Bits definition for CAN_CR1 register *********************/  
 #define TTCM                           0x4000                                  // rw-- Triple sampling enable 
 #define TSPSC3                         0x2000                                  // rw-- Timestamp clock divider3 /* factory */ 
 #define TSPSC2                         0x1000                                  // rw-- Timestamp clock divider2 /* factory */ 
 #define TSPSC1                         0x800                                   // rw-- Timestamp clock divider1 /* factory */ 
 #define TSPSC0                         0x400                                   // rw-- Timestamp clock divider0 /* factory */
 #define TSS                            0x200                                   // rw-- Timestamp clock source /* factory */
 #define CTTC                           0x100                                   // rw-- Time-triggered communication /* factory */
 #define TMOD                           0x80                                    // rw-- Mailbox transmit mode select
 #define OLREQ                          0x40                                    // rw-- Overload frame transmit request
 #define SLPREQ                         0x20                                    // rw-- Sleep request
 #define RSELF                          0x10                                    // rw-- Self-reception enable
 #define RFD                            0x04                                    // w1-- Release receive buffer
 #define NOART                          0x02                                    // rw-- Disable auto-retransmit enable
 
/********************* Bits definition for CAN_STS register *********************/  
 #define SLPACK                         0x40                                    // r--- Sleep mode acknowledgment
 #define TXING                          0x20                                    // r--- Transmitting flag
 #define RXING                          0x10                                    // r--- Receiving flag
 #define FOV                            0x02                                    // r--- FIFO overflow flag
 #define FEMP                           0x01                                    // r--- FIFO empty flag

/********************* Bits definition for CAN_IER register *********************/  
 #define TSIE                           0x1000                                  // rw-- Timestamp overflow interrupt enable /* factory */
 #define WKUIE                          0x800                                   // rw-- Wakeup interrupt enable
 #define SLPIE                          0x400                                   // rw-- Sleep interrupt enable
 #define OVLIE                          0x200                                   // rw-- Overload interrupt enable
 #define ERRIE                          0x100                                   // rw-- Error interrupt global enable
 #define ETYIE                          0x80                                    // rw-- Error type interrupt enable
 #define BOFIE                          0x40                                    // rw-- Bus-off interrupt enable
 #define PERIE                          0x20                                    // rw-- Passive error interrupt request
 #define ERWIE                          0x10                                    // rw-- Error warning interrupt enable
 #define OVIE                           0x08                                    // rw-- Overflow interrupt enable
 #define ABLIE                          0x04                                    // rw-- Arbitration interrupt enable
 #define TXIE                           0x02                                    // rw-- Transmit complete interrupt enable
 #define RXIE                           0x01                                    // rw-- Receive interrupt enable

/********************* Bits definition for CAN_IFR register *********************/  
 #define TSIF                           0x100                                   // rw0- Timestamp overflow event flag /* factory */
 #define WKUIF                          0x80                                    // rw0- Wakeup interrupt event flag
 #define SLPIF                          0x40                                    // rw0- Sleep interrupt event flag
 #define OVLIF                          0x20                                    // rw0- Overload interrupt event flag
 #define ERRIF                          0x10                                    // rw0- Error interrupt event flag
 #define OVIF                           0x08                                    // rw0- Overflow interrupt event flag
 #define ABLIF                          0x04                                    // rw0- Arbitration lost interrupt event flag
 #define TXIF                           0x02                                    // rw0- Transmit complete interrupt event flag
 #define RXIF                           0x01                                    // r--- Receive interrupt event flag

/********************* Bits definition for CAN_TSPT register *********************/  
 #define RDPTR1                         0x08                                    // r--- Receive message pointer1
 #define RDPTR0                         0x04                                    // r--- Receive message pointer0
 #define MESCNT1                        0x02                                    // r--- Valid message count1
 #define MESCNT0                        0x01                                    // r--- Valid message count0

/********************* Bits definition for CAN_ERR register *********************/  
 #define BOFF                           0x04                                    // rw-- Node bus-off
 #define PER                            0x02                                    // rw-- Passive error state
 #define WER                            0x01                                    // rw-- Error state

 /********************* Bits definition for CAN_TMSTA register *********************/  
 #define MSL2                           0x80000000                              // r--- Mailbox 2 last sent
 #define MSL1                           0x40000000                              // r--- Mailbox 1 last sent
 #define MSL0                           0x20000000                              // r--- Mailbox 0 last sent
 #define MNUM1                          0x10000000                              // r--- Next transmit mailbox number
 #define MNUM0                          0x8000000                               // r--- Next transmit mailbox number
 #define ME2                            0x4000000                               // r--- Transmit mailbox 2 empty
 #define ME1                            0x2000000                               // r--- Transmit mailbox 1 empty
 #define ME0                            0x1000000                               // r--- Transmit mailbox 0 empty
 #define MSTP2                          0x800000                                // rw-- Mailbox 2 stop transmit
 #define MERR2                          0x80000                                 // rw1- Mailbox 2 transmit error, write 1 to clear
 #define MAL2                           0x40000                                 // rw1- Mailbox 2 arbitration, write 1 to clear
 #define MOK2                           0x20000                                 // rw1- Mailbox 2 transmit success, write 1 to clear
 #define MDONE2                         0x10000                                 // rw1- Mailbox 2 transmit complete, write 1 to clear
 #define MSTP1                          0x8000                                  // rw-- Mailbox 1 stop transmit
 #define MERR1                          0x800                                   // rw1- Mailbox 1 transmit error, write 1 to clear
 #define MAL1                           0x400                                   // rw1- Mailbox 1 arbitration, write 1 to clear
 #define MOK1                           0x200                                   // rw1- Mailbox 1 transmit success, write 1 to clear
 #define MDONE1                         0x100                                   // rw1- Mailbox 1 transmit complete, write 1 to clear
 #define MSTP0                          0x80                                    // rw-- Mailbox 0 stop transmit
 #define MERR0                          0x08                                    // rw1- Mailbox 0 transmit error, write 1 to clear
 #define MAL0                           0x04                                    // rw1- Mailbox 0 arbitration, write 1 to clear
 #define MOK0                           0x02                                    // rw1- Mailbox 0 transmit success, write 1 to clear
 #define MDONE0                         0x01                                    // rw1- Mailbox 0 transmit complete, write 1 to clear

 /********************* Bits definition for CAN_TMIDx register *********************/  
 #define TREQ                           0x01                                    // w1-- Mailbox x transmit request

 /********************* Bits definition for CAN_TMDATx register *********************/  
 #define IDE                            0x100                                   // rw-- Standard frame / Extended frame
 #define RTR                            0x80                                    // rw-- Data frame / Remote frame
 #define FDF                            0x40                                    // rw-- CANFD frame message
 #define BRS                            0x20                                    // rw-- Bit rate switch frame select
 #define ESI                            0x10                                    // rw-- Error stateflag
 #define DLC3                           0x08                                    // rw-- DLC3
 #define DLC2                           0x04                                    // rw-- DLC2
 #define DLC1                           0x02                                    // rw-- DLC1
 #define DLC0                           0x01                                    // rw-- DLC0






/******************************************************************************/
/*                                     I2C                                    */
/******************************************************************************/
/******************** Bits definition for I2C_CR register *********************/
 #define I2CEN                          0x80                                    // rw-- I2C module enable
 #define I2CMS                          0x40                                    // rw-- I2C master mode select
 #define E2PRMVDDPD                     0x20                                    // rw-- E2PRMVDD5 power down enable, I2C1 only
 #define I2CDMANAKIG                    0x10                                    // rw-- DMA ignores NACK and continues sending
 #define I2CDMASENDAUTO                 0x08                                    // rw-- DMA auto-send first frame data
 #define I2CFSEL                        0x02                                    // rw-- I2C filter select
 #define I2CIE                          0x01                                    // rw-- I2Cinterrupt enable bit
/******************** Bits definition for I2C_SR register *********************/
 #define I2CBSY                         0x80                                    // r--- I2C busy status
 #define DMOD                           0x40                                    // rw-- I2C read/write status
 #define I2CSTA                         0x10                                    // rw-- I2C frame header flag
 #define I2CSTP                         0x08                                    // rw-- I2C stop flag
 #define STR                            0x04                                    // rw0- I2C bus suspend flag
 #define NACK                           0x02                                    // rw-- Receive direction send feedback
 #define I2CIF                          0x01                                    // r--- I2Cinterrupt flag
/******************** Bits definition for I2C_ID register *********************/
 #define GC                             0x01                                    // rw-- I2CID broadcast mode

/******************************************************************************/
/*                                     SPIx                                    */
/******************************************************************************/
/******************** Bits definition for SPIx_CR  register *******************/
 #define SAMSEL                         0x200                                   // rw-- SPI edge sampling select
 #define SCKRQ                          0x100                                   // r0w1 Single-wire master requests slave data
 #define CPHA                           0x80                                    // rw-- SPI clock phase
 #define CPOL                           0x40                                    // rw-- SPI clock idle level
 #define NSSMOD1                        0x20                                    // rw-- SPI mode config1
 #define NSSMOD0                        0x10                                    // rw-- SPI mode config0
 #define SLINE                          0x08                                    // rw-- single/duplexenable bit
 #define SPIIE                          0x04                                    // rw-- SPIinterrupt enable bit
 #define SPIMS                          0x02                                    // rw-- SPI master mode select 
 #define SPIEN                          0x01                                    // rw-- SPImoduleenable bit
/******************** Bits definition for SPIx_SR  register ********************/
 #define SLVSEL                         0x200                                   // r--- NSS chip select flag
 #define NSSIN                          0x100                                   // r--- NSS real-time signal
 #define SRMT                           0x80                                    // r--- Shift register empty flag
 #define RXBMT                          0x40                                    // r--- Receive buffer empty flag
 #define TXBMT                          0x20                                    // r--- Transmit buffer empty flag
 #define SPIBSY                         0x10                                    // r--- SPI busy status
 #define SPIIF                          0x08                                    // rw0- SPIinterrupt flag
 #define WCOL                           0x04                                    // rw0- Write collision interrupt event flag
 #define MODF                           0x02                                    // rw0- Master mode error interrupt event flag
 #define RXOVR                          0x01                                    // rw0- Receive overflow interrupt event flag

/******************************************************************************/
/*                                    BISS                                    */
/******************************************************************************/
/******************* Bits definition for BISS_STATE register *****************/
 #define BISS_AUTO_EN					0x0100                                  // r--- BiSS auto-trigger enable
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
 #define T2INM2                         0x400                                   // rw-- Timer2 filter coefficient2
 #define T2INM1                         0x200                                   // rw-- Timer2 filter coefficient1
 #define T2INM0                         0x100                                   // rw-- Timer2 filter coefficient0
 #define T2PSC2                         0x80                                    // rw-- Timer2 prescaler2
 #define T2PSC1                         0x40                                    // rw-- Timer2 prescaler1
 #define T2PSC0                         0x20                                    // rw-- Timer2 prescaler0
 #define T2CES                          0x10                                    // rw-- Timer2 edge select
 #define T2DIRIN                        0x08                                    // rw-- Direction input polarity select
 #define T2MOD2                         0x04                                    // rw-- Timer2 mode select2
 #define T2MOD1                         0x02                                    // rw-- Timer2 mode select1
 #define T2MOD0                         0x01                                    // rw-- Timer2 mode select0
/******************* Bits definition for TIM2_CR1 register ********************/
 #define T2_CNTR_CLR_EN                 0x100                                   // rw-- QEP load DR configuration
 #define T2OPM                          0x80                                    // rw-- Timer2 one-shot mode enable
 #define T2QEP_IN_CNTR_CLR              0x40                                    // rw-- QEP Z input clear CNTR enable
 #define T2Z_EDGE_SEL                   0x20                                    // rw-- QEP mode edge select
 #define T2SS                           0x10                                    // rw-- Stepping mode
 #define T2OCM                          0x04                                    // rw-- Output mode select
 #define T2_DIR_R                       0x02                                    // r--- QEP & stepper motor rotation direction
 #define T2EN                           0x01                                    // rw-- Timer2 enable
/******************* Bits definition for TIM2_IER register ********************/
 #define T2IRE                          0x04                                    // rw-- IRinterrupt enable bit
 #define T2IPE                          0x02                                    // rw-- IPinterrupt enable bit
 #define T2IFE                          0x01                                    // rw-- IFinterrupt enable bit
/******************* Bits definition for TIM2_SR register ********************/
 #define T2IR                           0x04                                    // rw0- IRinterrupt flag
 #define T2IP                           0x02                                    // rw0- IPinterrupt flag
 #define T2IF                           0x01                                    // rw0- IFinterrupt flag
/******************* Bits definition for TIM2_CR2 register ********************/
 #define TIM2_B_EDGE_SEL                0x20                                    // rw-- TIM2 QEP_B output polarity config
 #define TIM2_A_EDGE_SEL                0x10                                    // rw-- TIM2 QEP_A output polarity config
 #define TIM2_Z_SEL1                    0x08                                    // rw-- TIM2 QEP_Z output select1
 #define TIM2_Z_SEL0                    0x04                                    // rw-- TIM2 QEP_Z output select0
 #define TIM2_AB_SEL1                   0x02                                    // rw-- TIM2 QEP_AB output select1
 #define TIM2_AB_SEL0                   0x01                                    // rw-- TIM2 QEP_AB output select0
/******************************************************************************/
/*                                   TIMER3                                   */
/******************************************************************************/
/******************* Bits definition for TIM3_CR0 register ********************/
 #define T3PSC2                         0x80                                    // rw-- Timer3prescaler2
 #define T3PSC1                         0x40                                    // rw-- Timer3prescaler1
 #define T3PSC0                         0x20                                    // rw-- Timer3prescaler0
 #define T3FE1                          0x10                                    // rw-- Filter select1
 #define T3FE0                          0x08                                    // rw-- Filter select0
 #define T3OCM                          0x04                                    // rw-- Output mode select
 #define T3OPM                          0x02                                    // rw-- One-shot mode enable
 #define T3MOD                          0x01                                    // rw-- Timer3modeselect
/******************* Bits definition for TIM3_CR1 register ********************/
 #define T3EN                           0x01                                    // rw-- Timer3enable
/******************* Bits definition for TIM3_IER register ********************/
 #define T3IRE                          0x04                                    // rw-- IRinterrupt enable bit
 #define T3IPE                          0x02                                    // rw-- IPinterrupt enable bit
 #define T3IFE                          0x01                                    // rw-- IFinterrupt enable bit
/******************* Bits definition for TIM3_SR register ********************/
 #define T3IR                           0x04                                    // rw0- IRinterrupt flag
 #define T3IP                           0x02                                    // rw0- IPinterrupt flag
 #define T3IF                           0x01                                    // rw0- IFinterrupt flag
/******************************************************************************/
/*                                   TIMER4                                   */
/******************************************************************************/
/******************* Bits definition for TIM4_CR0 register ********************/
 #define T4PSC2                         0x80                                    // rw-- Timer4prescaler2
 #define T4PSC1                         0x40                                    // rw-- Timer4prescaler1
 #define T4PSC0                         0x20                                    // rw-- Timer4prescaler0
 #define T4FE1                          0x10                                    // rw-- Filter select1
 #define T4FE0                          0x08                                    // rw-- Filter select0
 #define T4OCM                          0x04                                    // rw-- Output mode select
 #define T4OPM                          0x02                                    // rw-- One-shot mode enable
 #define T4MOD                          0x01                                    // rw-- Timer4modeselect
/******************* Bits definition for TIM4_CR1 register ********************/
 #define T4EN                           0x01                                    // rw-- Timer4enable bit
/******************* Bits definition for TIM4_IER register ********************/
 #define T4IRE                          0x04                                    // rw-- IRinterrupt enable bit
 #define T4IPE                          0x02                                    // rw-- IPinterrupt enable bit
 #define T4IFE                          0x01                                    // rw-- IFinterrupt enable bit
/******************* Bits definition for TIM4_SR register ********************/
 #define T4IR                           0x04                                    // rw0- IRinterrupt flag
 #define T4IP                           0x02                                    // rw0- IPinterrupt flag
 #define T4IF                           0x01                                    // rw0- IFinterrupt flag
/******************************************************************************/
/*                                   TIMER5                                   */
/******************************************************************************/
/******************* Bits definition for TIM5_CR0 register ********************/
 #define T5INM2                         0x400                                   // rw-- Timer5filter coefficient2
 #define T5INM1                         0x200                                   // rw-- Timer5filter coefficient1
 #define T5INM0                         0x100                                   // rw-- Timer5filter coefficient0
 #define T5PSC2                         0x80                                    // rw-- Timer5prescaler2
 #define T5PSC1                         0x40                                    // rw-- Timer5prescaler1
 #define T5PSC0                         0x20                                    // rw-- Timer5prescaler0
 #define T5CES                          0x10                                    // rw-- Timer5edgeselect
 #define T5DIRIN                        0x08                                    // rw-- Direction input polarity select
 #define T5MOD2                         0x04                                    // rw-- Timer5modeselect2
 #define T5MOD1                         0x02                                    // rw-- Timer5modeselect1
 #define T5MOD0                         0x01                                    // rw-- Timer5modeselect0
/******************* Bits definition for TIM5_CR1 register ********************/
 #define T5_CNTR_CLR_EN                 0x100                                   // rw-- QEP load DR configuration
 #define T5OPM                          0x80                                    // rw-- Timer5One-shot mode enable
 #define T5QEP_IN_CNTR_CLR              0x40                                    // rw-- QEP Z input clear CNTR enable
 #define T5Z_EDGE_SEL                   0x20                                    // rw-- QEP mode edge select
 #define T5SS                           0x10                                    // rw-- Stepping mode
 #define T5OCM                          0x04                                    // rw-- Output mode select
 #define T5_DIR_R                       0x02                                    // r--- QEP & stepper motor rotation direction
 #define T5EN                           0x01                                    // rw-- Timer5enable
/******************* Bits definition for TIM5_IER register ********************/
 #define T5IRE                          0x04                                    // rw-- IRinterrupt enable bit
 #define T5IPE                          0x02                                    // rw-- IPinterrupt enable bit
 #define T5IFE                          0x01                                    // rw-- IFinterrupt enable bit
/******************* Bits definition for TIM5_SR register ********************/
 #define T5IR                           0x04                                    // rw0- IRinterrupt flag
 #define T5IP                           0x02                                    // rw0- IPinterrupt flag
 #define T5IF                           0x01                                    // rw0- IFinterrupt flag
 /******************* Bits definition for TIM5_CR2 register ********************/
 #define TIM5_B_EDGE_SEL                0x20                                    // rw-- TIM5QEP_Boutputpolarityconfig
 #define TIM5_A_EDGE_SEL                0x10                                    // rw-- TIM5QEP_Aoutputpolarityconfig
 #define TIM5_Z_SEL1                    0x08                                    // rw-- TIM5QEP_Zoutputselect1
 #define TIM5_Z_SEL0                    0x04                                    // rw-- TIM5QEP_Zoutputselect0
 #define TIM5_AB_SEL1                   0x02                                    // rw-- TIM5QEP_ABoutputselect1
 #define TIM5_AB_SEL0                   0x01                                    // rw-- TIM5QEP_ABoutputselect0
/******************************************************************************/
/*                                   TIMER6                                   */
/******************************************************************************/
/******************* Bits definition for TIM6_CR0 register ********************/
 #define T6INM2                         0x400                                   // rw-- Timer6filter coefficient2
 #define T6INM1                         0x200                                   // rw-- Timer6filter coefficient1
 #define T6INM0                         0x100                                   // rw-- Timer6filter coefficient0
 #define T6PSC2                         0x80                                    // rw-- Timer6prescaler2
 #define T6PSC1                         0x40                                    // rw-- Timer6prescaler1
 #define T6PSC0                         0x20                                    // rw-- Timer6prescaler0
 #define T6CES                          0x10                                    // rw-- Timer6edgeselect
 #define T6DIRIN                        0x08                                    // rw-- Direction input polarity select
 #define T6MOD2                         0x04                                    // rw-- Timer6modeselect2
 #define T6MOD1                         0x02                                    // rw-- Timer6modeselect1
 #define T6MOD0                         0x01                                    // rw-- Timer6modeselect0
/******************* Bits definition for TIM6_CR1 register ********************/
 #define T6_CNTR_CLR_EN                 0x100                                   // rw-- QEP load DR configuration
 #define T6OPM                          0x80                                    // rw-- Timer6One-shot modeenable bit
 #define T6QEP_IN_CNTR_CLR              0x40                                    // rw-- QEP Z input clear CNTR enable
 #define T6Z_EDGE_SEL                   0x20                                    // rw-- QEP mode edge select
 #define T6SS                           0x10                                    // rw-- Stepping mode
 #define T6OCM                          0x04                                    // rw-- Output mode select
 #define T6_DIR_R                       0x02                                    // r--- QEP & stepper motor rotation direction
 #define T6EN                           0x01                                    // rw-- Timer6enable
/******************* Bits definition for TIM6_IER register ********************/
 #define T6IRE                          0x04                                    // rw-- IRinterrupt enable bit
 #define T6IPE                          0x02                                    // rw-- IPinterrupt enable bit
 #define T6IFE                          0x01                                    // rw-- IFinterrupt enable bit
/******************* Bits definition for TIM6_SR register ********************/
 #define T6IR                           0x04                                    // rw0- IRinterrupt flag
 #define T6IP                           0x02                                    // rw0- IPinterrupt flag
 #define T6IF                           0x01                                    // rw0- IFinterrupt flag
/******************* Bits definition for TIM6_CR2 register ********************/
 #define TIM6_B_EDGE_SEL                0x20                                    // rw-- TIM6QEP_Boutputpolarityconfig
 #define TIM6_A_EDGE_SEL                0x10                                    // rw-- TIM6QEP_Aoutputpolarityconfig
 #define TIM6_Z_SEL1                    0x08                                    // rw-- TIM6QEP_Zoutputselect1
 #define TIM6_Z_SEL0                    0x04                                    // rw-- TIM6QEP_Zoutputselect0
 #define TIM6_AB_SEL1                   0x02                                    // rw-- TIM6QEP_ABoutputselect1
 #define TIM6_AB_SEL0                   0x01                                    // rw-- TIM6QEP_ABoutputselect0
/******************************************************************************/
/*                                   TIMER7                                   */
/******************************************************************************/
/******************* Bits definition for TIM7_CR0 register ********************/
 #define T7PSC2                         0x80                                    // rw-- Timer7prescaler2
 #define T7PSC1                         0x40                                    // rw-- Timer7prescaler1
 #define T7PSC0                         0x20                                    // rw-- Timer7prescaler0
 #define T7FE1                          0x10                                    // rw-- Filter mode1
 #define T7FE0                          0x08                                    // rw-- Filter mode0
 #define T7OCM                          0x04                                    // rw-- Output mode select
 #define T7OPM                          0x02                                    // rw-- One-shot mode enable
 #define T7MOD                          0x01                                    // rw-- Timer7modeselect
/******************* Bits definition for TIM7_CR1 register ********************/
 #define T7EN                           0x01                                    // rw-- Timer7moduleenable bit
/******************* Bits definition for TIM7_IER register ********************/
 #define T7IRE                          0x04                                    // rw-- IRinterrupt enable bit
 #define T7IPE                          0x02                                    // rw-- IPinterrupt enable bit
 #define T7IFE                          0x01                                    // rw-- IFinterrupt enable bit
/******************* Bits definition for TIM7_SR register ********************/
 #define T7IR                           0x04                                    // rw0- IRinterrupt flag
 #define T7IP                           0x02                                    // rw0- IPinterrupt flag
 #define T7IF                           0x01                                    // rw0- IFinterrupt flag
/******************************************************************************/
/*                                   TIMER8                                   */
/******************************************************************************/
/******************* Bits definition for TIM8_CR0 register ********************/
#define T8PSC2                         0x80                                    // rw-- Timer8prescaler2
#define T8PSC1                         0x40                                    // rw-- Timer8prescaler1
#define T8PSC0                         0x20                                    // rw-- Timer8prescaler0
#define T8FE1                          0x10                                    // rw-- Filter select1
#define T8FE0                          0x08                                    // rw-- Filter select0
#define T8OCM                          0x04                                    // rw-- Output mode select
#define T8OPM                          0x02                                    // rw-- One-shot mode enable
#define T8MOD                          0x01                                    // rw-- Timer8modeselect
/******************* Bits definition for TIM8_CR1 register ********************/
#define T8EN                           0x01                                    // rw-- Timer8enable
/******************* Bits definition for TIM8_IER register ********************/
#define T8IRE                          0x04                                    // rw-- IRinterrupt enable bit
#define T8IPE                          0x02                                    // rw-- IPinterrupt enable bit
#define T8IFE                          0x01                                    // rw-- IFinterrupt enable bit
/******************* Bits definition for TIM8_SR register ********************/
#define T8IR                           0x04                                    // rw0- IRinterrupt flag
#define T8IP                           0x02                                    // rw0- IPinterrupt flag
#define T8IF                           0x01                                    // rw0- IFinterrupt flag

/******************************************************************************/
/*                                   STPC                                     */
/******************************************************************************/
/******************* Bits definition for STPCx_CR register ********************/
#define PCOM_IE                        0x40                                    // rw-- Position compare interrupt enable
#define PCOM_SEL1                      0x20                                    // rw-- Position compare config bit1
#define PCOM_SEL0                      0x10                                    // rw-- Position compare config bit0
#define PCOM_EN                        0x08                                    // rw-- Position compare enable
#define STRO_IE                        0x04                                    // rw-- Probeinterrupt enable
#define STRO_SEL                       0x02                                    // rw-- Probetrigger edge select
#define STRO_EN                        0x01                                    // rw-- Probefunctionenable
/******************* Bits definition for STPCx_SR register ********************/
#define PCOM_IF                        0x02                                    // rw-- bit compareinterrupt flag
#define STRO_IF                        0x01                                    // rw-- Probeinterrupt flag

/******************************************************************************/
/*                                   SysTick                                  */
/******************************************************************************/
/********************* Bits definition for SYST_SR register *******************/
 #define INTCS_MD1                      0x08                                    // rw-- /* factory */
 #define INTCS_MD0                      0x04                                    // rw-- /* factory */
 #define SYSTIF                         0x02                                    // rw0- Systickinterrupt flag
 #define SYSTEN                         0x01                                    // rw-- Systickenable bit

/******************************************************************************/
/*                                     CAL                                    */
/******************************************************************************/
/********************* Bits definition for CAL_CR register ********************/
 #define CALBSY                         0x8000

/******************************************************************************/
/*                                     RTC                                    */
/******************************************************************************/
/********************* Bits definition for RTC_CR register ********************/
 #define RTCEN                          0x80                                    // rw-- RTC enable
 #define RTCIF                          0x40                                    // rw0- RTC interrupt flag
 #define SCKSEL                         0x20                                    // rw-- Calibration slow clock source select /* factory */
 #define ISOSCEN                        0x10                                    // rw-- Internal slow clock enable
 #define ESCKSEL                        0x02                                    // rw-- External slow clock digital input PIN select /* factory */
 #define ESCKEN                         0x01                                    // rw-- External slow clock digital input enable  /* factory */

/******************************************************************************/
/*                                     OSC                                    */
/******************************************************************************/
/********************* Bits definition for OSC_CR register ********************/
 #define MCDRET                         0x040                                   // rw1- Attempt to exit MCD state  /* factory */
 #define PLLLIE                         0x020                                   // rw-- PLL loss interrupt enable  /* factory */
 #define MCDIE                          0x010                                   // rw-- Clock missing interrupt enable  /* factory */
 #define EFOSCAE                        0x08                                    // rw-- External fast clock PIN analog enable  /* factory */
 #define EFCKEN                         0x04                                    // rw-- External fast clock force enable  /* factory */
 #define IFCKNE                         0x02                                    // rw-- Internal fast clock force enable  /* factory */
 #define PLLEN                          0x01                                    // rw-- PLL enable  /* factory */
/********************* Bits definition for OSC_SR register ********************/
 #define PLL_LOCK                       0x08                                    // r--- PLL lock flag  /* factory */
 #define PLLCK_STATUS                   0x04                                    // r--- PLL clock source select flag  /* factory */
 #define PLLLIF                         0x02                                    // rw0- PLL clock loss interrupt flag  /* factory */
 #define MCDIF                          0x01                                    // rw0- MCD interrupt flag  /* factory */

/******************************************************************************/
/*                                     IWDT                                   */
/******************************************************************************/

/******************************************************************************/
/*                                     WWDT                                   */
/******************************************************************************/
/********************* Bits definition for WWDT_CR register ********************/
 #define WWDTSTA                        0x80                                    // rw1- WWDT enable
/********************* Bits definition for WWDT_CFR register *******************/
 #define WWDTIE                         0x200                                   // rw-- WWDT early wakeup interrupt enable
 #define WWDTPSC1                       0x100                                   // rw-- WWDT count prescaler config1
 #define WWDTPSC0                       0x80                                    // rw-- WWDT count prescaler config0

/********************* Bits definition for WWDT_SR register ********************/
 #define EWIF                           0x01                                    // rw0- WWDT early wakeup interrupt flag


/******************************************************************************/
/*                                     CRC                                    */
/******************************************************************************/
/********************* Bits definition for CRC_CR register ********************/
 #define RESINV                         0x80                                    // rw-- Output result inversion
 #define DATINV                         0x40                                    // rw-- Data input inversion
 #define CRCSEL                         0x20                                    // rw-- CRC polynomial select
 #define CRCDONE                        0x10                                    // r1-- Auto CRC complete flag
 #define CRCDINI                        0x08                                    // w1-- CRC initialization
 #define CRCVAL                         0x04                                    // rw-- CRC initializationvalue
 #define AUTOINT                        0x02                                    // w1-- CRC auto-calculation enable

/******************************************************************************/
/*                                     CCFG                                   */
/******************************************************************************/
/********************* Bits definition for CCFG2 register ********************/
 #define LVWPD                          0x80                                    // rw-- Low voltage warning enable
 #define LVWIE                          0x40                                    // rw-- Low voltage warning interrupt enable
 #define IWDTEN                         0x20                                    // rw-- Independent WDT enable
 #define PLLSRC                         0x02                                    // rw-- PLL clock source select
 #define FCKMOD                         0x01                                    // rw-- System clock select
/********************* Bits definition for CCFG3 register ********************/
 #define EOSSET3                        0x80000                                 // rw-- Electrical over-stress level setting3
 #define EOSSET2                        0x40000                                 // rw-- Electrical over-stress level setting2
 #define EOSSET1                        0x20000                                 // rw-- Electrical over-stress level setting1
 #define EOSSET0                        0x10000                                 // rw-- Electrical over-stress level setting0
 #define LVRSEL1                        0x8000                                  // rw-- Low voltage reset voltage select1
 #define LVRSEL0                        0x4000                                  // rw-- Low voltage reset voltage select0 
 #define EOS_RST_EN                     0x800                                   // rw-- EOS electrical over-stress enable
 #define LVWSEL                         0x100                                   // rw-- VDD5 low voltage warning voltage select
 #define XT_CUR_CFG1                    0x20                                    // rw-- Crystal circuit drive capability config1
 #define XT_CUR_CFG0                    0x10                                    // rw-- Crystal circuit drive capability config0
 #define XT_GF_CFG1                     0x08                                    // rw-- Clock circuit glitch filter1
 #define XT_GF_CFG0                     0x04                                    // rw-- Clock circuit glitch filter0
 #define ECMOD                          0x02                                    // rw-- External clock source select
 #define PLLFSEL                        0x01                                    // rw-- PLL clock frequency select


/******************************************************************************/
/*                                   ME                                       */
/******************************************************************************/
/********************* Bits definition for ME_CR register *********************/
 #define CPUMEDIS                       0x8000                                  // rw-- Software disable FOC variable register write       /* factory */
 #define CPUBFWE                        0x4000                                  // rw-- CPU write buffer enable, CPUMEDIS must be 0       /* factory */
 #define UDC_DIS                        0x2000                                  // rw-- Disable UDC sampling; software must sample UDC and write to ME
 #define DRVSYN_EN                      0x20                                    // rw-- Dual motor sync enable
 #define ME_BLK_MD                      0x10                                    // rw-- CPU behavior when stopped in debug mode       /* factory */
 #define INTCD                          0x08                                    // rw-- External interrupt 1 clear DRV count, for ETHERCAT sync
 #define TRIG_MD                        0x04                                    // rw-- FOC1 dual-resistor sync sampling enable, prohibited in dual motor mode
 #define UDC2_MAEN                      0x02                                    // rw-- FOC2 UDC auto mode enable, for cases where FOC1 and FOC2 bus voltages differ
// #define FOCEN                          0x01                                    // rw-- FOC module global enable; module is in reset when disabled
/********************* Bits definition for ME_IER register *********************/
 #define NPE1                           0x0008                                  // rw-- Match state 1 pause enable       /* factory */
 #define NIE1                           0x0004                                  // rw-- Match state 1 interrupt enable       /* factory */
 #define NPE0                           0x0002                                  // rw-- Match state 0 pause enable       /* factory */
 #define NIE0                           0x0001                                  // rw-- Match state 0 interrupt enable       /* factory */
/********************* Bits definition for ME_IFR register *********************/
 #define NPF1                           0x0200                                  // rw-- Match state 1 pause status       /* factory */
 #define NPF0                           0x0100                                  // rw-- Match state 1 interrupt flag       /* factory */
 #define NIF1                           0x0002                                  // rw-- Match state 0 pause status       /* factory */
 #define NIF0                           0x0001                                  // rw-- Match state 0 interrupt flag       /* factory */

///****************************************************************************/
/*                                   Driver                                   */
/******************************************************************************/
/********************* Bits definition for DRVx_CR register ********************/
 #define DRV_CNTR_DIR                   0x8000                                  // rw-- DRV counter direction: 0-up
 #define IMM_UPDATE                     0x80                                    // rw-- Duty cycle immediate update
 #define OCP_MOEMD                      0x40                                    // rw-- Overcurrent protection MOE enable (in square-wave drive mode)
 #define MOEMD1                         0x20                                    // rw-- 00: MOE not auto-clear; 10: MOE auto-clear and auto-enable after Driver counter overflow/underflow or 5.3μs (square-wave)
 #define MOEMD0                         0x10                                    // rw-- 01: MOE auto-clear; 11: MOE auto-clear and auto-enable after Driver counter overflow/underflow or 2.6μs (square-wave)
 #define DRVMD                          0x08                                    // rw-- 0: Triangle wave mode  1: Sawtooth wave mode
 #define DDIR                           0x04                                    // rw-- DRV direction
 #define DRVEN                          0x02                                    // rw-- DRV enable
 #define DRVOE                          0x01                                    // rw-- DRV output enable
/********************* Bits definition for DRVx_IER register ********************/
 #define CAIE                           0x20                                    // rw-- Calculation complete error interrupt enable
 #define THIE                           0x10                                    // rw-- Electrical angle one-cycle interrupt enable
 #define FGIE                           0x08                                    // rw-- FG interrupt enable
 #define DCIP                           0x04                                    // rw-- 0: DCIF interrupt every carrier period; 1: DCIF interrupt every other carrier period
 #define DCIM1                          0x02                                    // rw-- 00: No DCIF interrupt; 01: DCIF interrupt during up-count
 #define DCIM0                          0x01                                    // rw-- 01: DCIF interrupt during down-count; 11: interrupt on both up/down count
/********************* Bits definition for DRVx_IFR register ********************/
 #define CAIF                           0x20                                    // rw0- Calculation complete error interrupt flag
 #define THIF                           0x10                                    // rw0- Electrical angle 179->180 generates interrupt, phase differs from FGIF
 #define FGIF                           0x08                                    // rw0- FG interrupt flag
 #define DCIF                           0x01                                    // rw0- DRV compare interrupt flag
/********************* Bits definition for DRVx_PER register ********************/
 #define PER_MD                         0x8000                                  // rw-- Protection sensitivity setting
 #define PL_MD							0x1000                                  // rw-- New phase loss protection enable
 #define LOCK_MD						0x0800                                  // rw-- Servo stall enable
 #define LOCK2EN                        0x0400                                  // rw-- Stall detection 2 enable
 #define LOCK1EN                        0x0200                                  // rw-- Stall detection 1 enable
 #define LOCK0EN                        0x0100                                  // rw-- Stall detection 0 enable
 #define ODCIF_EN                       0x080                                   // rw-- Carrier interrupt timeout protection enable
 #define OSPD_AUTO                      0x040                                   // rw-- Overspeed auto-calculation, once per carrier period
 #define OVEL_AUTO                      0x020                                   // rw-- Velocity error auto-calculation, once per outer loop period
 #define PL_AUTO                        0x010                                   // rw-- Phase loss auto-calculation and trigger interrupt
 #define LOCK_AUTO                      0x08                                    // rw-- Stall auto-calculation enable
 #define OUVP_AUTO1                     0x04                                    // rw-- 10: SysTick calculation once
 #define OUVP_AUTO0                     0x02                                    // rw-- 01: Carrier period calculation once
 #define SOCP_AUTO                      0x01                                    // rw-- Software overcurrent auto-calculation enable, Carrier period calculation once
/********************* Bits definition for DRVx_PTR register ********************/
 #define RAMP_TRG                       0x0200                                  // w1-- Ramp manual trigger
 #define WPI_TRG                        0x0100                                  // w1-- Outer loop PI calculation trigger
 #define OSPD_TRG                       0x20                                    // w1-- Overspeed calculation trigger
 #define OVEL_TRG                       0x10                                    // w1-- Velocity error calculation trigger
 #define PL_TRG                         0x08                                    // w1-- Phase loss calculation software trigger; calculates once after enable; triggers interrupt if phase loss active
 #define LOCK_TRG                       0x04                                    // w1-- Stall calculation trigger
 #define OUVP_TRG                       0x02                                    // w1-- Over/under voltage calculation software trigger
 #define SOCP_TRG                       0x01                                    // w1-- Software overcurrent calculation software trigger
/********************* Bits definition for DRV_PSR register ********************/
 #define CBA2                           0x4000                                  // r--- Sector number
 #define CBA1                           0x2000                                  // r--- Sector number
 #define CBA0                           0x1000                                  // r--- Sector number
 #define RIF                            0x100                                   // rw0- Current reference abnormal state, not an interrupt flag
 #define ODCIF_IF						0x80                                    // rw-- Carrier interrupt timeout protection enableinterrupt flag
 #define OSPDIF                         0x40                                    // rw0- Overspeed interrupt flag
 #define OVELIF                         0x20                                    // rw0- Velocity error interrupt flag
 #define PLIF                           0x10                                    // rw0- Phase loss interrupt flag
 #define LOCKIF                         0x08                                    // rw0- Stall interrupt flag
 #define UVPIF                          0x04                                    // rw0- Undervoltage interrupt flag
 #define OVPIF                          0x02                                    // rw0- Overvoltage interrupt flag
 #define SOCPIF                         0x01                                    // rw0- Software overcurrent interrupt flag
/******************** Bits definition for DRV_OUT register ********************/
 #define HREV_EN                        0x8000                                  // rw-- Upper bridge invert enable, select based on pre-driver
 #define LREV_EN                        0x4000                                  // rw-- Lower bridge invert enable, select based on pre-driver
 #define MOE                            0x80                                    // rw-- DRV output global enable
 #define OISWXL                         0x20                                    // rw-- WX phase lower bridge idle level
 #define OISWXH                         0x10                                    // rw-- WX phase upper bridge idle level
 #define OISVL                          0x08                                    // rw-- V phase lower bridge idle level
 #define OISVH                          0x04                                    // rw-- V phase upper bridge idle level
 #define OISUL                          0x02                                    // rw-- U phase lower bridge idle level
 #define OISUH                          0x01                                    // rw-- U phase upper bridge idle level
/******************** Bits definition for DRVx_CMR register ********************/
 #define WHP                            0x0800                                  // rw-- W phase upper bridge polarity
 #define WLP                            0x0400                                  // rw-- W phase lower bridge polarity
 #define VHP                            0x0200                                  // rw-- V phase upper bridge polarity
 #define VLP                            0x0100                                  // rw-- V phase lower bridge polarity
 #define UHP                            0x0080                                  // rw-- U phase upper bridge polarity
 #define ULP                            0x0040                                  // rw-- U phase lower bridge polarity
 #define WHE                            0x0020                                  // rw-- W phase upper bridge enable
 #define WLE                            0x0010                                  // rw-- W phase lower bridge enable
 #define VHE                            0x0008                                  // rw-- V phase upper bridge enable
 #define VLE                            0x0004                                  // rw-- V phase lower bridge enable
 #define UHE                            0x0002                                  // rw-- U phase upper bridge enable
 #define ULE                            0x0001                                  // rw-- U phase lower bridge enable

/******************************************************************************/
/*                                     PFC                                    */
/******************************************************************************/
/******************** Bits definition for PFC_CR0 register ********************/
 #define COM_ST                         0x100                                   // r--- Feedforward compensation current state: 1-dccm, 0-ddcm
 #define UAVGSW                         0x80                                    // rw-- Software start UAVG calculation; 0: no start, 1: start (HW auto-clears at next moment; writing 0 has no effect)
 #define COM_DIS                        0x40                                    // rw-- Feedforward compensation disable; 1: calculate com only, not applied to output
 #define PFC_FM                         0x20                                    // rw-- Protection action select; 0: CMP5/CMP11 trigger respective outputs; 1: either channel protection stops both outputs
 #define UAVGCDIS                       0x10                                    // rw-- Hardware auto UAVG calculation disable; 0: not disabled, 1: disabled
 #define PFCOA                          0x08                                    // rw-- Cycle-by-cycle current limit recovery enable
 #define IAC2EN                         0x04                                    // rw-- PFC2 enable
 #define PFCOE                          0x02                                    // rw-- PFC output enable, P04/P05
 #define PFCEN                          0x01                                    // rw-- PFC enable
          
/******************** Bits definition for PFC_CR1 register ********************/
 #define UACSAMSEL1                     0x80                                    // rw-- UAC sampling divider 1; sample once every 1/2/4/8 carrier periods
 #define UACSAMSEL0                     0x40                                    // rw-- UAC sampling divider 0; sample once every 1/2/4/8 carrier periods
 #define UTHR                           0x20                                    // rw-- UAC average calculation starting voltage
 #define UCTHR4                         0x10                                    // rw-- UAC 2/3N setting4
 #define UCTHR3                         0x08                                    // rw-- UAC 2/3N setting3
 #define UCTHR2                         0x04                                    // rw-- UAC 2/3N setting2
 #define UCTHR1                         0x02                                    // rw-- UAC 2/3N setting1
 #define UCTHR0                         0x01                                    // rw-- UAC 2/3N setting0
          
/******************** Bits definition for PFC_CR2 register ********************/
 #define PFC_IF                         0x8000                                  // rw0- PFC carrier underflow interrupt flag
 #define IAC_DDCM_DIS                   0x2000                                  // rw-- KIAC mode select; 0: internal vo/(vo-vi)*don calc; 1: no internal calc
 #define DDCM_SEL                       0x1000                                  // rw-- PFC_DCCMCS0 effect; 0: offset, positive=reduction; 1: scaling, Q15 format
 #define PFC_UDCSEL                     0x800                                   // rw-- PFC_UDC filter select; 0: NFOC_UDCFLT, 1: NFOC_UDC
 #define PFC_IE                         0x400                                   // rw-- PFC carrier underflow interrupt enable
 #define PFC_DR2MD                      0x200                                   // rw-- When enabled, DR2 value follows DR
 #define DRMIN_EN                       0x100                                   // rw-- Output minimum duty cycle limit
 #define PFC_COMMD1                     0x80                                    // rw-- Feedforward compensation mode; 00: internal udc_uk/(uavg*uavg); 01: internal udc_uk only; 1x: software fills kddcm
 #define PFC_COMMD0                     0x40                                    // rw-- Feedforward compensation mode; 00: internal udc_uk/(uavg*uavg); 01: internal udc_uk only; 1x: software fills kddcm
 #define PFC_TRIGMD                     0x20                                    // rw-- IAC/IAC2 sampling timing select; 0: end of high level; 1: middle of high level
 #define DRMIN_THR4                     0x10                                    // rw-- Output minimum duty cycle config bit4
 #define DRMIN_THR3                     0x08                                    // rw-- Output minimum duty cycle config bit3
 #define DRMIN_THR2                     0x04                                    // rw-- Output minimum duty cycle config bit2
 #define DRMIN_THR1                     0x02                                    // rw-- Output minimum duty cycle config bit1
 #define DRMIN_THR0                     0x01                                    // rw-- Output minimum duty cycle config bit0
 
/******************************************************************************/
/*                                      FOC                                    */
/******************************************************************************/
/******************** Bits definition f or DRV_FCR0 register *******************/
// rw-- 001: est_dis Skip estimator, start from ZALPHA; user fills NFOC_ZALPHA/ZBETA; MR can use this mode
// rw-- 010: zab_dis Skip estimator to ZALPHA/ZBETA, start from EALPHA/EBETA; user fills EALPHA/EBETA
// rw-- 011: eab_dis Skip estimator to EALPHA/EBETA, start from velocity; user fills NFOC_OMEGA; alternative mode, use case TBD
// rw-- 100: ang_dis Skip estimator to angle calculation, start from current loop; user fills NFOC_THETA; most servo applications use this mode
// rw-- 101: smozab_dis, Skip SMO estimated current to ZALPHA, start from ZALPHA; user fills NFOC_ZALPHA/ZBETA
 #define FDIS_MD2                       0x8000                                   // rw-- FDISMD[2]
 #define FDIS_MD1                       0x4000                                   // rw-- FDISMD[1]
 #define FDIS_MD0                       0x2000                                   // rw-- FDISMD[0]
 #define UALBE_SEL                      0x1000                                   // rw-- FOC_UDCALP/UDCBET calculation source select
 #define LO_EN                          0x0800                                   // rw-- Low-speed observer enable
 #define ITPOWMD1                       0x0400                                   // rw-- Power loop calculation mode select config1
 #define ITPOWMD0                       0x0200                                   // rw-- Power loop calculation mode select config0
 #define NMFPEN                         0x0100                                   // rw-- AO observer enable
 #define NVQDIS                         0x0080                                   // rw-- Q-axis PI disable
 #define NVDDIS                         0x0040                                   // rw-- D-axis PI disable
 #define NOVMDL                         0x0020                                   // rw-- Over-modulation enable
 #define NCSAMMD3                       0x0010                                   // rw-- Current sampling mode config3
 #define NCSAMMD2                       0x0008                                   // rw-- Current sampling mode config2
 #define NCSAMMD1                       0x0004                                   // rw-- Current sampling mode config1
 #define NCSAMMD0                       0x0002                                   // rw-- Current sampling mode config0
 #define NCALEN                         0x0001                                   // rw-- FOC calculation enable; per-carrier FOC calc, current sampling, duty auto-update to DRV
/******************** Bits definition for DRV_FCR1 register *******************/
 #define WPIAUTO1                       0x8000                                   // rw-- SysTick calculate outer loop once
 #define WPIAUTO0                       0x4000                                   // rw-- Carrier period calculation onceouter loop
 #define WPILDEN                        0x2000                                   // rw-- IQREF auto-load enable, IQREF=WUK
 #define FG_MD                          0x1000                                   // rw-- FG count clock select; 0: 750KHz count, 1: 48MHz count
 #define WPIMD1                         0x0800                                   // rw-- 00:User manually fills WFDB; 01: velocity loop
 #define WPIMD0                         0x0400                                   // rw-- 10:Voltage loop; 11: power loop
 #define RAMP_AUTO                      0x0200                                   // rw-- Hardware auto ramp enable, SysTick calculates once
 #define RAMPMD1                        0x0100                                   // rw-- 00: No update; 01: auto update to WREF
 #define RAMPMD0                        0x0080                                   // rw-- 10: Auto update to IQREF; 11: auto update to UQ[31:16]
 #define OME_STA_EN                     0x0040                                   // rw-- OMEGA startup enable
 #define CT_SEL                         0x0020                                   // rw-- FOC calculation timing; 0: calc at next overflow after current sampling; 1: calc immediately after current sampling
 #define ANGMAMD                        0x0010                                   // rw-- Angle manual mode; 0: THETA from ETHETA; 1: THETA from software
 #define OME_ABS_EN                     0x0008                                   // rw-- Estimated angle invert enable
 #define FG_IDLE_LEVEL                  0x0004                                   // rw-- FG initial level
 #define FG_CALEN                       0x0002                                   // rw-- FG calculation enable
 #define FG_OE                          0x0001                                   // rw-- FG output enable
/******************** Bits definition for DRV_FCR2 register *******************/
 #define HFI_ST                         0x8000                                   // rw-- HF injection UD state; 0: positive UD, 1: negative UD
 #define OFFSET_EN                      0x4000                                   // rw-- Current reference auto-calibration enable
 #define FWEAK_MD                       0x2000                                   // rw-- Field weakening mode: mode 0, mode 1
 #define FWEAK_EN                       0x1000                                   // rw-- Field weakening enable
 #define HFI_MD1                        0x0800                                   // rw-- HF injection delta-delta ig mode enable
 #define UABC_EN                        0x0400                                   // rw-- Three-phase voltage sampling enable
 #define OMESTA_MD                      0x0200                                   // rw-- OMEGA startup transition; 1: new method, 0: old method
 #define NSEG5                          0x0100                                   // rw-- 5-segment enable
 #define UQINJ_EN                       0x0080                                   // rw-- UQ injection enable; auto-updates NFOC_UQCPS when enabled
 #define FO_EN                          0x0040                                   // rw-- Flux observer enable
 #define HFI_MD                         0x0020                                   // rw-- HF injection delta-delta iq mode enable
 #define HFI_2XMD                       0x0010                                   // rw-- HF injection 2x frequency processing enable
 #define OMELD_EN                       0x0008                                   // rw-- Velocity select; 0: estimator velocity for angle calc; 1: HFI or LO velocity
 #define HFI_CAL_EN                     0x0004                                   // rw-- HF injection enable
 #define HFI_TOG_EN                     0x0002                                   // rw-- HFI_ST auto-invert enable
 #define IDQ_MD                         0x0001                                   // rw-- ID/IQ mode select enable, id=(id0+id1)/2, iq=(iq0+iq1)/2
 /******************** Bits definition for DRV_FCR3 register *******************/
 #define EPI_DIS_ONCE                   0x8000                                   // rw-- Estimator PI single-disable enable      /* factory */
 #define DEL_MD                         0x2000                                   // rw-- Estimated DELTHE calc mode; 0: atan, 1: sin/cos
 #define SMO_MD                         0x1000                                   // rw-- SMO calc mode; 0: ZALPHA/ZBETA+EALPHA/EBETA; 1: ZALPHA/ZBETA+0
 #define QFAC_SEL4                      0x0800                                   // rw-- IQREF filter 4 data format select; 0: Q29, 1: Q20
 #define QFAC_SEL3                      0x0400                                   // rw-- IQREF filter 3 data format select; 0: Q29, 1: Q20
 #define QFAC_SEL2                      0x0200                                   // rw-- IQREF filter 2 data format select; 0: Q29, 1: Q20
 #define QFAC_SEL1                      0x0100                                   // rw-- IQREF filter 1 data format select; 0: Q29, 1: Q20
 #define IQRF4_EN                       0x0080                                   // rw-- IQREF filter 4 enable
 #define IQRF3_EN                       0x0040                                   // rw-- IQREF filter 3 enable
 #define IQRF2_EN                       0x0020                                   // rw-- IQREF filter 2 enable
 #define IQRF1_EN                       0x0010                                   // rw-- IQREF filter 1 enable
 #define IQRF_SEL                       0x0008                                   // rw-- IQREF filter calculation period select; 0: current loop, 1: velocity loop
 #define IIG_EN                         0x0004                                   // rw-- Mask first-beat current during sector switching for all current sampling modes     /* factory */
 #define DLY_EN                         0x0002                                   // rw-- FOC calculation delay enable; used with CT_SEL, typically at high carrier frequencies
 #define SAMPM_EN                       0x0001                                   // rw-- Sampling point manual enable
 /******************** Bits definition for DRV_FCR4 register *******************/
 #define MMT_CAL						0x8000                                   // rw-- M/MT method calc flag; Read: 0=complete, 1=calculating; Write: 0=no effect, 1=start calc (Note: HW clears after SW writes 1)
 #define SF_CAL							0x4000                                   // rw-- Velocity feedback filter calc flag; Read: 0=complete, 1=calculating; Write: 0=no effect, 1=start calc
 #define WPI_CAL						0x2000                                   // rw-- Outer loop calculation flag (read-only); 0: no calc, 1: calc
 #define SPEED_AUTO						0x1000                                   // rw-- Velocity auto-calc enable; cal_en=0: MMT+mean filter only; cal_en=1: current loop MMT+mean filter, outer loop PDFF
 #define CUR_SAM_EN						0x0800                                   // rw-- Force current sampling enable; samples regardless of cal_en; 0: disable, 1: enable
 #define IQREF_INV						0x0400                                   // rw-- 4-stage filter output inverted and loaded into IQREF; 0: disable, 1: enable
 #define PDFF_EN						0x0200                                   // rw-- Outer loop PDFF enable; 0: use PI, 1: use PDFF
 #define WPI_CAL_CYCLE1                 0x0100                                   // rw-- Outer loop calc period select (DRV_FCR1[wpi_auto] must be 11); 00: every 1 MMT period, 01: every 2 MMT periods
 #define WPI_CAL_CYCLE0                 0x0080                                   // rw-- Outer loop calc period select (DRV_FCR1[wpi_auto] must be 11); 10: every 4 MMT periods, 11: every 8 MMT periods
 #define SLF2_EN                        0x0040                                   // rw-- Velocity feedback LPF 2 enable; 0: disable, 1: enable
 #define SLF1_EN                        0x0020                                   // rw-- Velocity feedback LPF 1 enable; 0: disable, 1: enable
 #define SMF_EN                         0x0010                                   // rw-- Velocity feedback mean filter enable; 0: disable, 1: enable
 #define MMT_CAL_CYCLE1                 0x0008                                   // rw-- M/MT method calc period select; 00: every 1 carrier interrupt, 01: every 2 carrier interrupts
 #define MMT_CAL_CYCLE0                 0x0004                                   // rw-- M/MT method calc period select; 10: every 4 carrier interrupts, 11: every 8 carrier interrupts
 #define MMT_SEL                        0x0002                                   // rw-- M/MT method select; 0: M-method, 1: MT-method
 #define UDQ_LPF_EN                     0x0001                                   // rw-- UDQ LPF enable; 0: disable, 1: enable
/******************** Bits definition for DRV_FCR5 register *******************/
 #define WPI_SERVO_EN					0x8000                                   // rw-- Servo outer loop calc enable (read-only); 0: no calc, 1: calc, updates every carrier, wider than WPI_CAL for easy SW sampling
 #define IQRF_UPDATE					0x4000                                   // rw-- Servo 4-stage filter 1st stage coefficient update enable; 0: disable, 1: enable
 #define ANGFU_MD1                      0x1000									 //Angle fusion mode bit
 #define ANGFU_MD0                      0x0800									 //Angle fusion mode bit
 #define DTC_EN							0x0400									 //Dead-time compensation enable; 0: disable, 1: enable
 #define ENCODER_STA_CYCLE1             0x0100                                   // rw-- Absolute encoder auto-trigger period select; 00: every 1 carrier interrupt, 01: every 2 carrier interrupts
 #define ENCODER_STA_CYCLE0             0x0080                                   // rw-- Absolute encoder auto-trigger period select; 10: every 4 carrier interrupts, 11: every 8 carrier interrupts
 #define ANGFU_MAEN                     0X0010									 //Angle fusion manual mode enable bit
 #define ANGFU_EN                       0x0008									 //Angle fusion enable bit
 #define IDQ_FB_SEL                     0x0004									 //ID/IQ current loop feedback value select bit
 #define IDQ_LPF_EN                     0x0002									 //ID/IQ low-pass filter enable
 #define LUT_EN							0x0001									 //0:LUT, 1:Cordic

/******************** Bits definition for DRV_FCR6 register *******************/
 #define CVD_SEL                          0x0400                 //Complex vector limit source select bit
 #define CVD_EN                           0x0200                 //Complex vector decoupling enable bit
 #define ESTU_SEL2                        0x0100                 //Estimator Q-format select2
 #define ESTU_SEL1                        0x0080                 //Estimator Q-format select1
 #define ESTU_SEL0                        0x0040                 //Estimator Q-format select0
 #define ESTID_SEL1                       0x0020                 //Estimator ID select bit1
 #define ESTID_SEL0                       0x0010                 //Estimator ID select bit0
 #define MFP_MD                           0x0008                 //SMO/AO mode select bit
 #define EST_MD2                          0x0004                 //Estimator mode select bit2
 #define EST_MD1                          0x0002                 //Estimator mode select bit1
 #define EST_MD0                          0x0001                 //Estimator mode select bit0

/******************** Bits definition for DRV_FCR7 register *******************/
 #define CVKP_SEL1						  0x8000                         //Decoupling controller KP Q-format select bit1
 #define CVKP_SEL0 						  0x4000                         //Decoupling controller KP Q-format select bit0
 #define CVKI1_SEL1 					  0x2000                         //Decoupling controller KI1 Q-format select bit1
 #define CVKI1_SEL0  					  0x1000                         //Decoupling controller KI1 Q-format select bit0
 #define CVKI2_SEL1  					  0x0800                         //Decoupling controller KI2 Q-format select bit1
 #define CVKI2_SEL0 					  0x0400                         //Decoupling controller KI2 Q-format select bit0
 #define CVKO_SEL1                        0x0200                         //Decoupling controller other coefficients Q-format select bit1
 #define CVKO_SEL0                        0x0100                         //Decoupling controller other coefficients Q-format select bit0
 #define CBA_MTSAM2                       0x0004                         //Triple-resistor current sampling channel select bit
 #define CBA_MTSAM1                       0x0002                         //Triple-resistor current sampling channel select bit
 #define CBA_MTSAM0                       0x0001                         //Triple-resistor current sampling channel select bit


 #define NFOC_BASE                      0x30000000
 #define NFOC_I1                        (*(volatile  int16* )(NFOC_BASE + ( 222*2)))    // RV:0000H 1st sample ADC value      /* factory */
 #define NFOC_I2                        (*(volatile  int16* )(NFOC_BASE + ( 223*2)))    // RV:0000H 2nd sample ADC value      /* factory */
 #define NFOC_IA                        (*(volatile  int16* )(NFOC_BASE + ( 224*2)))    // RV:0000H Calculated IA
 #define NFOC_IB                        (*(volatile  int16* )(NFOC_BASE + ( 225*2)))    // RV:0000H Calculated IB
 #define NFOC_IC                        (*(volatile  int16* )(NFOC_BASE + ( 226*2)))    // RV:0000H Calculated IC
 #define NFOC_ICMAX                     (*(volatile  int16* )(NFOC_BASE + ( 227*2)))    // RV:0000H IC max value
 #define NFOC_IAMAX                     (*(volatile  int16* )(NFOC_BASE + ( 228*2)))    // RV:0000H IA max value
 #define NFOC_IBMAX                     (*(volatile  int16* )(NFOC_BASE + ( 229*2)))    // RV:0000H IB max value
 #define NFOC_IALPHA                    (*(volatile  int16* )(NFOC_BASE + ( 154*2)))    // RV:0000H IALPHA after Clarke transform
 #define NFOC_IBETA                     (*(volatile  int16* )(NFOC_BASE + ( 155*2)))    // RV:0000H IBETA after Clarke transform
 #define NFOC_ID                        (*(volatile  int16* )(NFOC_BASE + ( 156*2)))    // RV:0000H ID after Park transform
 #define NFOC_IQ                        (*(volatile  int16* )(NFOC_BASE + ( 157*2)))    // RV:0000H IQ after Park transform
 #define NFOC_IDFLT                     (*(volatile  int32* )(NFOC_BASE + ( 158*2)))    // RV:0000H ID filtered value (32-bit)
 #define NFOC_IDFLTH                    (*(volatile  int16* )(NFOC_BASE + ( 159*2)))    // RV:0000H ID filtered value high 16-bit
 #define NFOC_IQFLT                     (*(volatile  int32* )(NFOC_BASE + ( 170*2)))    // RV:0000H IQ filtered value (32-bit)
 #define NFOC_IQFLTH                    (*(volatile  int16* )(NFOC_BASE + ( 171*2)))    // RV:0000H IQ filtered value high 16-bit
 #define NFOC_THETA                     (*(volatile  int32* )(NFOC_BASE + ( 172*2)))    // RV:0000H Angle value (32-bit)
 #define NFOC_THETAL                    (*(volatile  int16* )(NFOC_BASE + ( 172*2)))    // RV:0000H Angle value low 16-bit
 #define NFOC_THETAH                    (*(volatile  int16* )(NFOC_BASE + ( 173*2)))    // RV:0000H Angle value high 16-bit
 #define NFOC_EALPHA                    (*(volatile  int32* )(NFOC_BASE + ( 174*2)))    // RV:0000H Estimator estimated back-EMF EALPHA (32-bit)
 #define NFOC_EALPHAH                   (*(volatile  int16* )(NFOC_BASE + ( 175*2)))    // RV:0000H Estimator estimated back-EMF EALPHA high 16-bit
 #define NFOC_EBETA                     (*(volatile  int32* )(NFOC_BASE + ( 186*2)))    // RV:0000H Estimator estimated back-EMF EBETA (32-bit)
 #define NFOC_EBETAH                    (*(volatile  int16* )(NFOC_BASE + ( 187*2)))    // RV:0000H Estimator estimated back-EMF EBETA high 16-bit
 #define NFOC_ETHETA                    (*(volatile  int32* )(NFOC_BASE + ( 188*2)))    // RV:0000H Estimator estimated angle (32-bit)
 #define NFOC_ETHETAH                   (*(volatile  int16* )(NFOC_BASE + ( 189*2)))    // RV:0000H Estimator angle high 16-bit
 #define NFOC_ZALORG                    (*(volatile  int16* )(NFOC_BASE + ( 190*2)))    // RV:0000H Estimated back-EMF      /* factory */
 #define NFOC_ZBEORG                    (*(volatile  int16* )(NFOC_BASE + ( 191*2)))    // RV:0000H Estimated back-EMF      /* factory */
 #define NFOC_EMF                       (*(volatile  int16* )(NFOC_BASE + ( 240*2)))    // RV:0000H EALPHAandEBETAcalculationmagnitude (sqrt of sum of squares), i.e. Estimated back-EMFmagnitude
 #define NFOC_ATHETA                    (*(volatile  int16* )(NFOC_BASE + ( 241*2)))    // RV:0000H EALPHA/EBETA calculated angle      /* factory */
 #define NFOC_OMECLI                    (*(volatile  int32* )(NFOC_BASE + ( 256*2)))    // RV:0000H Omega startup real-time value (32-bit)      /* factory */
 #define NFOC_OMECLIL                   (*(volatile  int16* )(NFOC_BASE + ( 256*2)))    // RV:0000H Omega startup real-time value low 16-bit      /* factory */
 #define NFOC_OMECLIH                   (*(volatile  int16* )(NFOC_BASE + ( 257*2)))    // RV:0000H Omega startup real-time value high 16-bit      /* factory */
 #define NFOC_OMEGA                     (*(volatile  int16* )(NFOC_BASE + ( 258*2)))    // RV:0000H Estimated OMEGA
   
 #define NFOC_IESTA                     (*(volatile  int16* )(NFOC_BASE + ( 260*2)))    // RV:0000H Estimated current IALPHA
 #define NFOC_IESTB                     (*(volatile  int16* )(NFOC_BASE + ( 261*2)))    // RV:0000H Estimated current IBETA
 #define NFOC_OMEFLT                    (*(volatile  int32* )(NFOC_BASE + ( 262*2)))    // RV:0000H OMEGA 1st-stage filtered value (32-bit)
 #define NFOC_OMEFLTH                   (*(volatile  int16* )(NFOC_BASE + ( 263*2)))    // RV:0000H OMEGA 1st-stage filtered value high 16-bit
 #define NFOC_OMEFL2                    (*(volatile  int32* )(NFOC_BASE + ( 264*2)))    // RV:0000H OMEGA 2nd-stage filtered value (32-bit)
 #define NFOC_OMEFL2H                   (*(volatile  int16* )(NFOC_BASE + ( 265*2)))    // RV:0000H OMEGA 2nd-stage filtered value high 16-bit
 #define NFOC_ZALPHA                    (*(volatile  int16* )(NFOC_BASE + ( 266*2)))    // RV:0000H before filteringEstimated back-EMF      /* factory */
 #define NFOC_ZBETA                     (*(volatile  int16* )(NFOC_BASE + ( 267*2)))    // RV:0000H before filteringEstimated back-EMF      /* factory */
 #define NFOC_KLPF                      (*(volatile  int16* )(NFOC_BASE + ( 268*2)))    // RV:0000H Estimator LPF coefficient
 #define NFOC_UDFIN                     (*(volatile  int16* )(NFOC_BASE + ( 270*2)))    // RV:0000H UD final value
 #define NFOC_UQFIN                     (*(volatile  int16* )(NFOC_BASE + ( 271*2)))    // RV:0000H UQ final value
 #define NFOC_UALPHA                    (*(volatile  int16* )(NFOC_BASE + ( 272*2)))    // RV:0000H UALPHA
 #define NFOC_UBETA                     (*(volatile  int16* )(NFOC_BASE + ( 273*2)))    // RV:0000H UBETA
 #define NFOC_UALORG                    (*(volatile  int16* )(NFOC_BASE + ( 140*2)))    // RV:0000H UALORG
 #define NFOC_UBEORG                    (*(volatile  int16* )(NFOC_BASE + ( 141*2)))    // RV:0000H UBEORG
 #define NFOC_Y                         (*(volatile  int16* )(NFOC_BASE + ( 274*2)))    // RV:0000H SVPWM calculation intermediate value      /* factory */
 #define NFOC_Z                         (*(volatile  int16* )(NFOC_BASE + ( 275*2)))    // RV:0000H SVPWM calculation intermediate value      /* factory */

 #define NFOC_T1ORG                     (*(volatile  int16* )(NFOC_BASE + (450*2)))     // RV:0000H SVPWM calculation intermediate value      /* factory */
 #define NFOC_T2ORG                     (*(volatile  int16* )(NFOC_BASE + (451*2)))     // RV:0000H SVPWM calculation intermediate value      /* factory */
 #define NFOC_T1RC                      (*(volatile  int16* )(NFOC_BASE + (452*2)))     // RV:0000H SVPWM calculation intermediate value      /* factory */
 #define NFOC_T2RC                      (*(volatile  int16* )(NFOC_BASE + (453*2)))     // RV:0000H SVPWM calculation intermediate value      /* factory */
 #define NFOC_OMUNIT                    (*(volatile  int16* )(NFOC_BASE + (454*2)))     // RV:0000H Over-modulation amplification coefficient
 #define NFOC_TC                        (*(volatile  int16* )(NFOC_BASE + (456*2)))     // RV:0000H SVPWM calculation intermediate value      /* factory */
 #define NFOC_TB                        (*(volatile  int16* )(NFOC_BASE + (457*2)))     // RV:0000H SVPWM calculation intermediate value      /* factory */
 #define NFOC_TA                        (*(volatile  int16* )(NFOC_BASE + (458*2)))     // RV:0000H SVPWM calculation intermediate value      /* factory */
 #define NFOC_DLYCNT                    (*(volatile  uint16* )(NFOC_BASE  + (459*2)))    // RV:0000H CLK count for dly_en delay function
 #define NFOC_TAON                      (*(volatile  int16* )(NFOC_BASE + (460*2)))     // RV:0000H SVPWM calculation intermediate value      /* factory */
 #define NFOC_TAOND                     (*(volatile  int16* )(NFOC_BASE + (461*2)))     // RV:0000H SVPWM calculation intermediate value      /* factory */
 #define NFOC_TBON                      (*(volatile  int16* )(NFOC_BASE + (462*2)))     // RV:0000H SVPWM calculation intermediate value      /* factory */
 #define NFOC_TBOND                     (*(volatile  int16* )(NFOC_BASE + (463*2)))     // RV:0000H SVPWM calculation intermediate value      /* factory */
 #define NFOC_TCON                      (*(volatile  int16* )(NFOC_BASE + (464*2)))     // RV:0000H SVPWM calculation intermediate value      /* factory */
 #define NFOC_TCOND                     (*(volatile  int16* )(NFOC_BASE + (465*2)))     // RV:0000H SVPWM calculation intermediate value      /* factory */
 #define NFOC_TADTC                     (*(volatile  int16* )(NFOC_BASE + (466*2)))     // RV:0000H SVPWM calculation intermediate value      /* factory */
 #define NFOC_TADTCD                    (*(volatile  int16* )(NFOC_BASE + (467*2)))     // RV:0000H SVPWM calculation intermediate value      /* factory */
 #define NFOC_TBDTC                     (*(volatile  int16* )(NFOC_BASE + (468*2)))     // RV:0000H SVPWM calculation intermediate value      /* factory */
 #define NFOC_TBDTCD                    (*(volatile  int16* )(NFOC_BASE + (469*2)))     // RV:0000H SVPWM calculation intermediate value      /* factory */
 #define NFOC_TCDTC                     (*(volatile  int16* )(NFOC_BASE + (470*2)))     // RV:0000H SVPWM calculation intermediate value      /* factory */
 #define NFOC_TCDTCD                    (*(volatile  int16* )(NFOC_BASE + (471*2)))     // RV:0000H SVPWM calculation intermediate value      /* factory */

 #define NFOC_DR1                       (*(volatile uint16* )(NFOC_BASE + ( 70*2)))     // RV:0000H SVPWM calculation intermediate value      /* factory */
 #define NFOC_DR1N                      (*(volatile uint16* )(NFOC_BASE + ( 71*2)))     // RV:0000H SVPWM calculation intermediate value      /* factory */
 #define NFOC_DR2                       (*(volatile uint16* )(NFOC_BASE + ( 72*2)))     // RV:0000H SVPWM calculation intermediate value      /* factory */
 #define NFOC_DR2N                      (*(volatile uint16* )(NFOC_BASE + ( 73*2)))     // RV:0000H SVPWM calculation intermediate value      /* factory */
 #define NFOC_DR3                       (*(volatile uint16* )(NFOC_BASE + ( 74*2)))     // RV:0000H SVPWM calculation intermediate value      /* factory */
 #define NFOC_DR3N                      (*(volatile uint16* )(NFOC_BASE + ( 75*2)))     // RV:0000H SVPWM calculation intermediate value      /* factory */
 #define NFOC_DRA                       (*(volatile uint16* )(NFOC_BASE + ( 76*2)))     // RV:0000H SVPWM value loaded to DRV      /* factory */
 #define NFOC_DRAN                      (*(volatile uint16* )(NFOC_BASE + ( 77*2)))     // RV:0000H SVPWM value loaded to DRV      /* factory */
 #define NFOC_DRB                       (*(volatile uint16* )(NFOC_BASE + ( 78*2)))     // RV:0000H SVPWM value loaded to DRV      /* factory */
 #define NFOC_DRBN                      (*(volatile uint16* )(NFOC_BASE + ( 79*2)))     // RV:0000H SVPWM value loaded to DRV      /* factory */
 #define NFOC_DRC                       (*(volatile uint16* )(NFOC_BASE + ( 80*2)))     // RV:0000H SVPWM value loaded to DRV      /* factory */
 #define NFOC_DRCN                      (*(volatile uint16* )(NFOC_BASE + ( 81*2)))     // RV:0000H SVPWM value loaded to DRV      /* factory */
 #define NFOC_UDCALP                    (*(volatile  int16* )(NFOC_BASE + ( 82*2)))     // RV:0000H UDC*UALPHA
 #define NFOC_UDCBET                    (*(volatile  int16* )(NFOC_BASE + ( 83*2)))     // RV:0000H UDC*UBETA
 #define NFOC_MAY1                      (*(volatile  int16* )(NFOC_BASE + ( 84*2)))     // RV:0000H AO observer related signal      /* factory */
 #define NFOC_MBY1                      (*(volatile  int16* )(NFOC_BASE + ( 85*2)))     // RV:0000H AO observer related signal      /* factory */
 #define NFOC_MAY2                      (*(volatile  int16* )(NFOC_BASE + ( 86*2)))     // RV:0000H AO observer related signal      /* factory */
 #define NFOC_MBY2                      (*(volatile  int16* )(NFOC_BASE + ( 87*2)))     // RV:0000H AO observer related signal      /* factory */
 #define NFOC_MAY3                      (*(volatile  int16* )(NFOC_BASE + ( 88*2)))     // RV:0000H AO observer related signal      /* factory */
 #define NFOC_MBY3                      (*(volatile  int16* )(NFOC_BASE + ( 89*2)))     // RV:0000H AO observer related signal      /* factory */
 #define NFOC_MAY4                      (*(volatile  int16* )(NFOC_BASE + ( 90*2)))     // RV:0000H AO observer related signal      /* factory */
 #define NFOC_MBY4                      (*(volatile  int16* )(NFOC_BASE + ( 91*2)))     // RV:0000H AO observer related signal      /* factory */
 #define NFOC_MAY5                      (*(volatile  int16* )(NFOC_BASE + ( 92*2)))     // RV:0000H AO observer related signal      /* factory */
 #define NFOC_MBY5                      (*(volatile  int16* )(NFOC_BASE + ( 93*2)))     // RV:0000H AO observer related signal      /* factory */
 #define NFOC_MAU1                      (*(volatile  int16* )(NFOC_BASE + ( 94*2)))     // RV:0000H AO observer related signal      /* factory */
 #define NFOC_MBU1                      (*(volatile  int16* )(NFOC_BASE + ( 95*2)))     // RV:0000H AO observer related signal      /* factory */
 #define NFOC_MAU2                      (*(volatile  int16* )(NFOC_BASE + ( 96*2)))     // RV:0000H AO observer related signal      /* factory */
 #define NFOC_MBU2                      (*(volatile  int16* )(NFOC_BASE + ( 97*2)))     // RV:0000H AO observer related signal      /* factory */
 #define NFOC_MAU3                      (*(volatile  int16* )(NFOC_BASE + ( 98*2)))     // RV:0000H AO observer related signal      /* factory */
 #define NFOC_MBU3                      (*(volatile  int16* )(NFOC_BASE + ( 99*2)))     // RV:0000H AO observer related signal      /* factory */
 #define NFOC_MAU4                      (*(volatile  int16* )(NFOC_BASE + (100*2)))     // RV:0000H AO observer related signal      /* factory */
 #define NFOC_MBU4                      (*(volatile  int16* )(NFOC_BASE + (101*2)))     // RV:0000H AO observer related signal      /* factory */
    
 #define NFOC_FTCPS                     (*(volatile  int16* )(NFOC_BASE + (102*2)))     // RV:0000H Calculated dynamic compensation angleFTCPS = FTCK*OMEFL2*FBASE
 #define NFOC_FTHETA                    (*(volatile  int16* )(NFOC_BASE + (103*2)))     // RV:0000H Feedback angle to estimator PI
 #define NFOC_IS                        (*(volatile  int16* )(NFOC_BASE + (104*2)))     // RV:0000H IALPHA/IBETA magnitude (sqrt of sum of squares)
 #define NFOC_ITHETA                    (*(volatile  int16* )(NFOC_BASE + (105*2)))     // RV:0000H IALPHA/IBETA calculated angle
 #define NFOC_ITFLT                     (*(volatile  int32* )(NFOC_BASE + (106*2)))     // RV:0000H ITRIP filtered value (32-bit)
 #define NFOC_ITFLTH                    (*(volatile  int16* )(NFOC_BASE + (107*2)))     // RV:0000H ITRIP filtered value high 16-bit
 #define NFOC_ITRIP                     (*(volatile  int16* )(NFOC_BASE + (108*2)))     // RV:0000H Sampled ITRIP, for power calculation
 #define NFOC_POWER                     (*(volatile  int16* )(NFOC_BASE + (109*2)))     // RV:0000H Power value
 #define NFOC_US                        (*(volatile  int16* )(NFOC_BASE + (110*2)))     // RV:0000H UALPHA/UBETA magnitude (sqrt of sum of squares)
 #define NFOC_UTHETA                    (*(volatile  int16* )(NFOC_BASE + (111*2)))     // RV:0000H UALPHA/UBETA calculated angle
 
 #define NFOC_ID0                       (*(volatile  int16* )(NFOC_BASE + (122*2)))     // RV:0000H D-axis current from previous FOC calculation
 #define NFOC_IQ0                       (*(volatile  int16* )(NFOC_BASE + (123*2)))     // RV:0000H Q-axis current from previous FOC calculation
 #define NFOC_DELIAL                    (*(volatile  int16* )(NFOC_BASE + (124*2)))     // RV:0000H HF current      /* factory */
 #define NFOC_DELIBE                    (*(volatile  int16* )(NFOC_BASE + (125*2)))     // RV:0000H HF current      /* factory */
 #define NFOC_HALPHA                    (*(volatile  int16* )(NFOC_BASE + (126*2)))     // RV:0000H HF currentenvelope
 #define NFOC_HBETA                     (*(volatile  int16* )(NFOC_BASE + (127*2)))     // RV:0000H HF currentenvelope
 #define NFOC_HS                        (*(volatile  int16* )(NFOC_BASE + (138*2)))     // RV:0000H HALPHA/HBETA magnitude (sqrt of sum of squares)      /* factory */
 #define NFOC_HTHETA                    (*(volatile  int16* )(NFOC_BASE + (139*2)))     // RV:0000H HALPHA/HBETA calculated angle      /* factory */
 #define NFOC_DELIQ                     (*(volatile  int16* )(NFOC_BASE + (142*2)))     // RV:0000H HF injection calculation intermediate value
    
 #define NFOC_HKP                       (*(volatile  int16* )(NFOC_BASE + (112*2)))     // RV:0000H HF injection PI KP
 #define NFOC_HKI                       (*(volatile  int16* )(NFOC_BASE + (113*2)))     // RV:0000H HF injection PI KI
 #define NFOC_HMAX                      (*(volatile  int16* )(NFOC_BASE + (114*2)))     // RV:0000H HF injection PI upper limit
 #define NFOC_HMIN                      (*(volatile  int16* )(NFOC_BASE + (115*2)))     // RV:0000H HF injection PI lower limit
 #define NFOC_HEK                       (*(volatile  int16* )(NFOC_BASE + (116*2)))     // RV:0000H HF injection PI EK
 #define NFOC_HEK1                      (*(volatile  int16* )(NFOC_BASE + (117*2)))     // RV:0000H HF injection PI EK1
 #define NFOC_HUK                       (*(volatile  int32* )(NFOC_BASE + (118*2)))     // RV:0000H HF injection PI UK (32-bit)
 #define NFOC_HUKH                      (*(volatile  int16* )(NFOC_BASE + (119*2)))     // RV:0000H HF injection PI UK high 16-bit
 // #define NFOC_HEXC                      (*(volatile  int16* )(NFOC_BASE + (120*2))   )  // RV:0000H HF injectionPI UKoverflow value
    
 #define NFOC_DKP                       (*(volatile  int16* )(NFOC_BASE + (128*2)))     // RV:0000H D-axis PI current loop KP
 #define NFOC_DKI                       (*(volatile  int16* )(NFOC_BASE + (129*2)))     // RV:0000H D-axis PI current loop KI
 #define NFOC_DMAX                      (*(volatile  int16* )(NFOC_BASE + (130*2)))     // RV:0000H D-axis PI current loop upper limit
 #define NFOC_DMIN                      (*(volatile  int16* )(NFOC_BASE + (131*2)))     // RV:0000H D-axis PI current loop lower limit
 #define NFOC_DEK                       (*(volatile  int16* )(NFOC_BASE + (132*2)))     // RV:0000H D-axis PI current loop EK
 #define NFOC_DEK1                      (*(volatile  int16* )(NFOC_BASE + (133*2)))     // RV:0000H D-axis PI current loop EK1
 #define NFOC_DUK                       (*(volatile  int32* )(NFOC_BASE + (134*2)))     // RV:0000H D-axis PI current loop UK (32-bit); low 16-bit = complex vector Ukfin - uklimit
 #define NFOC_DUKH                      (*(volatile  int16* )(NFOC_BASE + (135*2)))     // RV:0000H D-axis PI current loop UK high 16-bit / complex vector UKLIMIT
 #define NFOC_CVDUK                     (*(volatile  int16* )(NFOC_BASE + (136*2)))     // RV:0000H Complex vector decoupling coefficient D-axis UK
 #define NFOC_CVKI2D                    (*(volatile  int16* )(NFOC_BASE + (137*2)))     // RV:0000H Complex vector decoupling coefficient D-axis KI2
 // #define NFOC_DEXC                      (*(volatile  int16* )(NFOC_BASE + (136*2)))  // RV:0000H DaxisPIcurrent loopUKoverflow value
 
 #define NFOC_QKP                       (*(volatile  int16* )(NFOC_BASE + (144*2)))     // RV:0000H Q-axis PI current loop KP
 #define NFOC_QKI                       (*(volatile  int16* )(NFOC_BASE + (145*2)))     // RV:0000H Q-axis PI current loop KI
 #define NFOC_QMAX                      (*(volatile  int16* )(NFOC_BASE + (146*2)))     // RV:0000H Q-axis PI current loop upper limit
 #define NFOC_QMIN                      (*(volatile  int16* )(NFOC_BASE + (147*2)))     // RV:0000H Q-axis PI current loop lower limit
 #define NFOC_QEK                       (*(volatile  int16* )(NFOC_BASE + (148*2)))     // RV:0000H Q-axis PI current loop EK
 #define NFOC_QEK1                      (*(volatile  int16* )(NFOC_BASE + (149*2)))     // RV:0000H Q-axis PI current loop EK1
 #define NFOC_QUK                       (*(volatile  int32* )(NFOC_BASE + (150*2)))     // RV:0000H Q-axis PI current loop UK (32-bit); low 16-bit = complex vector Ukfin - uklimit
 #define NFOC_QUKH                      (*(volatile  int16* )(NFOC_BASE + (151*2)))     // RV:0000H Q-axis PI current loop UK high 16-bit / complex vector UKLIMIT
 #define NFOC_CVQUK                     (*(volatile  int16* )(NFOC_BASE + (152*2)))     // RV:0000H Complex vector decoupling coefficient Q-axis UK
 #define NFOC_CVKI2Q                    (*(volatile  int16* )(NFOC_BASE + (153*2)))     // RV:0000H Complex vector decoupling coefficient Q-axis KI2
 // #define NFOC_QEXC                      (*(volatile  int16* )(NFOC_BASE + (152*2)))  // RV:0000H QaxisPIcurrent loopUKoverflow value

 #define NFOC_CVK1                      (*(volatile  int16* )(NFOC_BASE + (486*2)))     // RV:0000H Complex vector decoupling coefficient
 #define NFOC_CVK2                      (*(volatile  int16* )(NFOC_BASE + (496*2)))     // RV:0000H Complex vector decoupling coefficient
 #define NFOC_CVK3                      (*(volatile  int16* )(NFOC_BASE + (487*2)))     // RV:0000H Complex vector decoupling coefficient
 #define NFOC_CVDK4                     (*(volatile  int16* )(NFOC_BASE + (488*2)))     // RV:0000H Complex vector decoupling coefficient
 #define NFOC_CVQK4                     (*(volatile  int16* )(NFOC_BASE + (489*2)))     // RV:0000H Complex vector decoupling coefficient
 #define NFOC_CVDK5                     (*(volatile  int16* )(NFOC_BASE + (490*2)))     // RV:0000H Complex vector decoupling coefficient
 #define NFOC_CVQK5                     (*(volatile  int16* )(NFOC_BASE + (491*2)))     // RV:0000H Complex vector decoupling coefficient
 #define NFOC_UDCOM                     (*(volatile  int16* )(NFOC_BASE + (492*2)))     // RV:0000H Complex vector decoupling coefficient
 #define NFOC_UDAS                      (*(volatile  int16* )(NFOC_BASE + (493*2)))     // RV:0000H Complex vector decoupling coefficient
 #define NFOC_UQCOM                     (*(volatile  int16* )(NFOC_BASE + (494*2)))     // RV:0000H Complex vector decoupling coefficient
 #define NFOC_UQAS                      (*(volatile  int16* )(NFOC_BASE + (495*2)))     // RV:0000H Complex vector decoupling coefficient
 #define NFOC_UDCLIM                    (*(volatile  int16* )(NFOC_BASE + (497*2)))     // RV:0000H Complex vector decoupling coefficient
 #define NFOC_UDCMAX                    (*(volatile  int16* )(NFOC_BASE + (498 *2)))     // RV:0000H Complex vector decoupling coefficient
 #define NFOC_UDCMIN                    (*(volatile  int16* )(NFOC_BASE + (499 *2)))     // RV:0000H Complex vector decoupling coefficient
 #define NFOC_CVDULO                    (*(volatile  int16* )(NFOC_BASE + (385 *2)))     // RV:0000H Complex vector decoupling coefficient
 #define NFOC_CVQULO                    (*(volatile  int16* )(NFOC_BASE + (405 *2)))     // RV:0000H Complex vector decoupling coefficient
 #define NFOC_DUKF                      (*(volatile  int16* )(NFOC_BASE + (506 *2)))     // RV:0000H Complex vector decoupling coefficient
 #define NFOC_QUKF                      (*(volatile  int16* )(NFOC_BASE + (507 *2)))     // RV:0000H Complex vector decoupling coefficient

 
 #define NFOC_IRLOW                     (*(volatile  int16* )(NFOC_BASE + (8*2)))       // RV:0000H Current reference lower limit; triggers reference error when exceeded
 #define NFOC_IRUPP                     (*(volatile  int16* )(NFOC_BASE + (9*2)))       // RV:0000H Current reference upper limit; triggers reference error when exceeded
 
 #define NFOC_EKP                       (*(volatile  int16* )(NFOC_BASE + (160*2)))     // RV:0000H Estimator PI current loop KP
 #define NFOC_EKI                       (*(volatile  int16* )(NFOC_BASE + (161*2)))     // RV:0000H Estimator PI current loop KI
 #define NFOC_EMAX                      (*(volatile  int16* )(NFOC_BASE + (162*2)))     // RV:0000H Estimator PI current loop upper limit
 #define NFOC_EMIN                      (*(volatile  int16* )(NFOC_BASE + (163*2)))     // RV:0000H Estimator PI current loop lower limit
 #define NFOC_EEK                       (*(volatile  int16* )(NFOC_BASE + (164*2)))     // RV:0000H Estimator PI current loop EK
 #define NFOC_EEK1                      (*(volatile  int16* )(NFOC_BASE + (165*2)))     // RV:0000H Estimator PI current loop EK1
 #define NFOC_EUK                       (*(volatile  int32* )(NFOC_BASE + (166*2)))     // RV:0000H Estimator PI current loop UK (32-bit)
 #define NFOC_EUKH                      (*(volatile  int16* )(NFOC_BASE + (167*2)))     // RV:0000H Estimator PI current loop UK high 16-bit
 // #define NFOC_EEXC                      (*(volatile  int16* )(NFOC_BASE + (168*2)))  // RV:0000H EstimatorPIcurrent loopUKoverflow value

 #define NFOC_WKP                       (*(volatile  int16* )(NFOC_BASE + (176*2)))     // RV:0000H Outer loop PI current loop KP
 #define NFOC_WKI                       (*(volatile  int16* )(NFOC_BASE + (177*2)))     // RV:0000H Outer loop PI current loop KI
 #define NFOC_WMAX                      (*(volatile  int16* )(NFOC_BASE + (178*2)))     // RV:0000H Outer loop PI current loop upper limit
 #define NFOC_WMIN                      (*(volatile  int16* )(NFOC_BASE + (179*2)))     // RV:0000H Outer loop PI current loop lower limit
 #define NFOC_WEK                       (*(volatile  int16* )(NFOC_BASE + (180*2)))     // RV:0000H Outer loop PI current loop EK
 #define NFOC_WEK1                      (*(volatile  int16* )(NFOC_BASE + (181*2)))     // RV:0000H Outer loop PI current loop EK1
 #define NFOC_WUK                       (*(volatile  int32* )(NFOC_BASE + (182*2)))     // RV:0000H Outer loop PI current loop UK (32-bit)
 #define NFOC_WUKH                      (*(volatile  int16* )(NFOC_BASE + (183*2)))     // RV:0000H Outer loop PI current loop UK high 16-bit
 // #define NFOC_WEXC                      (*(volatile  int16* )(NFOC_BASE + (184*2)))  // RV:0000H outer loopPIcurrent loopUKoverflow value
 
 #define NFOC_FWKP                      (*(volatile  int16* )(NFOC_BASE + (192*2)))     // RV:0000H Field weakening PI KP
 #define NFOC_FWKI                      (*(volatile  int16* )(NFOC_BASE + (193*2)))     // RV:0000H Field weakening PI KI
 #define NFOC_FWMAX                     (*(volatile  int16* )(NFOC_BASE + (194*2)))     // RV:0000H Field weakening PI upper limit
 #define NFOC_FWMIN                     (*(volatile  int16* )(NFOC_BASE + (195*2)))     // RV:0000H Field weakening PI lower limit
 #define NFOC_FWEK                      (*(volatile  int16* )(NFOC_BASE + (196*2)))     // RV:0000H Field weakening PI EK
 #define NFOC_FWEK1                     (*(volatile  int16* )(NFOC_BASE + (197*2)))     // RV:0000H Field weakening PI EK1
 #define NFOC_FWUK                      (*(volatile  int32* )(NFOC_BASE + (198*2)))     // RV:0000H Field weakening PI UK (32-bit)
 #define NFOC_FWUKH                     (*(volatile  int16* )(NFOC_BASE + (199*2)))     // RV:0000H Field weakening PI UK high 16-bit
 #define NFOC_FWEXC                     (*(volatile  int16* )(NFOC_BASE + (200*2)))     // RV:0000H Field weakening PI UK overflow value
 #define NFOC_KUSF                      (*(volatile  int16* )(NFOC_BASE + (201*2)))     // RV:0000H US filter coefficient in field weakening calculation

     
 #define NFOC_OVP                       (*(volatile  int16* )(NFOC_BASE + (10*2)))      // RV:0000H Overvoltage threshold
 #define NFOC_OVPARR                    (*(volatile uint8*  )(NFOC_BASE + (11*2)))      // RV:00H   Overvoltage count target value (8-bit)
 #define NFOC_OVPCNT                    (*(volatile uint8*  )(NFOC_BASE + (11*2+1)))    // RV:00H   Overvoltage count value (8-bit)
 #define NFOC_UVP                       (*(volatile  int16* )(NFOC_BASE + (12*2)))      // RV:0000H Undervoltage threshold
 #define NFOC_UVPARR                    (*(volatile uint8*  )(NFOC_BASE + (13*2)))      // RV:00H   Undervoltage count target value (8-bit)
 #define NFOC_UVPCNT                    (*(volatile uint8*  )(NFOC_BASE + (13*2+1)))    // RV:00H   Undervoltage count value (8-bit)
 #define NFOC_SOCP                      (*(volatile  int16* )(NFOC_BASE + (14*2)))      // RV:0000H Software overcurrent threshold
 #define NFOC_SOCPARR                   (*(volatile uint8*  )(NFOC_BASE + (15*2)))      // RV:00H   Software overcurrent count target value (8-bit)
 #define NFOC_SOCPCNT                   (*(volatile uint8*  )(NFOC_BASE + (15*2+1)))    // RV:00H   Software overcurrent count value (8-bit)

 #define NFOC_LKSMIN                    (*(volatile  int16* )(NFOC_BASE + (16*2)))      // RV:0000H LOCK0 minimum stall speed
 #define NFOC_LKSMAX                    (*(volatile  int16* )(NFOC_BASE + (17*2)))      // RV:0000H LOCK1 maximum stall speed
 #define NFOC_LOCKK                     (*(volatile  int16* )(NFOC_BASE + (18*2)))      // RV:0000H LOCK2 speed/EMF multiple in Q8 format
 #define NFOC_LKARR                     (*(volatile uint16* )(NFOC_BASE + (20*2)))      // RV:0000H Stall count target value
 #define NFOC_LKCNT                     (*(volatile uint16* )(NFOC_BASE + (21*2)))      // RV:0000H Stall count value, shared by 3; increments by 1 only when all 3 conditions hold

 //Servo stall detection register, shared with original stall register
 #define NFOC_LKSTH						(*(volatile  int16* )(NFOC_BASE + (16*2)))      // RV:0000H Stall speed threshold, shared with NFOC_LKSMIN
 #define NFOC_LKITH                     (*(volatile  int16* )(NFOC_BASE + (17*2)))      // RV:0000H Stall current threshold, shared with NFOC_LKSMAX

 #define NFOC_NCURR                     (*(volatile  int16* )(NFOC_BASE + (22*2)))      // RV:0000H Phase loss detection current setting
 #define NFOC_PLK                       (*(volatile  int16* )(NFOC_BASE + (23*2)))      // RV:0000H Phase loss detection current multiplier coefficient

 #define NFOC_OVEL                      (*(volatile  int16* )(NFOC_BASE + (62*2)))      // RV:0000H Velocity error protection threshold
 #define NFOC_OVELARR                   (*(volatile uint8*  )(NFOC_BASE + (63*2)))      // RV:00H   Velocity error protection count target value (8-bit)
 #define NFOC_OVELCNT                   (*(volatile uint8*  )(NFOC_BASE + (63*2+1)))    // RV:00H   Velocity error protection count value (8-bit)

 #define NFOC_OSPD						(*(volatile  int16* )(NFOC_BASE + (64*2)))      // RV:0000H Overspeed protection threshold
 #define NFOC_OSPDARR                   (*(volatile uint8*  )(NFOC_BASE + (65*2)))      // RV:00H   Overspeed protection count target value (8-bit)
 #define NFOC_OSPDCNT                   (*(volatile uint8*  )(NFOC_BASE + (65*2+1)))    // RV:00H   Overspeed protection count value (8-bit)

 #define NFOC_PLTTH                     (*(volatile  int16* )(NFOC_BASE + (19*2)))      // RV:0000H New phase loss protection angle change threshold
 #define NFOC_PLTHE0                    (*(volatile  int16* )(NFOC_BASE + (22*2)))      // RV:0000H New phase loss protection previous angle
 #define NFOC_PLTHEM					(*(volatile  int16* )(NFOC_BASE + (23*2)))      // RV:0000H New phase loss protection angle zero-crossing count
 #define NFOC_PLRTH						(*(volatile  int16* )(NFOC_BASE + (66*2)))      // RV:0000H New phase loss protection current command threshold
 #define NFOC_PLITH                     (*(volatile  int16* )(NFOC_BASE + (67*2)))      // RV:0000H New phase loss protection phase current threshold
 #define NFOC_PLTHE1                    (*(volatile  int16* )(NFOC_BASE + (68*2)))      // RV:0000H New phase loss protection angle buffer (32-bit)
 
 
 #define NFOC_TS                        (*(volatile  int16* )(NFOC_BASE + (316*2)))     // RV:0000H Single-resistor phase shift / dual/triple resistor min sample pulse width [0,32767]
 #define NFOC_NTS                       (*(volatile  int16* )(NFOC_BASE + (317*2)))     // RV:0000H Triple-resistor pulse width mask / new single-resistor min pulse width [0,1023]
 #define NFOC_TDLY                      (*(volatile  int16* )(NFOC_BASE + (318*2)))     // RV:0000H Current sampling trigger timing
 #define NFOC_TDLYD                     (*(volatile  int16* )(NFOC_BASE + (319*2)))     // RV:0000H Single-resistor dynamic pre/post sampling timing
 #define NFOC_ARR                       (*(volatile uint16* )(NFOC_BASE + (320*2)))     // RV:0000H FOC carrier frequency
 #define NFOC_IDK                       (*(volatile  int16* )(NFOC_BASE + (322*2)))     // RV:0000H ID filter coefficient
 #define NFOC_IQK                       (*(volatile  int16* )(NFOC_BASE + (323*2)))     // RV:0000H IQ filter coefficient
 #define NFOC_OMEGAK                    (*(volatile  int16* )(NFOC_BASE + (324*2)))     // RV:0000H Omega 1st-stage filter coefficient
 #define NFOC_OMEK2                     (*(volatile  int16* )(NFOC_BASE + (325*2)))     // RV:0000H Omega 2nd-stage filter coefficient
 #define NFOC_OMEACC                    (*(volatile  int32* )(NFOC_BASE + (202*2)))     // RV:0000H OMEGA startup velocity increment
 #define NFOC_OMEEND                    (*(volatile  int32* )(NFOC_BASE + (204*2)))     // RV:0000H OMEGA startup END value
 #define NFOC_OMEENDH                   (*(volatile  int16* )(NFOC_BASE + (205*2)))     // RV:0000H OMEGA startup END value
 #define NFOC_OMEMIN                    (*(volatile  int16* )(NFOC_BASE + (206*2)))     // RV:0000H OMEGA startup transition value
 #define NFOC_FTCK                      (*(volatile  int16* )(NFOC_BASE + (207*2)))     // RV:0000H Feedback angle dynamic compensation coefficient
 #define NFOC_FBASE                     (*(volatile  int16* )(NFOC_BASE + (208*2)))     // RV:0000H Velocity reference
 #define NFOC_OMEMI2                    (*(volatile  int16* )(NFOC_BASE + (209*2)))     // RV:0000H Minimum velocity corresponding to KLPF
 #define NFOC_THECOM                    (*(volatile  int16* )(NFOC_BASE + (210*2)))     // RV:0000H Output angle static compensation angle
 #define NFOC_FTCOM                     (*(volatile  int16* )(NFOC_BASE + (211*2)))     // RV:0000H Feedback angle static compensation angle
 #define NFOC_EK1                       (*(volatile  int16* )(NFOC_BASE + (212*2)))     // RV:0000H FOC estimator parameter 1
 #define NFOC_EK2                       (*(volatile  int16* )(NFOC_BASE + (213*2)))     // RV:0000H FOC estimator parameter 2
 #define NFOC_EK3                       (*(volatile  int16* )(NFOC_BASE + (214*2)))     // RV:0000H FOC estimator parameter 3
 #define NFOC_EK4                       (*(volatile  int16* )(NFOC_BASE + (215*2)))     // RV:0000H FOC estimator parameter 4
 #define NFOC_KSLIDE                    (*(volatile  int16* )(NFOC_BASE + (216*2)))     // RV:0000H SMO coefficient
 #define NFOC_MAXERR                    (*(volatile  int16* )(NFOC_BASE + (217*2)))     // RV:0000H SMO limit
 #define NFOC_MERRRE                    (*(volatile  int16* )(NFOC_BASE + (218*2)))     // RV:0000H SMO limitreciprocal
 #define NFOC_TDTC                      (*(volatile  int16* )(NFOC_BASE + (219*2)))     // RV:0000H Dual/triple resistor dead-time compensation
 #define NFOC_IDREF                     (*(volatile  int16* )(NFOC_BASE + (220*2)))     // RV:0000H Given D-axis value
 #define NFOC_IQREF                     (*(volatile  int16* )(NFOC_BASE + (221*2)))     // RV:0000H Given Q-axis value
 #define NFOC_IAREF                     (*(volatile  int16* )(NFOC_BASE + (4*2)))       // RV:0000H U-phase current reference
 #define NFOC_IBREF                     (*(volatile  int16* )(NFOC_BASE + (5*2)))       // RV:0000H V-phase current reference
 #define NFOC_ICREF                     (*(volatile  int16* )(NFOC_BASE + (6*2)))       // RV:0000H W-phase current reference
 #define NFOC_ITREF                     (*(volatile  int16* )(NFOC_BASE + (7*2)))       // RV:0000H Bus current reference
 #define NFOC_UDC                       (*(volatile  int16* )(NFOC_BASE + (0*2)))       // RV:0000H Bus voltage sample value
 #define NFOC_UDCK                      (*(volatile  int16* )(NFOC_BASE + (1*2)))       // RV:0000H Bus voltage sample filter coefficient
 #define NFOC_UDCFLT                    (*(volatile  int32* )(NFOC_BASE + (2*2)))       // RV:0000H Bus voltage filtered value (32-bit)
 #define NFOC_UDCFLTH                   (*(volatile  int16* )(NFOC_BASE + (3*2)))       // RV:0000H Bus voltage filtered value high 16-bit
 #define NFOC_UQCPS                     (*(volatile  int16* )(NFOC_BASE + (231*2)))     // RV:0000H D-axis voltage compensation value
 #define NFOC_UDCPS                     (*(volatile  int16* )(NFOC_BASE + (230*2)))     // RV:0000H Q-axis voltage compensation value
 #define NFOC_WREF                      (*(volatile  int16* )(NFOC_BASE + (232*2)))     // RV:0000H Outer loop reference value [0~32767]
 #define NFOC_WFDB                      (*(volatile  int16* )(NFOC_BASE + (233*2)))     // RV:0000H Outer loop feedback value
 #define NFOC_ITK                       (*(volatile  int16* )(NFOC_BASE + (234*2)))     // RV:0000H ITRIP filter coefficient
 #define NFOC_POWK                      (*(volatile  int16* )(NFOC_BASE + (235*2)))     // RV:0000H POWER filter coefficient (two 8-bit) POWER = (ITRIP*K1)*(UDC*K2)
 #define NFOC_FGBASE                    (*(volatile  int16* )(NFOC_BASE + (236*2)))     // RV:0000H FGcalculationVelocity reference
 
 #define NFOC_UALCPS                    (*(volatile  int16* )(NFOC_BASE + (238*2)))     // RV:0000H UALPHA voltage compensation value
 #define NFOC_UBECPS                    (*(volatile  int16* )(NFOC_BASE + (239*2)))     // RV:0000H UBETA voltage compensation value
 
 #define NFOC_RATAR                     (*(volatile  int16* )(NFOC_BASE + (242*2)))     // RV:0000H User-filled ramp target value
 #define NFOC_RAOUT                     (*(volatile  int16* )(NFOC_BASE + (243*2)))     // RV:0000H Ramp output value after ramping
 #define NFOC_RAINC                     (*(volatile  int16* )(NFOC_BASE + (244*2)))     // RV:0000H Upward step increment value
 #define NFOC_RADEC                     (*(volatile  int16* )(NFOC_BASE + (245*2)))     // RV:0000H Downward step decrement value
 #define NFOC_LK1                       (*(volatile  int16* )(NFOC_BASE + (246*2)))     // RV:0000H Low-speed observer coefficient
 #define NFOC_LK2                       (*(volatile  int16* )(NFOC_BASE + (247*2)))     // RV:0000H Low-speed observer coefficient
 #define NFOC_LK3                       (*(volatile  int16* )(NFOC_BASE + (248*2)))     // RV:0000H Low-speed observer coefficient
 #define NFOC_LK4                       (*(volatile  int16* )(NFOC_BASE + (249*2)))     // RV:0000H Low-speed observer coefficient
 #define NFOC_LK5                       (*(volatile  int16* )(NFOC_BASE + (250*2)))     // RV:0000H Low-speed observer coefficient
 #define NFOC_LK6                       (*(volatile  int16* )(NFOC_BASE + (251*2)))     // RV:0000H Low-speed observer coefficient
 #define NFOC_LED                       (*(volatile  int16* )(NFOC_BASE + (252*2)))     // RV:0000H Low-speed observer coefficient
 #define NFOC_LEQ                       (*(volatile  int16* )(NFOC_BASE + (253*2)))     // RV:0000H Low-speed observer coefficient
 #define NFOC_LOME                      (*(volatile  int32* )(NFOC_BASE + (254*2)))     // RV:0000H Low-speed observer velocity
 #define NFOC_LOMEH                     (*(volatile  int16* )(NFOC_BASE + (255*2)))     // RV:0000H Low-speed observer velocity
 #define NFOC_XALPHA                    (*(volatile  int32* )(NFOC_BASE + (276*2)))     // RV:0000H Flux observer calculation intermediate value      /* factory */
 #define NFOC_XALPHAH                   (*(volatile  int16* )(NFOC_BASE + (277*2)))     // RV:0000H Flux observer calculation intermediate value      /* factory */
 #define NFOC_XBETA                     (*(volatile  int32* )(NFOC_BASE + (278*2)))     // RV:0000H Flux observer calculation intermediate value      /* factory */
 #define NFOC_XBETAH                    (*(volatile  int16* )(NFOC_BASE + (279*2)))     // RV:0000H Flux observer calculation intermediate value      /* factory */
 #define NFOC_ETALPHA                   (*(volatile  int16* )(NFOC_BASE + (298*2)))     // RV:0000H Flux observer calculation intermediate value      /* factory */
 #define NFOC_ETBETA                    (*(volatile  int16* )(NFOC_BASE + (299*2)))     // RV:0000H Flux observer calculation intermediate value      /* factory */
 #define NFOC_UABT                      (*(volatile  int16* )(NFOC_BASE + (280*2)))     // RV:0000H Flux observer calculation intermediate value      /* factory */
 #define NFOC_HEK0                      (*(volatile  int16* )(NFOC_BASE + (282*2)))     // RV:0000H Flux observer calculation intermediate value
 #define NFOC_PSI                       (*(volatile  int16* )(NFOC_BASE + (283*2)))     // RV:0000H Flux observer calculation intermediate value
 #define NFOC_UIK0                      (*(volatile  int16* )(NFOC_BASE + (284*2)))     // RV:0000H UQ compensation harmonic multiplier coefficient
 #define NFOC_UIK1                      (*(volatile  int16* )(NFOC_BASE + (285*2)))     // RV:0000H UQ compensation harmonic multiplier coefficient
 #define NFOC_UIK2                      (*(volatile  int16* )(NFOC_BASE + (286*2)))     // RV:0000H UQ compensation harmonic multiplier coefficient
 #define NFOC_UIK3                      (*(volatile  int16* )(NFOC_BASE + (287*2)))     // RV:0000H UQ compensation harmonic multiplier coefficient
 #define NFOC_UITC0                     (*(volatile  int16* )(NFOC_BASE + (288*2)))     // RV:0000H UQ compensation angular phase shift
 #define NFOC_UIUS0                     (*(volatile  int16* )(NFOC_BASE + (289*2)))     // RV:0000H UQ compensation magnitude
 #define NFOC_UITC1                     (*(volatile  int16* )(NFOC_BASE + (290*2)))     // RV:0000H UQ compensation angular phase shift
 #define NFOC_UIUS1                     (*(volatile  int16* )(NFOC_BASE + (291*2)))     // RV:0000H UQ compensation magnitude
 #define NFOC_UITC2                     (*(volatile  int16* )(NFOC_BASE + (292*2)))     // RV:0000H UQ compensation angular phase shift
 #define NFOC_UIUS2                     (*(volatile  int16* )(NFOC_BASE + (293*2)))     // RV:0000H UQ compensation magnitude
 #define NFOC_UITC3                     (*(volatile  int16* )(NFOC_BASE + (294*2)))     // RV:0000H UQ compensation angular phase shift
 #define NFOC_UIUS3                     (*(volatile  int16* )(NFOC_BASE + (295*2)))     // RV:0000H UQ compensation magnitude
 #define NFOC_TRG1                      (*(volatile  int16* )(NFOC_BASE + (296*2)))     // RV:0000H I1 sampling point DR value
 #define NFOC_TRG2                      (*(volatile  int16* )(NFOC_BASE + (297*2)))     // RV:0000H I2 sampling point DR value
    
 #define NFOC_OTHETA                    (*(volatile  int32* )(NFOC_BASE + (300*2)))     // RV:0000H Estimator estimated angle (32-bit)
 #define NFOC_OTHETAH                   (*(volatile  int16* )(NFOC_BASE + (301*2)))     // RV:0000H Estimator angle high 16-bit
  
 #define NFOC_USK                       (*(volatile  int16* )(NFOC_BASE + (302*2)))     // RV:0000H Phase voltage sample coefficient
 #define NFOC_UA                        (*(volatile  int16* )(NFOC_BASE + (303*2)))     // RV:0000H A-phase voltage sample value
 #define NFOC_UB                        (*(volatile  int16* )(NFOC_BASE + (304*2)))     // RV:0000H B-phase voltage sample value
 #define NFOC_UC                        (*(volatile  int16* )(NFOC_BASE + (305*2)))     // RV:0000H C-phase voltage sample value
 #define NFOC_USAL1                     (*(volatile  int16* )(NFOC_BASE + (306*2)))     // RV:0000H USALPHA value calculated from UA, UB, UC
 #define NFOC_USBE1                     (*(volatile  int16* )(NFOC_BASE + (307*2)))     // RV:0000H USBETA value calculated from UA, UB, UC
  
 #define NFOC_DELOTHE                   (*(volatile  int32* )(NFOC_BASE + (326*2)))     // RV:0000H Estimator estimated angle (32-bit)
 #define NFOC_DELOTHEH                  (*(volatile  int16* )(NFOC_BASE + (327*2)))     // RV:0000H Estimator estimated angle
 #define NFOC_DELETHE                   (*(volatile  int32* )(NFOC_BASE + (328*2)))     // RV:0000H Estimator estimated angle (32-bit)
 #define NFOC_DELETHEH                  (*(volatile  int16* )(NFOC_BASE + (329*2)))     // RV:0000H Estimator estimated angle
 #define NFOC_IG0                       (*(volatile  int16* )(NFOC_BASE + (310*2)))     // RV:0000H HF injection calculation intermediate value      /* factory */
 #define NFOC_IF0                       (*(volatile  int16* )(NFOC_BASE + (311*2)))     // RV:0000H HF injection calculation intermediate value      /* factory */
 #define NFOC_HUCPS                     (*(volatile  int16* )(NFOC_BASE + (312*2)))     // RV:0000H HF injection calculation intermediate value      /* factory */
 #define NFOC_HCTHE                     (*(volatile  int16* )(NFOC_BASE + (313*2)))     // RV:0000H HF injection calculation intermediate value      /* factory */
 #define NFOC_FWREF                     (*(volatile  int16* )(NFOC_BASE + (314*2)))     // RV:0000H Field weakeningPIgiven value
 
 #define NFOC_UDCD                      (*(volatile  int16* )(NFOC_BASE + (330*2)))     // RV:0000H D-axis UDC value
 #define NFOC_UDCQ                      (*(volatile  int16* )(NFOC_BASE + (331*2)))     // RV:0000H Q-axis UDC value
 
 #define NFOC_IQMAX                     (*(volatile uint16* )(NFOC_BASE + (332*2)))     // RV:0000H IQREF maximum value
 #define NFOC_IQMIN                     (*(volatile uint16* )(NFOC_BASE + (333*2)))     // RV:0000H IQREF minimum value
 
 #define NFOC_WUCPS                     (*(volatile  int16* )(NFOC_BASE + (414*2)))     // RV:0000H Outer loop compensation value
 #define NFOC_WUFIN                     (*(volatile  int16* )(NFOC_BASE + (415*2)))     // RV:0000H Outer loop final value
 #define NFOC_FWIDR                     (*(volatile  int16* )(NFOC_BASE + (446*2)))     // RV:0000H Field weakening output in FW MOD1
 #define NFOC_CSAM                      (*(volatile  int16* )(NFOC_BASE + (455*2)))     // RV:0000H Used to load into FOC_CSAM_MD
 #define NFOC_IDRLIM                    (*(volatile  int16* )(NFOC_BASE + (475*2)))     // RV:0000H IDREF limit value in field weakening calculation
 #define NFOC_USFLT                     (*(volatile  int32* )(NFOC_BASE + (504*2)))     // RV:0000H NFOCx_US filtered value
 
 #define NFOC_F1LB0                     (*(volatile uint16* )(NFOC_BASE + (334*2)))     // RV:0000H IQREF filter parameter
 #define NFOC_F1HB0                     (*(volatile uint16* )(NFOC_BASE + (335*2)))     // RV:0000H IQREF filter parameter
 #define NFOC_F1LB1                     (*(volatile uint16* )(NFOC_BASE + (336*2)))     // RV:0000H IQREF filter parameter
 #define NFOC_F1LB2                     (*(volatile uint16* )(NFOC_BASE + (337*2)))     // RV:0000H IQREF filter parameter
 #define NFOC_F1LA1                     (*(volatile uint16* )(NFOC_BASE + (338*2)))     // RV:0000H IQREF filter parameter
 #define NFOC_F1LA2                     (*(volatile uint16* )(NFOC_BASE + (339*2)))     // RV:0000H IQREF filter parameter
 #define NFOC_F1HB1                     (*(volatile uint16* )(NFOC_BASE + (340*2)))     // RV:0000H IQREF filter parameter
 #define NFOC_F1HB2                     (*(volatile uint16* )(NFOC_BASE + (341*2)))     // RV:0000H IQREF filter parameter
 #define NFOC_F1HA1                     (*(volatile uint16* )(NFOC_BASE + (342*2)))     // RV:0000H IQREF filter parameter
 #define NFOC_F1HA2                     (*(volatile uint16* )(NFOC_BASE + (343*2)))     // RV:0000H IQREF filter parameter
 #define NFOC_F1X0                      (*(volatile uint16* )(NFOC_BASE + (344*2)))     // RV:0000H IQREF filter parameter
 #define NFOC_F1X1                      (*(volatile uint16* )(NFOC_BASE + (346*2)))     // RV:0000H IQREF filter parameter
 #define NFOC_F1X2                      (*(volatile uint16* )(NFOC_BASE + (347*2)))     // RV:0000H IQREF filter parameter
 #define NFOC_F1Y1                      (*(volatile uint16* )(NFOC_BASE + (348*2)))     // RV:0000H IQREF filter parameter
 #define NFOC_F1Y2                      (*(volatile uint16* )(NFOC_BASE + (349*2)))     // RV:0000H IQREF filter parameter
 #define NFOC_F1Z1                      (*(volatile uint16* )(NFOC_BASE + (350*2)))     // RV:0000H IQREF filter parameter
 #define NFOC_F1Z2                      (*(volatile uint16* )(NFOC_BASE + (351*2)))     // RV:0000H IQREF filter parameter
 #define NFOC_F1Y                       (*(volatile uint32* )(NFOC_BASE + (352*2)))     // RV:0000H IQREF filter parameter
 #define NFOC_F1YH                      (*(volatile uint16* )(NFOC_BASE + (353*2)))     // RV:0000H IQREF filter parameter
 #define NFOC_F1U1                      (*(volatile uint16* )(NFOC_BASE + (416*2)))     // RV:0000H IQREF filter parameter
 #define NFOC_F1U2                      (*(volatile uint16* )(NFOC_BASE + (417*2)))     // RV:0000H IQREF filter parameter
 #define NFOC_F1YG                      (*(volatile uint32* )(NFOC_BASE + (424*2)))     // RV:0000H IQREF filter parameter      /* factory */
 #define NFOC_F1YD                      (*(volatile uint32* )(NFOC_BASE + (426*2)))     // RV:0000H IQREF filter parameter      /* factory */
 
 #define NFOC_F2LB0                     (*(volatile uint16* )(NFOC_BASE + (354*2)))     // RV:0000H IQREF filter parameter
 #define NFOC_F2HB0                     (*(volatile uint16* )(NFOC_BASE + (355*2)))     // RV:0000H IQREF filter parameter
 #define NFOC_F2LB1                     (*(volatile uint16* )(NFOC_BASE + (356*2)))     // RV:0000H IQREF filter parameter
 #define NFOC_F2LB2                     (*(volatile uint16* )(NFOC_BASE + (357*2)))     // RV:0000H IQREF filter parameter
 #define NFOC_F2LA1                     (*(volatile uint16* )(NFOC_BASE + (358*2)))     // RV:0000H IQREF filter parameter
 #define NFOC_F2LA2                     (*(volatile uint16* )(NFOC_BASE + (359*2)))     // RV:0000H IQREF filter parameter
 #define NFOC_F2HB1                     (*(volatile uint16* )(NFOC_BASE + (360*2)))     // RV:0000H IQREF filter parameter
 #define NFOC_F2HB2                     (*(volatile uint16* )(NFOC_BASE + (361*2)))     // RV:0000H IQREF filter parameter
 #define NFOC_F2HA1                     (*(volatile uint16* )(NFOC_BASE + (362*2)))     // RV:0000H IQREF filter parameter
 #define NFOC_F2HA2                     (*(volatile uint16* )(NFOC_BASE + (363*2)))     // RV:0000H IQREF filter parameter
 #define NFOC_F2X0                      (*(volatile uint16* )(NFOC_BASE + (364*2)))     // RV:0000H IQREF filter parameter
 #define NFOC_F2X1                      (*(volatile uint16* )(NFOC_BASE + (366*2)))     // RV:0000H IQREF filter parameter
 #define NFOC_F2X2                      (*(volatile uint16* )(NFOC_BASE + (367*2)))     // RV:0000H IQREF filter parameter
 #define NFOC_F2Y1                      (*(volatile uint16* )(NFOC_BASE + (368*2)))     // RV:0000H IQREF filter parameter
 #define NFOC_F2Y2                      (*(volatile uint16* )(NFOC_BASE + (369*2)))     // RV:0000H IQREF filter parameter
 #define NFOC_F2Z1                      (*(volatile uint16* )(NFOC_BASE + (370*2)))     // RV:0000H IQREF filter parameter
 #define NFOC_F2Z2                      (*(volatile uint16* )(NFOC_BASE + (371*2)))     // RV:0000H IQREF filter parameter
 #define NFOC_F2Y                       (*(volatile uint32* )(NFOC_BASE + (372*2)))     // RV:0000H IQREF filter parameter
 #define NFOC_F2YH                      (*(volatile uint16* )(NFOC_BASE + (373*2)))     // RV:0000H IQREF filter parameter
 #define NFOC_F2U1                      (*(volatile uint16* )(NFOC_BASE + (418*2)))     // RV:0000H IQREF filter parameter
 #define NFOC_F2U2                      (*(volatile uint16* )(NFOC_BASE + (419*2)))     // RV:0000H IQREF filter parameter
 #define NFOC_F2YG                      (*(volatile uint32* )(NFOC_BASE + (428*2)))     // RV:0000H IQREF filter parameter      /* factory */
 #define NFOC_F2YD                      (*(volatile uint32* )(NFOC_BASE + (430*2)))     // RV:0000H IQREF filter parameter      /* factory */
 
 #define NFOC_F3LB0                     (*(volatile uint16* )(NFOC_BASE + (374*2)))     // RV:0000H IQREF filter parameter
 #define NFOC_F3HB0                     (*(volatile uint16* )(NFOC_BASE + (375*2)))     // RV:0000H IQREF filter parameter
 #define NFOC_F3LB1                     (*(volatile uint16* )(NFOC_BASE + (376*2)))     // RV:0000H IQREF filter parameter
 #define NFOC_F3LB2                     (*(volatile uint16* )(NFOC_BASE + (377*2)))     // RV:0000H IQREF filter parameter
 #define NFOC_F3LA1                     (*(volatile uint16* )(NFOC_BASE + (378*2)))     // RV:0000H IQREF filter parameter
 #define NFOC_F3LA2                     (*(volatile uint16* )(NFOC_BASE + (379*2)))     // RV:0000H IQREF filter parameter
 #define NFOC_F3HB1                     (*(volatile uint16* )(NFOC_BASE + (380*2)))     // RV:0000H IQREF filter parameter
 #define NFOC_F3HB2                     (*(volatile uint16* )(NFOC_BASE + (381*2)))     // RV:0000H IQREF filter parameter
 #define NFOC_F3HA1                     (*(volatile uint16* )(NFOC_BASE + (382*2)))     // RV:0000H IQREF filter parameter
 #define NFOC_F3HA2                     (*(volatile uint16* )(NFOC_BASE + (383*2)))     // RV:0000H IQREF filter parameter
 #define NFOC_F3X0                      (*(volatile uint16* )(NFOC_BASE + (384*2)))     // RV:0000H IQREF filter parameter
 #define NFOC_F3X1                      (*(volatile uint16* )(NFOC_BASE + (386*2)))     // RV:0000H IQREF filter parameter
 #define NFOC_F3X2                      (*(volatile uint16* )(NFOC_BASE + (387*2)))     // RV:0000H IQREF filter parameter
 #define NFOC_F3Y1                      (*(volatile uint16* )(NFOC_BASE + (388*2)))     // RV:0000H IQREF filter parameter
 #define NFOC_F3Y2                      (*(volatile uint16* )(NFOC_BASE + (389*2)))     // RV:0000H IQREF filter parameter
 #define NFOC_F3Z1                      (*(volatile uint16* )(NFOC_BASE + (390*2)))     // RV:0000H IQREF filter parameter
 #define NFOC_F3Z2                      (*(volatile uint16* )(NFOC_BASE + (391*2)))     // RV:0000H IQREF filter parameter
 #define NFOC_F3Y                       (*(volatile uint32* )(NFOC_BASE + (392*2)))     // RV:0000H IQREF filter parameter
 #define NFOC_F3YH                      (*(volatile uint16* )(NFOC_BASE + (393*2)))     // RV:0000H IQREF filter parameter
 #define NFOC_F3U1                      (*(volatile uint16* )(NFOC_BASE + (420*2)))     // RV:0000H IQREF filter parameter
 #define NFOC_F3U2                      (*(volatile uint16* )(NFOC_BASE + (421*2)))     // RV:0000H IQREF filter parameter
 #define NFOC_F3YG                      (*(volatile uint32* )(NFOC_BASE + (432*2)))     // RV:0000H IQREF filter parameter      /* factory */
 #define NFOC_F3YD                      (*(volatile uint32* )(NFOC_BASE + (434*2)))     // RV:0000H IQREF filter parameter      /* factory */
 
 #define NFOC_F4LB0                     (*(volatile uint16* )(NFOC_BASE + (394*2)))     // RV:0000H IQREF filter parameter
 #define NFOC_F4HB0                     (*(volatile uint16* )(NFOC_BASE + (395*2)))     // RV:0000H IQREF filter parameter
 #define NFOC_F4LB1                     (*(volatile uint16* )(NFOC_BASE + (396*2)))     // RV:0000H IQREF filter parameter
 #define NFOC_F4LB2                     (*(volatile uint16* )(NFOC_BASE + (397*2)))     // RV:0000H IQREF filter parameter
 #define NFOC_F4LA1                     (*(volatile uint16* )(NFOC_BASE + (398*2)))     // RV:0000H IQREF filter parameter
 #define NFOC_F4LA2                     (*(volatile uint16* )(NFOC_BASE + (399*2)))     // RV:0000H IQREF filter parameter
 #define NFOC_F4HB1                     (*(volatile uint16* )(NFOC_BASE + (400*2)))     // RV:0000H IQREF filter parameter
 #define NFOC_F4HB2                     (*(volatile uint16* )(NFOC_BASE + (401*2)))     // RV:0000H IQREF filter parameter
 #define NFOC_F4HA1                     (*(volatile uint16* )(NFOC_BASE + (402*2)))     // RV:0000H IQREF filter parameter
 #define NFOC_F4HA2                     (*(volatile uint16* )(NFOC_BASE + (403*2)))     // RV:0000H IQREF filter parameter
 #define NFOC_F4X0                      (*(volatile uint16* )(NFOC_BASE + (404*2)))     // RV:0000H IQREF filter parameter
 #define NFOC_F4X1                      (*(volatile uint16* )(NFOC_BASE + (406*2)))     // RV:0000H IQREF filter parameter
 #define NFOC_F4X2                      (*(volatile uint16* )(NFOC_BASE + (407*2)))     // RV:0000H IQREF filter parameter
 #define NFOC_F4Y1                      (*(volatile uint16* )(NFOC_BASE + (408*2)))     // RV:0000H IQREF filter parameter
 #define NFOC_F4Y2                      (*(volatile uint16* )(NFOC_BASE + (409*2)))     // RV:0000H IQREF filter parameter
 #define NFOC_F4Z1                      (*(volatile uint16* )(NFOC_BASE + (410*2)))     // RV:0000H IQREF filter parameter
 #define NFOC_F4Z2                      (*(volatile uint16* )(NFOC_BASE + (411*2)))     // RV:0000H IQREF filter parameter
 #define NFOC_F4Y                       (*(volatile uint32* )(NFOC_BASE + (412*2)))     // RV:0000H IQREF filter parameter
 #define NFOC_F4YH                      (*(volatile uint16* )(NFOC_BASE + (413*2)))     // RV:0000H IQREF filter parameter
 #define NFOC_F4U1                      (*(volatile uint16* )(NFOC_BASE + (422*2)))     // RV:0000H IQREF filter parameter
 #define NFOC_F4U2                      (*(volatile uint16* )(NFOC_BASE + (423*2)))     // RV:0000H IQREF filter parameter
 #define NFOC_F4YG                      (*(volatile uint32* )(NFOC_BASE + (436*2)))     // RV:0000H IQREF filter parameter      /* factory */
 #define NFOC_F4YD                      (*(volatile uint32* )(NFOC_BASE + (438*2)))     // RV:0000H IQREF filter parameter      /* factory */

 #define NFOC_FOUT                      (*(volatile  int16* )(NFOC_BASE + (472*2)))     // RV:0000H 4-stage filter output

 #define NFOC_F1LB0SH                   (*(volatile uint16* )(NFOC_BASE + (476*2)))     // RV:0000H IQREF filter parametershadow register
 #define NFOC_F1HB0SH					(*(volatile uint16* )(NFOC_BASE + (477*2)))     // RV:0000H IQREF filter parametershadow register
 #define NFOC_F1LB1SH					(*(volatile uint16* )(NFOC_BASE + (478*2)))     // RV:0000H IQREF filter parametershadow register
 #define NFOC_F1LB2SH                   (*(volatile uint16* )(NFOC_BASE + (479*2)))     // RV:0000H IQREF filter parametershadow register
 #define NFOC_F1LA1SH                   (*(volatile uint16* )(NFOC_BASE + (480*2)))     // RV:0000H IQREF filter parametershadow register
 #define NFOC_F1LA2SH                   (*(volatile uint16* )(NFOC_BASE + (481*2)))     // RV:0000H IQREF filter parametershadow register
 #define NFOC_F1HB1SH                   (*(volatile uint16* )(NFOC_BASE + (482*2)))     // RV:0000H IQREF filter parametershadow register
 #define NFOC_F1HB2SH                   (*(volatile uint16* )(NFOC_BASE + (483*2)))     // RV:0000H IQREF filter parametershadow register
 #define NFOC_F1HA1SH                   (*(volatile uint16* )(NFOC_BASE + (484*2)))     // RV:0000H IQREF filter parametershadow register
 #define NFOC_F1HA2SH                   (*(volatile uint16* )(NFOC_BASE + (485*2)))     // RV:0000H IQREF filter parametershadow register
 
 #define NFOC_XI0                       (*(volatile  int16* )(NFOC_BASE + (24*2)))      // RV:0000H CORDIC0 SIN/COS X-axis input
 #define NFOC_YI0                       (*(volatile  int16* )(NFOC_BASE + (25*2)))      // RV:0000H CORDIC0 SIN/COS Y-axis input
 #define NFOC_THETA0                    (*(volatile  int16* )(NFOC_BASE + (27*2)))      // RV:0000H CORDIC0 SIN/COS angle input
 #define NFOC_XO0                       (*(volatile  int16* )(NFOC_BASE + (28*2)))      // RV:0000H CORDIC0 SIN/COS X-axis output
 #define NFOC_YO0                       (*(volatile  int16* )(NFOC_BASE + (29*2)))      // RV:0000H CORDIC0 SIN/COS Y-axis output
 #define NFOC_XI1                       (*(volatile  int16* )(NFOC_BASE + (30*2)))      // RV:0000H CORDIC1 SIN/COS X-axis input
 #define NFOC_YI1                       (*(volatile  int16* )(NFOC_BASE + (31*2)))      // RV:0000H CORDIC1 SIN/COS Y-axis input
 #define NFOC_THETA1                    (*(volatile  int16* )(NFOC_BASE + (33*2)))      // RV:0000H CORDIC1 SIN/COS angle input
 #define NFOC_XO1                       (*(volatile  int16* )(NFOC_BASE + (34*2)))      // RV:0000H CORDIC1 SIN/COS X-axis output
 #define NFOC_YO1                       (*(volatile  int16* )(NFOC_BASE + (35*2)))      // RV:0000H CORDIC1 SIN/COS Y-axis output
 #define NFOC_XI2                       (*(volatile  int16* )(NFOC_BASE + (36*2)))      // RV:0000H CORDIC2 ATAN X-axis input
 #define NFOC_YI2                       (*(volatile  int16* )(NFOC_BASE + (37*2)))      // RV:0000H CORDIC2 ATAN Y-axis input
 #define NFOC_US2                       (*(volatile  int16* )(NFOC_BASE + (38*2)))      // RV:0000H CORDIC2 ATAN magnitude output
 #define NFOC_THETA2                    (*(volatile  int16* )(NFOC_BASE + (39*2)))      // RV:0000H CORDIC2 ATAN angle output
 #define NFOC_XI3                       (*(volatile  int16* )(NFOC_BASE + (40*2)))      // RV:0000H CORDIC3 ATAN X-axis input
 #define NFOC_YI3                       (*(volatile  int16* )(NFOC_BASE + (41*2)))      // RV:0000H CORDIC3 ATAN Y-axis input
 #define NFOC_US3                       (*(volatile  int16* )(NFOC_BASE + (42*2)))      // RV:0000H CORDIC3 ATAN magnitude output
 #define NFOC_THETA3                    (*(volatile  int16* )(NFOC_BASE + (43*2)))      // RV:0000H CORDIC3 ATAN angle output

 //New servo M/MT method functionality (DRV_FCR4) and FOC registers:
 #define NFOC_MQEP                      (*(volatile  int16* )(NFOC_BASE + (44*2)))     // RV:0000H MMT calculated QEP pulse count
 #define NFOC_MQEP1                     (*(volatile  int16* )(NFOC_BASE + (45*2)))     // RV:0000H MMT calculated previous QEP pulse count
 #define NFOC_MBASE                     (*(volatile  int16* )(NFOC_BASE + (46*2)))     // RV:0000H MMT calculated velocity conversion coefficient
 #define NFOC_MSHFT                     (*(volatile  int16* )(NFOC_BASE + (47*2)))     // RV:0000H MMT calculated velocity shift value (0~16)
 #define NFOC_MDEL                      (*(volatile  int16* )(NFOC_BASE + (48*2)))     // RV:0000H MMT calculated pulse count increment

 #define NFOC_MDEL1                     (*(volatile  int16* )(NFOC_BASE + (49*2)))     // RV:0000H MMT calculated previous pulse count increment
 #define NFOC_MBLK                      (*(volatile  int16* )(NFOC_BASE + (50*2)))     // RV:0000H MMT calculated blank period count
 #define NFOC_MBLK1                     (*(volatile  int16* )(NFOC_BASE + (51*2)))     // RV:0000H MMT calculated previous blank period count
 #define NFOC_MREM                      (*(volatile  int16* )(NFOC_BASE + (52*2)))     // RV:0000H MMT calculated clock remainder
 #define NFOC_MREM1                     (*(volatile  int16* )(NFOC_BASE + (53*2)))     // RV:0000H MMT calculated previous clock remainder
 #define NFOC_MARR                      (*(volatile  int16* )(NFOC_BASE + (54*2)))     // RV:0000H MMT calculated single-period clock count
 #define NFOC_MCOE                      (*(volatile  int16* )(NFOC_BASE + (55*2)))     // RV:0000H MMT calculation intermediate value
 #define NFOC_MPERD                     (*(volatile  int32* )(NFOC_BASE + (56*2)))     // RV:0000H MMT calculation intermediate value (32bit)
 #define NFOC_MPERD1                    (*(volatile  int32* )(NFOC_BASE + (58*2)))     // RV:0000H MMT calculation intermediate value (32bit)
 #define NFOC_MOME                      (*(volatile  int16* )(NFOC_BASE + (60*2)))     // RV:0000H MMT calculated velocity

 #define NFOC_UDK                       (*(volatile  int16* )(NFOC_BASE + (440*2)))     // RV:0000H UD filter coefficient
 #define NFOC_UQK                       (*(volatile  int16* )(NFOC_BASE + (441*2)))     // RV:0000H UQ filter coefficient
 #define NFOC_UDFLT                     (*(volatile  int32* )(NFOC_BASE + (442*2)))     // RV:0000H UD filter output (32-bit)
 #define NFOC_UQFLT                     (*(volatile  int32* )(NFOC_BASE + (444*2)))     // RV:0000H UQ filter output (32-bit)
 #define NFOC_UQFLTH                    (*(volatile  int16* )(NFOC_BASE + (445*2)))     // RV:0000H UQ filtered value high 16-bit

 #define NFOC_OSCNT                     (*(volatile  int16* )(NFOC_BASE + (447*2)))     // RV:0000H OFFSET calibration count value
 #define NFOC_OSSUM                     (*(volatile  int32* )(NFOC_BASE + (448*2)))     // RV:0000H OFFSET calibration sum

 #define NFOC_FFLT						(*(volatile  int16* )(NFOC_BASE + (472*2)))     // RV:0000H 4-stage filter output
 #define NFOC_FCPS                      (*(volatile  int16* )(NFOC_BASE + (473*2)))     // RV:0000H 4-stage filter outputcompensation value
 #define NFOC_IQRORG                    (*(volatile  int16* )(NFOC_BASE + (474*2)))     // RV:0000H 4-stage filter output after compensation and limiting

 
 #define NFOC2_BASE                     0x30010000
 #define NFOC2_I1                       (*(volatile  int16* )(NFOC2_BASE + ( 222*2)))   // RV:0000H 1st sample ADC value      /* factory */
 #define NFOC2_I2                       (*(volatile  int16* )(NFOC2_BASE + ( 223*2)))   // RV:0000H 2nd sample ADC value      /* factory */
 #define NFOC2_IA                       (*(volatile  int16* )(NFOC2_BASE + ( 224*2)))   // RV:0000H Calculated IA
 #define NFOC2_IB                       (*(volatile  int16* )(NFOC2_BASE + ( 225*2)))   // RV:0000H Calculated IB
 #define NFOC2_IC                       (*(volatile  int16* )(NFOC2_BASE + ( 226*2)))   // RV:0000H Calculated IC
 #define NFOC2_ICMAX                    (*(volatile  int16* )(NFOC2_BASE + ( 227*2)))   // RV:0000H IC max value
 #define NFOC2_IAMAX                    (*(volatile  int16* )(NFOC2_BASE + ( 228*2)))   // RV:0000H IA max value
 #define NFOC2_IBMAX                    (*(volatile  int16* )(NFOC2_BASE + ( 229*2)))   // RV:0000H IB max value
 #define NFOC2_IALPHA                   (*(volatile  int16* )(NFOC2_BASE + ( 154*2)))   // RV:0000H IALPHA after Clarke transform
 #define NFOC2_IBETA                    (*(volatile  int16* )(NFOC2_BASE + ( 155*2)))   // RV:0000H IBETA after Clarke transform
 #define NFOC2_ID                       (*(volatile  int16* )(NFOC2_BASE + ( 156*2)))   // RV:0000H ID after Park transform
 #define NFOC2_IQ                       (*(volatile  int16* )(NFOC2_BASE + ( 157*2)))   // RV:0000H IQ after Park transform
 #define NFOC2_IDFLT                    (*(volatile  int32* )(NFOC2_BASE + ( 158*2)))   // RV:0000H ID filtered value (32-bit)
 #define NFOC2_IDFLTH                   (*(volatile  int16* )(NFOC2_BASE + ( 159*2)))   // RV:0000H ID filtered value high 16-bit
 #define NFOC2_IQFLT                    (*(volatile  int32* )(NFOC2_BASE + ( 170*2)))   // RV:0000H IQ filtered value (32-bit)
 #define NFOC2_IQFLTH                   (*(volatile  int16* )(NFOC2_BASE + ( 171*2)))   // RV:0000H IQ filtered value high 16-bit
 #define NFOC2_THETA                    (*(volatile  int32* )(NFOC2_BASE + ( 172*2)))   // RV:0000H Angle value (32-bit)
 #define NFOC2_THETAL                   (*(volatile  int16* )(NFOC2_BASE + ( 172*2)))   // RV:0000H Angle value low 16-bit
 #define NFOC2_THETAH                   (*(volatile  int16* )(NFOC2_BASE + ( 173*2)))   // RV:0000H Angle value high 16-bit
 #define NFOC2_EALPHA                   (*(volatile  int32* )(NFOC2_BASE + ( 174*2)))   // RV:0000H Estimator estimated back-EMF EALPHA (32-bit)
 #define NFOC2_EALPHAH                  (*(volatile  int16* )(NFOC2_BASE + ( 175*2)))   // RV:0000H Estimator estimated back-EMF EALPHA high 16-bit
 #define NFOC2_EBETA                    (*(volatile  int32* )(NFOC2_BASE + ( 186*2)))   // RV:0000H Estimator estimated back-EMF EBETA (32-bit)
 #define NFOC2_EBETAH                   (*(volatile  int16* )(NFOC2_BASE + ( 187*2)))   // RV:0000H Estimator estimated back-EMF EBETA high 16-bit
 #define NFOC2_ETHETA                   (*(volatile  int32* )(NFOC2_BASE + ( 188*2)))   // RV:0000H Estimator estimated angle (32-bit)
 #define NFOC2_ETHETAH                  (*(volatile  int16* )(NFOC2_BASE + ( 189*2)))   // RV:0000H Estimator angle high 16-bit
 #define NFOC2_ZALORG                   (*(volatile  int16* )(NFOC2_BASE + ( 190*2)))   // RV:0000H Estimated back-EMF      /* factory */
 #define NFOC2_ZBEORG                   (*(volatile  int16* )(NFOC2_BASE + ( 191*2)))   // RV:0000H Estimated back-EMF      /* factory */
 #define NFOC2_EMF                      (*(volatile  int16* )(NFOC2_BASE + ( 240*2)))   // RV:0000H EALPHAandEBETAcalculationmagnitude (sqrt of sum of squares), i.e. Estimated back-EMFmagnitude
 #define NFOC2_ATHETA                   (*(volatile  int16* )(NFOC2_BASE + ( 241*2)))   // RV:0000H EALPHA/EBETA calculated angle      /* factory */
 #define NFOC2_OMECLI                   (*(volatile  int32* )(NFOC2_BASE + ( 256*2)))   // RV:0000H Omega startup real-time value (32-bit)      /* factory */
 #define NFOC2_OMECLIL                  (*(volatile  int16* )(NFOC2_BASE + ( 256*2)))   // RV:0000H Omega startup real-time value low 16-bit      /* factory */
 #define NFOC2_OMECLIH                  (*(volatile  int16* )(NFOC2_BASE + ( 257*2)))   // RV:0000H Omega startup real-time value high 16-bit      /* factory */
 #define NFOC2_OMEGA                    (*(volatile  int16* )(NFOC2_BASE + ( 258*2)))   // RV:0000H Estimated OMEGA
 
 #define NFOC2_IESTA                    (*(volatile  int16* )(NFOC2_BASE + ( 260*2)))   // RV:0000H Estimated current IALPHA
 #define NFOC2_IESTB                    (*(volatile  int16* )(NFOC2_BASE + ( 261*2)))   // RV:0000H Estimated current IBETA
 #define NFOC2_OMEFLT                   (*(volatile  int32* )(NFOC2_BASE + ( 262*2)))   // RV:0000H OMEGA 1st-stage filtered value (32-bit)
 #define NFOC2_OMEFLTH                  (*(volatile  int16* )(NFOC2_BASE + ( 263*2)))   // RV:0000H OMEGA 1st-stage filtered value high 16-bit
 #define NFOC2_OMEFL2                   (*(volatile  int32* )(NFOC2_BASE + ( 264*2)))   // RV:0000H OMEGA 2nd-stage filtered value (32-bit)
 #define NFOC2_OMEFL2H                  (*(volatile  int16* )(NFOC2_BASE + ( 265*2)))   // RV:0000H OMEGA 2nd-stage filtered value high 16-bit
 #define NFOC2_ZALPHA                   (*(volatile  int16* )(NFOC2_BASE + ( 266*2)))   // RV:0000H before filteringEstimated back-EMF      /* factory */
 #define NFOC2_ZBETA                    (*(volatile  int16* )(NFOC2_BASE + ( 267*2)))   // RV:0000H before filteringEstimated back-EMF      /* factory */
 #define NFOC2_KLPF                     (*(volatile  int16* )(NFOC2_BASE + ( 268*2)))   // RV:0000H Estimator LPF coefficient
 #define NFOC2_UDFIN                    (*(volatile  int16* )(NFOC2_BASE + ( 270*2)))   // RV:0000H UD final value
 #define NFOC2_UQFIN                    (*(volatile  int16* )(NFOC2_BASE + ( 271*2)))   // RV:0000H UQ final value
 #define NFOC2_UALPHA                   (*(volatile  int16* )(NFOC2_BASE + ( 272*2)))   // RV:0000H UALPHA
 #define NFOC2_UBETA                    (*(volatile  int16* )(NFOC2_BASE + ( 273*2)))   // RV:0000H UBETA
 #define NFOC2_UALORG                   (*(volatile  int16* )(NFOC2_BASE + ( 140*2)))   // RV:0000H UALORG
 #define NFOC2_UBEORG                   (*(volatile  int16* )(NFOC2_BASE + ( 141*2)))   // RV:0000H UBEORG
 #define NFOC2_Y                        (*(volatile  int16* )(NFOC2_BASE + ( 274*2)))   // RV:0000H SVPWM calculation intermediate value      /* factory */
 #define NFOC2_Z                        (*(volatile  int16* )(NFOC2_BASE + ( 275*2)))   // RV:0000H SVPWM calculation intermediate value      /* factory */
 #define NFOC2_T1ORG                    (*(volatile  int16* )(NFOC2_BASE + ( 48*2)))    // RV:0000H SVPWM calculation intermediate value      /* factory */
 #define NFOC2_T2ORG                    (*(volatile  int16* )(NFOC2_BASE + ( 49*2)))    // RV:0000H SVPWM calculation intermediate value      /* factory */
 #define NFOC2_T1RC                     (*(volatile  int16* )(NFOC2_BASE + ( 50*2)))    // RV:0000H SVPWM calculation intermediate value      /* factory */
 #define NFOC2_T2RC                     (*(volatile  int16* )(NFOC2_BASE + ( 51*2)))    // RV:0000H SVPWM calculation intermediate value      /* factory */
 #define NFOC2_OMUNIT                   (*(volatile  int16* )(NFOC2_BASE + ( 52*2)))    // RV:0000H Over-modulation amplification coefficient
 #define NFOC2_TC                       (*(volatile  int16* )(NFOC2_BASE + ( 54*2)))    // RV:0000H SVPWM calculation intermediate value      /* factory */
 #define NFOC2_TB                       (*(volatile  int16* )(NFOC2_BASE + ( 55*2)))    // RV:0000H SVPWM calculation intermediate value      /* factory */
 #define NFOC2_TA                       (*(volatile  int16* )(NFOC2_BASE + ( 56*2)))    // RV:0000H SVPWM calculation intermediate value      /* factory */
 #define NFOC2_DLYCNT                   (*(volatile  uint16* )(NFOC2_BASE + ( 57*2)))   // RV:0000H CLK count for dly_en delay function
 #define NFOC2_TAON                     (*(volatile  int16* )(NFOC2_BASE + ( 58*2)))    // RV:0000H SVPWM calculation intermediate value      /* factory */
 #define NFOC2_TAOND                    (*(volatile  int16* )(NFOC2_BASE + ( 59*2)))    // RV:0000H SVPWM calculation intermediate value      /* factory */
 #define NFOC2_TBON                     (*(volatile  int16* )(NFOC2_BASE + ( 60*2)))    // RV:0000H SVPWM calculation intermediate value      /* factory */
 #define NFOC2_TBOND                    (*(volatile  int16* )(NFOC2_BASE + ( 61*2)))    // RV:0000H SVPWM calculation intermediate value      /* factory */
 #define NFOC2_TCON                     (*(volatile  int16* )(NFOC2_BASE + ( 62*2)))    // RV:0000H SVPWM calculation intermediate value      /* factory */
 #define NFOC2_TCOND                    (*(volatile  int16* )(NFOC2_BASE + ( 63*2)))    // RV:0000H SVPWM calculation intermediate value      /* factory */
 #define NFOC2_TADTC                    (*(volatile  int16* )(NFOC2_BASE + ( 64*2)))    // RV:0000H SVPWM calculation intermediate value      /* factory */
 #define NFOC2_TADTCD                   (*(volatile  int16* )(NFOC2_BASE + ( 65*2)))    // RV:0000H SVPWM calculation intermediate value      /* factory */
 #define NFOC2_TBDTC                    (*(volatile  int16* )(NFOC2_BASE + ( 66*2)))    // RV:0000H SVPWM calculation intermediate value      /* factory */
 #define NFOC2_TBDTCD                   (*(volatile  int16* )(NFOC2_BASE + ( 67*2)))    // RV:0000H SVPWM calculation intermediate value      /* factory */
 #define NFOC2_TCDTC                    (*(volatile  int16* )(NFOC2_BASE + ( 68*2)))    // RV:0000H SVPWM calculation intermediate value      /* factory */
 #define NFOC2_TCDTCD                   (*(volatile  int16* )(NFOC2_BASE + ( 69*2)))    // RV:0000H SVPWM calculation intermediate value      /* factory */
 #define NFOC2_DR1                      (*(volatile uint16* )(NFOC2_BASE + ( 70*2)))    // RV:0000H SVPWM calculation intermediate value      /* factory */
 #define NFOC2_DR1N                     (*(volatile uint16* )(NFOC2_BASE + ( 71*2)))    // RV:0000H SVPWM calculation intermediate value      /* factory */
 #define NFOC2_DR2                      (*(volatile uint16* )(NFOC2_BASE + ( 72*2)))    // RV:0000H SVPWM calculation intermediate value      /* factory */
 #define NFOC2_DR2N                     (*(volatile uint16* )(NFOC2_BASE + ( 73*2)))    // RV:0000H SVPWM calculation intermediate value      /* factory */
 #define NFOC2_DR3                      (*(volatile uint16* )(NFOC2_BASE + ( 74*2)))    // RV:0000H SVPWM calculation intermediate value      /* factory */
 #define NFOC2_DR3N                     (*(volatile uint16* )(NFOC2_BASE + ( 75*2)))    // RV:0000H SVPWM calculation intermediate value      /* factory */
 #define NFOC2_DRA                      (*(volatile uint16* )(NFOC2_BASE + ( 76*2)))    // RV:0000H SVPWM value loaded to DRV      /* factory */
 #define NFOC2_DRAN                     (*(volatile uint16* )(NFOC2_BASE + ( 77*2)))    // RV:0000H SVPWM value loaded to DRV      /* factory */
 #define NFOC2_DRB                      (*(volatile uint16* )(NFOC2_BASE + ( 78*2)))    // RV:0000H SVPWM value loaded to DRV      /* factory */
 #define NFOC2_DRBN                     (*(volatile uint16* )(NFOC2_BASE + ( 79*2)))    // RV:0000H SVPWM value loaded to DRV      /* factory */
 #define NFOC2_DRC                      (*(volatile uint16* )(NFOC2_BASE + ( 80*2)))    // RV:0000H SVPWM value loaded to DRV      /* factory */
 #define NFOC2_DRCN                     (*(volatile uint16* )(NFOC2_BASE + ( 81*2)))    // RV:0000H SVPWM value loaded to DRV      /* factory */
 #define NFOC2_UDCALP                   (*(volatile  int16* )(NFOC2_BASE + ( 82*2)))    // RV:0000H UDC*UALPHA
 #define NFOC2_UDCBET                   (*(volatile  int16* )(NFOC2_BASE + ( 83*2)))    // RV:0000H UDC*UBETA
 #define NFOC2_MAY1                     (*(volatile  int16* )(NFOC2_BASE + ( 84*2)))    // RV:0000H AO observer related signal      /* factory */
 #define NFOC2_MBY1                     (*(volatile  int16* )(NFOC2_BASE + ( 85*2)))    // RV:0000H AO observer related signal      /* factory */
 #define NFOC2_MAY2                     (*(volatile  int16* )(NFOC2_BASE + ( 86*2)))    // RV:0000H AO observer related signal      /* factory */
 #define NFOC2_MBY2                     (*(volatile  int16* )(NFOC2_BASE + ( 87*2)))    // RV:0000H AO observer related signal      /* factory */
 #define NFOC2_MAY3                     (*(volatile  int16* )(NFOC2_BASE + ( 88*2)))    // RV:0000H AO observer related signal      /* factory */
 #define NFOC2_MBY3                     (*(volatile  int16* )(NFOC2_BASE + ( 89*2)))    // RV:0000H AO observer related signal      /* factory */
 #define NFOC2_MAY4                     (*(volatile  int16* )(NFOC2_BASE + ( 90*2)))    // RV:0000H AO observer related signal      /* factory */
 #define NFOC2_MBY4                     (*(volatile  int16* )(NFOC2_BASE + ( 91*2)))    // RV:0000H AO observer related signal      /* factory */
 #define NFOC2_MAY5                     (*(volatile  int16* )(NFOC2_BASE + ( 92*2)))    // RV:0000H AO observer related signal      /* factory */
 #define NFOC2_MBY5                     (*(volatile  int16* )(NFOC2_BASE + ( 93*2)))    // RV:0000H AO observer related signal      /* factory */
 #define NFOC2_MAU1                     (*(volatile  int16* )(NFOC2_BASE + ( 94*2)))    // RV:0000H AO observer related signal      /* factory */
 #define NFOC2_MBU1                     (*(volatile  int16* )(NFOC2_BASE + ( 95*2)))    // RV:0000H AO observer related signal      /* factory */
 #define NFOC2_MAU2                     (*(volatile  int16* )(NFOC2_BASE + ( 96*2)))    // RV:0000H AO observer related signal      /* factory */
 #define NFOC2_MBU2                     (*(volatile  int16* )(NFOC2_BASE + ( 97*2)))    // RV:0000H AO observer related signal      /* factory */
 #define NFOC2_MAU3                     (*(volatile  int16* )(NFOC2_BASE + ( 98*2)))    // RV:0000H AO observer related signal      /* factory */
 #define NFOC2_MBU3                     (*(volatile  int16* )(NFOC2_BASE + ( 99*2)))    // RV:0000H AO observer related signal      /* factory */
 #define NFOC2_MAU4                     (*(volatile  int16* )(NFOC2_BASE + (100*2)))    // RV:0000H AO observer related signal      /* factory */
 #define NFOC2_MBU4                     (*(volatile  int16* )(NFOC2_BASE + (101*2)))    // RV:0000H AO observer related signal      /* factory */
 #define NFOC2_FTCPS                    (*(volatile  int16* )(NFOC2_BASE + (102*2)))    // RV:0000H Calculated dynamic compensation angleFTCPS = FTCK*OMEFL2*FBASE
 #define NFOC2_FTHETA                   (*(volatile  int16* )(NFOC2_BASE + (103*2)))    // RV:0000H Feedback angle to estimator PI
 #define NFOC2_IS                       (*(volatile  int16* )(NFOC2_BASE + (104*2)))    // RV:0000H IALPHA/IBETA magnitude (sqrt of sum of squares)
 #define NFOC2_ITHETA                   (*(volatile  int16* )(NFOC2_BASE + (105*2)))    // RV:0000H IALPHA/IBETA calculated angle
 #define NFOC2_ITFLT                    (*(volatile  int32* )(NFOC2_BASE + (106*2)))    // RV:0000H ITRIP filtered value (32-bit)
 #define NFOC2_ITFLTH                   (*(volatile  int16* )(NFOC2_BASE + (107*2)))    // RV:0000H ITRIP filtered value high 16-bit
 #define NFOC2_ITRIP                    (*(volatile  int16* )(NFOC2_BASE + (108*2)))    // RV:0000H Sampled ITRIP, for power calculation
 #define NFOC2_POWER                    (*(volatile  int16* )(NFOC2_BASE + (109*2)))    // RV:0000H Power value
 #define NFOC2_US                       (*(volatile  int16* )(NFOC2_BASE + (110*2)))    // RV:0000H UALPHA/UBETA magnitude (sqrt of sum of squares)
 #define NFOC2_UTHETA                   (*(volatile  int16* )(NFOC2_BASE + (111*2)))    // RV:0000H UALPHA/UBETA calculated angle
 
 #define NFOC2_ID0                      (*(volatile  int16* )(NFOC2_BASE + (122*2)))    // RV:0000H D-axis current from previous FOC calculation
 #define NFOC2_IQ0                      (*(volatile  int16* )(NFOC2_BASE + (123*2)))    // RV:0000H Q-axis current from previous FOC calculation
 #define NFOC2_DELIAL                   (*(volatile  int16* )(NFOC2_BASE + (124*2)))    // RV:0000H HF current      /* factory */
 #define NFOC2_DELIBE                   (*(volatile  int16* )(NFOC2_BASE + (125*2)))    // RV:0000H HF current      /* factory */
 #define NFOC2_HALPHA                   (*(volatile  int16* )(NFOC2_BASE + (126*2)))    // RV:0000H HF currentenvelope
 #define NFOC2_HBETA                    (*(volatile  int16* )(NFOC2_BASE + (127*2)))    // RV:0000H HF currentenvelope
 #define NFOC2_HS                       (*(volatile  int16* )(NFOC2_BASE + (138*2)))    // RV:0000H HALPHA/HBETA magnitude (sqrt of sum of squares)      /* factory */
 #define NFOC2_HTHETA                   (*(volatile  int16* )(NFOC2_BASE + (139*2)))    // RV:0000H HALPHA/HBETA calculated angle      /* factory */
 #define NFOC2_DELIQ                    (*(volatile  int16* )(NFOC2_BASE + (142*2)))    // RV:0000H HF injection calculation intermediate value
 
 #define NFOC2_HKP                      (*(volatile  int16* )(NFOC2_BASE + (112*2)))    // RV:0000H HF injection PI KP
 #define NFOC2_HKI                      (*(volatile  int16* )(NFOC2_BASE + (113*2)))    // RV:0000H HF injection PI KI
 #define NFOC2_HMAX                     (*(volatile  int16* )(NFOC2_BASE + (114*2)))    // RV:0000H HF injection PI upper limit
 #define NFOC2_HMIN                     (*(volatile  int16* )(NFOC2_BASE + (115*2)))    // RV:0000H HF injection PI lower limit
 #define NFOC2_HEK                      (*(volatile  int16* )(NFOC2_BASE + (116*2)))    // RV:0000H HF injection PI EK
 #define NFOC2_HEK1                     (*(volatile  int16* )(NFOC2_BASE + (117*2)))    // RV:0000H HF injection PI EK1
 #define NFOC2_HUK                      (*(volatile  int32* )(NFOC2_BASE + (118*2)))    // RV:0000H HF injection PI UK (32-bit)
 #define NFOC2_HUKH                     (*(volatile  int16* )(NFOC2_BASE + (119*2)))    // RV:0000H HF injection PI UK high 16-bit
 #define NFOC2_DKP                      (*(volatile  int16* )(NFOC2_BASE + (128*2)))    // RV:0000H D-axis PI current loop KP
 #define NFOC2_DKI                      (*(volatile  int16* )(NFOC2_BASE + (129*2)))    // RV:0000H D-axis PI current loop KI
 #define NFOC2_DMAX                     (*(volatile  int16* )(NFOC2_BASE + (130*2)))    // RV:0000H D-axis PI current loop upper limit
 #define NFOC2_DMIN                     (*(volatile  int16* )(NFOC2_BASE + (131*2)))    // RV:0000H D-axis PI current loop lower limit
 #define NFOC2_DEK                      (*(volatile  int16* )(NFOC2_BASE + (132*2)))    // RV:0000H D-axis PI current loop EK
 #define NFOC2_DEK1                     (*(volatile  int16* )(NFOC2_BASE + (133*2)))    // RV:0000H D-axis PI current loop EK1
 #define NFOC2_DUK                      (*(volatile  int32* )(NFOC2_BASE + (134*2)))    // RV:0000H DaxisPIcurrent loop UK (32bit)
 #define NFOC2_DUKH                     (*(volatile  int16* )(NFOC2_BASE + (135*2)))    // RV:0000H DaxisPIcurrent loopUK high 16-bit
 // #define NFOC2_DEXC                    (*(volatile  int16* )(NFOC2_BASE + (136*2)))  // RV:0000H DaxisPIcurrent loopUKoverflow value
 #define NFOC2_QKP                      (*(volatile  int16* )(NFOC2_BASE + (144*2)))    // RV:0000H Q-axis PI current loop KP
 #define NFOC2_QKI                      (*(volatile  int16* )(NFOC2_BASE + (145*2)))    // RV:0000H Q-axis PI current loop KI
 #define NFOC2_QMAX                     (*(volatile  int16* )(NFOC2_BASE + (146*2)))    // RV:0000H Q-axis PI current loop upper limit
 #define NFOC2_QMIN                     (*(volatile  int16* )(NFOC2_BASE + (147*2)))    // RV:0000H Q-axis PI current loop lower limit
 #define NFOC2_QEK                      (*(volatile  int16* )(NFOC2_BASE + (148*2)))    // RV:0000H Q-axis PI current loop EK
 #define NFOC2_QEK1                     (*(volatile  int16* )(NFOC2_BASE + (149*2)))    // RV:0000H Q-axis PI current loop EK1
 #define NFOC2_QUK                      (*(volatile  int32* )(NFOC2_BASE + (150*2)))    // RV:0000H QaxisPIcurrent loop UK (32bit)
 #define NFOC2_QUKH                     (*(volatile  int16* )(NFOC2_BASE + (151*2)))    // RV:0000H QaxisPIcurrent loopUK high 16-bit
 // #define NFOC2_QEXC                      (*(volatile  int16* )(NFOC2_BASE + (152*2)))  // RV:0000H QaxisPIcurrent loopUKoverflow value
  
 #define NFOC2_IRLOW                    (*(volatile  int16* )(NFOC2_BASE + (8*2)))      // RV:0000H Current reference lower limit; triggers reference error when exceeded
 #define NFOC2_IRUPP                    (*(volatile  int16* )(NFOC2_BASE + (9*2)))      // RV:0000H Current reference upper limit; triggers reference error when exceeded
  
 #define NFOC2_EKP                      (*(volatile  int16* )(NFOC2_BASE + (160*2)))    // RV:0000H Estimator PI current loop KP
 #define NFOC2_EKI                      (*(volatile  int16* )(NFOC2_BASE + (161*2)))    // RV:0000H Estimator PI current loop KI
 #define NFOC2_EMAX                     (*(volatile  int16* )(NFOC2_BASE + (162*2)))    // RV:0000H Estimator PI current loop upper limit
 #define NFOC2_EMIN                     (*(volatile  int16* )(NFOC2_BASE + (163*2)))    // RV:0000H Estimator PI current loop lower limit
 #define NFOC2_EEK                      (*(volatile  int16* )(NFOC2_BASE + (164*2)))    // RV:0000H Estimator PI current loop EK
 #define NFOC2_EEK1                     (*(volatile  int16* )(NFOC2_BASE + (165*2)))    // RV:0000H Estimator PI current loop EK1
 #define NFOC2_EUK                      (*(volatile  int32* )(NFOC2_BASE + (166*2)))    // RV:0000H Estimator PI current loop UK (32-bit)
 #define NFOC2_EUKH                     (*(volatile  int16* )(NFOC2_BASE + (167*2)))    // RV:0000H Estimator PI current loop UK high 16-bit
 // #define NFOC2_EEXC                     (*(volatile  int16* )(NFOC2_BASE + (168*2)))  // RV:0000H EstimatorPIcurrent loopUKoverflow value
 
 #define NFOC2_LKSMIN                   (*(volatile  int16* )(NFOC2_BASE + (16*2)))     // RV:0000H LOCK0 minimum stall speed
 #define NFOC2_LKSMAX                   (*(volatile  int16* )(NFOC2_BASE + (17*2)))     // RV:0000H LOCK1 maximum stall speed
 #define NFOC2_LOCKK                    (*(volatile  int16* )(NFOC2_BASE + (18*2)))     // RV:0000H LOCK2 speed/EMF multiple in Q8 format
 #define NFOC2_LKARR                    (*(volatile uint16* )(NFOC2_BASE + (20*2)))     // RV:0000H Stall count target value
 #define NFOC2_LKCNT                    (*(volatile uint16* )(NFOC2_BASE + (21*2)))     // RV:0000H Stall count value, shared by 3; increments by 1 only when all 3 conditions hold
     
 #define NFOC2_WKP                      (*(volatile  int16* )(NFOC2_BASE + (176*2)))     // RV:0000H Outer loop PI current loop KP
 #define NFOC2_WKI                      (*(volatile  int16* )(NFOC2_BASE + (177*2)))     // RV:0000H Outer loop PI current loop KI
 #define NFOC2_WMAX                     (*(volatile  int16* )(NFOC2_BASE + (178*2)))     // RV:0000H Outer loop PI current loop upper limit
 #define NFOC2_WMIN                     (*(volatile  int16* )(NFOC2_BASE + (179*2)))     // RV:0000H Outer loop PI current loop lower limit
 #define NFOC2_WEK                      (*(volatile  int16* )(NFOC2_BASE + (180*2)))     // RV:0000H Outer loop PI current loop EK
 #define NFOC2_WEK1                     (*(volatile  int16* )(NFOC2_BASE + (181*2)))     // RV:0000H Outer loop PI current loop EK1
 #define NFOC2_WUK                      (*(volatile  int32* )(NFOC2_BASE + (182*2)))     // RV:0000H Outer loop PI current loop UK (32-bit)
 #define NFOC2_WUKH                     (*(volatile  int16* )(NFOC2_BASE + (183*2)))     // RV:0000H Outer loop PI current loop UK high 16-bit
 // #define NFOC2_WEXC                     (*(volatile  int16* )(NFOC2_BASE + (184*2)))  // RV:0000H outer loopPIcurrent loopUKoverflow value
 
 #define NFOC2_FWKP                     (*(volatile  int16* )(NFOC2_BASE + (192*2)))     // RV:0000H Field weakening PI KP
 #define NFOC2_FWKI                     (*(volatile  int16* )(NFOC2_BASE + (193*2)))     // RV:0000H Field weakening PI KI
 #define NFOC2_FWMAX                    (*(volatile  int16* )(NFOC2_BASE + (194*2)))     // RV:0000H Field weakening PI upper limit
 #define NFOC2_FWMIN                    (*(volatile  int16* )(NFOC2_BASE + (195*2)))     // RV:0000H Field weakening PI lower limit
 #define NFOC2_FWEK                     (*(volatile  int16* )(NFOC2_BASE + (196*2)))     // RV:0000H Field weakening PI EK
 #define NFOC2_FWEK1                    (*(volatile  int16* )(NFOC2_BASE + (197*2)))     // RV:0000H Field weakening PI EK1
 #define NFOC2_FWUK                     (*(volatile  int32* )(NFOC2_BASE + (198*2)))     // RV:0000H Field weakening PI UK (32-bit)
 #define NFOC2_FWUKH                    (*(volatile  int16* )(NFOC2_BASE + (199*2)))     // RV:0000H Field weakening PI UK high 16-bit
 // #define NFOC2_FWEXC                      (*(volatile  int16* )(NFOC2_BASE + (200*2)))  // RV:0000H Field weakening PI UK overflow value
 
 #define NFOC2_OVP                      (*(volatile  int16* )(NFOC2_BASE + (10*2)))      // RV:0000H Overvoltage threshold
 #define NFOC2_OVPARR                   (*(volatile uint8*  )(NFOC2_BASE + (11*2)))      // RV:00H   Overvoltage count target value (8-bit)
 #define NFOC2_OVPCNT                   (*(volatile uint8*  )(NFOC2_BASE + (11*2+1)))    // RV:00H   Overvoltage count value (8-bit)
 #define NFOC2_UVP                      (*(volatile  int16* )(NFOC2_BASE + (12*2)))      // RV:0000H Undervoltage threshold
 #define NFOC2_UVPARR                   (*(volatile uint8*  )(NFOC2_BASE + (13*2)))      // RV:00H   Undervoltage count target value (8-bit)
 #define NFOC2_UVPCNT                   (*(volatile uint8*  )(NFOC2_BASE + (13*2+1)))    // RV:00H   Undervoltage count value (8-bit)
 #define NFOC2_SOCP                     (*(volatile  int16* )(NFOC2_BASE + (14*2)))      // RV:0000H Software overcurrent threshold
 #define NFOC2_SOCPARR                  (*(volatile uint8*  )(NFOC2_BASE + (15*2)))      // RV:00H   Software overcurrent count target value (8-bit)
 #define NFOC2_SOCPCNT                  (*(volatile uint8*  )(NFOC2_BASE + (15*2+1)))    // RV:00H   Software overcurrent count value (8-bit)
 
 #define NFOC2_TS                       (*(volatile  int16* )(NFOC2_BASE + (316*2)))     // RV:0000H Single-resistor phase shift / dual/triple resistor min sample pulse width [0,32767]
 #define NFOC2_NTS                      (*(volatile  int16* )(NFOC2_BASE + (317*2)))     // RV:0000H Triple-resistor pulse width mask / new single-resistor min pulse width [0,1023]
 #define NFOC2_TDLY                     (*(volatile  int16* )(NFOC2_BASE + (318*2)))     // RV:0000H Current sampling trigger timing
 #define NFOC2_TDLYD                    (*(volatile  int16* )(NFOC2_BASE + (319*2)))     // RV:0000H Single-resistor dynamic pre/post sampling timing
 #define NFOC2_ARR                      (*(volatile uint16* )(NFOC2_BASE + (320*2)))     // RV:0000H FOC carrier frequency
 #define NFOC2_IDK                      (*(volatile  int16* )(NFOC2_BASE + (322*2)))     // RV:0000H ID filter coefficient
 #define NFOC2_IQK                      (*(volatile  int16* )(NFOC2_BASE + (323*2)))     // RV:0000H IQ filter coefficient
 #define NFOC2_OMEGAK                   (*(volatile  int16* )(NFOC2_BASE + (324*2)))     // RV:0000H Omega 1st-stage filter coefficient
 #define NFOC2_OMEK2                    (*(volatile  int16* )(NFOC2_BASE + (325*2)))     // RV:0000H Omega 2nd-stage filter coefficient
 #define NFOC2_OMEACC                   (*(volatile  int32* )(NFOC2_BASE + (202*2)))     // RV:0000H OMEGA startup velocity increment
 #define NFOC2_OMEEND                   (*(volatile  int32* )(NFOC2_BASE + (204*2)))     // RV:0000H OMEGA startup END value
 #define NFOC2_OMEENDH                  (*(volatile  int16* )(NFOC2_BASE + (205*2)))     // RV:0000H OMEGA startup END value
 #define NFOC2_OMEMIN                   (*(volatile  int16* )(NFOC2_BASE + (206*2)))     // RV:0000H OMEGA startup transition value
 #define NFOC2_FTCK                     (*(volatile  int16* )(NFOC2_BASE + (207*2)))     // RV:0000H Feedback angle dynamic compensation coefficient
 #define NFOC2_FBASE                    (*(volatile  int16* )(NFOC2_BASE + (208*2)))     // RV:0000H Velocity reference
 #define NFOC2_OMEMI2                   (*(volatile  int16* )(NFOC2_BASE + (209*2)))     // RV:0000H Minimum velocity corresponding to KLPF
 #define NFOC2_THECOM                   (*(volatile  int16* )(NFOC2_BASE + (210*2)))     // RV:0000H Output angle static compensation angle
 #define NFOC2_FTCOM                    (*(volatile  int16* )(NFOC2_BASE + (211*2)))     // RV:0000H Feedback angle static compensation angle
 #define NFOC2_EK1                      (*(volatile  int16* )(NFOC2_BASE + (212*2)))     // RV:0000H FOC estimator parameter 1
 #define NFOC2_EK2                      (*(volatile  int16* )(NFOC2_BASE + (213*2)))     // RV:0000H FOC estimator parameter 3
 #define NFOC2_EK3                      (*(volatile  int16* )(NFOC2_BASE + (214*2)))     // RV:0000H FOC estimator parameter 2
 #define NFOC2_EK4                      (*(volatile  int16* )(NFOC2_BASE + (215*2)))     // RV:0000H FOC estimator parameter 4
 #define NFOC2_KSLIDE                   (*(volatile  int16* )(NFOC2_BASE + (216*2)))     // RV:0000H SMO coefficient
 #define NFOC2_MAXERR                   (*(volatile  int16* )(NFOC2_BASE + (217*2)))     // RV:0000H SMO limit
 #define NFOC2_MERRRE                   (*(volatile  int16* )(NFOC2_BASE + (218*2)))     // RV:0000H SMO limitreciprocal
 #define NFOC2_TDTC                     (*(volatile  int16* )(NFOC2_BASE + (219*2)))     // RV:0000H Dual/triple resistor dead-time compensation
 #define NFOC2_IDREF                    (*(volatile  int16* )(NFOC2_BASE + (220*2)))     // RV:0000H Given D-axis value
 #define NFOC2_IQREF                    (*(volatile  int16* )(NFOC2_BASE + (221*2)))     // RV:0000H Given Q-axis value
 #define NFOC2_IAREF                    (*(volatile  int16* )(NFOC2_BASE + (4*2)))       // RV:0000H U-phase current reference
 #define NFOC2_IBREF                    (*(volatile  int16* )(NFOC2_BASE + (5*2)))       // RV:0000H V-phase current reference
 #define NFOC2_ICREF                    (*(volatile  int16* )(NFOC2_BASE + (6*2)))       // RV:0000H W-phase current reference
 #define NFOC2_ITREF                    (*(volatile  int16* )(NFOC2_BASE + (7*2)))       // RV:0000H Bus current reference
 #define NFOC2_UDC                      (*(volatile  int16* )(NFOC2_BASE + (0*2)))       // RV:0000H Bus voltage sample value
 #define NFOC2_UDCK                     (*(volatile  int16* )(NFOC2_BASE + (1*2)))       // RV:0000H Bus voltage sample filter coefficient
 #define NFOC2_UDCFLT                   (*(volatile  int32* )(NFOC2_BASE + (2*2)))       // RV:0000H Bus voltage filtered value (32-bit)
 #define NFOC2_UDCFLTH                  (*(volatile  int16* )(NFOC2_BASE + (3*2)))       // RV:0000H Bus voltage filtered value high 16-bit
 #define NFOC2_UQCPS                    (*(volatile  int16* )(NFOC2_BASE + (231*2)))     // RV:0000H D-axis voltage compensation value
 #define NFOC2_UDCPS                    (*(volatile  int16* )(NFOC2_BASE + (230*2)))     // RV:0000H Q-axis voltage compensation value
 #define NFOC2_WREF                     (*(volatile  int16* )(NFOC2_BASE + (232*2)))     // RV:0000H Outer loop reference value [0~32767]
 #define NFOC2_WFDB                     (*(volatile  int16* )(NFOC2_BASE + (233*2)))     // RV:0000H Outer loop feedback value
 #define NFOC2_ITK                      (*(volatile  int16* )(NFOC2_BASE + (234*2)))     // RV:0000H ITRIP filter coefficient
 #define NFOC2_POWK                     (*(volatile  int16* )(NFOC2_BASE + (235*2)))     // RV:0000H POWER filter coefficient (two 8-bit) POWER = (ITRIP*K1)*(UDC*K2)
 #define NFOC2_FGBASE                   (*(volatile  int16* )(NFOC2_BASE + (236*2)))     // RV:0000H FGcalculationVelocity reference
 
 #define NFOC2_UALCPS                   (*(volatile  int16* )(NFOC2_BASE + (238*2)))     // RV:0000H UALPHA voltage compensation value
 #define NFOC2_UBECPS                   (*(volatile  int16* )(NFOC2_BASE + (239*2)))     // RV:0000H UBETA voltage compensation value
 #define NFOC2_NCURR                    (*(volatile  int16* )(NFOC2_BASE + (22*2)))      // RV:0000H Phase loss detection current setting
 #define NFOC2_PLK                      (*(volatile  int16* )(NFOC2_BASE + (23*2)))      // RV:0000H Phase loss detection current multiplier coefficient
 
 #define NFOC2_RATAR                    (*(volatile  int16* )(NFOC2_BASE + (242*2)))     // RV:0000H User-filled ramp target value
 #define NFOC2_RAOUT                    (*(volatile  int16* )(NFOC2_BASE + (243*2)))     // RV:0000H Ramp output value after ramping
 #define NFOC2_RAINC                    (*(volatile  int16* )(NFOC2_BASE + (244*2)))     // RV:0000H Upward step increment value
 #define NFOC2_RADEC                    (*(volatile  int16* )(NFOC2_BASE + (245*2)))     // RV:0000H Downward step decrement value
 #define NFOC2_LK1                      (*(volatile  int16* )(NFOC2_BASE + (246*2)))     // RV:0000H Low-speed observer coefficient
 #define NFOC2_LK2                      (*(volatile  int16* )(NFOC2_BASE + (247*2)))     // RV:0000H Low-speed observer coefficient
 #define NFOC2_LK3                      (*(volatile  int16* )(NFOC2_BASE + (248*2)))     // RV:0000H Low-speed observer coefficient
 #define NFOC2_LK4                      (*(volatile  int16* )(NFOC2_BASE + (249*2)))     // RV:0000H Low-speed observer coefficient   
 #define NFOC2_LK5                      (*(volatile  int16* )(NFOC2_BASE + (250*2)))     // RV:0000H Low-speed observer coefficient   
 #define NFOC2_LK6                      (*(volatile  int16* )(NFOC2_BASE + (251*2)))     // RV:0000H Low-speed observer coefficient   
 #define NFOC2_LED                      (*(volatile  int16* )(NFOC2_BASE + (252*2)))     // RV:0000H Low-speed observer coefficient
 #define NFOC2_LEQ                      (*(volatile  int16* )(NFOC2_BASE + (253*2)))     // RV:0000H Low-speed observer coefficient
 #define NFOC2_LOME                     (*(volatile  int32* )(NFOC2_BASE + (254*2)))     // RV:0000H Low-speed observer velocity
 #define NFOC2_LOMEH                    (*(volatile  int16* )(NFOC2_BASE + (255*2)))     // RV:0000H Low-speed observer velocity
 #define NFOC2_XALPHA                   (*(volatile  int32* )(NFOC2_BASE + (276*2)))     // RV:0000H Flux observer calculation intermediate value      /* factory */
 #define NFOC2_XALPHAH                  (*(volatile  int16* )(NFOC2_BASE + (277*2)))     // RV:0000H Flux observer calculation intermediate value      /* factory */
 #define NFOC2_XBETA                    (*(volatile  int32* )(NFOC2_BASE + (278*2)))     // RV:0000H Flux observer calculation intermediate value      /* factory */
 #define NFOC2_XBETAH                   (*(volatile  int16* )(NFOC2_BASE + (279*2)))     // RV:0000H Flux observer calculation intermediate value      /* factory */
 #define NFOC2_ETALPHA                  (*(volatile  int16* )(NFOC2_BASE + (298*2)))     // RV:0000H Flux observer calculation intermediate value      /* factory */
 #define NFOC2_ETBETA                   (*(volatile  int16* )(NFOC2_BASE + (299*2)))     // RV:0000H Flux observer calculation intermediate value      /* factory */
 #define NFOC2_UABT                     (*(volatile  int16* )(NFOC2_BASE + (280*2)))     // RV:0000H Flux observer calculation intermediate value      /* factory */
 #define NFOC2_HEK0                     (*(volatile  int16* )(NFOC2_BASE + (282*2)))     // RV:0000H Flux observer calculation intermediate value
 #define NFOC2_PSI                      (*(volatile  int16* )(NFOC2_BASE + (283*2)))     // RV:0000H Flux observer calculation intermediate value
 #define NFOC2_UIK0                     (*(volatile  int16* )(NFOC2_BASE + (284*2)))     // RV:0000H UQ compensation harmonic multiplier coefficient
 #define NFOC2_UIK1                     (*(volatile  int16* )(NFOC2_BASE + (285*2)))     // RV:0000H UQ compensation harmonic multiplier coefficient
 #define NFOC2_UIK2                     (*(volatile  int16* )(NFOC2_BASE + (286*2)))     // RV:0000H UQ compensation harmonic multiplier coefficient
 #define NFOC2_UIK3                     (*(volatile  int16* )(NFOC2_BASE + (287*2)))     // RV:0000H UQ compensation harmonic multiplier coefficient
 #define NFOC2_UITC0                    (*(volatile  int16* )(NFOC2_BASE + (288*2)))     // RV:0000H UQ compensation angular phase shift
 #define NFOC2_UIUS0                    (*(volatile  int16* )(NFOC2_BASE + (289*2)))     // RV:0000H UQ compensation magnitude
 #define NFOC2_UITC1                    (*(volatile  int16* )(NFOC2_BASE + (290*2)))     // RV:0000H UQ compensation angular phase shift
 #define NFOC2_UIUS1                    (*(volatile  int16* )(NFOC2_BASE + (291*2)))     // RV:0000H UQ compensation magnitude
 #define NFOC2_UITC2                    (*(volatile  int16* )(NFOC2_BASE + (292*2)))     // RV:0000H UQ compensation angular phase shift
 #define NFOC2_UIUS2                    (*(volatile  int16* )(NFOC2_BASE + (293*2)))     // RV:0000H UQ compensation magnitude
 #define NFOC2_UITC3                    (*(volatile  int16* )(NFOC2_BASE + (294*2)))     // RV:0000H UQ compensation angular phase shift
 #define NFOC2_UIUS3                    (*(volatile  int16* )(NFOC2_BASE + (295*2)))     // RV:0000H UQ compensation magnitude
 #define NFOC2_TRG1                     (*(volatile  int16* )(NFOC2_BASE + (296*2)))     // RV:0000H I1 sampling point DR value
 #define NFOC2_TRG2                     (*(volatile  int16* )(NFOC2_BASE + (297*2)))     // RV:0000H I2 sampling point DR value
 
 #define NFOC2_OTHETA                   (*(volatile  int32* )(NFOC2_BASE + (300*2)))     // RV:0000H Estimator estimated angle (32-bit)
 #define NFOC2_OTHETAH                  (*(volatile  int16* )(NFOC2_BASE + (301*2)))     // RV:0000H Estimator angle high 16-bit
 
 #define NFOC2_USK                      (*(volatile  int16* )(NFOC2_BASE + (302*2)))     // RV:0000H Phase voltage sample coefficient
 #define NFOC2_UA                       (*(volatile  int16* )(NFOC2_BASE + (303*2)))     // RV:0000H A-phase voltage sample value
 #define NFOC2_UB                       (*(volatile  int16* )(NFOC2_BASE + (304*2)))     // RV:0000H B-phase voltage sample value
 #define NFOC2_UC                       (*(volatile  int16* )(NFOC2_BASE + (305*2)))     // RV:0000H C-phase voltage sample value
 #define NFOC2_USAL1                    (*(volatile  int16* )(NFOC2_BASE + (306*2)))     // RV:0000H USALPHA value calculated from UA, UB, UC
 #define NFOC2_USBE1                    (*(volatile  int16* )(NFOC2_BASE + (307*2)))     // RV:0000H USBETA value calculated from UA, UB, UC
 
 
 #define NFOC2_DELOTHE                  (*(volatile  int32* )(NFOC2_BASE + (326*2)))     // RV:0000H Estimator estimated angle (32-bit)
 #define NFOC2_DELOTHEH                 (*(volatile  int16* )(NFOC2_BASE + (327*2)))     // RV:0000H Estimator estimated angle
 #define NFOC2_DELETHE                  (*(volatile  int32* )(NFOC2_BASE + (328*2)))     // RV:0000H Estimator estimated angle (32-bit)
 #define NFOC2_DELETHEH                 (*(volatile  int16* )(NFOC2_BASE + (329*2)))     // RV:0000H Estimator estimated angle
 #define NFOC2_IG0                      (*(volatile  int16* )(NFOC2_BASE + (310*2)))     // RV:0000H HF injection calculation intermediate value      /* factory */
 #define NFOC2_IF0                      (*(volatile  int16* )(NFOC2_BASE + (311*2)))     // RV:0000H HF injection calculation intermediate value      /* factory */
 #define NFOC2_HUCPS                    (*(volatile  int16* )(NFOC2_BASE + (312*2)))     // RV:0000H HF injection calculation intermediate value      /* factory */
 #define NFOC2_HCTHE                    (*(volatile  int16* )(NFOC2_BASE + (313*2)))     // RV:0000H HF injection calculation intermediate value      /* factory */
 #define NFOC2_FWREF                    (*(volatile  int16* )(NFOC2_BASE + (314*2)))     // RV:0000H Field weakeningPIgiven value
 #define NFOC2_UDCD                     (*(volatile  int16* )(NFOC2_BASE + (330*2)))     // RV:0000H D-axis UDC value
 #define NFOC2_UDCQ                     (*(volatile  int16* )(NFOC2_BASE + (331*2)))     // RV:0000H Q-axis UDC value
 
 #define NFOC2_IQMAX                    (*(volatile uint16* )(NFOC2_BASE + (332*2)))     // RV:0000H IQREF maximum value
 #define NFOC2_IQMIN                    (*(volatile uint16* )(NFOC2_BASE + (333*2)))     // RV:0000H IQREF minimum value
 
 #define NFOC2_WUCPS                    (*(volatile  int16* )(NFOC2_BASE + (414*2)))     // RV:0000H Outer loop compensation value
 #define NFOC2_WUFIN                    (*(volatile  int16* )(NFOC2_BASE + (415*2)))     // RV:0000H Outer loop final value
 
 #define NFOC2_OSCNT                    (*(volatile  int16* )(NFOC2_BASE + (447*2)))     // RV:0000H OFFSET calibration count value
 #define NFOC2_OSSUM                    (*(volatile  int32* )(NFOC2_BASE + (448*2)))     // RV:0000H OFFSET calibration sum

 #define NFOC2_F1LB0                    (*(volatile uint16* )(NFOC2_BASE + (334*2)))     // RV:0000H IQREF filter parameter
 #define NFOC2_F1HB0                    (*(volatile uint16* )(NFOC2_BASE + (335*2)))     // RV:0000H IQREF filter parameter
 #define NFOC2_F1LB1                    (*(volatile uint16* )(NFOC2_BASE + (336*2)))     // RV:0000H IQREF filter parameter
 #define NFOC2_F1LB2                    (*(volatile uint16* )(NFOC2_BASE + (337*2)))     // RV:0000H IQREF filter parameter
 #define NFOC2_F1LA1                    (*(volatile uint16* )(NFOC2_BASE + (338*2)))     // RV:0000H IQREF filter parameter
 #define NFOC2_F1LA2                    (*(volatile uint16* )(NFOC2_BASE + (339*2)))     // RV:0000H IQREF filter parameter
 #define NFOC2_F1HB1                    (*(volatile uint16* )(NFOC2_BASE + (340*2)))     // RV:0000H IQREF filter parameter
 #define NFOC2_F1HB2                    (*(volatile uint16* )(NFOC2_BASE + (341*2)))     // RV:0000H IQREF filter parameter
 #define NFOC2_F1HA1                    (*(volatile uint16* )(NFOC2_BASE + (342*2)))     // RV:0000H IQREF filter parameter
 #define NFOC2_F1HA2                    (*(volatile uint16* )(NFOC2_BASE + (343*2)))     // RV:0000H IQREF filter parameter
 #define NFOC2_F1X0                     (*(volatile uint16* )(NFOC2_BASE + (344*2)))     // RV:0000H IQREF filter parameter
 #define NFOC2_F1X1                     (*(volatile uint16* )(NFOC2_BASE + (346*2)))     // RV:0000H IQREF filter parameter
 #define NFOC2_F1X2                     (*(volatile uint16* )(NFOC2_BASE + (347*2)))     // RV:0000H IQREF filter parameter
 #define NFOC2_F1Y1                     (*(volatile uint16* )(NFOC2_BASE + (348*2)))     // RV:0000H IQREF filter parameter
 #define NFOC2_F1Y2                     (*(volatile uint16* )(NFOC2_BASE + (349*2)))     // RV:0000H IQREF filter parameter
 #define NFOC2_F1Z1                     (*(volatile uint16* )(NFOC2_BASE + (350*2)))     // RV:0000H IQREF filter parameter
 #define NFOC2_F1Z2                     (*(volatile uint16* )(NFOC2_BASE + (351*2)))     // RV:0000H IQREF filter parameter
 #define NFOC2_F1Y                      (*(volatile uint32* )(NFOC2_BASE + (352*2)))     // RV:0000H IQREF filter parameter
 #define NFOC2_F1YH                     (*(volatile uint16* )(NFOC2_BASE + (353*2)))     // RV:0000H IQREF filter parameter
 #define NFOC2_F1U1                     (*(volatile uint16* )(NFOC2_BASE + (416*2)))     // RV:0000H IQREF filter parameter
 #define NFOC2_F1U2                     (*(volatile uint16* )(NFOC2_BASE + (417*2)))     // RV:0000H IQREF filter parameter
 #define NFOC2_F1YG                     (*(volatile uint32* )(NFOC2_BASE + (424*2)))     // RV:0000H IQREF filter parameter      /* factory */
 #define NFOC2_F1YD                     (*(volatile uint32* )(NFOC2_BASE + (426*2)))     // RV:0000H IQREF filter parameter      /* factory */

 #define NFOC2_F2LB0                    (*(volatile uint16* )(NFOC2_BASE + (354*2)))     // RV:0000H IQREF filter parameter
 #define NFOC2_F2HB0                    (*(volatile uint16* )(NFOC2_BASE + (355*2)))     // RV:0000H IQREF filter parameter
 #define NFOC2_F2LB1                    (*(volatile uint16* )(NFOC2_BASE + (356*2)))     // RV:0000H IQREF filter parameter
 #define NFOC2_F2LB2                    (*(volatile uint16* )(NFOC2_BASE + (357*2)))     // RV:0000H IQREF filter parameter
 #define NFOC2_F2LA1                    (*(volatile uint16* )(NFOC2_BASE + (358*2)))     // RV:0000H IQREF filter parameter
 #define NFOC2_F2LA2                    (*(volatile uint16* )(NFOC2_BASE + (359*2)))     // RV:0000H IQREF filter parameter
 #define NFOC2_F2HB1                    (*(volatile uint16* )(NFOC2_BASE + (360*2)))     // RV:0000H IQREF filter parameter
 #define NFOC2_F2HB2                    (*(volatile uint16* )(NFOC2_BASE + (361*2)))     // RV:0000H IQREF filter parameter
 #define NFOC2_F2HA1                    (*(volatile uint16* )(NFOC2_BASE + (362*2)))     // RV:0000H IQREF filter parameter
 #define NFOC2_F2HA2                    (*(volatile uint16* )(NFOC2_BASE + (363*2)))     // RV:0000H IQREF filter parameter
 #define NFOC2_F2X0                     (*(volatile uint16* )(NFOC2_BASE + (364*2)))     // RV:0000H IQREF filter parameter
 #define NFOC2_F2X1                     (*(volatile uint16* )(NFOC2_BASE + (366*2)))     // RV:0000H IQREF filter parameter
 #define NFOC2_F2X2                     (*(volatile uint16* )(NFOC2_BASE + (367*2)))     // RV:0000H IQREF filter parameter
 #define NFOC2_F2Y1                     (*(volatile uint16* )(NFOC2_BASE + (368*2)))     // RV:0000H IQREF filter parameter
 #define NFOC2_F2Y2                     (*(volatile uint16* )(NFOC2_BASE + (369*2)))     // RV:0000H IQREF filter parameter
 #define NFOC2_F2Z1                     (*(volatile uint16* )(NFOC2_BASE + (370*2)))     // RV:0000H IQREF filter parameter
 #define NFOC2_F2Z2                     (*(volatile uint16* )(NFOC2_BASE + (371*2)))     // RV:0000H IQREF filter parameter
 #define NFOC2_F2HY                     (*(volatile uint32* )(NFOC2_BASE + (372*2)))     // RV:0000H IQREF filter parameter
 #define NFOC2_F2U1                     (*(volatile uint16* )(NFOC2_BASE + (418*2)))     // RV:0000H IQREF filter parameter
 #define NFOC2_F2U2                     (*(volatile uint16* )(NFOC2_BASE + (419*2)))     // RV:0000H IQREF filter parameter
 #define NFOC2_F2YG                     (*(volatile uint32* )(NFOC2_BASE + (428*2)))     // RV:0000H IQREF filter parameter      /* factory */
 #define NFOC2_F2YD                     (*(volatile uint32* )(NFOC2_BASE + (430*2)))     // RV:0000H IQREF filter parameter      /* factory */
 
 #define NFOC2_F3LB0                    (*(volatile uint16* )(NFOC2_BASE + (374*2)))     // RV:0000H IQREF filter parameter
 #define NFOC2_F3HB0                    (*(volatile uint16* )(NFOC2_BASE + (375*2)))     // RV:0000H IQREF filter parameter
 #define NFOC2_F3LB1                    (*(volatile uint16* )(NFOC2_BASE + (376*2)))     // RV:0000H IQREF filter parameter
 #define NFOC2_F3LB2                    (*(volatile uint16* )(NFOC2_BASE + (377*2)))     // RV:0000H IQREF filter parameter
 #define NFOC2_F3LA1                    (*(volatile uint16* )(NFOC2_BASE + (378*2)))     // RV:0000H IQREF filter parameter
 #define NFOC2_F3LA2                    (*(volatile uint16* )(NFOC2_BASE + (379*2)))     // RV:0000H IQREF filter parameter
 #define NFOC2_F3HB1                    (*(volatile uint16* )(NFOC2_BASE + (380*2)))     // RV:0000H IQREF filter parameter
 #define NFOC2_F3HB2                    (*(volatile uint16* )(NFOC2_BASE + (381*2)))     // RV:0000H IQREF filter parameter
 #define NFOC2_F3HA1                    (*(volatile uint16* )(NFOC2_BASE + (382*2)))     // RV:0000H IQREF filter parameter
 #define NFOC2_F3HA2                    (*(volatile uint16* )(NFOC2_BASE + (383*2)))     // RV:0000H IQREF filter parameter
 #define NFOC2_F3X0                     (*(volatile uint16* )(NFOC2_BASE + (384*2)))     // RV:0000H IQREF filter parameter
 #define NFOC2_F3X1                     (*(volatile uint16* )(NFOC2_BASE + (386*2)))     // RV:0000H IQREF filter parameter
 #define NFOC2_F3X2                     (*(volatile uint16* )(NFOC2_BASE + (387*2)))     // RV:0000H IQREF filter parameter
 #define NFOC2_F3Y1                     (*(volatile uint16* )(NFOC2_BASE + (388*2)))     // RV:0000H IQREF filter parameter
 #define NFOC2_F3Y2                     (*(volatile uint16* )(NFOC2_BASE + (389*2)))     // RV:0000H IQREF filter parameter
 #define NFOC2_F3Z1                     (*(volatile uint16* )(NFOC2_BASE + (390*2)))     // RV:0000H IQREF filter parameter
 #define NFOC2_F3Z2                     (*(volatile uint16* )(NFOC2_BASE + (391*2)))     // RV:0000H IQREF filter parameter
 #define NFOC2_F3HY                     (*(volatile uint32* )(NFOC2_BASE + (392*2)))     // RV:0000H IQREF filter parameter
 #define NFOC2_F3U1                     (*(volatile uint16* )(NFOC2_BASE + (420*2)))     // RV:0000H IQREF filter parameter
 #define NFOC2_F3U2                     (*(volatile uint16* )(NFOC2_BASE + (421*2)))     // RV:0000H IQREF filter parameter
 #define NFOC2_F3YG                     (*(volatile uint32* )(NFOC2_BASE + (432*2)))     // RV:0000H IQREF filter parameter      /* factory */
 #define NFOC2_F3YD                     (*(volatile uint32* )(NFOC2_BASE + (434*2)))     // RV:0000H IQREF filter parameter      /* factory */
 
 #define NFOC2_F4LB0                    (*(volatile uint16* )(NFOC2_BASE + (394*2)))     // RV:0000H IQREF filter parameter
 #define NFOC2_F4HB0                    (*(volatile uint16* )(NFOC2_BASE + (395*2)))     // RV:0000H IQREF filter parameter
 #define NFOC2_F4LB1                    (*(volatile uint16* )(NFOC2_BASE + (396*2)))     // RV:0000H IQREF filter parameter
 #define NFOC2_F4LB2                    (*(volatile uint16* )(NFOC2_BASE + (397*2)))     // RV:0000H IQREF filter parameter
 #define NFOC2_F4LA1                    (*(volatile uint16* )(NFOC2_BASE + (398*2)))     // RV:0000H IQREF filter parameter
 #define NFOC2_F4LA2                    (*(volatile uint16* )(NFOC2_BASE + (399*2)))     // RV:0000H IQREF filter parameter
 #define NFOC2_F4HB1                    (*(volatile uint16* )(NFOC2_BASE + (400*2)))     // RV:0000H IQREF filter parameter
 #define NFOC2_F4HB2                    (*(volatile uint16* )(NFOC2_BASE + (401*2)))     // RV:0000H IQREF filter parameter
 #define NFOC2_F4HA1                    (*(volatile uint16* )(NFOC2_BASE + (402*2)))     // RV:0000H IQREF filter parameter
 #define NFOC2_F4HA2                    (*(volatile uint16* )(NFOC2_BASE + (403*2)))     // RV:0000H IQREF filter parameter
 #define NFOC2_F4X0                     (*(volatile uint16* )(NFOC2_BASE + (404*2)))     // RV:0000H IQREF filter parameter
 #define NFOC2_F4X1                     (*(volatile uint16* )(NFOC2_BASE + (406*2)))     // RV:0000H IQREF filter parameter
 #define NFOC2_F4X2                     (*(volatile uint16* )(NFOC2_BASE + (407*2)))     // RV:0000H IQREF filter parameter
 #define NFOC2_F4Y1                     (*(volatile uint16* )(NFOC2_BASE + (408*2)))     // RV:0000H IQREF filter parameter
 #define NFOC2_F4Y2                     (*(volatile uint16* )(NFOC2_BASE + (409*2)))     // RV:0000H IQREF filter parameter
 #define NFOC2_F4Z1                     (*(volatile uint16* )(NFOC2_BASE + (410*2)))     // RV:0000H IQREF filter parameter
 #define NFOC2_F4Z2                     (*(volatile uint16* )(NFOC2_BASE + (411*2)))     // RV:0000H IQREF filter parameter
 #define NFOC2_F4HY                     (*(volatile uint32* )(NFOC2_BASE + (412*2)))     // RV:0000H IQREF filter parameter
 #define NFOC2_F4U1                     (*(volatile uint16* )(NFOC2_BASE + (422*2)))     // RV:0000H IQREF filter parameter
 #define NFOC2_F4U2                     (*(volatile uint16* )(NFOC2_BASE + (423*2)))     // RV:0000H IQREF filter parameter
 #define NFOC2_F4YG                     (*(volatile uint32* )(NFOC2_BASE + (436*2)))     // RV:0000H IQREF filter parameter      /* factory */
 #define NFOC2_F4YD                     (*(volatile uint32* )(NFOC2_BASE + (438*2)))     // RV:0000H IQREF filter parameter      /* factory */

 #define NFOC2_XI0                      (*(volatile  int16* )(NFOC2_BASE + (24*2)))     // RV:0000H CORDIC4 SIN/COS Xaxisinput
 #define NFOC2_YI0                      (*(volatile  int16* )(NFOC2_BASE + (25*2)))     // RV:0000H CORDIC4 SIN/COS yaxisinput
 #define NFOC2_THETA0                   (*(volatile  int16* )(NFOC2_BASE + (27*2)))     // RV:0000H CORDIC4 SIN/COS angle input
 #define NFOC2_XO0                      (*(volatile  int16* )(NFOC2_BASE + (28*2)))     // RV:0000H CORDIC4 SIN/COS Xaxis output
 #define NFOC2_YO0                      (*(volatile  int16* )(NFOC2_BASE + (29*2)))     // RV:0000H CORDIC4 SIN/COS yaxis output
 #define NFOC2_XI1                      (*(volatile  int16* )(NFOC2_BASE + (30*2)))     // RV:0000H CORDIC5 SIN/COS Xaxisinput
 #define NFOC2_YI1                      (*(volatile  int16* )(NFOC2_BASE + (31*2)))     // RV:0000H CORDIC5 SIN/COS yaxisinput
 #define NFOC2_THETA1                   (*(volatile  int16* )(NFOC2_BASE + (33*2)))     // RV:0000H CORDIC5 SIN/COS angle input
 #define NFOC2_XO51                     (*(volatile  int16* )(NFOC2_BASE + (34*2)))     // RV:0000H CORDIC5 SIN/COS Xaxis output
 #define NFOC2_YO1                      (*(volatile  int16* )(NFOC2_BASE + (35*2)))     // RV:0000H CORDIC5 SIN/COS yaxis output
 #define NFOC2_XI2                      (*(volatile  int16* )(NFOC2_BASE + (36*2)))     // RV:0000H CORDIC6 ATAN Xaxisinput
 #define NFOC2_YI2                      (*(volatile  int16* )(NFOC2_BASE + (37*2)))     // RV:0000H CORDIC6 ATAN yaxisinput
 #define NFOC2_US2                      (*(volatile  int16* )(NFOC2_BASE + (38*2)))     // RV:0000H CORDIC6 ATAN magnitudeoutput
 #define NFOC2_THETA2                   (*(volatile  int16* )(NFOC2_BASE + (39*2)))     // RV:0000H CORDIC6 ATAN angle output
 #define NFOC2_XI3                      (*(volatile  int16* )(NFOC2_BASE + (40*2)))     // RV:0000H CORDIC7 ATAN Xaxisinput
 #define NFOC2_YI3                      (*(volatile  int16* )(NFOC2_BASE + (41*2)))     // RV:0000H CORDIC7 ATAN yaxisinput
 #define NFOC2_US3                      (*(volatile  int16* )(NFOC2_BASE + (42*2)))     // RV:0000H CORDIC7 ATAN magnitudeoutput
 #define NFOC2_THETA3                   (*(volatile  int16* )(NFOC2_BASE + (43*2)))     // RV:0000H CORDIC7 ATAN angle output

 #define NFOC_PDCMD						(*(volatile  int16* )(NFOC2_BASE + (228*2)))     // RV:0000H PDFF target value
 #define NFOC_PDACT						(*(volatile  int16* )(NFOC2_BASE + (229*2)))     // RV:0000H PDFF feedback value
 #define NFOC_PDKP						(*(volatile  int16* )(NFOC2_BASE + (230*2)))     // RV:0000H PDFF coefficient KP
 #define NFOC_PDKI						(*(volatile  int16* )(NFOC2_BASE + (231*2)))     // RV:0000H PDFF coefficient KI
 #define NFOC_PDKF						(*(volatile  int16* )(NFOC2_BASE + (232*2)))     // RV:0000H PDFF coefficient KF
 #define NFOC_PDISAT					(*(volatile  int16* )(NFOC2_BASE + (233*2)))     // RV:0000H PDFF integral upper limit
 #define NFOC_PDITMP					(*(volatile  int32* )(NFOC2_BASE + (234*2)))     // RV:0000H PDFF integral value (32-bit)
 #define NFOC_PDMAX						(*(volatile  int16* )(NFOC2_BASE + (236*2)))     // RV:0000H PDFF output limit maximum
 #define NFOC_PDMIN						(*(volatile  int16* )(NFOC2_BASE + (237*2)))     // RV:0000H PDFF output limit minimum
 #define NFOC_PDUK						(*(volatile  int16* )(NFOC2_BASE + (238*2)))     // RV:0000H PDFF output

 #define NFOC_SFIN                      (*(volatile  int16* )(NFOC2_BASE + (240*2)))     // RV:0000H Velocity filter input
 #define NFOC_SFOUT						(*(volatile  int16* )(NFOC2_BASE + (241*2)))     // RV:0000H Velocity filter output

 #define NFOC_SLF1IN					(*(volatile  int16* )(NFOC2_BASE + (242*2)))     // RV:0000H LPF1 input
 #define NFOC_SLF1K						(*(volatile  int16* )(NFOC2_BASE + (243*2)))     // RV:0000H LPF1 coefficient
 #define NFOC_SLFLT1                    (*(volatile  int32* )(NFOC2_BASE + (244*2)))     // RV:0000H LPF1 output (32-bit)
 #define NFOC_SLF2IN					(*(volatile  int16* )(NFOC2_BASE + (246*2)))     // RV:0000H LPF2 input
 #define NFOC_SLF2K						(*(volatile  int16* )(NFOC2_BASE + (247*2)))     // RV:0000H LPF2 coefficient
 #define NFOC_SLFLT2                    (*(volatile  int32* )(NFOC2_BASE + (248*2)))     // RV:0000H LPF2 output (32-bit)


 #define NFOC_SMFPNT                    (*(volatile  uint8* )(NFOC2_BASE + (250*2)))     // RV:00H Moving average filter buffer index (8-bit)
 #define NFOC_SMFSIZE                   (*(volatile  uint8* )(NFOC2_BASE + (250*2+1)))   // RV:00H Moving average filter size (0~8)
 #define NFOC_SMFIN                     (*(volatile  int16* )(NFOC2_BASE + (251*2)))     // RV:0000H Moving average filter input
 #define NFOC_SMFSUM                    (*(volatile  int32* )(NFOC2_BASE + (252*2)))     // RV:0000H Moving average filter sum (32-bit)
 #define NFOC_SMFREM                    (*(volatile  int16* )(NFOC2_BASE + (254*2)))     // RV:0000H Moving average filter remainder
 #define NFOC_SMFOUT                    (*(volatile  int16* )(NFOC2_BASE + (255*2)))     // RV:0000H Moving average filter output
 #define NFOC_SMFARR0                   (*(volatile  int16* )(NFOC2_BASE + (256*2)))     // RV:0000H Moving average filter buffer0
 #define NFOC_SMFARR255                 (*(volatile  int16* )(NFOC2_BASE + (511*2)))     // RV:0000H Moving average filter buffer255
 

#endif
