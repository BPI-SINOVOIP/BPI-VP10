/*
 * Copyright (c) 2021-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : main.c
 * Author        : Fortior Application Team
 * Date          : 2021-04-27
 * Description   : 主循环
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


/*---------------------------------------------------------------------------*/
/* Name		:	void main(void)
/* Input	:	NO
/* Output	:	NO
/* Description:	主函数主要功能是初始化，包括上电等待，软件初始化，硬件初始化，
/*              调试模式设置，主循环扫描。
/*---------------------------------------------------------------------------*/
void main(void)
{
	Delay_ms(SYSTEM_POWERUP_TIME);// Wait until voltage and current stable

	/*Software Init*/
	SoftwareInit();

	/*Hardware Init*/
	HardwareInit();

	/****************************总中断使能**************************/
	set_csr(MIE, IRQ_EN);
	/****************************************************************/

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

			UpdateTemperature();		// 更新温度值
			
			/*****故障保护函数功能，如过欠压保护、启动保护、缺相、堵转等********/
			Fault_Detection();
			Fault_TimeCount();			// 报错计时

			Check_InPos();				// 检测是否到位完成

#if FUNC_LED_TUBE_ENABLED
			LedTube_UpdateStatus();       // 更新数码管的显示值
#endif //#if FUNC_LED_TUBE_ENABLED

#if FUNC_LED_DIODE_ENABLED
			LedDiode_Display();		     // 更新LED灯的闪烁
#endif // #if FUNC_LED_DIODE_ENABLED

			if (mcState == mcPhaseFind && McStaSet.SetFlag.PhaseFindSetFlag == 1)
				Motor_PhaseFind();

			
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
			
#if ENCODER_SEL_HALL_ENABLED
			usSRegInBuf[HALLS] = GetHallStatus();
#endif // #if ENCODER_SEL_HALL_ENABLED


			/*****电机状态机的时序处理*****/
			if (mcFocCtrl.State_Count > 0) mcFocCtrl.State_Count--;  // 状态机切换专用计数器
			
#if FUNC_DISMODE_ENABLED
			EmergencyStop_TimeCount();
#endif //#if FUNC_DISMODE_ENABLED
			
#if FUNC_FORCECTRL_ENABLED
			if (ForceCtrl.TimeCounter > 0) ForceCtrl.TimeCounter--;  // 力控模式各阶段等待时间计数器
#endif //#if FUNC_FORCECTRL_ENABLED
			
#if SPECIAL_ELESCREW_ENABLE
			ScrewCtrl_ProtectWarn();
#endif

#if FUNC_HOME_ENABLED
			Home_TimeCount();  // 回零计时
#endif //#if FUNC_HOME_ENABLED
			
			Motor_Profile_TimeCount();  // 位置规划计时
			
#if FUNC_MOTOREST_ENABLED
			if ((mcState == mcMotorIdentify) && (McStaSet.SetFlag.IdentifySetFlag == 1))
				Motor_Identify_realize();
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
		
		ModeSW_Update();

		MC_Control();                           // 主控函数

		if (mcState != mcReady)
		{
			UpdateParam();			                // 根据modbus传过来的参数更新变量值(非实时)
			UpdateDigitalIO();                      // 更新IO状态

#if FUNC_REGENERATION_ENABLED
			RegenerationHandler();                  // 再生制动
#endif //#if FUNC_REGENERATION_ENABLED

		}
		
		IWDT_Refresh();					//独立看门狗喂狗
		
#if EXCTRL_CANOPEN_ENABLED
		CANOpenProcess();
#endif //#if EXCTRL_CANOPEN_ENABLED

#if DEBUG_UART_ENABLED > 0 // 串口测试模式
		UART_ANODubugerBuffConfig();
		SendDataByUart();
#elif COMM_UART_ENABLED > 0 // 串口上位机通信模式
		eMBPoll();
#endif
		
#if COMM_CAN_ENABLED > 0 // CAN上位机通信模式
		eCSPoll();
#endif
	}
}



/*---------------------------------------------------------------------------*/
/* Name		:	void SoftwareInit(void)
/* Input	:	NO
/* Output	:	NO
/* Description:	软件初始化，初始化所有定义变量
/*---------------------------------------------------------------------------*/
void SoftwareInit(void)
{
	memset(NFOC_BASE, 0, 2048);
	/****初始化所有定义的参数变量****/
	MotorControlInit();
	/****电机初始状态为mcReady，故障保护为无故障******/
	mcState = mcReady;
}



/*---------------------------------------------------------------------------*/
/* Name		:	void HardwareInit(void)
/* Input	:	NO
/* Output	:	NO
/* Description:	硬件初始化，初始化需要使用的硬件设备配置，FOC必须配置的是
/*              运放电压、运放初始化、ADC初始化、Driver初始化
/*              TIM4初始化，其他的可根据实际需求加。
/*---------------------------------------------------------------------------*/
void HardwareInit(void)
{
	write_csr(CK_CR, 0xfffff); // 启动时钟


	/****** 功能IO初始化 ******/
	GPIO_Init();

	/****** SPI DEBUG 初始化 ******/
#if TEST_SPIDEBUG_HW_ENABLED || TEST_SPIDEBUG_SW_ENABLED
	SPIDebugSet();
#endif

	/****** Signal Debug 初始化 ******/
#if TEST_SIGNALDEBUG_ENABLED
	SignalDebugSet();			//打开DATAMONITOR，管脚PA9连接到单线DBG的板子能查看信号，管脚PA1能查看电流采样时机
#endif
	
#if FUNC_LED_TUBE_ENABLED || !FUNC_SOFT_EEPROM_ENABLED
	/****** IIC LED/EEPROM 初始化 ******/
	I2C_Init();
#endif // #if FUNC_LED_TUBE_ENABLED || FUNC_EEPROM_ENABLED
	
#if FUNC_EEPROM_ENABLED
	/****** 加载Flash的参数表 ******/
	// set newly added parameters default value here
	//	usSRegHoldBuf[FBSYNCSET] = 65241;
	UploadDataFromEEPROM(); // 参数表中包含电流基准校正需要的参数
	Fault_UploadErrCode();
	mcRegParam.DriveMode = usSRegHoldBuf[DRIVEMODE];
#endif // #if FUNC_EEPROM_ENABLED
	
	
#if DEBUG_UART_ENABLED > 0 // 串口测试模式
#if(MODBUS_UART == 1)
	UART1_Init();	// 串口调试模式 uart initial in UART.c
#else
	UART2_Init();
#endif
#elif COMM_UART_ENABLED > 0 // 串口上位机通信模式
	eMBInit(MODEBUS_SLAVE_ID);
	eMBEnable();
#endif

#if COMM_CAN_ENABLED > 0 // CAN上位机通信模式
	usSRegHoldBuf[CANBITRATE] = 0;
	eCSInit(usSRegHoldBuf[CANBITRATE]);
	eCSEnable();
#endif
	

#if EXCTRL_ECAT_ENABLED
	/****** EtherCAT同步信号外部中断初始化 ******/
	EXTI1_Init();	// 
	/****** EtherCAT初始化 ******/
	EcatInit();
#endif // #if EXCTRL_ECAT_ENABLED
	
	
#if EXCTRL_CANOPEN_ENABLED
	/****** CANopen初始化 ******/
#if (HARDWARE_VERSION == HARDWARE_FPGA_HIGHVOL_SWITCH || HARDWARE_VERSION == HARDWARE_FPGA_LOWVOL_SWITCH)
	usSRegHoldBuf[COMMADDR] = 5;
#endif
	usSRegHoldBuf[CANBITRATE] = 0;
	CANOpenInit(usSRegHoldBuf[COMMADDR], usSRegHoldBuf[CANBITRATE]);
#endif // #if EXCTRL_CANOPEN_ENABLED
	
	/****** ADC参考电压电压配置 ******/
	VREFConfigInit();
	
#if (HW_AMP_SEL == AMP_ONCHIP)
	/****** 运算放大器初始化 ******/
    AMP_Init();
#endif

	/****** ADC初始化 ******/
	ADC_Init();
	ADC2_Init();
	
	/****** 硬件FO过流，比较器初始化，用于硬件过流比较保护 ******/
#if (HardwareCurrent_Protect == Hardware_FO_Protect)		//外部中断初始化，用于外部中断硬件过流FO的保护
#if (Hardware_FO_SRC == Hardware_FO_EXTI0)
	EXTI0_Init();
#else
	EXTI2_Init();
#endif
#elif (HardwareCurrent_Protect == Hardware_CMP_Protect)		//选择比较过流，比较器初始化
	CMP3_Init();
#elif (HardwareCurrent_Protect == Hardware_FO_CMP_Protect)	//两者都选择
#if (Hardware_FO_SRC == Hardware_FO_EXTI0)
	EXTI0_Init();
#else
	EXTI2_Init();
#endif
	CMP3_Init();
#endif


	/****** Driver初始化 ******/
	Driver1_Init();

	/****** 位置环中断Timer3初始化 ******/
	Timer3_Init();
	
	/****** 编码器初始化 ******/
	Encoder_Init();

#if EXCTRL_ENCOUT_ENABLED
	/****** 分频输出初始化 ******/
	Timer5_Init();
#endif // #if EXCTRL_ENCOUT_ENABLED

#if EXCTRL_PULSE_ENABLED
	/****** 脉冲方向输入初始化 ******/
	Timer6_Init();
#endif // #if EXCTRL_PULSE_ENABLED

#if FUNC_REGENERATION_ENABLED
	/****** 制动斩波Timer初始化 ******/
	Timer8_Init();
#endif // #if FUNC_REGENERATION_ENABLED

#if FUNC_PROBE_ENABLED
	/****** 探针输入初始化 ******/
	Probe_Init();
#endif // #if FUNC_PROBE_ENABLED
	
#if FUNC_PCOM_ENABLED
	/****** 位置比较输出初始化 ******/
	PCOM_Init();
#endif // #if FUNC_PCOM_ENABLED

#if FUNC_LED_TUBE_ENABLED
	/****** 数码管初始化 ******/
	LedTube_Init();
#endif // #if FUNC_LED_TUBE_ENABLED

	/****** 上拉不用的GPIO ******/
	GPIO_PU_Init();
	
	/****** 独立看门狗初始化 ******/
	IWDT_Init();
}