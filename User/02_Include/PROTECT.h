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

// 运动相关报错
#define FaultHardOVCurrent			(0xA00 + 1)
#define FaultPeakOVCurrent			(0xA00 + 2)
#define FaultRMSOVCurrent			(0xA00 + 3)
#define FaultPhaseLoss				(0xA00 + 4)
#define FaultOverSpeed				(0xA00 + 5)
#define FaultOverPosErr				(0xA00 + 6)
#define FaultOverVelErr				(0xA00 + 7)
#define FaultStall					(0xA00 + 8)
#define FaultPhaseFindFailed		(0xA00 + 9)
#define FaultHomeFailed				(0xA00 + 10)
#define FaultParamError				(0xA00 + 11)
#define FaultPulseFreqTooHigh		(0xA00 + 12)
#define FaultCommutation			(0xA00 + 13)
#define FaultEmergencyStop			(0xA00 + 14)
#define FaultPositiveLimit			(0xA00 + 15)
#define FaultNegativeLimit			(0xA00 + 16)
#define FaultNotPhaseFind			(0xA00 + 17)
#define FaultMixErrOver  			(0xA00 + 18)
#define FaultFoldBackCurrent  	    (0xA00 + 19)
#define FaultGantryMaster  			(0xA00 + 20)
#define FaultGantrySlave            (0xA00 + 21)
#define FaultGantryErrOver          (0xA00 + 22)

// 驱动器相关报错
#define FaultUnderVoltage			(0xB00 + 1)
#define FaultOverVoltage			(0xB00 + 2)
#define FaultOverTemp				(0xB00 + 3)
#define FaultSTO					(0xB00 + 4)
#define FaultCurrentOffset			(0xB00 + 5)
#define FaultMainIntTimeOut 		(0xB00 + 6)
#define FaultAuxIntDelayTimeOut 	(0xB00 + 7)
#define FaultECatTimeOut 			(0xB00 + 8)
#define Fault485CRC 			    (0xB00 + 9)

// 编码器相关报错
#define FaultEncTimeOut				(0xC00 + 1)
#define FaultEncCRC					(0xC00 + 2)
#define FaultEncComError			(0xC00 + 3)
#define FaultEncBatteryErr			(0xC00 + 4)
#define FaultEncBatteryWarn			(0xC00 + 5)
#define FaultEncInternal			(0xC00 + 6)
#define FaultBiSSErr				(0xC00 + 7)
#define FaultBiSSWarn				(0xC00 + 8)
#define FaultHallsInvalid			(0xC00 + 9)
#define FaultEncOutFreqTooHigh		(0xC00 + 10)
#define FaultABLineBreak			(0xC00 + 11)
#define FaultSFBEncCRC				(0xC00 + 12)
#define FaultSFBEncInternal			(0xC00 + 13)

// 堵转判断范围	
#define ETHETA_60						(10922) // 60度电角度对应的值
#define ETHETA_160						(29127) // 160度电角度对应的值

// 载波中断超时判断阈值
#define VELLOOPTHRESHOLD				(375 / VELCTRL_FREQUENCY + 5)
	
// 报错历史存储		
#define MAXERRHIST						(11)
#define MAXERRHISTPOINTER				(MAXERRHIST << 1)

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

// 警告报错位
#define FLAGBIT_PARAMERR				(0) // 参数设置不合理
#define FLAGBIT_POSLIM					(1) // 正向超程
#define FLAGBIT_NEGLIM					(2) // 负向超程
#define FLAGBIT_STOERR					(3) // STO没接
#define FLAGBIT_CUROFF					(4) // 电流偏置异常
#define FLAGBIT_MAININTOT				(5) // 主中断超时
#define FLAGBIT_AUXINTOT				(6) // 子中断延时超时
#define FLAGBIT_BISSWARN				(7) // BiSS数据帧警告
#define FLAGBIT_BATWARN					(8) // 编码器电池报警
#define FLAGBIT_ENCCRC					(9) // 编码器CRC通信报警
#define FLAGBIT_ENCCOM					(10) // 编码器其他通信报警
#define FLAGBIT_ENCINT					(11) // 编码器内部错误报警
#define FLAGBIT_ECAT					(12) // EtherCAT通信超时
#define FLAGBIT_BISSERR					(13) // BiSS数据帧错误
#define FLAGBIT_BATERR					(14) // 编码器电池报错
#define FLAGBIT_HARDOVC					(15) // 硬件过流
#define FLAGBIT_HALLERR					(16) // Hall故障
#define FLAGBIT_ENCOT					(17) // 编码器通信超时
#define FLAGBIT_FOLDBACK                (18) // 折返电流警告
#define FLAGBIT_SFBENCCRC				(19) // 负载侧编码器CRC通信报警
#define FLAGBIT_SFBENCINT				(20) // 负载侧编码器内部错误报警

// 警告报错位
#define FLAG_PARAMERR					(0x00000001) // 参数设置不合理
#define FLAG_POSLIM						(0x00000002) // 正向超程
#define FLAG_NEGLIM						(0x00000004) // 负向超程
#define FLAG_STOERR						(0x00000008) // STO没接
#define FLAG_CUROFF						(0x00000010) // 电流偏置异常
#define FLAG_MAININTOT					(0x00000020) // 主中断超时
#define FLAG_AUXINTOT					(0x00000040) // 子中断延时超时
#define FLAG_BISSWARN					(0x00000080) // BiSS数据帧警告
#define FLAG_BATWARN					(0x00000100) // 编码器电池报警
#define FLAG_ENCCRC						(0x00000200) // 编码器CRC通信报警
#define FLAG_ENCCOM						(0x00000400) // 编码器其他通信报警
#define FLAG_ENCINT						(0x00000800) // 编码器内部错误报警
#define FLAG_ECAT						(0x00001000) // EtherCAT通信超时
#define FLAG_BISSERR					(0x00002000) // BiSS数据帧错误
#define FLAG_BATERR						(0x00004000) // 编码器电池报错
#define FLAG_HARDOVC					(0x00008000) // 硬件过流
#define FLAG_HALLERR					(0x00010000) // Hall故障
#define FLAG_ENCOT						(0x00020000) // 编码器通信超时
#define FLAG_FOLDBACK                   (0x00040000) // 折返电流警告
#define FLAG_SFBENCCRC					(0x00080000) // 负载侧编码器CRC通信报警
#define FLAG_SFBENCINT					(0x00100000) // 负载侧编码器内部错误报警



typedef struct
{
	//Current protect
	uint8 OverCurCnt;         // 软件峰值过流计数
	uint16 RMSCurCnt;          // RMS软件过流计数

	uint16 Abs_ia;				      // IA的绝对值
	uint16 Abs_ib;				      // IB的绝对值
	uint16 Abs_ic;				      // IC的绝对值

	uint16 Max_ia;				      // IA的绝对值
	uint16 Max_ib;				      // IB的绝对值
	uint16 Max_ic;				      // IC的绝对值

	uint32 Sum_ia;				      // IA的sum
	uint32 Sum_ib;				      // IB的sum
	uint32 Sum_ic;				      // IC的sum

	uint32 RMSSumThreshold;      // RMS Current Sum Threshold
	
	uint16 PeakCurArr;				  // 芯片软件过流计数
	uint16 PeakCurCnt;
	uint16 PeakCurLatch;
} CurrentVarible;


typedef struct
{
	uint16 OverVoltDetecCnt; // 过压检测计数
	uint16 UnderVoltDetecCnt;// 欠压检测计数
//	uint16 VoltRecoverCnt;	  // 过压恢复计数

	//OVER Current protect recover
//	uint16 CurrentRecoverCnt;  // 过流保护恢复计数
	uint16 SoftOVCurrentTimes; // 过流保护次数

	uint16 OverPosErrCnt; // 位置跟随误差过大计数
	uint16 OverGanTryPosErrCnt; // 龙门误差过大计数
	uint16 OverVelErrCnt; // 速度跟随误差过大计数
	uint16 OverSpeedCnt; // 速度过超计数
	uint16 DriveThermCnt;  // 过温计数
	uint16 StallCnt;		// 堵转计数
	uint16 HallCnt;  // Hall计数
	uint16 CurIntCnt; // 载波中断超时计数
	uint8  PosLmtPosCnt; // 正向超程计数
	uint8  PosLmtNegCnt; // 负向超程计数
	
	//Loss Phase protect
//	uint16 Lphasecnt;          // 缺相保护计时
	uint16 AOpencnt;          // A缺相计数
//	uint16 BOpencnt;          // B缺相计数
//	uint16 COpencnt;          // C缺相计数
//	uint16 mcLossPHRecCount;   // 缺相恢复计数
	int32 ThetaNow;
	int32 ThetaPre;
	uint16 ThetaSingle;
	uint16 ThetaSingleLatch;
	int16 ThetaMulti;
	

//	uint16 TemperatureRecoverCount;    // Delay time after over temperature protect

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

