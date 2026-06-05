/*
 * Copyright (c) 2022-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : FocControlFunction.h
 * Author        : Fortior Application Team
 * Date          : 2022-09-21
 * Description   : define motor contorl parameter
 *
 * Record        :
 * V1.0, 2022-09-21, Fortior Application Team: Created file
 */

#ifndef __FocControlFunction_H_
#define __FocControlFunction_H_
/* Define to prevent recursive inclusion -------------------------------------*/



typedef struct
{
	uint8 PosLoopTime;             // Position Loop Time
	uint8 PosLoopTimeLatch;
	uint8 VelLoopTime;             // Speed Loop Time
	uint8 MultiOffsetFirstFlag;
	uint8 MultiOffsetFirstCounter;
	uint16 State_Count;	            // 电机各个状态的时间计数
	uint16 ModeSwitchFlag;
	
	int32 ThetaErr;
	int32 ActPos;
	int32 ActLoadPos;
	int32 QepPos;
	int32 QepPosMulti;
	int32 QEPThetaOffset;           // PosOffset
	int32 QEPLoadThetaOffset;
	int32 QEPLoadMultiOffset;

	int16 QepSpeedCoe;
	uint32 EncRes;
	uint32 SfbEncRes;
	uint32 AngToCnt;         // Encoder count per electrical circle

	int32 ActualAngle;				  // 误差校准后的实际位置
	int32 ActualAngleRaw;			  // 误差校准前的实际位置
	
	int32 TargetAngleFilt;            // 滤波后的目标位置
	int32 TargetAngle;                // 滤波前的目标位置
	int32 TargetAngleLatch;           // 滤波前的目标位置锁存值
	int32 TargetRef;                  // 位置环每周期的位置指令增量
	int32 TargetReftoSpd;             // 位置环每周期的位置指令增量对应的速度
	int32 TargetAngleSum;             // 位置指令增量的累加和
	uint8 TargetRefFirstFlag;		  // 计算位置指令增量的标志位

	int16 mcIqRef;                    // Iq Ref before LPF
	int16 focIqRef;                   // Iq Ref after LPF

	uint8 CurLoopEnable;
	uint8 VelLoopEnable;
	uint8 PosLoopEnable;
	uint8 FrcLoopEnable;			  // 压力环使能标志

	uint8 DigitalInPre;
	
	uint8 AngDir;  // 1：编码器跟ActPos的方向相反
	uint8 LoadAngDir;
	uint8 EAngDir;  // 1：电角度跟ActPos的方向相反
	
	uint16 InPosCounter;  // 计算到位的累计时间
	
	uint8 StopFlag;                  // 表示需要停止后需要重新使能

	uint8 RunMod;
	uint8 DrvComrVal;				// 载波中断触发点切换标志位
	uint8 VelCnt;
	uint8 Timer1msCount;
	
	uint8 ChargeStep;				// 预充电步骤
	uint8 ChargeFinish;				// 预充电完成标志

} FOCCTRL;


typedef struct
{
	int16   SMT_SpdFdb;				// SMT算法算出来的速度
	int16	MT_Qep_Margin;          // 相邻时刻位置差分
	int16	MT_Act_Margin;          // 相邻时刻位置差分，修正正方向后
	int16	MT_Qep_Margin_Sum;      // 相邻时刻位置差分累计量
	int16	MT_Qep_Margin_Delta;    // 外环周期两拍之间脉冲数差值

} QEP_Typedef;



typedef struct
{
	uint16 WorkMode;                // 控制模式
	uint16 WorkMode_Pre;            // 控制模式
	uint16 PulseMode;                // 脉冲模式
	uint16 PulseMode_Pre;           // 脉冲模式历史值

	uint16 DQKQSel;
	uint16 DriveCtrl;
	uint16 DriveMode;
	uint16 DigInStatus;
	uint16 FlashCtrl;
	uint16 ProfileCtrl;
} RegParamTypeDef;

// Analog Input
typedef struct
{
	int16 AnInValue;
	int16 AnInValue_s;
	int32 AnInValue_k; // 低通滤波器缓存
} AnInTypeDef;



extern FOCCTRL mcFocCtrl;
extern QEP_Typedef QEP;

extern RegParamTypeDef mcRegParam;
extern AnInTypeDef mcAnalogInput;

extern uint8 SYNC0_Flag;
extern uint8 EscIntStep;
extern volatile uint8 TimerFlag_1ms;   // 不加volatile会被编译器优化，导致取值错误


extern void FOC_Init(void);
extern void FOC_RunModeUpdate(void);
extern void MotorControlInit(void);

extern void Motor_Open(void);
extern void Motor_Stop(void);
extern void Motor_Run(void);

extern void Motor_EnableServo(void);
extern void Motor_DisableServo(void);

extern void UpdateParam(void);

extern int32 Motor_Pulse_Handler(void);

extern void RegenerationHandler(void);
extern void Motor_AnalogIn_Handler(void);

extern void Fan_Control(void);
extern void Check_InPos(void);
extern void UpdateTemperature(void);

extern void VCM_DriverOut(void);

#endif