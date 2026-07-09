/*
 * Copyright (c) 2024-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : FreqDiv.c
 * Author        : Victor.jin
 * Date          : 2024-04-07
 * Description   : Frequency Division Output
 *
 * Record        :
 * V1.0, 2024-04-07, Victor.jin: Created file
 */


/********************************************************************************
* Header Definition
********************************************************************************/
#include <Myproject.h>


#if EXCTRL_ENCOUT_ENABLED

/********************************************************************************
* Macro & Structure Definition
*******************************************************************************/
FreqDivTypedef FreqDiv = { 0 };


/********************************************************************************
* Internal Routine Prototypes
********************************************************************************/
void FreqDiv_Init(void);
void FreqDiv_Handler(void);


/*---------------------------------------------------------------------------
 * Name		:	FreqDiv_Init
 * Input	:	No
 * Output	:	No
 * Description:	Frequency division output initialization
 *---------------------------------------------------------------------------*/
void FreqDiv_Init(void)
{
	FreqDiv.OUT_SourceSel = usSRegHoldBuf[ENCOUTMODE] & 0x03;				// 0-Disable output 1-Encoder division output 2-Encoder synchronous output 3-Pulse command synchronous output
	FreqDiv.OUT_PhaseSel = (usSRegHoldBuf[ENCOUTMODE] & 0x04) >> 2;			// 0-A leads B		1-B leads A
	FreqDiv.OUT_Z_ModeSel = (usSRegHoldBuf[ENCOUTMODE] & 0x08) >> 3;		// 0-One Z signal per revolution/pole pitch		1-Actual feedback produces Z signal
	FreqDiv.OUT_Z_PolaritySel = (usSRegHoldBuf[ENCOUTMODE] & 0x10) >> 4;	// 0-Z signal high level active	1-Z signal low level active

	FreqDiv.OUT_FreqDivPulse = ((uint32)usSRegHoldBuf[ENCOUTRES_H] << 16) | usSRegHoldBuf[ENCOUTRES_L];	// Encoder frequency division pulse count
	FreqDiv.OUT_Z_PulseInterval = FreqDiv.OUT_FreqDivPulse / 4;	// Cycle for Z signal generation, one generated per single revolution division pulse count

	
	// QEP output mode loads DR configuration
	clr_csr(TIM5_CR1, T5_CNTR_CLR_EN);	// 0-DR value updated every master clock, 1-DR value updated when Driver1 carrier interrupt DCIF arrives
	
	if (FreqDiv.OUT_SourceSel != 0) // 1-Encoder frequency division output 2-Encoder synchronous output 3-Pulse command synchronous output
	{
		/* DR and QEP_ARR values must be re-updated after changing the operation mode, otherwise internal exceptions will occur */
		set_csr(TIM5_CR0, T5MOD2);	// 000-->Input capture mode		001-->Output mode
		clr_csr(TIM5_CR0, T5MOD1);	// 010-->Input counting mode		011-->QEP input or step mode
		clr_csr(TIM5_CR0, T5MOD0);	// 100-->QEP output mode

		// Timer5 QEP A output polarity configuration
		clr_csr(TIM5_CR2, TIM5_A_EDGE_SEL);	// 0-Initial level is low	1-Initial level is high
		// Timer5 QEP B output polarity configuration
		set_csr(TIM5_CR2, TIM5_B_EDGE_SEL);	// 0-Initial level is low	1-Initial level is high

		// Count value within one output cycle at the current clock frequency. E.g.: 48M clock 8kHz interrupt: 48000000/8000 = 6000
		// ! Modify this macro when changing the frequency division output cycle
		write_csr(TIM5_ARR, MAXFREQOUT);

		if (FreqDiv.OUT_SourceSel == 1)			// 1-Encoder frequency division output
		{
			// Timer5 QEP AB output selection
			clr_csr(TIM5_CR2, TIM5_AB_SEL1);		// 00-Timer5 calculated output
			clr_csr(TIM5_CR2, TIM5_AB_SEL0);		// 01-Pass-through output of T2 input		10-Pass-through output of T6 input

			// Output phase selection
			if (FreqDiv.OUT_PhaseSel == 0)		// 0-A leads B
			{
				FreqDiv.OUT_PhaseFlag = 1;
			}
			else							// 1-B leads A
			{
				FreqDiv.OUT_PhaseFlag = -1;
			}
			
			// Z signal mode selection
			if (FreqDiv.OUT_Z_ModeSel == 0)		// 0-Output one Z signal per revolution/pole pitch
			{
				// Timer5 QEP Z output selection
				clr_csr(TIM5_CR2, TIM5_Z_SEL1);		// 00-Timer5 calculated output
				clr_csr(TIM5_CR2, TIM5_Z_SEL0);		// 01-Pass-through output of T2 input		10-Pass-through output of T6 input

				write_csr(TIM5_QEP_ARR, FreqDiv.OUT_Z_PulseInterval);
			}
			else							// 1-Output Z signal is consistent with encoder signal
			{
				// Timer5 QEP Z output selection
				clr_csr(TIM5_CR2, TIM5_Z_SEL1);		// 00-Timer5 calculated output
				set_csr(TIM5_CR2, TIM5_Z_SEL0);		// 01-Pass-through output of T2 input		10-Pass-through output of T6 input
			}
			// Z signal polarity selection
			if (FreqDiv.OUT_Z_PolaritySel == 0)	// 0-Z signal high level active
			{
				clr_csr(TIM5_CR1, T5Z_EDGE_SEL);
			}
			else							// 1-Z signal low level active
			{
				set_csr(TIM5_CR1, T5Z_EDGE_SEL);
			}
		}
		else if (FreqDiv.OUT_SourceSel == 2)	// 2-Encoder synchronous output (cannot be used without QEP encoder input; polarity or phase cannot be changed during pass-through)
		{
			// Timer5 QEP AB output selection
			clr_csr(TIM5_CR2, TIM5_AB_SEL1);		// 00-Timer5 calculated output
			set_csr(TIM5_CR2, TIM5_AB_SEL0);		// 01-Pass-through output of T2 input		10-Pass-through output of T6 input

			// Z signal mode selection
			if (FreqDiv.OUT_Z_ModeSel == 0)		// 0-Output one Z signal per revolution/pole pitch
			{
				// Timer5 QEP Z output selection
				clr_csr(TIM5_CR2, TIM5_Z_SEL1);		// 00-Timer5 calculated output
				clr_csr(TIM5_CR2, TIM5_Z_SEL0);		// 01-Pass-through output of T2 input		10-Pass-through output of T6 input

				write_csr(TIM5_QEP_ARR, FreqDiv.OUT_Z_PulseInterval);
			}
			else							// 1-Output Z signal is consistent with encoder signal
			{
				// Timer5 QEP Z output selection
				clr_csr(TIM5_CR2, TIM5_Z_SEL1);		// 00-Timer5 calculated output
				set_csr(TIM5_CR2, TIM5_Z_SEL0);		// 01-Pass-through output of T2 input		10-Pass-through output of T6 input
			}
			// Z signal polarity selection
			if (FreqDiv.OUT_Z_PolaritySel == 0)	// 0-Z signal high level active
			{
				clr_csr(TIM5_CR1, T5Z_EDGE_SEL);
			}
			else							// 1-Z signal low level active
			{
				set_csr(TIM5_CR1, T5Z_EDGE_SEL);
			}
		}
		else if (FreqDiv.OUT_SourceSel == 3)	// 3-Pulse command synchronous output
		{
			// Timer5 QEP AB output selection
			set_csr(TIM5_CR2, TIM5_AB_SEL1);		// 00-Timer5 calculated output
			clr_csr(TIM5_CR2, TIM5_AB_SEL0);		// 01-Pass-through output of T2 input		10-Pass-through output of T6 input

			/* Set to simulation output and clear QEP_ARR so that the Z signal is not output */
			clr_csr(TIM5_CR2, TIM5_Z_SEL1);		// 00-Timer5 calculated output
			clr_csr(TIM5_CR2, TIM5_Z_SEL0);		// 01-Pass-through output of T2 input		10-Pass-through output of T6 input

			clr_csr(TIM5_CR1, T5Z_EDGE_SEL);	// Z polarity selection (0 - high level active; 1 - low level active)
			write_csr(TIM5_QEP_ARR, 0);
		}
	}
	else	// 0-Disable output
	{
		/* In the disable output mode, it can be used for full-closed loop function as encoder output. Remaining configurations for encoder input can be added here later. */
		clr_csr(TIM5_CR0, T5MOD2);	// 000-->Input capture mode		001-->Output mode
		set_csr(TIM5_CR0, T5MOD1);	// 010-->Input counting mode		011-->QEP input or step mode
		set_csr(TIM5_CR0, T5MOD0);	// 100-->QEP output mode
	}
}


/*---------------------------------------------------------------------------
 * Name		:	FreqDiv_Handler
 * Input	:	No
 * Output	:	No
 * Description:	Update frequency division output
 *---------------------------------------------------------------------------*/
void FreqDiv_Handler(void)
{
	if (FreqDiv.OUT_SourceSel != 0) // 1-Encoder frequency division output 2-Encoder synchronous output 3-Pulse command synchronous output
	{
		if (mcFocCtrl.EncRes != 0)	// If the divisor is 0, the digital calculation result is -1, which is currently avoided by software
		{
			FreqDiv.EncPos = mcFocCtrl.QepPos;
			// Pulses output in this step including decimals (after amplification) = Input pulse difference of this step * Total number of single-turn frequency division outputs
			FreqDiv.OUT_PulseDecimal = (int64)(FreqDiv.EncPos - FreqDiv.EncPosLatch) * FreqDiv.OUT_FreqDivPulse;	
			// Actual value of output pulses in this step = (Pulses output in this step including decimals (after amplification) + Fractional remainder from previous step (after amplification)) / Total number of single-turn encoder inputs				
			FreqDiv.OUT_PulseDelta = (FreqDiv.OUT_PulseDecimal + FreqDiv.OUT_PulseRemain) / (int32)mcFocCtrl.EncRes;	

			// When the output frequency division number is less than the single-turn resolution, a pulse needs to be introduced in step 0, i.e., a negative pulse is generated upon the first reversal, otherwise one pulse will be lost
			if (FreqDiv.OUT_FreqDivPulse < mcFocCtrl.EncRes && FreqDiv.OUT_PulseDelta < 0)
				FreqDiv.OUT_PulseDelta -= 1;																	

			// Fractional remainder of this step (after amplification) = Fractional remainder of previous step (after amplification) + Pulses output in this step including decimals (after amplification) - Actual number of pulses output in this step * Total number of single-turn encoder inputs
			FreqDiv.OUT_PulseRemain += FreqDiv.OUT_PulseDecimal - FreqDiv.OUT_PulseDelta * mcFocCtrl.EncRes;			
			
			FreqDiv.EncPosLatch = FreqDiv.EncPos;
		}
		else
		{
			FreqDiv.OUT_PulseDelta = 0;
		}

		if (FreqDiv.OUT_PhaseSel == 0)		// Number of pulses output within one Drv interrupt cycle. Writing a positive number makes A lead B, writing a negative number makes B lead A
		{
			FreqDiv.OUT_PulseDelta = FreqDiv.OUT_PulseDelta;
		}
		else
		{
			FreqDiv.OUT_PulseDelta = -FreqDiv.OUT_PulseDelta;
		}
	}
	else
	{
		FreqDiv.OUT_PulseDelta = 0;
	}
	write_csr(TIM5_DR, FreqDiv.OUT_PulseDelta);	// Number of pulses output by frequency division in each interrupt cycle, updated in the next interrupt cycle after writing
}


#endif // #if EXCTRL_ENCOUT_ENABLED