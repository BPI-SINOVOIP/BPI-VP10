/*
 * Copyright (c) 2021-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : PROTECT.h
 * Author        : Summer
 * Date          : 2021-11-13
 * Description   : define some protect function.
 *
 * Record        :
 * V1.0, 2021-11-13, Summer: Created file
 */


/* Define to prevent recursive inclusion -------------------------------------------------------- */
#ifndef __PROTECT_H_
#define __PROTECT_H_

#include "Parameter.h"

/*! \brief If Hardware do Over and Under Voltage protection is enabled. */
#define PROT_OUVP_HARDWARE_ENABLED					( 0 )

/*! \brief If Hardware do over peak current protection is enabled. */
#define PROT_SOCP_HARDWARE_ENABLED					( 1 )

/*! \brief If Hardware do over velocity error protection is enabled. */
#define PROT_OVEL_HARDWARE_ENABLED					( 1 )

/*! \brief If Hardware do over speed error protection is enabled. */
#define PROT_OSPD_HARDWARE_ENABLED					( 1 )

/*! \brief If Hardware do stall error protection is enabled. */
#define PROT_STALL_HARDWARE_ENABLED					( 1 )

/*! \brief If Hardware do phase loss error protection is enabled. */
#define PROT_PLOSS_HARDWARE_ENABLED					( 1 )

/*! \brief If Hardware do carrier interrupt timeout protection is enabled. */
#define PROT_CARINTOT_HARDWARE_ENABLED				( 1 )

/*! \brief If Hardware do any protection is enabled. */
#define PROT_HARDWARE_ENABLED						(PROT_OUVP_HARDWARE_ENABLED | PROT_SOCP_HARDWARE_ENABLED | PROT_OVEL_HARDWARE_ENABLED | \
													PROT_OSPD_HARDWARE_ENABLED | PROT_STALL_HARDWARE_ENABLED | PROT_PLOSS_HARDWARE_ENABLED | \
													PROT_CARINTOT_HARDWARE_ENABLED)


#define FaultNoSource				(0x00)

// Motion related errors
#define FaultHardOVCurrent			(0xA00 + 1) // Hardware overcurrent
#define FaultPeakOVCurrent			(0xA00 + 2) // Software overcurrent
#define FaultRMSOVCurrent			(0xA00 + 3) // RMS overcurrent
#define FaultPhaseLoss				(0xA00 + 4) // Phase loss
#define FaultOverSpeed				(0xA00 + 5) // Overspeed
#define FaultOverPosErr				(0xA00 + 6) // Position over error
#define FaultOverVelErr				(0xA00 + 7) // Velocity over error
#define FaultStall					(0xA00 + 8) // Stall
#define FaultPhaseFindFailed		(0xA00 + 9) // Phase alignment failed
#define FaultHomeFailed				(0xA00 + 10) // Homing failed
#define FaultParamError				(0xA00 + 11) // Unreasonable parameter setting
#define FaultPulseFreqTooHigh		(0xA00 + 12) // Pulse frequency too high (not used)
#define FaultCommutation			(0xA00 + 13) // Commutation failed (not used)
#define FaultEmergencyStop			(0xA00 + 14) // Emergency stop  (not used)
#define FaultPositiveLimit			(0xA00 + 15) // Positive overtravel
#define FaultNegativeLimit			(0xA00 + 16) // Negative overtravel
#define FaultNotPhaseFind			(0xA00 + 17) // Phase not aligned
#define FaultMixErrOver  			(0xA00 + 18) // Dual-encoder mixed deviation too large
#define FaultFoldBackCurrent  	    (0xA00 + 19) // Foldback current warning
#define FaultGantryMaster  			(0xA00 + 20) // Gantry master axis error
#define FaultGantrySlave            (0xA00 + 21) // Gantry slave axis error
#define FaultGantryErrOver          (0xA00 + 22) // Master-slave mixed deviation too large

// Driver related errors
#define FaultUnderVoltage			(0xB00 + 1) // Undervoltage
#define FaultOverVoltage			(0xB00 + 2) // Overvoltage
#define FaultOverTemp				(0xB00 + 3) // Overtemperature
#define FaultSTO					(0xB00 + 4) // STO not connected
#define FaultCurrentOffset			(0xB00 + 5) // Current offset abnormal
#define FaultMainIntTimeOut 		(0xB00 + 6) // Main interrupt timeout
#define FaultAuxIntDelayTimeOut 	(0xB00 + 7) // Sub-interrupt delay timeout
#define FaultECatTimeOut 			(0xB00 + 8) // EtherCAT communication timeout
#define Fault485CRC 			    (0xB00 + 9) // 485 communication CRC error

// Encoder related errors
#define FaultEncTimeOut				(0xC00 + 1) // Encoder communication timeout
#define FaultEncCRC					(0xC00 + 2) // Encoder CRC communication alarm
#define FaultEncComError			(0xC00 + 3) // Encoder other communication alarm
#define FaultEncBatteryErr			(0xC00 + 4) // Encoder battery error
#define FaultEncBatteryWarn			(0xC00 + 5) // Encoder battery alarm
#define FaultEncInternal			(0xC00 + 6) // Encoder internal error alarm
#define FaultBiSSErr				(0xC00 + 7) // BiSS data frame error
#define FaultBiSSWarn				(0xC00 + 8) // BiSS data frame warning
#define FaultHallsInvalid			(0xC00 + 9) // Hall fault
#define FaultEncOutFreqTooHigh		(0xC00 + 10) // Encoder output pulse frequency too high
#define FaultABLineBreak			(0xC00 + 11) // Encoder AB wiring disconnected (not used)
#define FaultSFBEncCRC				(0xC00 + 12) // Load-side encoder CRC communication alarm
#define FaultSFBEncInternal			(0xC00 + 13) // Load-side encoder internal error alarm

// Constants
#define MS_PER_MINUTE					(60000) // how many ms per minute

// Carrier interrupt timeout judgment threshold
#define VELLOOPTHRESHOLD				(375 / VELCTRL_FREQUENCY + 5)
	
// Error history storage		
#define MAXERRHIST						(11)
#define MAXERRHISTPOINTER				(MAXERRHIST << 1)

// Encoder errors
#define ENCERRSIZE						(10)
#define BISSERRSIZE						(4)
#if ENCODER_SEL_BISS_ENABLED && ENCODER_SEL_TMG_ENABLED
#define ENCERRARRAYSIZE					(ENCERRSIZE)
#elif ENCODER_SEL_BISS_ENABLED
#define ENCERRARRAYSIZE					(BISSERRSIZE)
#elif ENCODER_SEL_TMG_ENABLED
#define ENCERRARRAYSIZE					(ENCERRSIZE - BISSERRSIZE)
#else
#define ENCERRARRAYSIZE					(0)
#endif

// Warning/Error bits
#define FLAGBIT_PARAMERR				(0) // Unreasonable parameter setting
#define FLAGBIT_POSLIM					(1) // Positive overtravel
#define FLAGBIT_NEGLIM					(2) // Negative overtravel
#define FLAGBIT_STOERR					(3) // STO not connected
#define FLAGBIT_CUROFF					(4) // Current offset abnormal
#define FLAGBIT_MAININTOT				(5) // Main interrupt timeout
#define FLAGBIT_AUXINTOT				(6) // Sub-interrupt delay timeout
#define FLAGBIT_BISSWARN				(7) // BiSS data frame warning
#define FLAGBIT_BATWARN					(8) // Encoder battery alarm
#define FLAGBIT_ENCCRC					(9) // Encoder CRC communication alarm
#define FLAGBIT_ENCCOM					(10) // Encoder other communication alarm
#define FLAGBIT_ENCINT					(11) // Encoder internal error alarm
#define FLAGBIT_ECAT					(12) // EtherCAT communication timeout
#define FLAGBIT_BISSERR					(13) // BiSS data frame error
#define FLAGBIT_BATERR					(14) // Encoder battery error
#define FLAGBIT_HARDOVC					(15) // Hardware overcurrent
#define FLAGBIT_HALLERR					(16) // Hall fault
#define FLAGBIT_ENCOT					(17) // Encoder communication timeout
#define FLAGBIT_FOLDBACK                (18) // Foldback current warning
#define FLAGBIT_SFBENCCRC				(19) // Load-side encoder CRC communication alarm
#define FLAGBIT_SFBENCINT				(20) // Load-side encoder internal error alarm

// Warning/Error bits
#define FLAG_PARAMERR					(0x00000001) // Unreasonable parameter setting
#define FLAG_POSLIM						(0x00000002) // Positive overtravel
#define FLAG_NEGLIM						(0x00000004) // Negative overtravel
#define FLAG_STOERR						(0x00000008) // STO not connected
#define FLAG_CUROFF						(0x00000010) // Current offset abnormal
#define FLAG_MAININTOT					(0x00000020) // Main interrupt timeout
#define FLAG_AUXINTOT					(0x00000040) // Sub-interrupt delay timeout
#define FLAG_BISSWARN					(0x00000080) // BiSS data frame warning
#define FLAG_BATWARN					(0x00000100) // Encoder battery alarm
#define FLAG_ENCCRC						(0x00000200) // Encoder CRC communication alarm
#define FLAG_ENCCOM						(0x00000400) // Encoder other communication alarm
#define FLAG_ENCINT						(0x00000800) // Encoder internal error alarm
#define FLAG_ECAT						(0x00001000) // EtherCAT communication timeout
#define FLAG_BISSERR					(0x00002000) // BiSS data frame error
#define FLAG_BATERR						(0x00004000) // Encoder battery error
#define FLAG_HARDOVC					(0x00008000) // Hardware overcurrent
#define FLAG_HALLERR					(0x00010000) // Hall fault
#define FLAG_ENCOT						(0x00020000) // Encoder communication timeout
#define FLAG_FOLDBACK                   (0x00040000) // Foldback current warning
#define FLAG_SFBENCCRC					(0x00080000) // Load-side encoder CRC communication alarm
#define FLAG_SFBENCINT					(0x00100000) // Load-side encoder internal error alarm



typedef struct
{
	//Current protect
	uint8 OverCurCnt;				// Software peak overcurrent count
	uint16 RMSCurCnt;				// RMS software overcurrent count

	uint16 Abs_ia;					// Absolute value of IA
	uint16 Abs_ib;				    // Absolute value of IB
	uint16 Abs_ic;				    // Absolute value of IC

	uint16 Max_ia;				    // IA absolute value max
	uint16 Max_ib;				    // IB absolute value max
	uint16 Max_ic;				    // IC absolute value max

	uint32 Sum_ia;				    // Sum of IA
	uint32 Sum_ib;				    // Sum of IB
	uint32 Sum_ic;				    // Sum of IC

	uint32 RMSSumThreshold;			// RMS Current Sum Threshold
	
	uint16 PeakCurArr;				// Chip software overcurrent count
	uint16 PeakCurCnt;
	uint16 PeakCurLatch;
} CurrentVarible;


typedef struct
{
	uint16 OverVoltDetecCnt;		// Overvoltage detection count
	uint16 UnderVoltDetecCnt;		// Undervoltage detection count

	uint16 OverPosErrCnt;			// Position following error too large count
	uint16 OverGanTryPosErrCnt;		// Gantry error too large count
	uint16 OverVelErrCnt;			// Velocity following error too large count
	uint16 OverSpeedCnt;			// Overspeed count
	uint16 DriveThermCnt;			// Overtemperature count
	uint16 StallCnt;				// Stall count
	uint16 HallCnt;					// Hall count
	uint16 CurIntCnt;				// Carrier interrupt timeout count
	uint8  PosLmtPosCnt;			// Positive overtravel count
	uint8  PosLmtNegCnt;			// Negative overtravel count
	
	uint16 AOpencnt;				// Phase A loss count
	int32 ThetaNow;
	int32 ThetaPre;
	uint16 ThetaSingle;
	uint16 ThetaSingleLatch;
	int16 ThetaMulti;
	
	uint16 CurrentTimeCount;
	uint16 CurrentMinute;

	uint16* pErrorHist;
	uint16 ErrorHistPointer;
	uint16 ErrorHistFlag;
	
	uint8 ErrorHistFirstFlag;
} FaultVarible;



extern CurrentVarible mcCurVarible;
extern FaultVarible mcFaultDect;
extern uint16 mcFaultSource;
extern uint16 mcWarnSource;
extern uint8 mcFaultSourceSize[3];
	

extern void Fault_Detection(void);
extern void FaultProcess(void);
extern void FaultClear(void);
extern void Fault_UploadErrCode();
extern void Fault_AddErrorHistory(uint16 FaultSrc);
extern void Fault_Handler(uint16 FaultSrc, uint32 FaultMask);

extern void Fault_FoldBackCurrent(FaultVarible* h_Fault);
extern void Fault_MixErrOver(FaultVarible* h_Fault);
extern void Fault_OverUnderVoltage(FaultVarible* h_Fault);
extern void Fault_PeakOvercurrent(CurrentVarible* h_Cur);
extern void Fault_RMSOvercurrent(CurrentVarible* h_Cur);
extern void Fault_OverSpeed(FaultVarible* h_Fault);
extern void Fault_OverPosErr(FaultVarible* h_Fault);
extern void Fault_OverVelErr(FaultVarible* h_Fault);
extern void Fault_PhaseLoss(FaultVarible* h_Fault); 
extern void Fault_Stall(FaultVarible* h_Fault);
extern void Fault_OverTemperature(FaultVarible* h_Fault);
extern void Fault_STO(FaultVarible* h_Fault);
extern void Fault_CurrentOffset();
extern void Fault_HardOvercurrent(FaultVarible* h_Fault);
extern void Fault_ParamError(FaultVarible* h_Fault);
extern void Fault_Encoder(FaultVarible* h_Fault);
extern void Fault_Hall(FaultVarible* h_Fault);
extern void Fault_EncOutFreqTooHigh(FaultVarible* h_Fault);
extern void Fault_MainIntPeriodTimeOut(FaultVarible* h_Fault);
extern void Fault_AuxIntDelayTimeOut();
extern void Fault_ExceedPositionLimit(FaultVarible* h_Fault);
extern void Fault_TimeCount();


#endif