/*
 * Copyright (c) 2025-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : mt68xx.c
 * Author        : Summer
 * Date          : 2025-11-17
 * Description   : File of MT68xx chip communication.
 *
 * Record        :
 * V1.0, 2025-11-17, Summer: Created file
 */

#include "mt68xx.h"
#include "SPI.h"

#if ENCODER_SEL_SPI_ENABLED > 0 || ENCODER_SEL_SPI2_ENABLED > 0

EncMTTypedef EncMT1;
EncMTTypedef EncMT2;

/**
 * @brief  MT68_Init.
 * @param  EncMTTypedef pointer.
 * @retval None.
 */
void MT68_Init(EncMTTypedef* p, uint8_t SPISel)
{
	memset(p, 0, sizeof(EncMTTypedef));
	p->SPISel = SPISel;
}

/**
  * @brief  Reads the angle and returns the CRC check result.
  * @param  pAngle pointer to angle.
  * @retval If the CRC check succeeds, return 1. 
            If the CRC check fails, return 0.
  */
uint8_t MT68_ReadAngle(EncMTTypedef* p, uint32_t *pAngle)
{
  	uint8_t crcflag = 0;
  	uint8_t dataSend[2] = { MT68_READ_ANGLE << 4, 0x03 };
  	uint8_t dataBack[4];

  	SPI_TransmitReceive(p->SPISel, dataSend, dataBack, 2, 4);
  	crcflag = CalCRC8(dataBack, 4, 0x00);
  	*pAngle = ((uint32) dataBack[0] << 13) + ((uint32) dataBack[1] << 5)
  		+((uint32) dataBack[2] >> 3);
  	return crcflag;
}

/**
  * @brief  Reads the register value via the address parameter.
  * @param  Register address.
  * @param  pRegValue pointer to register value.
  * @retval None.
  */
void MT68_ReadReg(EncMTTypedef* p, uint16_t addr, uint8_t *pRegValue)
{
  	uint8_t dataSend[2] = { (MT68_READ_REG << 4) | ((addr >> 8) & 0x0F), addr & 0xFF };
  	uint8_t dataBack[1];

  	SPI_TransmitReceive(p->SPISel, dataSend, dataBack, 2, 1);
  	*pRegValue = dataBack[0];
}

/**
  * @brief  Writes the register.
  * @param  Register address.
  * @param  The value you want to write to the register.
  * @retval None
  */
void MT68_WriteReg(EncMTTypedef* p, uint16_t addr, uint8_t data)
{
  	uint8_t dataSend[3] = { (MT68_WRITE_REG << 4) | ((addr >> 8) & 0x0F), addr & 0xFF, data};
  	uint8_t dataBack = 0;

  	SPI_TransmitReceive(p->SPISel, dataSend, &dataBack, 3, 0);
}


/**
  * @brief  Writes the register value to MTP.
  * @retval crcflag
  */
uint8_t MT68_WriteRegToMTP(EncMTTypedef* p)
{
	uint8_t dataSend[2] = { (MT68_WRITE_MTP << 4), 0x00 };
	uint8_t dataBack[1];
	uint8_t crcflag;

	SPI_TransmitReceive(p->SPISel, dataSend, dataBack, 2, 1);
	crcflag = (0x55 == dataBack[0]) ? 1 : 0;

	return crcflag;
}



/*=================================================================================
Function Name	:	MT68_Calibration(void)
Description		:	Do Encoder_Calibration
Parameter		:	SPISel - SPI or SPI2.
					EncCalStart - Start/Stop calibration.
					EncCalSave - Save parameter to encoder chip MTP.
					EncRegWrite - Write encoder register.
					EncRegRead - Read encoder register.
					EncRegAddr - Register Address
					pEncRegValue - Register Value
=================================================================================*/
uint8 MT68_Calibration(EncMTTypedef* p, uint16 EncCalStart, uint16 EncSave, uint16 EncRegWrite,
	uint16 EncRegRead, uint16 EncRegAddr, uint16* pEncRegValue)
{
	uint8 calStatus;

#ifdef ENCCAL_PIN
	if (!p->EncCalStart && EncCalStart) // 开始校准
	{
		clr_csr(ENCCAL_GPIO, ENCCAL_PIN); // 启动非线性校准
		set_csr(ENCCAL_GPIO, ENCCAL_PIN);

		p->EncCalCounter = 0;
		p->EncCalState = ENCCALSTA_DOING;
	}
	else if (p->EncCalState != ENCCALSTA_IDLE && !EncCalStart) // 结束校准
	{
		clr_csr(ENCCAL_GPIO, ENCCAL_PIN); // 重置非线性校准
		p->EncCalState = ENCCALSTA_IDLE;
	}
	else if (p->EncCalState == ENCCALSTA_DOING)
	{
		p->EncCalCounter++;
		if (p->EncCalCounter > 19200000) // 20 minute
		{
			clr_csr(ENCCAL_GPIO, ENCCAL_PIN); // 重置非线性校准
			p->EncCalState = ENCCALSTA_FAIL;
		}
		else if (p->EncCalCounter > 160) // 检查校准状态
		{
			// 读校准状态
			MT68_ReadReg(p, 0x113, &calStatus);

			calStatus = (calStatus >> 6) & 0x03;
			if (calStatus != ENCCALSTA_DOING)
			{
				clr_csr(ENCCAL_GPIO, ENCCAL_PIN);
				p->EncCalState = calStatus;
			}
		}
	}
	else 
#endif

	// 保存到MTP
	if (!p->EncSave && EncSave)
	{
		MT68_WriteRegToMTP(p);
	}
	
	// 写寄存器
	else if (!p->EncRegWrite && EncRegWrite)
	{
		MT68_WriteReg(p, EncRegAddr, *pEncRegValue);
	}

	// 读寄存器
	else if (!p->EncRegRead && EncRegRead)
	{
		MT68_ReadReg(p, EncRegAddr, pEncRegValue);
	}

	p->EncCalStart = EncCalStart;
	p->EncSave = EncSave;
	p->EncRegWrite = EncRegWrite;
	p->EncRegRead = EncRegRead;
	
	return p->EncCalState;
}
#endif // #if ENCODER_SEL_SPI_ENABLED > 0 || ENCODER_SEL_SPI2_ENABLED > 0
