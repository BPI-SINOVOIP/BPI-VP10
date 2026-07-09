/*
 * Copyright (c) 2025-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : CurrentBack.h
 * Author        : wynn.wang
 * Date          : 2025-01-46
 * Description   : Current Foldback.
 *
 * Record        :
 * V1.0, 2025-01-46, wynn.wang: Created file
 */


/* Define to prevent recursive inclusion -------------------------------------------------------- */
#ifndef __CURRENTBACK_H__
#define __CURRENTBACK_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "fu7502.h"
#include "Math.h"
#include "Filter.h"


/* ------ FeedBack Type ------ */
/* ------ External input variables ------ */
typedef struct
{
	int32 Tdelay;                        // Peak current delay time ms
	int32 Tc;                            // Time constant ms
	int16 DriveVal;                      // Sustained current value
	int16 PeakVal;                       // Peak current value
	int16 WarnThresHoldVal;              // Warning current threshold value
	int16 FaultThresHoldVal;             // Fault current threshold value
	int16 CurrMax;						// Current threshold upper limit
	int16 CurrMin;						// Current threshold lower limit
	uint16 CurBackFreq;					// Update frequency
	const int16* pActualCurrent;              // Actual current value
	const uint8* pFoldbackSon;				// Foldback enable status - 1: enabled 0: disabled
	const uint8* pLoopEnable;                 // Current loop enable status - 1: enabled 0: disabled
} CurrBackCfgTypedef;


typedef struct CurrBackTypedf_t CurrBackTypedf;

extern CurrBackTypedf MotorCurrBack;

/*************************************************************************************///External Function


/*---------------------------------------------------------------------------
 * Name		:	CurrBackProtect_Init
 * Input	:	p - Pointer to CurrBackTypedf instance
 *				cfg - Configuration parameters
 * Output	:	No
 * Description:	Initialize current foldback
 *---------------------------------------------------------------------------*/
extern void CurrBackProtect_Init(CurrBackTypedf* p, CurrBackCfgTypedef * cfg);


/*---------------------------------------------------------------------------
 * Name		:	CurrBackProtect_Clr
 * Input	:	p - Pointer to CurrBackTypedf instance
 * Output	:	No
 * Description:	Reset current foldback
 *---------------------------------------------------------------------------*/
extern void CurrBackProtect_Clr(CurrBackTypedf* p);


 /*---------------------------------------------------------------------------
 * Name		:	CurrBackProtect_realize
 * Input	:	p - Pointer to CurrBackTypedf instance
 * Output	:	No
 * Description:	Execute current foldback function, updating current limits IQMAX/IQMIN
 *---------------------------------------------------------------------------*/
extern void CurrBackProtect_realize(CurrBackTypedf* p);


/*---------------------------------------------------------------------------
 * Name     :   CurrBackProtect_Fault
 * Input    :   p - Pointer to CurrBackTypedf instance
 * Output   :   Current foldback fault flag
 * Description: Get current foldback fault flag
 *---------------------------------------------------------------------------*/
extern uint8 CurrBackProtect_Fault(CurrBackTypedf* p);


/*---------------------------------------------------------------------------
 * Name     :   CurrBackProtect_Warn
 * Input    :   p - Pointer to CurrBackTypedf instance
 * Output   :   Current foldback warning flag
 * Description: Get current foldback warning flag
 *---------------------------------------------------------------------------*/
extern uint8 CurrBackProtect_Warn(CurrBackTypedf* p);

#ifdef __cplusplus
}
#endif

#endif