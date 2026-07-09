/*
 * Copyright (c) 2025-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : Gantry.h
 * Author        : wynn.wang
 * Date          : 2025-12-05
 * Description   : Gantry control
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



// Function code update

/* ------ FeedBack Type ------ */
/* ------ Static structure used for variables with fixed values; not cleared ------ */
typedef struct
{
	
} GanTryStaticTypedf;

/* ------ Dynamic structure used for variables that change in real-time; need to be cleared ------ */
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