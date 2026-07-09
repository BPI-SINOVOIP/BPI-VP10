/*
 * Copyright (c) 2022-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : UART.c
 * Author        : Fortior Application Team
 * Date          : 2022-09-21
 * Description   : define UART
 *
 * Record        :
 * V1.0, 2022-09-21, Fortior Application Team: Created file
 */

#include <Myproject.h>

TypeDef_Uart UART_ANO = { 0 };


void UART2_Init(void)
{
	clr_csr(PH_SEL, UT2CT1);		// UT2 pin enable selection 00: PA2-TX PA3-RX	1x: PB2 (Single-wire mode IO, non-single-wire O)
	clr_csr(PH_SEL, UT2CT0);		// UT2 pin enable selection 01: PA5-TX PA4-RX	11: PD3-TX PD0-RX(7502BC)

	set_csr(UT2_CR0, UTREN);		// 0--> Disable serial input	1--> Enable serial input, cleared by software;
	set_csr(UT2_CR0, UTEN);			// 0--> Disable serial output	1--> Enable serial output;

	clr_csr(UT2_CR0, UTMOD1);		// Mode selection 00: Single-wire half-duplex mode 8-bit	01: Full/half-duplex mode 8-bit
	set_csr(UT2_CR0, UTMOD0);		// Mode selection 10: Single-wire half-duplex mode 9-bit	11: Full/half-duplex mode 9-bit

	clr_csr(UT2_CR0, UTSM2);		// 0--> Single-machine communication			1--> Multi-machine communication;
	clr_csr(UT2_CR0, UTRB8);		// Bit 9 of received data in mode 2/3, if SM2=0, used as stop bit

	clr_csr(UT2_CR1, BAUDSEL);		// Baud rate frequency doubling enable 0--> Disable  1--> Enable

	clr_csr(UT2_CR1, CHKMOD1);		// Parity mode selection 00: Manual mode TB9=0 (no parity in 8-bit mode)	01: Even parity
	clr_csr(UT2_CR1, CHKMOD0);		// Parity mode selection 10: Odd parity								11: Manual mode TB9=1 (no parity in 8-bit mode)

	clr_csr(UT2_CR0, UTTI | UTRI);	// Clear TX/RX interrupt flags
	clr_csr(UT2_CR1, UTIE);			// UART2 TX/RX interrupt enable 0--> Disable	1--> Enable

#if (MCU_CLOCK == FREQ_48M)
	write_csr(UT2_BAUD, 0x0005);	// Baud rate can be set = 48000000/(16/(1+ UT_BAUD[BAUD_SEL]))/(UT_BAUD+1)
	// 0x0137-->9600 0x0019-->115200 0x000B-->250000 0x0005-->500000
#elif(MCU_CLOCK == FREQ_24M)
	write_csr(UT2_BAUD, 0x0002);	// Baud rate can be set = 24000000/(16/(1+ UT_BAUD[BAUD_SEL]))/(UT_BAUD+1)
	// 0x009B-->9600 0x000C-->115200 0x0005-->250000 0x0002-->500000
#endif
}


void UART1_Init(void)
{
	clr_csr(PH_SEL, UT1CT1);		// UT1 pin enable selection 00: PA0-TX PA1-RX
	clr_csr(PH_SEL, UT1CT0);		// UT1 pin enable selection 01: PA7-TX PA6-RX	1x: PA10-TX PA11-RX

	clr_csr(PA_OE, PIN1);			// Input enable
	set_csr(PA_PU, PIN1);			// Pull-up resistor

	set_csr(UT1_CR0, UTREN);		// 0--> Disable serial input	1--> Enable serial input, cleared by software;
	set_csr(UT1_CR0, UTEN);			// 0--> Disable serial output	1--> Enable serial output;

	clr_csr(UT1_CR0, UTMOD1);		// Mode selection 00: Single-wire half-duplex mode 8-bit	01: Full/half-duplex mode 8-bit
	set_csr(UT1_CR0, UTMOD0);		// Mode selection 10: Single-wire half-duplex mode 9-bit	11: Full/half-duplex mode 9-bit

	clr_csr(UT1_CR0, UTSM2);		// 0--> Single-machine communication			1--> Multi-machine communication;
	clr_csr(UT1_CR0, UTRB8);		// Bit 9 of received data in mode 2/3, if SM2=0, used as stop bit

	clr_csr(UT1_CR1, BAUDSEL);		// Baud rate frequency doubling enable 0--> Disable  1--> Enable

	clr_csr(UT1_CR1, CHKMOD1);		// Parity mode selection 00: Manual mode TB9=0 (no parity in 8-bit mode)	01: Even parity
	clr_csr(UT1_CR1, CHKMOD0);		// Parity mode selection 10: Odd parity								11: Manual mode TB9=1 (no parity in 8-bit mode)

	clr_csr(UT1_CR0, UTTI | UTRI);	// Clear TX/RX interrupt flags
	clr_csr(UT1_CR1, UTIE);			// UART1 TX/RX interrupt enable 0--> Disable	1--> Enable

#if (MCU_CLOCK == FREQ_48M)
	write_csr(UT1_BAUD, 0x0005);	// Baud rate can be set = 48000000/(16/(1+ UT_BAUD[BAUD_SEL]))/(UT_BAUD+1)
	// 0x0137-->9600 0x0019-->115200 0x000B-->250000 0x0005-->500000
#elif(MCU_CLOCK == FREQ_24M)
	write_csr(UT1_BAUD, 0x0002);	// Baud rate can be set = 24000000/(16/(1+ UT_BAUD[BAUD_SEL]))/(UT_BAUD+1)
	// 0x009B-->9600 0x000C-->115200 0x0005-->250000 0x0002-->500000
#endif
}

void UART1_Close(void)
{
	clr_csr(UT1_CR0, UTEN);			// 0--> Disable serial output	1--> Enable serial output;
	clr_csr(UT1_CR1, UTIE);			// UART1 interrupt enable 0--> Disable	1--> Enable
}



void UART2_Close(void)
{
	clr_csr(UT2_CR0, UTEN);			// 0--> Disable serial output	1--> Enable serial output;
	clr_csr(UT2_CR1, UTIE);			// UART1 interrupt enable 0--> Disable  1--> Enable
}

void UART1_Clear(void)
{
	clr_csr(UT1_CR0, UTTI); // Clear flag bit
	clr_csr(UT1_CR0, UTRI);
}

void UART2_Clear(void)
{
	clr_csr(UT2_CR0, UTTI); // Clear flag bit
	clr_csr(UT2_CR0, UTRI);
}

void PutByte(char c)
{
	write_csr(UT2_DR, c);
}


void GetByte(char* c)
{
	*c = read_csr(UT2_DR);
}


void UART2_UpdateBaud(uint16 Baud)
{
	write_csr(UT2_BAUD, Baud);		// Baud rate can be set = 24000000/(16/(1+ UT_BAUD[BAUD_SEL]))/(UT_BAUD+1)
}


union
{
	unsigned short m_w;
	unsigned char m_uc[2];
} uChange;

void UART_ANODubugerBuffConfig(void)
{
	uint8 i;
	uint16 Angle_Temp = 0;
	UART_ANO.Length = 0;
	UART_ANO.T_DATA[UART_ANO.Length++] = 0xAA;              // Frame header
	UART_ANO.T_DATA[UART_ANO.Length++] = 0x05;              // Freely defined by client
	UART_ANO.T_DATA[UART_ANO.Length++] = 0xAF;              // AF represents Anonymous Host Computer
	UART_ANO.T_DATA[UART_ANO.Length++] = 0xF1;
	UART_ANO.T_DATA[UART_ANO.Length++] = 0;                 // Initial length value, needs reassignment at the end

	//////*********************** Move Test *********************************////
	// CH1
	uChange.m_w = 0x0001; 
	UART_ANO.T_DATA[UART_ANO.Length++] = uChange.m_uc[1];
	UART_ANO.T_DATA[UART_ANO.Length++] = uChange.m_uc[0];

	// CH2
	uChange.m_w = 0x0203;
	UART_ANO.T_DATA[UART_ANO.Length++] = uChange.m_uc[1];
	UART_ANO.T_DATA[UART_ANO.Length++] = uChange.m_uc[0];

	// CH3
	uChange.m_w = 0x0405;
	UART_ANO.T_DATA[UART_ANO.Length++] = uChange.m_uc[1];
	UART_ANO.T_DATA[UART_ANO.Length++] = uChange.m_uc[0];

	// CH4
	uChange.m_w = 0x0607; 
	UART_ANO.T_DATA[UART_ANO.Length++] = uChange.m_uc[1];
	UART_ANO.T_DATA[UART_ANO.Length++] = uChange.m_uc[0];


	UART_ANO.T_DATA[4] = UART_ANO.Length - 5;                 // Re-assign correct value to length
	UART_ANO.CheckSum = 0;
	for (i = 0; i < UART_ANO.Length; i++)
	{
		UART_ANO.CheckSum += UART_ANO.T_DATA[i];
	}
	UART_ANO.T_DATA[UART_ANO.Length] = UART_ANO.CheckSum;

}


void UART_ANODubugerBuffInit(void)
{
	uint8 i;

	UART_ANO.Length = 0;
	UART_ANO.T_DATA[UART_ANO.Length++] = 0xAA;              // Frame header
	UART_ANO.T_DATA[UART_ANO.Length++] = 0x05;              // Freely defined by client
	UART_ANO.T_DATA[UART_ANO.Length++] = 0xAF;              // AF represents Anonymous Host Computer
	UART_ANO.T_DATA[UART_ANO.Length++] = 0xF1;
	UART_ANO.T_DATA[UART_ANO.Length++] = UARTDATALEN;   // Initial length value, needs reassignment at the end

	UART_ANO.CheckSumInit = 0;
	for (i = 0; i < UARTHEADLEN; i++)
	{
		UART_ANO.CheckSumInit += UART_ANO.T_DATA[i];
	}
}

void UART_ANODubugerBuffData(void)
{
	uint8 i;

	// CH1
	uChange.m_w = 0x0001;
	UART_ANO.T_DATA[5] = uChange.m_uc[1];
	UART_ANO.T_DATA[6] = uChange.m_uc[0];

	// CH2
	uChange.m_w = 0x0203;
	UART_ANO.T_DATA[7] = uChange.m_uc[1];
	UART_ANO.T_DATA[8] = uChange.m_uc[0];

	// CH3
	uChange.m_w = 0x0405;
	UART_ANO.T_DATA[9] = uChange.m_uc[1];
	UART_ANO.T_DATA[10] = uChange.m_uc[0];

	// CH4
	uChange.m_w = 0x0607;
	UART_ANO.T_DATA[11] = uChange.m_uc[1];
	UART_ANO.T_DATA[12] = uChange.m_uc[0];


	UART_ANO.CheckSum = UART_ANO.CheckSumInit;
	for (i = UARTHEADLEN; i < UARTDATALEN + UARTHEADLEN; i++)
	{
		UART_ANO.CheckSum += UART_ANO.T_DATA[i];
	}
	UART_ANO.T_DATA[UARTDATALEN + UARTHEADLEN] = UART_ANO.CheckSum;

}

void SendDataByUart()
{
	uint8 i;
	for (i = 0; i <= UART_ANO.Length; i++)
	{
#if(MODBUS_UART == 1)
		write_csr(UT1_DR, UART_ANO.T_DATA[i]);
		while (!readbit_csr(UT1_CR0, UTTI));
		clr_csr(UT1_CR0, UTTI);
#else
		write_csr(UT2_DR, UART_ANO.T_DATA[i]);
		while (!readbit_csr(UT2_CR0, UTTI));
		clr_csr(UT2_CR0, UTTI);
#endif
	}
}