/********************************************************************************
/************* Copyright (C), 2022, Fortior Technology Co., Ltd.  ***************
/********************************************************************************
/* File Name     : Interrupt.c
/* Author        : Summer HW&RD
/* Date          : 2022-09-23
/* Description   : define interrupt function.
/* Version       : 1.0
/* Record        :
/* V1.0          : 2022-09-23    Summer HW&RD    Created file
/********************************************************************************/



/* Includes -------------------------------------------------------------------------------------*/
#include <Myproject.h>

#define FO_INT        _interrupt_handler_1		// IPM hardware overcurrent interrupt
#define FO2_INT       _interrupt_handler_3		// IPM hardware overcurrent interrupt
#define CMP3_INT	  _interrupt_handler_4		// MOS hardware overcurrent interrupt
#define EXTERN1_INT   _interrupt_handler_2		// EtherCAT external interrupt
#define DRVPIF_INT    _interrupt_handler_6		// Protection interrupt
#define FOC_INT       _interrupt_handler_8		// Carrier interrupt
#define MEFSM_INT     _interrupt_handler_10		// ME state machine interrupt
#define DMA0_INT      _interrupt_handler_12		// DMA serial RX/TX interrupt
#define SYSTICK_INT   _interrupt_handler_15     // Systick interrupt (Not used)
#define TIM3_INT      _interrupt_handler_17		// Position loop interrupt
#define CAN_INT       _interrupt_handler_30		// CAN receive complete interrupt


/*---------------------------------------------------------------------------
 * Name		:	FO_INT
 * Input	:	No
 * Output	:	No
 * Description:	Hardware FO overcurrent protection, shut down output, highest interrupt priority.
 *---------------------------------------------------------------------------*/
#if ((HardwareCurrent_Protect == Hardware_FO_Protect) || (HardwareCurrent_Protect == Hardware_FO_CMP_Protect))
#if (Hardware_FO_SRC == Hardware_FO_EXTI0)
__attribute__((__interrupt__)) void FO_INT(void) // interrupt 1					// Hardware FO overcurrent interrupt, shut down output
{
	if (readbit_csr(EXT0IF, EX0IF13))
	{
		Fault_Handler(FaultHardOVCurrent, FLAG_HARDOVC);
		clr_csr(EXT0IF, EX0IF13);
	}
}
#else
__attribute__((__interrupt__)) void FO2_INT(void) // interrupt 3					// Hardware FO overcurrent interrupt, shut down output
{
	if (readbit_csr(EXT2IF, EX2IE10))
	{
		if (mcFocCtrl.CurLoopEnable == 1) // FO signal may be abnormal when first powered on; must avoid
		{
			Fault_Handler(FaultHardOVCurrent, FLAG_HARDOVC);
		}
		clr_csr(EXT2IF, EX2IE10);
	}
}
#endif  // #if #if (Hardware_FO_SRC == Hardware_FO_EXTI0)
#endif  // #if ((HardwareCurrent_Protect == Hardware_FO_Protect) || (HardwareCurrent_Protect == Hardware_FO_CMP_Protect))


/*---------------------------------------------------------------------------
 * Name		:	CMP3_INT
 * Input	:	No
 * Output	:	No
 * Description:	Hardware comparator overcurrent interrupt, shut down output, highest interrupt priority.
 *---------------------------------------------------------------------------*/
#if ((HardwareCurrent_Protect == Hardware_CMP_Protect) || (HardwareCurrent_Protect == Hardware_FO_CMP_Protect))
__attribute__((__interrupt__)) void CMP3_INT(void)
{
	if (readbit_csr(CMP_IFR, CMP3IF))	
	{
		Fault_Handler(FaultHardOVCurrent, FLAG_HARDOVC);
		clr_csr(CMP_IFR, CMP3IF);
	}
}
#endif 

/*---------------------------------------------------------------------------
 * Name		:	EXTERN1_INT
 * Input	:	No
 * Output	:	No
 * Description:	External interrupt, used for EtherCAT sync0 signal
 *---------------------------------------------------------------------------*/
#if EXCTRL_ECAT_ENABLED
__attribute__((__interrupt__)) void EXTERN1_INT(void) // interrupt 2
{
	if (readbit_csr(EXT1IF, EX1IF8))
	{
		SYNC0_Flag = 1;
		mcFocCtrl.PosLoopTime = 0;		
		mcFocCtrl.Timer1msCount = (uint16)VELCTRL_FREQUENCY - 3;
		EscIntStep = 1;	
		EcatCSPVar.ExcCnt = 3;
		mcEncoder.EncLoopTime = 0;
		clr_csr(EXT1IF, EX1IF8);                    // Clear interrupt flag
	}
}
#endif //#if EXCTRL_ECAT_ENABLED


/*---------------------------------------------------------------------------
 * Name		:	DRVPIF_INT
 * Input	:	No
 * Output	:	No
 * Description:	Hardware protection interrupt 
 *---------------------------------------------------------------------------*/
#if PROT_HARDWARE_ENABLED
__attribute__((__interrupt__)) void DRVPIF_INT(void) // interrupt 6
{
#if PROT_OUVP_HARDWARE_ENABLED
	if (readbit_csr(DRV1_PSR, OVPIF))     // Software over-voltage protection triggered
	{
		mcFaultSource = FaultOverVoltage;
		FaultProcess();
		clr_csr(DRV1_PSR, OVPIF);   
	}
	
	if (readbit_csr(DRV1_PSR, UVPIF))     // Software under-voltage protection triggered
	{
		mcFaultSource = FaultUnderVoltage;
		FaultProcess();
		clr_csr(DRV1_PSR, UVPIF); 
	}
#endif // #if PROT_OUVP_HARDWARE_ENABLED
	
#if PROT_SOCP_HARDWARE_ENABLED
	if (readbit_csr(DRV1_PSR, SOCPIF))     // Software over-current protection triggered
	{
		if (mcCurVarible.PeakCurCnt >= mcCurVarible.PeakCurArr)
		{
			mcCurVarible.PeakCurCnt = 0;
			mcFaultSource = FaultPeakOVCurrent;
			FaultProcess();
		}	
		else
		{
			mcCurVarible.PeakCurCnt++;
		}
		clr_csr(DRV1_PSR, SOCPIF); 
	}
#endif // #if PROT_SOCP_HARDWARE_ENABLED
	
#if PROT_OVEL_HARDWARE_ENABLED
	if (readbit_csr(DRV1_PSR, OVELIF))     // Over-speed error protection triggered
	{
		mcFaultSource = FaultOverVelErr;
		FaultProcess();
		clr_csr(DRV1_PSR, OVELIF);

}
#endif // #if PROT_OVEL_HARDWARE_ENABLED
	
#if PROT_OSPD_HARDWARE_ENABLED
	if (readbit_csr(DRV1_PSR, OSPDIF))     // Over-speed protection triggered
	{
		mcFaultSource = FaultOverSpeed;
		FaultProcess();
		clr_csr(DRV1_PSR, OSPDIF); 
	}
#endif // #if PROT_OSPD_HARDWARE_ENABLED
	
#if PROT_STALL_HARDWARE_ENABLED
	if (readbit_csr(DRV1_PSR, LOCKIF))     // Stall protection triggered
	{
		mcFaultSource = FaultStall;
		FaultProcess();
		clr_csr(DRV1_PSR, LOCKIF); 
	}
#endif // #if PROT_STALL_HARDWARE_ENABLED
	
#if PROT_PLOSS_HARDWARE_ENABLED
	if (readbit_csr(DRV1_PSR, PLIF))     // Phase loss protection triggered
	{
		mcFaultSource = FaultPhaseLoss;
		FaultProcess();
		clr_csr(DRV1_PSR, PLIF);  
	}
#endif // #if PROT_PLOSS_HARDWARE_ENABLED
	
#if PROT_CARINTOT_HARDWARE_ENABLED
	if (readbit_csr(DRV1_PSR, ODCIF_IF))     // Carrier interrupt timeout protection triggered
	{
		Fault_Handler(FaultMainIntTimeOut, FLAG_MAININTOT);
		clr_csr(DRV1_PSR, ODCIF_IF); 
	}
#endif // #if PROT_CARINTOT_HARDWARE_ENABLED
	
}
#endif // #if PROT_HARDWARE_ENABLED


/*---------------------------------------------------------------------------
 * Name		:	FOC_INT
 * Input	:	No
 * Output	:	No
 * Description:	FOC interrupt (carrier interrupt), executed every 1, 2 or 0.5 carrier cycles, used to handle routines requiring higher response. 
 *---------------------------------------------------------------------------*/
__attribute__((__interrupt__)) void FOC_INT(void) // interrupt 8
{
#if TESTPIN_ENABLED
	set_csr(TEST_GPIO, TEST_PIN);
#endif
	
	if (readbit_csr(DRV1_IFR, DCIF))
	{
		ServoControl_Isr();

#if TEST_SPIDEBUG_SW_ENABLED
		spidebug[0] = NFOC_IA << 2;
		spidebug[1] = NFOC_IBETA << 2;
		spidebug[2] = NFOC_UDCFLTH;
		spidebug[3] = NFOC_THETAH;
#endif

		clr_csr(DRV1_IFR, DCIF);
	}
	
#if TESTPIN_ENABLED
	clr_csr(TEST_GPIO, TEST_PIN);
#endif

}


/*---------------------------------------------------------------------------
 * Name		:	SYSTICK_INT
 * Input	:	No
 * Output	:	No
 * Description:	1 ms timer interrupt (SYSTICK interrupt), currently not used
 *---------------------------------------------------------------------------*/
__attribute__((__interrupt__)) void SYSTICK_INT(void)
{

}


/*---------------------------------------------------------------------------
 * Name		:	TIM3_INT
 * Input	:	No
 * Output	:	No
 * Description:	Position-loop interrupt
 *---------------------------------------------------------------------------*/
__attribute__((__interrupt__)) void TIM3_INT(void)
{
#if TESTPIN_ENABLED
	set_csr(TEST_GPIO2, TEST_PIN2);
#endif
	
	if (readbit_csr(TIM3_SR, T3IR)) // Compare match flag
	{
		Fault_AuxIntDelayTimeOut(); // Check if interrupt delay is abnormal
		clr_csr(TIM3_SR, T3IR);
		
		PosControl_Isr();
		
	}
	
#if TESTPIN_ENABLED
	clr_csr(TEST_GPIO2, TEST_PIN2);
#endif
}


/*---------------------------------------------------------------------------
 * Name		:	DMA0_INT
 * Input	:	No
 * Output	:	No
 * Description:	UART receive/transmit interrupt
 *---------------------------------------------------------------------------*/
#if COMM_UART_ENABLED > 0
__attribute__((__interrupt__)) void DMA0_INT(void)
{
	if (readbit_csr(DMA0_CR, DMAIF))
	{
		clr_csr(DMA0_CR, DMAIF);
		if (PortSerial.RxEnable)
			xMBRTUReceiveDMAFSM();
		else if (PortSerial.TxEnable)
			xMBRTUTransmitDMAFSM();
	}
}
#endif // #if COMM_UART_ENABLED > 0


/*---------------------------------------------------------------------------
 * Name		:	MEFSM_INT
 * Input	:	No
 * Output	:	No
 * Description:	ME state-machine interrupt, handles voice-coil motor or field weakening
 *---------------------------------------------------------------------------*/
#if MOTOR_VCM_ENABLED | FUNC_FIELDWEAKEN_ENABLED
__attribute__((__interrupt__)) void MEFSM_INT(void)			// ME interrupt
{
	
#if FUNC_FIELDWEAKEN_ENABLED
	int16 IQMax = 0;
	int16 IQMin = 0;
	int32 WUFIN_TEMP = 0;

if (readbit_csr(ME_IFR, NIF0))
	{
		if (mcFocCtrl.VelLoopEnable)
		{
			IQMax = (int16)usSRegHoldBuf[VOUTMAX];
			IQMin = (int16)usSRegHoldBuf[VOUTMIN];
			WUFIN_TEMP = (int32)NFOC_WUFIN;

			IQMax = MIN(IQMax, mcFieldWeakenControl.Weaken_IqRefLmtPos);
			IQMin = MAX(IQMin, mcFieldWeakenControl.Weaken_IqRefLmtNeg);
			
			NFOC_F1X0 = (int16)WUFIN_TEMP;
			NFOC_IQMAX = (int16)IQMax;
			NFOC_IQMIN = (int16)IQMin;

			write_csr(ME_STR, 939);
			clr_csr(ME_IER, NIE0 | NPE0);
			clr_csr(ME_IFR, NIF0 | NPF0);
			set_csr(ME_IER, NIE0 | NPE0);
		}	
	}		
#elif MOTOR_VCM_ENABLED
	static uint8 MEFlag = 0;
	
	if (readbit_csr(ME_IFR, NIF0))
	{
		if (MEFlag == 0)
		{
			MEFlag = 1;
//			NFOC_ID = NFOC_IB;
			NFOC_IQ = NFOC_IA;
			
			write_csr(ME_STR, 27);		// Skip Clarke transform
			write_csr(ME_ST0, 140);		// 147 generates interrupt before SVPWM 136: generates interrupt after current-loop PI
		}
		else
		{
			MEFlag = 0;
			VCM_DriverOut();
			write_csr(ME_STR, 221);		// Skip SVPWM
			write_csr(ME_ST0, 8);		// Generate interrupt at the Clarke transform step
		}

		clr_csr(ME_IER, NIE0 | NPE0);
		clr_csr(ME_IFR, NIF0 | NPF0);
		set_csr(ME_IER, NIE0 | NPE0);
	}		
#endif
}
#endif // #if MOTOR_VCM_ENABLED


/*---------------------------------------------------------------------------
 * Name		:	CAN receive/transmit complete interrupt
 * Input	:	No
 * Output	:	No
 * Description:	CAN receive/transmit complete interrupt
 *---------------------------------------------------------------------------*/
#if EXCTRL_CANOPEN_ENABLED || COMM_CAN_ENABLED
__attribute__((__interrupt__)) void CAN_INT(void)			//CAN interrupt
{
	if (readbit_csr(CAN_IFR, RXIF))
	{
		clr_csr(CAN_IFR, RXIF);
		
		CAN_TxRxHeaderTypeDef rxHeader;
		UCHAR data[64];
		CAN_Receive(&rxHeader, data);

#if COMM_CAN_ENABLED
		uint16 ident = rxHeader.ident;
		uint8 fdf = (rxHeader.frame & FDF) == FDF_CANFD ? 0x01 : 0x00;
		if (fdf != 0x00 || 
			(((ident & 0xF0) == CS_CODEID_SDO || (ident & 0xF0) == CS_CODEID_PDO) && 
			((ident >> 8) & 0x00F) == (ident & 0x00F) && ((ident & 0x00F) == usSRegHoldBuf[COMMADDR] || 
			(ident & 0x00F) == CS_ADDRESS_BROADCAST))) // CANSpec
		{
			CanspecFT.header = rxHeader;
			CanspecFT.fdf = fdf;
			memcpy(CanspecFT.data, data, rxHeader.length);
			xCSRTUReceiveFSM();
		}	
#endif	
#if EXCTRL_CANOPEN_ENABLED
#if COMM_CAN_ENABLED
		else
#endif
		{
			CO_CANinterrupt_RX(&rxHeader, data);
		}
#endif
	}
	
	if (readbit_csr(CAN_IFR, TXIF))
	{
		clr_csr(CAN_IFR, TXIF);
#if COMM_CAN_ENABLED
		uint32 tmsta = read_csr(CAN_TMSTA);
		if (CanspecFT.mode == 1 && ((CanspecFT.mail == 0 && (tmsta & MDONE0)) // CANSpec
			|| (CanspecFT.mail == 1 && (tmsta & MDONE1)) || (CanspecFT.mail == 2 && (tmsta & MDONE2)))) 
		{
			xCSRTUTransmitFSM();
		}
#endif
	}
}
#endif // #if EXCTRL_CANOPEN_ENABLED || COMM_CAN_ENABLED