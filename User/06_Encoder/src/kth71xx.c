/**************************************************
** Copyright (c) 2016-202X CONNTEK Microelectronics
** @file    kth71xx.c
** @author  liujunbo
** @date    2025.07.04
** @brief   File of KTH71xx chip communication.
**
**************************************************/

#include "kth71xx.h"
#include "SPI.h"

#if ENCODER_SEL_SPI_ENABLED > 0 || ENCODER_SEL_SPI2_ENABLED > 0

EncKTHTypedef EncKTH1;
EncKTHTypedef EncKTH2;

/**
 * @brief  KTH71_Init.
 * @param  EncKTHTypedef pointer.
 * @retval None.
 */
void KTH71_Init(EncKTHTypedef* p, uint8_t SPISel)
{
	memset(p, 0, sizeof(EncKTHTypedef));
	p->SPISel = SPISel;
}

/**
  * @brief  Reads the angle and returns the CRC check result.
  * @param  pAngle pointer to angle.
  * @retval If the CRC check succeeds, return 1. 
            If the CRC check fails, return 0.
  */
uint8_t KTH71_ReadAngle(EncKTHTypedef* p, uint16_t *pAngle)
{
  	uint8_t crcflag = 0;
  	uint8_t dataSend = KTH71_READ_ANGLE;
  	uint8_t dataBack[3];

  	SPI_TransmitReceive(p->SPISel, &dataSend, dataBack, 1, 3);
  	crcflag = CalCRC8(dataBack, 3, 0x55);
  	*pAngle = (dataBack[0] << 8) | dataBack[1];
  	return crcflag;
}

/**
  * @brief  Reads the register value via the address parameter and returns the CRC check result.
  * @param  Register address.
  * @param  pRegValue pointer to register value.
  * @retval If the CRC check succeeds, return 1. 
            If the CRC check fails, return 0.
  */
uint8_t KTH71_ReadReg(EncKTHTypedef* p, uint8_t addr, uint8_t *pRegValue)
{
  	uint8_t crcflag = 0;
  	uint8_t dataSend[2] = {KTH71_READ_REG, addr};
  	uint8_t dataBack[2];

  	SPI_TransmitReceive(p->SPISel, dataSend, dataBack, 2, 2);
  	crcflag = CalCRC8(dataBack, 2, 0x55);
  	*pRegValue = dataBack[0];
  	return crcflag;
}

/**
  * @brief  Writes the register.
  * @param  Register address.
  * @param  The value you want to write to the register.
  * @retval The value of the newly written register
  */
uint8_t KTH71_WriteReg(EncKTHTypedef* p, uint8_t addr, uint8_t data)
{
  	uint8_t dataSend[3] = {KTH71_WRITE_REG, addr, data};
  	uint8_t dataBack = 0;

  	SPI_TransmitReceive(p->SPISel, dataSend, &dataBack, 3, 1);
  	return dataBack;
}

/**
  * @brief  Unlocks registers.
  * @retval None
  */
void KTH71_UnlockReg(EncKTHTypedef* p)
{
	if (p->UnlockFlag == 0)
	{
		p->UnlockFlag = 1;

		uint8_t dataSend[4] = { 0x20, 0x24, 0x01, 0x01 };
		if (p->SPISel == SEL_SPI1)
			SELECT_SPI;
		else
			SELECT_SPI2;

		SPI_Transmit(p->SPISel, dataSend, 4, 0xFFFF);

		if (p->SPISel == SEL_SPI1)
			DESELECT_SPI;
		else
			DESELECT_SPI2;
	}
}

/**
  * @brief  Locks registers.
  * @retval None
  */
void KTH71_LockReg(EncKTHTypedef* p)
{
  	uint8_t dataSend[4] = {0x20, 0x24, 0x12, 0x31};
  	if (p->SPISel == SEL_SPI1)
  		SELECT_SPI;
  	else
  		SELECT_SPI2;
  	
  	SPI_Transmit(p->SPISel, dataSend, 4, 0xFFFF);
  	
  	if (p->SPISel == SEL_SPI1)
  		DESELECT_SPI;
  	else
  		DESELECT_SPI2;
  	
  	p->UnlockFlag = 0;
}

/**
  * @brief  Writes the register value to MTP..
  * @retval None
  */
void KTH71_WriteRegToMTP(EncKTHTypedef* p)
{
  	uint8_t dataSend[3] = {0x22, 0x55, 0xAA};
  	if (p->SPISel == SEL_SPI1)
  		SELECT_SPI;
  	else
  		SELECT_SPI2;
  	
  	SPI_Transmit(p->SPISel, dataSend, 3, 0xFFFF);
  	
  	if (p->SPISel == SEL_SPI1)
  		DESELECT_SPI;
  	else
  		DESELECT_SPI2;
  	
//  	Delay_ms(400); // MTP 烧写命令间隔必须大于
}



/*=================================================================================
Function Name	:	KTH71_Calibration(void)
Description		:	Do Encoder_Calibration
Parameter		:	SPISel - SPI or SPI2.
					EncCalStart - Start/Stop calibration.
					EncCalSave - Save parameter to encoder chip MTP.
					EncRegWrite - Write encoder register.
					EncRegRead - Read encoder register.
					EncRegAddr - Register Address
					pEncRegValue - Register Value
=================================================================================*/
uint8 KTH71_Calibration(EncKTHTypedef* p, uint16 EncCalStart, uint16 EncSave, uint16 EncRegWrite,
	uint16 EncRegRead, uint16 EncRegAddr, uint16 *pEncRegValue)
{
	uint8 calStatus;

	if (!p->EncCalStart && EncCalStart) // 开始校准
	{
		KTH71_UnlockReg(p); // 解锁
		KTH71_WriteReg(p, 0x16, 0x08); // 重置非线性校准
		KTH71_WriteReg(p, 0x16, 0x18); // 启动非线性校准

		p->EncCalCounter = 0;
		p->EncCalState = ENCCALSTA_DOING;
	}
	else if (p->EncCalState != ENCCALSTA_IDLE && !EncCalStart) // 结束校准
	{
		KTH71_WriteReg(p, 0x16, 0x08); // 重置非线性校准
		p->EncCalState = ENCCALSTA_IDLE;
	}
	else if (p->EncCalState == ENCCALSTA_DOING)
	{
		p->EncCalCounter++;
		if (p->EncCalCounter > 19200000) // 20 minute
		{
			KTH71_WriteReg(p, 0x16, 0x08); // 重置非线性校准
			p->EncCalState = ENCCALSTA_FAIL;
		}
		else if (p->EncCalCounter > 160 && KTH71_ReadReg(p, 0x72, &calStatus)) // 检查校准状态
		{
			calStatus = (calStatus >> 4) & 0x03;
			if (calStatus != ENCCALSTA_DOING)
			{
				KTH71_WriteReg(p, 0x16, 0x08); // 重置非线性校准
				p->EncCalState = calStatus;
			}
		}
	}

	// 保存到MTP
	else if (!p->EncSave && EncSave)
	{
		KTH71_UnlockReg(p); // 解锁
		KTH71_WriteRegToMTP(p);
	}

	// 写寄存器
	else if (!p->EncRegWrite && EncRegWrite)
	{
		KTH71_UnlockReg(p); // 解锁
		KTH71_WriteReg(p, EncRegAddr, *pEncRegValue);
	}
	
	// 读寄存器
	else if (!p->EncRegRead && EncRegRead)
	{
		KTH71_ReadReg(p, EncRegAddr, pEncRegValue);
	}

	p->EncCalStart = EncCalStart;
	p->EncSave = EncSave;
	p->EncRegWrite = EncRegWrite;
	p->EncRegRead = EncRegRead;
	
	return p->EncCalState;
}
#endif // #if ENCODER_SEL_SPI_ENABLED > 0 || ENCODER_SEL_SPI2_ENABLED > 0
