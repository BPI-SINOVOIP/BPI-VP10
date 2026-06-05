/*
 * Copyright (c) 2025-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : Gantry.h
 * Author        : wynn.wang
 * Date          : 2025-12-05
 * Description   : 龙门控制
 *
 * Record        :
 * V1.0, 2025-12-05, wynn.wang: Created file
 */

/* Define to prevent recursive inclusion -------------------------------------------------------- */
#ifndef __GANTRY_H__
#define __GANTRY_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "fu7502.h"
#include "Parameter.h"



// 功能码更新

/* ------ FeedBack Type ------ */
/* ------ 静态结构体用于固定值的变量，不清除 ------ */
typedef struct
{
	
} GanTryStaticTypedf;

/* ------ 动态结构体用于实时变化的变量，需要清除 ------ */
typedef struct
{	
	
} GanTryEvalTypedf;

typedef struct
{
	GanTryStaticTypedf Static;
	GanTryEvalTypedf Eval;
	
} GanTryTypedf;
/*************************************************************************************///External Function
extern GanTryTypedf GanTryCtrl;


#ifdef __cplusplus
}
#endif

#endif