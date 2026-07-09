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

#define DisengagNLimitToIndex          (1)             // After leaving the negative limit, the first index mark is reset to zero.
#define DisengagPLimitToIndex          (2)             // After leaving the positive limit, the first index mark is reset to zero.
#define DisengagHomeSwitchPToIndex     (3)             // After leaving the home switch, the first index mark is reset to zero (positive travel home switch).
#define DisengagHomeSwitchNToIndex     (5)             // After leaving the home switch, the first index mark is reset to zero (negative travel home switch).
#define NToIndex                       (33)            // Index mark set as zero position, move in negative direction.
#define PToIndex                       (34)            // Index mark set as zero position, move in positive direction.
#define NowPositionAsHome              (35)            // Declare current position as zero.
#define HardStopNToIndex               (-33)           // After hitting the hard negative limit, find the first index to reset to zero (negative hard limit).
#define HardStopPToIndex               (-34)           // After hitting the hard positive limit, find the first index to reset to zero (positive hard limit).
#define HardStopN                      (-125)          // Stop after hitting hard negative limit (negative hard limit).
#define HardStopP                      (-126)          // Stop after hitting hard positive limit (positive hard limit).

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
    uint16 HomeSpeed;
    uint16 ZeroSpeed;
    uint16 HomeAcc;
    
    uint16 LimitButton;
    int16  IqRefLimit;
    uint8  SkipFaultOverPosErr;
    uint8  EnableStatus;
}HomeTypeDef;


extern HomeTypeDef          mcDoHome;


extern void Motor_Home(void);
extern void DoHoming(void);
extern void Home_Reset(void);
extern void Home_ZCaptured(void);
extern void Home_TimeCount(void);

#endif