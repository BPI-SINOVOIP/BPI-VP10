/*
 * FreeModbus Libary: user callback functions and buffer define in slave mode
 * Copyright (C) 2013 Armink <armink.ztl@gmail.com>
 * 
 * Modifications Copyright (C) 2022-2026 Fortior Technology Co., Ltd.
 * Author: Summer.li <summer.li@fortiortech.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * File: $Id: user_mb_app.h,v 1.60 2013/11/23 11:49:05 Armink $
 *		 $Id: user_mb_app.h,v 2.01 2022/05/13 11:09:05 Summer.li: Added extended register mapping for servo motor control $
 */

#ifndef USER_APP
#define USER_APP
/* ----------------------- Modbus includes ----------------------------------*/
#include "mb.h"
#include "mbconfig.h"
#include "mbframe.h"


/* -----------------------Slave Defines -------------------------------------*/
#define S_DISCRETE_INPUT_START        (0)
#define S_DISCRETE_INPUT_NDISCRETES   (0)  // 16
#define S_COIL_START                  (0)
#define S_COIL_NCOILS                 (0)  // 64
#define S_REG_INPUT_START             (0)
#define S_REG_INPUT_NREGS             (160)
#define S_REG_HOLDING_START           (0)
#define S_REG_HOLDING_NREGS           (800)

#define S_REG_SCOPE_START             (0)
#define S_REG_SCOPE_NREGS             (1200)


/* -----------------------Slave ID -------------------------------------*/
#define MODEBUS_SLAVE_ID				( 0x01 )  //


/* -----------------------Basic function Defines -------------------------------------*/
#ifndef SetReg
#define SetReg(reg, val1, val2)         ((reg) = ((reg) & (~(val1))) | ((val2) & (val1)))    // Setregval1Write bits corresponding toval2
#endif

#ifndef GetReg
#define GetReg(reg, val1)               ((reg) & (val1))						// Getregval1
#endif

#ifndef SetBit
#define SetBit(reg, val)                ((reg) |=  (val))                       // Set bits specified by val in reg to 1
#endif

#ifndef ClrBit
#define ClrBit(reg, val)                ((reg) &= ~(val))                       // Clear bits specified by val in reg to 0
#endif

#ifndef XorBit
#define XorBit(reg, val)                ((reg) ^=  (val))                       // Toggle bits specified by val in reg
#endif

#ifndef ReadBit
#define ReadBit(reg, val)               (((reg) & (val)) != 0)                  // Check if bits specified by val in reg are set
#endif


/////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////// Holding Register /////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////
// Variable groups
#define S_REG_HOLDING_INDEX_CTRL				(0)
#define S_REG_HOLDING_INDEX_COMMUNICATION		(1)
#define S_REG_HOLDING_INDEX_DRIVER				(2)
#define S_REG_HOLDING_INDEX_MOTOR				(3)
#define S_REG_HOLDING_INDEX_FEEDBACK			(4)
#define S_REG_HOLDING_INDEX_CONTROLLER			(5)
#define S_REG_HOLDING_INDEX_OUTFILT				(6)
#define S_REG_HOLDING_INDEX_LIMIT				(7)
#define S_REG_HOLDING_INDEX_MOTION				(8)
#define S_REG_HOLDING_INDEX_FORCECTRL			(9)
#define S_REG_HOLDING_INDEX_DIGITAL				(10)
#define S_REG_HOLDING_INDEX_ANALOG				(11)
#define S_REG_HOLDING_INDEX_TEST				(12)
#define S_REG_HOLDING_INDEX_ERRCOR				(13)

#define S_REG_HOLDING_INDEX_MAX  				(14)

// Number of variables per group
#define S_REG_HOLDING_SIZE_CTRL					(5)
#define S_REG_HOLDING_SIZE_COMMUNICATION		(16)
#define S_REG_HOLDING_SIZE_DRIVER				(28)
#define S_REG_HOLDING_SIZE_MOTOR				(42)
#define S_REG_HOLDING_SIZE_FEEDBACK				(40)
#define S_REG_HOLDING_SIZE_CONTROLLER			(110)
#define S_REG_HOLDING_SIZE_OUTFILT				(98)
#define S_REG_HOLDING_SIZE_LIMIT				(60)
#define S_REG_HOLDING_SIZE_MOTION				(40)
#define S_REG_HOLDING_SIZE_FORCECTRL			(156)
#define S_REG_HOLDING_SIZE_DIGITAL				(28)
#define S_REG_HOLDING_SIZE_ANALOG				(7)
#define S_REG_HOLDING_SIZE_TEST					(10)
#define S_REG_HOLDING_SIZE_ERRCOR				(73)


#define S_REG_HOLDING_START_CTRL				(0)
#define S_REG_HOLDING_START_COMMUNICATION		(S_REG_HOLDING_START_CTRL + S_REG_HOLDING_SIZE_CTRL)
#define S_REG_HOLDING_START_DRIVER				(S_REG_HOLDING_START_COMMUNICATION + S_REG_HOLDING_SIZE_COMMUNICATION)
#define S_REG_HOLDING_START_MOTOR				(S_REG_HOLDING_START_DRIVER + S_REG_HOLDING_SIZE_DRIVER)
#define S_REG_HOLDING_START_FEEDBACK			(S_REG_HOLDING_START_MOTOR + S_REG_HOLDING_SIZE_MOTOR)
#define S_REG_HOLDING_START_CONTROLLER			(S_REG_HOLDING_START_FEEDBACK + S_REG_HOLDING_SIZE_FEEDBACK)
#define S_REG_HOLDING_START_OUTFILT				(S_REG_HOLDING_START_CONTROLLER + S_REG_HOLDING_SIZE_CONTROLLER)
#define S_REG_HOLDING_START_LIMIT				(S_REG_HOLDING_START_OUTFILT + S_REG_HOLDING_SIZE_OUTFILT)
#define S_REG_HOLDING_START_MOTION				(S_REG_HOLDING_START_LIMIT + S_REG_HOLDING_SIZE_LIMIT)
#define S_REG_HOLDING_START_FORCECTRL			(S_REG_HOLDING_START_MOTION + S_REG_HOLDING_SIZE_MOTION)	//NEW
#define S_REG_HOLDING_START_DIGITAL				(S_REG_HOLDING_START_FORCECTRL + S_REG_HOLDING_SIZE_FORCECTRL)
#define S_REG_HOLDING_START_ANALOG				(S_REG_HOLDING_START_DIGITAL + S_REG_HOLDING_SIZE_DIGITAL)
#define S_REG_HOLDING_START_TEST				(S_REG_HOLDING_START_ANALOG + S_REG_HOLDING_SIZE_ANALOG)
#define S_REG_HOLDING_START_ERRCOR				(S_REG_HOLDING_START_TEST + S_REG_HOLDING_SIZE_TEST)

#define S_REG_HOLDING_SIZE_TOTAL				(S_REG_HOLDING_START_ERRCOR + S_REG_HOLDING_SIZE_ERRCOR)


//************** Control parameters S_REG_HOLDING_INDEX_CTRL (0) **************//
#define DRIVECTRL								(S_REG_HOLDING_START_CTRL + 0) // Control word, see below for details
#define DRIVEMODE								(S_REG_HOLDING_START_CTRL + 1) // Control mode, see below for details
// 0xE8E8->0x5A5A: upload parameter from flash; 0xE8E8->0xA5A5: download Holding register to flash;
#define FLASHCTRL								(S_REG_HOLDING_START_CTRL + 2) // Flash operation
#define OPMODESWITCH							(S_REG_HOLDING_START_CTRL + 3) // Mode switching
#define DRIVESWITCH								(S_REG_HOLDING_START_CTRL + 4) // Control switch, see below for details


//************** Communication parameters S_REG_HOLDING_INDEX_COMMUNICATION (1) **************//
#define SCOPECTRL								(S_REG_HOLDING_START_COMMUNICATION + 0) // Scope sampling control
#define SCOPEADDR_0								(S_REG_HOLDING_START_COMMUNICATION + 1) // Scope variable 0 address
#define SCOPEADDR_1								(S_REG_HOLDING_START_COMMUNICATION + 2) // Scope variable 1 address
#define SCOPEADDR_2								(S_REG_HOLDING_START_COMMUNICATION + 3) // Scope variable 2 address
#define SCOPEADDR_3								(S_REG_HOLDING_START_COMMUNICATION + 4) // Scope variable 3 address
#define SCOPEADDR_4								(S_REG_HOLDING_START_COMMUNICATION + 5) // Scope variable 4 address
#define SCOPEADDR_5								(S_REG_HOLDING_START_COMMUNICATION + 6) // Scope variable 5 address
#define SCOPENUM								(S_REG_HOLDING_START_COMMUNICATION + 7) // Number of samples per scope variable
#define SCOPEINTERVAL							(S_REG_HOLDING_START_COMMUNICATION + 8) // Scope sampling interval
#define SCOPETRIGADDR							(S_REG_HOLDING_START_COMMUNICATION + 9) // Trigger sampling variable address
#define SCOPETRIGLEVEL_L						(S_REG_HOLDING_START_COMMUNICATION + 10) // Trigger sampling threshold, low 16-bit
#define SCOPETRIGLEVEL_H						(S_REG_HOLDING_START_COMMUNICATION + 11) // Trigger sampling threshold, high 16-bit
#define SCOPETRIGPRE							(S_REG_HOLDING_START_COMMUNICATION + 12) // Number of pre-trigger samples to record
#define CANBITRATE								(S_REG_HOLDING_START_COMMUNICATION + 13) // CAN baud rate
#define COMMADDR								(S_REG_HOLDING_START_COMMUNICATION + 14) // CAN communication address ID
#define FBSYNCSET								(S_REG_HOLDING_START_COMMUNICATION + 15) // CAN sync period

//************** Driver parameters S_REG_HOLDING_INDEX_DRIVER (2) **************//
#define CURCOE									(S_REG_HOLDING_START_DRIVER + 0) // Current conversion coefficient, count/A
#define DRIVERPEAKCUR							(S_REG_HOLDING_START_DRIVER + 1) // Driver peak current
#define DRIVERRMSCUR							(S_REG_HOLDING_START_DRIVER + 2) // Driver rated current
#define VBUS									(S_REG_HOLDING_START_DRIVER + 3) // Driver bus voltage
#define VOLGAIN									(S_REG_HOLDING_START_DRIVER + 4) // Bus voltage conversion coefficient: gain
#define VOLOFFSET								(S_REG_HOLDING_START_DRIVER + 5) // Bus voltage conversion coefficient: offset
#define REGENVMHIGH								(S_REG_HOLDING_START_DRIVER + 6) // Regenerative braking voltage upper limit
#define REGENVMLOW								(S_REG_HOLDING_START_DRIVER + 7) // Regenerative braking voltage lower limit
#define REGENPOW								(S_REG_HOLDING_START_DRIVER + 8) // Regenerative resistor power
#define REGENRES								(S_REG_HOLDING_START_DRIVER + 9) // Regenerative resistor resistance
#define REGENCOE								(S_REG_HOLDING_START_DRIVER + 10) // Regenerative braking calculation coefficient
#define UDCMAX									(S_REG_HOLDING_START_DRIVER + 11) // Bus voltage fluctuation upper limit, for current loop complex vector controller
#define UDCMIN									(S_REG_HOLDING_START_DRIVER + 12) // Bus voltage fluctuation lower limit, for current loop complex vector controller
#define DEADCOMPCUR								(S_REG_HOLDING_START_DRIVER + 13) // Current threshold for enabling dead-time compensation
#define DISMODE									(S_REG_HOLDING_START_DRIVER + 14) // Stop mode
#define STOPCURRENT								(S_REG_HOLDING_START_DRIVER + 15) // Dynamic braking current
#define STOPCURLIM								(S_REG_HOLDING_START_DRIVER + 16) // Stop current threshold
#define DISSPEED								(S_REG_HOLDING_START_DRIVER + 17) // Stop speed
#define DISDEC									(S_REG_HOLDING_START_DRIVER + 18) // Stop deceleration
#define DISDECTIME								(S_REG_HOLDING_START_DRIVER + 19) // Stop deceleration time
#define DISTIME									(S_REG_HOLDING_START_DRIVER + 20) // Stop confirmation time
#define DISTIMEOUT								(S_REG_HOLDING_START_DRIVER + 21) // Stop timeout
#define IDQLPFK									(S_REG_HOLDING_START_DRIVER + 22) // ID/IQ low-pass filter coefficient
#define UDQLPFK									(S_REG_HOLDING_START_DRIVER + 23) // UD/UQ low-pass filter coefficient
#define DEADTIME								(S_REG_HOLDING_START_DRIVER + 24) // Dead time
#define ISAMDELAY								(S_REG_HOLDING_START_DRIVER + 25) // Sampling delay time
#define MINPWMWIDTH								(S_REG_HOLDING_START_DRIVER + 26) // Minimum sampling pulse width
#define VOLDEN									(S_REG_HOLDING_START_DRIVER + 27) // Bus voltage conversion coefficient: denominator

//************** Motor parameters S_REG_HOLDING_INDEX_MOTOR (3) **************//
#define POLES									(S_REG_HOLDING_START_MOTOR + 0) // Rotary motor: pole count; Linear motor: 2
#define PITCH_L									(S_REG_HOLDING_START_MOTOR + 1) // Rotary motor: 1000; Linear motor: pole pitch, um
#define PITCH_H									(S_REG_HOLDING_START_MOTOR + 2)  
#define MASS_L									(S_REG_HOLDING_START_MOTOR + 3) // Motor inertia, kg·cm² or kg, Q10
#define MASS_H									(S_REG_HOLDING_START_MOTOR + 4) 
#define FORCECONST								(S_REG_HOLDING_START_MOTOR + 5) // Torque constant, Nm/A or N/A, Q7
#define INDUCTANCE								(S_REG_HOLDING_START_MOTOR + 6) // Line inductance, mH, Q8
#define RESISTANCE								(S_REG_HOLDING_START_MOTOR + 7) // Line resistance, Ohms, Q8
#define MOTORMAXSPEED							(S_REG_HOLDING_START_MOTOR + 8) // Motor max speed, rpm, mm/s
#define QEPSPEEDCOE								(S_REG_HOLDING_START_MOTOR + 9) // Speed calculation conversion coefficient
#define SPEEDCOERANK							(S_REG_HOLDING_START_MOTOR + 10) // Speed calculation conversion coefficient2
#define HARDCURRENT								(S_REG_HOLDING_START_MOTOR + 11) // Motor hardware overcurrent protection current, count
#define PEAKCURRENT								(S_REG_HOLDING_START_MOTOR + 12) // Motor peak current, count
#define RMSCURRENT								(S_REG_HOLDING_START_MOTOR + 13) // Motor rated current, count
#define LMJREST				     				(S_REG_HOLDING_START_MOTOR + 14) // Inertia identification enable
#define LMJR				     				(S_REG_HOLDING_START_MOTOR + 15) // Inertia ratio = load inertia / motor inertia, 0.1x
#define LMJRHIGHSPEED				     		(S_REG_HOLDING_START_MOTOR + 16) // Motor max speed for inertia identification
#define LMJRSTARTRATIO				     		(S_REG_HOLDING_START_MOTOR + 17) // Inertia identification start speed percentage
#define LMJRCALCLENGTH				     		(S_REG_HOLDING_START_MOTOR + 18) // Inertia identification detection data length
#define MOTORNAME_0				     			(S_REG_HOLDING_START_MOTOR + 19) // Motor name
#define MOTORNAME_1				     			(S_REG_HOLDING_START_MOTOR + 20)
#define MOTORNAME_2				     			(S_REG_HOLDING_START_MOTOR + 21)
#define MOTORNAME_3				     			(S_REG_HOLDING_START_MOTOR + 22)
#define MOTORNAME_4				     			(S_REG_HOLDING_START_MOTOR + 23)
#define MOTORNAME_5				     			(S_REG_HOLDING_START_MOTOR + 24)
#define MOTORNAME_6				     			(S_REG_HOLDING_START_MOTOR + 25)
#define MOTORNAME_7				     			(S_REG_HOLDING_START_MOTOR + 26)
#define DINDUCTANCE				     			(S_REG_HOLDING_START_MOTOR + 27) // D-axis inductance
#define BEMFCONST				     			(S_REG_HOLDING_START_MOTOR + 28) // Back-EMF constant, V/(rad/s) or V/(m/s), Q7
#define MOTORRATEDSPEED							(S_REG_HOLDING_START_MOTOR + 29) // Motor rated speed, count
#define ESTMODE				     				(S_REG_HOLDING_START_MOTOR + 30) // Motor parametersidentification mode
#define ESTIAMP									(S_REG_HOLDING_START_MOTOR + 31) // Motor parametersidentification current amplitude
#define ESTIMINRATIO							(S_REG_HOLDING_START_MOTOR + 32) // Motor resistance estimation min current percentage
#define ESTRTIME				     			(S_REG_HOLDING_START_MOTOR + 33) // Motor resistance estimation per-segment signal duration
#define ESTLTIME				     			(S_REG_HOLDING_START_MOTOR + 34) // Motor inductance estimation per-segment signal duration
#define ESTUMAX				     				(S_REG_HOLDING_START_MOTOR + 35) // Motor inductance estimation max voltage
#define ESTUMIN				     				(S_REG_HOLDING_START_MOTOR + 36) // Motor inductance estimation initial voltage
#define ESTUDELTA				     			(S_REG_HOLDING_START_MOTOR + 37) // Motor inductance estimation voltage increment
#define ESTFMAX				     				(S_REG_HOLDING_START_MOTOR + 38) // Motor inductance estimation max frequency
#define ESTFMIN				     				(S_REG_HOLDING_START_MOTOR + 39) // Motor inductance estimation min frequency
#define ESTFDELTA								(S_REG_HOLDING_START_MOTOR + 40) // Motor inductance estimation frequency increment
#define ESTRRATIO				     			(S_REG_HOLDING_START_MOTOR + 41) // Motor resistance estimation result coefficient



//************** Encoder parameters S_REG_HOLDING_INDEX_FEEDBACK (4) **************//
#define ENCTYPE 								(S_REG_HOLDING_START_FEEDBACK + 0) // Encoder type
#define ENCRES_L								(S_REG_HOLDING_START_FEEDBACK + 1) // Encoder per-revolution or pole-pitch resolution, count
#define ENCRES_H								(S_REG_HOLDING_START_FEEDBACK + 2)
#define HALLMODE								(S_REG_HOLDING_START_FEEDBACK + 3) // Hall mode
#define ELECANGSHIFT							(S_REG_HOLDING_START_FEEDBACK + 4) // Hall phase shift angle / absolute encoder electrical angle offset
#define ENCDATABITS								(S_REG_HOLDING_START_FEEDBACK + 5) // Encoder protocol data segment total length
#define ENCVALIDBITS							(S_REG_HOLDING_START_FEEDBACK + 6) // Encoder valid data length
#define ENCZEROBITS								(S_REG_HOLDING_START_FEEDBACK + 7) // BiSS low-bit invalid data length
#define ENCCLKFREQ								(S_REG_HOLDING_START_FEEDBACK + 8) // BiSS clock frequency
#define AQBFILT									(S_REG_HOLDING_START_FEEDBACK + 9) // AQB filter depth
// Encoder Output
#define ENCOUTMODE								(S_REG_HOLDING_START_FEEDBACK + 10) // Encoder emulation output mode
#define ENCOUTRES_L								(S_REG_HOLDING_START_FEEDBACK + 11) // Encoder emulation output resolution, count
#define ENCOUTRES_H								(S_REG_HOLDING_START_FEEDBACK + 12) 
#define ENCOUTMAX								(S_REG_HOLDING_START_FEEDBACK + 13) // Encoder output max frequency
#define ELECANGSW_L								(S_REG_HOLDING_START_FEEDBACK + 14) // Electrical angle conversion coefficient, _Q16(POLES * 32768 / ENCRES)
#define ELECANGSW_H							    (S_REG_HOLDING_START_FEEDBACK + 15) //
#define ELECANGMW_L								(S_REG_HOLDING_START_FEEDBACK + 16) // Electrical angle conversion coefficient 2, _Q15(POLES*32768/ENCRES*65536*65536)
#define ELECANGMW_H							    (S_REG_HOLDING_START_FEEDBACK + 17) //
// Phase find
#define PHASEFINDMODE							(S_REG_HOLDING_START_FEEDBACK + 18) // Phase find mode: 0: NormalStart; 1: SmoothStart; 8: Autophase
#define PHASEFINDCURRENT						(S_REG_HOLDING_START_FEEDBACK + 19) // Phase find current
#define PHASEFINDTIMEOUT						(S_REG_HOLDING_START_FEEDBACK + 20) // Phase find timeout, ms
#define PHASEFINDIDSTEP							(S_REG_HOLDING_START_FEEDBACK + 21) // Command current increment per ms, count
#define PHASEFINDTANGLESTEP						(S_REG_HOLDING_START_FEEDBACK + 22) // Command electrical angle increment per ms, count
#define PHASEFINDMOVEMENT						(S_REG_HOLDING_START_FEEDBACK + 23) // Encoder value corresponding to electrical angle change threshold
#define PHASEFINDMOVEANG_L						(S_REG_HOLDING_START_FEEDBACK + 24) // Autophase total movement distance, count-eAngle
#define PHASEFINDMOVEANG_H						(S_REG_HOLDING_START_FEEDBACK + 25)
#define PHASEFINDTIME							(S_REG_HOLDING_START_FEEDBACK + 26) // Dwell time during phase find
#define HALLCOMMTHRESH							(S_REG_HOLDING_START_FEEDBACK + 27) // When Hall static count exceeds this value, use 6-step commutation for electrical angle; otherwise use position interpolation; Halls-Only mode only
#define HALLPOSLPFK								(S_REG_HOLDING_START_FEEDBACK + 28) // Halls-Only position 1st-order LPF coefficient
#define MOTORCOMMTYPE							(S_REG_HOLDING_START_FEEDBACK + 29) // Motor commutation type
#define SFBENCTYPE								(S_REG_HOLDING_START_FEEDBACK + 30) // loadEncoder type
#define SFBENCRES_L								(S_REG_HOLDING_START_FEEDBACK + 31) // Load-side encoder resolution
#define SFBENCRES_H								(S_REG_HOLDING_START_FEEDBACK + 32)
#define ENCCALCTRL								(S_REG_HOLDING_START_FEEDBACK + 33) // Encoder register read/write control
#define ENCREGADDR								(S_REG_HOLDING_START_FEEDBACK + 34) // Encoder register address
#define ENCREGVAL								(S_REG_HOLDING_START_FEEDBACK + 35) // Encoder register value
#define ANGOFFSET_L								(S_REG_HOLDING_START_FEEDBACK + 36) // Motor-side position offset
#define ANGOFFSET_H								(S_REG_HOLDING_START_FEEDBACK + 37)
#define SFBANGOFFSET_L							(S_REG_HOLDING_START_FEEDBACK + 38) // Output-side position offset
#define SFBANGOFFSET_H							(S_REG_HOLDING_START_FEEDBACK + 39)

//************** Three-loopControl parameters S_REG_HOLDING_INDEX_CONTROLLER (5) **************//
// Current Loop
#define DQKP									(S_REG_HOLDING_START_CONTROLLER + 0) // DQ-axis KP, corresponds to legacy current loop
#define DQKI									(S_REG_HOLDING_START_CONTROLLER + 1) // DQ-axis KI, corresponds to legacy current loop
// Velocity Loop
#define VKP										(S_REG_HOLDING_START_CONTROLLER + 2) // Velocity loop KP
#define VKI										(S_REG_HOLDING_START_CONTROLLER + 3) // Velocity loop KI
#define VKP2									(S_REG_HOLDING_START_CONTROLLER + 4) // 2ndVelocity loop KP2
#define VKI2									(S_REG_HOLDING_START_CONTROLLER + 5) // 2ndVelocity loop KI2
#define VFR										(S_REG_HOLDING_START_CONTROLLER + 6) // Pseudo-derivative feedback coefficient (PDFF)
// Position Loop
#define PKP										(S_REG_HOLDING_START_CONTROLLER + 7) // Position loop KP (_Q12)
#define PKI										(S_REG_HOLDING_START_CONTROLLER + 8) // Position loop KI (_Q15)
#define PKP2									(S_REG_HOLDING_START_CONTROLLER + 9) // 2ndPosition loop KP (_Q12)
#define PKI2									(S_REG_HOLDING_START_CONTROLLER + 10) // 2ndPosition loop KI (_Q15)
// Gain Switch
#define GAINSWMODE								(S_REG_HOLDING_START_CONTROLLER + 11) // Gain switching condition
#define GAINSWDLYTM								(S_REG_HOLDING_START_CONTROLLER + 12) // Gain switching delay time
#define GAINSWLEVEL								(S_REG_HOLDING_START_CONTROLLER + 13) // Gain switching level
#define GAINSWHYSTERESIS						(S_REG_HOLDING_START_CONTROLLER + 14) // Gain switching hysteresis
#define GAINSWPACCTM							(S_REG_HOLDING_START_CONTROLLER + 15) // Position gain switch ramp-up time
#define GAINSWPDECTM							(S_REG_HOLDING_START_CONTROLLER + 16) // Position gain switch ramp-down time
#define GAINSWVACCTM							(S_REG_HOLDING_START_CONTROLLER + 17) // Velocity gain switch ramp-up time
#define GAINSWVDECTM							(S_REG_HOLDING_START_CONTROLLER + 18) // Velocity gain switch ramp-down time

#define INFILTCTRL								(S_REG_HOLDING_START_CONTROLLER + 19) // Filter type
#define INFILT1AVG								(S_REG_HOLDING_START_CONTROLLER + 20) // Position command filter 1, moving average depth
#define INFILT1LPFK								(S_REG_HOLDING_START_CONTROLLER + 21) // Position command filter 1, 1st-order LPF cutoff frequency
#define INFILT2AVG								(S_REG_HOLDING_START_CONTROLLER + 22) // Position command filter 2, moving average depth
#define INFILT2LPFK								(S_REG_HOLDING_START_CONTROLLER + 23) // Position command filter 2, 1st-order LPF cutoff frequency
#define INFILT3AVG								(S_REG_HOLDING_START_CONTROLLER + 24) // Velocity feedback filter 1, moving average depth
#define INFILT3LPFK								(S_REG_HOLDING_START_CONTROLLER + 25) // Velocity feedback filter 1, 1st-order LPF cutoff frequency
#define INFILT4AVG								(S_REG_HOLDING_START_CONTROLLER + 26) // Velocity feedback filter 2, moving average depth
#define INFILT4LPFK								(S_REG_HOLDING_START_CONTROLLER + 27) // Velocity feedback filter 2, 1st-order LPF cutoff frequency

#define NTF1MODE                                (S_REG_HOLDING_START_CONTROLLER + 28) // Vibration suppression mode select
#define NTF1HZ                                  (S_REG_HOLDING_START_CONTROLLER + 29) // Vibration suppression filter frequency (0.1Hz)
#define NTF1SHARP                               (S_REG_HOLDING_START_CONTROLLER + 30) // Vibration suppression filter sharpness (0.01)
#define NTF1GAIN                                (S_REG_HOLDING_START_CONTROLLER + 31) // Vibration suppression damping gain (Rad*10⁻³/Nm)
#define NTF2MODE                                (S_REG_HOLDING_START_CONTROLLER + 32) // Vibration suppression mode select
#define NTF2HZ                                  (S_REG_HOLDING_START_CONTROLLER + 33) // Vibration suppression filter frequency (0.1Hz)
#define NTF2SHARP                               (S_REG_HOLDING_START_CONTROLLER + 34) // Vibration suppression filter sharpness (0.01)
#define NTF2GAIN                                (S_REG_HOLDING_START_CONTROLLER + 35) // Vibration suppression damping gain (Rad*10⁻³/Nm)

#define PVFRMOD									(S_REG_HOLDING_START_CONTROLLER + 36) // Velocity feedforward
#define PVFR									(S_REG_HOLDING_START_CONTROLLER + 37) // Velocity feedforwardcoefficient
#define PVFRLPFHZ								(S_REG_HOLDING_START_CONTROLLER + 38) // Velocity feedforwardLPF cutoff frequency(0.1Hz)

#define LPF2FREQ                                (S_REG_HOLDING_START_CONTROLLER + 39) // Torque feedforward LPF cutoff frequency (0.1Hz)
#define KACCB                                   (S_REG_HOLDING_START_CONTROLLER + 40) // Torque feedforward gain
#define KACMOD                                  (S_REG_HOLDING_START_CONTROLLER + 41) // Torque feedforward source
#define KACAVG									(S_REG_HOLDING_START_CONTROLLER + 42) // Torque feedforward smoothing filter depth

#define CBW										(S_REG_HOLDING_START_CONTROLLER + 43) // Current loop bandwidth
#define VBW										(S_REG_HOLDING_START_CONTROLLER + 44) // Velocity loop bandwidth

#define NTF1B0_L								(S_REG_HOLDING_START_CONTROLLER + 45) // Vibration suppression filter 1 coefficient B0, low 16-bit
#define NTF1B0_H								(S_REG_HOLDING_START_CONTROLLER + 46) // Vibration suppression filter 1 coefficient B0, high 16-bit
#define NTF1B1_L								(S_REG_HOLDING_START_CONTROLLER + 47)
#define NTF1B2_L								(S_REG_HOLDING_START_CONTROLLER + 48)
#define NTF1A1_L								(S_REG_HOLDING_START_CONTROLLER + 49)
#define NTF1A2_L								(S_REG_HOLDING_START_CONTROLLER + 50)
#define NTF1B1_H								(S_REG_HOLDING_START_CONTROLLER + 51)
#define NTF1B2_H								(S_REG_HOLDING_START_CONTROLLER + 52)
#define NTF1A1_H								(S_REG_HOLDING_START_CONTROLLER + 53)
#define NTF1A2_H								(S_REG_HOLDING_START_CONTROLLER + 54)

#define NTF2B0_L								(S_REG_HOLDING_START_CONTROLLER + 55) // Vibration suppression filter 2 coefficient B0, low 16-bit
#define NTF2B0_H								(S_REG_HOLDING_START_CONTROLLER + 56) // Vibration suppression filter 2 coefficient B0, high 16-bit
#define NTF2B1_L								(S_REG_HOLDING_START_CONTROLLER + 57)
#define NTF2B2_L								(S_REG_HOLDING_START_CONTROLLER + 58)
#define NTF2A1_L								(S_REG_HOLDING_START_CONTROLLER + 59)
#define NTF2A2_L								(S_REG_HOLDING_START_CONTROLLER + 60)
#define NTF2B1_H								(S_REG_HOLDING_START_CONTROLLER + 61)
#define NTF2B2_H								(S_REG_HOLDING_START_CONTROLLER + 62)
#define NTF2A1_H								(S_REG_HOLDING_START_CONTROLLER + 63)
#define NTF2A2_H								(S_REG_HOLDING_START_CONTROLLER + 64)

#define VFR2									(S_REG_HOLDING_START_CONTROLLER + 65) // Pseudo-derivative feedback coefficient 2 (PDFF)
#define DESATUR									(S_REG_HOLDING_START_CONTROLLER + 66) // Velocity loop controller desaturation coefficient (Q14)

#define IGRAV									(S_REG_HOLDING_START_CONTROLLER + 67) // Gravity compensation value
#define FRICMOD									(S_REG_HOLDING_START_CONTROLLER + 68) // Friction function enable
#define FRICVSRC								(S_REG_HOLDING_START_CONTROLLER + 69) // Friction speed select: 0-PTPCMD, 1-CMDVEL, 2-ACTVEL
#define FRICIPOS								(S_REG_HOLDING_START_CONTROLLER + 70) // Forward friction compensation value
#define FRICINEG								(S_REG_HOLDING_START_CONTROLLER + 71) // Reverse friction compensation value
#define FRICPVHYST								(S_REG_HOLDING_START_CONTROLLER + 72) // Forward friction compensation dead-zone threshold
#define FRICNVHYST								(S_REG_HOLDING_START_CONTROLLER + 73) // Reverse friction compensation dead-zone threshold
#define FRICPVTHRESH							(S_REG_HOLDING_START_CONTROLLER + 74) // Friction compensation forward velocity threshold
#define FRICNVTHRESH							(S_REG_HOLDING_START_CONTROLLER + 75) // Friction compensation reverse velocity threshold
#define FRICLPFHZ								(S_REG_HOLDING_START_CONTROLLER + 76) // Friction compensation low-pass filter

#define CVMOD									(S_REG_HOLDING_START_CONTROLLER + 77) // Complex vector decoupling controller mode select
#define CVKQSEL									(S_REG_HOLDING_START_CONTROLLER + 78) // Complex vector decoupling controller Q-format select
#define CVKI2D									(S_REG_HOLDING_START_CONTROLLER + 79) // Complex vector decoupling controller D-axis KI2 coefficient
#define CVKI2Q									(S_REG_HOLDING_START_CONTROLLER + 80) // Complex vector decoupling controller Q-axis KI2 coefficient
#define CVK1									(S_REG_HOLDING_START_CONTROLLER + 81) // Complex vector decoupling controller coefficient 1
#define CVK2									(S_REG_HOLDING_START_CONTROLLER + 82) // Complex vector decoupling controller coefficient 2
#define CVK3									(S_REG_HOLDING_START_CONTROLLER + 83) // Complex vector decoupling controller coefficient 3
#define CVDK4									(S_REG_HOLDING_START_CONTROLLER + 84) // Complex vector decoupling controller coefficient 4
#define CVQK4									(S_REG_HOLDING_START_CONTROLLER + 85) // Complex vector decoupling controller coefficient 4
#define CVDK5									(S_REG_HOLDING_START_CONTROLLER + 86) // Complex vector decoupling controller coefficient 5
#define CVQK5									(S_REG_HOLDING_START_CONTROLLER + 87) // Complex vector decoupling controller coefficient 5
#define CFR										(S_REG_HOLDING_START_CONTROLLER + 88) // Current loop feedforward coefficient

#define DKP										(S_REG_HOLDING_START_CONTROLLER + 89) // D-axis KP, applicable to complex vector controller
#define DKI										(S_REG_HOLDING_START_CONTROLLER + 90) // D-axis KI, applicable to complex vector controller
#define QKP										(S_REG_HOLDING_START_CONTROLLER + 91) // Q-axis KP, applicable to complex vector controller
#define QKI										(S_REG_HOLDING_START_CONTROLLER + 92) // Q-axis KI, applicable to complex vector controller

#define FEEDBACKMODE                            (S_REG_HOLDING_START_CONTROLLER + 93) // Full closed-loop mode: 0=inner loop, 1=outer loop, 2=switch
#define MIXERRMAXVAL_L                          (S_REG_HOLDING_START_CONTROLLER + 94) // Alarm when inner/outer loop deviation difference exceeds this value (low)
#define MIXERRMAXVAL_H                          (S_REG_HOLDING_START_CONTROLLER + 95) // Alarm when inner/outer loop deviation difference exceeds this value (high)
#define MIXERRCLRRPM                            (S_REG_HOLDING_START_CONTROLLER + 96) // Mix error clear turn count
#define LOADFEEDPULSE_L                         (S_REG_HOLDING_START_CONTROLLER + 97) // External encoder pulse count per motor revolution (low)
#define LOADFEEDPULSE_H                         (S_REG_HOLDING_START_CONTROLLER + 98) // External encoder pulse count per motor revolution (high)
#define LOADFEEDLPFFREQ                         (S_REG_HOLDING_START_CONTROLLER + 99) // Outer loop LPF (0.1Hz)

//************** Torque filter parameters S_REG_HOLDING_INDEX_OUTFILT (6) **************//
// 4 Output Filter
#define OUTFILTCTRL								(S_REG_HOLDING_START_OUTFILT + 0) // torqueFilter type
#define OUTFILT1HZ1								(S_REG_HOLDING_START_OUTFILT + 1) // Torque filter 1 parameter 1, e.g. frequency (0.1Hz)
#define OUTFILT1HZ2								(S_REG_HOLDING_START_OUTFILT + 2) // Torque filter 1 parameter 2, e.g. damping coefficient
#define OUTFILT1HZ3								(S_REG_HOLDING_START_OUTFILT + 3) // Torque filter 1 parameter 3, e.g. filter depth
#define OUTFILT1HZ4								(S_REG_HOLDING_START_OUTFILT + 4) // Torque filter 1 parameter 4, e.g. damping (denominator)
#define OUTFILT2HZ1								(S_REG_HOLDING_START_OUTFILT + 5) // Torque filter 2 parameters, same format as filter 1
#define OUTFILT2HZ2								(S_REG_HOLDING_START_OUTFILT + 6)
#define OUTFILT2HZ3								(S_REG_HOLDING_START_OUTFILT + 7)
#define OUTFILT2HZ4								(S_REG_HOLDING_START_OUTFILT + 8)
#define OUTFILT3HZ1								(S_REG_HOLDING_START_OUTFILT + 9) // Torque filter 3 parameters
#define OUTFILT3HZ2								(S_REG_HOLDING_START_OUTFILT + 10)
#define OUTFILT3HZ3								(S_REG_HOLDING_START_OUTFILT + 11)
#define OUTFILT3HZ4								(S_REG_HOLDING_START_OUTFILT + 12)
#define OUTFILT4HZ1								(S_REG_HOLDING_START_OUTFILT + 13) // Torque filter 4 parameters
#define OUTFILT4HZ2								(S_REG_HOLDING_START_OUTFILT + 14)
#define OUTFILT4HZ3								(S_REG_HOLDING_START_OUTFILT + 15)
#define OUTFILT4HZ4								(S_REG_HOLDING_START_OUTFILT + 16)

#define OUTFILTQFAC								(S_REG_HOLDING_START_OUTFILT + 17) // Torque filter coefficient Q value

#define OUT1FILT1B0_L							(S_REG_HOLDING_START_OUTFILT + 18) // Torque filter 1 coefficient B0, low 15-bit, applicable in velocity loop
#define OUT1FILT1B0_H							(S_REG_HOLDING_START_OUTFILT + 19) // Torque filter 1 coefficient B0, high 15-bit
#define OUT1FILT1B1_L							(S_REG_HOLDING_START_OUTFILT + 20)
#define OUT1FILT1B2_L							(S_REG_HOLDING_START_OUTFILT + 21)
#define OUT1FILT1A1_L							(S_REG_HOLDING_START_OUTFILT + 22)
#define OUT1FILT1A2_L							(S_REG_HOLDING_START_OUTFILT + 23)
#define OUT1FILT1B1_H							(S_REG_HOLDING_START_OUTFILT + 24)
#define OUT1FILT1B2_H							(S_REG_HOLDING_START_OUTFILT + 25)
#define OUT1FILT1A1_H							(S_REG_HOLDING_START_OUTFILT + 26)
#define OUT1FILT1A2_H							(S_REG_HOLDING_START_OUTFILT + 27)

#define OUT1FILT2B0_L							(S_REG_HOLDING_START_OUTFILT + 28)
#define OUT1FILT2B0_H							(S_REG_HOLDING_START_OUTFILT + 29)
#define OUT1FILT2B1_L							(S_REG_HOLDING_START_OUTFILT + 30)
#define OUT1FILT2B2_L							(S_REG_HOLDING_START_OUTFILT + 31)
#define OUT1FILT2A1_L							(S_REG_HOLDING_START_OUTFILT + 32)
#define OUT1FILT2A2_L							(S_REG_HOLDING_START_OUTFILT + 33)
#define OUT1FILT2B1_H							(S_REG_HOLDING_START_OUTFILT + 34)
#define OUT1FILT2B2_H							(S_REG_HOLDING_START_OUTFILT + 35)
#define OUT1FILT2A1_H							(S_REG_HOLDING_START_OUTFILT + 36)
#define OUT1FILT2A2_H							(S_REG_HOLDING_START_OUTFILT + 37)

#define OUT1FILT3B0_L							(S_REG_HOLDING_START_OUTFILT + 38)
#define OUT1FILT3B0_H							(S_REG_HOLDING_START_OUTFILT + 39)
#define OUT1FILT3B1_L							(S_REG_HOLDING_START_OUTFILT + 40)
#define OUT1FILT3B2_L							(S_REG_HOLDING_START_OUTFILT + 41)
#define OUT1FILT3A1_L							(S_REG_HOLDING_START_OUTFILT + 42)
#define OUT1FILT3A2_L							(S_REG_HOLDING_START_OUTFILT + 43)
#define OUT1FILT3B1_H							(S_REG_HOLDING_START_OUTFILT + 44)
#define OUT1FILT3B2_H							(S_REG_HOLDING_START_OUTFILT + 45)
#define OUT1FILT3A1_H							(S_REG_HOLDING_START_OUTFILT + 46)
#define OUT1FILT3A2_H							(S_REG_HOLDING_START_OUTFILT + 47)

#define OUT1FILT4B0_L							(S_REG_HOLDING_START_OUTFILT + 48)
#define OUT1FILT4B0_H							(S_REG_HOLDING_START_OUTFILT + 49)
#define OUT1FILT4B1_L							(S_REG_HOLDING_START_OUTFILT + 50)
#define OUT1FILT4B2_L							(S_REG_HOLDING_START_OUTFILT + 51)
#define OUT1FILT4A1_L							(S_REG_HOLDING_START_OUTFILT + 52)
#define OUT1FILT4A2_L							(S_REG_HOLDING_START_OUTFILT + 53)
#define OUT1FILT4B1_H							(S_REG_HOLDING_START_OUTFILT + 54)
#define OUT1FILT4B2_H							(S_REG_HOLDING_START_OUTFILT + 55)
#define OUT1FILT4A1_H							(S_REG_HOLDING_START_OUTFILT + 56)
#define OUT1FILT4A2_H							(S_REG_HOLDING_START_OUTFILT + 57)

#define OUT2FILT1B0_L							(S_REG_HOLDING_START_OUTFILT + 58) // Torque filter 1 coefficient B0, low 15-bit, applicable in current loop
#define OUT2FILT1B0_H							(S_REG_HOLDING_START_OUTFILT + 59)
#define OUT2FILT1B1_L							(S_REG_HOLDING_START_OUTFILT + 60)
#define OUT2FILT1B2_L							(S_REG_HOLDING_START_OUTFILT + 61)
#define OUT2FILT1A1_L							(S_REG_HOLDING_START_OUTFILT + 62)
#define OUT2FILT1A2_L							(S_REG_HOLDING_START_OUTFILT + 63)
#define OUT2FILT1B1_H							(S_REG_HOLDING_START_OUTFILT + 64)
#define OUT2FILT1B2_H							(S_REG_HOLDING_START_OUTFILT + 65)
#define OUT2FILT1A1_H							(S_REG_HOLDING_START_OUTFILT + 66)
#define OUT2FILT1A2_H							(S_REG_HOLDING_START_OUTFILT + 67)

#define OUT2FILT2B0_L							(S_REG_HOLDING_START_OUTFILT + 68)
#define OUT2FILT2B0_H							(S_REG_HOLDING_START_OUTFILT + 69)
#define OUT2FILT2B1_L							(S_REG_HOLDING_START_OUTFILT + 70)
#define OUT2FILT2B2_L							(S_REG_HOLDING_START_OUTFILT + 71)
#define OUT2FILT2A1_L							(S_REG_HOLDING_START_OUTFILT + 72)
#define OUT2FILT2A2_L							(S_REG_HOLDING_START_OUTFILT + 73)
#define OUT2FILT2B1_H							(S_REG_HOLDING_START_OUTFILT + 74)
#define OUT2FILT2B2_H							(S_REG_HOLDING_START_OUTFILT + 75)
#define OUT2FILT2A1_H							(S_REG_HOLDING_START_OUTFILT + 76)
#define OUT2FILT2A2_H							(S_REG_HOLDING_START_OUTFILT + 77)

#define OUT2FILT3B0_L							(S_REG_HOLDING_START_OUTFILT + 78)
#define OUT2FILT3B0_H							(S_REG_HOLDING_START_OUTFILT + 79)
#define OUT2FILT3B1_L							(S_REG_HOLDING_START_OUTFILT + 80)
#define OUT2FILT3B2_L							(S_REG_HOLDING_START_OUTFILT + 81)
#define OUT2FILT3A1_L							(S_REG_HOLDING_START_OUTFILT + 82)
#define OUT2FILT3A2_L							(S_REG_HOLDING_START_OUTFILT + 83)
#define OUT2FILT3B1_H							(S_REG_HOLDING_START_OUTFILT + 84)
#define OUT2FILT3B2_H							(S_REG_HOLDING_START_OUTFILT + 85)
#define OUT2FILT3A1_H							(S_REG_HOLDING_START_OUTFILT + 86)
#define OUT2FILT3A2_H							(S_REG_HOLDING_START_OUTFILT + 87)

#define OUT2FILT4B0_L							(S_REG_HOLDING_START_OUTFILT + 88)
#define OUT2FILT4B0_H							(S_REG_HOLDING_START_OUTFILT + 89)
#define OUT2FILT4B1_L							(S_REG_HOLDING_START_OUTFILT + 90)
#define OUT2FILT4B2_L							(S_REG_HOLDING_START_OUTFILT + 91)
#define OUT2FILT4A1_L							(S_REG_HOLDING_START_OUTFILT + 92)
#define OUT2FILT4A2_L							(S_REG_HOLDING_START_OUTFILT + 93)
#define OUT2FILT4B1_H							(S_REG_HOLDING_START_OUTFILT + 94)
#define OUT2FILT4B2_H							(S_REG_HOLDING_START_OUTFILT + 95)
#define OUT2FILT4A1_H							(S_REG_HOLDING_START_OUTFILT + 96)
#define OUT2FILT4A2_H							(S_REG_HOLDING_START_OUTFILT + 97)

//************** Limit parameters S_REG_HOLDING_INDEX_LIMIT (7) **************//
#define DOUTMAX									(S_REG_HOLDING_START_LIMIT + 0) // D-axis max limit value, output duty cycle (_Q15)
#define DOUTMIN									(S_REG_HOLDING_START_LIMIT + 1) // D-axis min limit value
#define QOUTMAX									(S_REG_HOLDING_START_LIMIT + 2) // Q-axis max limit value
#define QOUTMIN									(S_REG_HOLDING_START_LIMIT + 3) // Q-axis min limit value
#define VOUTMAX									(S_REG_HOLDING_START_LIMIT + 4) // Velocity loop output max limit
#define VOUTMIN									(S_REG_HOLDING_START_LIMIT + 5) // Velocity loop output min limit
#define POUTMAX									(S_REG_HOLDING_START_LIMIT + 6) // Position loop output max limit (_Q15)
#define POUTMIN									(S_REG_HOLDING_START_LIMIT + 7) // Position loop output min limit (_Q15)
#define PEINPOSRANGE							(S_REG_HOLDING_START_LIMIT + 8) // In-position range
#define PEINPOSTIME								(S_REG_HOLDING_START_LIMIT + 9) // In-position time window
#define PEMAX_L									(S_REG_HOLDING_START_LIMIT + 10) // Position following error, count
#define PEMAX_H									(S_REG_HOLDING_START_LIMIT + 11) // 
#define PEMAXTIME								(S_REG_HOLDING_START_LIMIT + 12) // Position following error detection time, count
#define VEMAX									(S_REG_HOLDING_START_LIMIT + 13) // Velocity following error, count
#define VEMAXTIME								(S_REG_HOLDING_START_LIMIT + 14) // Velocity following error detection time, checked once per velocity loop
#define OVERSPEED								(S_REG_HOLDING_START_LIMIT + 15) // Overspeed, count
#define OVERSPEEDTIME							(S_REG_HOLDING_START_LIMIT + 16) // Overspeed detection time, checked once per carrier period
#define PEAKCURTIME								(S_REG_HOLDING_START_LIMIT + 17) // Motor peak overcurrent window time, checked every 1 ms
#define RMSCURTIME								(S_REG_HOLDING_START_LIMIT + 18) // Motor RMS overcurrent detection time, checked every 1 ms
#define PHASELOSSCMDCUR							(S_REG_HOLDING_START_LIMIT + 19) // Phase loss current command threshold
#define PHASELOSSACTCUR							(S_REG_HOLDING_START_LIMIT + 20) // Phase loss phase current threshold
#define PHASELOSSANGLE							(S_REG_HOLDING_START_LIMIT + 21) // Phase loss electrical angle change range
#define STALLCUR								(S_REG_HOLDING_START_LIMIT + 22) // Stall current
#define STALLVEL								(S_REG_HOLDING_START_LIMIT + 23) // Stall detection time, checked once per carrier period
#define STALLTIME								(S_REG_HOLDING_START_LIMIT + 24) // Phase loss current value, count  
#define OVERVOLTAGE								(S_REG_HOLDING_START_LIMIT + 25) // Overvoltage protection value
#define OVERVOLTIME								(S_REG_HOLDING_START_LIMIT + 26) // Overvoltage protection window time, checked every 1 ms
#define UNDERVOLTAGE							(S_REG_HOLDING_START_LIMIT + 27) // Undervoltage protection value
#define UNDERVOLTIME							(S_REG_HOLDING_START_LIMIT + 28) // Undervoltage protection window time, checked every 1 ms
#define MOTORTHERMTRIP   						(S_REG_HOLDING_START_LIMIT + 29) // Motor over-temperature fault threshold
#define MOTORTHERMCLEAR   						(S_REG_HOLDING_START_LIMIT + 30) // Motor over-temperature fault clear threshold, not used
#define DRIVETHERMTRIP							(S_REG_HOLDING_START_LIMIT + 31) // Driver over-temperature fault threshold
#define THERMTIME								(S_REG_HOLDING_START_LIMIT + 32) // Over-temperature window time, checked every 1 ms
#define MAININTTIME								(S_REG_HOLDING_START_LIMIT + 33) // Main interrupt timeout window, not used
#define AUXINTDELAY								(S_REG_HOLDING_START_LIMIT + 34) // Delay from sub-interrupt trigger to execution
#define POSLIMMODE								(S_REG_HOLDING_START_LIMIT + 35) // Software limit switch
#define POSLIMPOS_L								(S_REG_HOLDING_START_LIMIT + 36) // Software forward limit, low 16-bit
#define POSLIMPOS_H								(S_REG_HOLDING_START_LIMIT + 37) // Software reverse limit, low 16-bit
#define POSLIMNEG_L								(S_REG_HOLDING_START_LIMIT + 38) //
#define POSLIMNEG_H								(S_REG_HOLDING_START_LIMIT + 39) // Software reverse limit, low 16-bit
#define CUROFFJITTER							(S_REG_HOLDING_START_LIMIT + 40) // Current offset allowable range
#define HALLINVALIDTIME							(S_REG_HOLDING_START_LIMIT + 41) // Hall signal anomaly detection window, checked every 1 ms
#define FAULTMASK0								(S_REG_HOLDING_START_LIMIT + 42) // Fault mask: 1=Fault, 0=Warning
#define FAULTMASK1								(S_REG_HOLDING_START_LIMIT + 43) // Fault mask 1: 1=Fault, 0=Warning
#define FOLDBACKEN                              (S_REG_HOLDING_START_LIMIT + 44) // Current foldback enable
#define FBDELAYTIME_L                           (S_REG_HOLDING_START_LIMIT + 45) // Current foldback peak current delay time (ms)
#define FBDELAYTIME_H                           (S_REG_HOLDING_START_LIMIT + 46)
#define FBRECOVERYTIME_L                        (S_REG_HOLDING_START_LIMIT + 47) // Current foldback recovery time (ms)
#define FBRECOVERYTIME_H                        (S_REG_HOLDING_START_LIMIT + 48)
#define FBTIMECONSTANT_L                        (S_REG_HOLDING_START_LIMIT + 49) // Current foldback time constant (ms)
#define FBTIMECONSTANT_H                        (S_REG_HOLDING_START_LIMIT + 50)
#define FBFAULTHOLDVALUE                        (S_REG_HOLDING_START_LIMIT + 51) // Current foldback fault current threshold
#define FBWARNHOLDVAL                           (S_REG_HOLDING_START_LIMIT + 52) // Current foldback warning current threshold

//************** Motion parameters S_REG_HOLDING_INDEX_MOTION (8) **************//
// Position mode T/S profile
#define PROFILECTRL								(S_REG_HOLDING_START_MOTION + 0) // Motion control, see below for details
#define PROFILEMOVDIS_L							(S_REG_HOLDING_START_MOTION + 1) // Motion profile target position, low 16-bit
#define PROFILEMOVDIS_H							(S_REG_HOLDING_START_MOTION + 2) // 
#define PROFILEMOVDIS2_L						(S_REG_HOLDING_START_MOTION + 3) // Motion profile target position 2, low 16-bit
#define PROFILEMOVDIS2_H						(S_REG_HOLDING_START_MOTION + 4) // 
#define PROFILEMAXVEL							(S_REG_HOLDING_START_MOTION + 5) // Motion profile max velocity (rpm or mm/s)
#define PROFILEMAXACC_L							(S_REG_HOLDING_START_MOTION + 6) // Motion profile max acceleration (rps² or mm/s²)
#define PROFILEMAXACC_H							(S_REG_HOLDING_START_MOTION + 7) // 
#define PROFILEMAXJERK_L						(S_REG_HOLDING_START_MOTION + 8) // Motion profile max jerk (rps³ or mm/s³)
#define PROFILEMAXJERK_H						(S_REG_HOLDING_START_MOTION + 9) // 
#define PROFILEDWELLTIME						(S_REG_HOLDING_START_MOTION + 10) // Motion profile dwell time (ms)
#define WAVETYPE								(S_REG_HOLDING_START_MOTION + 11) // Velocity/current loop waveform type
// velocity/current loop Trap Wave
#define WAVECMD									(S_REG_HOLDING_START_MOTION + 12) // Velocity/current loop command value (count)
#define WAVEINC									(S_REG_HOLDING_START_MOTION + 13) // Velocity/current loop increment value (count)
#define WAVEDWELLTIME							(S_REG_HOLDING_START_MOTION + 14) // Trapezoidal wave dwell time
// sin output
#define SINFRE									(S_REG_HOLDING_START_MOTION + 15) // Sine signal frequency
#define SINVS									(S_REG_HOLDING_START_MOTION + 16) // Sine signal amplitude
#define SINPHASE								(S_REG_HOLDING_START_MOTION + 17) // Sine signal phase
// pulse and direction
#define GEARIN									(S_REG_HOLDING_START_MOTION + 18) // Gear ratio numerator
#define GEAROUT									(S_REG_HOLDING_START_MOTION + 19) // Gear ratio denominator
// home
#define HOMEMETHOD								(S_REG_HOLDING_START_MOTION + 20) // Homing method: 0=HardStop, 1=HardStopOutToIndex
#define HOMETIMEOUT								(S_REG_HOLDING_START_MOTION + 21) // Homing timeout (ms)
#define HOMEOFFSET_L							(S_REG_HOLDING_START_MOTION + 22) // Home zero offset - Zero position = Home Attained Position + Home Offset
#define HOMEOFFSET_H							(S_REG_HOLDING_START_MOTION + 23) // 
#define HOMESPEED1								(S_REG_HOLDING_START_MOTION + 24) // Homing speed when searching for limit/home switch/hard stop (rpm or mm/s)
#define HOMESPEED2								(S_REG_HOLDING_START_MOTION + 25) // Homing speed when searching for Z Index (rpm or mm/s)
#define HOMEACC									(S_REG_HOLDING_START_MOTION + 26) // Homing acceleration (rps² or mm/s²)
#define HOMEBLOCKCURRENT						(S_REG_HOLDING_START_MOTION + 27) // Hard stop current detection threshold (A)
#define HOMEBLOCKSPEED							(S_REG_HOLDING_START_MOTION + 28) // Hard stop speed detection threshold (count)
#define HOMEBLOCKTIME							(S_REG_HOLDING_START_MOTION + 29) // Hard stop detection time (ms)

#define FBNUM_L									(S_REG_HOLDING_START_MOTION + 30) // Fieldbus unit conversion numerator
#define FBNUM_H									(S_REG_HOLDING_START_MOTION + 31) // Fieldbus unit conversion denominator
#define FBDEN									(S_REG_HOLDING_START_MOTION + 32) //

#define SWEEPSTARTFREQ							(S_REG_HOLDING_START_MOTION + 33) // Sweep start frequency
#define SWEEPENDFREQ							(S_REG_HOLDING_START_MOTION + 34) // Sweep end frequency
#define SWEEPPOINT								(S_REG_HOLDING_START_MOTION + 35) // Sweep Chirp frequency points
#define SWEEPAMP								(S_REG_HOLDING_START_MOTION + 36) // Sweep amplitude

#define WAVEREPTIMES							(S_REG_HOLDING_START_MOTION + 37) // Velocity/current trapezoid repeat count
#define WAVEPOSTIME								(S_REG_HOLDING_START_MOTION + 38) // Velocity/current trapezoid forward constant-speed time
#define WAVENEGTIME								(S_REG_HOLDING_START_MOTION + 39) // Velocity/current trapezoid reverse constant-speed time

//************** Force control mode parameters S_REG_HOLDING_INDEX_FORCECTRL (9) **************//
#define FCMOD									(S_REG_HOLDING_START_FORCECTRL + 0) // Force control function mode select
#define FCINITPOS_L								(S_REG_HOLDING_START_FORCECTRL + 1) // Force control mode initial position
#define FCINITPOS_H								(S_REG_HOLDING_START_FORCECTRL + 2)
#define FCSAFPOS_L								(S_REG_HOLDING_START_FORCECTRL + 3) // Force control mode safe position
#define FCSAFPOS_H								(S_REG_HOLDING_START_FORCECTRL + 4)
#define FCSLOWSPD								(S_REG_HOLDING_START_FORCECTRL + 5) // Force control mode slow search speed
#define FCSLOWACC								(S_REG_HOLDING_START_FORCECTRL + 6) // Force control mode slow search acceleration
#define FCTHRESHOLD								(S_REG_HOLDING_START_FORCECTRL + 7) // Force control mode contact detection threshold
#define FCCURCMD								(S_REG_HOLDING_START_FORCECTRL + 8) // Force control mode target force
#define FCCURINC								(S_REG_HOLDING_START_FORCECTRL + 9) // Force control mode target forceincrement value
#define FCSAFPOSTIME							(S_REG_HOLDING_START_FORCECTRL + 10) // Force control mode wait time after reaching safe position
#define FCREACHTIME								(S_REG_HOLDING_START_FORCECTRL + 11) // Force control mode contact position wait time
#define FCHOLDTIME								(S_REG_HOLDING_START_FORCECTRL + 12) // Force control mode hold time
#define FCDWELLTIME								(S_REG_HOLDING_START_FORCECTRL + 13) // Force control mode dwell time after process completion
#define FCKP									(S_REG_HOLDING_START_FORCECTRL + 14) // Closed-loop force control proportional gain
#define FCKI									(S_REG_HOLDING_START_FORCECTRL + 15) // Closed-loop force control integral gain
#define FCERRVALUE								(S_REG_HOLDING_START_FORCECTRL + 16) // Force control protection pressure threshold
#define FCCOMPMODE                              (S_REG_HOLDING_START_FORCECTRL + 17) // Force control compensation mode
#define FCCLRCNT                                (S_REG_HOLDING_START_FORCECTRL + 18) // Force control sensor clear timer
#define FCPEVALUE                               (S_REG_HOLDING_START_FORCECTRL + 19) // Force control fast descent position protection threshold

//************** Electric screwdriver mode parameters S_REG_HOLDING_INDEX_FORCECTRL  **************//
#define ESCMOD							        (S_REG_HOLDING_START_FORCECTRL + 20) // Electric screwdriver mode: 0=disable, 1=enable
#define ESCERRCODE                              (S_REG_HOLDING_START_FORCECTRL + 21) // Electric screwdriver fault code display
#define ESCSAMPLETIME                           (S_REG_HOLDING_START_FORCECTRL + 22) // Electric screwdriver sampling window 1ms
#define ESCAXISNUM                              (S_REG_HOLDING_START_FORCECTRL + 23) // Electric screwdriver axis number

#define ESCLOWSPD1                              (S_REG_HOLDING_START_FORCECTRL + 24) // Electric screwdriver thread-engaging detection speed, rpm
#define ESCLOWTOQHOLD1                          (S_REG_HOLDING_START_FORCECTRL + 25) // Electric screwdriver thread-engaging current threshold, A
#define ESCRATIOHOLD1                           (S_REG_HOLDING_START_FORCECTRL + 26) // Electric screwdriver thread-engaging success detection ratio, 0.01A/p
#define ESCNEARCNTHOLD1                         (S_REG_HOLDING_START_FORCECTRL + 27) // Electric screwdriver thread-engaging success detection window, 1ms
#define ESCNEAROVERTIMEHOLD1                    (S_REG_HOLDING_START_FORCECTRL + 28) // Electric screwdriver thread-engaging timeout fault window, 1ms
#define ESCLOWTOQLMT1                           (S_REG_HOLDING_START_FORCECTRL + 29) // Electric screwdriver thread-engaging torque limit, A
#define ESCHIGHPOS1_L                           (S_REG_HOLDING_START_FORCECTRL + 30) // Electric screwdriver screw-in position turns (low), mechanical angle
#define ESCHIGHPOS1_H						    (S_REG_HOLDING_START_FORCECTRL + 31) // Electric screwdriver screw-in position turns (high), mechanical angle
#define ESCHIGHSPD1                             (S_REG_HOLDING_START_FORCECTRL + 32) // Electric screwdriver screw-in high speed, rpm
#define ESCHIGHTOQLMT1                          (S_REG_HOLDING_START_FORCECTRL + 33) // Electric screwdriver screw-in torque limit, A
#define ESCHIGHTOQHOLD1                         (S_REG_HOLDING_START_FORCECTRL + 34) // Electric screwdriver screw-in current threshold, A
#define ESCENTERCNTHOLD1                        (S_REG_HOLDING_START_FORCECTRL + 35) // Electric screwdriver screw-in success detection window, 1ms
#define ESCENTEROVERTIMEHOLD1                   (S_REG_HOLDING_START_FORCECTRL + 36) // Electric screwdriver screw-in timeout fault window, 1ms
#define ESCFINALSPD1                            (S_REG_HOLDING_START_FORCECTRL + 37) // Electric screwdriver tightening continuous speed, rpm
#define ESCFINALTOQHOLD1                        (S_REG_HOLDING_START_FORCECTRL + 38) // Electric screwdriver tightening current threshold, A
#define ESCFINALTOQLMT1                         (S_REG_HOLDING_START_FORCECTRL + 39) // Electric screwdriver tightening torque limit, A
#define ESCFINALCNTHOLD1                        (S_REG_HOLDING_START_FORCECTRL + 40) // Electric screwdriver tightening success detection window, 1ms
#define ESCFINALSPDHOLD1                        (S_REG_HOLDING_START_FORCECTRL + 41) // Electric screwdriver tightening zero-speed threshold, rpm
#define ESCFINALOVERTIMEHOLD1                   (S_REG_HOLDING_START_FORCECTRL + 42) // Electric screwdriver tightening timeout fault window, 1ms
#define ESCACTPOS1_L                            (S_REG_HOLDING_START_FORCECTRL + 43) // Electric screwdriver tightening success position (low), mechanical angle
#define ESCACTPOS1_H                            (S_REG_HOLDING_START_FORCECTRL + 44) // Electric screwdriver tightening success position (high), mechanical angle
#define ESCLOWACC1                              (S_REG_HOLDING_START_FORCECTRL + 45) // Electric screwdriver thread-engaging speed command acceleration
#define ESCHIGHACC1                             (S_REG_HOLDING_START_FORCECTRL + 46) // Electric screwdriver screw-in speed command acceleration
#define ESCHOLDACC1                             (S_REG_HOLDING_START_FORCECTRL + 47) // Electric screwdriver tightening speed command acceleration

#define ESCLOWSPD2                              (S_REG_HOLDING_START_FORCECTRL + 48) // Electric screwdriver thread-engaging detection speed, rpm
#define ESCLOWTOQHOLD2                          (S_REG_HOLDING_START_FORCECTRL + 49) // Electric screwdriver thread-engaging current threshold, A
#define ESCRATIOHOLD2                           (S_REG_HOLDING_START_FORCECTRL + 50) // Electric screwdriver thread-engaging success detection ratio, 0.01A/p
#define ESCNEARCNTHOLD2                         (S_REG_HOLDING_START_FORCECTRL + 51) // Electric screwdriver thread-engaging success detection window, 1ms
#define ESCNEAROVERTIMEHOLD2                    (S_REG_HOLDING_START_FORCECTRL + 52) // Electric screwdriver thread-engaging timeout fault window, 1ms
#define ESCLOWTOQLMT2                           (S_REG_HOLDING_START_FORCECTRL + 53) // Electric screwdriver thread-engaging torque limit, A
#define ESCHIGHPOS2_L                           (S_REG_HOLDING_START_FORCECTRL + 54) // Electric screwdriver screw-in position turns (low), mechanical angle
#define ESCHIGHPOS2_H						    (S_REG_HOLDING_START_FORCECTRL + 55) // Electric screwdriver screw-in position turns (high), mechanical angle
#define ESCHIGHSPD2                             (S_REG_HOLDING_START_FORCECTRL + 56) // Electric screwdriver screw-in high speed, rpm
#define ESCHIGHTOQLMT2                          (S_REG_HOLDING_START_FORCECTRL + 57) // Electric screwdriver screw-in torque limit, A
#define ESCHIGHTOQHOLD2                         (S_REG_HOLDING_START_FORCECTRL + 58) // Electric screwdriver screw-in current threshold, A
#define ESCENTERCNTHOLD2                        (S_REG_HOLDING_START_FORCECTRL + 59) // Electric screwdriver screw-in success detection window, 1ms
#define ESCENTEROVERTIMEHOLD2                   (S_REG_HOLDING_START_FORCECTRL + 60) // Electric screwdriver screw-in timeout fault window, 1ms
#define ESCFINALSPD2                            (S_REG_HOLDING_START_FORCECTRL + 61) // Electric screwdriver tightening continuous speed, rpm
#define ESCFINALTOQHOLD2                        (S_REG_HOLDING_START_FORCECTRL + 62) // Electric screwdriver tightening current threshold, A
#define ESCFINALTOQLMT2                         (S_REG_HOLDING_START_FORCECTRL + 63) // Electric screwdriver tightening torque limit, A
#define ESCFINALCNTHOLD2                        (S_REG_HOLDING_START_FORCECTRL + 64) // Electric screwdriver tightening success detection window, 1ms
#define ESCFINALSPDHOLD2                        (S_REG_HOLDING_START_FORCECTRL + 65) // Electric screwdriver tightening zero-speed threshold, rpm
#define ESCFINALOVERTIMEHOLD2                   (S_REG_HOLDING_START_FORCECTRL + 66) // Electric screwdriver tightening timeout fault window, 1ms
#define ESCACTPOS2_L                            (S_REG_HOLDING_START_FORCECTRL + 67) // Electric screwdriver tightening success position (low), mechanical angle
#define ESCACTPOS2_H                            (S_REG_HOLDING_START_FORCECTRL + 68) // Electric screwdriver tightening success position (high), mechanical angle
#define ESCLOWACC2                              (S_REG_HOLDING_START_FORCECTRL + 69) // Electric screwdriver thread-engaging speed command acceleration
#define ESCHIGHACC2                             (S_REG_HOLDING_START_FORCECTRL + 70) // Electric screwdriver screw-in speed command acceleration
#define ESCHOLDACC2                             (S_REG_HOLDING_START_FORCECTRL + 71) // Electric screwdriver tightening speed command acceleration

#define ESCLOWSPD3                              (S_REG_HOLDING_START_FORCECTRL + 72) // Electric screwdriver thread-engaging detection speed, rpm
#define ESCLOWTOQHOLD3                          (S_REG_HOLDING_START_FORCECTRL + 73) // Electric screwdriver thread-engaging current threshold, A
#define ESCRATIOHOLD3                           (S_REG_HOLDING_START_FORCECTRL + 74) // Electric screwdriver thread-engaging success detection ratio, 0.01A/p
#define ESCNEARCNTHOLD3                         (S_REG_HOLDING_START_FORCECTRL + 75) // Electric screwdriver thread-engaging success detection window, 1ms
#define ESCNEAROVERTIMEHOLD3                    (S_REG_HOLDING_START_FORCECTRL + 76) // Electric screwdriver thread-engaging timeout fault window, 1ms
#define ESCLOWTOQLMT3                           (S_REG_HOLDING_START_FORCECTRL + 77) // Electric screwdriver thread-engaging torque limit, A
#define ESCHIGHPOS3_L                           (S_REG_HOLDING_START_FORCECTRL + 78) // Electric screwdriver screw-in position turns (low), mechanical angle
#define ESCHIGHPOS3_H						    (S_REG_HOLDING_START_FORCECTRL + 79) // Electric screwdriver screw-in position turns (high), mechanical angle
#define ESCHIGHSPD3                             (S_REG_HOLDING_START_FORCECTRL + 80) // Electric screwdriver screw-in high speed, rpm
#define ESCHIGHTOQLMT3                          (S_REG_HOLDING_START_FORCECTRL + 81) // Electric screwdriver screw-in torque limit, A
#define ESCHIGHTOQHOLD3                         (S_REG_HOLDING_START_FORCECTRL + 82) // Electric screwdriver screw-in current threshold, A
#define ESCENTERCNTHOLD3                        (S_REG_HOLDING_START_FORCECTRL + 83) // Electric screwdriver screw-in success detection window, 1ms
#define ESCENTEROVERTIMEHOLD3                   (S_REG_HOLDING_START_FORCECTRL + 84) // Electric screwdriver screw-in timeout fault window, 1ms
#define ESCFINALSPD3                            (S_REG_HOLDING_START_FORCECTRL + 85) // Electric screwdriver tightening continuous speed, rpm
#define ESCFINALTOQHOLD3                        (S_REG_HOLDING_START_FORCECTRL + 86) // Electric screwdriver tightening current threshold, A
#define ESCFINALTOQLMT3                         (S_REG_HOLDING_START_FORCECTRL + 87) // Electric screwdriver tightening torque limit, A
#define ESCFINALCNTHOLD3                        (S_REG_HOLDING_START_FORCECTRL + 88) // Electric screwdriver tightening success detection window, 1ms
#define ESCFINALSPDHOLD3                        (S_REG_HOLDING_START_FORCECTRL + 89) // Electric screwdriver tightening zero-speed threshold, rpm
#define ESCFINALOVERTIMEHOLD3                   (S_REG_HOLDING_START_FORCECTRL + 90) // Electric screwdriver tightening timeout fault window, 1ms
#define ESCACTPOS3_L                            (S_REG_HOLDING_START_FORCECTRL + 91) // Electric screwdriver tightening success position (low), mechanical angle
#define ESCACTPOS3_H                            (S_REG_HOLDING_START_FORCECTRL + 92) // Electric screwdriver tightening success position (high), mechanical angle
#define ESCLOWACC3                              (S_REG_HOLDING_START_FORCECTRL + 93) // Electric screwdriver thread-engaging speed command acceleration
#define ESCHIGHACC3                             (S_REG_HOLDING_START_FORCECTRL + 94) // Electric screwdriver screw-in speed command acceleration
#define ESCHOLDACC3                             (S_REG_HOLDING_START_FORCECTRL + 95) // Electric screwdriver tightening speed command acceleration

#define ESCLOWSPD4                              (S_REG_HOLDING_START_FORCECTRL + 96) // Electric screwdriver thread-engaging detection speed, rpm
#define ESCLOWTOQHOLD4                          (S_REG_HOLDING_START_FORCECTRL + 97) // Electric screwdriver thread-engaging current threshold, A
#define ESCRATIOHOLD4                           (S_REG_HOLDING_START_FORCECTRL + 98) // Electric screwdriver thread-engaging success detection ratio, 0.01A/p
#define ESCNEARCNTHOLD4                         (S_REG_HOLDING_START_FORCECTRL + 99) // Electric screwdriver thread-engaging success detection window, 1ms
#define ESCNEAROVERTIMEHOLD4                    (S_REG_HOLDING_START_FORCECTRL + 100) // Electric screwdriver thread-engaging timeout fault window, 1ms
#define ESCLOWTOQLMT4                           (S_REG_HOLDING_START_FORCECTRL + 101) // Electric screwdriver thread-engaging torque limit, A
#define ESCHIGHPOS4_L                           (S_REG_HOLDING_START_FORCECTRL + 102) // Electric screwdriver screw-in position turns (low), mechanical angle
#define ESCHIGHPOS4_H						    (S_REG_HOLDING_START_FORCECTRL + 103) // Electric screwdriver screw-in position turns (high), mechanical angle
#define ESCHIGHSPD4                             (S_REG_HOLDING_START_FORCECTRL + 104) // Electric screwdriver screw-in high speed, rpm
#define ESCHIGHTOQLMT4                          (S_REG_HOLDING_START_FORCECTRL + 105) // Electric screwdriver screw-in torque limit, A
#define ESCHIGHTOQHOLD4                         (S_REG_HOLDING_START_FORCECTRL + 106) // Electric screwdriver screw-in current threshold, A
#define ESCENTERCNTHOLD4                        (S_REG_HOLDING_START_FORCECTRL + 107) // Electric screwdriver screw-in success detection window, 1ms
#define ESCENTEROVERTIMEHOLD4                   (S_REG_HOLDING_START_FORCECTRL + 108) // Electric screwdriver screw-in timeout fault window, 1ms
#define ESCFINALSPD4                            (S_REG_HOLDING_START_FORCECTRL + 109) // Electric screwdriver tightening continuous speed, rpm
#define ESCFINALTOQHOLD4                        (S_REG_HOLDING_START_FORCECTRL + 110) // Electric screwdriver tightening current threshold, A
#define ESCFINALTOQLMT4                         (S_REG_HOLDING_START_FORCECTRL + 111) // Electric screwdriver tightening torque limit, A
#define ESCFINALCNTHOLD4                        (S_REG_HOLDING_START_FORCECTRL + 112) // Electric screwdriver tightening success detection window, 1ms
#define ESCFINALSPDHOLD4                        (S_REG_HOLDING_START_FORCECTRL + 113) // Electric screwdriver tightening zero-speed threshold, rpm
#define ESCFINALOVERTIMEHOLD4                   (S_REG_HOLDING_START_FORCECTRL + 114) // Electric screwdriver tightening timeout fault window, 1ms
#define ESCACTPOS4_L                            (S_REG_HOLDING_START_FORCECTRL + 115) // Electric screwdriver tightening success position (low), mechanical angle
#define ESCACTPOS4_H                            (S_REG_HOLDING_START_FORCECTRL + 116) // Electric screwdriver tightening success position (high), mechanical angle
#define ESCLOWACC4                              (S_REG_HOLDING_START_FORCECTRL + 117) // Electric screwdriver thread-engaging speed command acceleration
#define ESCHIGHACC4                             (S_REG_HOLDING_START_FORCECTRL + 118) // Electric screwdriver screw-in speed command acceleration
#define ESCHOLDACC4                             (S_REG_HOLDING_START_FORCECTRL + 119) // Electric screwdriver tightening speed command acceleration

#define ESCLOWSPD5                              (S_REG_HOLDING_START_FORCECTRL + 120) // Electric screwdriver thread-engaging detection speed, rpm
#define ESCLOWTOQHOLD6                          (S_REG_HOLDING_START_FORCECTRL + 121) // Electric screwdriver thread-engaging current threshold, A
#define ESCRATIOHOLD5                           (S_REG_HOLDING_START_FORCECTRL + 122) // Electric screwdriver thread-engaging success detection ratio, 0.01A/p
#define ESCNEARCNTHOLD5                         (S_REG_HOLDING_START_FORCECTRL + 123) // Electric screwdriver thread-engaging success detection window, 1ms
#define ESCNEAROVERTIMEHOLD5                    (S_REG_HOLDING_START_FORCECTRL + 124) // Electric screwdriver thread-engaging timeout fault window, 1ms
#define ESCLOWTOQLMT5                           (S_REG_HOLDING_START_FORCECTRL + 125) // Electric screwdriver thread-engaging torque limit, A
#define ESCHIGHPOS5_L                           (S_REG_HOLDING_START_FORCECTRL + 126) // Electric screwdriver screw-in position turns (low), mechanical angle
#define ESCHIGHPOS5_H						    (S_REG_HOLDING_START_FORCECTRL + 127) // Electric screwdriver screw-in position turns (high), mechanical angle
#define ESCHIGHSPD5                             (S_REG_HOLDING_START_FORCECTRL + 128) // Electric screwdriver screw-in high speed, rpm
#define ESCHIGHTOQLMT5                          (S_REG_HOLDING_START_FORCECTRL + 129) // Electric screwdriver screw-in torque limit, A
#define ESCHIGHTOQHOLD5                         (S_REG_HOLDING_START_FORCECTRL + 130) // Electric screwdriver screw-in current threshold, A
#define ESCENTERCNTHOLD5                        (S_REG_HOLDING_START_FORCECTRL + 131) // Electric screwdriver screw-in success detection window, 1ms
#define ESCENTEROVERTIMEHOLD5                   (S_REG_HOLDING_START_FORCECTRL + 132) // Electric screwdriver screw-in timeout fault window, 1ms
#define ESCFINALSPD5                            (S_REG_HOLDING_START_FORCECTRL + 133) // Electric screwdriver tightening continuous speed, rpm
#define ESCFINALTOQHOLD5                        (S_REG_HOLDING_START_FORCECTRL + 134) // Electric screwdriver tightening current threshold, A
#define ESCFINALTOQLMT5                         (S_REG_HOLDING_START_FORCECTRL + 135) // Electric screwdriver tightening torque limit, A
#define ESCFINALCNTHOLD5                        (S_REG_HOLDING_START_FORCECTRL + 136) // Electric screwdriver tightening success detection window, 1ms
#define ESCFINALSPDHOLD5                        (S_REG_HOLDING_START_FORCECTRL + 137) // Electric screwdriver tightening zero-speed threshold, rpm
#define ESCFINALOVERTIMEHOLD5                   (S_REG_HOLDING_START_FORCECTRL + 138) // Electric screwdriver tightening timeout fault window, 1ms
#define ESCACTPOS5_L                            (S_REG_HOLDING_START_FORCECTRL + 139) // Electric screwdriver tightening success position (low), mechanical angle
#define ESCACTPOS5_H                            (S_REG_HOLDING_START_FORCECTRL + 140) // Electric screwdriver tightening success position (high), mechanical angle
#define ESCLOWACC5                              (S_REG_HOLDING_START_FORCECTRL + 141) // Electric screwdriver thread-engaging speed command acceleration
#define ESCHIGHACC5                             (S_REG_HOLDING_START_FORCECTRL + 142) // Electric screwdriver screw-in speed command acceleration
#define ESCHOLDACC5                             (S_REG_HOLDING_START_FORCECTRL + 143) // Electric screwdriver tightening speed command acceleration

//************** Compliance control parameters S_REG_HOLDING_INDEX_FORCECTRL  **************//
#define SOFTCTRLKP_L                            (S_REG_HOLDING_START_FORCECTRL + 144) // Compliance stiffness gain K
#define SOFTCTRLKP_H                            (S_REG_HOLDING_START_FORCECTRL + 145) // Compliance stiffness gain K
#define SOFTCTRLKI_L                            (S_REG_HOLDING_START_FORCECTRL + 146) // Compliance damping gain B
#define SOFTCTRLKI_H                            (S_REG_HOLDING_START_FORCECTRL + 147) // Compliance damping gain B
#define SOFTCTRLKD_L                            (S_REG_HOLDING_START_FORCECTRL + 148) // Compliance mass gain M
#define SOFTCTRLKD_H                            (S_REG_HOLDING_START_FORCECTRL + 149) // Compliance mass gain M
#define SOFTCTRLCMPMOD                          (S_REG_HOLDING_START_FORCECTRL + 150) // Compliance compensation mode
#define SOFTCTRLXD                              (S_REG_HOLDING_START_FORCECTRL + 151) // End-effector position command
#define SOFTCTRLXC                              (S_REG_HOLDING_START_FORCECTRL + 152) // End-effector position feedback
#define SOFTCTRLFD                              (S_REG_HOLDING_START_FORCECTRL + 153) // End-effector force command
#define SOFTCTRLFC                              (S_REG_HOLDING_START_FORCECTRL + 154) // End-effector force feedback
#define SOFTCTRLWORMOD                          (S_REG_HOLDING_START_FORCECTRL + 155) // Compliance mode: 0=off, 1=impedance (local), 2=admittance (local)

//************** Digital I/O parameters S_REG_HOLDING_INDEX_DIGITAL (10) **************//
#define DIGINOUTINV								(S_REG_HOLDING_START_DIGITAL + 0) // Digital I/O invert switch: high 8-bit=output, low 8-bit=input
#define DIGINVIRTUALSWITCH						(S_REG_HOLDING_START_DIGITAL + 1) // Virtual digital input switch
#define DIGINVIRTUAL							(S_REG_HOLDING_START_DIGITAL + 2) // Virtual digital input level
#define INMODE12								(S_REG_HOLDING_START_DIGITAL + 3) // Digital input mode: high 8-bit=IN2 mode, low 8-bit=IN1 mode
#define INMODE34								(S_REG_HOLDING_START_DIGITAL + 4) // Digital input mode: high 8-bit=IN4 mode, low 8-bit=IN3 mode
#define INMODE56								(S_REG_HOLDING_START_DIGITAL + 5) // Digital input mode: high 8-bit=IN6 mode, low 8-bit=IN5 mode
#define INMODE78								(S_REG_HOLDING_START_DIGITAL + 6) // Digital input mode: high 8-bit=IN8 mode, low 8-bit=IN7 mode
#define OUTMODE12								(S_REG_HOLDING_START_DIGITAL + 7) // Digital output mode: high 8-bit=OUT2 mode, low 8-bit=OUT1 mode
#define OUTMODE34								(S_REG_HOLDING_START_DIGITAL + 8) // Digital output mode: high 8-bit=OUT4 mode, low 8-bit=OUT3 mode
#define OUTMODE56								(S_REG_HOLDING_START_DIGITAL + 9) // Digital output mode: high 8-bit=OUT6 mode, low 8-bit=OUT5 mode
#define PROBECONFIG								(S_REG_HOLDING_START_DIGITAL + 10) // Probe configuration

#define PCOM1CNTRL								(S_REG_HOLDING_START_DIGITAL + 11) // Position compare output 1 configuration
#define PCOM1START_L							(S_REG_HOLDING_START_DIGITAL + 12) // Position compare output 1 start position
#define PCOM1START_H							(S_REG_HOLDING_START_DIGITAL + 13)
#define PCOM1END_L								(S_REG_HOLDING_START_DIGITAL + 14) // Position compare output 1 end position
#define PCOM1END_H								(S_REG_HOLDING_START_DIGITAL + 15)
#define PCOM1OFFSET_L							(S_REG_HOLDING_START_DIGITAL + 16) // Position compare output 1 position interval
#define PCOM1OFFSET_H							(S_REG_HOLDING_START_DIGITAL + 17)
#define PCOM1POS0_L								(S_REG_HOLDING_START_DIGITAL + 18) // Position compare output 1 table position 0
#define PCOM1POS0_H								(S_REG_HOLDING_START_DIGITAL + 19)
#define PCOM1POS1_L								(S_REG_HOLDING_START_DIGITAL + 20) // Position compare output 1 table position 1
#define PCOM1POS1_H								(S_REG_HOLDING_START_DIGITAL + 21)
#define PCOM1POS2_L								(S_REG_HOLDING_START_DIGITAL + 22) // Position compare output 1 table position 2
#define PCOM1POS2_H								(S_REG_HOLDING_START_DIGITAL + 23)
#define PCOM1POS3_L								(S_REG_HOLDING_START_DIGITAL + 24) // Position compare output 1 table position 3
#define PCOM1POS3_H								(S_REG_HOLDING_START_DIGITAL + 25)
#define PCOM1TABLELEN							(S_REG_HOLDING_START_DIGITAL + 26) // Position compare output 1 table length
#define PCOM1WIDTH								(S_REG_HOLDING_START_DIGITAL + 27) // Position compare output 1 pulse width

//************** Analog input parameters S_REG_HOLDING_INDEX_ANALOG (11) **************//
#define ANINOFFSET								(S_REG_HOLDING_START_ANALOG + 0) // Analog input offset voltage
#define ANINDEADBAND							(S_REG_HOLDING_START_ANALOG + 1) // Analog input dead band range
#define ANINLPFK								(S_REG_HOLDING_START_ANALOG + 2) // Analog input 1st-order LPF coefficient
#define ANINISCALE								(S_REG_HOLDING_START_ANALOG + 3) // Analog input current conversion coefficient
#define ANINVSCALE								(S_REG_HOLDING_START_ANALOG + 4) // Analog input velocity conversion coefficient
#define ANINFSCALE								(S_REG_HOLDING_START_ANALOG + 5) // Analog input pressure conversion coefficient
#define ANINCOE									(S_REG_HOLDING_START_ANALOG + 6) // Analog input voltage conversion coefficient


//************** Test parameters S_REG_HOLDING_INDEX_TEST (12) **************//
#define RESERVED1								(S_REG_HOLDING_START_TEST + 0) // Test register
#define RESERVED2								(S_REG_HOLDING_START_TEST + 1)
#define RESERVED3								(S_REG_HOLDING_START_TEST + 2)
#define RESERVED4								(S_REG_HOLDING_START_TEST + 3)
#define RESERVED5								(S_REG_HOLDING_START_TEST + 4)
#define RESERVED6								(S_REG_HOLDING_START_TEST + 5)
#define RESERVED7								(S_REG_HOLDING_START_TEST + 6)
#define RESERVED8								(S_REG_HOLDING_START_TEST + 7)
#define RESERVED9								(S_REG_HOLDING_START_TEST + 8)
#define RESERVED10								(S_REG_HOLDING_START_TEST + 9)

//************** Test parameters S_REG_HOLDING_INDEX_ERRORCOR (13) **************//
#define ERRCOREN								(S_REG_HOLDING_START_ERRCOR + 0) // Error correction enable
#define ERRCORNUMPOINTS							(S_REG_HOLDING_START_ERRCOR + 1) // Error correction number of points
#define ERRCORUNITS								(S_REG_HOLDING_START_ERRCOR + 2) // Error correction unit
#define ERRCORINTERVAL_L						(S_REG_HOLDING_START_ERRCOR + 3) // Error correction interval, low
#define ERRCORINTERVAL_H						(S_REG_HOLDING_START_ERRCOR + 4) // Error correction interval, high
#define ERRCORSTARTPOS_L						(S_REG_HOLDING_START_ERRCOR + 5) // Error correction start position, low
#define ERRCORSTARTPOS_H						(S_REG_HOLDING_START_ERRCOR + 6) // Error correction start position, high
#define ERRCORPROTARY_L							(S_REG_HOLDING_START_ERRCOR + 7) // Error correction start position, low
#define ERRCORPROTARY_H							(S_REG_HOLDING_START_ERRCOR + 8) // Error correction start position, high
#define ERRCORER1								(S_REG_HOLDING_START_ERRCOR + 9) // Error correction position 1 deviation
#define ERRCORER64								(S_REG_HOLDING_START_ERRCOR + 72) // Error correction position 64 deviation
// 64 error correction positions

// Definition of register DRIVECTRL
#define CTRL_CLEARPHASEFIND							   0x0080          // rw-- Clear phase find success flag
#define CTRL_CLEARENC								   0x0040          // rw-- Clear TMG encoder multi-turn
#define CTRL_DOMOTOREST								   0x0020          // rw-- Do motor parameter estimation
#define CTRL_DOPHASEFIND                               0x0010          // rw-- Do phase find
#define CTRL_DOHOME                                    0x0008          // rw-- Do home
#define CTRL_CLEARERR                                  0x0004          // rw-- Clear error
#define CTRL_DISABLE                                   0x0002          // rw-- Disable motor
#define CTRL_ENABLE                                    0x0001          // rw-- Enable motor

// Definition of register DRIVEMODE
#define MODE_DISABLEMODE                               0x8000          // rw-- 0: Disable directly, 1: Decelerate then disable
#define MODE_PULSEMODE1                                0x4000          // rw-- 1x = Aphase+Bphase
#define MODE_PULSEMODE0                                0x2000          // rw-- 00=Pulse+Direction, 01=CW+CCW
#define MODE_XXX									   0x1000          // rw-- reserve
#define MODE_SFBANGDIR								   0x0800          // rw-- 0: Load encoder direction not inverted, 1: Load encoder direction inverted
#define MODE_MOTORTYPE                                 0x0400          // rw-- 0: Linear Motor, 1: Rotary Motor
#define MODE_ANGDIR                                    0x0200          // rw-- 1: Encoder and ActPos direction are different
#define MODE_ELECANGDIR                                0x0100          // rw-- 1: Encoder and ElecAng direction are different
#define MODE_ENCABS									   0x0080          // rw-- 1: Absolute Encoder
#define MODE_AUTOPHASEFIND                             0x0040          // rw-- 1: Auto phase find on power-up
#define MODE_AUTOHOME                                  0x0020          // rw-- 1:Auto Do home when powerup
#define MODE_AUTOENABLE                                0x0010          // rw-- 1: Auto enable on power-up
#define MODE_WORKMODE3                                 0x0008          // rw-- 7=FORCECTRL, 8=VELFRF, 9=CURFRF
#define MODE_WORKMODE2                                 0x0004          // rw-- 4=PULSEDIR, 5=POSSERIAL, 6=EtherCAT
#define MODE_WORKMODE1                                 0x0002          // rw-- 2=CURSERIAL, 3=CURANALOG
#define MODE_WORKMODE0                                 0x0001          // rw-- 0=VELSERIAL, 1=VELANALOG

// Definition of register DRIVESWITCH
#define SW_MTMODE									   0x0001          // rw-- 0=M-method, 1=MT-method

// Definition of register PROFILECTRL
#define PROF_VELJOG									   0x0020          // rw-- 1: Jog, 0: No Jog
#define PROF_PROFILETYPE                               0x0010          // rw-- 1: S-curve, 0: T-curve
#define PROF_PROFILERND                                0x0008          // rw-- 1: Move back and forth
#define PROF_PROFILEREP                                0x0004          // rw-- 1: Repetitively move
#define PROF_PROFILEABS                                0x0002          // rw-- 1: Absolute move
#define PROF_MOTIONEN                                  0x0001          // rw-- Rising edge: Start move; Falling edge: Stop move


/////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////// Input Register (read-only) /////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////
// Variable groups
#define S_REG_INPUT_INDEX_STATUS				(0)
#define S_REG_INPUT_INDEX_VERSION				(1)
#define S_REG_INPUT_INDEX_CONTROLLER			(2)
#define S_REG_INPUT_INDEX_DIGITAL				(3)
#define S_REG_INPUT_INDEX_OTHERS				(4)
#define S_REG_INPUT_INDEX_PROTECT				(5)
#define S_REG_INPUT_INDEX_TEST					(6)

#define S_REG_INPUT_INDEX_MAX  					(7)

// Number of variables per group
#define S_REG_INPUT_SIZE_STATUS					(2)
#define S_REG_INPUT_SIZE_VERSION				(18)
#define S_REG_INPUT_SIZE_CONTROLLER				(50)
#define S_REG_INPUT_SIZE_DIGITAL				(11)
#define S_REG_INPUT_SIZE_OTHERS					(30)
#define S_REG_INPUT_SIZE_PROTECT				(31)
#define S_REG_INPUT_SIZE_TEST					(9)


#define S_REG_INPUT_START_STATUS				(0)
#define S_REG_INPUT_START_VERSION				(S_REG_INPUT_START_STATUS + S_REG_INPUT_SIZE_STATUS)
#define S_REG_INPUT_START_CONTROLLER			(S_REG_INPUT_START_VERSION + S_REG_INPUT_SIZE_VERSION)
#define S_REG_INPUT_START_DIGITAL				(S_REG_INPUT_START_CONTROLLER + S_REG_INPUT_SIZE_CONTROLLER)
#define S_REG_INPUT_START_OTHERS				(S_REG_INPUT_START_DIGITAL + S_REG_INPUT_SIZE_DIGITAL)
#define S_REG_INPUT_START_PROTECT				(S_REG_INPUT_START_OTHERS + S_REG_INPUT_SIZE_OTHERS)
#define S_REG_INPUT_START_TEST					(S_REG_INPUT_START_PROTECT + S_REG_INPUT_SIZE_PROTECT)

#define S_REG_INPUT_SIZE_TOTAL					(S_REG_INPUT_START_TEST + S_REG_INPUT_SIZE_TEST)


//************** Status information S_REG_INPUT_INDEX_STATUS (0) **************//
#define DRIVESTATUS								(S_REG_INPUT_START_STATUS + 0) // Status word, see below for details
#define CONTROLSTATUS							(S_REG_INPUT_START_STATUS + 1) // Status word 2, see below for details

//************** Version information S_REG_INPUT_INDEX_VERSION (1) **************//
#define FIRMWAREVERSION_L						(S_REG_INPUT_START_VERSION + 0) // Firmware version
#define FIRMWAREVERSION_H						(S_REG_INPUT_START_VERSION + 1)
#define PWMFREQUENCY							(S_REG_INPUT_START_VERSION + 2) // Carrier frequency
#define CURCTRLFREQUENCY						(S_REG_INPUT_START_VERSION + 3) // Current loop frequency
#define VELCTRLFREQUENCY						(S_REG_INPUT_START_VERSION + 4) // Velocity loop frequency
#define POSCTRLFREQUENCY						(S_REG_INPUT_START_VERSION + 5) // Position loop frequency
#define SERCURFREQ								(S_REG_INPUT_START_VERSION + 6) // Serial current mode frequency
#define SERVELFREQ								(S_REG_INPUT_START_VERSION + 7) // Serial velocity mode frequency
#define ANACURFREQ								(S_REG_INPUT_START_VERSION + 8) // Analog current mode frequency
#define ANAVELFREQ								(S_REG_INPUT_START_VERSION + 9) // Analog velocity mode frequency
#define SCOPEFREQ								(S_REG_INPUT_START_VERSION + 10) // Scope sampling frequency
#define OUTFILTFREQ								(S_REG_INPUT_START_VERSION + 11) // Torque filter operating frequency
#define VELFEBFREQ								(S_REG_INPUT_START_VERSION + 12) // Velocity feedback calculation frequency
#define POSREFFREQ								(S_REG_INPUT_START_VERSION + 13) // Position command filter frequency
#define DRIVERTYPE								(S_REG_INPUT_START_VERSION + 14) // Driver type
#define MCUCLOCK								(S_REG_INPUT_START_VERSION + 15) // System clock frequency
#define FUNCMASK0								(S_REG_INPUT_START_VERSION + 16) // Function switches
#define FUNCMASK1								(S_REG_INPUT_START_VERSION + 17)

//************** Controller information S_REG_INPUT_INDEX_CONTROLLER (2) **************//
#define CMDPOS_L								(S_REG_INPUT_START_CONTROLLER + 0) // Position command (after filtering)
#define CMDPOS_H								(S_REG_INPUT_START_CONTROLLER + 1)
#define ACTPOS_L								(S_REG_INPUT_START_CONTROLLER + 2) // Actual position (after offset+calibration)
#define ACTPOS_H								(S_REG_INPUT_START_CONTROLLER + 3)
#define POSERR_L								(S_REG_INPUT_START_CONTROLLER + 4) // Position error
#define POSERR_H								(S_REG_INPUT_START_CONTROLLER + 5)
#define CMDVEL									(S_REG_INPUT_START_CONTROLLER + 6) // Command velocity
#define ACTVEL									(S_REG_INPUT_START_CONTROLLER + 7) // Actual velocity
#define CMDCUR									(S_REG_INPUT_START_CONTROLLER + 8) // IQ command current (before torque filter)
#define ACTCUR									(S_REG_INPUT_START_CONTROLLER + 9) // Actual current
#define ELECANG									(S_REG_INPUT_START_CONTROLLER + 10) // Electrical angle (count) 
#define ELECANGOFFSET							(S_REG_INPUT_START_CONTROLLER + 11) // Electrical angle offset (count) 
#define CMDPOSRAW_L								(S_REG_INPUT_START_CONTROLLER + 12) // Position command (before filtering)
#define CMDPOSRAW_H								(S_REG_INPUT_START_CONTROLLER + 13)
#define QEPPOS_L								(S_REG_INPUT_START_CONTROLLER + 14) // Encoder raw value
#define QEPPOS_H								(S_REG_INPUT_START_CONTROLLER + 15)
#define HALLS									(S_REG_INPUT_START_CONTROLLER + 16) // Hall signal
#define MB_IDREF								(S_REG_INPUT_START_CONTROLLER + 17) // D-axis current command
#define MB_ID									(S_REG_INPUT_START_CONTROLLER + 18) // DaxisActual current
#define MB_UQ									(S_REG_INPUT_START_CONTROLLER + 19) // Q-axis output duty cycle
#define MB_UD									(S_REG_INPUT_START_CONTROLLER + 20) // D-axis output duty cycle
#define MB_IA									(S_REG_INPUT_START_CONTROLLER + 21) // IAActual current
#define MB_IB									(S_REG_INPUT_START_CONTROLLER + 22) // IBActual current
#define MB_IC									(S_REG_INPUT_START_CONTROLLER + 23) // ICActual current
#define SPEEDFF									(S_REG_INPUT_START_CONTROLLER + 24) // Velocity feedforward
#define ACCFF									(S_REG_INPUT_START_CONTROLLER + 25) // addVelocity feedforward
#define PTPVCMD									(S_REG_INPUT_START_CONTROLLER + 26) // Position command velocity
#define MB_IQREF								(S_REG_INPUT_START_CONTROLLER + 27) // IQ command current (after torque filter)
#define CMDFRC									(S_REG_INPUT_START_CONTROLLER + 28) // Pressure loop pressure command
#define ACTFRC									(S_REG_INPUT_START_CONTROLLER + 29) // Pressure loop pressure feedback
#define ESCRATIO								(S_REG_INPUT_START_CONTROLLER + 30) // Electric screwdriver success detection ratio
#define VELCTRLOUT								(S_REG_INPUT_START_CONTROLLER + 31) // Velocity controller output (filtered), MB_IQREF = VELCTRLOUT + CURFF
#define CURFF									(S_REG_INPUT_START_CONTROLLER + 32) // Current loop feedforward compensation (added after filter)
#define VELERR									(S_REG_INPUT_START_CONTROLLER + 33) // Velocity error
#define ACTPOSRAW_L								(S_REG_INPUT_START_CONTROLLER + 34) // Actual position (before error correction)
#define ACTPOSRAW_H								(S_REG_INPUT_START_CONTROLLER + 35)
#define ERRCORSTATUS							(S_REG_INPUT_START_CONTROLLER + 36) // Error correction status
#define ERRCORINDEX								(S_REG_INPUT_START_CONTROLLER + 37) // Error correction index
#define SFBACTPOS_L								(S_REG_INPUT_START_CONTROLLER + 38) // Load-side actual position
#define SFBACTPOS_H								(S_REG_INPUT_START_CONTROLLER + 39) // 
#define MIXPOSERR_L                             (S_REG_INPUT_START_CONTROLLER + 40) // MixedPosition error
#define MIXPOSERR_H                             (S_REG_INPUT_START_CONTROLLER + 41)
#define WARNMIXPOSERR_L                         (S_REG_INPUT_START_CONTROLLER + 42) // MonitorMixedPosition error
#define WARNMIXPOSERR_H                         (S_REG_INPUT_START_CONTROLLER + 43)
#define LOADVEL_L                               (S_REG_INPUT_START_CONTROLLER + 44) // Outer loop velocity
#define LOADVEL_H                               (S_REG_INPUT_START_CONTROLLER + 45)
#define SFBACTPOSRAW_L							(S_REG_INPUT_START_CONTROLLER + 46) // loadsideActual position (before error correction)
#define SFBACTPOSRAW_H							(S_REG_INPUT_START_CONTROLLER + 47) // 

//************** Digital/analog I/O S_REG_INPUT_INDEX_DIGITAL (3) **************//
#define DIGINSTATUS								(S_REG_INPUT_START_DIGITAL + 0) // Digital input status
#define DIGITALINPUT							(S_REG_INPUT_START_DIGITAL + 1) // Digital input
#define DIGITALOUTPUT							(S_REG_INPUT_START_DIGITAL + 2) // Digital output
#define ANALOGIN								(S_REG_INPUT_START_DIGITAL + 3) // Analog input signal (before dead band calculation and LPF)
#define PROBE1DATA_L							(S_REG_INPUT_START_DIGITAL + 4) // Probe 1 latch position value
#define PROBE1DATA_H							(S_REG_INPUT_START_DIGITAL + 5)
#define PROBE2DATA_L							(S_REG_INPUT_START_DIGITAL + 6) // Probe 2 latch position value
#define PROBE2DATA_H							(S_REG_INPUT_START_DIGITAL + 7)
#define PROBESTATUS								(S_REG_INPUT_START_DIGITAL + 8) // Probe status
#define PCOMSTATUS								(S_REG_INPUT_START_DIGITAL + 9) // Position compare output status
#define DIGINSTAEN								(S_REG_INPUT_START_DIGITAL + 10) // Digital input statusvalid, same definition asDIGINSTATUS


//************** Others S_REG_INPUT_INDEX_OTHERS (4) **************//
#define BUSVOLTAGE								(S_REG_INPUT_START_OTHERS + 0) // Bus voltage
#define SCOPESTATUS							    (S_REG_INPUT_START_OTHERS + 1) // Scope sampling status
#define SCOPETRIGSTA							(S_REG_INPUT_START_OTHERS + 2) // Scope trigger sampling status
#define MOTORTEMP								(S_REG_INPUT_START_OTHERS + 3) // Motor temperature
#define DRIVETEMP								(S_REG_INPUT_START_OTHERS + 4) // Driver temperature
#define ADCIA									(S_REG_INPUT_START_OTHERS + 5) // IA ADC value
#define ADCIB									(S_REG_INPUT_START_OTHERS + 6) // IB ADC value
#define HALLTHETA0								(S_REG_INPUT_START_OTHERS + 7) // Electrical angle at Hall transition edge 0
#define HALLTHETA1								(S_REG_INPUT_START_OTHERS + 8) // Electrical angle at Hall transition edge 1
#define HALLTHETA2								(S_REG_INPUT_START_OTHERS + 9) // Electrical angle at Hall transition edge 2
#define HALLTHETA3								(S_REG_INPUT_START_OTHERS + 10) // Electrical angle at Hall transition edge 3
#define HALLTHETA4								(S_REG_INPUT_START_OTHERS + 11) // Electrical angle at Hall transition edge 4
#define HALLTHETA5								(S_REG_INPUT_START_OTHERS + 12) // Electrical angle at Hall transition edge 5
#define HALLSTATUS01							(S_REG_INPUT_START_OTHERS + 13) // Hall value at transition edge: high 8-bit=1st Hall, low 8-bit=0th Hall
#define HALLSTATUS23							(S_REG_INPUT_START_OTHERS + 14) // Hall value at transition edge: high 8-bit=3rd Hall, low 8-bit=2nd Hall
#define HALLSTATUS45							(S_REG_INPUT_START_OTHERS + 15) // Hall value at transition edge: high 8-bit=5th Hall, low 8-bit=4th Hall
#define LMJRSTATUS								(S_REG_INPUT_START_OTHERS + 16) // Inertia identification status
#define LMJRRESULT_L							(S_REG_INPUT_START_OTHERS + 17) // Inertia identification result
#define LMJRRESULT_H							(S_REG_INPUT_START_OTHERS + 18)
#define ECCOMMSTATE								(S_REG_INPUT_START_OTHERS + 19) // EtherCAT slave status, e.g. OP
#define FBSYNCACT								(S_REG_INPUT_START_OTHERS + 20) // Fieldbus sync period
#define FBOPMODE								(S_REG_INPUT_START_OTHERS + 21) // 0x6061 Modes of operation display
#define PCMDFBRAW_L								(S_REG_INPUT_START_OTHERS + 22) // 0x607A Position demand, passed from communication variable to motor control
#define PCMDFBRAW_H								(S_REG_INPUT_START_OTHERS + 23)
#define ESTSTATUS								(S_REG_INPUT_START_OTHERS + 24) // Motor parametersidentification status
#define CANCONTROLWORD							(S_REG_INPUT_START_OTHERS + 25) // 0x6040 CAN controlword
#define CANSTATUSWORD							(S_REG_INPUT_START_OTHERS + 26) // 0x6041 CAN statusword
#define FBOPMODERAW								(S_REG_INPUT_START_OTHERS + 27) // 0x6060 Modes of operation
#define ENCCALSTATUS							(S_REG_INPUT_START_OTHERS + 28) // Encoder calibration status
#define ENCSPISRC								(S_REG_INPUT_START_OTHERS + 29) // SPIEncoder type

//************** Fault information S_REG_INPUT_INDEX_PROTECT (5) **************//
#define CURRENTTIME								(S_REG_INPUT_START_PROTECT + 0) // Current time, counts from power-up, max 45.5 days
#define ERRORSTATUS0							(S_REG_INPUT_START_PROTECT + 1) // Fault 0, see fault definition for details
#define ERRORSTATUS1							(S_REG_INPUT_START_PROTECT + 2) // Fault 1, see fault definition for details
#define ERRORSTATUS2							(S_REG_INPUT_START_PROTECT + 3) // Fault 2, see fault definition for details
#define ERRORTIME0								(S_REG_INPUT_START_PROTECT + 4) // Fault history time 0, latches CURRENTTIME at fault occurrence
#define ERRORHIST0								(S_REG_INPUT_START_PROTECT + 5) // Fault history record 0
#define ERRORTIME1								(S_REG_INPUT_START_PROTECT + 6)
#define ERRORHIST1								(S_REG_INPUT_START_PROTECT + 7)
#define ERRORTIME2								(S_REG_INPUT_START_PROTECT + 8)
#define ERRORHIST2								(S_REG_INPUT_START_PROTECT + 9)
#define ERRORTIME3								(S_REG_INPUT_START_PROTECT + 10)
#define ERRORHIST3								(S_REG_INPUT_START_PROTECT + 11)
#define ERRORTIME4								(S_REG_INPUT_START_PROTECT + 12)
#define ERRORHIST4								(S_REG_INPUT_START_PROTECT + 13)
#define ERRORTIME5								(S_REG_INPUT_START_PROTECT + 14)
#define ERRORHIST5								(S_REG_INPUT_START_PROTECT + 15)
#define ERRORTIME6								(S_REG_INPUT_START_PROTECT + 16)
#define ERRORHIST6								(S_REG_INPUT_START_PROTECT + 17)
#define ERRORTIME7								(S_REG_INPUT_START_PROTECT + 18)
#define ERRORHIST7								(S_REG_INPUT_START_PROTECT + 19)
#define ERRORTIME8								(S_REG_INPUT_START_PROTECT + 20)
#define ERRORHIST8								(S_REG_INPUT_START_PROTECT + 21)
#define ERRORTIME9								(S_REG_INPUT_START_PROTECT + 22)
#define ERRORHIST9								(S_REG_INPUT_START_PROTECT + 23)
#define ERRORTIME10								(S_REG_INPUT_START_PROTECT + 24)
#define ERRORHIST10								(S_REG_INPUT_START_PROTECT + 25)
#define ENCODERERR								(S_REG_INPUT_START_PROTECT + 26) // Encoder specific fault
#define WARNSTATUS0								(S_REG_INPUT_START_PROTECT + 27) // Driver warning
#define WARNSTATUS1								(S_REG_INPUT_START_PROTECT + 28)
#define SFBENCERR								(S_REG_INPUT_START_PROTECT + 29) // loadsideEncoder specific fault
#define PHASEFINDERR							(S_REG_INPUT_START_PROTECT + 30) // Phase find specific fault

//************** Test register S_REG_INPUT_INDEX_TEST (6) **************//
#define TESTVAR0								(S_REG_INPUT_START_TEST + 0) // Test channel 0
#define TESTVAR1								(S_REG_INPUT_START_TEST + 1) // Test channel 1
#define TESTVAR2								(S_REG_INPUT_START_TEST + 2)
#define TESTVAR3_L								(S_REG_INPUT_START_TEST + 3)
#define TESTVAR3_H								(S_REG_INPUT_START_TEST + 4)
#define TESTVAR4_L								(S_REG_INPUT_START_TEST + 5)
#define TESTVAR4_H								(S_REG_INPUT_START_TEST + 6)
#define TESTVAR5_L								(S_REG_INPUT_START_TEST + 7)
#define TESTVAR5_H								(S_REG_INPUT_START_TEST + 8)


// read only
// Definition of register DRIVESTATUS
#define STATUS_WARNING                                 0x0080          // rw-- 1: Warning exists
#define STATUS_STOPPED                                 0x0020          // rw-- 0=Motion profile complete, 1=in motion profile
#define STATUS_INPOS                                   0x0010          // rw-- 1: In-position OK, 0: In-position not OK
#define STATUS_PHASEFINDSUCCEED                        0x0008          // rw-- 1: Phase find succeeded
#define STATUS_HOMECOMPLETE                            0x0004          // rw-- 1: Home complete
#define STATUS_FAULT                                   0x0002          // rw-- 1: Fault exists
#define STATUS_ENABLE                                  0x0001          // rw-- 0: Motor disabled, 1: Motor enabled


// Definition of register CONTROLSTATUS
#define CTSTATUS_DATASTREAM                            0x0100          // rw-- 1: Data stream mode, 0: Modbus mode
#define CTSTATUS_FLASHSTATE2                           0x0080          // r-- 0=FLASH_SUCCESS, 1=FLASH_FAIL_FROZEN
#define CTSTATUS_FLASHSTATE1                           0x0040          // r-- 2=FLASH_FAIL_UNLOCK, 3=FLASH_FAIL_PREPROGRAM
#define CTSTATUS_FLASHSTATE0                           0x0020          // r-- 4=FLASH_FAIL_ERASE, 5=FLASH_FAIL_WRITE, 7=FLASH_OPERATING
#define CTSTATUS_MCSTATE4                              0x0010          // r-- 0=Ready: calculating current offset; 1=Idle: idle state
#define CTSTATUS_MCSTATE3                              0x0008          // r-- 2=Disable: disabled state; 3=PhaseFind: phase finding
#define CTSTATUS_MCSTATE2                              0x0004          // r-- 4=Home: homing; 5=Start: enabled
#define CTSTATUS_MCSTATE1                              0x0002          // r-- 6=Run: moving; 7=Stop: stopping; 8=Fault: fault
#define CTSTATUS_MCSTATE0                              0x0001          // r-- 9=UpFlash: load params from flash; 10=DownFlash: save params to flash




typedef struct
{
	USHORT Length[4];
	UCHAR * Addr[4]; // including head, data, CRC
	UCHAR Count; // 3 or 4
} SendFramePointerTypeDef;

extern SendFramePointerTypeDef SendFramePointer;

extern USHORT usSRegInBuf[S_REG_INPUT_NREGS];
extern const USHORT usSRegInStartArray[S_REG_INPUT_INDEX_MAX + 1];
extern USHORT usSRegHoldBuf[S_REG_HOLDING_NREGS];
extern const USHORT usSRegHoldStartArray[S_REG_HOLDING_INDEX_MAX + 1];
extern USHORT usSRegScopeBuf[S_REG_SCOPE_NREGS];

#endif
