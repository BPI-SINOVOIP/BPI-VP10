/*
 * Copyright (c) 2024-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : ProbePcom.c
 * Author        : Summer
 * Date          : 2024-08-21
 * Description   : Probe and position compare output
 *
 * Record        :
 * V1.0, 2024-08-21, Summer: Created file
 */


/* Includes -------------------------------------------------------------------------------------*/
#include <Myproject.h>
#include "ProbePcom.h"

#if FUNC_PROBE_ENABLED || FUNC_PCOM_ENABLED

VelEstTypeDef mcVelEst = {0};
ProbeTypeDef mcProbe = { 0 };
PcomTypeDef mcPcom = { 0 };


#if FUNC_PROBE_ENABLED
/*---------------------------------------------------------------------------
 * Name		:	Probe_Init
 * Input	:	No
 * Output	:	No
 * Description:	Probe initialize. TIM2 Enable probe function
 *---------------------------------------------------------------------------*/
void Probe_Init(void)
{
	memset(&mcVelEst, 0, sizeof(VelEstTypeDef));
	memset(&mcProbe, 0, sizeof(ProbeTypeDef));
	
	/****** probeStrobe ******/
	set_csr(CMP_CR5, STRCT);	// Probe function transfer bit: 0-PA14, PA15; 1-PC6, PC7
	
#if FUNC_PROBE1_ENABLED
	clr_csr(STPC0_CR, STRO_IE);		// Probe 0 interrupt enable
	clr_csr(STPC0_SR, STRO_IF);		// Probe 0 interrupt flag
	clr_csr(STPC0_CR, STRO_SEL);	// Probe 0 trigger edge selection, 0-->rising edge, 1-->falling edge
	write_csr(STRO0_ARR, 0);		// Probe 0 latch value
	clr_csr(STPC0_CR, STRO_EN);		// Probe 0 enable
#endif // #if FUNC_PROBE1_ENABLED

#if FUNC_PROBE2_ENABLED
	clr_csr(STPC1_CR, STRO_IE);		// Probe 1 interrupt enable
	clr_csr(STPC1_SR, STRO_IF);		// Probe 1 interrupt flag
	clr_csr(STPC1_CR, STRO_SEL);	// Probe 1 trigger edge selection, 0-->rising edge, 1-->falling edge
	write_csr(STRO1_ARR, 0);		// Probe 1 latch value
	clr_csr(STPC1_CR, STRO_EN);		// Probe 1 enable
#endif // #if FUNC_PROBE2_ENABLED
}


/*---------------------------------------------------------------------------
 * Name		:	Probe_Update
 * Input	:	No
 * Output	:	No
 * Description:	Probe parameter update new, in main call
 *---------------------------------------------------------------------------*/
void Probe_Update(void)
{
	if (mcProbe.ProbeConfig != usSRegHoldBuf[PROBECONFIG])
	{
		uint16 probeStatusTemp = usSRegInBuf[PROBESTATUS];
		
#if FUNC_PROBE1_ENABLED
		if ((mcProbe.ProbeConfig & 0xFF) != (usSRegHoldBuf[PROBECONFIG] & 0xFF))
		{
			mcProbe.Probe1En = 0;
			mcProbe.Probe1TrigSigZ = ReadBit(usSRegHoldBuf[PROBECONFIG], PROBE1SIGNAL);
			mcProbe.Probe1TrigCon = ReadBit(usSRegHoldBuf[PROBECONFIG], PROBE1MODE);

			// Probe 1 enable
			uint8 probe1EnTemp = ReadBit(usSRegHoldBuf[PROBECONFIG], PROBE1EN);
			if (probe1EnTemp)
			{
				SetBit(probeStatusTemp, PROBE1ENSTA);
				mcProbe.Probe1TrigTimes = 0;
				if (!mcProbe.Probe1TrigSigZ) // DI signal
				{
					clr_csr(STPC0_SR, STRO_IF);
					set_csr(STPC0_CR, STRO_EN);
				}
				else
				{
					clr_csr(TIM2_SR, T2IR);
					clr_csr(STPC0_CR, STRO_EN);
				}	
			}
			else
			{
				SetReg(probeStatusTemp, PROBE1ENSTA | PROBE1RISESTA | PROBE1FALLSTA | PROBE1TRIGTIMES, 0);
				clr_csr(STPC0_CR, STRO_EN);
			}

			if (mcProbe.Probe1TrigCon || !probe1EnTemp) // Continuous trigger
			{
				mcProbe.Probe1OffFlag = 0;
			}

			// Probe 1 trigger edge selection
			if (ReadBit(usSRegHoldBuf[PROBECONFIG], PROBE1RISEEN))
			{
				if (!mcProbe.Probe1TrigSigZ) // DI signal
					clr_csr(STPC0_CR, STRO_SEL);	// Probe trigger edge selection, 0-->rising edge, 1-->falling edge
				else
					clr_csr(TIM2_CR1, T2Z_EDGE_SEL); // QEP input mode, Z signal valid edge: 0-->rising edge, 1-->falling edge
			}
			else if (ReadBit(usSRegHoldBuf[PROBECONFIG], PROBE1FALLEN))
			{
				if (!mcProbe.Probe1TrigSigZ) // DI signal
					set_csr(STPC0_CR, STRO_SEL);
				else
					set_csr(TIM2_CR1, T2Z_EDGE_SEL);
			}
			else
			{
				if (!mcProbe.Probe1TrigSigZ)
					clr_csr(STPC0_CR, STRO_SEL);
				else
					clr_csr(TIM2_CR1, T2Z_EDGE_SEL);
			}

			clr_csr(STPC0_SR, STRO_IF);
			mcProbe.Probe1En = probe1EnTemp;
		}
#endif // #if FUNC_PROBE1_ENABLED
		
#if FUNC_PROBE2_ENABLED
		if ((mcProbe.ProbeConfig & 0xFF00) != (usSRegHoldBuf[PROBECONFIG] & 0xFF00))
		{
			mcProbe.Probe2En = 0;
			mcProbe.Probe2TrigSigZ = ReadBit(usSRegHoldBuf[PROBECONFIG], PROBE2SIGNAL);
			mcProbe.Probe2TrigCon = ReadBit(usSRegHoldBuf[PROBECONFIG], PROBE2MODE);

			// Probe 2 enable
			uint8 probe2EnTemp = ReadBit(usSRegHoldBuf[PROBECONFIG], PROBE2EN);
			if (probe2EnTemp)
			{
				SetBit(probeStatusTemp, PROBE2ENSTA);
				mcProbe.Probe2TrigTimes = 0;
				if (!mcProbe.Probe2TrigSigZ) // DI signal
				{
					clr_csr(STPC1_SR, STRO_IF);
					set_csr(STPC1_CR, STRO_EN);
				}
				else
				{
					clr_csr(TIM2_SR, T2IR);
					clr_csr(STPC1_CR, STRO_EN);
				}		
			}
			else
			{
				SetReg(probeStatusTemp, PROBE2ENSTA | PROBE2RISESTA | PROBE2FALLSTA | PROBE2TRIGTIMES, 0);
				clr_csr(STPC1_CR, STRO_EN);
			}

			if (mcProbe.Probe2TrigCon || !probe2EnTemp) // Continuous trigger
			{
				mcProbe.Probe2OffFlag = 0;
			}

			// Probe 2 trigger edge selection
			if (ReadBit(usSRegHoldBuf[PROBECONFIG], PROBE2RISEEN))
			{
				if (!mcProbe.Probe2TrigSigZ) // DI signal
					clr_csr(STPC1_CR, STRO_SEL);	// Probe trigger edge selection, 0-->rising edge, 1-->falling edge
				else
					clr_csr(TIM2_CR1, T2Z_EDGE_SEL); // QEP input mode, Z signal valid edge: 0-->rising edge, 1-->falling edge
			}
			else if (ReadBit(usSRegHoldBuf[PROBECONFIG], PROBE2FALLEN))
			{
				if (!mcProbe.Probe2TrigSigZ) // DI signal
					set_csr(STPC1_CR, STRO_SEL);
				else
					set_csr(TIM2_CR1, T2Z_EDGE_SEL);
			}
			else
			{
				if (!mcProbe.Probe2TrigSigZ)
					clr_csr(STPC1_CR, STRO_SEL);
				else
					clr_csr(TIM2_CR1, T2Z_EDGE_SEL);
			}

			clr_csr(STPC1_SR, STRO_IF);
			mcProbe.Probe2En = probe2EnTemp;
		}
#endif // #if FUNC_PROBE2_ENABLED
		
		
		mcProbe.ProbeConfig = usSRegHoldBuf[PROBECONFIG];
		usSRegInBuf[PROBESTATUS] = probeStatusTemp;
	}	
}
#endif // #if FUNC_PROBE_ENABLED


#if FUNC_PCOM_ENABLED
/*---------------------------------------------------------------------------
 * Name		:	PCOM_Init
 * Input	:	No
 * Output	:	No
 * Description:	Position compare output initialization
 *---------------------------------------------------------------------------*/
void PCOM_Init(void)
{
	memset(&mcVelEst, 0, sizeof(VelEstTypeDef));
	memset(&mcPcom, 0, sizeof(PcomTypeDef));
	mcPcom.Pcom1Arr = 0xFFFFFFFF;
//	mcPcom.Pcom2Arr = 0xFFFFFFFF;

	/****** Position compare PCOM ******/
	// TIM2 enable position compare output function
	clr_csr(STPC0_CR, PCOM_IE);		// Position compare interrupt enable
	clr_csr(STPC0_SR, PCOM_IF);		// Position compare interrupt flag
	set_csr(STPC0_CR, PCOM_SEL1);	// Position compare trigger edge selection, 00-->trigger only when T2DIR=0, 01-->trigger only when T2DIR=1
	set_csr(STPC0_CR, PCOM_SEL0);	// Position compare trigger edge selection, 1x-->trigger regardless of T2DIR state
	write_csr(PCOM0_ARR, 1000);		// Position compare comparison value
	Timer4_Init();
	clr_csr(STPC0_CR, PCOM_EN);		// Position compare enable

	//	clr_csr(STPC1_CR, PCOM_IE);		// Position compare interrupt enable
	//	clr_csr(STPC1_SR, PCOM_IF);		// Position compare interrupt flag
	//	set_csr(STPC1_CR, PCOM_SEL1);	// Position compare trigger edge selection, 00-->trigger only when T2DIR=0, 01-->trigger only when T2DIR=1
	//	set_csr(STPC1_CR, PCOM_SEL0);	// Position compare trigger edge selection, 1x-->trigger regardless of T2DIR state
	//	write_csr(PCOM1_ARR, 1000);		// Position compare comparison value
	//  Timer7_Init();
	//	clr_csr(STPC1_CR, PCOM_EN);		// Position compare enable

}


/*---------------------------------------------------------------------------
 * Name		:	PCOM_Update
 * Input	:	No
 * Output	:	No
 * Description:	PCOM parameter update new, in main call
 *---------------------------------------------------------------------------*/
void PCOM_Update(void)
{
	uint16 pcomDir, encABS;
	uint8 pcomTableLen;
	uint8 pcom1EnTemp;

	encABS = ReadBit(usSRegHoldBuf[DRIVEMODE], MODE_ENCABS);
	if (mcPcom.EncABS != encABS)
	{
		mcPcom.EncABS = encABS;
		mcPcom.Pcom1Flag = 0;
		mcPcom.Pcom1Arr = 0xFFFFFFFF;
		if (encABS)
		{
			set_csr(STPC0_CR, PCOM_SEL1);
			set_csr(STPC0_CR, PCOM_SEL0);
		}
	}
	
	if (mcPcom.Pcom1Ctrl != usSRegHoldBuf[PCOM1CNTRL])
	{
		mcPcom.Pcom1Ctrl = usSRegHoldBuf[PCOM1CNTRL];
		
		mcPcom.Pcom1Mode = ReadBit(mcPcom.Pcom1Ctrl, PCOM1MODE);

		// PCOM1 enable
		pcom1EnTemp = ReadBit(mcPcom.Pcom1Ctrl, PCOM1EN);
		if (pcom1EnTemp)
		{
			clr_csr(STPC0_SR, PCOM_IF);
			set_csr(STPC0_CR, PCOM_EN);
		}
		else
		{
			clr_csr(STPC0_CR, PCOM_EN);
			mcPcom.Pcom1Flag = 0;
			mcPcom.Pcom1Arr = 0xFFFFFFFF;
		}	

		// PCOM1 motion direction
		pcomDir = GetReg(mcPcom.Pcom1Ctrl, PCOM1DIR);
		pcomDir = pcomDir >> PCOMDIR1SHIFT;
		mcPcom.Pcom1Dir = pcomDir + 1;
		
		if (encABS || (mcPcom.Pcom1Dir != PCOMDIRNEG && mcPcom.Pcom1Dir != PCOMDIRPOS))
		{
			set_csr(STPC0_CR, PCOM_SEL1);
			set_csr(STPC0_CR, PCOM_SEL0);
		}
		else if (mcPcom.Pcom1Dir == PCOMDIRNEG)
		{
			clr_csr(STPC0_CR, PCOM_SEL1);	// Position compare trigger edge selection, 00-->trigger only when T2DIR=0, 01-->trigger only when T2DIR=1
			set_csr(STPC0_CR, PCOM_SEL0);	// Position compare trigger edge selection, 1x-->trigger regardless of T2DIR state
		}
		else if (mcPcom.Pcom1Dir == PCOMDIRPOS)
		{
			clr_csr(STPC0_CR, PCOM_SEL1);
			clr_csr(STPC0_CR, PCOM_SEL0);
		}
	}
	
	// PCOM1 pulse width
	if (mcPcom.Pcom1Width != usSRegHoldBuf[PCOM1WIDTH])
	{
		mcPcom.Pcom1Width = usSRegHoldBuf[PCOM1WIDTH];
		write_csr(TIM4_DR, usSRegHoldBuf[PCOM1WIDTH]);
	}
	
	if (!mcPcom.Pcom1Mode) // Fixed interval
	{
		mcPcom.pPcom1Start = (int32*)&usSRegHoldBuf[PCOM1START_L];
		mcPcom.pPcom1End = (int32*)&usSRegHoldBuf[PCOM1END_L];
		mcPcom.Pcom1Offset = ((int32)usSRegHoldBuf[PCOM1OFFSET_H] << 16) + usSRegHoldBuf[PCOM1OFFSET_L];
	}
	else // Table
	{
		pcomTableLen = usSRegHoldBuf[PCOM1TABLELEN];
		if (pcomTableLen > 4)
			pcomTableLen = 4;
		mcPcom.pPcom1Start = (int32*)&usSRegHoldBuf[PCOM1POS0_L];
		mcPcom.pPcom1End = (int32*)&usSRegHoldBuf[PCOM1POS0_L] + pcomTableLen - 1;
	}
	mcPcom.Pcom1En = pcom1EnTemp;
}
#endif // #if FUNC_PCOM_ENABLED


/*---------------------------------------------------------------------------
 * Name		:	ProbePCOM_realize
 * Input	:	ActPos: Current Position;
 *				EncUpdate: 1 - Position updated; 0 - Position not updated
 * Output	:	No
 * Description:	Probe and PCOM realize, called in carrier interrupt
 *---------------------------------------------------------------------------*/
void ProbePCOM_realize(int ActPos, uint8 EncUpdate)
{
	uint16 timeStamp, encABS;
	int32 posMarginAvg, probePos = 0; 
	int32 pcomV, pcomPos, pcomPosNext;
	int32 *pPcomPosNext;

	
	encABS = ReadBit(usSRegHoldBuf[DRIVEMODE], MODE_ENCABS);
	if ((!encABS || EncUpdate) && (mcProbe.Probe1En || mcProbe.Probe2En || mcPcom.Pcom1En))
	{
		if (encABS)
		{
			timeStamp = read_csr(TIM2_QEP_TNUM);
		}
		mcVelEst.PosMarginPre = mcVelEst.PosMargin;
		mcVelEst.PosMargin = ActPos - mcVelEst.ActPos;
		mcVelEst.ActPos = ActPos;
		posMarginAvg = (mcVelEst.PosMargin + mcVelEst.PosMarginPre) >> 1; // Velocity prediction
			

#if FUNC_PROBE1_ENABLED // Probe 1
		if (mcProbe.Probe1En && !mcProbe.Probe1OffFlag && ((!mcProbe.Probe1TrigSigZ && readbit_csr(STPC0_SR, STRO_IF)) || 
			(mcProbe.Probe1TrigSigZ && readbit_csr(TIM2_SR, T2IR))))
		{
			if (!mcProbe.Probe1TrigSigZ)
			{
				probePos = read_csr(STRO0_ARR);
				clr_csr(STPC0_SR, STRO_IF);
			}	
			else
			{
				probePos = read_csr(TIM2_QEP_ARR);
				clr_csr(TIM2_SR, T2IR);
			}
			
			if (encABS)
			{
				probePos = ActPos + (int32)(int16)((uint16)probePos - timeStamp) * posMarginAvg / ENCABS_TS;
			}
				
			usSRegInBuf[PROBE1DATA_H] = probePos >> 16;
			usSRegInBuf[PROBE1DATA_L] = probePos;
			
			if (!mcProbe.Probe1TrigCon) // Single trigger
			{
				clr_csr(STPC0_CR, STRO_EN);
				mcProbe.Probe1OffFlag = 1;
			}
			
			// Probe 1 trigger edge selection
			if (ReadBit(mcProbe.ProbeConfig, PROBE1RISEEN))
			{
				SetBit(usSRegInBuf[PROBESTATUS], PROBE1RISESTA);
			}
			else if (ReadBit(mcProbe.ProbeConfig, PROBE1FALLEN))
			{
				SetBit(usSRegInBuf[PROBESTATUS], PROBE1FALLSTA);
			}
			
			if (mcProbe.Probe1TrigTimes < 3)
			{
				mcProbe.Probe1TrigTimes++;
				SetReg(usSRegInBuf[PROBESTATUS], PROBE1TRIGTIMES, mcProbe.Probe1TrigTimes << PROBE1TRIGTIMESSHIFT);
			}	
		}
#endif // #if FUNC_PROBE1_ENABLED
		
#if FUNC_PROBE2_ENABLED // Probe 2
		if (mcProbe.Probe2En && !mcProbe.Probe2OffFlag && ((!mcProbe.Probe2TrigSigZ && readbit_csr(STPC1_SR, STRO_IF)) ||
			(mcProbe.Probe2TrigSigZ && readbit_csr(TIM2_SR, T2IR))))
		{
			if (!mcProbe.Probe2TrigSigZ)
			{
				probePos = read_csr(STRO1_ARR);
				clr_csr(STPC1_SR, STRO_IF);
			}
			else
			{
				probePos = read_csr(TIM2_QEP_ARR);
				clr_csr(TIM2_SR, T2IR);
			}
				
			if (encABS)
			{
				probePos = ActPos + (int32)(int16)((uint16)probePos - timeStamp) * posMarginAvg / ENCABS_TS;
			}

			usSRegInBuf[PROBE2DATA_H] = probePos >> 16;
			usSRegInBuf[PROBE2DATA_L] = probePos;

			if (!mcProbe.Probe2TrigCon) // Single trigger
			{
				clr_csr(STPC1_CR, STRO_EN);
				mcProbe.Probe2OffFlag = 1;
			}

			// Probe 2 trigger edge selection
			if (ReadBit(mcProbe.ProbeConfig, PROBE2RISEEN))
			{
				SetBit(usSRegInBuf[PROBESTATUS], PROBE2RISESTA);
			}
			else if (ReadBit(mcProbe.ProbeConfig, PROBE2FALLEN))
			{
				SetBit(usSRegInBuf[PROBESTATUS], PROBE2FALLSTA);
			}

			if (mcProbe.Probe2TrigTimes < 3)
			{
				mcProbe.Probe2TrigTimes++;
				SetReg(usSRegInBuf[PROBESTATUS], PROBE2TRIGTIMES, mcProbe.Probe2TrigTimes << PROBE2TRIGTIMESSHIFT);
			}
		}
#endif // #if FUNC_PROBE2_ENABLED

#if FUNC_PCOM_ENABLED
		// PCOM1
		if (mcPcom.Pcom1En)
		{
			if (!mcPcom.Pcom1Flag)
			{
				pcomV = ActPos + posMarginAvg;
				if (pcomV <= *mcPcom.pPcom1Start)
					pcomPos = *mcPcom.pPcom1Start;
				else if(pcomV >= *mcPcom.pPcom1End)
					pcomPos = *mcPcom.pPcom1End;
				else
				{
					pcomPosNext = *mcPcom.pPcom1Start;
					pcomPos = pcomPosNext;
					pPcomPosNext = mcPcom.pPcom1Start;
					while (pcomPosNext < *mcPcom.pPcom1End)
					{
						pcomPos = pcomPosNext;
						if (!mcPcom.Pcom1Mode) // Fixed interval
						{
							pcomPosNext += mcPcom.Pcom1Offset;
						}
						else // Table lookup
						{
							pcomPosNext = *(pPcomPosNext++);
						}
						if (pcomV >= pcomPos && pcomV <= pcomPosNext)
						{
							if (pcomV - pcomPos >= pcomPosNext - pcomV)
								pcomPos = pcomPosNext;
							break;
						}
					}
				}

				if (!encABS)
				{ 
					mcPcom.Pcom1Arr = pcomPos;
				}
				else
				{
					pcomV = pcomPos - ActPos;
					if (((mcPcom.Pcom1Dir & 0x02) && pcomV > 0 && pcomV >= posMarginAvg && pcomV <= posMarginAvg * 3) || \
						((mcPcom.Pcom1Dir & 0x01) && pcomV < 0 && pcomV <= posMarginAvg && pcomV >= posMarginAvg * 3))
					{
						mcPcom.Pcom1Flag = 1;
						mcPcom.Pcom1Arr = timeStamp + pcomV * ENCABS_TS / posMarginAvg - PCOM_DELAY;
						mcPcom.Pcom1Arr &= 0xFFFF;
					}
				}			
			}
			else
			{
				if (readbit_csr(STPC0_SR, PCOM_IF) || (timeStamp > mcPcom.Pcom1Arr && timeStamp - mcPcom.Pcom1Arr < 32768) ||
					(timeStamp < mcPcom.Pcom1Arr && mcPcom.Pcom1Arr - timeStamp >= 32768))
				{
					mcPcom.Pcom1Flag = 0;
					mcPcom.Pcom1Arr = 0xFFFFFFFF;
					clr_csr(STPC0_SR, PCOM_IF);
				}
			}
			write_csr(PCOM0_ARR, mcPcom.Pcom1Arr);		// Position compare 1 comparison value
		}
#endif // #if FUNC_PCOM_ENABLED
		
	}	
}

#endif // #if FUNC_PROBE_ENABLED || FUNC_PCOM_ENABLED