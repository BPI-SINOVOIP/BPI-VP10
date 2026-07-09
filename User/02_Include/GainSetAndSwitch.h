/*
 * Copyright (c) 2023-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : GainSetAndSwitch.h
 * Author        : wynn.wang
 * Date          : 2023-08-11
 * Description   : Gain switching
 *
 * Record        :
 * V1.0, 2023-08-11, wynn.wang: Created file
 */


/* Define to prevent recursive inclusion -------------------------------------------------------- */
#ifndef __GAINSETANDSWITCH_H__
#define __GAINSETANDSWITCH_H__

#ifdef __cplusplus
extern "C"{
#endif

#include "fu7502.h"
#include "Math.h"
#include "PIControl.h"
#include "Customer.h"

#ifndef CURMOD
#define CURMOD						   ( 1 )
#endif

#ifndef VELMOD
#define VELMOD						   ( 2 )
#endif

#ifndef POSMOD
#define POSMOD                         ( 4 )
#endif


/*************************************************************************************///External Function
typedef enum {
	GNSWCTRL_POS,
	GNSWCTRL_SPD,
} GNSWCtrlType;


typedef struct
{
	const uint16* pVp;				 // Speed loop proportional Kp
	const uint16* pVi;				 // Speed loop integral Ki
	const uint16* pVp2;				 // Speed loop proportional Kp2
	const uint16* pVi2;				 // Speed loop integral Ki2

	const uint16* pPp;				 // Speed loop proportional Kp
	const uint16* pPi;				 // Speed loop integral Ki
	const uint16* pPp2;				 // Speed loop proportional Kp2
	const uint16* pPi2;				 // Speed loop integral Ki2

	const uint16* pVfr;				 //
	const uint16* pVfr2;			 //

	const uint16* pGnSWDlyTm;             // Gain switch delay time

	const uint16* pGnSWPAccTm;           // Position loop gain switch delay time (first gain to second gain switching)
	const uint16* pGnSWPDecTm;           // Position loop gain switch delay time (second gain to first gain switching)
	const uint16* pGnSWVAccTm;           // Speed loop gain switch delay time (first gain to second gain switching)
	const uint16* pGnSWVDecTm;           // Speed loop gain switch delay time (second gain to first gain switching)

	const int16* pGnSwLvl;				  // Gain switching level
	const int16* pGnSwHysteresis;		  // Gain switching hysteresis
	const int16* pRmsCurrent;             // Rated current
	const int16* pMaxSpeed;               // Maximum speed

	const int16* pIqRef;                  // Torque command
	const int16* pVelRef;                 // Speed command
	const int16* pActVel;				  // Actual speed
	const int32* pPosRef;				  // Position command
	const int32* pPosErr;                 // Position error

	int16 PosCtrlFreq;				// Position loop frequency
	int16 VelCtrlFreq;				// Speed loop frequency

	const uint8* pRunMod;					// Run mode
	const uint8* pGnSWMode;               // Gain switching mode
	uint8 GnSwitch;					// IO-controlled gain switching
	uint8 InPos;					// In-position status

} GnSWPCfgTypedef;


typedef struct GnSWPIGainTypedef_t GnSWPIGainTypedef;



/*---------------------------------------------------------------------------
 * Name		:	GainSW_Init
 * Input	:	cfg - configuration parameters
 * Output	:	No
 * Description:	Initialize gain switching
 *---------------------------------------------------------------------------*/
extern void GainSW_Init(const GnSWPCfgTypedef* cfg);


/*---------------------------------------------------------------------------
 * Name		:	GainSW_realize
 * Input	:	cfg - configuration parameters
 * Output	:	No
 * Description:	Update real-time variables (current, velocity, etc.) and gain switching status
 *---------------------------------------------------------------------------*/
extern void GainSW_realize(const GnSWPCfgTypedef* cfg);


/*---------------------------------------------------------------------------
 * Name		:	GainSW_Update
 * Input	:	cfg - configuration parameters
 * Output	:	No
 * Description:	Gain switching related variable update
 *---------------------------------------------------------------------------*/
extern void GainSW_Update(const GnSWPCfgTypedef* cfg);


/*---------------------------------------------------------------------------
 * Name		:	GainSwitching_realize
 * Input	:	p - pointer to PIControl instance
 *				type - 0: position loop, 1: velocity loop
 * Output	:	No
 * Description:	Execute gain switching, update PI gain
 *---------------------------------------------------------------------------*/
extern void GainSwitching_realize(PIControl* p, GNSWCtrlType type);


/*---------------------------------------------------------------------------
 * Name		:	GetGnFir
 * Input	:	p - pointer to PIControl instance
 * Output	:	No
 * Description:	Apply first gain set
 *---------------------------------------------------------------------------*/
extern void GetGnFir(PIControl* p);


/*---------------------------------------------------------------------------
 * Name		:	GainSW_GetSWVelParam
 * Input	:	No
 * Output	:	Pointer to configured GnSWPIGainTypedef instance
 * Description:	Get pointer to velocity loop variable in gain switching
 *---------------------------------------------------------------------------*/
extern GnSWPIGainTypedef* GainSW_GetSWVelParam(void);


/*---------------------------------------------------------------------------
 * Name		:	GainSW_GetSWPosParam
 * Input	:	No
 * Output	:	Pointer to configured GnSWPIGainTypedef instance
 * Description:	Get pointer to position loop variable in gain switching
 *---------------------------------------------------------------------------*/
extern GnSWPIGainTypedef* GainSW_GetSWPosParam(void);

#ifdef __cplusplus
}
#endif

#endif