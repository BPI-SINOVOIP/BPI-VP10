/*
 * Copyright (c) 2024-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : MotorIdentify.h
 * Author        : wynn.wang
 * Date          : 2024-12-02
 * Description   : 电机参数辨识和惯量识别初始化
 *
 * Record        :
 * V1.0, 2024-12-02, wynn.wang: Created file
 */


/* Define to prevent recursive inclusion -------------------------------------------------------- */
#ifndef __MOTORIDENTIFY_H_
#define __MOTORIDENTIFY_H_


#include <Myproject.h>


extern MotorEstCfgTypeDef mcEstCfg;
extern InFricIdCfgTypedef InFricIdCfg;


extern void Motor_Identify_Init(void);
extern void InFricId_Demo_Init(void);

#endif

