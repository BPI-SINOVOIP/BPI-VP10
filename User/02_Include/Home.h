/*
 * Copyright (c) 2021-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : Home.h
 * Author        : Summer
 * Date          : 2021-11-13
 * Description   : define some function for home.
 *
 * Record        :
 * V1.0, 2021-11-13, Summer: Created file
 */


#ifndef __HOME_H_
#define __HOME_H_
/* Define to prevent recursive inclusion -------------------------------------*/

#define DisengagNLimitToIndex          (1)             // 离开负限位后，第一个index标记回零。
#define DisengagPLimitToIndex          (2)             // 离开正限位后，第一个index标记回零。
#define DisengagHomeSwitchPToIndex     (3)             // 离开回零开关后，第一个index标记回零（正行程回零开关）。
#define DisengagHomeSwitchNToIndex     (5)             // 离开回零开关后，第一个index标记回零（负行程回零开关）。
#define NToIndex                       (33)            // index标记为零位，负方向移动。
#define PToIndex                       (34)            // index标记为零位，正方向移动。
#define NowPositionAsHome              (35)            // 声明当前位置为零位。
#define HardStopNToIndex               (-33)           // 撞硬限位后找第一个index回零（负硬限位）。
#define HardStopPToIndex               (-34)           // 撞硬限位后找第一个index回零（正硬限位）。
#define HardStopN                      (-125)          // 撞硬限位后停止（负硬限位）。
#define HardStopP                      (-126)          // 撞硬限位后停止（正硬限位）。

// Home state machine
#define HOME_IDLE						(0)             //
#define HOME_START						(1)             //
#define HOME_SEARCHLIMIT				(2)             //
#define HOME_REACHLIMIT					(3)             //
#define HOME_SEARCHINDEX				(4)             //
#define HOME_CATCHINDEX					(5)             //
#define HOME_TURNAROUND					(6)             //
#define HOME_SLOWDOWN					(7)             //
#define HOME_GETABS						(8)             //
#define HOME_GOTOZERO					(9)             //
#define HOME_FINISH						(10)            //

#define HomeBlockEndWaitTime           (50.0)       // (ms)


typedef struct
{
    uint8  State;
    uint8  NextState;
    uint8  FinishFlag;
    uint16 TimeCounter;
    int32  MoveDistance;
    int32  EncThetaBuffer;
    int32  LoadEncThetaBuffer;
    uint8  ZCapturedFlag;
    uint16 HomeSpeed;
    uint16 ZeroSpeed;
    uint16 HomeAcc;
    uint8  SkipFaultOverPosErr;
    uint16 LimitButton;
    
    uint8  EnableStatus;
}HomeTypeDef;


extern HomeTypeDef          mcDoHome;


extern void Motor_Home(void);
extern void DoHoming(void);
extern void Home_Reset(void);
extern void Home_ZCaptured(void);
extern void Home_TimeCount(void);

#endif