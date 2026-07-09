/*
 * Copyright (c) 2022-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : DMA.c
 * Author        : Fortior Application Team
 * Date          : 2022-09-21
 * Description   : define DMA
 *
 * Record        :
 * V1.0, 2022-09-21, Fortior Application Team: Created file
 */

#include <Myproject.h>

void SetPipe_DMA0(uint16 ePipe)
{
	bool bTmp = false;
	uint16 reg;

	if (readbit_csr(DMA0_CR, DMAEN))
	{
		bTmp = true;
		while (readbit_csr(DMA0_CR, DMABSY));
		clr_csr(DMA0_CR, DMAEN);
	}

	reg = read_csr(DMA0_CR);

	SetReg(reg, DMACFG4 | DMACFG3 | DMACFG2 | DMACFG1 | DMACFG0, ePipe);

	write_csr(DMA0_CR, reg);

	if (bTmp) set_csr(DMA0_CR, DMAEN);
}

void SetPipe_DMA1(uint16 ePipe)
{
	bool bTmp = false;
	uint16 reg;

	if (readbit_csr(DMA1_CR, DMAEN))
	{
		bTmp = true;
		while (readbit_csr(DMA1_CR, DMABSY));
		clr_csr(DMA1_CR, DMAEN);
	}

	reg = read_csr(DMA1_CR);
	SetReg(reg, DMACFG4 | DMACFG3 | DMACFG2 | DMACFG1 | DMACFG0, ePipe);
	write_csr(DMA1_CR, reg);

	if (bTmp) set_csr(DMA1_CR, DMAEN);
}

void SetDataPackage_DMA0(unsigned char* ulAddr, char cLen)
{
	bool bTmp = false;

	if (readbit_csr(DMA0_CR, DMAEN))
	{
		bTmp = true;

		while (readbit_csr(DMA0_CR, DMABSY));
		clr_csr(DMA0_CR, DMAEN);
	}

	write_csr(DMA0_LEN, cLen - 1);
	write_csr(DMA0_BA, ulAddr);

	if (bTmp) set_csr(DMA0_CR, DMAEN);
}

void SetDataPackage_DMA1(unsigned char* ulAddr, char cLen)
{
	bool bTmp = false;

	if (readbit_csr(DMA1_CR, DMAEN))
	{
		bTmp = true;

		while (readbit_csr(DMA1_CR, DMABSY));
		clr_csr(DMA1_CR, DMAEN);
	}

	write_csr(DMA1_LEN, cLen - 1);
	write_csr(DMA1_BA, ulAddr);

	if (bTmp) set_csr(DMA1_CR, DMAEN);
}

void SetIRQ_DMA0(bool eIRQ)
{
	clr_csr(DMA0_CR, DMAIF);
	if (eIRQ)
		set_csr(DMA0_CR, DMAIE);
	else
		clr_csr(DMA0_CR, DMAIE);

	if (eIRQ)
	{
		write_csr(IP12, DMA0_INT_PRI);			// DRV1 interrupt (interrupt number 8) priority is 4
	}
}

void SetIRQ_DMA1(bool eIRQ)
{
	clr_csr(DMA1_CR, DMAIF);
	if (eIRQ)
		set_csr(DMA1_CR, DMAIE);
	else
		clr_csr(DMA1_CR, DMAIE);

	if (eIRQ)
	{
		write_csr(IP12, DMA0_INT_PRI);			// DRV1 interrupt (interrupt number 8) priority is 4
	}
}

void Set_DBG_DMA(void)
{
	write_csr(DMA1_LEN, 7);
	set_csr(DMA1_CR, DMAEN);

	//	set_csr(DMA0_CR, ENDIAN);		//DMA data transfer order mode

	set_csr(DMA1_CR, DMACFG2);	//
	clr_csr(DMA1_CR, DMACFG1);
	set_csr(DMA1_CR, DMACFG0);

	//	set_csr(DMA1_CR, DBGEN);

#if TEST_SPIDEBUG_HW_ENABLED
	write_csr(DMA1_BA, 0x70000164); //HARD_SPIDATA
#elif TEST_SPIDEBUG_SW_ENABLED
	write_csr(DMA1_BA, spidebug);
#endif

	set_csr(DMA1_CR, DMABSY);
}

void Switch_DMA0(void)
{
	set_csr(DMA0_CR, DMAEN);
	set_csr(DMA0_CR, DMABSY);
}

void Switch_DMA1(void)
{
	set_csr(DMA1_CR, DMAEN);
	set_csr(DMA1_CR, DMABSY);
}

void Close_DMA0(void)
{
	clr_csr(DMA0_CR, DMAEN);
}

void Reset_DMA0(void)
{
	clr_csr(DMA0_CR, DMAEN);
	set_csr(DMA0_CR, DMAEN);
	set_csr(DMA0_CR, DMABSY);
}