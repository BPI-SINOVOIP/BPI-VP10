/*
 * Copyright (c) 2022-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : GPIO.c
 * Author        : Fortior Application Team
 * Date          : 2022-09-21
 * Description   : define GPIO
 *
 * Record        :
 * V1.0, 2022-09-21, Fortior Application Team: Created file
 */


#include <Myproject.h>

void GPIO_Init(void)
{
	// IN1
#ifdef IN1_PIN
    clr_csr(IN1_OE, IN1_PIN);  // Input enable	/* 0: Disable digital output */
    set_csr(IN1_PU, IN1_PIN);  				/* 0: Disable internal pull up */
#endif

    // IN2
#ifdef IN2_PIN
    clr_csr(IN2_OE, IN2_PIN);  // Input enable	/* 0: Disable digital output */
    set_csr(IN2_PU, IN2_PIN);  				/* 0: Disable internal pull up */
#endif
    
    // IN3
#ifdef IN3_PIN
    clr_csr(IN3_OE, IN3_PIN);  // Input enable	/* 0: Disable digital output */
    set_csr(IN3_PU, IN3_PIN);  				/* 0: Disable internal pull up */
#endif
    
    // IN4
#ifdef IN4_PIN
    clr_csr(IN4_OE, IN4_PIN);  // Input enable	/* 0: Disable digital output */
    set_csr(IN4_PU, IN4_PIN);  				/* 0: Disable internal pull up */
#endif
    
    // IN5
#ifdef IN5_PIN
    clr_csr(IN5_OE, IN5_PIN);  // Input enable	/* 0: Disable digital output */
    set_csr(IN5_PU, IN5_PIN);  				/* 0: Disable internal pull up */
#endif
    
    // IN6
#ifdef IN6_PIN
    clr_csr(IN6_OE, IN6_PIN);  // Input enable	/* 0: Disable digital output */
    set_csr(IN6_PU, IN6_PIN);  				/* 0: Disable internal pull up */
#endif
    
    // IN7
#ifdef IN7_PIN
    clr_csr(IN7_OE, IN7_PIN);  // Input enable	/* 0: Disable digital output */
    set_csr(IN7_PU, IN7_PIN);  				/* 0: Disable internal pull up */
#endif
    
    // IN8
#ifdef IN8_PIN
    clr_csr(IN8_OE, IN8_PIN);  // Input enable	/* 0: Disable digital output */
    set_csr(IN8_PU, IN8_PIN);  				/* 0: Disable internal pull up */
#endif
    
	// OUT1
#ifdef OUT1_PIN
    clr_csr(OUT1_GPIO, OUT1_PIN);
    set_csr(OUT1_OE, OUT1_PIN);		// Output enable /* 0: Enable digital output */
#endif
    
    // OUT2
#ifdef OUT2_PIN
    clr_csr(OUT2_GPIO, OUT2_PIN);
    set_csr(OUT2_OE, OUT2_PIN);		// Output enable /* 0: Enable digital output */
#endif   
    
    // OUT3
#ifdef OUT3_PIN
    clr_csr(OUT3_GPIO, OUT3_PIN);
    set_csr(OUT3_OE, OUT3_PIN);		// Output enable /* 0: Enable digital output */
#endif
    
    // OUT4
#ifdef OUT4_PIN
    clr_csr(OUT4_GPIO, OUT4_PIN);
    set_csr(OUT4_OE, OUT4_PIN);		// Output enable /* 0: Enable digital output */
#endif
    
    // OUT5
#ifdef OUT5_PIN
    clr_csr(OUT5_GPIO, OUT5_PIN);
    set_csr(OUT5_OE, OUT5_PIN);		// Output enable /* 0: Enable digital output */
#endif
    
    // OUT6
#ifdef OUT6_PIN
    clr_csr(OUT6_GPIO, OUT6_PIN);
    set_csr(OUT6_OE, OUT6_PIN);		// Output enable /* 0: Enable digital output */
#endif

    // FAN 
#ifdef FAN_PIN
    set_csr(FAN_GPIO, FAN_PIN);		// Output enable /* 0: Enable digital output */
    set_csr(FAN_OE, FAN_PIN);
#endif

    // RELAY soft start
#ifdef RELAY_PIN
    set_csr(RELAY_GPIO, RELAY_PIN);		// Output enable /* 0: Enable digital output */
    set_csr(RELAY_OE, RELAY_PIN);
#endif
    
    // STO
#ifdef STO_PIN
    clr_csr(STO_OE, STO_PIN);		// Input enable /* 0: Disable digital output */
    clr_csr(STO_PU, STO_PIN);  					/* 0: Disable internal pull up */
#endif
    
    // Error
#ifdef ERR_PIN
    clr_csr(ERR_GPIO, ERR_PIN);		// Output enable /* 0: Enable digital output */
    set_csr(ERR_OE, ERR_PIN);
#endif
    
   // Power-on display 
#ifdef PWD_PIN 
    set_csr(PWD_GPIO, PWD_PIN);		// Output enable /* 0: Enable digital output */
    set_csr(PWD_OE, PWD_PIN);
#endif


#if TESTPIN_ENABLED
    // Test pin output: carrier interruption
    set_csr(TEST_GPIO, TEST_PIN);
    set_csr(TEST_OE, TEST_PIN);

	// Test pin 1: 1ms loop
    set_csr(TEST_GPIO1, TEST_PIN1);
    set_csr(TEST_OE1, TEST_PIN1);

	// Test pin 2: position loop interruption
    set_csr(TEST_GPIO2, TEST_PIN2);
    set_csr(TEST_OE2, TEST_PIN2);
#endif // #if TESTPIN_ENABLED
}


/*******************************************************************************
 * Function Name  : GPIO_PU_Init
 * Description    : To improve the chip's anti-interference ability and reduce power consumption, please configure all unused GPIOs to input pull-up by default in specific projects.
 * Input          : None
 * Output         : None
 * Return         : None
 *******************************************************************************/
void GPIO_PU_Init(void)
{
	uint16 temp;
	temp = read_csr(PA_OE);
	write_csr(PA_PU, ~temp);
	temp = read_csr(PB_OE);
	write_csr(PB_PU, ~temp);
	temp = read_csr(PC_OE);
	write_csr(PC_PU, ~temp);
	temp = read_csr(PD_OE);
	write_csr(PD_PU, ~temp);
}

#if ((HardwareCurrent_Protect == Hardware_FO_Protect) || (HardwareCurrent_Protect == Hardware_FO_CMP_Protect))
/*******************************************************************************
 * Function Name  : EXTI0_Init
 * Description    : FO hardware overcurrent
 * Input          : None
 * Output         : None
 * Return         : None
 *******************************************************************************/
void EXTI0_Init(void)
{
	clr_csr(HOV_OE, HOV_PIN);				// Configure PD0 as input, hardware overcurrent FO port
	set_csr(HOV_PU, HOV_PIN);				// Enable pull-up

	write_csr(EXT0IE, EX0IE13);			// Enable PD0 as external interrupt 0 port
	clr_csr(EXT0IF, EX0IF13);			// Clear PD0 external interrupt 0 flag

	clr_csr(TCON, IT01);				// 00-->Rising	01-->Falling
	set_csr(TCON, IT00);				// 1x-->Rising&Falling

	write_csr(IP1, FO_INT_PRI);				// External interrupt 0 (interrupt number 1) priority level is 7

	set_csr(PIE, EX0);					// INT0 interrupt enable
}
#endif

/*******************************************************************************
 * Function Name  : EXTI1_Init
 * Description    : EtherCAT synchronization signal interrupt
 * Input          : None
 * Output         : None
 * Return         : None
 *******************************************************************************/
void EXTI1_Init(void)
{
	set_csr(ME_CR, INTCD);	// External interrupt 1 clears DRV count, used for EtherCAT synchronization
	
	clr_csr(PA_OE, PIN8);				// Configure PA8 as input, ECAT synchronization signal SYNC0
	set_csr(PA_PU, PIN8);				// Enable pull-up

	write_csr(EXT1IE, EX1IE8);			// Enable PA8 as external interrupt 1 port
	clr_csr(EXT1IF, EX1IF8);			// Clear PA8 external interrupt 1 flag

	clr_csr(TCON, IT11);				// 00-->Rising	01-->Falling
	set_csr(TCON, IT10);				// 1x-->Rising&Falling

	write_csr(IP2, EXTERN1_INT_PRI);				// External interrupt 1 (interrupt number 2) priority level is 6

	set_csr(PIE, EX1);					// INT1 interrupt enable
}


/*******************************************************************************
 * Function Name  : EXTI1_Clear
 * Description    : P11
 * Input          : None
 * Output         : None
 * Return         : None
 *******************************************************************************/
void EXTI1_Clear(void)
{
	write_csr(EXT1IE, 0x00);		// Disable PA8 as external interrupt 1 port
	clr_csr(PIE, EX1);				// INT1 interrupt disable
}

#if ((HardwareCurrent_Protect == Hardware_FO_Protect) || (HardwareCurrent_Protect == Hardware_FO_CMP_Protect))
/*******************************************************************************
 * Function Name  : EXTI2_Init
 * Description    : FO hardware overcurrent
 * Input          : None
 * Output         : None
 * Return         : None
 *******************************************************************************/
void EXTI2_Init(void)
{
	clr_csr(HOV_OE, HOV_PIN);				// Configure PC2 as input, hardware overcurrent FO port
	set_csr(HOV_PU, HOV_PIN);				// Enable pull-up

	write_csr(EXT2IE, EX2IE10);			// Enable PC2 as external interrupt 2 port
	clr_csr(EXT2IF, EX2IE10);			// Clear PC2 external interrupt 2 flag

	clr_csr(TCON, IT21);				// 00-->Rising	01-->Falling
	set_csr(TCON, IT20);				// 1x-->Rising&Falling

	write_csr(IP3, FO_INT_PRI);				// External interrupt 2 (interrupt number 3) priority level is 7

	set_csr(PIE, EX2);					// INT2 interrupt enable
}
#endif

/*---------------------------------------------------------------------------*/
/* Name		:	void Delay_ms(void)
/* Input	:	ms, unit: ms.
/* Output	:	NO
/* Description:	Delay n ms.
/*---------------------------------------------------------------------------*/
void Delay_ms(int8 ms)
{
	uint8 i, j;
	for (; ms > 0; ms--)
	{
		for (i = 51; i > 0; i--)
		{
			for (j = 100; j > 0; j--)
			{
				asm volatile("nop");
			}
		}
	}
}


/*---------------------------------------------------------------------------*/
/* Name		:	void Delay_us(void)
/* Input	:	us, unit: us.
/* Output	:	NO
/* Description:	Delay n us.
/*---------------------------------------------------------------------------*/
void Delay_us(int8 us)
{
	for (; us > 0; us--)
	{
		asm volatile("nop");
		asm volatile("nop");
		asm volatile("nop");
		asm volatile("nop");
		asm volatile("nop");
		asm volatile("nop");
		asm volatile("nop");
		asm volatile("nop");
		asm volatile("nop");
		asm volatile("nop");
		asm volatile("nop");
		asm volatile("nop");
		asm volatile("nop");
		asm volatile("nop");
		asm volatile("nop");
		asm volatile("nop");
		asm volatile("nop");
	}
}