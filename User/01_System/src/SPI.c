/*
 * Copyright (c) 2022-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : SPI.c
 * Author        : Fortior Application Team
 * Date          : 2022-09-21
 * Description   : define SPI
 *
 * Record        :
 * V1.0, 2022-09-21, Fortior Application Team: Created file
 */


#include <Myproject.h>


void SPI1_Init(void)
{
	clr_csr(SPI1_CR, SPIEN);				//Disable SPI enable

	/*------------------------------------------------------------------------------
	SPI slave mode selection configuration
	00: 3-wire slave mode or 3-wire master mode, NSS signal not connected to port pins
	01: 4-wire slave mode or 4-wire multi-master mode, NSS configured as input
	1x: 4-wire single-master mode, NSS configured as output, NSS signal output level x
	------------------------------------------------------------------------------*/
	set_csr(SPI1_CR, NSSMOD1);				// Don't ask why, just do it
	set_csr(SPI1_CR, NSSMOD0);
	/*------------------------------------------------------------------------------
	SPI clock phase/polarity configuration
	CPHA = 0, CPOL = 0: Receive on rising edge, transmit on falling edge, idle level low
	CPHA = 0, CPOL = 1: Transmit on rising edge, receive on falling edge, idle level high
	CPHA = 1, CPOL = 0: Transmit on rising edge, receive on falling edge, idle level low
	CPHA = 1, CPOL = 1: Receive on rising edge, transmit on falling edge, idle level high
	------------------------------------------------------------------------------*/
	set_csr(SPI1_CR, CPHA);
	set_csr(SPI1_CR, CPOL);

	clr_csr(SPI1_SR, SPIIF);				// This bit needs to be software cleared, FTC6901W BUG
	clr_csr(SPI1_CR, SPIIE);				// SPI interrupt enable 0-->Disable  1-->Enable

	set_csr(SPI1_CR, SCKRQ);				// Single-wire master request slave data enable bit 0-->Disable   1-->Enable
	set_csr(SPI1_CR, SAMSEL);				// SPI edge sampling selection 0-->slave     1-->master

	set_csr(SPI1_CR, SPIMS);				// 0-->slave     1-->master
	write_csr(SPI1_CLK, 5);					// fsck = sysclk/2*(SPI_CLK[7:0]+1), here it is 8MHz 48M/[2*(1+1)] == 12M (maximum value currently settable)
//	set_csr(SPI1_CR, SPIEN);				// SPI enable 0-->Disable 1-->Enable
}

void SPI2_Init(void)
{
	clr_csr(SPI2_CR, SPIEN);				//Disable SPI enable

	/*------------------------------------------------------------------------------
	SPI slave mode selection configuration
	00: 3-wire slave mode or 3-wire master mode, NSS signal not connected to port pins
	01: 4-wire slave mode or 4-wire multi-master mode, NSS configured as input
	1x: 4-wire single-master mode, NSS configured as output, NSS signal output level x
	------------------------------------------------------------------------------*/
	clr_csr(SPI2_CR, NSSMOD1);				// Don't ask why, just do it
	clr_csr(SPI2_CR, NSSMOD0);
	
#ifdef NSS2_PIN
	set_csr(NSS2_GPIO, NSS2_PIN);
	set_csr(NSS2_OE, NSS2_PIN);
	clr_csr(NSS2_PU, NSS2_PIN);
#endif
//	clr_csr(PA_PU, PIN10);
//	clr_csr(PA_PU, PIN11);
//	clr_csr(PA_PU, PIN12);
//	clr_csr(PA_PU, PIN13);
	
	/*------------------------------------------------------------------------------
	SPI clock phase/polarity configuration
	CPHA = 0, CPOL = 0: Receive on rising edge, transmit on falling edge, idle level low
	CPHA = 0, CPOL = 1: Transmit on rising edge, receive on falling edge, idle level high
	CPHA = 1, CPOL = 0: Transmit on rising edge, receive on falling edge, idle level low
	CPHA = 1, CPOL = 1: Receive on rising edge, transmit on falling edge, idle level high
	------------------------------------------------------------------------------*/
	set_csr(SPI2_CR, CPHA);
	set_csr(SPI2_CR, CPOL);

	clr_csr(SPI2_SR, SPIIF);				// This bit needs to be software cleared, FTC6901W BUG
	clr_csr(SPI2_CR, SPIIE);				// SPI interrupt enable 0-->Disable  1-->Enable

	set_csr(SPI2_CR, SCKRQ);				// Single-wire master request slave data enable bit 0-->Disable   1-->Enable
	set_csr(SPI2_CR, SAMSEL);				// SPI edge sampling selection 0-->slave     1-->master

	set_csr(SPI2_CR, SPIMS);				// 0-->slave     1-->master
	write_csr(SPI2_CLK, 5);					// fsck = sysclk/2*(SPI_CLK[7:0]+1), here it is 8MHz 48M/[2*(1+1)] == 12M (maximum value currently settable)
	
}



void SPI_ECAT_Init(void)
{
	clr_csr(SPI1_CR, SPIEN);				//Disable SPI enable
	
	clr_csr(PH_SEL, SPICT);		// 1: PA15-SCLK PA14-MOSI PA13-MISO PA7-NSS (7502BC)

	/*------------------------------------------------------------------------------
	SPI slave mode selection configuration
	00: 3-wire slave mode or 3-wire master mode, NSS signal not connected to port pins
	01: 4-wire slave mode or 4-wire multi-master mode, NSS configured as input
	1x: 4-wire single-master mode, NSS configured as output, NSS signal output level x
	------------------------------------------------------------------------------*/
	set_csr(SPI1_CR, NSSMOD1);				// Don't ask why, just do it
	set_csr(SPI1_CR, NSSMOD0);
	/*------------------------------------------------------------------------------
	SPI clock phase/polarity configuration
	CPHA = 0, CPOL = 0: Receive on rising edge, transmit on falling edge, idle level low
	CPHA = 0, CPOL = 1: Transmit on rising edge, receive on falling edge, idle level high
	CPHA = 1, CPOL = 0: Transmit on rising edge, receive on falling edge, idle level low
	CPHA = 1, CPOL = 1: Receive on rising edge, transmit on falling edge, idle level high
	------------------------------------------------------------------------------*/
	set_csr(SPI1_CR, CPHA);
	set_csr(SPI1_CR, CPOL);

	clr_csr(SPI1_SR, SPIIF);				// This bit needs to be software cleared, FTC6901W BUG
	clr_csr(SPI1_CR, SPIIE);				// SPI interrupt enable 0-->Disable  1-->Enable
	
	set_csr(SPI1_CR, SCKRQ);				// Single-wire master request slave data enable bit 0-->Disable   1-->Enable
	set_csr(SPI1_CR, SAMSEL);				// SPI edge sampling selection 0-->slave     1-->master

	set_csr(SPI1_CR, SPIMS);				// 0-->slave     1-->master
	write_csr(SPI1_CLK, 3);					// fsck = sysclk/2*(SPI_CLK[7:0]+1), here it is 8MHz 48M/[2*(1+1)] == 12M (maximum value currently settable)
	set_csr(SPI1_CR, SPIEN);				// SPI enable 0-->Disable 1-->Enable
}



/*******************************************************************************
 * Function Name  : WR_CMD
 * Description    : Read and Wire data to ET1100
 * Input          : - cmd: the data send to ET1100
 * Output         : none
 * Return         : temp: the data read from ET1100
 * Attention		 : None
 *******************************************************************************/
uint8 WR_CMD(uint8 cmd)
{
	uint8 temp = 0;
	uint8 TmpCnt = 255;

	clr_csr(SPI1_SR, SPIIF);
	/* Wait for SPI1 Tx buffer empty */
//	while (!readbit_csr(SPI1_SR, TXBMT));  // NSS will be abnormal after adding this line in 7502B
	/* Send SPI1 data */
	write_csr(SPI1_DR, cmd);
	/* Wait for SPI1 data reception */
	while (TmpCnt-- > 0)
	{
		if (!readbit_csr(SPI1_SR, SPIBSY) && readbit_csr(SPI1_SR, SPIIF))
		{
			/* Read SPI1 received data */
			temp = read_csr(SPI1_DR);
			break;
		}	
	}
	return temp;
}

/*******************************************************************************
 * Function Name  : WR_CMD2
 * Description    : Read and Wire data to ET1100
 * Input          : - cmd: the data send to ET1100
 * Output         : none
 * Return         : temp: the data read from ET1100
 * Attention		 : None
 *******************************************************************************/
uint8 WR_CMD2(uint8 cmd)
{
	uint8 temp = 0;
	uint8 TmpCnt = 255;

	clr_csr(SPI2_SR, SPIIF);
	/* Wait for SPI2 Tx buffer empty */
	//	while (!readbit_csr(SPI2_SR, TXBMT));  // NSS will be abnormal after adding this line in 7502B
	/* Send SPI2 data */
	write_csr(SPI2_DR, cmd);
	/* Wait for SPI1 data reception */
	while (TmpCnt-- > 0)
	{
		if (!readbit_csr(SPI2_SR, SPIBSY) && readbit_csr(SPI2_SR, SPIIF))
		{
			/* Read SPI2 received data */
			temp = read_csr(SPI2_DR);
			break;
		}
	}

	return temp;
}

/*******************************************************************************
 * Function Name  : SPI_Transmit
 * Description    : Write data through SPI.
 * Input          : SPISel - SPI Select.
 * Input          : pTxData - pTxData pointer to transmission data buffer.
 * Input          : txLen - Transmission data buffer length.
 * Output         : none
 * Return         : Return 1 for success and 0 for failure
 * Attention		 : None
 *******************************************************************************/
uint8 SPI_Transmit(uint8 SPISel, uint8* pTxData, uint8 txLen, uint8 Timeout)
{
	uint8 retVal = 1;
	uint8 * pTmpData = pTxData;
	uint8 i = txLen;
	while (i-- > 0)
	{
		if(SPISel == SEL_SPI1)
			WR_CMD(*pTmpData++);
		else
			WR_CMD2(*pTmpData++);
	}
	return retVal;
}


/*******************************************************************************
 * Function Name  : SPI_Receive
 * Description    : Read data through SPI.
 * Input          : SPISel - SPI Select.
 * Input          : pRxData - pTxData pointer to transmission data buffer.
 * Input          : rxLen - Transmission data buffer length.
 * Output         : none
 * Return         : Return 1 for success and 0 for failure
 * Attention		 : None
 *******************************************************************************/
uint8 SPI_Receive(uint8 SPISel, uint8* pRxData, uint8 rxLen, uint8 Timeout)
{
	uint8 retVal = 1;
	uint8* pTmpData = pRxData;
	uint8 i = rxLen;
	while (i-- > 0)
	{
		if (SPISel == SEL_SPI1)
			*pTmpData++ = WR_CMD(0xFF);
		else
			*pTmpData++ = WR_CMD2(0xFF);
	}
	return retVal;
}

/**
 * @brief  Transmit and Receive data.
 * @param  hspi pointer to a SPI_HandleTypeDef structure that contains the configuration information for SPI module.
 * @param  pTxData pointer to transmission data buffer.
 * @param  pRxData pointer to reception data buffer.
 * @param  Transmission data buffer length.
 * @param  Reception data buffer length.
 * @retval None
 */
void SPI_TransmitReceive(uint8 SPISel, uint8* pTxData, uint8* pRxData, uint8 txLen, uint8 rxLen)
{
	if (SPISel == SEL_SPI1)
		SELECT_SPI;
	else
		SELECT_SPI2;

	SPI_Transmit(SPISel, pTxData, txLen, 0xFF);
	SPI_Receive(SPISel, pRxData, rxLen, 0xFF);

	if (SPISel == SEL_SPI1)
		DESELECT_SPI;
	else
		DESELECT_SPI2;
}