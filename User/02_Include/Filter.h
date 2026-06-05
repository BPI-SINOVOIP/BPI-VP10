/*
 * Copyright (c) 2023-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : Filter.h
 * Author        : wynn.wang
 * Date          : 2023-08-11
 * Description   : 通用滤波器
 *
 * Record        :
 * V1.0, 2023-08-11, wynn.wang: Created file
 */


/* Define to prevent recursive inclusion -------------------------------------------------------- */
#ifndef __FILTER_H__
#define __FILTER_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "fu7502.h"
#include "math.h"


/*************************************************************************************///External Function
// 1st low pass filter
#define INLPF_Q_SHIFT						(15)
#define INLPF_Q_HALF						(int32)(1 << (INLPF_Q_SHIFT - 1))
#define pi_Q15								(102944)


// 分配的内存大小(字节)
#define LPFILT_MEM_SIZE						( 44 )
#define POSLPFILT_MEM_SIZE					( 36 )
#define AVGFILT_MEM_SIZE					( 526 )



typedef struct LowPassFiltTypedef_t LowPassFiltTypedef;
typedef struct PosLowPassFiltTypedef_t PosLowPassFiltTypedef;
typedef struct AvgFiltTypedef_t AvgFiltTypedef;


extern LowPassFiltTypedef* LowPassFilt_Init(void* memory_buffer, int32 freq, int32 sampFreq);
extern int32 LowPassFilt_realize(LowPassFiltTypedef* p, int32 Input);
extern void LowPassFilt_Clr(LowPassFiltTypedef* p);

extern PosLowPassFiltTypedef* PosLowPassFilt_Init(void* memory_buffer, int32 freq, int32 sampFreq);
extern int32 PosLowPassFilt_realize(PosLowPassFiltTypedef* p, int32 Input);
extern void PosLowPassFilt_Clr(PosLowPassFiltTypedef* p);

extern AvgFiltTypedef* AvgFilt_Init(void* memory_buffer, uint16 filtSize);
extern int16 AvgFilt_realize(AvgFiltTypedef* p, int16 Input);
extern void AvgFilt_Clr(AvgFiltTypedef* p);

#ifdef __cplusplus
}
#endif

#endif
