/*
 * FreeModbus Libary: BARE Port
 * Copyright (C) 2013 Armink <armink.ztl@gmail.com>
 *
 * Modifications Copyright (C) 2022-2026 Fortior Technology Co., Ltd.
 * Author: Summer.li <summer.li@fortiortech.com>
 * 
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * File: $Id: port.h,v 1.60 2013/08/13 15:07:05 Armink add Master Functions $
 *		 $Id: port.h,v 2.01 2022/05/13 11:09:05 Summer.li: 针对峰岹MCU芯片做相应修改 $
 */

#ifndef _PORT_H
#define _PORT_H


#include "mbconfig.h"

#include <assert.h>
#include <stdint.h>

#define INLINE
#define PR_BEGIN_EXTERN_C           extern "C" {
#define PR_END_EXTERN_C             }

#define ENTER_CRITICAL_SECTION()    // EnterCriticalSection()
#define EXIT_CRITICAL_SECTION()    // ExitCriticalSection()


//此处需修改成宏定义模式，否则与ecat协议栈相关定义冲突  by Victor 20230321
//typedef unsigned char  BOOL;
#ifndef BOOL
#define BOOL                                      unsigned char
#endif

//typedef unsigned char UCHAR;
#ifndef UCHAR
#define UCHAR                                     unsigned char
#endif
//typedef char    CHAR;
#ifndef CHAR
#define CHAR									  char
#endif

//typedef unsigned short USHORT;
#ifndef USHORT
#define USHORT									  unsigned short
#endif
//typedef short SHORT;
#ifndef SHORT
#define SHORT									  short
#endif

//typedef unsigned long ULONG;
#ifndef ULONG
#define ULONG									  unsigned long
#endif
//typedef long LONG;
#ifndef LONG
#define LONG									  long
#endif


typedef struct
{
	BOOL RxEnable;
	BOOL TxEnable;
} PortSerialTypeDef;


extern PortSerialTypeDef PortSerial;


#ifndef TRUE
#define TRUE            1
#endif

#ifndef FALSE
#define FALSE           0
#endif

void EnterCriticalSection(void);
void ExitCriticalSection(void);


#endif
