/*
 * Copyright (c) 2023-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : EEPROM.c
 * Author        : Zougi.Zou
 * Date          : 2023-09-20
 * Description   : EEPROM read and write
 *
 * Record        :
 * V1.0, 2023-09-20, Zougi.Zou: Created file
 */

#include <Myproject.h>



/*---------------------------------------------------------------------------
 * Name          : DownloadDataToEEPROM
 * Input         : None
 * Output        : retValue-Whether successful
 * Description   : Download Holding Register to EEPROM
 *---------------------------------------------------------------------------*/
bool DownloadDataToEEPROM(void)
{
	uint8 ucAddress;
	USHORT usSRegHoldStartBuf[EEPROM_PNUM_ADDR_SIZE >> 1] = { 0 };

	bool retValue = EEPROM_WriteBytes(EEPROM_PARAM_ADDR_START, (uint8*) usSRegHoldBuf, EEPROM_PARAM_ADDR_SIZE);
	if (retValue == 1) // EEPROM write no error
	{
		memcpy(usSRegHoldStartBuf, usSRegHoldStartArray, (S_REG_HOLDING_INDEX_MAX + 1) << 1);
		retValue = EEPROM_WriteBytes(EEPROM_PNUM_ADDR_START, (uint8*) usSRegHoldStartBuf, EEPROM_PNUM_ADDR_SIZE);

#if COMM_CAN_ENABLED > 0 // Store ID number separately
		retValue = EEPROM_WriteBytes(EEPROM_ID_ADDR_START, (uint8*) & usSRegHoldBuf[COMMADDR], EEPROM_ID_ADDR_SIZE);
#endif
	}

	return retValue;
}

/*---------------------------------------------------------------------------
 * Name          : UploadDataFromEEPROM
 * Input         : None
 * Output        : retValue-Whether successful
 * Description   : Load data from EEPROM to Holding Register
 *---------------------------------------------------------------------------*/
bool UploadDataFromEEPROM(void)
{
	uint8 i = 0;
	USHORT usSRegHoldStartBuf[EEPROM_PNUM_ADDR_SIZE >> 1] = { 0 };
	bool retValue = EEPROM_ReadBytes(EEPROM_PNUM_ADDR_START, (uint8*) usSRegHoldStartBuf, EEPROM_PNUM_ADDR_SIZE);

	if (retValue == 1)// EEPROM read no error
	{
		if ((usSRegHoldStartBuf[1] == 0 && usSRegHoldStartBuf[2] == 0) || usSRegHoldStartBuf[0] != 0 ||
			usSRegHoldStartBuf[1] == 65535 || usSRegHoldStartBuf[2] == 65535)
		{
			retValue = EEPROM_ReadBytes(EEPROM_PARAM_ADDR_START, (uint8*) usSRegHoldBuf, EEPROM_PARAM_ADDR_SIZE);
		}	
		else
		{
			retValue = EEPROM_ReadRegister(EEPROM_PARAM_ADDR_START, usSRegHoldBuf, usSRegHoldStartArray, usSRegHoldStartBuf);
		}	
	}

	// Clear some variables that use rising edges
	usSRegHoldBuf[DRIVECTRL] = 0;
	usSRegHoldBuf[FLASHCTRL] = 0;
	usSRegHoldBuf[ENCCALCTRL] = 0;
	ClrBit(usSRegHoldBuf[SCOPECTRL], SCOPE_EN);
	ClrBit(usSRegHoldBuf[SCOPECTRL], SCOPE_START);
	ClrBit(usSRegHoldBuf[PROFILECTRL], PROF_MOTIONEN);

	return retValue;
}

/*---------------------------------------------------------------------------
 * Name		:	I2C_Master_WriteBytes()
 * Input	:	WordAddr - Start address for writing to EEPROM
 *				Addr - Device Address, *pData-pointer to data to write,
 *				NumByte - Number of bytes to write
 * Output	:	bool - false or true
 * Description:	I2C_Master_WriteBytes to slave
 *---------------------------------------------------------------------------*/
bool EEPROM_WriteBytes(uint16 WordAddr, uint8* pData, uint16 NumByte)
{
#if FUNC_SOFT_EEPROM_ENABLED
	return (AT24C16_Write_Array(WordAddr, pData, NumByte) == 1);
#else
	uint8 deviceaddr;
	uint16 wordaddr, page;
	uint8* pdata;
	bool retValue = false;
	uint8 rank, pagesize;
	wordaddr = WordAddr;
	pdata = pData;
	
#if FUNC_EEPROM_24C16B_SWITCH
	rank = 4;
#else
	rank = 6;
#endif
	pagesize = 1 << rank;

	for (page = 0; page < (NumByte >> rank); page++)
	{
#if FUNC_EEPROM_24C16B_SWITCH
		deviceaddr = EEPROM_DEV_ADDR | ((wordaddr >> 8) << 1);
#else
		deviceaddr = EEPROM_DEV_ADDR;
#endif
		
		retValue = I2C_Master_WriteBytes_Ext(deviceaddr, wordaddr, pdata, pagesize);
		wordaddr += pagesize;
		pdata += pagesize;
		Delay_ms(6);
		IWDT_Refresh(); // Promptly feed the watchdog timer
	}
	
#if FUNC_EEPROM_24C16B_SWITCH
	deviceaddr = EEPROM_DEV_ADDR | ((wordaddr >> 8) << 1);
#else
	deviceaddr = EEPROM_DEV_ADDR;
#endif
	retValue = I2C_Master_WriteBytes_Ext(deviceaddr, wordaddr, pdata, NumByte - ((NumByte >> rank) << rank));
	
	return retValue;
#endif
}

/*---------------------------------------------------------------------------
 * Name		:	EEPROM_ReadBytes()
 * Input	:	WordAddr - Start address for reading from EEPROM
 *				Addr - Device Address, *pData-pointer to data to write,
 *				NumByte - Number of bytes to read
 * Output	:	bool-false or true
 * Description:	I2C_Master_ReadBytes from slave
 *---------------------------------------------------------------------------*/
bool EEPROM_ReadBytes(uint16 WordAddr, uint8* pData, uint16 NumByte)
{
#if FUNC_SOFT_EEPROM_ENABLED
	return (AT24C16_Read_Array(WordAddr, pData, NumByte) == 1);
#else
	uint8 deviceaddr;
	bool retValue = false;	
	
#if FUNC_EEPROM_24C16B_SWITCH
	deviceaddr = EEPROM_DEV_ADDR | ((WordAddr >> 8) << 1);
#else
	deviceaddr = EEPROM_DEV_ADDR;
#endif
	 
	retValue = I2C_Master_WriteBytes_Ext(deviceaddr, WordAddr, pData, 0);
	if (!retValue)
		return retValue;

	retValue = I2C_Master_ReadBytes(deviceaddr, pData, NumByte, 1, 1);

	return retValue;
#endif
}

/*---------------------------------------------------------------------------
 * Name		:	EEPROM_ReadRegister()
 * Input	:	Addr - Device Address, 
 *				*pData - pointer to data to read,
 *				*pRegStartNew - RegHoldStartArray defined in code
 *				*pRegStartOld - RegHoldStartArray stored in EEPROM
 * Output	:	bool-false or true
 * Description:	Read Holding Register from EEPROM, here it is assumed that the new is always longer than the old
 *---------------------------------------------------------------------------*/
bool EEPROM_ReadRegister(uint16 WordAddr, uint16* pData, uint16* pRegStartNew, uint16* pRegStartOld)
{
#if FUNC_SOFT_EEPROM_ENABLED
	uint16 i = 0, j = 0;
	uint16 Data;
	int16 margin = 0;
	if (AT24C16_Read_Array_Step1(WordAddr) == 1)
	{
		for (i = 0; i < S_REG_HOLDING_INDEX_MAX; i++)
		{
			if (pRegStartOld[i + 1] <= pRegStartOld[i])
			{
				break;
			}
				
			for (j = 0; j < pRegStartOld[i + 1] - pRegStartOld[i]; j++)
			{
				if (AT24C16_Read_Array_Step2(&Data, 2, 1) == 0)
				{
					AT24C16_Read_Array_Step3();
					return 0;
				}
				
				if (j < pRegStartNew[i + 1] - pRegStartNew[i])
					*pData++ = Data;
			}
			margin = (int16)(pRegStartNew[i + 1] - pRegStartNew[i]) - (int16)(pRegStartOld[i + 1] - pRegStartOld[i]);
			if (margin > 0)
				pData = pData + margin;
		}
		AT24C16_Read_Array_Step2(&Data, 2, 0);
		AT24C16_Read_Array_Step3();
		return 1;
	}
	else
	{
		AT24C16_Read_Array_Step3();
		return 0;
	}
#else
	uint8 deviceaddr;

#if FUNC_EEPROM_24C16B_SWITCH
	deviceaddr = EEPROM_DEV_ADDR | ((WordAddr >> 8) << 1);
#else
	deviceaddr = EEPROM_DEV_ADDR;
#endif

	uint16 i = 0, j = 0;
	uint16 Data;
	int16 margin = 0;
	if (I2C_Master_WriteBytes_Ext(deviceaddr, WordAddr, pData, 0) == 1 && 
		I2C_Master_ReadBytes(deviceaddr, &Data, 0, 1, 0) == 1)
	{
		for (i = 0; i < S_REG_HOLDING_INDEX_MAX; i++)
		{
			if (pRegStartOld[i + 1] <= pRegStartOld[i])
			{
				break;
			}

			for (j = 0; j < pRegStartOld[i + 1] - pRegStartOld[i]; j++)
			{
				if (I2C_Master_ReadBytes(deviceaddr, &Data, 2, 0, 0) == 0)
				{
					I2C_Master_ReadBytes(deviceaddr, &Data, 0, 0, 1);
					return 0;
				}

				if (j < pRegStartNew[i + 1] - pRegStartNew[i])
					*pData++ = Data;
			}
			margin = (int16)(pRegStartNew[i + 1] - pRegStartNew[i]) - (int16)(pRegStartOld[i + 1] - pRegStartOld[i]);
			if (margin > 0)
				pData = pData + margin;
		}
		I2C_Master_ReadBytes(deviceaddr, &Data, 0, 0, 1);
		return 1;
	}
	else
	{
		I2C_Master_ReadBytes(deviceaddr, &Data, 0, 0, 1);
		return 0;
	}
#endif
}

/*---------------------------------------------------------------------------
 * Name		:	bool EEPROM_Check(void)
 * Input	:	NO
 * Output	:	NO
 * Description:	Check if EEPRPM read and write is correct, for test.
 *---------------------------------------------------------------------------*/
bool EEPROM_Check(void)
{
	bool retValue = false;
	uint8 ReadData[2] = { 0 }, WriteData[2] = { CHECK_KEY1, CHECK_KEY2 };

	EEPROM_ReadBytes(CHECK_ADDR, ReadData, 2);
	Delay_ms(10);

	if (ReadData[0] == CHECK_KEY1 && ReadData[1] == CHECK_KEY2)
	{
		retValue = true;
		return retValue;
	}
	else
	{
		EEPROM_WriteBytes(CHECK_ADDR, WriteData, 2);
		Delay_ms(10);
		EEPROM_ReadBytes(CHECK_ADDR, ReadData, 2);

		if (ReadData[0] == CHECK_KEY1 && ReadData[1] == CHECK_KEY2)
		{
			retValue = true;
			return retValue;
		}
	}
	return retValue;
}