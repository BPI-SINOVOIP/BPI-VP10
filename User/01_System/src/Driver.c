/*
 * Copyright (c) 2022-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : Driver.c
 * Author        : Fortior Application Team
 * Date          : 2022-09-21
 * Description   : define Driver FOC
 *
 * Record        :
 * V1.0, 2022-09-21, Fortior Application Team: Created file
 */


#include <Myproject.h>


void Driver1_Init(void)
{
	/* Configure PWM period value and dead time */
	write_csr(DRV1_ARR, PWM_VALUE_LOAD);		// Carrier frequency period value, triangular wave increases from 0 to ARR-1, then decreases from ARR to 1
	write_csr(DRV1_DTR, ((uint32)usSRegHoldBuf[DEADTIME] * MCU_CLOCK) >> 10); // Dead time
	write_csr(DRV1_DR, 0);
	write_csr(DRV1_CMR, 0x003f);				// Six-tube enable
	write_csr(DRV1_OUT, HW_PWM_IDLELEVEL);		// Idle level
	
	// If initial values are not assigned, speed calculation before enable after power-up in double sampling speed automatic mode will have anomalies
	write_csr(DRV1_TRG1, 0x00);					// DR value for the 1st sampling, assign initial value
	write_csr(DRV1_TRG2, PWM_VALUE_LOAD);		// DR value for the 2nd sampling, assign initial value


	/* Selection of final output polarity of the driver */
#if(HW_PWM_LEVEL_MODE == LOW_LEVEL)
	{
		set_csr(DRV1_OUT, HREV_EN);
		set_csr(DRV1_OUT, LREV_EN);
	}
#elif(HW_PWM_LEVEL_MODE == UP_H_DOWN_L)
	{
		set_csr(DRV1_OUT, LREV_EN);
	}
#elif(HW_PWM_LEVEL_MODE == UP_L_DOWN_H)
	{
		set_csr(DRV1_OUT, HREV_EN);
	}
#endif


	/* Clear interrupt flags, enable interrupts, configure comparison values, set interrupt priority */
	clr_csr(DRV1_IER, FGIE);			// FG interrupt enable			0-->Disable		1-->Enable
	clr_csr(DRV1_IFR, FGIF);			// Clear FG interrupt flag

	clr_csr(DRV1_IER, THIE);
	clr_csr(DRV1_IFR, THIF);

	clr_csr(DRV1_IFR, DCIF);			// Clear DRV interrupt flag

	/**************************************************
	DRV comparison match interrupt mode
	When the count value equals DRV1_COMR, judge whether to generate an interrupt flag based on the DCIM setting
	00: No interrupt       01: Upward direction
	10: Downward direction         11: Upward/Downward direction
	*************************************************/
	set_csr(DRV1_IER, DCIM1);
	clr_csr(DRV1_IER, DCIM0);

	/* Set comparison match value of the DRV counter; when the DRV count value equals COMR, judge if a comparison match event is generated according to DCIM of DRV_SR register */
	write_csr(DRV1_COMR, PWM_VALUE_DOWNLOAD);


	write_csr(IP8, FOC_INT_PRI);		// DRV1 interrupt (Interrupt No. 8) priority level is 5, priority is lower than overcurrent protection

	clr_csr(DRV1_IER, DCIP);			// 0-->Interrupt generated every 1 count cycle  1-->Interrupt generated every 2 count cycles

	set_csr(DRV1_FCR1, CT_SEL);         // FOC calculation timing 0: Calculate FOC at the next overflow point after current sampling 1: Calculate FOC immediately after current sampling

	set_csr(DRV1_CR, DRVEN);			// Counter enable		0-->Disable		1-->Enable
//	set_csr(DRV1_CR, DRVOE);			// Driver output enable	0-->Disable		1-->Enable

	clr_csr(DRV1_FCR0, NCALEN);			// FOC calculation enable, equivalent to turning on FOC


	// Current sampling------------------------------------------------------------
#if DOUBLESAMP_ENABLE_SWITCH
	set_csr(DRV1_FCR0, NCSAMMD3);	// Dual-resistor double sampling (1001), meanwhile CT_SEL must be set to 1
	clr_csr(DRV1_FCR0, NCSAMMD2);
	clr_csr(DRV1_FCR0, NCSAMMD1);
	set_csr(DRV1_FCR0, NCSAMMD0);
	NFOC_CSAM = 0x09; // Initial value of sampling mode
#else
	clr_csr(DRV1_FCR0, NCSAMMD3);	// Dual-resistor single sampling (0001)
	clr_csr(DRV1_FCR0, NCSAMMD2);
	clr_csr(DRV1_FCR0, NCSAMMD1);
	set_csr(DRV1_FCR0, NCSAMMD0);
	NFOC_CSAM = 0x01; // Initial value of sampling mode
#endif
	set_csr(DRV1_FCR4, CUR_SAM_EN);		// Forced current sampling enable, regardless of whether cal_en is enabled
	
#if (HW_ADC_SYNC == ADCSAM_SYNC)
	set_csr(ME_CR, TRIG_MD);			// Enable dual ADC synchronized sampling
#endif

	// M/MT method speed measurement------------------------------------------------------------
	clr_csr(DRV1_FCR4, MMT_SEL);			// M/MT method selection  0: M method  1: MT method

	clr_csr(DRV1_FCR4, MMT_CAL_CYCLE1);		// M/MT method calculation cycle selection  00: Every 1 carrier interrupt 01: Every 2 carrier interrupts
	clr_csr(DRV1_FCR4, MMT_CAL_CYCLE0);		// M/MT method calculation cycle selection  10: Every 4 carrier interrupts 11: Every 8 carrier interrupts

	NFOC_MBASE = usSRegHoldBuf[QEPSPEEDCOE];
	NFOC_MSHFT = usSRegHoldBuf[SPEEDCOERANK];
	NFOC_MARR = VELCTRL_TS;

	// Automatic speed calculation------------------------------------------------------------
	set_csr(DRV1_FCR4, SPEED_AUTO);		// Automatic speed calculation enable cal_en=0: only calculate MMT and average filtering; cal_en=1: current loop only calculates MMT and average filtering, outer loop calculates PDFF

	clr_csr(DRV1_FCR4, UDQ_LPF_EN);     // UDQ low pass filter enable	0: Disable  1: Enable



	// Protection------------------------------------------------------------
	write_csr(DRV1_PER, 0x0000);

#if PROT_HARDWARE_ENABLED
	write_csr(IP6, DRVPIF_INT_PRI);		// DRV1 protection interrupt (Interrupt No. 6) priority level is 5
	set_csr(DRV1_PER, PER_MD);		// 0-Sensitive error reporting; 1-Reduced sensitivity
#endif

#if PROT_OUVP_HARDWARE_ENABLED
	/************** Overvoltage/Undervoltage detection parameter settings ************/
	clr_csr(DRV1_PER, OUVP_AUTO1);       // 00: Disable  01: Calculate once per carrier cycle 10: Calculate once per SYSTICK 11: Prohibit
	clr_csr(DRV1_PER, OUVP_AUTO0);
	clr_csr(DRV1_PSR, OVPIF);        // Clear interrupt flag
	clr_csr(DRV1_PSR, UVPIF);        // Clear interrupt flag

    NFOC_OVP = 0x7FFF;    // Overvoltage protection threshold
    NFOC_UVP = 0x00;    // Undervoltage protection threshold
    NFOC_OVPARR = 0xFF; // Overvoltage protection count target value
    NFOC_UVPARR = 0xFF; // Undervoltage protection count target value

#endif // #if PROT_OUVP_HARDWARE_ENABLED

#if PROT_SOCP_HARDWARE_ENABLED
	/************** Software overcurrent detection parameter settings ************/
	NFOC_SOCP = 0x7FFF; 
	NFOC_SOCPARR = 0xFF;// Overcurrent protection count target value
	clr_csr(DRV1_PSR, SOCPIF);
	set_csr(DRV1_PER, SOCP_AUTO); // Automatically enable software overcurrent calculation once every carrier cycle
#endif // #if PROT_SOCP_HARDWARE_ENABLED
	
#if PROT_OVEL_HARDWARE_ENABLED
	/************** Speed deviation detection parameter settings ************/
	NFOC_OVEL = 0x7FFF; // Speed deviation protection threshold
	NFOC_OVELARR = 0xFF; // Speed deviation target value
	NFOC_OVELCNT = 0;
	clr_csr(DRV1_PSR, OVELIF);
	set_csr(DRV1_PER, OVEL_AUTO); // Automatically enable speed deviation calculation once every outer loop cycle
#endif // #if PROT_SOCP_HARDWARE_ENABLED
	
#if PROT_OSPD_HARDWARE_ENABLED
	/************** Overspeed detection parameter settings ************/
	NFOC_OSPD = 0x7FFF; // Overspeed protection threshold
	NFOC_OSPDARR = 0xFF; // Overspeed target value
	NFOC_OSPDCNT = 0;
	clr_csr(DRV1_PSR, OSPDIF);
	set_csr(DRV1_PER, OSPD_AUTO); // Automatically enable overspeed calculation once every carrier cycle
#endif // #if PROT_OSPD_HARDWARE_ENABLED
	
#if PROT_STALL_HARDWARE_ENABLED
	/************** Stall detection parameter settings ************/
	NFOC_LKSTH = 0x7FFF; // Stall protection speed threshold
	NFOC_LKITH = 0x7FFF; // Stall protection current threshold
	NFOC_LKARR = 0xFFFF; // Stall protection target value
	NFOC_LKCNT = 0;
	clr_csr(DRV1_PSR, LOCKIF);
	set_csr(DRV1_PER, LOCK_MD); // Enable servo stall protection
	set_csr(DRV1_PER, LOCK_AUTO); // Automatically enable stall protection calculation once every carrier cycle
#endif // #if PROT_STALL_HARDWARE_ENABLED
	
#if PROT_PLOSS_HARDWARE_ENABLED
	/************** Phase loss protection parameter settings ************/
	NFOC_PLTTH = 0x7FFF; // Phase loss protection angle change threshold
	NFOC_PLRTH = 0x7FFF; // Phase loss protection current command threshold
	NFOC_PLITH = 0x7FFF; // Phase loss protection phase current threshold

	clr_csr(DRV1_PSR, PLIF);
	set_csr(DRV1_PER, PL_MD); // Enable phase loss protection
	set_csr(DRV1_PER, PL_AUTO); // Automatically enable phase loss protection calculation once every carrier cycle
#endif // #if PROT_PLOSS_HARDWARE_ENABLED
	
#if PROT_CARINTOT_HARDWARE_ENABLED
	/************** Carrier interrupt timeout protection parameter settings ************/
	clr_csr(DRV1_PSR, ODCIF_IF);
	set_csr(DRV1_PER, ODCIF_EN); // Enable carrier interrupt timeout protection
#endif // #if PROT_CARINTOT_HARDWARE_ENABLED


#if FUNC_DUTYUPDATENOW_ENABLED
	/* Immediate update of duty cycle */
	set_csr(DRV1_CR, IMM_UPDATE);

#endif

}