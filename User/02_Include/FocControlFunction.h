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


#define FOC_REG_CLEAR_OFFSET				(136) // Start address for clearing in FOC_Init


typedef struct
{
	uint8 PosLoopTime;             // Position Loop Time
	uint8 PosLoopTimeLatch;
	uint8 VelLoopTime;             // Speed Loop Time
	uint8 MultiOffsetFirstFlag;
	uint8 MultiOffsetFirstCounter;
	uint16 State_Count;	            // Time count for each motor state
	uint16 ModeSwitchFlag;
	
	int32 ThetaErr;
	int32 ActPos;
	int32 ActLoadPos;
	int32 QepPos;
	int32 QepPosMulti;
	int32 QepThetaOffset;           // PosOffset
	int32 QepLoadThetaOffset;
	int16 QepPosDiff;

	int16 QepSpeedCoe;
	uint32 EncRes;
	uint32 SfbEncRes;
	uint32 AngToCnt;         // Encoder count per electrical circle

	int32 ActualAngle;				  // Actual position after error calibration
	int32 ActualAngleRaw;			  // Actual position before error calibration
	
	int32 TargetAngleFilt;            // Filtered target position
	int32 TargetAngle;                // Target position before filtering
	int32 TargetAngleLatch;           // Latched target position before filtering
	int32 TargetRef;                  // Position command increment per cycle of the position loop
	int32 TargetReftoSpd;             // Speed corresponding to the position command increment per cycle of the position loop
	int32 TargetAngleSum;             // Sum of position command increments
	uint8 TargetRefFirstFlag;		  // Flag for computing position command increment

	int16 mcIqRef;                    // Iq Ref before LPF
	int16 focIqRef;                   // Iq Ref after LPF

	uint8 CurLoopEnable;
	uint8 VelLoopEnable;
	uint8 PosLoopEnable;
	uint8 FrcLoopEnable;			  // Pressure loop enable flag

	uint8 DigitalInPre;
	
	uint8 AngDir;  // 1: encoder direction is opposite to ActPos
	uint8 LoadAngDir;
	uint8 EAngDir;  // 1: electrical angle direction is opposite to ActPos
	
	uint16 InPosCounter;  // Accumulated time for in-position calculation
	uint8 RunMod;
	uint8 DrvComrVal;				// Flag for switching carrier interrupt trigger point
	uint8 VelCnt;
	uint8 Timer1msCount;
	
	uint8 ChargeStep;				// Pre-charge step
	uint8 ChargeFinish;				// Pre-charge completion flag

} FOCCTRL;




typedef struct
{
	uint16 WorkMode;                // Control mode
	uint16 WorkMode_Pre;            // Control mode
	uint16 PulseMode;                // Pulse mode
	uint16 PulseMode_Pre;           // Pulse mode historical value

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
	int32 AnInValue_k; // Low-pass filter buffer
} AnInTypeDef;



extern FOCCTRL mcFocCtrl;

extern RegParamTypeDef mcRegParam;
extern AnInTypeDef mcAnalogInput;

extern uint8 SYNC0_Flag;
extern uint8 EscIntStep;
extern volatile uint8 TimerFlag_1ms;   // Without volatile, compiler optimizations may cause incorrect reads


extern void FOC_Init(void);
extern void FOC_RunModeUpdate(void);
extern void MotorControlInit(void);

extern void Motor_Open(void);
extern void Motor_Run(void);

extern void Motor_EnableServo(void);
extern void Motor_DisableServo(void);

extern void UpdateParam(void);

extern int32 Motor_Pulse_Handler(void);

extern void RegenerationHandler(void);
extern void Motor_AnalogIn_Handler(void);

extern void Fan_Control(void);
extern void Check_InPos(void);


extern void VCM_DriverOut(void);

#endif