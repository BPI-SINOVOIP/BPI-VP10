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
	clr_csr(PH_SEL, UT2CT1);		// UT2管脚使能选择 00：PA2-TX PA3-RX
	clr_csr(PH_SEL, UT2CT0);		// UT2管脚使能选择 01：PA5-TX PA4-RX	1x：PB2（单线模式IO，非单线O）

	clr_csr(PA_OE, PIN3);			// 输入使能
	set_csr(PA_PU, PIN3);			// 上拉电阻

	set_csr(UT2_CR0, UTREN);		// 0-->失能串行输入	1-->使能串行输入，软件清0;
	set_csr(UT2_CR0, UTEN);			// 0-->失能串行输出	1-->使能串行输出;

	clr_csr(UT2_CR0, UTMOD1);		// 模式选择 00：单线制半双工模式 8位	01：全/半双工模式 8位
	set_csr(UT2_CR0, UTMOD0);		// 模式选择 10：单线制半双工模式 9位	11：全/半双工模式 9位

	clr_csr(UT2_CR0, UTSM2);		// 0-->单机通讯			1-->多机通讯；
	clr_csr(UT2_CR0, UTRB8);		// 模式2/3下数据接收第9位，若SM2=0,作为停止位

	clr_csr(UT2_CR1, BAUDSEL);		// 波特率倍频使能 0-->Disable  1-->Enable

	clr_csr(UT2_CR1, CHKMOD1);		// 校验模式选择 00：手动模式TB9=0（8位模式时为不校验）	01：偶校验
	clr_csr(UT2_CR1, CHKMOD0);		// 校验模式选择	10：奇校验								11：手动模式TB9=1（8位模式时为不校验）

	clr_csr(UT2_CR0, UTTI | UTRI);	// 清收发中断标志位
	clr_csr(UT2_CR1, UTIE);			// UART2收发中断使能 0-->Disable	1-->Enable

#if (MCU_CLOCK == FREQ_48M)
	write_csr(UT2_BAUD, 0x0005);	// 波特率可设置 = 48000000/(16/(1+ UT_BAUD[BAUD_SEL]))/(UT_BAUD+1)
	// 0x0137-->9600 0x0019-->115200 0x000B-->250000 0x0005-->500000
#elif(MCU_CLOCK == FREQ_24M)
	write_csr(UT2_BAUD, 0x0002);	// 波特率可设置 = 24000000/(16/(1+ UT_BAUD[BAUD_SEL]))/(UT_BAUD+1)
	// 0x009B-->9600 0x000C-->115200 0x0005-->250000 0x0002-->500000
#endif
}


void UART1_Init(void)
{
	clr_csr(PH_SEL, UT1CT1);		// UT1管脚使能选择 00：PA0-TX PA1-RX
	clr_csr(PH_SEL, UT1CT0);		// UT1管脚使能选择 01：PA7-TX PA6-RX	1x：PA10-TX PA11-RX

	clr_csr(PA_OE, PIN1);			// 输入使能
	set_csr(PA_PU, PIN1);			// 上拉电阻

	set_csr(UT1_CR0, UTREN);		// 0-->失能串行输入	1-->使能串行输入，软件清0;
	set_csr(UT1_CR0, UTEN);			// 0-->失能串行输出	1-->使能串行输出;

	clr_csr(UT1_CR0, UTMOD1);		// 模式选择 00：单线制半双工模式 8位	01：全/半双工模式 8位
	set_csr(UT1_CR0, UTMOD0);		// 模式选择 10：单线制半双工模式 9位	11：全/半双工模式 9位

	clr_csr(UT1_CR0, UTSM2);		// 0-->单机通讯			1-->多机通讯；
	clr_csr(UT1_CR0, UTRB8);		// 模式2/3下数据接收第9位，若SM2=0,作为停止位

	clr_csr(UT1_CR1, BAUDSEL);		// 波特率倍频使能 0-->Disable  1-->Enable

	clr_csr(UT1_CR1, CHKMOD1);		// 校验模式选择 00：手动模式TB9=0（8位模式时为不校验）	01：偶校验
	clr_csr(UT1_CR1, CHKMOD0);		// 校验模式选择	10：奇校验								11：手动模式TB9=1（8位模式时为不校验）

	clr_csr(UT1_CR0, UTTI | UTRI);	// 清收发中断标志位
	clr_csr(UT1_CR1, UTIE);			// UART1收发中断使能 0-->Disable	1-->Enable

#if (MCU_CLOCK == FREQ_48M)
	write_csr(UT1_BAUD, 0x0005);	// 波特率可设置 = 48000000/(16/(1+ UT_BAUD[BAUD_SEL]))/(UT_BAUD+1)
	// 0x0137-->9600 0x0019-->115200 0x000B-->250000 0x0005-->500000
#elif(MCU_CLOCK == FREQ_24M)
	write_csr(UT1_BAUD, 0x0002);	// 波特率可设置 = 24000000/(16/(1+ UT_BAUD[BAUD_SEL]))/(UT_BAUD+1)
	// 0x009B-->9600 0x000C-->115200 0x0005-->250000 0x0002-->500000
#endif
}

void UART1_Close(void)
{
	clr_csr(UT1_CR0, UTEN);			// 0-->失能串行输出	1-->使能串行输出;
	clr_csr(UT1_CR1, UTIE);			// UART1中断使能 0-->Disable	1-->Enable
}



void UART2_Close(void)
{
	clr_csr(UT2_CR0, UTEN);			// 0-->失能串行输出	1-->使能串行输出;
	clr_csr(UT2_CR1, UTIE);			// UART1中断使能0-->Disable  1-->Enable
}

void UART1_Clear(void)
{
	clr_csr(UT1_CR0, UTTI); // 清标志位
	clr_csr(UT1_CR0, UTRI);
}

void UART2_Clear(void)
{
	clr_csr(UT2_CR0, UTTI); // 清标志位
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
	write_csr(UT2_BAUD, Baud);		// 波特率可设置 = 24000000/(16/(1+ UT_BAUD[BAUD_SEL]))/(UT_BAUD+1)
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
	UART_ANO.T_DATA[UART_ANO.Length++] = 0xAA;              //帧头
	UART_ANO.T_DATA[UART_ANO.Length++] = 0x05;              //客户端随便定义
	UART_ANO.T_DATA[UART_ANO.Length++] = 0xAF;              //AF表示匿名上位机
	UART_ANO.T_DATA[UART_ANO.Length++] = 0xF1;
	UART_ANO.T_DATA[UART_ANO.Length++] = 0;                 // 初始化长度值，结束需要重新赋值

	//////*********************** Move Test *********************************////
	// CH1
	uChange.m_w = 0x0001; // QEP.PosDiff;
	UART_ANO.T_DATA[UART_ANO.Length++] = uChange.m_uc[1];
	UART_ANO.T_DATA[UART_ANO.Length++] = uChange.m_uc[0];

	// CH2
	uChange.m_w = 0x0203; // QEP.PosDiffSum;
	UART_ANO.T_DATA[UART_ANO.Length++] = uChange.m_uc[1];
	UART_ANO.T_DATA[UART_ANO.Length++] = uChange.m_uc[0];

	// CH3
	uChange.m_w = 0x0405; // usSRegInBuf[ACTVEL];
	UART_ANO.T_DATA[UART_ANO.Length++] = uChange.m_uc[1];
	UART_ANO.T_DATA[UART_ANO.Length++] = uChange.m_uc[0];

	// CH4
	uChange.m_w = 0x0607; // QEP.PosDiffArray[QEP.ArrayPointer];
	UART_ANO.T_DATA[UART_ANO.Length++] = uChange.m_uc[1];
	UART_ANO.T_DATA[UART_ANO.Length++] = uChange.m_uc[0];


	UART_ANO.T_DATA[4] = UART_ANO.Length - 5;                 // 重新将长度给正确值
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
	UART_ANO.T_DATA[UART_ANO.Length++] = 0xAA;              //帧头
	UART_ANO.T_DATA[UART_ANO.Length++] = 0x05;              //客户端随便定义
	UART_ANO.T_DATA[UART_ANO.Length++] = 0xAF;              //AF表示匿名上位机
	UART_ANO.T_DATA[UART_ANO.Length++] = 0xF1;
	UART_ANO.T_DATA[UART_ANO.Length++] = UARTDATALEN;   // 初始化长度值，结束需要重新赋值

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