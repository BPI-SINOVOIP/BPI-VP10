/*
 * Copyright (c) 2021-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : AddFunction.c
 * Author        : Summer
 * Date          : 2021-11-13
 * Description   : This file defines some basic function.
 *
 * Record        :
 * V1.0, 2021-11-13, Summer: Created file
 */

/********************************************************************************
* Header Definition
********************************************************************************/
#include <Myproject.h>


/********************************************************************************
* Macro & Structure Definition
*******************************************************************************/

#if TEST_SPIDEBUG_SW_ENABLED
unsigned short spidebug[4] = { 0 };		//< SPI debug output channel buffer; the SPI debugger will output this variable's value
#endif


uint16 TestVariable_1 = 0;
uint16 TestVariable_2 = 0;
uint16 TestVariable_3 = 0;
uint32 TestVariable_u32_1 = 0;
uint32 TestVariable_u32_2 = 0;
uint32 TestVariable_u32_3 = 0;


/********************************************************************************
* Internal Routine Prototypes
********************************************************************************/

/*--------------------------------------------------------------------------- 
 * Name		:	Test_Buff
 * Input	:	No
 * Output	:	No
 * Description:	Place related variables into the test channels to facilitate troubleshooting
 *				and debugging of code bugs using an oscilloscope. You can also set the amplitude for individual test channels in the code.
 *---------------------------------------------------------------------------*/
void Test_Buff(void)
{
	usSRegInBuf[TESTVAR0] = TestVariable_1;
	usSRegInBuf[TESTVAR1] = TestVariable_2;
	usSRegInBuf[TESTVAR2] = TestVariable_3;
	usSRegInBuf[TESTVAR3_H] = TestVariable_u32_1 >> 16;
	usSRegInBuf[TESTVAR3_L] = TestVariable_u32_1;
	usSRegInBuf[TESTVAR4_H] = TestVariable_u32_2 >> 16;
	usSRegInBuf[TESTVAR4_L] = TestVariable_u32_2;
	usSRegInBuf[TESTVAR5_H] = TestVariable_u32_3 >> 16;
	usSRegInBuf[TESTVAR5_L] = TestVariable_u32_3;
}


/*--------------------------------------------------------------------------- 
 * Name          : IWDT_Init
 * Input         : None
 * Description   : This function initializes the IWDT (independent watchdog). The user only needs to provide the reload
 *                value to this function; enabling and loading of the reload value for the independent watchdog are handled here.
 *                To modify IWDT_KR, 0x5555 must first be written to the IWDT_KR register.
 *---------------------------------------------------------------------------*/
void IWDT_Init(void)
{
	write_csr(IWDT_KR, IWDT_KRCHANGE);		// Must write 0x5555 first before modifying the IWDT_KR register
	write_csr(IWDT_KR, IWDT_OPEN);			// Enable independent watchdog
	
	write_csr(IWDT_KR, IWDT_KRCHANGE);
	write_csr(IWDT_REL, IWDT_RELOAD);		// Write reload value
	
	write_csr(IWDT_KR, IWDT_KRCHANGE);
	write_csr(IWDT_KR, IWDT_FEED);			// Enable write protection
}

/*--------------------------------------------------------------------------- 
 * Name			 : IWDT_Refresh
 * Input         : None
 * Description   : This function performs the IWDT feed operation; feeding of the independent watchdog is completed by this function.
 *                 If the software does not write a reset command or disable command to the key register before the counter finishes,
 *                 the system will generate an independent watchdog reset.
 *---------------------------------------------------------------------------*/
void IWDT_Refresh(void)
{
	// Independent watchdog feed
	write_csr(IWDT_KR, IWDT_KRCHANGE);
	write_csr(IWDT_KR, IWDT_FEED);
}

/*--------------------------------------------------------------------------- 
 * Name          : SPIDebugSet
 * Input         : None
 * Output        : None
 * Description   : Initializes SPI debug, supporting hardware SPI debug (by specifying the hardware register address)
 *				    and software SPI debug (by placing software values in the spidebug variable). The SPI debug tool
 *					outputs corresponding signals which can be observed with an oscilloscope.
 *---------------------------------------------------------------------------*/
void SPIDebugSet(void)
{
#if TEST_SPIDEBUG_HW_ENABLED || TEST_SPIDEBUG_SW_ENABLED
//	SPI_Init();
#endif
	write_csr(SPIDBG_DMA_LEN, 7);
	write_csr(SPIDBG_DMA_CR, DMAEN | DMA_MON_Send);

#if TEST_SPIDEBUG_HW_ENABLED
	write_csr(SPIDBG_DMA_BA, HARD_SPIDATA);
#elif TEST_SPIDEBUG_SW_ENABLED
	write_csr(SPIDBG_DMA_BA, spidebug);
#endif
	// 00: PA9 multiplexed as DataMonitor; 01: PA0 multiplexed as DataMonitor; 1x: PB0 multiplexed as DataMonitor
	clr_csr(PH_SEL, MONCT1);  //DataMonitor pin enable 1  
	clr_csr(PH_SEL, MONCT0);  //DataMonitor pin enable 0

	set_csr(SPIDBG_DMA_CR, DMABSY);
	set_csr(SPIDBG_DMA_CR, DMACONEN);
}
	
/*--------------------------------------------------------------------------- 
 * Name          : SignalDebugSet
 * Input         : None
 * Output        : None
 * Description   : Configure related pins to output FOC test signals or the sampled results of CMPx_OUT
 *---------------------------------------------------------------------------*/
void SignalDebugSet(void)
{
	/*Observation signal Select*/
	reset_csr(CMP_DBR, DBG1SEL0 | DBG1SEL1 | DBG1SEL2 | DBG1SEL3 | DBG1SEL4, GPA1_DBG_Conf);
	reset_csr(CMP_DBR, DBG2SEL0 | DBG2SEL1 | DBG2SEL2 | DBG2SEL3 | DBG2SEL4, GPB0_DBG_Conf);

	clr_csr(PH_SEL, CMPCT);		// Comparator signal output pin selection 0: PA1 1: PA3
	reset_csr(CMP_DBR, CMPSEL0 | CMPSEL1 | CMPSEL2 | CMPSEL3 | CMPSEL4, GPAx_DBG_Conf);
}

/*--------------------------------------------------------------------------- 
 * Name     :   void Motor_Charge(void)
 * Input    :   NO
 * Output   :   NO
 * Description: Pre-charge. When continuously in pre-charge state and the motor is not connected, this can be used to verify IPM or MOSFETs.
 *              The pre-charge proceeds in three steps: first pre-charge phase U; second pre-charge phases U and V; third pre-charge phases U, V, and W.
 *---------------------------------------------------------------------------*/
void Motor_Charge(void)
{
	if (McStaSet.SetFlag.ChargeSetFlag == 0)
	{
		McStaSet.SetFlag.ChargeSetFlag = 1;
		set_csr(DRV1_CR, DRVEN);			 /* Counter enable... */
		write_csr(DRV1_DR, (unsigned short)((PWM_VALUE_LOAD) >> 1)); /* Lower bridge arm 50% duty... */
		write_csr(DRV1_CMR, 0x0000);     /* Pre-charge configuration differs from normal FOC configuration... */
		set_csr(DRV1_OUT, MOE);			 /* Enable MOE... */
		set_csr(DRV1_CR, DRVOE);			// Driver output enable 0-->Disable		1-->Enable
		mcFocCtrl.ChargeStep = 0;
		mcFocCtrl.State_Count = CHARGE_TIME;
		mcFocCtrl.ChargeFinish = 0;
	}

	if ((mcFocCtrl.State_Count < CHARGE_TIME) && (mcFocCtrl.ChargeStep == 0))
	{
		mcFocCtrl.ChargeStep = 1;
		reset_csr(DRV1_CMR, ULE, ULE);  /* U-phase lower bridge arm conduction... */

		set_csr(DRV1_OUT, MOE);
		set_csr(DRV1_CR, DRVOE);		// Driver output enable 0-->Disable		1-->Enable
	}
	if ((mcFocCtrl.State_Count <= (CHARGE_TIME << 1) / 3) && (mcFocCtrl.ChargeStep == 1))
	{
		mcFocCtrl.ChargeStep = 2;
		reset_csr(DRV1_CMR, VLE, VLE); /* V-phase lower bridge arm conduction... */
	}
	if ((mcFocCtrl.State_Count <= CHARGE_TIME / 3) && (mcFocCtrl.ChargeStep == 2))
	{
		mcFocCtrl.ChargeStep = 3;
		reset_csr(DRV1_CMR, WLE, WLE); /* W-phase lower bridge arm conduction... */
	}

	if ((mcFocCtrl.State_Count == 0) && (mcFocCtrl.ChargeStep == 3))
	{
		mcFocCtrl.ChargeFinish = 1;
	}

}