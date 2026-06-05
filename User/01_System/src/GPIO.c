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
    clr_csr(IN1_OE, IN1_PIN);  // 输入使能	/* 0: Disable digital output */
    set_csr(IN1_PU, IN1_PIN);  				/* 0: Disable internal pull up */
#endif

    // IN2
#ifdef IN2_PIN
    clr_csr(IN2_OE, IN2_PIN);  // 输入使能	/* 0: Disable digital output */
    set_csr(IN2_PU, IN2_PIN);  				/* 0: Disable internal pull up */
#endif
    
    // IN3
#ifdef IN3_PIN
    clr_csr(IN3_OE, IN3_PIN);  // 输入使能	/* 0: Disable digital output */
    set_csr(IN3_PU, IN3_PIN);  				/* 0: Disable internal pull up */
#endif
    
    // IN4
#ifdef IN4_PIN
    clr_csr(IN4_OE, IN4_PIN);  // 输入使能	/* 0: Disable digital output */
    set_csr(IN4_PU, IN4_PIN);  				/* 0: Disable internal pull up */
#endif
    
    // IN5
#ifdef IN5_PIN
    clr_csr(IN5_OE, IN5_PIN);  // 输入使能	/* 0: Disable digital output */
    set_csr(IN5_PU, IN5_PIN);  				/* 0: Disable internal pull up */
#endif
    
    // IN6
#ifdef IN6_PIN
    clr_csr(IN6_OE, IN6_PIN);  // 输入使能	/* 0: Disable digital output */
    set_csr(IN6_PU, IN6_PIN);  				/* 0: Disable internal pull up */
#endif
    
    // IN7
#ifdef IN7_PIN
    clr_csr(IN7_OE, IN7_PIN);  // 输入使能	/* 0: Disable digital output */
    set_csr(IN7_PU, IN7_PIN);  				/* 0: Disable internal pull up */
#endif
    
    // IN8
#ifdef IN8_PIN
    clr_csr(IN8_OE, IN8_PIN);  // 输入使能	/* 0: Disable digital output */
    set_csr(IN8_PU, IN8_PIN);  				/* 0: Disable internal pull up */
#endif
    
	// OUT1
#ifdef OUT1_PIN
    clr_csr(OUT1_GPIO, OUT1_PIN);
    set_csr(OUT1_OE, OUT1_PIN);		// 输出使能 /* 0: Enable digital output */
#endif
    
    // OUT2
#ifdef OUT2_PIN
    clr_csr(OUT2_GPIO, OUT2_PIN);
    set_csr(OUT2_OE, OUT2_PIN);		// 输出使能 /* 0: Enable digital output */
#endif   
    
    // OUT3
#ifdef OUT3_PIN
    clr_csr(OUT3_GPIO, OUT3_PIN);
    set_csr(OUT3_OE, OUT3_PIN);		// 输出使能 /* 0: Enable digital output */
#endif
    
    // OUT4
#ifdef OUT4_PIN
    clr_csr(OUT4_GPIO, OUT4_PIN);
    set_csr(OUT4_OE, OUT4_PIN);		// 输出使能 /* 0: Enable digital output */
#endif
    
    // OUT5
#ifdef OUT5_PIN
    clr_csr(OUT5_GPIO, OUT5_PIN);
    set_csr(OUT5_OE, OUT5_PIN);		// 输出使能 /* 0: Enable digital output */
#endif
    
    // OUT6
#ifdef OUT6_PIN
    clr_csr(OUT6_GPIO, OUT6_PIN);
    set_csr(OUT6_OE, OUT6_PIN);		// 输出使能 /* 0: Enable digital output */
#endif

    // FAN风扇 
#ifdef FAN_PIN
    set_csr(FAN_GPIO, FAN_PIN);		// 输出使能 /* 0: Enable digital output */
    set_csr(FAN_OE, FAN_PIN);
#endif

    // RELAY软启动
#ifdef RELAY_PIN
    set_csr(RELAY_GPIO, RELAY_PIN);		// 输出使能 /* 0: Enable digital output */
    set_csr(RELAY_OE, RELAY_PIN);
#endif
    
    // STO
#ifdef STO_PIN
    clr_csr(STO_OE, STO_PIN);		// 输入使能 /* 0: Disable digital output */
    clr_csr(STO_PU, STO_PIN);  					/* 0: Disable internal pull up */
#endif
    
    // Error
#ifdef ERR_PIN
    clr_csr(ERR_GPIO, ERR_PIN);		// 输出使能 /* 0: Enable digital output */
    set_csr(ERR_OE, ERR_PIN);
#endif
    
   // 上电显示 
#ifdef PWD_PIN 
    set_csr(PWD_GPIO, PWD_PIN);		// 输出使能 /* 0: Enable digital output */
    set_csr(PWD_OE, PWD_PIN);
#endif


#if TESTPIN_ENABLED
    // 测试脚输出：载波中断
    set_csr(TEST_GPIO, TEST_PIN);
    set_csr(TEST_OE, TEST_PIN);

	// 测试脚1：1ms循环
    set_csr(TEST_GPIO1, TEST_PIN1);
    set_csr(TEST_OE1, TEST_PIN1);

	// 测试脚2：位置环中断
    set_csr(TEST_GPIO2, TEST_PIN2);
    set_csr(TEST_OE2, TEST_PIN2);
#endif // #if TESTPIN_ENABLED
}


/*******************************************************************************
 * Function Name  : GPIO_PU_Init
 * Description    : 为提高芯片的抗干扰能力，降低芯片功耗，请在具体项目时，将不需要用的GPIO默认都配置为输入上拉。
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
 * Description    : FO硬件过流
 * Input          : None
 * Output         : None
 * Return         : None
 *******************************************************************************/
void EXTI0_Init(void)
{
	clr_csr(HOV_OE, HOV_PIN);				// 配置PD0为输入，硬件过流FO端口
	set_csr(HOV_PU, HOV_PIN);				// 使能上拉

	write_csr(EXT0IE, EX0IE13);			// 使能PD0作为外部中断0端口
	clr_csr(EXT0IF, EX0IF13);			// 清除PD0外部中断0标志

	clr_csr(TCON, IT01);				// 00-->Rising	01-->Falling
	set_csr(TCON, IT00);				// 1x-->Rising&Falling

	write_csr(IP1, FO_INT_PRI);				// 外部中断0(中断号1) 优先级别为7

	set_csr(PIE, EX0);					// INT0中断使能
}
#endif

/*******************************************************************************
 * Function Name  : EXTI1_Init
 * Description    : EtherCAT同步信号中断
 * Input          : None
 * Output         : None
 * Return         : None
 *******************************************************************************/
void EXTI1_Init(void)
{
	set_csr(ME_CR, INTCD);	// 外部中断1清零DRV计数，用于EtherCAT同步
	
	clr_csr(PA_OE, PIN8);				// 配置PA8为输入，ECAT同步信号SYNC0
	set_csr(PA_PU, PIN8);				// 使能上拉

	write_csr(EXT1IE, EX1IE8);			// 使能PA8作为外部中断1端口
	clr_csr(EXT1IF, EX1IF8);			// 清除PA8外部中断1标志

	clr_csr(TCON, IT11);				// 00-->Rising	01-->Falling
	set_csr(TCON, IT10);				// 1x-->Rising&Falling

	write_csr(IP2, EXTERN1_INT_PRI);				// 外部中断1(中断号2) 优先级别为6

	set_csr(PIE, EX1);					// INT1中断使能
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
	write_csr(EXT1IE, 0x00);		// 取消PA8作为外部中断1端口
	clr_csr(PIE, EX1);				// INT1中断去使能
}

#if ((HardwareCurrent_Protect == Hardware_FO_Protect) || (HardwareCurrent_Protect == Hardware_FO_CMP_Protect))
/*******************************************************************************
 * Function Name  : EXTI2_Init
 * Description    : FO硬件过流
 * Input          : None
 * Output         : None
 * Return         : None
 *******************************************************************************/
void EXTI2_Init(void)
{
	clr_csr(HOV_OE, HOV_PIN);				// 配置PC2为输入，硬件过流FO端口
	set_csr(HOV_PU, HOV_PIN);				// 使能上拉

	write_csr(EXT2IE, EX2IE10);			// 使能PC2作为外部中断2端口
	clr_csr(EXT2IF, EX2IE10);			// 清除PC2外部中断2标志

	clr_csr(TCON, IT21);				// 00-->Rising	01-->Falling
	set_csr(TCON, IT20);				// 1x-->Rising&Falling

	write_csr(IP3, FO_INT_PRI);				// 外部中断2(中断号3) 优先级别为7

	set_csr(PIE, EX2);					// INT2中断使能
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