/*
 * Copyright (c) 2021-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : main.c
 * Author        : Fortior Application Team
 * Date          : 2021-04-27
 * Description   : Main loop
 *
 * Record        :
 * V1.0, 2021-04-27, Fortior Application Team: Created file
 */

/********************************************************************************
 * Header Definition
 ********************************************************************************/
#include <Myproject.h>


/********************************************************************************
 * Macro & Structure Definition
 *******************************************************************************/


/********************************************************************************
 * Internal Routine Prototypes
 ********************************************************************************/
void HardwareInit(void);
void SoftwareInit(void);


/*---------------------------------------------------------------------------
 * Name		:	main
 * Input	:	h_Fault - Pointer to the instance of FaultVarible
 * Output	:	No
 * Description:	The main function's primary role is initialization, including power-on wait, software initialization, hardware initialization, 
 *              debug mode setup, main loop scanning, and 1ms processing.
 *---------------------------------------------------------------------------*/
void main(void)
{
	Delay_ms(SYSTEM_POWERUP_TIME);// Wait until voltage and current stable

	/*Software initialization*/
	SoftwareInit();

	/*Hardware initialization*/
	HardwareInit();

	/*Global interrupt enable*/
	set_csr(MIE, IRQ_EN);

	while (1)
	{
		if (TimerFlag_1ms == 1)
		{
#if TESTPIN_ENABLED
			set_csr(TEST_GPIO1, TEST_PIN1);
#endif
			
#if EXCTRL_ECAT_ENABLED || EXCTRL_CANOPEN_ENABLED
			EcatOpModeSW_Update();
#endif
			
#if EXCTRL_ECAT_ENABLED	
			if(mcFocCtrl.Timer1msCount < MAX1MSDELAY)
				EcatHandle(); //EtherCAT
#endif //#if EXCTRL_ECAT_ENABLED
		
#if EXCTRL_CANOPEN_ENABLED
			CANOpenInterrupt();
#endif //#if EXCTRL_CANOPEN_ENABLED		
			
#if COMM_CAN_PDO_ENABLED
			CANSpec_cycle_process();
#endif

			UpdateTemperature();		// Update temperature value
			
			// Fault protection functions, such as over/under voltage protection, startup protection, phase loss, locked-rotor, etc.
			Fault_Detection();
			Fault_TimeCount();			// Error timing

			Check_InPos();				// Check if position reached/completed

#if FUNC_LED_TUBE_ENABLED
			LedTube_UpdateStatus();       // Update digital tube display value
#endif //#if FUNC_LED_TUBE_ENABLED

#if FUNC_LED_DIODE_ENABLED
			LedDiode_Display();		     // Update LED blinking
#endif // #if FUNC_LED_DIODE_ENABLED

			if (mcState == mcPhaseFind && McStaSet.SetFlag.PhaseFindSetFlag == 1)
				Motor_PhaseFind(); // Phase finding

			// Update phase currents, bus voltage (for host computer display)
			usSRegInBuf[MB_IC] = NFOC_IC;
			usSRegInBuf[BUSVOLTAGE] = NFOC_UDC; // NFOC_UDCFLTH;
			if (mcFocCtrl.CurLoopEnable == 1)
			{
				usSRegInBuf[MB_IA] = NFOC_IA;
				usSRegInBuf[MB_IB] = NFOC_IB;
			}
			else
			{
				usSRegInBuf[MB_IA] = NFOC_I1 - NFOC_IAREF;
				usSRegInBuf[MB_IB] = NFOC_I2 - NFOC_IBREF;
			}
			usSRegInBuf[MB_ID] = NFOC_ID;
			usSRegInBuf[MB_UD] = NFOC_UDFIN;
			usSRegInBuf[MB_UQ] = NFOC_UQFIN;
			// UV phase current
			usSRegInBuf[ADCIA] = NFOC_I1;
			usSRegInBuf[ADCIB] = NFOC_I2;
			
#if ENCODER_SEL_HALL_ENABLED
			usSRegInBuf[HALLS] = GetHallStatus();
#endif // #if ENCODER_SEL_HALL_ENABLED

			if (mcFocCtrl.State_Count > 0) mcFocCtrl.State_Count--;  // Special counter for state machine switching
			
#if FUNC_DISMODE_ENABLED
			EmergencyStop_TimeCount();
#endif //#if FUNC_DISMODE_ENABLED
			
#if FUNC_FORCECTRL_ENABLED
			if (ForceCtrl.TimeCounter > 0) ForceCtrl.TimeCounter--;  // Wait time counter for each stage of force control mode
#endif //#if FUNC_FORCECTRL_ENABLED
			
#if SPECIAL_ELESCREW_ENABLE
			ScrewCtrl_ProtectWarn();
#endif

#if FUNC_HOME_ENABLED
			Home_TimeCount();  // Homing timing
#endif //#if FUNC_HOME_ENABLED
			
			Motor_Profile_TimeCount();  // Position profiling timing
			
#if FUNC_MOTOREST_ENABLED
			if ((mcState == mcMotorIdentify) && (McStaSet.SetFlag.IdentifySetFlag == 1))
				Motor_Identify_realize(); // Motor parameter identification
#endif
				
			TimerFlag_1ms = 0;
			
#if TESTPIN_ENABLED
			clr_csr(TEST_GPIO1, TEST_PIN1);
#endif
		}

#if FUNC_FORCECTRL_ENABLED
		ForceCtrl_Update();
#endif //#if FUNC_FORCECTRL_ENABLED
		
#if SPECIAL_ELESCREW_ENABLE
		ScrewCtrl_Update();
#endif
		
		ModeSW_Update();							// Mode switching

		MC_Control();								// Main state machine function

		if (mcState != mcReady)
		{
			UpdateParam();			                // Update variable values based on parameters from serial port (non-real-time)
			UpdateDigitalIO();                      // Update IO status

#if FUNC_REGENERATION_ENABLED
			RegenerationHandler();                  // Regenerative braking
#endif //#if FUNC_REGENERATION_ENABLED

		}
		
		IWDT_Refresh();								//Independent watchdog feed
		
#if EXCTRL_CANOPEN_ENABLED
		CANOpenProcess();
#endif //#if EXCTRL_CANOPEN_ENABLED

#if DEBUG_UART_ENABLED > 0 // Serial port test mode
		UART_ANODubugerBuffConfig();
		SendDataByUart();
#elif COMM_UART_ENABLED > 0 // Serial port host communication mode
		eMBPoll();
#endif
		
#if COMM_CAN_ENABLED > 0 // CAN host communication mode
		eCSPoll();
#endif
	}
}


/*---------------------------------------------------------------------------
 * Name		:	SoftwareInit
 * Input	:	No
 * Output	:	No
 * Description:	Software initialization, initializes all defined variables
 *---------------------------------------------------------------------------*/
void SoftwareInit(void)
{
	memset(NFOC_BASE, 0, 2048); // Initialize all hardware FOC variables
	
	MotorControlInit(); // Initialize all defined parameter variables

	mcState = mcReady; // Motor initial state is mcReady
}



/*---------------------------------------------------------------------------
 * Name		:	HardwareInit
 * Input	:	No
 * Output	:	No
 * Description:	Hardware initialization, initializes required hardware configurations; for FOC, op-amp voltage, 
 *              op-amp initialization, ADC initialization, and driver initialization are mandatory.
 *---------------------------------------------------------------------------*/
void HardwareInit(void)
{
	/****** Start clock ******/
	write_csr(CK_CR, 0xfffff);

	/****** Functional IO initialization ******/
	GPIO_Init();

	/****** SPI DEBUG initialization ******/
#if TEST_SPIDEBUG_HW_ENABLED || TEST_SPIDEBUG_SW_ENABLED
	SPIDebugSet();
#endif

	/****** Signal Debug initialization ******/
#if TEST_SIGNALDEBUG_ENABLED
	SignalDebugSet();			//Turn on DATAMONITOR; PA9 connected to single-wire DBG board allows signal monitoring, PA1 allows checking current sampling timing.
#endif
	
#if FUNC_LED_TUBE_ENABLED || !FUNC_SOFT_EEPROM_ENABLED
	/****** IIC LED/EEPROM initialization ******/
	I2C_Init();
#endif
	
#if FUNC_EEPROM_ENABLED
	/****** Load from EEPROM ******/
	UploadDataFromEEPROM(); // Load parameter table
	Fault_UploadErrCode();  // Load error history
	mcRegParam.DriveMode = usSRegHoldBuf[DRIVEMODE];
#endif // #if FUNC_EEPROM_ENABLED
	
	
#if DEBUG_UART_ENABLED > 0 // Serial port test mode
#if(MODBUS_UART == 1)
	UART1_Init();
#else
	UART2_Init();
#endif
#elif COMM_UART_ENABLED > 0 // Serial port host communication mode
	eMBInit(MODEBUS_SLAVE_ID);
	eMBEnable();
#endif

#if COMM_CAN_ENABLED > 0 // CAN host communication mode
	usSRegHoldBuf[CANBITRATE] = 0;
	eCSInit(usSRegHoldBuf[CANBITRATE]);
	eCSEnable();
#endif
	

#if EXCTRL_ECAT_ENABLED
	/****** EtherCAT synchronization signal external interrupt initialization ******/
	EXTI1_Init();	// 
	/****** EtherCAT initialization ******/
	EcatInit();
#endif // #if EXCTRL_ECAT_ENABLED
	
	
#if EXCTRL_CANOPEN_ENABLED
	/****** CANopen initialization ******/
#if (HARDWARE_VERSION == HARDWARE_FPGA_HIGHVOL_SWITCH || HARDWARE_VERSION == HARDWARE_FPGA_LOWVOL_SWITCH)
	usSRegHoldBuf[COMMADDR] = 5;
#endif
	usSRegHoldBuf[CANBITRATE] = 0;
	CANOpenInit(usSRegHoldBuf[COMMADDR], usSRegHoldBuf[CANBITRATE]);
#endif // #if EXCTRL_CANOPEN_ENABLED
	
	/****** ADC reference voltage configuration ******/
	VREFConfigInit();
	
#if (HW_AMP_SEL == AMP_ONCHIP)
	/****** Operational amplifier initialization ******/
    AMP_Init();
#endif

	/****** ADC initialization ******/
	ADC_Init();
	ADC2_Init();
	
	/****** Hardware FO overcurrent, comparator initialization, used for hardware overcurrent comparison protection ******/
#if (HardwareCurrent_Protect == Hardware_FO_Protect)		//External interrupt initialization, used for external interrupt hardware overcurrent FO protection
#if (Hardware_FO_SRC == Hardware_FO_EXTI0)
	EXTI0_Init();
#else
	EXTI2_Init();
#endif
#elif (HardwareCurrent_Protect == Hardware_CMP_Protect)		//Select comparison overcurrent, comparator initialization
	CMP3_Init();
#elif (HardwareCurrent_Protect == Hardware_FO_CMP_Protect)	//Both selected
#if (Hardware_FO_SRC == Hardware_FO_EXTI0)
	EXTI0_Init();
#else
	EXTI2_Init();
#endif
	CMP3_Init();
#endif


	/****** Driver initialization ******/
	Driver1_Init();

	/****** Position loop interrupt Timer3 initialization ******/
	Timer3_Init();
	
	/****** Encoder initialization ******/
	Encoder_Init();

#if EXCTRL_ENCOUT_ENABLED
	/****** Frequency division output initialization ******/
	Timer5_Init();
#endif // #if EXCTRL_ENCOUT_ENABLED

#if EXCTRL_PULSE_ENABLED
	/****** Pulse-direction input initialization ******/
	Timer6_Init();
#endif // #if EXCTRL_PULSE_ENABLED

#if FUNC_REGENERATION_ENABLED
	/****** Regenerative braking chopper Timer initialization ******/
	Timer8_Init();
#endif // #if FUNC_REGENERATION_ENABLED

#if FUNC_PROBE_ENABLED
	/****** Probe input initialization ******/
	Probe_Init();
#endif // #if FUNC_PROBE_ENABLED
	
#if FUNC_PCOM_ENABLED
	/****** Position comparison output initialization ******/
	PCOM_Init();
#endif // #if FUNC_PCOM_ENABLED

#if FUNC_LED_TUBE_ENABLED
	/****** Digital tube initialization ******/
	LedTube_Init();
#endif // #if FUNC_LED_TUBE_ENABLED

	/****** Pull up unused GPIOs ******/
	GPIO_PU_Init();
	
	/****** Independent watchdog initialization ******/
	IWDT_Init();
}