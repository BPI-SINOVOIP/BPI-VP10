/*
 * Copyright (c) 2025-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : EncSPI.c
 * Author        : Summer
 * Date          : 2025-09-21
 * Description   : SPI Encoder decoding function.
 *
 * Record        :
 * V1.0, 2025-09-21, Summer: Created file
 */

#include <Myproject.h>
#include <Encoder.h>


#if ENCODER_SEL_SPI_ENABLED > 0

#if ENC_SPI_DMA_ENABLED
UINT8 EncSPIReadData[ENC_SPI_LEN] = { 0 };
UINT8 EncSPIWriteData[ENC_SPI_LEN] = { 0 };
#endif


/*---------------------------------------------------------------------------
 * Name		:	SPI_Encoder_Init
 * Input	:	No
 * Output	:	No
 * Description:	SPI encoder initialization
 *---------------------------------------------------------------------------*/
void SPI_Encoder_Init(void)
{
	SPI1_Init();
	
#if ENC_SPI_DMA_ENABLED
	// Read
	write_csr(ENCSPI1_RD_DMA_CR, DMA_SPI1_Read);
	write_csr(ENCSPI1_RD_DMA_LEN, ENC_SPI_LEN - 1);
	write_csr(ENCSPI1_RD_DMA_BA, EncSPIReadData);
	clr_csr(ENCSPI1_RD_DMA_CR, DMAEN);

	// Write
	write_csr(ENCSPI1_WR_DMA_CR, DMA_SPI1_Send);
	write_csr(ENCSPI1_WR_DMA_LEN, ENC_SPI_LEN - 1);
	write_csr(ENCSPI1_WR_DMA_BA, EncSPIWriteData);
	clr_csr(ENCSPI1_WR_DMA_CR, DMAEN);
#endif
	
#ifdef ENCCAL_PIN
	clr_csr(ENCCAL_GPIO, ENCCAL_PIN);
	set_csr(ENCCAL_OE, ENCCAL_PIN);		// Output enable /* 0: Enable digital output */
#endif

#if (ENCSPI_Source == ENCSPI_KTH)
	KTH71_Init(&EncKTH1, SEL_SPI1);
#else
	MT68_Init(&EncMT1, SEL_SPI1);
#endif
}


/*---------------------------------------------------------------------------
 * Name		:	SPI_Encoder_Enable
 * Input	:	No
 * Output	:	No
 * Description:	SPI encoder enable
 *---------------------------------------------------------------------------*/
void SPI_Encoder_Enable(uint8 EncSel)
{
	set_csr(SPI1_CR, SPIEN);				// SPI enable 0-->Disable 1-->Enable
	
	mcEncoder.SPI.Multi = 0;
	mcEncoder.SPI.EncSel = EncSel;
	
	if (EncSel == ENCSEL_MOTOR)
	{
		usSRegInBuf[ENCSPISRC] = (usSRegInBuf[ENCSPISRC] & 0xFF00) | ENCSPI_Source;
	}
	else
	{
		usSRegInBuf[ENCSPISRC] = (usSRegInBuf[ENCSPISRC] & 0x00FF) | ((uint16)ENCSPI_Source << 8);
	}
	
#if (ENCSPI_Source == ENCSPI_KTH)
	mcEncoder.SPI.DataBits = 16;
#else
	mcEncoder.SPI.DataBits = 21;
#endif
	mcEncoder.SPI.ZeroBits = 0;
	mcEncoder.SPI.ValidBits = mcEncoder.SPI.DataBits - mcEncoder.SPI.ZeroBits;
	mcEncoder.SPI.DataMask = (1 << mcEncoder.SPI.ValidBits) - 1;
	mcEncoder.SPI.SingleHalf = 1 << (mcEncoder.SPI.ValidBits - 1);
	mcEncoder.SPI.Single = mcEncoder.SPI.SingleHalf;
	mcEncoder.SPI.Multi = 0;
	mcEncoder.SPI.FirstFlag = 0;

#if (ENCSPI_Source == ENCSPI_KTH)
	KTH71_Init(&EncKTH1, SEL_SPI1);
#else
	MT68_Init(&EncMT1, SEL_SPI1);
	
#if ENC_SPI_DMA_ENABLED
	EncSPIWriteData[0] = 0xA0;
	EncSPIWriteData[1] = 0x03;
#endif
#endif
	
	DESELECT_SPI; // Pull high NSS pin
}


/*---------------------------------------------------------------------------
 * Name		:	SPI_Encoder_Disable
 * Input	:	No
 * Output	:	No
 * Description:	SPI encoder disable
 *---------------------------------------------------------------------------*/
void SPI_Encoder_Disable(void)
{
	DESELECT_SPI;			// Pull high NSS pin
	clr_csr(SPI1_CR, SPIEN);				// SPI enable 0-->Disable 1-->Enable
}


/*---------------------------------------------------------------------------
 * Name		:	SPI_Encoder_Update
 * Input	:	No
 * Output	:	No
 * Description:	SPI encoder parameter update
 *---------------------------------------------------------------------------*/
void SPI_Encoder_Update(void)
{
	if (mcEncoder.SPI.EncSel == ENCSEL_MOTOR && mcEncoder.SPI.ZeroBits != usSRegHoldBuf[ENCZEROBITS])
	{
		mcEncoder.SPI.ZeroBits = usSRegHoldBuf[ENCZEROBITS];
		mcEncoder.SPI.ValidBits = mcEncoder.SPI.DataBits - mcEncoder.SPI.ZeroBits;
		mcEncoder.SPI.DataMask = (1 << mcEncoder.SPI.ValidBits) - 1;
		mcEncoder.SPI.SingleHalf = 1 << (mcEncoder.SPI.ValidBits - 1);
	}
}


/*---------------------------------------------------------------------------
 * Name		:	SPI_Encoder_Calibration
 * Input	:	No
 * Output	:	No
 * Description:	SPI encoder calibration
 *---------------------------------------------------------------------------*/
void SPI_Encoder_Calibration(void)
{
#if (ENCSPI_Source == ENCSPI_KTH)
	uint8 encCalState;
	if (mcEncoder.SPI.EncSel == ENCSEL_MOTOR)
	{
		encCalState = KTH71_Calibration(&EncKTH1, GetReg(usSRegHoldBuf[ENCCALCTRL], ENCCAL_START),
			GetReg(usSRegHoldBuf[ENCCALCTRL], ENCCAL_SAVE), GetReg(usSRegHoldBuf[ENCCALCTRL], ENCREG_WRITE),
			GetReg(usSRegHoldBuf[ENCCALCTRL], ENCREG_READ), usSRegHoldBuf[ENCREGADDR], &usSRegHoldBuf[ENCREGVAL]);
		
		usSRegInBuf[ENCCALSTATUS] = (usSRegInBuf[ENCCALSTATUS] & 0xFF00) | encCalState;
	}
	else
	{
		encCalState = KTH71_Calibration(&EncKTH1, GetReg(usSRegHoldBuf[ENCCALCTRL], SFBENCCAL_START),
			GetReg(usSRegHoldBuf[ENCCALCTRL], SFBENCCAL_SAVE), GetReg(usSRegHoldBuf[ENCCALCTRL], SFBENCREG_WRITE),
			GetReg(usSRegHoldBuf[ENCCALCTRL], SFBENCREG_READ), usSRegHoldBuf[ENCREGADDR], &usSRegHoldBuf[ENCREGVAL]);
		
		usSRegInBuf[ENCCALSTATUS] = (usSRegInBuf[ENCCALSTATUS] & 0xFF) | ((uint16)encCalState << 8);
	}
#else // #if (ENCSPI_Source == ENCSPI_MT)
	uint8 encCalState;
	if (mcEncoder.SPI.EncSel == ENCSEL_MOTOR)
	{
		encCalState = MT68_Calibration(&EncMT1, GetReg(usSRegHoldBuf[ENCCALCTRL], ENCCAL_START),
			GetReg(usSRegHoldBuf[ENCCALCTRL], ENCCAL_SAVE), GetReg(usSRegHoldBuf[ENCCALCTRL], ENCREG_WRITE),
			GetReg(usSRegHoldBuf[ENCCALCTRL], ENCREG_READ), usSRegHoldBuf[ENCREGADDR], &usSRegHoldBuf[ENCREGVAL]);
		
		usSRegInBuf[ENCCALSTATUS] = (usSRegInBuf[ENCCALSTATUS] & 0xFF00) | encCalState;
	}
	else
	{
		encCalState = MT68_Calibration(&EncMT1, GetReg(usSRegHoldBuf[ENCCALCTRL], SFBENCCAL_START),
			GetReg(usSRegHoldBuf[ENCCALCTRL], SFBENCCAL_SAVE), GetReg(usSRegHoldBuf[ENCCALCTRL], SFBENCREG_WRITE),
			GetReg(usSRegHoldBuf[ENCCALCTRL], SFBENCREG_READ), usSRegHoldBuf[ENCREGADDR], &usSRegHoldBuf[ENCREGVAL]);
		
		usSRegInBuf[ENCCALSTATUS] = (usSRegInBuf[ENCCALSTATUS] & 0xFF) | ((uint16)encCalState << 8);
	}
#endif
}


/*---------------------------------------------------------------------------
 * Name		:	SPI_Encoder_GetPos
 * Input	:	*pEncPos - encoder value
 * Output	:	encoder error status
 * Description:	Get SPI encoder value
 *---------------------------------------------------------------------------*/
uint16 SPI_Encoder_GetPos(uint32* pEncPos)
{
	uint8 EncSPIData[4] = { 0 };
	uint16 errCode = 0;
	
#if ENC_SPI_DMA_ENABLED

	DESELECT_SPI;
	
//	if (readbit_csr(ENCSPI1_WR_DMA_CR, DMABSY) && readbit_csr(ENCSPI1_RD_DMA_CR, DMABSY) && readbit_csr(SPI1_SR, SPIIF))
	if(mcEncoder.SPI.FirstFlag != 0)
	{
#if (ENCSPI_Source == ENCSPI_KTH)
		EncSPIData[0] = EncSPIReadData[0];
		EncSPIData[1] = EncSPIReadData[1];
		EncSPIData[2] = EncSPIReadData[2];
		EncSPIData[3] = EncSPIReadData[3];
#else
		EncSPIData[0] = EncSPIReadData[2];
		EncSPIData[1] = EncSPIReadData[3];
		EncSPIData[2] = EncSPIReadData[4];
		EncSPIData[3] = EncSPIReadData[5];
#endif
	}
	
#if ENCODER_CALIBRATE_ENABLED
	SPI_Encoder_Calibration();
#endif
		
	clr_csr(SPI1_SR, SPIIF);
	
	set_csr(ENCSPI1_RD_DMA_CR, DMAEN);
	set_csr(ENCSPI1_WR_DMA_CR, DMAEN);
	
	SELECT_SPI;

	set_csr(ENCSPI1_WR_DMA_CR, DMABSY);
	set_csr(ENCSPI1_RD_DMA_CR, DMABSY); // Read busy must be placed after write busy

#else
	SELECT_SPI;
	
#if (ENCSPI_Source == ENCSPI_KTH)	
	uint8 dataSend = KTH71_READ_ANGLE;
	SPI_TransmitReceive(SEL_SPI1, &dataSend, &EncSPIData[1], 1, 3);
#else
	uint8 dataSend[2] = { 0xA0, 0x03 };
	SPI_Transmit(SEL_SPI1, dataSend, 2, 0xFF);
	SPI_Receive(SEL_SPI1, EncSPIData, 4, 0xFF);
#endif

	DESELECT_SPI;
	
#if ENCODER_CALIBRATE_ENABLED
	SPI_Encoder_Calibration();
#endif

#endif // #if ENC_SPI_DMA_ENABLED
	
	if (mcEncoder.SPI.FirstFlag == 0)
	{
		mcEncoder.SPI.FirstFlag = 1;
		return errCode;
	}

#if (ENCSPI_Source == ENCSPI_KTH)
	if (CalCRC8(&EncSPIData[1], 3, 0x55))
	{
		mcEncoder.SPI.SingleLatch = mcEncoder.SPI.Single;
		mcEncoder.SPI.Single = (((uint16)EncSPIData[1] << 8) + EncSPIData[2]);
#else		
	if (CalCRC8(EncSPIData, 4, 0x00)) 			// 
	{
		mcEncoder.SPI.SingleLatch = mcEncoder.SPI.Single;
		mcEncoder.SPI.Single = (((uint32) EncSPIData[0] << 13) + ((uint32) EncSPIData[1] << 5) 
			+ ((uint32) EncSPIData[2] >> 3));
		
		errCode = (EncSPIData[2] & 0x07) << 2;
#endif	
		mcEncoder.SPI.Single = (mcEncoder.SPI.Single >> mcEncoder.SPI.ZeroBits);
		if (mcEncoder.SPI.Single > mcEncoder.SPI.SingleLatch &&
			mcEncoder.SPI.Single - mcEncoder.SPI.SingleLatch > mcEncoder.SPI.SingleHalf)
			mcEncoder.SPI.Multi--;
		else if (mcEncoder.SPI.SingleLatch > mcEncoder.SPI.Single &&
			mcEncoder.SPI.SingleLatch - mcEncoder.SPI.Single > mcEncoder.SPI.SingleHalf)
			mcEncoder.SPI.Multi++;

		mcEncoder.SPI.EncData = (mcEncoder.SPI.Multi << mcEncoder.SPI.ValidBits) + mcEncoder.SPI.Single;
	}
	else
	{
		errCode = FAULT_ENC_CRC;
	}
		
	*pEncPos = mcEncoder.SPI.EncData;
	return errCode;
}
#endif // #if ENCODER_SEL_SPI_ENABLED > 0