/*
 * Copyright (c) 2022-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : EncTMG.c
 * Author        : Victor Jin
 * Date          : 2022-09-21
 * Description   : Serial Encoder decoding function.
 *
 * Record        :
 * V1.0, 2022-09-21, Victor Jin: Created file
 */


#include <Myproject.h>
#include <Encoder.h>

#if ENCODER_SEL_TMG_ENABLED > 0

/*---------------------------------------------------------------------------
 * Name		:	TMG_Encoder_Init
 * Input	:	No
 * Output	:	No
 * Description:	Serial encoder initialization
 *---------------------------------------------------------------------------*/
void TMG_Encoder_Init(void)
{
#if (SLRE_GPIO == PA && SLRE_PIN == PIN13)
	clr_csr(CMP_CR6, SFRCT2);	// Tamagawa RE function select: 00-PA12; 01-PA13
	set_csr(PH_SEL, SFRCT);		// Tamagawa RE function select: 10-PC0; 11-PA13
#elif (SLRE_GPIO == PC && SLRE_PIN == PIN0)
	set_csr(CMP_CR6, SFRCT2);	// Tamagawa RE function select: 00-PA12; 01-PA13
	clr_csr(PH_SEL, SFRCT);		// Tamagawa RE function select: 10-PC0; 11-PA13
#else
	clr_csr(CMP_CR6, SFRCT2);	// Tamagawa RE function select: 00-PA12; 01-PA13
	clr_csr(PH_SEL, SFRCT);		// Tamagawa RE function select: 10-PC0; 11-PA13
#endif 
	/****************************************************************
	Initialization sends one Request first; subsequent interrupts receive status flag before sending,
	DMA receives data during interrupt idle time to avoid waiting in interrupt
	*****************************************************************/
	// 32-bit buff format: 00(reserved)+xx(EE content)+xx(EE address)+IDC_Code (EE content and address valid only when ID is 6 or D)
	mcEncoder.TMG.TxRx_XRAM_Buf[0] = ID_0;
	write_csr(REG_DMA_BA, mcEncoder.TMG.TxRx_XRAM_Buf);			// DMA channel XRAM base address config
	write_csr(REG_DMA_CR, DMA_SF_Read);
	clr_csr(REG_DMA_CR, DMAEN);									// DMA enable
	clr_csr(REG_DMA_CR, DMAIE);									// DMA interrupt enable

	clr_csr(SF_CR, SF_EN);										// Related module enable
	clr_csr(SF_CR, SEND_REQ);									// Start send request command

	// Absolute encoder auto-trigger period: 00: every 1 PWM interrupt; 01: every 2 PWM interrupts
	// Absolute encoder auto-trigger period: 10: every 4 PWM interrupts; 11: every 8 PWM interrupts
#if DRV32K_ENABLE_SWITCH > 0
	clr_csr(DRV1_FCR5, ENCODER_STA_CYCLE1);
	set_csr(DRV1_FCR5, ENCODER_STA_CYCLE0);
#else
	clr_csr(DRV1_FCR5, ENCODER_STA_CYCLE1);
	clr_csr(DRV1_FCR5, ENCODER_STA_CYCLE0);
#endif
	
	write_csr(SF_BAUD, 0x0012); // Encoder serial interface baud rate register
}


/*---------------------------------------------------------------------------
 * Name		:	TMG_Encoder_Enable
 * Input	:	No
 * Output	:	No
 * Description:	Serial encoder enable
 *---------------------------------------------------------------------------*/
void TMG_Encoder_Enable(void)
{
	mcEncoder.TMG.Multi = 0;
	clr_csr(CK_CR, BISSCKEN);								// Disable BiSS module clock
	set_csr(CK_CR, SFCKEN);									// Enable TMG module clock
	
#ifdef MARE_PIN
	set_csr(MARE_GPIO, MARE_PIN);							// Pull high MA RE pin
#endif

	if (mcEncoder.TypeSelect == ENCODER_SEL_TMG_ABS_SIN || mcEncoder.TypeSelect == ENCODER_SEL_TMG_ABS_MUL)
		mcEncoder.TMG.TxRx_XRAM_Buf[0] = ID_3;	
	else
		mcEncoder.TMG.TxRx_XRAM_Buf[0] = ID_0;
	set_csr(REG_DMA_CR, DMAEN);								// DMA enable
	set_csr(SF_CR, SF_EN);									// Related module enable
	set_csr(SF_CR, SF_AUTO_EN);								// Auto-trigger enable
}


/*---------------------------------------------------------------------------
 * Name		:	TMG_Encoder_Disable
 * Input	:	No
 * Output	:	No
 * Description:	Serial encoder disable
 *---------------------------------------------------------------------------*/
void TMG_Encoder_Disable(void)
{
	clr_csr(CK_CR, SFCKEN);									// Disable TMG module clock
	clr_csr(REG_DMA_CR, DMAEN);								// DMA disable
	clr_csr(SF_CR, SF_AUTO_EN);								// Disable auto-trigger enable
	clr_csr(SF_CR, SF_EN);									// Related module disable
}


/*---------------------------------------------------------------------------
 * Name		:	TMG_Encoder_Update
 * Input	:	No
 * Output	:	No
 * Description:	Serial encoder parameter update, e.g. data length
 *---------------------------------------------------------------------------*/
void TMG_Encoder_Update(void)
{
	if (mcEncoder.TMG.ValidBits != usSRegHoldBuf[ENCVALIDBITS])
	{
		mcEncoder.TMG.ValidBits = usSRegHoldBuf[ENCVALIDBITS];
		mcEncoder.TMG.SingleHalf = 1 << (mcEncoder.TMG.ValidBits - 1);
	}
	mcEncoder.TMG.ZeroBits = usSRegHoldBuf[ENCZEROBITS];

	// Clear Multiturn value and error
	if (!GetReg(mcRegParam.DriveCtrl, CTRL_CLEARENC) && GetReg(usSRegHoldBuf[DRIVECTRL], CTRL_CLEARENC))
		mcEncoder.TMG.ClearMultiFlag = 1;
}


/*---------------------------------------------------------------------------
 * Name		:	TMG_Encoder_GetMultiAbsPos
 * Input	:	*pEncPos - encoder value
 * Output	:	encoder error status
 * Description:	Get serial encoder value, read single-turn absolute + ENID + multi-turn count + ALMC(Encoder Err) (ID_3) 
 *				Returns the most complete info but takes the longest time,
 *				ALMC is returned only under ID_3, providing detailed explanation of fault codes in SF(status field)
 *				Hot-plugging encoder will cause ALMC Err, so it is recommended to reset after changing encoder type while powered
 *---------------------------------------------------------------------------*/
uint16 TMG_Encoder_GetMultiAbsPos(uint32* pEncPos)
{
	uint8 EncStatus, EncError;
	uint32 EncSingle, EncMulti;
	uint16 CommStatus;
	uint16 errCode = 0;

	/* Wait for data */
	CommStatus = read_csr(SF_SR);
//	ControlField = mcEncoder.TMG.TxRx_XRAM_Buf[0] & 0x000000ff;				// TMG returned control field CF
	EncStatus = (mcEncoder.TMG.TxRx_XRAM_Buf[0] & 0x0000ff00) >> 8;			// TMG returned status field SF
	EncSingle = (mcEncoder.TMG.TxRx_XRAM_Buf[0] & 0xffff0000) >> 16;		// TMG single-turn absolute position
	EncSingle += (mcEncoder.TMG.TxRx_XRAM_Buf[1] & 0x000000ff) << 16;
	EncMulti = (mcEncoder.TMG.TxRx_XRAM_Buf[1] & 0xffff0000) >> 16;			// TMG multi-turn value
	EncError = (mcEncoder.TMG.TxRx_XRAM_Buf[2] & 0x0000ff00) >> 8;			// TMG detailed fault code explanation (only available under ID_3)

	mcEncoder.EncLoopTime = 1;
	if (CommStatus & SF_DONE) // Successfully received encoder data complete	
	{
		mcEncoder.TMG.TxRx_XRAM_Buf[0] = ID_3;		//Read single-turn absolute + ENID + multi-turn count + ALMC (Encoder Err)
		if (CommStatus & SF_SUC)	// Successfully received encoder return data
		{
			mcEncoder.TMG.EncData = (EncMulti << mcEncoder.TMG.ValidBits) +
				(EncSingle >> mcEncoder.TMG.ZeroBits);	// Multi-turn absolute position

			errCode = ((EncStatus & 0xC0) << 2) + EncError;
			mcEncoder.EncLoopTime = 0;
			clr_csr(SF_SR, SF_SUC);	//Clear receive success flag
		}
		else	// Failed to receive encoder return data - communication fault
		{
			// Detect CRC error/frame sync error/request command error/request timeout error
			errCode = (CommStatus << TMG_ERRSHIFT) & TMG_ERRMASK;
		}
		clr_csr(SF_SR, SF_DONE);	//Clear receive complete flag
	}
	else	// Failed to receive encoder return data - communication fault
	{
		// Detect CRC error/frame sync error/request command error/request timeout error
		errCode = (CommStatus << TMG_ERRSHIFT) & TMG_ERRMASK;
	}
	
	*pEncPos = mcEncoder.TMG.EncData;
	return errCode;
}


/*---------------------------------------------------------------------------
 * Name		:	TMG_Encoder_GetSingleAbsPos
 * Input	:	*pEncPos - encoder value
 * Output	:	encoder error status
 * Description:	Get serial encoder value, read single-turn absolute (ID_0), only returns single-turn absolute and status field
 *---------------------------------------------------------------------------*/
uint16 TMG_Encoder_GetSingleAbsPos(uint32* pEncPos)
{
	uint8 EncStatus;
	uint32 EncSingle;
	uint16 CommStatus;
	uint16 errCode = 0;

	/* Wait for data */
	CommStatus = read_csr(SF_SR);
//	mcEncoder.TMG.CF = mcEncoder.TMG.TxRx_XRAM_Buf[0] & 0x000000ff;			// TMG returned control field CF
	EncStatus = (mcEncoder.TMG.TxRx_XRAM_Buf[0] & 0x0000ff00) >> 8;		// TMG returned status field SF
	EncSingle = (mcEncoder.TMG.TxRx_XRAM_Buf[0] & 0xffff0000) >> 16;		// TMG single-turn absolute position
	EncSingle += (mcEncoder.TMG.TxRx_XRAM_Buf[1] & 0x000000ff) << 16;
	
	mcEncoder.EncLoopTime = 1;
	if (CommStatus & SF_DONE)
	{
		mcEncoder.TMG.TxRx_XRAM_Buf[0] = ID_0;		// Read single-turn absolute value
		if (CommStatus & SF_SUC)	// Successfully received encoder return data
		{
			mcEncoder.EncLoopTime = 0;
			mcEncoder.TMG.SingleLatch = mcEncoder.TMG.Single;
			mcEncoder.TMG.Single = EncSingle >> mcEncoder.TMG.ZeroBits;
			
			if (mcEncoder.TMG.Single > mcEncoder.TMG.SingleLatch &&
				mcEncoder.TMG.Single - mcEncoder.TMG.SingleLatch > mcEncoder.TMG.SingleHalf)
				mcEncoder.TMG.Multi--;
			else if (mcEncoder.TMG.SingleLatch > mcEncoder.TMG.Single &&
				mcEncoder.TMG.SingleLatch - mcEncoder.TMG.Single > mcEncoder.TMG.SingleHalf)
				mcEncoder.TMG.Multi++;

			mcEncoder.TMG.EncData = (mcEncoder.TMG.Multi << mcEncoder.TMG.ValidBits) + mcEncoder.TMG.Single;
			
			errCode = ((EncStatus & 0xC0) << 2) | ((EncStatus & 0x10) >> 2)
				|((EncStatus & 0x20) >> 4); // ca01 + ea01

			clr_csr(SF_SR, SF_SUC);	//Clear receive success flag
		}
		else	// Failed to receive encoder return data - communication fault
		{
			// Detect CRC error/frame sync error/request command error/request timeout error
			errCode = (CommStatus << TMG_ERRSHIFT) & TMG_ERRMASK;	
		}
		clr_csr(SF_SR, SF_DONE);	//Clear receive complete flag
	}
	else	// Failed to receive encoder return data - communication fault
	{
		// Detect CRC error/frame sync error/request command error/request timeout error
		errCode = (CommStatus << TMG_ERRSHIFT) & TMG_ERRMASK;
	}
	
	*pEncPos = mcEncoder.TMG.EncData;
	return errCode;
}


/*---------------------------------------------------------------------------
 * Name		:	TMG_Encoder_GetMultiTurns
 * Input	:	*pEncMulti - encoder turn count
 * Output	:	encoder error status
 * Description:	Get serial encoder value, read multi-turn value (ID_1), only returns multi-turn value and status field
 *---------------------------------------------------------------------------*/
uint16 TMG_Encoder_GetMultiTurns(uint32* pEncMulti)
{
	uint8 EncStatus;
	uint32 EncMulti;
	uint16 CommStatus;
	uint16 errCode = 0;

	/* Wait for data */
	CommStatus = read_csr(SF_SR);
//	mcEncoder.TMG.CF = mcEncoder.TMG.TxRx_XRAM_Buf[0] & 0x000000ff;			// TMG returned control field CF
	EncStatus = (mcEncoder.TMG.TxRx_XRAM_Buf[0] & 0x0000ff00) >> 8;		// TMG returned status field SF
	EncMulti = (mcEncoder.TMG.TxRx_XRAM_Buf[0] & 0xffff0000) >> 16; // TMG multi-turn count value

	mcEncoder.EncLoopTime = 1;
	if (CommStatus & SF_DONE)
	{
		mcEncoder.TMG.TxRx_XRAM_Buf[0] = ID_1;		// Read single-turn absolute value
		if (CommStatus & SF_SUC)	// Successfully received encoder return data
		{
			mcEncoder.EncLoopTime = 0;
			errCode = ((EncStatus & 0xC0) << 2) | ((EncStatus & 0x10) >> 2)
				|((EncStatus & 0x20) >> 4); // ca01 + ea01

			clr_csr(SF_SR, SF_SUC);	//Clear receive success flag
		}
		else // Failed to receive encoder return data - communication fault
		{
			// Detect CRC error/frame sync error/request command error/request timeout error
			errCode = (CommStatus << TMG_ERRSHIFT) & TMG_ERRMASK;
		}
		clr_csr(SF_SR, SF_DONE);	//Clear receive complete flag
	}
	else	// Failed to receive encoder return data - communication fault
	{
		// Detect CRC error/frame sync error/request command error/request timeout error
		errCode = (CommStatus << TMG_ERRSHIFT) & TMG_ERRMASK;
	}

	*pEncMulti = EncMulti;
	return errCode;
}


/*---------------------------------------------------------------------------
 * Name		:	TMG_Encoder_Reset
 * Input	:	Reset_ID - 
 *						ID_7 - Reset all encoder faults
 *						ID_8 - Reset single-turn absolute position to 0
 *						ID_C - Reset multi-turn count (without resetting single-turn absolute) + all encoder faults
 * Output	:	encoder error status
 * Description:	Serial encoder fault, single-turn position, multi-turn value reset
 *				Shaft must be stationary; transmit this function 10 times with interval >= 40us to complete reset
 *---------------------------------------------------------------------------*/
uint16 TMG_Encoder_Reset(uint8 Reset_ID)
{
	uint8 EncStatus;
	uint16 CommStatus;
	uint16 errCode = 0;

	/* Wait for data */
	CommStatus = read_csr(SF_SR);
//	mcEncoder.TMG.CF = mcEncoder.TMG.TxRx_XRAM_Buf[0] & 0x000000ff;			// TMG returned control field CF
	EncStatus = (mcEncoder.TMG.TxRx_XRAM_Buf[0] & 0x0000ff00) >> 8;		// TMG returned status field SF
//	EncSingle = (mcEncoder.TMG.TxRx_XRAM_Buf[0] & 0xffff0000) >> 16;		// TMG single-turn absolute position
//	EncSingle += (mcEncoder.TMG.TxRx_XRAM_Buf[1] & 0x000000ff) << 16;
	
	mcEncoder.EncLoopTime = 1;
	if (CommStatus & SF_DONE)
	{
		mcEncoder.TMG.TxRx_XRAM_Buf[0] = Reset_ID;
		if (CommStatus & SF_SUC)	// Successfully received encoder return data
		{
			mcEncoder.EncLoopTime = 0;
			errCode = ((EncStatus & 0xC0) << 2) | ((EncStatus & 0x10) >> 2)
				|((EncStatus & 0x20) >> 4); // ca01 + ea01

			clr_csr(SF_SR, SF_SUC);	//Clear receive success flag
		}
		else	// Failed to receive encoder return data - communication fault
		{
			// Detect CRC error/frame sync error/request command error/request timeout error
			errCode = (CommStatus << TMG_ERRSHIFT) & TMG_ERRMASK;
		}
		clr_csr(SF_SR, SF_DONE);	//Clear receive complete flag
	}
	else	// Failed to receive encoder return data - communication fault
	{
		// Detect CRC error/frame sync error/request command error/request timeout error
		errCode = (CommStatus << TMG_ERRSHIFT) & TMG_ERRMASK;
	}
	
	return errCode;
}


/*---------------------------------------------------------------------------
 * Name		:	TMG_Encoder_ReadEEPROM
 * Input	:	AddressField - Address to read (ADF)
 *						Measured 17-bit absolute encoder readable address range is 0~79,
 *						exceeding this range returns ID_3 data and reports request command error fault
 * Output	:	encoder error status
 * Description:	Read encoder built-in EEPROM value (ID_D)
 *---------------------------------------------------------------------------*/
uint16 TMG_Encoder_ReadEEPROM(uint8 AddressField)
{
	uint16 CommStatus;
	uint16 errCode = 0;

	/* Wait for data */
	CommStatus = read_csr(SF_SR);
//	mcEncoder.TMG.CF = mcEncoder.TMG.TxRx_XRAM_Buf[0] & 0x000000ff;			// TMG returned control field CF
//	mcEncoder.TMG.ADF = (mcEncoder.TMG.TxRx_XRAM_Buf[0] & 0x0000ff00) >> 8;		// TMG EEPROM read operation request address field
//	mcEncoder.TMG.EDF = (mcEncoder.TMG.TxRx_XRAM_Buf[0] & 0x00ff0000) >> 16;	// TMG EEPROM read operation returned data EEPROM field

	mcEncoder.EncLoopTime = 1;
	if (CommStatus & SF_DONE)
	{
		// Read TMG encoder built-in EEPROM, 32-bit buff format: 00(reserved)+xx(EE content)+xx(EE address)+IDC_Code (EE content and address valid only when ID is 6 or D)
		mcEncoder.TMG.TxRx_XRAM_Buf[0] = AddressField << 8 | ID_D;
		if (CommStatus & SF_SUC)	// Successfully received encoder return data
		{
			mcEncoder.EncLoopTime = 0;
			errCode = 0;	// Clear communication fault on success
			clr_csr(SF_SR, SF_SUC);	//Clear receive success flag
		}
		else	// Failed to receive encoder return data - communication fault
		{
			// Detect CRC error/frame sync error/request command error/request timeout error
			errCode = (CommStatus << TMG_ERRSHIFT) & TMG_ERRMASK;
		}
		clr_csr(SF_SR, SF_DONE);	//Clear receive complete flag
	}
	else	// Failed to receive encoder return data - communication fault
	{
		// Detect CRC error/frame sync error/request command error/request timeout error
		errCode = (CommStatus << TMG_ERRSHIFT) & TMG_ERRMASK;
	}
	
	return errCode;
}


/*---------------------------------------------------------------------------
 * Name		:	TMG_Encoder_WriteEEPROM
 * Input	:	AddressField - Address to write (ADF)
 *				EepromField  - Content to write (EDF)
 * Output	:	encoder error status
 * Description:	Write encoder built-in EEPROM (ID_6)
 *					Note! Writing EEPROM requires some time, so data returned after sending write request
 *					may read EDF as 0 due to ADF busy bit, so typically after sending write request
 *					send a read request to ensure the EEPROM write operation is complete.
 *---------------------------------------------------------------------------*/
uint16 TMG_Encoder_WriteEEPROM(uint8 AddressField, uint8 EepromField)
{
	uint16 CommStatus;
	uint16 errCode = 0;

	/* Wait for data */
	CommStatus = read_csr(SF_SR);		// For debug, print TMG peripheral status register
//	mcEncoder.TMG.CF = mcEncoder.TMG.TxRx_XRAM_Buf[0] & 0x000000ff;			// TMG returned control field CF
//	mcEncoder.TMG.ADF = (mcEncoder.TMG.TxRx_XRAM_Buf[0] & 0x0000ff00) >> 8;		// TMG EEPROM read operation request address field
//	mcEncoder.TMG.EDF = (mcEncoder.TMG.TxRx_XRAM_Buf[0] & 0x00ff0000) >> 16;	// TMG EEPROM read operation returned data EEPROM field

	
	mcEncoder.EncLoopTime = 1;
	if (CommStatus & SF_DONE)
	{
		// Read TMG encoder built-in EEPROM, 32-bit buff format: 00(reserved)+xx(EE content)+xx(EE address)+IDC_Code (EE content and address valid only when ID is 6 or D)
		mcEncoder.TMG.TxRx_XRAM_Buf[0] = EepromField << 16 | AddressField << 8 | ID_6;
		if (CommStatus & SF_SUC)	// Successfully received encoder return data
		{
			mcEncoder.EncLoopTime = 0;
			errCode = 0;	// Clear communication fault on success
			clr_csr(SF_SR, SF_SUC);	//Clear receive success flag
		}
		else	// Failed to receive encoder return data - communication fault
		{
			// Detect CRC error/frame sync error/request command error/request timeout error
			errCode = (CommStatus << TMG_ERRSHIFT) & TMG_ERRMASK;
		}
		clr_csr(SF_SR, SF_DONE);	//Clear receive complete flag
	}
	else	// Failed to receive encoder return data - communication fault
	{
		// Detect CRC error/frame sync error/request command error/request timeout error
		errCode = (CommStatus << TMG_ERRSHIFT) & TMG_ERRMASK;
	}

	return errCode;
}
#endif
