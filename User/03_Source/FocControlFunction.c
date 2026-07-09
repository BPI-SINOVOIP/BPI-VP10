/*
 * Copyright (c) 2022-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : FocControlFunction.c
 * Author        : Fortior Application Team
 * Date          : 2022-09-21
 * Description   : define motor contorl parameter
 *
 * Record        :
 * V1.0, 2022-09-21, Fortior Application Team: Created file
 */


/********************************************************************************
* Header Definition
********************************************************************************/
#include <Myproject.h>
#include "FocControlFunction.h"


/********************************************************************************
* Macro & Structure Definition
*******************************************************************************/
FOCCTRL				mcFocCtrl = { 0 };

RegParamTypeDef		mcRegParam __attribute__((section(".pram.data.mcRegParam"))) = { 0 };
AnInTypeDef			mcAnalogInput __attribute__((section(".pram.data.mcAnalogInput"))) = { 0 };

volatile uint8 TimerFlag_1ms = 0;
uint8 SYNC0_Flag = 0;
uint8 EscIntStep = 0;

/********************************************************************************
* Internal Routine Prototypes
********************************************************************************/

/*---------------------------------------------------------------------------
 * Name		:	FOC_Init
 * Input	:	No
 * Output	:	No
 * Description:	FOC initialization, configure FOC related registers
 *---------------------------------------------------------------------------*/
void FOC_Init(void)
{
	uint16 reg;
	
	memset(NFOC_BASE + FOC_REG_CLEAR_OFFSET, 0, 1024 - FOC_REG_CLEAR_OFFSET); //Clear FOC1 related registers
	
	write_csr(DRV1_FCR0, 0x00);		//Clear FOC1 related registers
	write_csr(DRV1_FCR1, 0x00);		//Clear FOC1 related registers
	
	NFOC_ARR = PWM_VALUE_LOAD; // FOC carrier frequency, must match DRVx_ARR value

	clr_csr(DRV1_FCR1, ANGMAMD);	//After enable, NFOC_THETA no longer comes from ETHETA
	
	set_csr(DRV1_FCR0, FDIS_MD2);	//Skip estimator angle calculation, start from current loop, user fills NFOC_THETA
	clr_csr(DRV1_FCR0, FDIS_MD1);
	clr_csr(DRV1_FCR0, FDIS_MD0);
	
	set_csr(DRV1_FCR5, LUT_EN); // 0:LUT, 1:Cordic
	clr_csr(DRV1_FCR5, DTC_EN); // Dead-time compensation enable, 0:disable, 1:enable

	
	// Electrical angle and ActPos direction
	if (mcFocCtrl.EAngDir)
	{
		set_csr(DRV1_FCR4, IQREF_INV); // IQREF inverted
	}
	else
	{
		clr_csr(DRV1_FCR4, IQREF_INV); // IQREF not inverted
	}
	

	/* Outer loop selection */
	clr_csr(DRV1_FCR1, WPIMD0 | WPIMD1);  //User manually fills WFDB

    /* Outer loop initialization */
	NFOC_WKP = 0;
	NFOC_WKI = 0;
	NFOC_WMAX = usSRegHoldBuf[VOUTMAX];
	NFOC_WMIN = usSRegHoldBuf[VOUTMIN];
	
	// Outer loop calculation period selection (DRV_FCR1[wpi_auto] must be 11)  00:every 1 MMT period 01:every 2 MMT periods
	// Outer loop calculation period selection (DRV_FCR1[wpi_auto] must be 11)  10:every 4 MMT periods 11:every 8 MMT periods	
#if DRV32K_ENABLE_SWITCH
	set_csr(DRV1_FCR4, WPI_CAL_CYCLE1);
	clr_csr(DRV1_FCR4, WPI_CAL_CYCLE0);
#else
	clr_csr(DRV1_FCR4, WPI_CAL_CYCLE1);
	set_csr(DRV1_FCR4, WPI_CAL_CYCLE0);
#endif	

	/* Power calculation configuration */
#if (IT_POW_MD == DIS_IT_POW)
	{
		clr_csr(DRV1_FCR0, ITPOWMD0 | ITPOWMD1);
	}
#elif (IT_POW_MD == EX_IT_POW)
	{
		set_csr(DRV1_FCR0, ITPOWMD0);
		clr_csr(DRV1_FCR0, ITPOWMD1);
	}
#elif (IT_POW_MD == IN_IT_POW)
	{
		clr_csr(DRV1_FCR0, ITPOWMD0);
		set_csr(DRV1_FCR0, ITPOWMD1);
	}
#elif (IT_POW_MD == IS_IT_POW)
	{
		set_csr(DRV1_FCR0, ITPOWMD0);
		set_csr(DRV1_FCR0, ITPOWMD1);
	}	
#endif

	/*Current sampling mode*/
#if (HW_ADC_RESISTOR_MODE == SINGLE_RESISTOR)
#if (Single_Resistor_ignoreEnable == 1)
	set_csr(DRV1_FCR0, 0x08);        // DRV1_FCR0(bit1-bit3): Current sampling modeconfiguration                                     //Legacy single-resistor ignore mode
#endif
	NFOC_TS = PWM_TS_LOAD;									//Single-resistor minimum sampling window
	NFOC_TDTC = 0;
	NFOC_NTS = 0;
	NFOC_TDLY = 0x0A;          // Advanced sampling set 0x0fff, delayed sampling set 0x0005;

#elif (HW_ADC_RESISTOR_MODE == DOUBLE_RESISTOR)
	
#if DOUBLESAMP_ENABLE_SWITCH
	set_csr(DRV1_FCR0, NCSAMMD3);	// Double-resistor dual sampling (1001), CT_SEL must be set to 1
	clr_csr(DRV1_FCR0, NCSAMMD2);
	clr_csr(DRV1_FCR0, NCSAMMD1);
	set_csr(DRV1_FCR0, NCSAMMD0);
	NFOC_CSAM = 0x09; // sampling mode initial value
#else
	clr_csr(DRV1_FCR0, NCSAMMD3);	// Double-resistor single sampling (0001)
	clr_csr(DRV1_FCR0, NCSAMMD2);
	clr_csr(DRV1_FCR0, NCSAMMD1);
	set_csr(DRV1_FCR0, NCSAMMD0);
	NFOC_CSAM = 0x01;
#endif
	
	set_csr(DRV1_FCR1, CT_SEL);      // FOC calculation timing 0:calculate FOC at next overflow after current sampling  1:calculate FOC immediately after current sampling
	
#if (HW_ADC_SYNC == ADCSAM_SYNC)
	set_csr(ME_CR, TRIG_MD);			// Enable dual ADC synchronous sampling
#endif
	
	NFOC_TS = usSRegHoldBuf[MINPWMWIDTH]; //PWM_DLOWL_TIME;
	NFOC_TDTC = PWM_DT_LOAD;
//	NFOC_NTS = 0; // omitted
	NFOC_TDLY = ((uint32)usSRegHoldBuf[ISAMDELAY] * MCU_CLOCK) >> 10; // ISAM_DELAY;
	write_csr(DRV1_DTR, ((uint32)usSRegHoldBuf[DEADTIME] * MCU_CLOCK) >> 10); // PWM_LOAD_DEADTIME
	
	/*5-segment or 7-segment selection*/
#if (HW_SVPWM_MODE == SVPWM_7_SEGMENT)
	{
		clr_csr(DRV1_FCR2, NSEG5);							// 7-segment
	}
#elif (HW_SVPWM_MODE == SVPWM_5_SEGMENT)
	{
		set_csr(DRV1_FCR2, NSEG5);							// 5-segment
	}
#endif

#elif (HW_ADC_RESISTOR_MODE == THREE_RESISTOR)
	set_csr(DRV1_FCR0, 0x04);                                                // Three-resistor mode
#if (Three_Resistor_switcheEnable == 1)
	set_csr(DRV1_FCR0, 0x0C);                                            // newThree-resistor mode
#endif
	NFOC_TS = usSRegHoldBuf[MINPWMWIDTH]; //PWM_DLOWL_TIME;
	NFOC_TDTC = PWM_DT_LOAD;
	NFOC_NTS = 0;
	NFOC_TDLY = 0x0006;          // advanced sampling set 0x0805, delayed sampling set0x0005;

#elif (HW_ADC_RESISTOR_MODE == SINGLE_RESISTOR_NEW)
	set_csr(DRV1_FCR0, 0x06);                                                // New single-resistor mode
	NFOC_TS = 0;
	NFOC_TDTC = 0;
	NFOC_NTS = 30;              // Single-resistor sampling window
	NFOC_TDLY = 0x0F;            // Advanced sampling set 0x0805, delayed sampling set 0x0005; TBD
#endif

	/* Initialize Driver output */
	uint16 halfPWM = (PWM_VALUE_LOAD) >> 1;
	NFOC_DR1	= halfPWM;
	NFOC_DR1N	= halfPWM;
	NFOC_DR2	= halfPWM;
	NFOC_DR2N	= halfPWM;
	NFOC_DR3	= halfPWM;
	NFOC_DR3N	= halfPWM;

	write_csr(DRV1_CMPU1, halfPWM);
	write_csr(DRV1_CMPD1, halfPWM);
	write_csr(DRV1_CMPU2, halfPWM);
	write_csr(DRV1_CMPD2, halfPWM);
	write_csr(DRV1_CMPU3, halfPWM);
	write_csr(DRV1_CMPD3, halfPWM);
	
#if (OVMDL_EN == 1)
	set_csr(DRV1_FCR0, NOVMDL); // Over-modulation
#endif
	

	/* Current loop complex vector decoupling */
	if (usSRegHoldBuf[CVMOD] == 0)
	{
		clr_csr(DRV1_FCR6, CVD_EN);                //Complex vector decoupling enable bit
	}
	else
	{
		// Set current loop complex vector controller coefficients
		set_csr(DRV1_FCR6, CVD_EN);                
		// If NFOC_UDCMAX = 0x7fff, NFOC_UDCMIN = 0x7fff, and only KP/KI are provided, the effect is the same as the original current loop
		
		NFOC_UDCMAX = usSRegHoldBuf[UDCMAX]; // UdcMax; //
		NFOC_UDCMIN = usSRegHoldBuf[UDCMIN]; // UdcMin; //
		NFOC_UDCLIM = usSRegHoldBuf[UDCMIN]; // UdcMin; // UDCLIM needs an initial value
	}
	
	/* Current loop PI enable */
#if OPENLOOP_ENABLE_TEST
	if (mcState == mcStart)
	{
		set_csr(DRV1_FCR0, NVQDIS); // Q-axis PI disable
		set_csr(DRV1_FCR0, NVDDIS); // D-axis PI disable
		clr_csr(DRV1_FCR6, CVD_EN); // Complex vector decoupling enable bit
	}
	else
	{
		clr_csr(DRV1_FCR0, NVQDIS);		// Q-axis PI enable
		clr_csr(DRV1_FCR0, NVDDIS);		// D-axis PI enable
	}
#else
	clr_csr(DRV1_FCR0, NVQDIS);		// Q-axis PI enable
	clr_csr(DRV1_FCR0, NVDDIS);		// D-axis PI enable
#endif
	
	/* Current loop PI controller output limits */
	NFOC_DMAX = usSRegHoldBuf[DOUTMAX];
	NFOC_DMIN = usSRegHoldBuf[DOUTMIN];

	NFOC_QMAX = usSRegHoldBuf[QOUTMAX];
	NFOC_QMIN = usSRegHoldBuf[QOUTMIN];

	/* Velocity loop controller output limits */
    NFOC_IQMAX = usSRegHoldBuf[VOUTMAX];
    NFOC_IQMIN = usSRegHoldBuf[VOUTMIN];
	
    /* Filter settings */
	set_csr(DRV1_FCR5, IDQ_LPF_EN); // Enable ID/IQ filter
	set_csr(DRV1_FCR5, IDQ_FB_SEL); // ID/IQ select filtered value as feedback
	NFOC_IDK = usSRegHoldBuf[IDQLPFK]; // 9000Hz 51BE fs:32kHz
	NFOC_IQK = usSRegHoldBuf[IDQLPFK];
	
	set_csr(DRV1_FCR4, UDQ_LPF_EN);     // UDQ low-pass filter enable	0:disable  1:enable
	NFOC_UDK = usSRegHoldBuf[UDQLPFK];  // 9000Hz 51BE fs:32kHz
	NFOC_UQK = usSRegHoldBuf[UDQLPFK];
	
	NFOC_UDCK = 0x1000; // Bus voltage sampling filter coefficient
	
	/* Velocity calculation M-method */
	NFOC_MBASE = usSRegHoldBuf[QEPSPEEDCOE];
	NFOC_MSHFT = usSRegHoldBuf[SPEEDCOERANK];
	if (GetReg(usSRegHoldBuf[DRIVESWITCH], SW_MTMODE))
	{
		NFOC_MARR = VELCTRL_TS * 2;
	}
	else
	{
		NFOC_MARR = VELCTRL_TS;
	}
	
	/* Set DAC hardware overcurrent value */
#if (HardwareCurrent_Protect == Hardware_CMP_Protect || \
	HardwareCurrent_Protect == Hardware_FO_CMP_Protect)	//Both selected
#if FUNC_EEPROM_ENABLED
		uint16 temp = usSRegHoldBuf[HARDCURRENT] >> 5;
	if (temp > 511)
		temp = 511;
	write_csr(DAC_DR0, temp);
#else
	write_csr(DAC_DR0, 511);// Temporarily set to maximum to avoid false triggering caused by input voltage fluctuation after motor enable
#endif
#endif
	
	/* Current offset calibration */
#if(HW_ADC_CALIB_MODE == CALIB_START)
	UpdateCurrentOffset();              // Current offset acquisition
#endif
	
#if MOTOR_VCM_ENABLED
	/*Voice coil motor control requires ME interrupt configuration*/
	if (usSRegHoldBuf[MOTORCOMMTYPE] == VOICECOIL_MOTOR)
	{
		write_csr(ME_ST0, 8);				// Generate interrupt at Clarke transform step
		set_csr(ME_IER, 0x03);				// Enable ME state machine interrupt
		write_csr(IP10, MEFSM_INT_PRI);		// ME state machine interrupt (IRQ 10) priority 6
	}
#endif

#if FUNC_FIELDWEAKEN_ENABLED
	/*Field weakening control requires ME interrupt configuration*/
	write_csr(ME_ST0, 567);				
	set_csr(ME_IER, NPE0 | NIE0);
	write_csr(IP10, MEFSM_INT_PRI);		// ME state machine interrupt (IRQ 10) priority 6
#endif
	
	set_csr(DRV1_FCR0, NCALEN);			// FOC calculation enable
}


/*---------------------------------------------------------------------------
 * Name		:	FOC_RunModeUpdate
 * Input	:	No
 * Output	:	No
 * Description:	Set corresponding registers based on RunMod
 *---------------------------------------------------------------------------*/
void FOC_RunModeUpdate(void)
{	
#if FUNC_SOFTCTRL_ENABLED
	if ((mcFocCtrl.RunMod == CURMOD) ||
		((mcFocCtrl.RunMod == POS_CURMOD) && (FieldSoftControl_GetSwToPosFlag() != 1)))
#else
	if (mcFocCtrl.RunMod == CURMOD)
#endif
	{
		clr_csr(DRV1_FCR1, WPILDEN);	// Velocity loop output NFOC_WUFIN auto-loads into torque filter input NFOC_FIX0
		clr_csr(DRV1_FCR1, WPIAUTO1);	// 00: Outer loop disable
		clr_csr(DRV1_FCR1, WPIAUTO0);	
	}
	else 
	{
		set_csr(DRV1_FCR1, WPILDEN);	// Velocity loop output NFOC_WUFIN auto-loads into torque filter input NFOC_FIX0
		set_csr(DRV1_FCR1, WPIAUTO1);	// 11: Velocity loop frequency determined by WPI_CAL_CYCLE1
		set_csr(DRV1_FCR1, WPIAUTO0);	
		
#if FUNC_FIELDWEAKEN_ENABLED
		set_csr(DRV1_FCR2, FWEAK_EN);
		set_csr(DRV1_FCR2, FWEAK_MD); // Field weakening mode 1 enable bit active
#endif
	}

}


/*---------------------------------------------------------------------------
 * Name		:	MotorControlInit
 * Input	:	No
 * Output	:	No
 * Description:	Software variable power-on initialization, including protection parameters and motor state initialization
 *---------------------------------------------------------------------------*/
void MotorControlInit(void)
{
	Scope_Init();
	
	ElecAngCal_Init();
	
#if FUNC_GAINSW_ENABLED
	GainSW_Demo_Init();  // Gain switching initialization
#endif //#if FUNC_GAINSW_ENABLED
	
	PI_Init();	
	
#if FUNC_FRICOMP_ENABLED
	FricCmp_Demo_Init();
#endif

#if FUNC_FEEDBACKONLOAD_ENABLED
	FeedBackOnLoad_Demo_Init();
#endif
	
#if FUNC_SPDFF_ENABLED
	SpdFF_Init(); // Velocity feedforward initialization
#endif //#if FUNC_SPDFF_ENABLED

#if FUNC_TOQFF_ENABLED
	ToqFF_Init(); // Torque feedforward initialization
#endif //#if FUNC_TOQFF_ENABLED

	ModeSW_Init(); // Mode switching initialization

#if FUNC_INERTIA_ENABLED
	InFricId_Demo_Init();
#endif //#if FUNC_INERTIA_ENABLED

	InputFilter_Rst();
	
	HardVelFilter_Clr(&HardInFilt1VelFeb);

	HardVelFilter_Clr(&HardInFilt2VelFeb);
	
#if FUNC_PCOM_ENABLED > 0
	PCOM_Init();
#endif
	
#if FUNC_CURRENTBACK_ENABLED
	CurrBack_Demo_Init();
#endif

#if DEADTIME_COMPENSATE_ENABLED
	DeadTimeCompensationInit(usSRegHoldBuf[DEADCOMPCUR]);
#endif
	
#if COMM_CAN_PDO_ENABLED
	DynTrap_Demo_Init();
#endif

    mcFaultDect.pErrorHist = &usSRegInBuf[ERRORTIME0];

	// Firmware version number
    usSRegInBuf[FIRMWAREVERSION_H] = (uint32)FIRMWAREVERSION_I >> 16;
    usSRegInBuf[FIRMWAREVERSION_L] =(uint32)FIRMWAREVERSION_I;
	// Carrier period
    usSRegInBuf[PWMFREQUENCY] = (uint16)PWM_FREQUENCY;
    usSRegInBuf[CURCTRLFREQUENCY] = (uint16)CURCTRL_FREQUENCY;
    usSRegInBuf[VELCTRLFREQUENCY] = (uint16)VELCTRL_FREQUENCY;
    usSRegInBuf[POSCTRLFREQUENCY] = (uint16)POSCTRL_FREQUENCY;
    usSRegInBuf[SERCURFREQ] = (uint16) SERIAL_CURRENT_FREQUENCY;
    usSRegInBuf[SERVELFREQ] = (uint16) SERIAL_VELOCITY_FREQUENCY;
    usSRegInBuf[ANACURFREQ] = (uint16) ANALOG_CURRENT_FREQUENCY;
    usSRegInBuf[ANAVELFREQ] = (uint16) ANALOG_VELOCITY_FREQUENCY;
    usSRegInBuf[SCOPEFREQ] = (uint16) SCOPE_FREQUENCY;
    usSRegInBuf[OUTFILTFREQ] = (uint16) OUTFILT_FREQUENCY;
    usSRegInBuf[VELFEBFREQ] = (uint16) VELFEB_FREQUENCY;
    usSRegInBuf[POSREFFREQ] = (uint16) POSREF_FREQUENCY;
    // Driver type
    usSRegInBuf[DRIVERTYPE] = HARDWARE_VERSION;
    // Master clock frequency
    usSRegInBuf[MCUCLOCK] = (uint16)MCU_CLOCK;
    // Function switches
    usSRegInBuf[FUNCMASK0] = (uint16)(EXCTRL_ECAT_ENABLED | (EXCTRL_PULSE_ENABLED << 1) | (EXCTRL_ANALOG_ENABLED << 2) |
    	(EXCTRL_ENCOUT_ENABLED << 3) | (EXCTRL_CANOPEN_ENABLED << 4) | (MOTOR_VCM_ENABLED << 5) |
    	(ENCODER_SEL_ABZ_ENABLED << 6) | (ENCODER_SEL_HALL_ENABLED << 7) | (ENCODER_SEL_TMG_ENABLED << 8) |
    	(ENCODER_SEL_BISS_ENABLED << 9) | (ENCODER_SEL_HALLSONLY_ENABLED << 10) | (FUNC_REGENERATION_ENABLED << 11) |
    	(FUNC_HOME_ENABLED << 12) | (FUNC_MOTOREST_ENABLED << 13) | (FUNC_CURTUNE_ENABLED << 14) |
    	(FUNC_GAINSW_ENABLED << 15));

    usSRegInBuf[FUNCMASK1] = (uint16)(DOUBLESAMP_ENABLE_SWITCH | (FUNC_SPDFF_ENABLED << 1) | (FUNC_TOQFF_ENABLED << 2) |
    	(FUNC_FORCECTRL_ENABLED << 3) | (FUNC_FORCECLOSEDLOOP_ENABLED << 4) | (FUNC_FRICOMP_ENABLED << 5) |
    	(FUNC_HIGHMODE_ENABLED << 6) | (FUNC_DUTYUPDATENOW_ENABLED << 7) | (SPECIAL_ELESCREW_ENABLE << 8) |
    	(FUNC_ENCODERCOMP_ENABLED << 9) | (FUNC_FEEDBACKONLOAD_ENABLED << 10) | (FUNC_NTF_ENABLED << 11)) |
    	(FUNC_SWEEP_ENABLED << 12);
}


/*---------------------------------------------------------------------------
 * Name		:	Motor_EnableServo
 * Input	:	No
 * Output	:	No
 * Description:	Motor enable
 *---------------------------------------------------------------------------*/
void Motor_EnableServo(void)
{
	FOC_Init(); 

	NFOC_IDREF = 0;
	NFOC_IQREF = 0;
	
	NFOC_UDFIN = 0;
    NFOC_UQFIN = 0;
	
	usSRegInBuf[CMDCUR] = 0;
	usSRegInBuf[MB_IDREF] = 0;
	
#if FUNC_ERRORCORRECTION_ENABLED
	ErrorCorrection_Demo_Init(); // Error correction initialization
#endif
	
#if FUNC_GAINSW_ENABLED
	GainSW_Demo_Init();  // Gain switching initialization
#endif //#if FUNC_GAINSW_ENABLED
	
	PI_Init();	// Velocity loop PI initialization
	
#if FUNC_FEEDBACKONLOAD_ENABLED
	FeedBackOnLoad_Demo_Init();
#endif
	
#if FUNC_FRICOMP_ENABLED
	FricCmp_Demo_Init();
#endif
	
#if FUNC_INERTIA_ENABLED
	InFricId_Demo_Init();
#endif //#if FUNC_INERTIA_ENABLED
	
#if FUNC_CURRENTBACK_ENABLED
	CurrBack_Demo_Init();
#endif
	
	InputFilter_Rst();

	mcFocCtrl.TargetRefFirstFlag = 0; // Clear flag for position command calculation
	
	usSRegInBuf[CMDVEL] = 0;
	mcElecAng.FOCThetaFlag = 0;

	Motor_Profile_Reset();	// Initialize trajectory planning related variables

#if FUNC_NTF_ENABLED
	NTF_Demo_Init();  // Nodal vibration suppression initialization
#endif //#if FUNC_NTF_ENABLED
  
#if FUNC_SPDFF_ENABLED
    SpdFF_Init(); // Velocity feedforward initialization
#endif //#if FUNC_SPDFF_ENABLED

#if FUNC_TOQFF_ENABLED   
    ToqFF_Init(); // Torque feedforward initialization
#endif //#if FUNC_TOQFF_ENABLED
    
#if EXCTRL_ECAT_ENABLED || EXCTRL_CANOPEN_ENABLED || COMM_CAN_PDO_ENABLED
    ECATCSP_Init();// Linear interpolation initialization
#endif //#if EXCTRL_ECAT_ENABLED
  
#if COMM_CAN_PDO_ENABLED
    DynTrap_Demo_Init();
#endif
   
#if DEADTIME_COMPENSATE_ENABLED
    DeadTimeCompensationInit(usSRegHoldBuf[DEADCOMPCUR]);
#endif
    
	RunMode_Update();
	
	OutputFilter_Init();  // torque filter initialization
	
#if (HW_UVW_POLARITY == UVWPOL_NORMAL)
	write_csr(DRV1_CMR, 0x0abF);
#else
	write_csr(DRV1_CMR, 0x057F);
#endif
    set_csr(DRV1_OUT, MOE);
    set_csr(DRV1_CR, DRVOE);			// Driver output enable	0-->Disable		1-->Enable
		
	SetReg(usSRegInBuf[DRIVESTATUS], STATUS_ENABLE, STATUS_ENABLE);
	
#if FUNC_FIELDWEAKEN_ENABLED
	FieldWeakenControlInit();
#endif
	
#if FUNC_SOFTCTRL_ENABLED
	FieldSoftControl_Demo_Init();
#endif
}


/*---------------------------------------------------------------------------
 * Name		:	Motor_DisableServo
 * Input	:	No
 * Output	:	No
 * Description:	Motor disable
 *---------------------------------------------------------------------------*/
void Motor_DisableServo(void)
{
	clr_csr(DRV1_CR, DRVOE);	// Driver output enable	0-->Disable		1-->Enable
	clr_csr(DRV1_OUT, MOE);
	clr_csr(DRV1_FCR0, NCALEN);	// disable FOC calculation enable, equivalent to disable FOC
	mcFocCtrl.CurLoopEnable = 0;
	mcFocCtrl.VelLoopEnable = 0;
	mcFocCtrl.PosLoopEnable = 0;
#if FUNC_FORCECLOSEDLOOP_ENABLED
	mcFocCtrl.FrcLoopEnable = 0;
#endif


	PI_Clear();
	
#if FUNC_FEEDBACKONLOAD_ENABLED
	FeedBackOnLoad_Clr();
#endif
	
#if FUNC_FRICOMP_ENABLED
	FricCmp_Clr();
#endif
	
	InputFilter_Rst();
	
#if FUNC_CURRENTBACK_ENABLED
	CurrBackProtect_Clr(&MotorCurrBack);
#endif
	
#if FUNC_NTF_ENABLED
	NTF_Rst();
#endif //#if FUNC_NTF_ENABLED
	
#if SPECIAL_ELESCREW_ENABLE
	memset(&ScrewCtrl, 0, sizeof(EleScrewTypedf));
	ScrewCtrl.ScrewStep = SCREW_NEAR_STEP;
	ScrewCtrl.ScrewStatus = READY;
	ScrewCtrl.PauseFlag = 0;
#endif //#if SPECIAL_ELESCREW_ENABLE
	
	mcFocCtrl.ThetaErr = 0;

#if FUNC_SOFTCTRL_ENABLED
	FieldSoftControl_Clr();
#endif

#if FUNC_FORCECTRL_ENABLED
	ForceCtrl_Clr();
#endif
	Motor_Profile_Clr();
	ModeSW.SwitchFlag = 0;
	
	memset(&mcSigGen, 0, sizeof(SigGenTypeDef));
	SetReg(usSRegInBuf[DRIVESTATUS], STATUS_ENABLE, 0);  
	
	usSRegInBuf[PTPVCMD] = 0;
	usSRegInBuf[CMDVEL] = 0;
	usSRegInBuf[CMDCUR] = 0;
}


/*---------------------------------------------------------------------------
 * Name		:	Motor_Open
 * Input	:	No
 * Output	:	No
 * Description:	Motor enters running state
 *---------------------------------------------------------------------------*/
void Motor_Open(void)
{  
	McStaSet.SetFlag.AutoEnableSetFlag = 1;
		
	Motor_DisableServo();
	Motor_EnableServo();
}


/*---------------------------------------------------------------------------
 * Name		:	Motor_Run
 * Input	:	No
 * Output	:	No
 * Description:	Running mode and parameter settings in run state
 *---------------------------------------------------------------------------*/
void Motor_Run(void)
{ 
	// Serial position mode
	Motor_Profile_Update();
	
	// Serial velocity mode
	Motor_SerialIn_Update();
}


/*---------------------------------------------------------------------------
 * Name		:	UpdateParam
 * Input	:	No
 * Output	:	No
 * Description:	Update parameter variables based on parameter table changes
 *---------------------------------------------------------------------------*/
void UpdateParam(void)
{	
	Scope_Update();
	
#if FUNC_GAINSW_ENABLED
	GainSW_Demo_Update();
#endif //#if FUNC_GAINSW_ENABLED
	
	PI_Update();
	
	InputFilter_Init();
	
	Encoder_Update();
	
	Motor_PhaseFind_Update();
	
	OutputFilter_CoeUpdate();

#if FUNC_SOFTCTRL_ENABLED
	FieldSoftControl_PIDUpdate();
#endif
	
#if FUNC_PROBE_ENABLED
	Probe_Update();
#endif
	
#if FUNC_PCOM_ENABLED
	PCOM_Update();
#endif

    mcRegParam.DriveCtrl = usSRegHoldBuf[DRIVECTRL];

	mcRegParam.ProfileCtrl = usSRegHoldBuf[PROFILECTRL];

    mcRegParam.FlashCtrl = usSRegHoldBuf[FLASHCTRL];

    mcRegParam.DigInStatus = usSRegInBuf[DIGINSTATUS];


    mcRegParam.PulseMode = GetReg(usSRegHoldBuf[DRIVEMODE],MODE_PULSEMODE1 | MODE_PULSEMODE0);
    if(mcRegParam.PulseMode != mcRegParam.PulseMode_Pre)
    {
        mcRegParam.PulseMode_Pre = mcRegParam.PulseMode;
    }

    // Current loop PI or complex vector controller
    if (usSRegHoldBuf[CVMOD] == 0)
    {
    	NFOC_DKP = usSRegHoldBuf[DQKP];
    	NFOC_DKI = usSRegHoldBuf[DQKI];
    	NFOC_QKP = usSRegHoldBuf[DQKP];
    	NFOC_QKI = usSRegHoldBuf[DQKI];
    }
    else
    {
    	NFOC_DKP = usSRegHoldBuf[DKP];
    	NFOC_DKI = usSRegHoldBuf[DKI];
    	NFOC_QKP = usSRegHoldBuf[QKP];
    	NFOC_QKI = usSRegHoldBuf[QKI];
    	
    	NFOC_CVK1 = ((int32)usSRegHoldBuf[CVK1] * (int32)usSRegHoldBuf[CFR]) >> 14;
    	NFOC_CVK2 = ((int32)usSRegHoldBuf[CVK2] * (int32)usSRegHoldBuf[CFR]) >> 14;
    	NFOC_CVK3 = ((int32)usSRegHoldBuf[CVK3] * (int32)usSRegHoldBuf[CFR]) >> 14;
    	NFOC_CVDK4 = ((int32)usSRegHoldBuf[CVDK4] * (int32)usSRegHoldBuf[CFR]) >> 14;
    	NFOC_CVQK4 = ((int32)usSRegHoldBuf[CVQK4] * (int32)usSRegHoldBuf[CFR]) >> 14;
    	NFOC_CVDK5 = ((int32)usSRegHoldBuf[CVDK5] * (int32)usSRegHoldBuf[CFR]) >> 14;
    	NFOC_CVQK5 = ((int32)usSRegHoldBuf[CVQK5] * (int32)usSRegHoldBuf[CFR]) >> 14;
    	NFOC_CVKI2D = ((int32)usSRegHoldBuf[CVKI2D] * (int32)usSRegHoldBuf[CFR]) >> 14;
    	NFOC_CVKI2Q = ((int32)usSRegHoldBuf[CVKI2Q] * (int32)usSRegHoldBuf[CFR]) >> 14;

    	if (mcRegParam.DQKQSel != usSRegHoldBuf[CVKQSEL])
    	{
    		reset_csr(DRV1_FCR7, CVKP_SEL1 | CVKP_SEL0 | CVKI1_SEL1 | CVKI1_SEL0 | CVKI2_SEL1 | CVKI2_SEL0 |
    			CVKO_SEL1 | CVKO_SEL0, usSRegHoldBuf[CVKQSEL] << 8);

    		mcRegParam.DQKQSel = usSRegHoldBuf[CVKQSEL];
    	}
    }


    SetReg(usSRegInBuf[CONTROLSTATUS], CTSTATUS_MCSTATE0 | CTSTATUS_MCSTATE1 | CTSTATUS_MCSTATE2 
                                     | CTSTATUS_MCSTATE3 | CTSTATUS_MCSTATE4, mcState);
    
    mcElecAng.ElecAngDir = ReadBit(usSRegHoldBuf[DRIVEMODE], MODE_ELECANGDIR);
    mcFocCtrl.AngDir = ReadBit(usSRegHoldBuf[DRIVEMODE], MODE_ANGDIR);
    mcFocCtrl.LoadAngDir = ReadBit(usSRegHoldBuf[DRIVEMODE], MODE_SFBANGDIR);
    mcFocCtrl.EAngDir = mcElecAng.ElecAngDir ^ mcFocCtrl.AngDir;

    // M-method
    mcFocCtrl.QepSpeedCoe = usSRegHoldBuf[QEPSPEEDCOE];
    NFOC_MBASE = usSRegHoldBuf[QEPSPEEDCOE];
    NFOC_MSHFT = usSRegHoldBuf[SPEEDCOERANK];
    if (GetReg(usSRegHoldBuf[DRIVESWITCH], SW_MTMODE))
    {
    	NFOC_MARR = VELCTRL_TS * 2;
    }
    else
    {
    	NFOC_MARR = VELCTRL_TS;
    }
    
    
    mcFocCtrl.EncRes = *((uint32*) &usSRegHoldBuf[ENCRES_L]);
    mcFocCtrl.SfbEncRes = *((uint32*) & usSRegHoldBuf[SFBENCRES_L]);
    
    mcFocCtrl.AngToCnt = mcFocCtrl.EncRes / (usSRegHoldBuf[POLES] >> 1);
    mcFocCtrl.QepLoadThetaOffset = *((int32*) & usSRegHoldBuf[SFBANGOFFSET_L]);

    mcFocCtrl.QepThetaOffset = *((int32*) & usSRegHoldBuf[ANGOFFSET_L]);

}


/*---------------------------------------------------------------------------
 * Name		:	Motor_Pulse_Handler
 * Input	:	No
 * Output	:	No
 * Description:	Pulse direction control
 *---------------------------------------------------------------------------*/
int32 Motor_Pulse_Handler(void)
{	
	return (mcProfile.StartingAngle + read_csr(TIM6_CNTR) * (int16)usSRegHoldBuf[GEARIN] 
		/(int16)usSRegHoldBuf[GEAROUT]);
}


/*---------------------------------------------------------------------------
 * Name		:	RegenerationHandler
 * Input	:	No
 * Output	:	No
 * Description:	Regenerative braking, handle regeneration based on direct duty control.
 *---------------------------------------------------------------------------*/
void RegenerationHandler(void)
{
	uint16 busvoltage = usSRegInBuf[BUSVOLTAGE];
	uint16 RegenDuty = 0;
	
	if (usSRegHoldBuf[REGENPOW] == 0 || usSRegHoldBuf[REGENRES] == 0 || usSRegHoldBuf[REGENCOE] == 0 ||
		busvoltage <= usSRegHoldBuf[REGENVMLOW] || usSRegHoldBuf[REGENVMLOW] > usSRegHoldBuf[REGENVMHIGH])
	{
		RegenDuty = 0;
	}
	else
	{
		if (busvoltage > usSRegHoldBuf[REGENVMHIGH])
			busvoltage = usSRegHoldBuf[REGENVMHIGH];
		
		RegenDuty = ((uint32)(busvoltage - usSRegHoldBuf[REGENVMLOW]) * usSRegHoldBuf[REGENCOE]) >> 6;
		if (RegenDuty > MAXREGENDUTY)
			RegenDuty = MAXREGENDUTY;
	}
    write_csr(TIM8_DR, MAXREGENDUTY - RegenDuty);

}

#if EXCTRL_ANALOG_ENABLED
/*---------------------------------------------------------------------------
 * Name		:	Motor_AnalogIn_Handler
 * Input	:	No
 * Output	:	No
 * Description:	Analog control, VelAnalog and CurAnalog Control
 *---------------------------------------------------------------------------*/
void Motor_AnalogIn_Handler(void)
{
	set_csr(ADC1_CR, ADCBSY);            // ???ADC
	while (readbit_csr(ADC1_CR, ADCBSY)) {};
	
	usSRegInBuf[ANALOGIN] = (int16)(ADCDR_ANAIN >> 3) - usSRegHoldBuf[ANINOFFSET];
	
	if((int16)usSRegInBuf[ANALOGIN] < (int16)usSRegHoldBuf[ANINDEADBAND] && (int16)usSRegInBuf[ANALOGIN] > -(int16)usSRegHoldBuf[ANINDEADBAND])
		mcAnalogInput.AnInValue = 0;
	else
		mcAnalogInput.AnInValue = usSRegInBuf[ANALOGIN];
	
	mcAnalogInput.AnInValue_k += (int32)usSRegHoldBuf[ANINLPFK] * (mcAnalogInput.AnInValue - mcAnalogInput.AnInValue_s);
	mcAnalogInput.AnInValue_s = mcAnalogInput.AnInValue_k >> 15;
	
	if(mcRegParam.WorkMode == VELANALOG) // Velocity loop
        usSRegInBuf[CMDVEL] = ((int32)mcAnalogInput.AnInValue_s * usSRegHoldBuf[ANINVSCALE]) >> 10;
	else if (mcRegParam.WorkMode == CURANALOG) // Current loop
        usSRegInBuf[CMDCUR] = ((int32)mcAnalogInput.AnInValue_s * usSRegHoldBuf[ANINISCALE]) >> 10;
#if FUNC_FORCECLOSEDLOOP_ENABLED
	else // Force loop
		usSRegInBuf[ACTFRC] = ((int32)mcAnalogInput.AnInValue_s * usSRegHoldBuf[ANINFSCALE]) >> 10; // Pressure feedback value
#endif
}
#endif // #if EXCTRL_ANALOG_ENABLED


#ifdef FAN_PIN
/*---------------------------------------------------------------------------
 * Name		:	Fan_Control
 * Input	:	No
 * Output	:	No
 * Description:	Fan control, control the fan with different duty cycle.
 *---------------------------------------------------------------------------*/
void Fan_Control(void)
{
    xor_csr(FAN_GPIO, FAN_PIN); // FANPIN = ~FANPIN;
}
#endif

/*---------------------------------------------------------------------------*
 * Name		:	void Check_InPos(void)
 * Input	:	NO
 * Output	:	NO
 * Description:	In-position signal, the motor is considered settled when PE (position error)  
 *              has remained below PEINPOS for the time defined by PEINPOSTIME.
 *---------------------------------------------------------------------------*/
void Check_InPos(void)
{
	int32 PeinPosRange = 0;
	int32 ThetaErr;
	static int32 TargetAngleLatch = 0;

	if (mcFocCtrl.PosLoopEnable == 1 && mcState != mcFault)						// check in position loop
	{
		ThetaErr = ABS(mcFocCtrl.ThetaErr);
		PeinPosRange = (int32)usSRegHoldBuf[PEINPOSRANGE];
#if FUNC_FEEDBACKONLOAD_ENABLED
		if (FEEDBACK_LOAD == Feedback_GetOnLoadFlag())  
			PeinPosRange = (int16)(((int64)PeinPosRange * Feedback_GetMotorToLoadCoef()) >> LOADCOEF);
#endif		
		if (ThetaErr <= PeinPosRange && (mcFocCtrl.TargetAngleFilt == TargetAngleLatch))
			mcFocCtrl.InPosCounter++;
		else
			mcFocCtrl.InPosCounter = 0;
		TargetAngleLatch = mcFocCtrl.TargetAngleFilt;

		if (mcFocCtrl.InPosCounter >= usSRegHoldBuf[PEINPOSTIME])
		{
			mcFocCtrl.InPosCounter = usSRegHoldBuf[PEINPOSTIME]; // in case overflow
			SetReg(usSRegInBuf[DRIVESTATUS], STATUS_INPOS, STATUS_INPOS);
		}
		else
		{
			SetReg(usSRegInBuf[DRIVESTATUS], STATUS_INPOS, 0);
		}

        /*-----------------------------------STOPPED--------------------------------------*/
		if ((mcRegParam.WorkMode == POSSERIAL 
#if EXCTRL_ECAT_ENABLED || EXCTRL_CANOPEN_ENABLED
			|| usSRegInBuf[FBOPMODE] == PROFILE_POSITION_MODE
#endif
			) && (Position_Profile_GetMotionStatus() == MS_MOVING ||
			(Position_Profile_GetMotionStatus() == MS_FINISH && 
			GetReg(usSRegHoldBuf[PROFILECTRL], PROF_MOTIONEN) != 0 &&
			GetReg(usSRegHoldBuf[PROFILECTRL], PROF_PROFILEREP) != 0)))
		{
			SetReg(usSRegInBuf[DRIVESTATUS], STATUS_STOPPED, STATUS_STOPPED);
		}
		else
		{
			SetReg(usSRegInBuf[DRIVESTATUS], STATUS_STOPPED, 0);
		}
	}
	else
	{
		mcFocCtrl.InPosCounter = 0;
		SetReg(usSRegInBuf[DRIVESTATUS], STATUS_INPOS, 0);
		SetReg(usSRegInBuf[DRIVESTATUS], STATUS_STOPPED, 0);
	}
}


#if MOTOR_VCM_ENABLED
/*---------------------------------------------------------------------------
 * Name		:	VCM_DriverOut
 * Input	:	No
 * Output	:	No
 * Description:	Voice coil motor, update PWM of Voice Coil Motor.
 *---------------------------------------------------------------------------*/
void VCM_DriverOut(void)
{
	int16 U_Duty;
	uint16 DR1;
	uint16 DR2;
	
	U_Duty = NFOC_UQFIN;
	U_Duty = ((int32) U_Duty * PWM_VALUE_LOAD) >> 16;

	DR1 = ((PWM_VALUE_LOAD) >> 1) + U_Duty;
	DR2 = ((PWM_VALUE_LOAD) >> 1) - U_Duty;

	NFOC_DR1 = DR1;
	NFOC_DR1N = DR1;
	NFOC_DR2 = DR2;
	NFOC_DR2N = DR2;
	NFOC_DR3 = 0;	// When set to 0, the upper switch is always on and the lower switch is always off; W-phase to ground voltage is 11.8V; because CMR register polarity is set to lower bridge normal output, upper bridge inverted complementary output.
	NFOC_DR3N = 0;	// When set to PWM_VALUE_LOAD, the lower switch is always on and the upper switch is always off; W-phase to ground voltage is 0V.
}
#endif // #if MOTOR_VCM_ENABLED

