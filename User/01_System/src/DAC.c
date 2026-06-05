/*
 * Copyright (c) 2022-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : DAC.c
 * Author        : Fortior Application Team
 * Date          : 2022-09-21
 * Description   : define DAC
 *
 * Record        :
 * V1.0, 2022-09-21, Fortior Application Team: Created file
 */

#include "DAC.h"

void DAC_Init(void)
{
	//	/*****DAC0端口 配置9bit******/
	//	set_csr(P2_AN , P26);	//DAC0 端口初始化为P26
	//	set_csr(P2_OE , P26);
	//
	//	/*****DAC1端口 配置6bit******/
	//	set_csr(P2_AN , P23);	//DAC1 端口初始化为P23
	//	set_csr(P2_OE , P23);
	//
	//	/*****DAC2端口 配置8bit******/
	//	set_csr(P1_AN , P15);	//DAC2 端口初始化为P15
	//	set_csr(P1_OE , P15);

	//	/*****DAC0&1/2 配置******/
	//	clr_csr(DAC_CR , 0x40);	//0-->正常模式(负端为VSS)  1-->半电压模式(负端为VHALF)
	//	write_csr(DAC_DR0 , 0x1ff);	//VREF 9Bit
	//	write_csr(DAC_DR1 , 0x3f);	//VREF 6Bit
	//	write_csr(DAC_DR2 , 0xff);	//5V REF 8Bit
	//	set_csr(DAC_CR , 0x80);
	//	set_csr(DAC_CR , 0x02);
}