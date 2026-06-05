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
	clr_csr(SPI1_CR, SPIEN);				//关SPI使能

	/*------------------------------------------------------------------------------
	SPI从方式选择配置
	00：3线从方式或3线主方式，NSS信号不连到端口管脚
	01：4线从方式或4线多主方式，NSS配置为输入
	1x：4线单主方式，NSS配置为输出，NSS信号输出x电平
	------------------------------------------------------------------------------*/
	set_csr(SPI1_CR, NSSMOD1);				// 不要问为什么，照做就是
	set_csr(SPI1_CR, NSSMOD0);
	/*------------------------------------------------------------------------------
	SPI时钟相位/极性配置
	CPHA = 0, CPOL = 0:上升沿接收，下降沿发送，空闲电平为低
	CPHA = 0, CPOL = 1:上升沿发送，下降沿接收，空闲电平为高
	CPHA = 1, CPOL = 0:上升沿发送，下降沿接收，空闲电平为低
	CPHA = 1, CPOL = 1:上升沿接收，下降沿发送，空闲电平为高
	------------------------------------------------------------------------------*/
	set_csr(SPI1_CR, CPHA);
	set_csr(SPI1_CR, CPOL);

	clr_csr(SPI1_SR, SPIIF);				// 此位需要软件清0，FTC6901W BUG
	clr_csr(SPI1_CR, SPIIE);				// SPI中断使能0-->Disable  1-->Enable

	set_csr(SPI1_CR, SCKRQ);				// 单线主机请求从机数据使能位 0-->不使能   1-->使能
	set_csr(SPI1_CR, SAMSEL);				// SPI沿边采样选择 0-->slave     1-->master

	set_csr(SPI1_CR, SPIMS);				// 0-->slave     1-->master
	write_csr(SPI1_CLK, 5);					// fsck = sysclk/2*(SPI_CLK[7:0]+1)，此处为8MHz 48M/[2*(1+1)] == 12M（目前可设的最大值）
//	set_csr(SPI1_CR, SPIEN);				// SPI使能 0-->Disable 1-->Enable
}

void SPI2_Init(void)
{
	clr_csr(SPI2_CR, SPIEN);				//关SPI使能

	/*------------------------------------------------------------------------------
	SPI从方式选择配置
	00：3线从方式或3线主方式，NSS信号不连到端口管脚
	01：4线从方式或4线多主方式，NSS配置为输入
	1x：4线单主方式，NSS配置为输出，NSS信号输出x电平
	------------------------------------------------------------------------------*/
	clr_csr(SPI2_CR, NSSMOD1);				// 不要问为什么，照做就是
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
	SPI时钟相位/极性配置
	CPHA = 0, CPOL = 0:上升沿接收，下降沿发送，空闲电平为低
	CPHA = 0, CPOL = 1:上升沿发送，下降沿接收，空闲电平为高
	CPHA = 1, CPOL = 0:上升沿发送，下降沿接收，空闲电平为低
	CPHA = 1, CPOL = 1:上升沿接收，下降沿发送，空闲电平为高
	------------------------------------------------------------------------------*/
	set_csr(SPI2_CR, CPHA);
	set_csr(SPI2_CR, CPOL);

	clr_csr(SPI2_SR, SPIIF);				// 此位需要软件清0，FTC6901W BUG
	clr_csr(SPI2_CR, SPIIE);				// SPI中断使能0-->Disable  1-->Enable

	set_csr(SPI2_CR, SCKRQ);				// 单线主机请求从机数据使能位 0-->不使能   1-->使能
	set_csr(SPI2_CR, SAMSEL);				// SPI沿边采样选择 0-->slave     1-->master

	set_csr(SPI2_CR, SPIMS);				// 0-->slave     1-->master
	write_csr(SPI2_CLK, 5);					// fsck = sysclk/2*(SPI_CLK[7:0]+1)，此处为8MHz 48M/[2*(1+1)] == 12M（目前可设的最大值）
	
}



void SPI_ECAT_Init(void)
{
	clr_csr(SPI1_CR, SPIEN);				//关SPI使能

	/*------------------------------------------------------------------------------
	SPI从方式选择配置
	00：3线从方式或3线主方式，NSS信号不连到端口管脚
	01：4线从方式或4线多主方式，NSS配置为输入
	1x：4线单主方式，NSS配置为输出，NSS信号输出x电平
	------------------------------------------------------------------------------*/
	set_csr(SPI1_CR, NSSMOD1);				// 不要问为什么，照做就是
	set_csr(SPI1_CR, NSSMOD0);
	/*------------------------------------------------------------------------------
	SPI时钟相位/极性配置
	CPHA = 0, CPOL = 0:上升沿接收，下降沿发送，空闲电平为低
	CPHA = 0, CPOL = 1:上升沿发送，下降沿接收，空闲电平为高
	CPHA = 1, CPOL = 0:上升沿发送，下降沿接收，空闲电平为低
	CPHA = 1, CPOL = 1:上升沿接收，下降沿发送，空闲电平为高
	------------------------------------------------------------------------------*/
	set_csr(SPI1_CR, CPHA);
	set_csr(SPI1_CR, CPOL);

	clr_csr(SPI1_SR, SPIIF);				// 此位需要软件清0，FTC6901W BUG
	clr_csr(SPI1_CR, SPIIE);				// SPI中断使能0-->Disable  1-->Enable
	
	set_csr(SPI1_CR, SCKRQ);				// 单线主机请求从机数据使能位 0-->不使能   1-->使能
	set_csr(SPI1_CR, SAMSEL);				// SPI沿边采样选择 0-->slave     1-->master

	set_csr(SPI1_CR, SPIMS);				// 0-->slave     1-->master
	write_csr(SPI1_CLK, 3);					// fsck = sysclk/2*(SPI_CLK[7:0]+1)，此处为8MHz 48M/[2*(1+1)] == 12M（目前可设的最大值）
	set_csr(SPI1_CR, SPIEN);				// SPI使能 0-->Disable 1-->Enable
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
//	while (!readbit_csr(SPI1_SR, TXBMT));  // 7502B加了这句后NSS会异常
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
	//	while (!readbit_csr(SPI2_SR, TXBMT));  // 7502B加了这句后NSS会异常
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