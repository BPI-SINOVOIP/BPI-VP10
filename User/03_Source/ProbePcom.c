/*
 * Copyright (c) 2024-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : ProbePcom.c
 * Author        : Summer
 * Date          : 2024-08-21
 * Description   : 探针和位置比较输出
 *
 * Record        :
 * V1.0, 2024-08-21, Summer: Created file
 */


/* Includes -------------------------------------------------------------------------------------*/
#include <Myproject.h>
#include "ProbePcom.h"

#if FUNC_PROBE_ENABLED || FUNC_PCOM_ENABLED

#if FUNC_PROBE_ENABLED || FUNC_PCOM_ENABLED
VelEstTypeDef mcVelEst = {0};
ProbeTypeDef mcProbe = { 0 };
PcomTypeDef mcPcom = { 0 };
#endif

#if FUNC_PROBE_ENABLED
/*---------------------------------------------------------------------------*/
/* Name		:	void Probe_Init(void)
/* Input	:	NO
/* Output	:	NO
/* Description:	Probe initialize. TIM2 使能探针功能
/*---------------------------------------------------------------------------*/
void Probe_Init(void)
{
	memset(&mcVelEst, 0, sizeof(VelEstTypeDef));
	memset(&mcProbe, 0, sizeof(ProbeTypeDef));
	
	/****** 探针Strobe ******/
	set_csr(CMP_CR5, STRCT);	// 探针功能转移位: 0-PA14、PA15; 1-PC6、PC7
	
#if FUNC_PROBE1_ENABLED
	clr_csr(STPC0_CR, STRO_IE);		// 探针0中断使能
	clr_csr(STPC0_SR, STRO_IF);		// 探针0中断标志位
	clr_csr(STPC0_CR, STRO_SEL);	// 探针0触发边沿选择，0-->上升沿，1-->下降沿
	write_csr(STRO0_ARR, 0);		// 探针0锁存值
	clr_csr(STPC0_CR, STRO_EN);		// 探针0使能
#endif // #if FUNC_PROBE1_ENABLED

#if FUNC_PROBE2_ENABLED
	clr_csr(STPC1_CR, STRO_IE);		// 探针1中断使能
	clr_csr(STPC1_SR, STRO_IF);		// 探针1中断标志位
	clr_csr(STPC1_CR, STRO_SEL);	// 探针1触发边沿选择，0-->上升沿，1-->下降沿
	write_csr(STRO1_ARR, 0);		// 探针1锁存值
	clr_csr(STPC1_CR, STRO_EN);		// 探针1使能
#endif // #if FUNC_PROBE2_ENABLED
}


/*---------------------------------------------------------------------------*/
/* Name		:	void Probe_Update(void)
/* Input	:	NO
/* Output	:	NO
/* Description:	Probe update，参数更新，在main调用
/*---------------------------------------------------------------------------*/
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

			// 探针1使能
			uint8 probe1EnTemp = ReadBit(usSRegHoldBuf[PROBECONFIG], PROBE1EN);
			if (probe1EnTemp)
			{
				SetBit(probeStatusTemp, PROBE1ENSTA);
				mcProbe.Probe1TrigTimes = 0;
				if (!mcProbe.Probe1TrigSigZ) // DI信号
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

			if (mcProbe.Probe1TrigCon || !probe1EnTemp) // 连续触发
			{
				mcProbe.Probe1OffFlag = 0;
			}

			// 探针1触发边沿选择
			if (ReadBit(usSRegHoldBuf[PROBECONFIG], PROBE1RISEEN))
			{
				if (!mcProbe.Probe1TrigSigZ) // DI信号
					clr_csr(STPC0_CR, STRO_SEL);	// 探针触发边沿选择，0-->上升沿，1-->下降沿
				else
					clr_csr(TIM2_CR1, T2Z_EDGE_SEL); // QEP输入模式，Z 信号有效沿：0-->上升沿，1-->下降沿
			}
			else if (ReadBit(usSRegHoldBuf[PROBECONFIG], PROBE1FALLEN))
			{
				if (!mcProbe.Probe1TrigSigZ) // DI信号
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

			// 探针2使能
			uint8 probe2EnTemp = ReadBit(usSRegHoldBuf[PROBECONFIG], PROBE2EN);
			if (probe2EnTemp)
			{
				SetBit(probeStatusTemp, PROBE2ENSTA);
				mcProbe.Probe2TrigTimes = 0;
				if (!mcProbe.Probe2TrigSigZ) // DI信号
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

			if (mcProbe.Probe2TrigCon || !probe2EnTemp) // 连续触发
			{
				mcProbe.Probe2OffFlag = 0;
			}

			// 探针2触发边沿选择
			if (ReadBit(usSRegHoldBuf[PROBECONFIG], PROBE2RISEEN))
			{
				if (!mcProbe.Probe2TrigSigZ) // DI信号
					clr_csr(STPC1_CR, STRO_SEL);	// 探针触发边沿选择，0-->上升沿，1-->下降沿
				else
					clr_csr(TIM2_CR1, T2Z_EDGE_SEL); // QEP输入模式，Z 信号有效沿：0-->上升沿，1-->下降沿
			}
			else if (ReadBit(usSRegHoldBuf[PROBECONFIG], PROBE2FALLEN))
			{
				if (!mcProbe.Probe2TrigSigZ) // DI信号
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
/*---------------------------------------------------------------------------*/
/* Name		:	void PCOM_Init(void)
/* Input	:	NO
/* Output	:	NO
/* Description:	PCOM initialize.
/*---------------------------------------------------------------------------*/
void PCOM_Init(void)
{
	memset(&mcVelEst, 0, sizeof(VelEstTypeDef));
	memset(&mcPcom, 0, sizeof(PcomTypeDef));
	mcPcom.Pcom1Arr = 0xFFFFFFFF;
//	mcPcom.Pcom2Arr = 0xFFFFFFFF;

	/****** 位置比较PCOM ******/
	// TIM2 使能位置比较输出功能
	clr_csr(STPC0_CR, PCOM_IE);		// 位置比较中断使能
	clr_csr(STPC0_SR, PCOM_IF);		// 位置比较中断标志位
	set_csr(STPC0_CR, PCOM_SEL1);	// 位置比较触发边沿选择，00-->T2DIR=0时才触发，01-->T2DIR=1时才触发
	set_csr(STPC0_CR, PCOM_SEL0);	// 位置比较触发边沿选择，1x-->不论T2DIR状态都触发
	write_csr(PCOM0_ARR, 1000);		// 位置比较的比较值
	Timer4_Init();
	clr_csr(STPC0_CR, PCOM_EN);		// 位置比较使能

	//	clr_csr(STPC1_CR, PCOM_IE);		// 位置比较中断使能
	//	clr_csr(STPC1_SR, PCOM_IF);		// 位置比较中断标志位
	//	set_csr(STPC1_CR, PCOM_SEL1);	// 位置比较触发边沿选择，00-->T2DIR=0时才触发，01-->T2DIR=1时才触发
	//	set_csr(STPC1_CR, PCOM_SEL0);	// 位置比较触发边沿选择，1x-->不论T2DIR状态都触发
	//	write_csr(PCOM1_ARR, 1000);		// 位置比较的比较值
	//  Timer7_Init();
	//	clr_csr(STPC1_CR, PCOM_EN);		// 位置比较使能

}


/*---------------------------------------------------------------------------*/
/* Name		:	void PCOM_Update(void)
/* Input	:	NO
/* Output	:	NO
/* Description:	PCOM update，参数更新，在main调用
/*---------------------------------------------------------------------------*/
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

		// PCOM1使能
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

		// PCOM1运动方向
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
			clr_csr(STPC0_CR, PCOM_SEL1);	// 位置比较触发边沿选择，00-->T2DIR=0时才触发，01-->T2DIR=1时才触发
			set_csr(STPC0_CR, PCOM_SEL0);	// 位置比较触发边沿选择，1x-->不论T2DIR状态都触发
		}
		else if (mcPcom.Pcom1Dir == PCOMDIRPOS)
		{
			clr_csr(STPC0_CR, PCOM_SEL1);
			clr_csr(STPC0_CR, PCOM_SEL0);
		}
	}
	
	// PCOM1脉冲宽度
	if (mcPcom.Pcom1Width != usSRegHoldBuf[PCOM1WIDTH])
	{
		mcPcom.Pcom1Width = usSRegHoldBuf[PCOM1WIDTH];
		write_csr(TIM4_DR, usSRegHoldBuf[PCOM1WIDTH]);
	}
	
	if (!mcPcom.Pcom1Mode) // 固定间隔
	{
		mcPcom.pPcom1Start = (int32*)&usSRegHoldBuf[PCOM1START_L];
		mcPcom.pPcom1End = (int32*)&usSRegHoldBuf[PCOM1END_L];
		mcPcom.Pcom1Offset = ((int32)usSRegHoldBuf[PCOM1OFFSET_H] << 16) + usSRegHoldBuf[PCOM1OFFSET_L];
	}
	else // 表格
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


/*---------------------------------------------------------------------------*/
/* Name		:	void ProbePCOM_realize()
/* Input	:	ActPos: Current Position;
 *				EncUpdate: 1 - Position updated; 0 - Position not updated
/* Output	:	NO
/* Description:	Probe and PCOM realize，在载波中断调用
/*---------------------------------------------------------------------------*/
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
		posMarginAvg = (mcVelEst.PosMargin + mcVelEst.PosMarginPre) >> 1; // 速度预测
			

#if FUNC_PROBE1_ENABLED // 探针1
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
			
			if (!mcProbe.Probe1TrigCon) // 单次触发
			{
				clr_csr(STPC0_CR, STRO_EN);
				mcProbe.Probe1OffFlag = 1;
			}
			
			// 探针1触发边沿选择
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
		
#if FUNC_PROBE2_ENABLED // 探针2
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

			if (!mcProbe.Probe2TrigCon) // 单次触发
			{
				clr_csr(STPC1_CR, STRO_EN);
				mcProbe.Probe2OffFlag = 1;
			}

			// 探针2触发边沿选择
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
						if (!mcPcom.Pcom1Mode) // 固定间隔
						{
							pcomPosNext += mcPcom.Pcom1Offset;
						}
						else // 查表
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
			write_csr(PCOM0_ARR, mcPcom.Pcom1Arr);		// 位置比较1的比较值
		}
#endif // #if FUNC_PCOM_ENABLED
		
	}	
}

#endif // #if FUNC_PROBE_ENABLED || FUNC_PCOM_ENABLED