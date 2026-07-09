/*
 * Copyright (c) 2025-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : EncSPI2.c
 * Author        : Summer
 * Date          : 2025-09-21
 * Description   : SPI2 Encoder decoding function.
 *
 * Record        :
 * V1.0, 2025-09-21, Summer: Created file
 */


#include <Myproject.h>
#include <Encoder.h>


#if ENCODER_SEL_SPI2_ENABLED > 0

#if ENC_SPI2_DMA_ENABLED
UINT8 EncSPI2ReadData[ENC_SPI2_LEN] = { 0 };
UINT8 EncSPI2WriteData[ENC_SPI2_LEN] = { 0 };
#endif


/*---------------------------------------------------------------------------
 * Name		:	SPI2_Encoder_Init
 * Input	:	No
 * Output	:	No
 * Description:	SPI2 encoder initialization
 *---------------------------------------------------------------------------*/
void SPI2_Encoder_Init(void)
{
	SPI2_Init();
	
#if ENC_SPI2_DMA_ENABLED
	// Read
	write_csr(ENCSPI2_RD_DMA_CR, DMA_SPI2_Read);
	write_csr(ENCSPI2_RD_DMA_LEN, ENC_SPI2_LEN - 1);
	write_csr(ENCSPI2_RD_DMA_BA, EncSPI2ReadData);
	clr_csr(ENCSPI2_RD_DMA_CR, DMAEN);

	// Write
	write_csr(ENCSPI2_WR_DMA_CR, DMA_SPI2_Send);
	write_csr(ENCSPI2_WR_DMA_LEN, ENC_SPI2_LEN - 1);
	write_csr(ENCSPI2_WR_DMA_BA, EncSPI2WriteData);
	clr_csr(ENCSPI2_WR_DMA_CR, DMAEN);
#endif
	
#ifdef ENCCAL_PIN
	clr_csr(ENCCAL_GPIO, ENCCAL_PIN);
	set_csr(ENCCAL_OE, ENCCAL_PIN);		// Output enable /* 0: Enable digital output */
#endif

#if (ENCSPI2_Source == ENCSPI_KTH)
	KTH71_Init(&EncKTH2, SEL_SPI2);
#else
	MT68_Init(&EncMT2, SEL_SPI2);
#endif
}


/*---------------------------------------------------------------------------
 * Name		:	SPI2_Encoder_Enable
 * Input	:	No
 * Output	:	No
 * Description:	SPI2 encoder enable
 *---------------------------------------------------------------------------*/
void SPI2_Encoder_Enable(uint8 EncSel)
{
	clr_csr(CK_CR, BISSCKEN);				// Disable BiSS module clock
	set_csr(SPI2_CR, SPIEN);				// SPI enable 0-->Disable 1-->Enable
	
	mcEncoder.SPI2.Multi = 0;
	mcEncoder.SPI2.EncSel = EncSel;
	
	if (EncSel == ENCSEL_MOTOR)
	{
		usSRegInBuf[ENCSPISRC] = (usSRegInBuf[ENCSPISRC] & 0xFF00) | ENCSPI2_Source;
	}
	else
	{
		usSRegInBuf[ENCSPISRC] = (usSRegInBuf[ENCSPISRC] & 0x00FF) | ((uint16)ENCSPI2_Source << 8);
	}
	
#if (ENCSPI2_Source == ENCSPI_KTH)
	mcEncoder.SPI2.DataBits = 16;
#else
	mcEncoder.SPI2.DataBits = 21;
#endif
	mcEncoder.SPI2.ZeroBits = 0;
	mcEncoder.SPI2.ValidBits = mcEncoder.SPI2.DataBits - mcEncoder.SPI2.ZeroBits;
	mcEncoder.SPI2.DataMask = (1 << mcEncoder.SPI2.ValidBits) - 1;
	mcEncoder.SPI2.SingleHalf = 1 << (mcEncoder.SPI2.ValidBits - 1);
	mcEncoder.SPI2.Single = mcEncoder.SPI2.SingleHalf;
	mcEncoder.SPI2.Multi = 0;
	mcEncoder.SPI2.FirstFlag = 0;
	
#if (ENCSPI2_Source == ENCSPI_KTH)
	KTH71_Init(&EncKTH2, SEL_SPI2);
#else
	MT68_Init(&EncMT2, SEL_SPI2);
	
#if ENC_SPI2_DMA_ENABLED
	EncSPI2WriteData[0] = 0xA0;
	EncSPI2WriteData[1] = 0x03;
#endif
#endif
	
	DESELECT_SPI2; // Pull high NSS pin
}


/*---------------------------------------------------------------------------
 * Name		:	SPI2_Encoder_Disable
 * Input	:	No
 * Output	:	No
 * Description:	SPI2 encoder disable
 *---------------------------------------------------------------------------*/
void SPI2_Encoder_Disable(void)
{
	DESELECT_SPI2;			// Pull high NSS pin
	clr_csr(SPI2_CR, SPIEN);				// SPI enable 0-->Disable 1-->Enable
}


/*---------------------------------------------------------------------------
 * Name		:	SPI2_Encoder_Update
 * Input	:	No
 * Output	:	No
 * Description:	SPI2 encoder parameter update
 *---------------------------------------------------------------------------*/
void SPI2_Encoder_Update(void)
{
	if (mcEncoder.SPI2.EncSel == ENCSEL_MOTOR && mcEncoder.SPI2.ZeroBits != usSRegHoldBuf[ENCZEROBITS])
	{
		mcEncoder.SPI2.ZeroBits = usSRegHoldBuf[ENCZEROBITS];
		mcEncoder.SPI2.ValidBits = mcEncoder.SPI2.DataBits - mcEncoder.SPI2.ZeroBits;
		mcEncoder.SPI2.DataMask = (1 << mcEncoder.SPI2.ValidBits) - 1;
		mcEncoder.SPI2.SingleHalf = 1 << (mcEncoder.SPI2.ValidBits - 1);
	}
}


/*---------------------------------------------------------------------------
 * Name		:	SPI2_Encoder_Calibration
 * Input	:	No
 * Output	:	No
 * Description:	SPI2 encoder calibration
 *---------------------------------------------------------------------------*/
void SPI2_Encoder_Calibration(void)
{
#if (ENCSPI2_Source == ENCSPI_KTH)
	uint8 encCalState;
	if (mcEncoder.SPI2.EncSel == ENCSEL_MOTOR)
	{
		encCalState = KTH71_Calibration(&EncKTH2, GetReg(usSRegHoldBuf[ENCCALCTRL], ENCCAL_START),
			GetReg(usSRegHoldBuf[ENCCALCTRL], ENCCAL_SAVE), GetReg(usSRegHoldBuf[ENCCALCTRL], ENCREG_WRITE),
			GetReg(usSRegHoldBuf[ENCCALCTRL], ENCREG_READ), usSRegHoldBuf[ENCREGADDR], &usSRegHoldBuf[ENCREGVAL]);
		
		usSRegInBuf[ENCCALSTATUS] = (usSRegInBuf[ENCCALSTATUS] & 0xFF00) | encCalState;
	}
	else
	{
		encCalState = KTH71_Calibration(&EncKTH2, GetReg(usSRegHoldBuf[ENCCALCTRL], SFBENCCAL_START),
			GetReg(usSRegHoldBuf[ENCCALCTRL], SFBENCCAL_SAVE), GetReg(usSRegHoldBuf[ENCCALCTRL], SFBENCREG_WRITE),
			GetReg(usSRegHoldBuf[ENCCALCTRL], SFBENCREG_READ), usSRegHoldBuf[ENCREGADDR], &usSRegHoldBuf[ENCREGVAL]);
		
		usSRegInBuf[ENCCALSTATUS] = (usSRegInBuf[ENCCALSTATUS] & 0xFF) | ((uint16)encCalState << 8);
	}
#else // #if (ENCSPI2_Source == ENCSPI_MT)
	uint8 encCalState;
	if (mcEncoder.SPI2.EncSel == ENCSEL_MOTOR)
	{
		encCalState = MT68_Calibration(&EncMT2, GetReg(usSRegHoldBuf[ENCCALCTRL], ENCCAL_START),
			GetReg(usSRegHoldBuf[ENCCALCTRL], ENCCAL_SAVE), GetReg(usSRegHoldBuf[ENCCALCTRL], ENCREG_WRITE),
			GetReg(usSRegHoldBuf[ENCCALCTRL], ENCREG_READ), usSRegHoldBuf[ENCREGADDR], &usSRegHoldBuf[ENCREGVAL]);

		usSRegInBuf[ENCCALSTATUS] = (usSRegInBuf[ENCCALSTATUS] & 0xFF00) | encCalState;
	}
	else
	{
		encCalState = MT68_Calibration(&EncMT2, GetReg(usSRegHoldBuf[ENCCALCTRL], SFBENCCAL_START),
			GetReg(usSRegHoldBuf[ENCCALCTRL], SFBENCCAL_SAVE), GetReg(usSRegHoldBuf[ENCCALCTRL], SFBENCREG_WRITE),
			GetReg(usSRegHoldBuf[ENCCALCTRL], SFBENCREG_READ), usSRegHoldBuf[ENCREGADDR], &usSRegHoldBuf[ENCREGVAL]);

		usSRegInBuf[ENCCALSTATUS] = (usSRegInBuf[ENCCALSTATUS] & 0xFF) | ((uint16)encCalState << 8);
	}
#endif
}


/*---------------------------------------------------------------------------
 * Name		:	SPI2_Encoder_GetPos
 * Input	:	*pEncPos - encoder value
 * Output	:	encoder error status
 * Description:	Get SPI2 encoder value
 *---------------------------------------------------------------------------*/
uint16 SPI2_Encoder_GetPos(uint32* pEncPos) 
{
	uint8 EncSPIData[4] = { 0 };
	uint16 errCode = 0;
	
#if ENC_SPI2_DMA_ENABLED

	DESELECT_SPI2;
	
//	if (readbit_csr(ENCSPI2_WR_DMA_CR, DMABSY) && readbit_csr(ENCSPI2_RD_DMA_CR, DMABSY) && readbit_csr(SPI2_SR, SPIBSY))
	if (mcEncoder.SPI2.FirstFlag != 0)
	{
#if (ENCSPI2_Source == ENCSPI_KTH)
		EncSPIData[0] = EncSPI2ReadData[0];
		EncSPIData[1] = EncSPI2ReadData[1];
		EncSPIData[2] = EncSPI2ReadData[2];
		EncSPIData[3] = EncSPI2ReadData[3];
#else
		EncSPIData[0] = EncSPI2ReadData[2];
		EncSPIData[1] = EncSPI2ReadData[3];
		EncSPIData[2] = EncSPI2ReadData[4];
		EncSPIData[3] = EncSPI2ReadData[5];
#endif
	}
	
#if ENCODER_CALIBRATE_ENABLED
	SPI2_Encoder_Calibration();
#endif
	
	clr_csr(SPI2_SR, SPIIF);
	
	set_csr(ENCSPI2_RD_DMA_CR, DMAEN);
	set_csr(ENCSPI2_WR_DMA_CR, DMAEN);
	
	SELECT_SPI2;

	set_csr(ENCSPI2_WR_DMA_CR, DMABSY);
	set_csr(ENCSPI2_RD_DMA_CR, DMABSY); // Read busy must be placed after write busy

#else
	SELECT_SPI2;
		
#if (ENCSPI2_Source == ENCSPI_KTH)	
	uint8 dataSend = KTH71_READ_ANGLE;
	SPI_TransmitReceive(SEL_SPI2, &dataSend, &EncSPIData[1], 1, 3);
#else
	uint8 dataSend[2] = { 0xA0, 0x03 };
	SPI_Transmit(SEL_SPI2, dataSend, 2, 0xFF);
	SPI_Receive(SEL_SPI2, EncSPIData, 4, 0xFF);
#endif

	DESELECT_SPI2;
	
#if ENCODER_CALIBRATE_ENABLED
	SPI2_Encoder_Calibration();
#endif
#endif // #if ENC_SPI2_DMA_ENABLED
	

	if (mcEncoder.SPI2.FirstFlag == 0)
	{
		mcEncoder.SPI2.FirstFlag = 1;
		return errCode;
	}

#if (ENCSPI2_Source == ENCSPI_KTH)
	if (CalCRC8(&EncSPIData[1], 3, 0x55))
	{
		mcEncoder.SPI2.SingleLatch = mcEncoder.SPI2.Single;
		mcEncoder.SPI2.Single = (((uint16)EncSPIData[1] << 8) + EncSPIData[2]);
#else
	if (CalCRC8(EncSPIData, 4, 0x00)) 			//
	{
		mcEncoder.SPI2.SingleLatch = mcEncoder.SPI2.Single;
		mcEncoder.SPI2.Single = (((uint32)EncSPIData[0] << 13) + ((uint32)EncSPIData[1] << 5)
			+((uint32)EncSPIData[2] >> 3));

		errCode = (EncSPIData[2] & 0x07) << 2;
#endif
		
		mcEncoder.SPI2.Single = (mcEncoder.SPI2.Single >> mcEncoder.SPI2.ZeroBits);
		if (mcEncoder.SPI2.Single > mcEncoder.SPI2.SingleLatch &&
			mcEncoder.SPI2.Single - mcEncoder.SPI2.SingleLatch > mcEncoder.SPI2.SingleHalf)
			mcEncoder.SPI2.Multi--;
		else if (mcEncoder.SPI2.SingleLatch > mcEncoder.SPI2.Single &&
			mcEncoder.SPI2.SingleLatch - mcEncoder.SPI2.Single > mcEncoder.SPI2.SingleHalf)
			mcEncoder.SPI2.Multi++;

		mcEncoder.SPI2.EncData = (mcEncoder.SPI2.Multi << mcEncoder.SPI2.ValidBits) + mcEncoder.SPI2.Single;
	}
	else
	{
		errCode = FAULT_ENC_CRC;
	}
		
	*pEncPos = mcEncoder.SPI2.EncData;
	
	return errCode;
}
#endif // #if ENCODER_SEL_SPI2_ENABLED > 0