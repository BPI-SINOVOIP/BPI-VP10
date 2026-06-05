/*
 * Copyright (c) 2022-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : I2C.c
 * Author        : Fortior Application Team
 * Date          : 2022-09-21
 * Description   : define I2C read and write
 *
 * Record        :
 * V1.0, 2022-09-21, Fortior Application Team: Created file
 */

#include <Myproject.h>


/********************************************************************/
/*								I2C初始化							*/
/********************************************************************/
/* 函数名称：I2C_Init
 * 函数功能：I2C模块设置
 * 参数说明：
 * 注意事项：
 */
void I2C_Init(void)
{
	I2CConfiguration I2CConfig;

#if (SCL_GPIO == PA && SCL_PIN == PIN1)
	I2CConfig.PortSel = InitialPort; //功能转移，0-->PA0:SDA, PA1:SCL; 1-->不复用
#else
	I2CConfig.PortSel = TransferPort;
#endif
	
	I2CConfig.Mode = Master;
	I2CConfig.Baud = I2C_Speed_400K / 2;
	//	I2CConfig.ID = 0x50;
	I2CConfig.GCSel = Enable;
	I2CConfig.DataDirection = Data_Send;
	I2CConfig.Interrupt = Disable;
	I2CConfig.AutoDMA = Enable;
	I2CConfig.DMANackIgnore = Disable;

	I2C_Configuration(I2C, &I2CConfig);
}

void I2C_Configuration(uint8 I2CSel, I2CConfiguration* Config)
{
	if (I2CSel == I2C)
	{
		write_csr(I2C1_CR, 0);
		write_csr(I2C1_SR, 0);

		set_csr(I2C1_CR, Config->Mode << 6);
		set_csr(I2C1_CR, Config->Interrupt);
		set_csr(I2C1_CR, Config->AutoDMA << 3);
		set_csr(I2C1_CR, Config->DMANackIgnore << 4);
		write_csr(I2C1_BAUD, Config->Baud);

		set_csr(I2C1_SR, Config->DataDirection << 6);
		write_csr(I2C1_ID, (Config->ID & 0x7F) << 1);
		set_csr(I2C1_ID, Config->GCSel);

		clr_csr(PH_SEL, 1 << 20);
		set_csr(PH_SEL, (uint32)Config->PortSel << 20);

		set_csr(I2C1_CR, I2CEN);
	}
	else
	{
		write_csr(I2C2_CR, 0);
		write_csr(I2C2_SR, 0);

		set_csr(I2C2_CR, Config->Mode << 6);
		set_csr(I2C2_CR, Config->Interrupt);
		set_csr(I2C2_CR, Config->AutoDMA << 3);
		set_csr(I2C2_CR, Config->DMANackIgnore << 4);
		write_csr(I2C2_BAUD, Config->Baud);

		set_csr(I2C2_SR, Config->DataDirection << 6);
		write_csr(I2C2_ID, (Config->ID & 0x7F) << 1);
		set_csr(I2C2_ID, Config->GCSel);

		clr_csr(PH_SEL, 1 << 20);
		set_csr(PH_SEL, (uint32)Config->PortSel << 20);

		set_csr(I2C2_CR, I2CEN);
	}
}


/*---------------------------------------------------------------------------*/
/* Name		:	I2C_Master_WriteBytes()
/* Input	:	Addr-Device Address, *pData-pointer to data to write,
/*				NumByte-Number of bytes to write
/* Output	:	bool-false or true
/* Description:	I2C_Master_WriteBytes to slave
/*---------------------------------------------------------------------------*/
bool I2C_Master_WriteBytes(uint8 DevAddr, uint8* pData, uint16 NumByte)
{
	uint16 I2C_Counter = 0;
	uint8 I2C_Overtime = 255;
	bool retValue = false;

	clr_csr(I2C1_SR, DMOD);

	for (I2C_Counter = 0; I2C_Counter <= NumByte; I2C_Counter++)
	{
		if (I2C_Counter == 0)
		{
			write_csr(I2C1_ID, DevAddr);
			set_csr(I2C1_SR, I2CSTA);
		}
		else
		{
			write_csr(I2C1_DR, *pData++);
			clr_csr(I2C1_SR, STR);
		}

		I2C_Overtime = 255;
		while (!readbit_csr(I2C1_SR, STR))
		{
			if (I2C_Overtime-- == 0)
			{
				set_csr(I2C1_SR, I2CSTP);
				clr_csr(I2C1_SR, STR);
				return retValue;									//接收数据异常
			}
		}

		if (readbit_csr(I2C1_SR, NACK))
		{
			break;										//接收数据异常
		}
	}

	set_csr(I2C1_SR, NACK);					//停止接收数据
	set_csr(I2C1_SR, I2CSTP);
	clr_csr(I2C1_SR, STR);					//释放IIC总线

	retValue = true;
	return retValue;
}


/*---------------------------------------------------------------------------*/
/* Name		:	I2C_Master_WriteBytes_Ext()
/* Input	:	Addr-Device Address, *pData-pointer to data to write,
/*				NumByte-Number of bytes to write
/* Output	:	bool-false or true
/* Description:	I2C_Master_WriteBytes to slave
/*---------------------------------------------------------------------------*/
bool I2C_Master_WriteBytes_Ext(uint8 DevAddr, uint16 WordAddr, uint8* pData, uint16 NumByte)
{
	uint16 I2C_Counter = 0;
	uint8 I2C_Overtime = 255;
	uint16 I2C_NumBytes;
	bool retValue = false;
	
#if FUNC_EEPROM_24C16B_SWITCH
	I2C_NumBytes = NumByte + 1;
#else
	I2C_NumBytes = NumByte + 2;
#endif

	clr_csr(I2C1_SR, DMOD);

	for (I2C_Counter = 0; I2C_Counter <= I2C_NumBytes; I2C_Counter++)
	{
		if (I2C_Counter == 0)
		{
			write_csr(I2C1_ID, DevAddr);
			set_csr(I2C1_SR, I2CSTA);
		}
#if FUNC_EEPROM_24C16B_SWITCH
		else if (I2C_Counter == 1)
		{
			write_csr(I2C1_DR, WordAddr & 0xFF);		//EEPROM16k的时序
			clr_csr(I2C1_SR, STR);
		}
#else
		else if (I2C_Counter == 1)
		{
			write_csr(I2C1_DR, (WordAddr >> 8) & 0xFF);
			clr_csr(I2C1_SR, STR);
		}
		else if (I2C_Counter == 2)
		{
			write_csr(I2C1_DR, WordAddr & 0xFF);
			clr_csr(I2C1_SR, STR);
		}
#endif
		else
		{
			write_csr(I2C1_DR, *pData++);
			clr_csr(I2C1_SR, STR);
		}

		I2C_Overtime = 255;
		while (!readbit_csr(I2C1_SR, STR))
		{
			if (I2C_Overtime-- == 0)
			{
				set_csr(I2C1_SR, I2CSTP);
				clr_csr(I2C1_SR, STR);
				return retValue;									//接收数据异常
			}
		}

		if (readbit_csr(I2C1_SR, NACK))
		{
			break;										//接收数据异常
		}
	}

	set_csr(I2C1_SR, NACK);					//停止接收数据
	set_csr(I2C1_SR, I2CSTP);
	clr_csr(I2C1_SR, STR);					//释放IIC总线

	retValue = true;
	return retValue;
}

/*---------------------------------------------------------------------------*/
/* Name		:	I2C_Master_ReadBytes()
/* Input	:	Addr-Device Address, *pData-pointer to data to read,
/*				NumByte-Number of bytes to read
 *				isStart: 0-没有DevAddr帧，1-有DevAddr帧；
 *				isEnd: 0-没有NACK, 1-有NACK
/* Output	:	bool-false or true
/* Description:	I2C_Master_ReadBytes from slave
/*---------------------------------------------------------------------------*/
bool I2C_Master_ReadBytes(uint8 DevAddr, uint8* pData, uint16 NumByte, uint8 isStart, uint8 isEnd)
{
	uint8 I2C_Overtime = 255;
	uint16 I2C_Counter = (isStart == 1 ? 0 : 1);
	bool retValue = false;

	set_csr(I2C1_SR, DMOD);

	for (; I2C_Counter <= NumByte; I2C_Counter++)
	{
		if (I2C_Counter == 0)
		{
			write_csr(I2C1_ID, DevAddr);
			set_csr(I2C1_SR, I2CSTA);
		}
		else
		{
			clr_csr(I2C1_SR, NACK);
			clr_csr(I2C1_SR, STR);
		}

		I2C_Overtime = 255;
		while (!readbit_csr(I2C1_SR, STR))
		{
			if (I2C_Overtime-- == 0)
			{
				set_csr(I2C1_SR, I2CSTP);
				clr_csr(I2C1_SR, STR);
				return retValue;					//接收数据异常
			}
		}

		if (readbit_csr(I2C1_SR, NACK))
		{
			break;										//接收数据异常
		}
		if (I2C_Counter > 0)
			*pData++ = read_csr(I2C1_DR);


	}

	if (isEnd == 1)
	{
		set_csr(I2C1_SR, NACK);					//停止接收数据
		set_csr(I2C1_SR, I2CSTP);
		clr_csr(I2C1_SR, STR);					//释放IIC总线
		clr_csr(I2C1_SR, DMOD);
	}

	retValue = true;
	return retValue;
}
