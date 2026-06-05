/*
 * FreeModbus Libary: RT-Thread Port
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
 * File: $Id: port.c,v 1.60 2015/02/01 9:18:05 Armink $
 *		 $Id: port.c,v 2.01 2022/05/13 11:09:05 Summer.li: 针对峰岹MCU芯片做相应修改 $
 */

/* ----------------------- System includes --------------------------------*/

/* ----------------------- Modbus includes ----------------------------------*/
#include "port.h"
/* ----------------------- Variables ----------------------------------------*/

/* ----------------------- Start implementation -----------------------------*/
void EnterCriticalSection(void)
{
//    rt_enter_critical();
}

void ExitCriticalSection(void)
{
//    rt_exit_critical();
}

