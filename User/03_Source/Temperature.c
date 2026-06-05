/********************************************************************************
/*
 * Copyright (c) 2025-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : Temperature.c
 * Author        : Summer
 * Date          : 2025-09-05
 * Description   : 驱动器温度
 *
 * Record        :
 * V1.0, 2025-09-05, Summer: Created file
 */


#include <Myproject.h>

#if TEMPSRC_KNTC_ENABLED > 0

// 热敏电阻- KNTC0603 - 100KF3950: 0 degree : 324.899 Kohm; 分压电阻: 22 Kohm
// 324.899 / (324.899 + 22) * 4096 = 3836
const uint16 TempTable_KNTC100[TEMPTABLE_LEN] =
{
//	0		5		10		15		20
	3836, 3768, 3687, 3592, 3482,
//	25		30		35		40		45
	3356, 3216, 3062, 2896, 2720,
//	50		55		60		65		70
	2538, 2352, 2166, 1983, 1805,
//	75		80		85		90		95
	1635, 1474, 1325, 1187, 1060,
//	100		105		110		115		120
	946, 842, 749, 667, 593
};



/*---------------------------------------------------------------------------*/
/* Name		:	void TemperatureCalc(void)
/* Input	:	InputTempAD from ADC
/* Output	:	NO
/* Description:	Calculate Temperature of NTC by lookup table.
/*---------------------------------------------------------------------------*/
uint16 TemperatureCalc(uint16 InputTempAD)
{
	uint16* pTempTable;
	uint16 TempAD;
	uint16 TempCelsius;
	uint16 i, temp0, temp1;

	// 温度曲线的选定
	pTempTable = (uint16*) TempTable_KNTC100;

	// 硬件采样值修正
	TempAD = (InputTempAD >> 3);

	// 温度限幅
	if (TempAD >= pTempTable[0])
	{
		TempCelsius = 0;
	}
	else if (TempAD <= pTempTable[TEMPTABLE_LEN - 1])
	{
		TempCelsius = 1200;
	}
	else
	{
		// 开始查询温度表
		for (i = 0; i <= (TEMPTABLE_LEN - 1); i++)
		{
			if ((TempAD > pTempTable[i + 1]) && (TempAD <= pTempTable[i]))
			{
				break;
			}
		}

		//通过温度曲线，反推温度
		temp0 = pTempTable[i] - TempAD;
		temp1 = pTempTable[i] - pTempTable[i + 1];

		TempCelsius = temp0 * 50 / temp1 + i * 50;
	}

	return TempCelsius;
}

#else

// MCU内置温度传感器
const uint8 TempTable_TSD[TEMPTABLETSD_LEN] =
{
	//71   76    81    86    91
	0x3F, 0x44, 0x48, 0x4D, 0x51,
	//96   101   106   111  116
	0x55, 0x59, 0x5C, 0x5F, 0x63,
	//121  126   131  136   141
	0x66, 0x69, 0x6C, 0x70, 0x72,
	//146		
	0x75, 
};



/*---------------------------------------------------------------------------*/
/* Name		:	void TemperatureTSDCalc(void)
/* Input	:	NO
/* Output	:	NO
/* Description:	Calculate Temperature of MCU TSD by lookup table.
/*---------------------------------------------------------------------------*/
uint16 TemperatureCalc(uint16 InputTempAD)
{
	uint8* pTempTable;
	uint8 TempAD;
	uint16 TempCelsius;
	uint16 i, temp0, temp1;

	// 温度传感器使能
	set_csr(TSD_CR, TSEN_EN);
	set_csr(TSD_CR, TSD_EN);
	
	// 温度曲线的选定
	pTempTable = (uint8*) TempTable_TSD;

	// 硬件采样值
	TempAD = read_csr(TSEN_DR);

	// 温度限幅
	if (TempAD <= pTempTable[0])
	{
		TempCelsius = 710;
	}
	else if (TempAD >= pTempTable[TEMPTABLETSD_LEN - 1])
	{
		TempCelsius = 1460;
	}
	else
	{
		// 开始查询温度表
		for (i = 0; i <= (TEMPTABLETSD_LEN - 1); i++)
		{
			if ((TempAD < pTempTable[i + 1]) && (TempAD >= pTempTable[i]))
			{
				break;
			}
		}

		//通过温度曲线，反推温度
		temp0 = TempAD - pTempTable[i];
		temp1 = pTempTable[i + 1] - pTempTable[i];

		TempCelsius = temp0 * 50 / temp1 + i * 50 + 710;
	}

	return TempCelsius;
}
#endif // #if TEMPSRC_KNTC_ENABLED > 0