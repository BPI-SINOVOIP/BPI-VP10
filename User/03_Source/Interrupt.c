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

#define FO_INT        _interrupt_handler_1		// IPM硬件过流中断
#define FO2_INT       _interrupt_handler_3		// IPM硬件过流中断
#define CMP3_INT	  _interrupt_handler_4		// MOS硬件过流中断
#define EXTERN1_INT   _interrupt_handler_2		// ECAT外部中断
#define DRVPIF_INT    _interrupt_handler_6		// 保护中断
#define FOC_INT       _interrupt_handler_8		// 载波中断
#define MEFSM_INT     _interrupt_handler_10		// ME状态机中断
#define DMA0_INT      _interrupt_handler_12		// DMA串口接收/发送中断
#define SYSTICK_INT   _interrupt_handler_15
#define TIM2_INT      _interrupt_handler_16		// Z信号中断
#define TIM3_INT      _interrupt_handler_17		// 位置环中断
#define CAN_INT       _interrupt_handler_30		// CAN接收完成中断



/*---------------------------------------------------------------------------*/
/* Name		:	void FO_INT(void)
/* Input	:	NO
/* Output	:	NO
/* Description:	FO_INT interrupt，硬件过流，硬件FO过流保护，关断输出，中断优先级最高。
/*---------------------------------------------------------------------------*/
#if ((HardwareCurrent_Protect == Hardware_FO_Protect) || (HardwareCurrent_Protect == Hardware_FO_CMP_Protect))
#if (Hardware_FO_SRC == Hardware_FO_EXTI0)
__attribute__((__interrupt__)) void FO_INT(void) // interrupt 1					// 硬件FO过流中断，关闭输出
{
	if (readbit_csr(EXT0IF, EX0IF13))
	{
		Fault_Handler(FaultHardOVCurrent, FLAG_HARDOVC);
		clr_csr(EXT0IF, EX0IF13);
	}
}
#else
__attribute__((__interrupt__)) void FO2_INT(void) // interrupt 3					// 硬件FO过流中断，关闭输出
{
	if (readbit_csr(EXT2IF, EX2IE10))
	{
		if (mcFocCtrl.CurLoopEnable == 1) // FO信号刚上电时异常，需避开
		{
			Fault_Handler(FaultHardOVCurrent, FLAG_HARDOVC);
		}
		clr_csr(EXT2IF, EX2IE10);
	}
}
#endif  // #if #if (Hardware_FO_SRC == Hardware_FO_EXTI0)
#endif  // #if ((HardwareCurrent_Protect == Hardware_FO_Protect) || (HardwareCurrent_Protect == Hardware_FO_CMP_Protect))


/*---------------------------------------------------------------------------*/
/* Name		:	void CMP3_INT(void) interrupt 4
/* Input	:	NO
/* Output	:	NO
/* Description:	硬件比较器过流中断，关断输出，中断优先级最高。
/*---------------------------------------------------------------------------*/
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


/*---------------------------------------------------------------------------*/
/* Name        : void EXTERN1_INT(void)
/* Input       : NO
/* Output      : NO
/* Description : 外部中断，用于处于EtherCAT的sync0信号
/*---------------------------------------------------------------------------*/
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
		clr_csr(EXT1IF, EX1IF8);                    // 清零中断标志位
	}
}
#endif //#if EXCTRL_ECAT_ENABLED


/*---------------------------------------------------------------------------*/
/* Name        : void DRVPIF_INT(void)
/* Input       : NO
/* Output      : NO
/* Description : 硬件保护中断 
/*---------------------------------------------------------------------------*/
#if PROT_HARDWARE_ENABLED
__attribute__((__interrupt__)) void DRVPIF_INT(void) // interrupt 6
{
#if PROT_OUVP_HARDWARE_ENABLED
	if (readbit_csr(DRV1_PSR, OVPIF))     // 软件过压保护触发
	{
		mcFaultSource = FaultOverVoltage;
		FaultProcess();
		clr_csr(DRV1_PSR, OVPIF);   
	}
	
	if (readbit_csr(DRV1_PSR, UVPIF))     // 软件欠压保护触发
	{
		mcFaultSource = FaultUnderVoltage;
		FaultProcess();
		clr_csr(DRV1_PSR, UVPIF); 
	}
#endif // #if PROT_OUVP_HARDWARE_ENABLED
	
#if PROT_SOCP_HARDWARE_ENABLED
	if (readbit_csr(DRV1_PSR, SOCPIF))     // 软件过流保护触发
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
	if (readbit_csr(DRV1_PSR, OVELIF))     // 速度超差保护触发
	{
		mcFaultSource = FaultOverVelErr;
		FaultProcess();
		clr_csr(DRV1_PSR, OVELIF); 
	}
#endif // #if PROT_OVEL_HARDWARE_ENABLED
	
#if PROT_OSPD_HARDWARE_ENABLED
	if (readbit_csr(DRV1_PSR, OSPDIF))     // 速度过超保护触发
	{
		mcFaultSource = FaultOverSpeed;
		FaultProcess();
		clr_csr(DRV1_PSR, OSPDIF); 
	}
#endif // #if PROT_OSPD_HARDWARE_ENABLED
	
#if PROT_STALL_HARDWARE_ENABLED
	if (readbit_csr(DRV1_PSR, LOCKIF))     // 堵转保护触发
	{
		mcFaultSource = FaultStall;
		FaultProcess();
		clr_csr(DRV1_PSR, LOCKIF); 
	}
#endif // #if PROT_STALL_HARDWARE_ENABLED
	
#if PROT_PLOSS_HARDWARE_ENABLED
	if (readbit_csr(DRV1_PSR, PLIF))     // 缺相保护触发
	{
		mcFaultSource = FaultPhaseLoss;
		FaultProcess();
		clr_csr(DRV1_PSR, PLIF);  
	}
#endif // #if PROT_PLOSS_HARDWARE_ENABLED
	
#if PROT_CARINTOT_HARDWARE_ENABLED
	if (readbit_csr(DRV1_PSR, ODCIF_IF))     // 载波中断超时保护触发
	{
		Fault_Handler(FaultMainIntTimeOut, FLAG_MAININTOT);
		clr_csr(DRV1_PSR, ODCIF_IF); 
	}
#endif // #if PROT_CARINTOT_HARDWARE_ENABLED
	
}
#endif // #if PROT_HARDWARE_ENABLED


/*---------------------------------------------------------------------------*/
/* Name     :   void FOC_INT(void) interrupt 3
/* Input    :   NO
/* Output   :   NO
/* Description: FOC中断(Drv中断),每1个载波周期执行一次，用于处理响应较高的程序。
/*---------------------------------------------------------------------------*/
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


/*---------------------------------------------------------------------------*/
/* Name     :   void TIM4S_INT(void) interrupt 10
/* Input    :   NO
/* Output   :   NO
/* Description: 1ms定时器中断（SYS TICK中断），用于处理附加功能，如寻相、
/*              各种保护等。中断优先级为1，低于FO中断和FOC中断。
/*---------------------------------------------------------------------------*/
__attribute__((__interrupt__)) void SYSTICK_INT(void)
{

}


/*---------------------------------------------------------------------------*/
/* Name     :   void TIM2_INT(void)
/* Input    :   NO
/* Output   :   NO
/* Description: Z 信号上升沿中断，中断优先级为3，较低
/*---------------------------------------------------------------------------*/
#if ENCODER_SEL_ABZ_ENABLED
__attribute__((__interrupt__)) void TIM2_INT(void)
{
	if (readbit_csr(TIM2_SR, T2IR)) // 计数上溢标志
	{
#if FUNC_HOME_ENABLED
		Home_ZCaptured();
#endif //#if FUNC_HOME_ENABLED		
		clr_csr(TIM2_SR, T2IR);
	}
}
#endif //#if ENCODER_SEL_ABZ_ENABLED


/*---------------------------------------------------------------------------*/
/* Name     :   void TIM3_INT(void) interrupt 17
/* Input    :   NO
/* Output   :   NO
/* Description: 位置环中断
/*---------------------------------------------------------------------------*/
__attribute__((__interrupt__)) void TIM3_INT(void)
{
#if TESTPIN_ENABLED
	set_csr(TEST_GPIO2, TEST_PIN2);
#endif
	
	if (readbit_csr(TIM3_SR, T3IR)) // 比较匹配标志
	{
		Fault_AuxIntDelayTimeOut(); // 检查中断延时是否异常
		clr_csr(TIM3_SR, T3IR);
		
		PosControl_Isr();
		
	}
	
#if TESTPIN_ENABLED
	clr_csr(TEST_GPIO2, TEST_PIN2);
#endif
}


/*---------------------------------------------------------------------------*/
/* Name     :   void DMA0_INT(void) interrupt 12
/* Input    :   NO
/* Output   :   NO
/* Description: 串口接收/发送中断
/*---------------------------------------------------------------------------*/
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


/*---------------------------------------------------------------------------*/
/* Name     :   void MEFSM_INT(void) interrupt 10
/* Input    :   NO
/* Output   :   NO
/* Description: ME状态机中断
/*---------------------------------------------------------------------------*/
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
			
			write_csr(ME_STR, 27);		// 跳过Clarke变换
			write_csr(ME_ST0, 140);		// 147在SVPWM之前产生中断 136:在电流环PI之后产生中断
		}
		else
		{
			MEFlag = 0;
			VCM_DriverOut();
			write_csr(ME_STR, 221);		// 跳过SVPWM
			write_csr(ME_ST0, 8);		// 在Clarke变换这一步产生中断
		}

		clr_csr(ME_IER, NIE0 | NPE0);
		clr_csr(ME_IFR, NIF0 | NPF0);
		set_csr(ME_IER, NIE0 | NPE0);
	}
		
#endif

}
#endif // #if MOTOR_VCM_ENABLED


/*---------------------------------------------------------------------------*/
/* Name     :   void CAN_INT(void) interrupt 30
/* Input    :   NO
/* Output   :   NO
/* Description: CAN接收/发送完成中断
/*---------------------------------------------------------------------------*/
#if EXCTRL_CANOPEN_ENABLED || COMM_CAN_ENABLED
__attribute__((__interrupt__)) void CAN_INT(void)			//CAN中断
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