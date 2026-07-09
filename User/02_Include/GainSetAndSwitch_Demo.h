/*
 * Copyright (c) 2023-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : GainSetAndSwitch_Demo.h
 * Author        : wynn.wang
 * Date          : 2023-08-11
 * Description   : Gain switching
 *
 * Record        :
 * V1.0, 2023-08-11, wynn.wang: Created file
 */


/* Define to prevent recursive inclusion -------------------------------------------------------- */
#ifndef __GAINSETANDSWITCH_DEMO_H__
#define __GAINSETANDSWITCH_DEMO_H__

#ifdef __cplusplus
extern "C"{
#endif

#include <Myproject.h>

/*************************************************************************************///External Function

extern GnSWPCfgTypedef GainSWCfg;

extern void GainSW_Demo_Init(void);
extern void GainSW_Demo_Update(void);
extern void GainSW_Demo_realize(void);


#ifdef __cplusplus
}
#endif

#endif