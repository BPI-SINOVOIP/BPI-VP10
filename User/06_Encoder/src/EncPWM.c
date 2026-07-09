/*
 * Copyright (c) 2022-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : EncPWM.c
 * Author        : Summer
 * Date          : 2025-10-20
 * Description   : PWM Encoder decoding function.
 *
 * Record        :
 * V1.0, 2025-10-20, Summer: Created file
 */

#include <Myproject.h>
#include <Encoder.h>


#if ENCODER_SEL_PWM_ENABLED > 0
/*---------------------------------------------------------------------------
 * Name		:	PWM_Encoder_Init
 * Input	:	No
 * Output	:	No
 * Description:	PWM encoder initialize
 *---------------------------------------------------------------------------*/
void PWM_Encoder_Init(void)
{
	Timer4_PWM_Init();
}


/*---------------------------------------------------------------------------
 * Name		:	PWM_Encoder_Enable
 * Input	:	No
 * Output	:	No
 * Description:	PWM encoder enable
 *---------------------------------------------------------------------------*/
void PWM_Encoder_Enable(void)
{
	mcEncoder.PWM.Multi = 0;
	PWM_Encoder_Update();
	set_csr(TIM4_CR1, T4EN);
}


/*---------------------------------------------------------------------------
 * Name		:	PWM_Encoder_Disable
 * Input	:	No
 * Output	:	No
 * Description:	PWM encoder disable
 *---------------------------------------------------------------------------*/
void PWM_Encoder_Disable(void)
{
	clr_csr(TIM4_CR1, T4EN);
}


/*---------------------------------------------------------------------------
 * Name		:	PWM_Encoder_Update
 * Input	:	No
 * Output	:	No
 * Description:	PWM encoder parameter update
 *---------------------------------------------------------------------------*/
void PWM_Encoder_Update(void)
{
//	if (mcEncoder.PWM.ValidBits != usSRegHoldBuf[ENCVALIDBITS])
	{
		mcEncoder.PWM.ValidBits = 12; // usSRegHoldBuf[ENCVALIDBITS];
		mcEncoder.PWM.DataMask = (1 << mcEncoder.PWM.ValidBits) - 1;
		mcEncoder.PWM.SingleHalf = 1 << (mcEncoder.PWM.ValidBits - 1);
	}
}


/*---------------------------------------------------------------------------
 * Name		:	PWM_Encoder_GetPos
 * Input	:	*pEncPos - encoder value
 * Output	:	encoder error status
 * Description:	Get PWM encoder value
 *---------------------------------------------------------------------------*/
uint16 PWM_Encoder_GetPos(uint32* pEncPos)    //Function to get absolute encoder position
{
	uint16 tOn = read_csr(TIM4_DR);
	uint16 tAll = read_csr(TIM4_ARR);
	uint16 errCode = 0;
	
	if (tOn != 0 && tOn != tAll && tAll != 0xFFFF)
	{
		mcEncoder.PWM.SingleLatch = mcEncoder.PWM.Single;
		mcEncoder.PWM.Single = (uint32)tOn * 4160 / tAll;
		if (mcEncoder.PWM.Single < 32)
			mcEncoder.PWM.Single = 32;
		else if (mcEncoder.PWM.Single > 4128)
			mcEncoder.PWM.Single = 4128;
		
		mcEncoder.PWM.Single -= 32;
		
		if (mcEncoder.PWM.Single > mcEncoder.PWM.SingleLatch &&
			mcEncoder.PWM.Single - mcEncoder.PWM.SingleLatch > mcEncoder.PWM.SingleHalf)
			mcEncoder.PWM.Multi--;
		else if (mcEncoder.PWM.SingleLatch > mcEncoder.PWM.Single &&
			mcEncoder.PWM.SingleLatch - mcEncoder.PWM.Single > mcEncoder.PWM.SingleHalf)
			mcEncoder.PWM.Multi++;

		mcEncoder.PWM.EncData = (mcEncoder.PWM.Multi << mcEncoder.PWM.ValidBits) + mcEncoder.PWM.Single;
	}
	else
	{
		errCode = FaultEncInternal;
	}
	
	*pEncPos = mcEncoder.PWM.EncData;
	return errCode;
}
#endif // #if ENCODER_SEL_PWM_ENABLED > 0