/*
 * Copyright (c) 2025-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : PIControl.c
 * Author        : wynn.wang
 * Date          : 2025-04-20
 * Description   : 实现PI控制器核心功能，包括参数初始化、控制量计算、积分限幅等
 *
 * Record        :
 * V1.0, 2025-04-20, wynn.wang: 初始版本，实现基本PI控制算法
 */


#include <Myproject.h>


PIControl PID_Speed __attribute__((section(".pram.data.PID_Speed")));
PIControl PID_Pos;

#if FUNC_FORCECTRL_ENABLED
PIControlSimple PID_Force;
#endif

uint8 KpKiQArray[4] = { 15, 12, 8, 4 };

/*---------------------------------------------------------------------------*/
/* Name     :  
/* Input    :   
/* Output   :   
/* Description: 
/*---------------------------------------------------------------------------*/
void PI_Init(void)
{
	Hard_PI_Init();	
}

/*---------------------------------------------------------------------------*/
/* Name     :
/* Input    :
/* Output   :
/* Description:
/*---------------------------------------------------------------------------*/
void PI_Clear(void)
{
	Hard_PI_Clear();
}


/*---------------------------------------------------------------------------*/
/* Name     :
/* Input    :
/* Output   :
/* Description:
/*---------------------------------------------------------------------------*/
void Hard_PI_Init(void)
{
	PI_Update();

#if FUNC_GAINSW_ENABLED
	PID_Speed.pGnSW = GainSW_GetSWVelParam();
#endif //#if FUNC_GAINSW_ENABLED
	
	
	set_csr(DRV1_FCR4, PDFF_EN); // 外环PDFF使能, 0: 外环使用PI, 1: 外环使用PDFF
	
	NFOC_PDKP = PID_Speed.Kp1 + PID_Speed.KpQSel;
	NFOC_PDKI = PID_Speed.Ki1 + PID_Speed.KiQSel;
	NFOC_PDKF = (((uint32) PID_Speed.Kp1 * (uint32) PID_Speed.Kvf1) >> 16) + PID_Speed.KpQSel;

	
	if (PID_Speed.SetLimitEn)
	{
		NFOC_PDMAX = PID_Speed.ValueMaxBuffer;
		NFOC_PDMIN = PID_Speed.ValueMinBuffer;
	}
	else
	{
		NFOC_PDMAX = usSRegHoldBuf[VOUTMAX];
		NFOC_PDMIN = usSRegHoldBuf[VOUTMIN];
	}
	NFOC_PDITMP = 0; // 清零积分项
	NFOC_PDISAT = usSRegHoldBuf[DESATUR]; // 积分饱和值
	NFOC_PDUK = 0;
	
	PID_Pos.ValueMax = usSRegHoldBuf[POUTMAX];
	PID_Pos.ValueMin = usSRegHoldBuf[POUTMIN];
	
#if FUNC_GAINSW_ENABLED
	PID_Pos.pGnSW = GainSW_GetSWPosParam();
#endif //#if FUNC_GAINSW_ENABLED

#if FUNC_FORCECLOSEDLOOP_ENABLED
	PI_Control_Init(&PID_Force);
#endif
}

/*---------------------------------------------------------------------------*/
/* Name     :
/* Input    :
/* Output   :
/* Description:
/*---------------------------------------------------------------------------*/
void Hard_PI_Clear(void)
{
	// Clear VelLoop PI
	memset(&NFOC_PDCMD, 0, 11 * 2);
#if FUNC_FORCECLOSEDLOOP_ENABLED
	PI_Control_Clear(&PID_Force);
#endif

	memset(&PID_Speed, 0, sizeof(PIControl));
	memset(&PID_Pos, 0, sizeof(PIControl));

	// Clear CurLoop PI
	NFOC_IDREF = 0;
	NFOC_IQREF = 0;

	usSRegInBuf[CMDCUR] = 0;
	usSRegInBuf[MB_IDREF] = 0;
}

/*---------------------------------------------------------------------------*/
/* Name     :   PI_Spd_realize(void)
/* Input    :
/* Output   :
/* Description: 增量式PI控制 U[k] = U[k-1] + Kp*(E[k] - E[k-1]) + Ki*E[K];
/*---------------------------------------------------------------------------*/
int16 Hard_PI_Spd_realize(int16 Cmd, int16 Act)
{
	NFOC_PDCMD = Cmd;
	NFOC_PDACT = Act;

	NFOC_PDKP = PID_Speed.Kp + PID_Speed.KpQSel;
	NFOC_PDKI = PID_Speed.Ki + PID_Speed.KiQSel;
	NFOC_PDKF = PID_Speed.Kf + PID_Speed.KpQSel;

	return NFOC_PDUK;
}


/*---------------------------------------------------------------------------*/
/* Name     :   PI_Spd_realize(void)
/* Input    :
/* Output   :
/* Description: 增量式PI控制 U[k] = U[k-1] + Kp*(E[k] - E[k-1]) + Ki*E[K];
/*---------------------------------------------------------------------------*/
void Hard_PI_Gain_Update()
{
	NFOC_PDKP = PID_Speed.Kp + PID_Speed.KpQSel;
	NFOC_PDKI = PID_Speed.Ki + PID_Speed.KiQSel;
	NFOC_PDKF = PID_Speed.Kf + PID_Speed.KpQSel;
}


#if FUNC_FORCECTRL_ENABLED
void PI_Spd_Clear(void)
{
	NFOC_PDITMP = 0;
}

void PI_Toq_Clear(void)
{
	NFOC_DEK = 0;
	NFOC_DEK1 = 0;
	NFOC_DUK = 0;
	NFOC_DUKH = 0;

	NFOC_QEK = 0;
	NFOC_QEK1 = 0;
	NFOC_QUK = 0;
	NFOC_QUKH = 0;
}
#endif // #if FUNC_FORCECTRL_ENABLED

/*---------------------------------------------------------------------------*/
/* Name     :   PI_Pos_realize(void)
/* Input    :
/* Output   :
/* Description: 增量式PI控制 U[k] = U[k-1] + Kp*(E[k] - E[k-1]) + Ki*E[K];
/*---------------------------------------------------------------------------*/
int16 PI_Pos_realize(int32 ErrValue)
{
	int64 temp = 0;
	int32 ValuetempKp = 0;
	int8 KpRank = KP_RANK;
	
#if FUNC_FEEDBACKONLOAD_ENABLED
	if (FEEDBACK_LOAD == Feedback_GetOnLoadFlag())
	{
		// 将速度指令由外环转换成内环单位
		temp = (int64)ErrValue * PID_Pos.Kp * Feedback_GetLoadToMotorCoef(); // 注意溢出
		KpRank += MOTORCOEF;
	}
	else
	{
		temp = (int64)ErrValue * PID_Pos.Kp;
	}
#else
	temp = (int64)ErrValue * PID_Pos.Kp;
#endif

	
	if (temp < 0)
	{
		ValuetempKp = (int32)(-((-(int64)temp) >> KpRank));
	}
	else
	{
		ValuetempKp = (int32)((int64)temp >> KpRank);
	}	
	
	ValuetempKp += (int16)usSRegInBuf[SPEEDFF];
	
	if (ValuetempKp > PID_Pos.ValueMax)
	{
		ValuetempKp = PID_Pos.ValueMax;
	}
	else if (ValuetempKp < PID_Pos.ValueMin)
	{
		ValuetempKp = PID_Pos.ValueMin;
	}

	return (int16)ValuetempKp;
}

/*---------------------------------------------------------------------------*/
/* Name     : PI_Spd_UpdateLimit(int16 Max, int16 Min)
/* Input    :
/* Output   :
/* Description:
/*---------------------------------------------------------------------------*/
void PI_Spd_UpdateLimit(int16 Max, int16 Min)
{
	PID_Speed.SetLimitEn = 1;
	PID_Speed.ValueMaxBuffer = Max;
	PID_Speed.ValueMinBuffer = Min;
}

/*---------------------------------------------------------------------------*/
/* Name     : PI_Spd_ResetLimit()
/* Input    :
/* Output   :
/* Description:
/*---------------------------------------------------------------------------*/
void PI_Spd_ResetLimit()
{
	PID_Speed.SetLimitEn = 0;
}


/*---------------------------------------------------------------------------*/
/* Name     :   PI_Update(void)
/* Input    :
/* Output   :
/* Description: 从上位机更新PI增益
/*---------------------------------------------------------------------------*/
void PI_Update()
{
	if (usSRegHoldBuf[VKP] == 0 || usSRegHoldBuf[VKP2] == 0 || 
		(usSRegHoldBuf[VKP] & 0xC000) == (usSRegHoldBuf[VKP2] & 0xC000))
	{
		PID_Speed.Kp1 = usSRegHoldBuf[VKP] & 0x3FFF;
		PID_Speed.Kp2 = usSRegHoldBuf[VKP2] & 0x3FFF;
		PID_Speed.KpQSel = usSRegHoldBuf[VKP] & 0xC000;	
	}

	if (usSRegHoldBuf[VKI] == 0 || usSRegHoldBuf[VKI2] == 0 || 
		(usSRegHoldBuf[VKI] & 0xC000) == (usSRegHoldBuf[VKI2] & 0xC000))
	{
		PID_Speed.Ki1 = usSRegHoldBuf[VKI] & 0x3FFF;
		PID_Speed.Ki2 = usSRegHoldBuf[VKI2] & 0x3FFF;
		PID_Speed.KiQSel = usSRegHoldBuf[VKI] & 0xC000;	
	}
	
	PID_Speed.KpQVal = KpKiQArray[PID_Speed.KpQSel >> 14];
	PID_Speed.KiQVal = KpKiQArray[PID_Speed.KiQSel >> 14];	

	PID_Speed.Kvf1 = usSRegHoldBuf[VFR];
	PID_Speed.Kvf2 = usSRegHoldBuf[VFR2];

	PID_Pos.Kp1 = usSRegHoldBuf[PKP];
	PID_Pos.Ki1 = usSRegHoldBuf[PKI];
	PID_Pos.Kp2 = usSRegHoldBuf[PKP2];
	PID_Pos.Ki2 = usSRegHoldBuf[PKI2];
}