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
	//	/*****DAC0 port configuration 9bit******/
	//	set_csr(P2_AN , P26);	//DAC0 port initialized to P26
	//	set_csr(P2_OE , P26);
	//
	//	/*****DAC1 port configuration 6bit******/
	//	set_csr(P2_AN , P23);	//DAC1 port initialized to P23
	//	set_csr(P2_OE , P23);
	//
	//	/*****DAC2 port configuration 8bit******/
	//	set_csr(P1_AN , P15);	//DAC2 port initialized to P15
	//	set_csr(P1_OE , P15);

	//	/*****DAC0&1/2 configuration******/
	//	clr_csr(DAC_CR , 0x40);	//0-->Normal mode (negative terminal is VSS)  1-->Half-voltage mode (negative terminal is VHALF)
	//	write_csr(DAC_DR0 , 0x1ff);	//VREF 9Bit
	//	write_csr(DAC_DR1 , 0x3f);	//VREF 6Bit
	//	write_csr(DAC_DR2 , 0xff);	//5V REF 8Bit
	//	set_csr(DAC_CR , 0x80);
	//	set_csr(DAC_CR , 0x02);
}