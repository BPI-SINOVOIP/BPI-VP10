/*
 * FreeModbus Libary: user callback functions and buffer define in slave mode
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
 * File: $Id: user_mb_app.h,v 1.60 2013/11/23 11:49:05 Armink $
 *		 $Id: user_mb_app.h,v 2.01 2022/05/13 11:09:05 Summer.li: 添加伺服电机控制相关的扩展寄存器映射 $
 */

#ifndef USER_APP
#define USER_APP
/* ----------------------- Modbus includes ----------------------------------*/
#include "mb.h"
#include "mbconfig.h"
#include "mbframe.h"


/* -----------------------Slave Defines -------------------------------------*/
#define S_DISCRETE_INPUT_START        (0)
#define S_DISCRETE_INPUT_NDISCRETES   (0)  // 16
#define S_COIL_START                  (0)
#define S_COIL_NCOILS                 (0)  // 64
#define S_REG_INPUT_START             (0)
#define S_REG_INPUT_NREGS             (160)
#define S_REG_HOLDING_START           (0)
#define S_REG_HOLDING_NREGS           (800)

#define S_REG_SCOPE_START             (0)
#define S_REG_SCOPE_NREGS             (1200)


/* -----------------------Slave ID -------------------------------------*/
#define MODEBUS_SLAVE_ID				( 0x01 )  //


/* -----------------------Basic function Defines -------------------------------------*/
#ifndef SetReg
#define SetReg(reg, val1, val2)         ((reg) = ((reg) & (~(val1))) | ((val2) & (val1)))    // 将reg中val1对应的位写val2
#endif

#ifndef GetReg
#define GetReg(reg, val1)               ((reg) & (val1))						// 获取reg中val1的值
#endif

#ifndef SetBit
#define SetBit(reg, val)                ((reg) |=  (val))                       // 将reg中val对应的位写1
#endif

#ifndef ClrBit
#define ClrBit(reg, val)                ((reg) &= ~(val))                       // 将reg中val对应的位写0
#endif

#ifndef XorBit
#define XorBit(reg, val)                ((reg) ^=  (val))                       // 将reg中val对应的位取反
#endif

#ifndef ReadBit
#define ReadBit(reg, val)               (((reg) & (val)) != 0)                  // 判断reg中val对应的位是否为1
#endif


/////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////// Holding Register /////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////
// 变量分组
#define S_REG_HOLDING_INDEX_CTRL				(0)
#define S_REG_HOLDING_INDEX_COMMUNICATION		(1)
#define S_REG_HOLDING_INDEX_DRIVER				(2)
#define S_REG_HOLDING_INDEX_MOTOR				(3)
#define S_REG_HOLDING_INDEX_FEEDBACK			(4)
#define S_REG_HOLDING_INDEX_CONTROLLER			(5)
#define S_REG_HOLDING_INDEX_OUTFILT				(6)
#define S_REG_HOLDING_INDEX_LIMIT				(7)
#define S_REG_HOLDING_INDEX_MOTION				(8)
#define S_REG_HOLDING_INDEX_FORCECTRL			(9)
#define S_REG_HOLDING_INDEX_DIGITAL				(10)
#define S_REG_HOLDING_INDEX_ANALOG				(11)
#define S_REG_HOLDING_INDEX_TEST				(12)
#define S_REG_HOLDING_INDEX_ERRCOR				(13)

#define S_REG_HOLDING_INDEX_MAX  				(14)

// 每一组的变量个数
#define S_REG_HOLDING_SIZE_CTRL					(5)
#define S_REG_HOLDING_SIZE_COMMUNICATION		(16)
#define S_REG_HOLDING_SIZE_DRIVER				(28)
#define S_REG_HOLDING_SIZE_MOTOR				(42)
#define S_REG_HOLDING_SIZE_FEEDBACK				(40)
#define S_REG_HOLDING_SIZE_CONTROLLER			(110)
#define S_REG_HOLDING_SIZE_OUTFILT				(98)
#define S_REG_HOLDING_SIZE_LIMIT				(60)
#define S_REG_HOLDING_SIZE_MOTION				(40)
#define S_REG_HOLDING_SIZE_FORCECTRL			(156)
#define S_REG_HOLDING_SIZE_DIGITAL				(28)
#define S_REG_HOLDING_SIZE_ANALOG				(7)
#define S_REG_HOLDING_SIZE_TEST					(10)
#define S_REG_HOLDING_SIZE_ERRCOR				(73)


#define S_REG_HOLDING_START_CTRL				(0)
#define S_REG_HOLDING_START_COMMUNICATION		(S_REG_HOLDING_START_CTRL + S_REG_HOLDING_SIZE_CTRL)
#define S_REG_HOLDING_START_DRIVER				(S_REG_HOLDING_START_COMMUNICATION + S_REG_HOLDING_SIZE_COMMUNICATION)
#define S_REG_HOLDING_START_MOTOR				(S_REG_HOLDING_START_DRIVER + S_REG_HOLDING_SIZE_DRIVER)
#define S_REG_HOLDING_START_FEEDBACK			(S_REG_HOLDING_START_MOTOR + S_REG_HOLDING_SIZE_MOTOR)
#define S_REG_HOLDING_START_CONTROLLER			(S_REG_HOLDING_START_FEEDBACK + S_REG_HOLDING_SIZE_FEEDBACK)
#define S_REG_HOLDING_START_OUTFILT				(S_REG_HOLDING_START_CONTROLLER + S_REG_HOLDING_SIZE_CONTROLLER)
#define S_REG_HOLDING_START_LIMIT				(S_REG_HOLDING_START_OUTFILT + S_REG_HOLDING_SIZE_OUTFILT)
#define S_REG_HOLDING_START_MOTION				(S_REG_HOLDING_START_LIMIT + S_REG_HOLDING_SIZE_LIMIT)
#define S_REG_HOLDING_START_FORCECTRL			(S_REG_HOLDING_START_MOTION + S_REG_HOLDING_SIZE_MOTION)	//NEW
#define S_REG_HOLDING_START_DIGITAL				(S_REG_HOLDING_START_FORCECTRL + S_REG_HOLDING_SIZE_FORCECTRL)
#define S_REG_HOLDING_START_ANALOG				(S_REG_HOLDING_START_DIGITAL + S_REG_HOLDING_SIZE_DIGITAL)
#define S_REG_HOLDING_START_TEST				(S_REG_HOLDING_START_ANALOG + S_REG_HOLDING_SIZE_ANALOG)
#define S_REG_HOLDING_START_ERRCOR				(S_REG_HOLDING_START_TEST + S_REG_HOLDING_SIZE_TEST)

#define S_REG_HOLDING_SIZE_TOTAL				(S_REG_HOLDING_START_ERRCOR + S_REG_HOLDING_SIZE_ERRCOR)


//************** 控制参数 S_REG_HOLDING_INDEX_CTRL (0) **************//
#define DRIVECTRL								(S_REG_HOLDING_START_CTRL + 0) // 控制字, 详见后面
#define DRIVEMODE								(S_REG_HOLDING_START_CTRL + 1) // 控制模式, 详见后面
// 0xE8E8->0x5A5A: upload parameter from flash; 0xE8E8->0xA5A5: download Holding register to flash;
#define FLASHCTRL								(S_REG_HOLDING_START_CTRL + 2) // Flash操作
#define OPMODESWITCH							(S_REG_HOLDING_START_CTRL + 3) // 模式切换
#define DRIVESWITCH								(S_REG_HOLDING_START_CTRL + 4) // 控制开关, 详见后面


//************** 通信参数 S_REG_HOLDING_INDEX_COMMUNICATION (1) **************//
#define SCOPECTRL								(S_REG_HOLDING_START_COMMUNICATION + 0) // 示波器采样控制
#define SCOPEADDR_0								(S_REG_HOLDING_START_COMMUNICATION + 1) // 示波器变量0地址
#define SCOPEADDR_1								(S_REG_HOLDING_START_COMMUNICATION + 2) // 示波器变量1地址
#define SCOPEADDR_2								(S_REG_HOLDING_START_COMMUNICATION + 3) // 示波器变量2地址
#define SCOPEADDR_3								(S_REG_HOLDING_START_COMMUNICATION + 4) // 示波器变量3地址
#define SCOPEADDR_4								(S_REG_HOLDING_START_COMMUNICATION + 5) // 示波器变量4地址
#define SCOPEADDR_5								(S_REG_HOLDING_START_COMMUNICATION + 6) // 示波器变量5地址
#define SCOPENUM								(S_REG_HOLDING_START_COMMUNICATION + 7) // 示波器每个变量采样的次数
#define SCOPEINTERVAL							(S_REG_HOLDING_START_COMMUNICATION + 8) // 示波器采样间隔
#define SCOPETRIGADDR							(S_REG_HOLDING_START_COMMUNICATION + 9) // 触发采样变量地址
#define SCOPETRIGLEVEL_L						(S_REG_HOLDING_START_COMMUNICATION + 10) // 触发采样阈值，低16位
#define SCOPETRIGLEVEL_H						(S_REG_HOLDING_START_COMMUNICATION + 11) // 触发采样阈值，高16位
#define SCOPETRIGPRE							(S_REG_HOLDING_START_COMMUNICATION + 12) // 触发采样前记录的点数
#define CANBITRATE								(S_REG_HOLDING_START_COMMUNICATION + 13) // CAN波特率
#define COMMADDR								(S_REG_HOLDING_START_COMMUNICATION + 14) // CAN通信地址ID
#define FBSYNCSET								(S_REG_HOLDING_START_COMMUNICATION + 15) // CAN同步周期

//************** 驱动器参数 S_REG_HOLDING_INDEX_DRIVER (2) **************//
#define CURCOE									(S_REG_HOLDING_START_DRIVER + 0) // 电流转换系数, count/A
#define DRIVERPEAKCUR							(S_REG_HOLDING_START_DRIVER + 1) // 驱动器峰值电流
#define DRIVERRMSCUR							(S_REG_HOLDING_START_DRIVER + 2) // 驱动器额定电流
#define VBUS									(S_REG_HOLDING_START_DRIVER + 3) // 驱动母线电压
#define VOLGAIN									(S_REG_HOLDING_START_DRIVER + 4) // 母线电压计算转换系数：增益
#define VOLOFFSET								(S_REG_HOLDING_START_DRIVER + 5) // 母线电压计算转换系数：偏置
#define REGENVMHIGH								(S_REG_HOLDING_START_DRIVER + 6) // 再生制动的电压上限
#define REGENVMLOW								(S_REG_HOLDING_START_DRIVER + 7) // 再生制动的电压下限
#define REGENPOW								(S_REG_HOLDING_START_DRIVER + 8) // 再生电阻的功率
#define REGENRES								(S_REG_HOLDING_START_DRIVER + 9) // 再生电阻的阻值
#define REGENCOE								(S_REG_HOLDING_START_DRIVER + 10) // 再生制动的计算系数
#define UDCMAX									(S_REG_HOLDING_START_DRIVER + 11) // 母线电压波动上限，用于电流环复矢量控制器
#define UDCMIN									(S_REG_HOLDING_START_DRIVER + 12) // 母线电压波动下限，用于电流环复矢量控制器
#define DEADCOMPCUR								(S_REG_HOLDING_START_DRIVER + 13) // 启动死区补偿的电流阈值
#define DISMODE									(S_REG_HOLDING_START_DRIVER + 14) // 停机模式
#define STOPCURRENT								(S_REG_HOLDING_START_DRIVER + 15) // 动态制动电流
#define STOPCURLIM								(S_REG_HOLDING_START_DRIVER + 16) // 停机电流阈值
#define DISSPEED								(S_REG_HOLDING_START_DRIVER + 17) // 停机速度
#define DISDEC									(S_REG_HOLDING_START_DRIVER + 18) // 停机减速度
#define DISDECTIME								(S_REG_HOLDING_START_DRIVER + 19) // 停机减速时间
#define DISTIME									(S_REG_HOLDING_START_DRIVER + 20) // 停机确认时间
#define DISTIMEOUT								(S_REG_HOLDING_START_DRIVER + 21) // 停机超时时间
#define IDQLPFK									(S_REG_HOLDING_START_DRIVER + 22) // ID/IQ低通滤波系数
#define UDQLPFK									(S_REG_HOLDING_START_DRIVER + 23) // UD/UQ低通滤波系数
#define DEADTIME								(S_REG_HOLDING_START_DRIVER + 24) // 死区时间
#define ISAMDELAY								(S_REG_HOLDING_START_DRIVER + 25) // 采样延时时间
#define MINPWMWIDTH								(S_REG_HOLDING_START_DRIVER + 26) // 最小采样脉宽
#define VOLDEN									(S_REG_HOLDING_START_DRIVER + 27) // 母线电压计算转换系数：分母

//************** 电机参数 S_REG_HOLDING_INDEX_MOTOR (3) **************//
#define POLES									(S_REG_HOLDING_START_MOTOR + 0) // 旋转电机: 极个数; 直线电机: 2
#define PITCH_L									(S_REG_HOLDING_START_MOTOR + 1) // 旋转电机: 1000; 直线电机: 极距, um
#define PITCH_H									(S_REG_HOLDING_START_MOTOR + 2)  
#define MASS_L									(S_REG_HOLDING_START_MOTOR + 3) // 电机惯量, kg·cm^2 or kg, Q10
#define MASS_H									(S_REG_HOLDING_START_MOTOR + 4) 
#define FORCECONST								(S_REG_HOLDING_START_MOTOR + 5) // 转矩常数, Nm/A or N/A, Q7
#define INDUCTANCE								(S_REG_HOLDING_START_MOTOR + 6) // 线电感, mH, Q8
#define RESISTANCE								(S_REG_HOLDING_START_MOTOR + 7) // 线电阻, Ohms, Q8
#define MOTORMAXSPEED							(S_REG_HOLDING_START_MOTOR + 8) // 电机最大速度, rpm, mm/s
#define QEPSPEEDCOE								(S_REG_HOLDING_START_MOTOR + 9) // 速度计算转换系数
#define SPEEDCOERANK							(S_REG_HOLDING_START_MOTOR + 10) // 速度计算转换系数2
#define HARDCURRENT								(S_REG_HOLDING_START_MOTOR + 11) // 电机硬件过流保护电流, count
#define PEAKCURRENT								(S_REG_HOLDING_START_MOTOR + 12) // 电机峰值电流, count
#define RMSCURRENT								(S_REG_HOLDING_START_MOTOR + 13) // 电机额定电流, count
#define LMJREST				     				(S_REG_HOLDING_START_MOTOR + 14) // 惯量辨识使能
#define LMJR				     				(S_REG_HOLDING_START_MOTOR + 15) // 惯量比 = 负载惯量/电机惯量, 0.1倍
#define LMJRHIGHSPEED				     		(S_REG_HOLDING_START_MOTOR + 16) // 惯量辨识的电机最高运行速度
#define LMJRSTARTRATIO				     		(S_REG_HOLDING_START_MOTOR + 17) // 惯量辨识的起始速度百分比
#define LMJRCALCLENGTH				     		(S_REG_HOLDING_START_MOTOR + 18) // 惯量辨识的检测数据长度
#define MOTORNAME_0				     			(S_REG_HOLDING_START_MOTOR + 19) // 电机名称
#define MOTORNAME_1				     			(S_REG_HOLDING_START_MOTOR + 20)
#define MOTORNAME_2				     			(S_REG_HOLDING_START_MOTOR + 21)
#define MOTORNAME_3				     			(S_REG_HOLDING_START_MOTOR + 22)
#define MOTORNAME_4				     			(S_REG_HOLDING_START_MOTOR + 23)
#define MOTORNAME_5				     			(S_REG_HOLDING_START_MOTOR + 24)
#define MOTORNAME_6				     			(S_REG_HOLDING_START_MOTOR + 25)
#define MOTORNAME_7				     			(S_REG_HOLDING_START_MOTOR + 26)
#define DINDUCTANCE				     			(S_REG_HOLDING_START_MOTOR + 27) // D轴电感
#define BEMFCONST				     			(S_REG_HOLDING_START_MOTOR + 28) // 反电势常数, V/(rad/s) or V/(m/s), Q7
#define MOTORRATEDSPEED							(S_REG_HOLDING_START_MOTOR + 29) // 电机额定速度, count
#define ESTMODE				     				(S_REG_HOLDING_START_MOTOR + 30) // 电机参数辨识模式
#define ESTIAMP									(S_REG_HOLDING_START_MOTOR + 31) // 电机参数辨识电流幅值
#define ESTIMINRATIO							(S_REG_HOLDING_START_MOTOR + 32) // 电机电阻辨识电流最小值百分比
#define ESTRTIME				     			(S_REG_HOLDING_START_MOTOR + 33) // 电机电阻辨识每一段信号的持续时间
#define ESTLTIME				     			(S_REG_HOLDING_START_MOTOR + 34) // 电机电感辨识每一段信号的持续时间
#define ESTUMAX				     				(S_REG_HOLDING_START_MOTOR + 35) // 电机电感辨识最大电压
#define ESTUMIN				     				(S_REG_HOLDING_START_MOTOR + 36) // 电机电感辨识初始电压
#define ESTUDELTA				     			(S_REG_HOLDING_START_MOTOR + 37) // 电机电感辨识电压增量
#define ESTFMAX				     				(S_REG_HOLDING_START_MOTOR + 38) // 电机电感辨识最大频率
#define ESTFMIN				     				(S_REG_HOLDING_START_MOTOR + 39) // 电机电感辨识最小频率
#define ESTFDELTA								(S_REG_HOLDING_START_MOTOR + 40) // 电机电感辨识频率增量
#define ESTRRATIO				     			(S_REG_HOLDING_START_MOTOR + 41) // 电机电阻辨识结果系数



//************** 编码器参数 S_REG_HOLDING_INDEX_FEEDBACK (4) **************//
#define ENCTYPE 								(S_REG_HOLDING_START_FEEDBACK + 0) // 编码器类型
#define ENCRES_L								(S_REG_HOLDING_START_FEEDBACK + 1) // 编码器一圈分辨率或者一个极距的分辨率, count
#define ENCRES_H								(S_REG_HOLDING_START_FEEDBACK + 2)
#define HALLMODE								(S_REG_HOLDING_START_FEEDBACK + 3) // Hall模式
#define ELECANGSHIFT							(S_REG_HOLDING_START_FEEDBACK + 4) // Hall相移角 / 绝对式编码器电角度偏移角
#define ENCDATABITS								(S_REG_HOLDING_START_FEEDBACK + 5) // 编码器协议数据段总长度
#define ENCVALIDBITS							(S_REG_HOLDING_START_FEEDBACK + 6) // 编码器有效数据长度
#define ENCZEROBITS								(S_REG_HOLDING_START_FEEDBACK + 7) // BiSS低位无效数据长度
#define ENCCLKFREQ								(S_REG_HOLDING_START_FEEDBACK + 8) // BiSS时钟频率
#define AQBFILT									(S_REG_HOLDING_START_FEEDBACK + 9) // AQB的滤波深度
// Encoder Output
#define ENCOUTMODE								(S_REG_HOLDING_START_FEEDBACK + 10) // 编码器仿真输出模式
#define ENCOUTRES_L								(S_REG_HOLDING_START_FEEDBACK + 11) // 编码器仿真输出分辨率, count
#define ENCOUTRES_H								(S_REG_HOLDING_START_FEEDBACK + 12) 
#define ENCOUTMAX								(S_REG_HOLDING_START_FEEDBACK + 13) // 编码器输出最大频率
#define ELECANGSW_L								(S_REG_HOLDING_START_FEEDBACK + 14) // 电角度计算转换系数, _Q16(POLES * 32768 / ENCRES)
#define ELECANGSW_H							    (S_REG_HOLDING_START_FEEDBACK + 15) //
#define ELECANGMW_L								(S_REG_HOLDING_START_FEEDBACK + 16) // 电角度计算转换系数2, _Q15(POLES * 32768 / ENCRES * 65536 * 65536)
#define ELECANGMW_H							    (S_REG_HOLDING_START_FEEDBACK + 17) //
// Phase find
#define PHASEFINDMODE							(S_REG_HOLDING_START_FEEDBACK + 18) // 寻相模式：0: NormalStart; 1: SmoothStart; 8: Autophase
#define PHASEFINDCURRENT						(S_REG_HOLDING_START_FEEDBACK + 19) // 寻相电流
#define PHASEFINDTIMEOUT						(S_REG_HOLDING_START_FEEDBACK + 20) // 寻相超时时间, ms
#define PHASEFINDIDSTEP							(S_REG_HOLDING_START_FEEDBACK + 21) // 每一毫秒命令电流增量值, count
#define PHASEFINDTANGLESTEP						(S_REG_HOLDING_START_FEEDBACK + 22) // 每一毫秒命令电角度的增量值, count
#define PHASEFINDMOVEMENT						(S_REG_HOLDING_START_FEEDBACK + 23) // 电角度变化阈值所对应的编码器值
#define PHASEFINDMOVEANG_L						(S_REG_HOLDING_START_FEEDBACK + 24) // Autophase运动总距离, count-eAngle
#define PHASEFINDMOVEANG_H						(S_REG_HOLDING_START_FEEDBACK + 25)
#define PHASEFINDTIME							(S_REG_HOLDING_START_FEEDBACK + 26) // 寻相过程中的停留时间
#define HALLCOMMTHRESH							(S_REG_HOLDING_START_FEEDBACK + 27) // Halls静止计数大于该值时用6步换相计算电角度，否则用位置插值计算电角度，只用于Halls-Only
#define HALLPOSLPFK								(S_REG_HOLDING_START_FEEDBACK + 28) // Halls-Only位置一阶低通滤波器系数
#define MOTORCOMMTYPE							(S_REG_HOLDING_START_FEEDBACK + 29) // 电机换相类型
#define SFBENCTYPE								(S_REG_HOLDING_START_FEEDBACK + 30) // 负载编码器类型
#define SFBENCRES_L								(S_REG_HOLDING_START_FEEDBACK + 31) // 负载编码器分辨率
#define SFBENCRES_H								(S_REG_HOLDING_START_FEEDBACK + 32)
#define ENCCALCTRL								(S_REG_HOLDING_START_FEEDBACK + 33) // 编码器寄存器读写控制
#define ENCREGADDR								(S_REG_HOLDING_START_FEEDBACK + 34) // 编码器寄存器地址
#define ENCREGVAL								(S_REG_HOLDING_START_FEEDBACK + 35) // 编码器寄存器值
#define ANGOFFSET_L								(S_REG_HOLDING_START_FEEDBACK + 36) // 电机侧位置值偏置
#define ANGOFFSET_H								(S_REG_HOLDING_START_FEEDBACK + 37)
#define SFBANGOFFSET_L							(S_REG_HOLDING_START_FEEDBACK + 38) // 输出侧位置值偏置
#define SFBANGOFFSET_H							(S_REG_HOLDING_START_FEEDBACK + 39)

//************** 三环控制参数 S_REG_HOLDING_INDEX_CONTROLLER (5) **************//
// Current Loop
#define DQKP									(S_REG_HOLDING_START_CONTROLLER + 0) // DQ轴KP, 对应的旧版电流环
#define DQKI									(S_REG_HOLDING_START_CONTROLLER + 1) // DQ轴KI, 对应的旧版电流环
// Velocity Loop
#define VKP										(S_REG_HOLDING_START_CONTROLLER + 2) // 速度环KP
#define VKI										(S_REG_HOLDING_START_CONTROLLER + 3) // 速度环KI
#define VKP2									(S_REG_HOLDING_START_CONTROLLER + 4) // 第二速度环KP2
#define VKI2									(S_REG_HOLDING_START_CONTROLLER + 5) // 第二速度环KI2
#define VFR										(S_REG_HOLDING_START_CONTROLLER + 6) // 伪微分调节器系数(PDFF)
// Position Loop
#define PKP										(S_REG_HOLDING_START_CONTROLLER + 7) // 位置环KP(_Q12)
#define PKI										(S_REG_HOLDING_START_CONTROLLER + 8) // 位置环KI(_Q15)
#define PKP2									(S_REG_HOLDING_START_CONTROLLER + 9) // 第二位置环KP(_Q12)
#define PKI2									(S_REG_HOLDING_START_CONTROLLER + 10) // 第二位置环KI(_Q15)
// Gain Switch
#define GAINSWMODE								(S_REG_HOLDING_START_CONTROLLER + 11) // 增益切换条件
#define GAINSWDLYTM								(S_REG_HOLDING_START_CONTROLLER + 12) // 增益切换延迟时间
#define GAINSWLEVEL								(S_REG_HOLDING_START_CONTROLLER + 13) // 增益切换等级
#define GAINSWHYSTERESIS						(S_REG_HOLDING_START_CONTROLLER + 14) // 增益切换迟滞
#define GAINSWPACCTM							(S_REG_HOLDING_START_CONTROLLER + 15) // 位置增益切换上升斜坡时间
#define GAINSWPDECTM							(S_REG_HOLDING_START_CONTROLLER + 16) // 位置增益切换下降斜坡时间
#define GAINSWVACCTM							(S_REG_HOLDING_START_CONTROLLER + 17) // 速度增益切换上升斜坡时间
#define GAINSWVDECTM							(S_REG_HOLDING_START_CONTROLLER + 18) // 速度增益切换下降斜坡时间

#define INFILTCTRL								(S_REG_HOLDING_START_CONTROLLER + 19) // 滤波器类型
#define INFILT1AVG								(S_REG_HOLDING_START_CONTROLLER + 20) // 位置指令滤波1，滑动平均滤波深度
#define INFILT1LPFK								(S_REG_HOLDING_START_CONTROLLER + 21) // 位置指令滤波1，一阶低通滤波器截止频率
#define INFILT2AVG								(S_REG_HOLDING_START_CONTROLLER + 22) // 位置指令滤波2，滑动平均滤波深度
#define INFILT2LPFK								(S_REG_HOLDING_START_CONTROLLER + 23) // 位置指令滤波2，一阶低通滤波器截止频率
#define INFILT3AVG								(S_REG_HOLDING_START_CONTROLLER + 24) // 速度反馈滤波1，滑动平均滤波深度
#define INFILT3LPFK								(S_REG_HOLDING_START_CONTROLLER + 25) // 速度反馈滤波1，一阶低通滤波器截止频率
#define INFILT4AVG								(S_REG_HOLDING_START_CONTROLLER + 26) // 速度反馈滤波2，滑动平均滤波深度
#define INFILT4LPFK								(S_REG_HOLDING_START_CONTROLLER + 27) // 速度反馈滤波2，一阶低通滤波器截止频率

#define NTF1MODE                                (S_REG_HOLDING_START_CONTROLLER + 28) // 振动抑制模式选择
#define NTF1HZ                                  (S_REG_HOLDING_START_CONTROLLER + 29) // 振动抑制滤波频率 (0.1Hz)
#define NTF1SHARP                               (S_REG_HOLDING_START_CONTROLLER + 30) // 振动抑制滤波锐度 (0.01)
#define NTF1GAIN                                (S_REG_HOLDING_START_CONTROLLER + 31) // 振动抑制阻尼增益 (Rad*10-3/Nm)
#define NTF2MODE                                (S_REG_HOLDING_START_CONTROLLER + 32) // 振动抑制模式选择
#define NTF2HZ                                  (S_REG_HOLDING_START_CONTROLLER + 33) // 振动抑制滤波频率 (0.1Hz)
#define NTF2SHARP                               (S_REG_HOLDING_START_CONTROLLER + 34) // 振动抑制滤波锐度 (0.01)
#define NTF2GAIN                                (S_REG_HOLDING_START_CONTROLLER + 35) // 振动抑制阻尼增益 (Rad*10-3/Nm)

#define PVFRMOD									(S_REG_HOLDING_START_CONTROLLER + 36) // 速度前馈
#define PVFR									(S_REG_HOLDING_START_CONTROLLER + 37) // 速度前馈系数
#define PVFRLPFHZ								(S_REG_HOLDING_START_CONTROLLER + 38) // 速度前馈低通滤波截止频率(0.1Hz)

#define LPF2FREQ                                (S_REG_HOLDING_START_CONTROLLER + 39) // 转矩前馈低通滤波截止频率(0.1Hz)
#define KACCB                                   (S_REG_HOLDING_START_CONTROLLER + 40) // 转矩前馈增益
#define KACMOD                                  (S_REG_HOLDING_START_CONTROLLER + 41) // 转矩前馈来源
#define KACAVG									(S_REG_HOLDING_START_CONTROLLER + 42) // 转矩前馈平滑滤波深度

#define CBW										(S_REG_HOLDING_START_CONTROLLER + 43) // 电流环带宽
#define VBW										(S_REG_HOLDING_START_CONTROLLER + 44) // 速度环带宽

#define NTF1B0_L								(S_REG_HOLDING_START_CONTROLLER + 45) // 振动抑制滤波1系数B0, 低16位
#define NTF1B0_H								(S_REG_HOLDING_START_CONTROLLER + 46) // 振动抑制滤波1系数B0, 高16位
#define NTF1B1_L								(S_REG_HOLDING_START_CONTROLLER + 47)
#define NTF1B2_L								(S_REG_HOLDING_START_CONTROLLER + 48)
#define NTF1A1_L								(S_REG_HOLDING_START_CONTROLLER + 49)
#define NTF1A2_L								(S_REG_HOLDING_START_CONTROLLER + 50)
#define NTF1B1_H								(S_REG_HOLDING_START_CONTROLLER + 51)
#define NTF1B2_H								(S_REG_HOLDING_START_CONTROLLER + 52)
#define NTF1A1_H								(S_REG_HOLDING_START_CONTROLLER + 53)
#define NTF1A2_H								(S_REG_HOLDING_START_CONTROLLER + 54)

#define NTF2B0_L								(S_REG_HOLDING_START_CONTROLLER + 55) // 振动抑制滤波2系数B0, 低16位
#define NTF2B0_H								(S_REG_HOLDING_START_CONTROLLER + 56) // 振动抑制滤波2系数B0, 高16位
#define NTF2B1_L								(S_REG_HOLDING_START_CONTROLLER + 57)
#define NTF2B2_L								(S_REG_HOLDING_START_CONTROLLER + 58)
#define NTF2A1_L								(S_REG_HOLDING_START_CONTROLLER + 59)
#define NTF2A2_L								(S_REG_HOLDING_START_CONTROLLER + 60)
#define NTF2B1_H								(S_REG_HOLDING_START_CONTROLLER + 61)
#define NTF2B2_H								(S_REG_HOLDING_START_CONTROLLER + 62)
#define NTF2A1_H								(S_REG_HOLDING_START_CONTROLLER + 63)
#define NTF2A2_H								(S_REG_HOLDING_START_CONTROLLER + 64)

#define VFR2									(S_REG_HOLDING_START_CONTROLLER + 65) // 伪微分调节器系数2(PDFF)
#define DESATUR									(S_REG_HOLDING_START_CONTROLLER + 66) // 速度环控制器退饱和系数(Q14)

#define IGRAV									(S_REG_HOLDING_START_CONTROLLER + 67) // 重力补偿值
#define FRICMOD									(S_REG_HOLDING_START_CONTROLLER + 68) // 摩擦力功能开启
#define FRICVSRC								(S_REG_HOLDING_START_CONTROLLER + 69) // 摩擦力速度选择：0-PTPCMD 1-CMDVEL 2-ACTVEL
#define FRICIPOS								(S_REG_HOLDING_START_CONTROLLER + 70) // 正向摩擦力补偿值
#define FRICINEG								(S_REG_HOLDING_START_CONTROLLER + 71) // 负向摩擦力补偿值
#define FRICPVHYST								(S_REG_HOLDING_START_CONTROLLER + 72) // 正向摩擦力补偿死区阈值
#define FRICNVHYST								(S_REG_HOLDING_START_CONTROLLER + 73) // 负向摩擦力补偿死区阈值
#define FRICPVTHRESH							(S_REG_HOLDING_START_CONTROLLER + 74) // 摩擦力补偿正向速度阈值
#define FRICNVTHRESH							(S_REG_HOLDING_START_CONTROLLER + 75) // 摩擦里补偿负向速度阈值
#define FRICLPFHZ								(S_REG_HOLDING_START_CONTROLLER + 76) // 摩擦力补偿低通滤波

#define CVMOD									(S_REG_HOLDING_START_CONTROLLER + 77) // 复矢量解耦控制器模式选择
#define CVKQSEL									(S_REG_HOLDING_START_CONTROLLER + 78) // 复矢量解耦控制器Q格式选择
#define CVKI2D									(S_REG_HOLDING_START_CONTROLLER + 79) // 复矢量解耦控制器系数D轴KI2
#define CVKI2Q									(S_REG_HOLDING_START_CONTROLLER + 80) // 复矢量解耦控制器系数Q轴KI2
#define CVK1									(S_REG_HOLDING_START_CONTROLLER + 81) // 复矢量解耦控制器系数1
#define CVK2									(S_REG_HOLDING_START_CONTROLLER + 82) // 复矢量解耦控制器系数2
#define CVK3									(S_REG_HOLDING_START_CONTROLLER + 83) // 复矢量解耦控制器系数3
#define CVDK4									(S_REG_HOLDING_START_CONTROLLER + 84) // 复矢量解耦控制器系数4
#define CVQK4									(S_REG_HOLDING_START_CONTROLLER + 85) // 复矢量解耦控制器系数4
#define CVDK5									(S_REG_HOLDING_START_CONTROLLER + 86) // 复矢量解耦控制器系数5
#define CVQK5									(S_REG_HOLDING_START_CONTROLLER + 87) // 复矢量解耦控制器系数5
#define CFR										(S_REG_HOLDING_START_CONTROLLER + 88) // 电流环前馈系数

#define DKP										(S_REG_HOLDING_START_CONTROLLER + 89) // D轴KP, 适用复矢量控制器
#define DKI										(S_REG_HOLDING_START_CONTROLLER + 90) // D轴KI, 适用复矢量控制器
#define QKP										(S_REG_HOLDING_START_CONTROLLER + 91) // Q轴KP, 适用复矢量控制器
#define QKI										(S_REG_HOLDING_START_CONTROLLER + 92) // Q轴KI, 适用复矢量控制器

#define FEEDBACKMODE                            (S_REG_HOLDING_START_CONTROLLER + 93) // 全闭环模式, 0：内环 1：外环 2：内外环切换
#define MIXERRMAXVAL_L                          (S_REG_HOLDING_START_CONTROLLER + 94) // 内、外环偏差的差值超过该值时应该报警（低位）
#define MIXERRMAXVAL_H                          (S_REG_HOLDING_START_CONTROLLER + 95) // 内、外环偏差的差值超过该值时应该报警（高位）
#define MIXERRCLRRPM                            (S_REG_HOLDING_START_CONTROLLER + 96) // 混合偏差清0圈数
#define LOADFEEDPULSE_L                         (S_REG_HOLDING_START_CONTROLLER + 97) // 电机旋转一圈外部编码器的脉冲数（低位）
#define LOADFEEDPULSE_H                         (S_REG_HOLDING_START_CONTROLLER + 98) // 电机旋转一圈外部编码器的脉冲数（高位）
#define LOADFEEDLPFFREQ                         (S_REG_HOLDING_START_CONTROLLER + 99) // 外环低通滤波器(0.1Hz)

//************** 转矩滤波参数 S_REG_HOLDING_INDEX_OUTFILT (6) **************//
// 4 Output Filter
#define OUTFILTCTRL								(S_REG_HOLDING_START_OUTFILT + 0) // 转矩滤波器类型
#define OUTFILT1HZ1								(S_REG_HOLDING_START_OUTFILT + 1) // 转矩滤波器1参数1，如频率(0.1Hz)
#define OUTFILT1HZ2								(S_REG_HOLDING_START_OUTFILT + 2) // 转矩滤波器1参数2，如阻尼系数
#define OUTFILT1HZ3								(S_REG_HOLDING_START_OUTFILT + 3) // 转矩滤波器1参数3，如滤波深度
#define OUTFILT1HZ4								(S_REG_HOLDING_START_OUTFILT + 4) // 转矩滤波器1参数4，如阻尼(分母)
#define OUTFILT2HZ1								(S_REG_HOLDING_START_OUTFILT + 5) // 转矩滤波器2参数, 同转矩滤波器1
#define OUTFILT2HZ2								(S_REG_HOLDING_START_OUTFILT + 6)
#define OUTFILT2HZ3								(S_REG_HOLDING_START_OUTFILT + 7)
#define OUTFILT2HZ4								(S_REG_HOLDING_START_OUTFILT + 8)
#define OUTFILT3HZ1								(S_REG_HOLDING_START_OUTFILT + 9) // 转矩滤波器3参数
#define OUTFILT3HZ2								(S_REG_HOLDING_START_OUTFILT + 10)
#define OUTFILT3HZ3								(S_REG_HOLDING_START_OUTFILT + 11)
#define OUTFILT3HZ4								(S_REG_HOLDING_START_OUTFILT + 12)
#define OUTFILT4HZ1								(S_REG_HOLDING_START_OUTFILT + 13) // 转矩滤波器4参数
#define OUTFILT4HZ2								(S_REG_HOLDING_START_OUTFILT + 14)
#define OUTFILT4HZ3								(S_REG_HOLDING_START_OUTFILT + 15)
#define OUTFILT4HZ4								(S_REG_HOLDING_START_OUTFILT + 16)

#define OUTFILTQFAC								(S_REG_HOLDING_START_OUTFILT + 17) // 转矩滤波器系数Q值

#define OUT1FILT1B0_L							(S_REG_HOLDING_START_OUTFILT + 18) // 转矩滤波1系数B0, 低15位, 运行于速度环时适用
#define OUT1FILT1B0_H							(S_REG_HOLDING_START_OUTFILT + 19) // 转矩滤波1系数B0, 高15位
#define OUT1FILT1B1_L							(S_REG_HOLDING_START_OUTFILT + 20)
#define OUT1FILT1B2_L							(S_REG_HOLDING_START_OUTFILT + 21)
#define OUT1FILT1A1_L							(S_REG_HOLDING_START_OUTFILT + 22)
#define OUT1FILT1A2_L							(S_REG_HOLDING_START_OUTFILT + 23)
#define OUT1FILT1B1_H							(S_REG_HOLDING_START_OUTFILT + 24)
#define OUT1FILT1B2_H							(S_REG_HOLDING_START_OUTFILT + 25)
#define OUT1FILT1A1_H							(S_REG_HOLDING_START_OUTFILT + 26)
#define OUT1FILT1A2_H							(S_REG_HOLDING_START_OUTFILT + 27)

#define OUT1FILT2B0_L							(S_REG_HOLDING_START_OUTFILT + 28)
#define OUT1FILT2B0_H							(S_REG_HOLDING_START_OUTFILT + 29)
#define OUT1FILT2B1_L							(S_REG_HOLDING_START_OUTFILT + 30)
#define OUT1FILT2B2_L							(S_REG_HOLDING_START_OUTFILT + 31)
#define OUT1FILT2A1_L							(S_REG_HOLDING_START_OUTFILT + 32)
#define OUT1FILT2A2_L							(S_REG_HOLDING_START_OUTFILT + 33)
#define OUT1FILT2B1_H							(S_REG_HOLDING_START_OUTFILT + 34)
#define OUT1FILT2B2_H							(S_REG_HOLDING_START_OUTFILT + 35)
#define OUT1FILT2A1_H							(S_REG_HOLDING_START_OUTFILT + 36)
#define OUT1FILT2A2_H							(S_REG_HOLDING_START_OUTFILT + 37)

#define OUT1FILT3B0_L							(S_REG_HOLDING_START_OUTFILT + 38)
#define OUT1FILT3B0_H							(S_REG_HOLDING_START_OUTFILT + 39)
#define OUT1FILT3B1_L							(S_REG_HOLDING_START_OUTFILT + 40)
#define OUT1FILT3B2_L							(S_REG_HOLDING_START_OUTFILT + 41)
#define OUT1FILT3A1_L							(S_REG_HOLDING_START_OUTFILT + 42)
#define OUT1FILT3A2_L							(S_REG_HOLDING_START_OUTFILT + 43)
#define OUT1FILT3B1_H							(S_REG_HOLDING_START_OUTFILT + 44)
#define OUT1FILT3B2_H							(S_REG_HOLDING_START_OUTFILT + 45)
#define OUT1FILT3A1_H							(S_REG_HOLDING_START_OUTFILT + 46)
#define OUT1FILT3A2_H							(S_REG_HOLDING_START_OUTFILT + 47)

#define OUT1FILT4B0_L							(S_REG_HOLDING_START_OUTFILT + 48)
#define OUT1FILT4B0_H							(S_REG_HOLDING_START_OUTFILT + 49)
#define OUT1FILT4B1_L							(S_REG_HOLDING_START_OUTFILT + 50)
#define OUT1FILT4B2_L							(S_REG_HOLDING_START_OUTFILT + 51)
#define OUT1FILT4A1_L							(S_REG_HOLDING_START_OUTFILT + 52)
#define OUT1FILT4A2_L							(S_REG_HOLDING_START_OUTFILT + 53)
#define OUT1FILT4B1_H							(S_REG_HOLDING_START_OUTFILT + 54)
#define OUT1FILT4B2_H							(S_REG_HOLDING_START_OUTFILT + 55)
#define OUT1FILT4A1_H							(S_REG_HOLDING_START_OUTFILT + 56)
#define OUT1FILT4A2_H							(S_REG_HOLDING_START_OUTFILT + 57)

#define OUT2FILT1B0_L							(S_REG_HOLDING_START_OUTFILT + 58) // 转矩滤波1系数B0, 低15位, 运行于电流环时适用
#define OUT2FILT1B0_H							(S_REG_HOLDING_START_OUTFILT + 59)
#define OUT2FILT1B1_L							(S_REG_HOLDING_START_OUTFILT + 60)
#define OUT2FILT1B2_L							(S_REG_HOLDING_START_OUTFILT + 61)
#define OUT2FILT1A1_L							(S_REG_HOLDING_START_OUTFILT + 62)
#define OUT2FILT1A2_L							(S_REG_HOLDING_START_OUTFILT + 63)
#define OUT2FILT1B1_H							(S_REG_HOLDING_START_OUTFILT + 64)
#define OUT2FILT1B2_H							(S_REG_HOLDING_START_OUTFILT + 65)
#define OUT2FILT1A1_H							(S_REG_HOLDING_START_OUTFILT + 66)
#define OUT2FILT1A2_H							(S_REG_HOLDING_START_OUTFILT + 67)

#define OUT2FILT2B0_L							(S_REG_HOLDING_START_OUTFILT + 68)
#define OUT2FILT2B0_H							(S_REG_HOLDING_START_OUTFILT + 69)
#define OUT2FILT2B1_L							(S_REG_HOLDING_START_OUTFILT + 70)
#define OUT2FILT2B2_L							(S_REG_HOLDING_START_OUTFILT + 71)
#define OUT2FILT2A1_L							(S_REG_HOLDING_START_OUTFILT + 72)
#define OUT2FILT2A2_L							(S_REG_HOLDING_START_OUTFILT + 73)
#define OUT2FILT2B1_H							(S_REG_HOLDING_START_OUTFILT + 74)
#define OUT2FILT2B2_H							(S_REG_HOLDING_START_OUTFILT + 75)
#define OUT2FILT2A1_H							(S_REG_HOLDING_START_OUTFILT + 76)
#define OUT2FILT2A2_H							(S_REG_HOLDING_START_OUTFILT + 77)

#define OUT2FILT3B0_L							(S_REG_HOLDING_START_OUTFILT + 78)
#define OUT2FILT3B0_H							(S_REG_HOLDING_START_OUTFILT + 79)
#define OUT2FILT3B1_L							(S_REG_HOLDING_START_OUTFILT + 80)
#define OUT2FILT3B2_L							(S_REG_HOLDING_START_OUTFILT + 81)
#define OUT2FILT3A1_L							(S_REG_HOLDING_START_OUTFILT + 82)
#define OUT2FILT3A2_L							(S_REG_HOLDING_START_OUTFILT + 83)
#define OUT2FILT3B1_H							(S_REG_HOLDING_START_OUTFILT + 84)
#define OUT2FILT3B2_H							(S_REG_HOLDING_START_OUTFILT + 85)
#define OUT2FILT3A1_H							(S_REG_HOLDING_START_OUTFILT + 86)
#define OUT2FILT3A2_H							(S_REG_HOLDING_START_OUTFILT + 87)

#define OUT2FILT4B0_L							(S_REG_HOLDING_START_OUTFILT + 88)
#define OUT2FILT4B0_H							(S_REG_HOLDING_START_OUTFILT + 89)
#define OUT2FILT4B1_L							(S_REG_HOLDING_START_OUTFILT + 90)
#define OUT2FILT4B2_L							(S_REG_HOLDING_START_OUTFILT + 91)
#define OUT2FILT4A1_L							(S_REG_HOLDING_START_OUTFILT + 92)
#define OUT2FILT4A2_L							(S_REG_HOLDING_START_OUTFILT + 93)
#define OUT2FILT4B1_H							(S_REG_HOLDING_START_OUTFILT + 94)
#define OUT2FILT4B2_H							(S_REG_HOLDING_START_OUTFILT + 95)
#define OUT2FILT4A1_H							(S_REG_HOLDING_START_OUTFILT + 96)
#define OUT2FILT4A2_H							(S_REG_HOLDING_START_OUTFILT + 97)

//************** 限定参数 S_REG_HOLDING_INDEX_LIMIT (7) **************//
#define DOUTMAX									(S_REG_HOLDING_START_LIMIT + 0) // D轴最大限幅值，输出占空比(_Q15)
#define DOUTMIN									(S_REG_HOLDING_START_LIMIT + 1) // D轴最小限幅值
#define QOUTMAX									(S_REG_HOLDING_START_LIMIT + 2) // Q轴最大限幅值
#define QOUTMIN									(S_REG_HOLDING_START_LIMIT + 3) // Q轴最小限幅值
#define VOUTMAX									(S_REG_HOLDING_START_LIMIT + 4) // 速度环输出最大限幅值
#define VOUTMIN									(S_REG_HOLDING_START_LIMIT + 5) // 速度环输出最小限幅值
#define POUTMAX									(S_REG_HOLDING_START_LIMIT + 6) // 位置环输出最大限幅值 (_Q15)
#define POUTMIN									(S_REG_HOLDING_START_LIMIT + 7) // 位置环输出最小限幅值 (_Q15)
#define PEINPOSRANGE							(S_REG_HOLDING_START_LIMIT + 8) // 到位范围
#define PEINPOSTIME								(S_REG_HOLDING_START_LIMIT + 9) // 到位时间窗口
#define PEMAX_L									(S_REG_HOLDING_START_LIMIT + 10) // 位置超差, count
#define PEMAX_H									(S_REG_HOLDING_START_LIMIT + 11) // 
#define PEMAXTIME								(S_REG_HOLDING_START_LIMIT + 12) // 位置超差检测时间, count
#define VEMAX									(S_REG_HOLDING_START_LIMIT + 13) // 速度超差, count
#define VEMAXTIME								(S_REG_HOLDING_START_LIMIT + 14) // 速度超差检测时间, 每个速度环检测一次
#define OVERSPEED								(S_REG_HOLDING_START_LIMIT + 15) // 速度过超, count
#define OVERSPEEDTIME							(S_REG_HOLDING_START_LIMIT + 16) // 速度过超检测时间, 每个载波周期检测一次
#define PEAKCURTIME								(S_REG_HOLDING_START_LIMIT + 17) // 电机峰值过流窗口时间, 每1 ms检测一次
#define RMSCURTIME								(S_REG_HOLDING_START_LIMIT + 18) // 电机RMS过流检测时间, 每1 ms检测一次
#define PHASELOSSCMDCUR							(S_REG_HOLDING_START_LIMIT + 19) // 缺相电流命令阈值
#define PHASELOSSACTCUR							(S_REG_HOLDING_START_LIMIT + 20) // 缺相相电流阈值
#define PHASELOSSANGLE							(S_REG_HOLDING_START_LIMIT + 21) // 缺相电角度变化范围
#define STALLCUR								(S_REG_HOLDING_START_LIMIT + 22) // 堵转电流
#define STALLVEL								(S_REG_HOLDING_START_LIMIT + 23) // 堵转检测时间, 每个载波周期检测一次
#define STALLTIME								(S_REG_HOLDING_START_LIMIT + 24) // 缺相电流值, count  
#define OVERVOLTAGE								(S_REG_HOLDING_START_LIMIT + 25) // 过压保护值
#define OVERVOLTIME								(S_REG_HOLDING_START_LIMIT + 26) // 过压保护窗口时间, 每1 ms检测一次
#define UNDERVOLTAGE							(S_REG_HOLDING_START_LIMIT + 27) // 欠压保护值
#define UNDERVOLTIME							(S_REG_HOLDING_START_LIMIT + 28) // 欠压保护窗口时间, 每1 ms检测一次
#define MOTORTHERMTRIP   						(S_REG_HOLDING_START_LIMIT + 29) // 触发电机过温报错的温度阈值
#define MOTORTHERMCLEAR   						(S_REG_HOLDING_START_LIMIT + 30) // 清除电机过温报错的温度阈值, not used
#define DRIVETHERMTRIP							(S_REG_HOLDING_START_LIMIT + 31) // 触发驱动器过温报错的温度阈值
#define THERMTIME								(S_REG_HOLDING_START_LIMIT + 32) // 过温窗口时间, 每1 ms检测一次
#define MAININTTIME								(S_REG_HOLDING_START_LIMIT + 33) // 主中断超时窗口时间, not used
#define AUXINTDELAY								(S_REG_HOLDING_START_LIMIT + 34) // 从发起子中断到子中断执行的延时时间
#define POSLIMMODE								(S_REG_HOLDING_START_LIMIT + 35) // 软件限位开关
#define POSLIMPOS_L								(S_REG_HOLDING_START_LIMIT + 36) // 软件正限位，低16位
#define POSLIMPOS_H								(S_REG_HOLDING_START_LIMIT + 37) // 软件负限位，低16位
#define POSLIMNEG_L								(S_REG_HOLDING_START_LIMIT + 38) //
#define POSLIMNEG_H								(S_REG_HOLDING_START_LIMIT + 39) // 软件负限位，低16位
#define CUROFFJITTER							(S_REG_HOLDING_START_LIMIT + 40) // 电流偏置允许范围
#define HALLINVALIDTIME							(S_REG_HOLDING_START_LIMIT + 41) // Hall信号异常判断窗口时间, 每1 ms检测一次
#define FAULTMASK0								(S_REG_HOLDING_START_LIMIT + 42) // 报错掩码：1-Fault; 0-Warn
#define FAULTMASK1								(S_REG_HOLDING_START_LIMIT + 43) // 报错掩码1：1-Fault; 0-Warn
#define FOLDBACKEN                              (S_REG_HOLDING_START_LIMIT + 44) // 电流折返使能
#define FBDELAYTIME_L                           (S_REG_HOLDING_START_LIMIT + 45) // 电流折返峰值电流延迟时间(ms)
#define FBDELAYTIME_H                           (S_REG_HOLDING_START_LIMIT + 46)
#define FBRECOVERYTIME_L                        (S_REG_HOLDING_START_LIMIT + 47) // 恢复时间(ms)
#define FBRECOVERYTIME_H                        (S_REG_HOLDING_START_LIMIT + 48)
#define FBTIMECONSTANT_L                        (S_REG_HOLDING_START_LIMIT + 49) // 时间常数(ms)
#define FBTIMECONSTANT_H                        (S_REG_HOLDING_START_LIMIT + 50)
#define FBFAULTHOLDVALUE                        (S_REG_HOLDING_START_LIMIT + 51) // 电流折返故障电流阈值
#define FBWARNHOLDVAL                           (S_REG_HOLDING_START_LIMIT + 52) // 电流折返警告电流阈值

//************** 运动参数 S_REG_HOLDING_INDEX_MOTION (8) **************//
// 位置模式 T/S profile
#define PROFILECTRL								(S_REG_HOLDING_START_MOTION + 0) // 运动控制，详见下面定义
#define PROFILEMOVDIS_L							(S_REG_HOLDING_START_MOTION + 1) // 运动规划目标位置, 低16位
#define PROFILEMOVDIS_H							(S_REG_HOLDING_START_MOTION + 2) // 
#define PROFILEMOVDIS2_L						(S_REG_HOLDING_START_MOTION + 3) // 运动规划目标位置2, 低16位
#define PROFILEMOVDIS2_H						(S_REG_HOLDING_START_MOTION + 4) // 
#define PROFILEMAXVEL							(S_REG_HOLDING_START_MOTION + 5) // 运动规划最大速度(rpm or mm/s)
#define PROFILEMAXACC_L							(S_REG_HOLDING_START_MOTION + 6) // 运动规划最大加速度(rps^2 or mm/s^2)
#define PROFILEMAXACC_H							(S_REG_HOLDING_START_MOTION + 7) // 
#define PROFILEMAXJERK_L						(S_REG_HOLDING_START_MOTION + 8) // 运动规划最大加加速度(rps^3 or mm/s^3)
#define PROFILEMAXJERK_H						(S_REG_HOLDING_START_MOTION + 9) // 
#define PROFILEDWELLTIME						(S_REG_HOLDING_START_MOTION + 10) // 运动规划停留时间(ms)
#define WAVETYPE								(S_REG_HOLDING_START_MOTION + 11) // 速度环/电流环波形类型
// velocity/current loop Trap Wave
#define WAVECMD									(S_REG_HOLDING_START_MOTION + 12) // 速度环/电流环命令值(count)
#define WAVEINC									(S_REG_HOLDING_START_MOTION + 13) // 速度环/电流环增量值(count)
#define WAVEDWELLTIME							(S_REG_HOLDING_START_MOTION + 14) // 梯形波停顿时间
// sin output
#define SINFRE									(S_REG_HOLDING_START_MOTION + 15) // Sin信号频率
#define SINVS									(S_REG_HOLDING_START_MOTION + 16) // Sin信号幅值
#define SINPHASE								(S_REG_HOLDING_START_MOTION + 17) // Sin信号相位
// pulse and direction
#define GEARIN									(S_REG_HOLDING_START_MOTION + 18) // 齿轮比分子
#define GEAROUT									(S_REG_HOLDING_START_MOTION + 19) // 齿轮比分母
// home
#define HOMEMETHOD								(S_REG_HOLDING_START_MOTION + 20) // 回零方法, 0: HardStop; 1: HardStopOutToIndex
#define HOMETIMEOUT								(S_REG_HOLDING_START_MOTION + 21) // 回零超时时间(ms)
#define HOMEOFFSET_L							(S_REG_HOLDING_START_MOTION + 22) // 回零零点偏置 - Zero position = Home Attained Position + Home Offset
#define HOMEOFFSET_H							(S_REG_HOLDING_START_MOTION + 23) // 
#define HOMESPEED1								(S_REG_HOLDING_START_MOTION + 24) // 回零过程中寻找限位开关/回零开关/硬限位时的速度(rpm or mm/s)
#define HOMESPEED2								(S_REG_HOLDING_START_MOTION + 25) // 回零过程中寻找Z Index时的速度(rpm or mm/s)
#define HOMEACC									(S_REG_HOLDING_START_MOTION + 26) // 回零运动的加速度(rps^2 or mm/s^2)
#define HOMEBLOCKCURRENT						(S_REG_HOLDING_START_MOTION + 27) // 撞到硬限位的电流判断阈值(A)
#define HOMEBLOCKSPEED							(S_REG_HOLDING_START_MOTION + 28) // 撞到硬限位的速度判断阈值(count)
#define HOMEBLOCKTIME							(S_REG_HOLDING_START_MOTION + 29) // 撞到硬限位的判断时间(ms)

#define FBNUM_L									(S_REG_HOLDING_START_MOTION + 30) // 总线单位转换分子
#define FBNUM_H									(S_REG_HOLDING_START_MOTION + 31) // 总线单位转换分母
#define FBDEN									(S_REG_HOLDING_START_MOTION + 32) //

#define SWEEPSTARTFREQ							(S_REG_HOLDING_START_MOTION + 33) // 扫频开始频率
#define SWEEPENDFREQ							(S_REG_HOLDING_START_MOTION + 34) // 扫频结束频率
#define SWEEPPOINT								(S_REG_HOLDING_START_MOTION + 35) // 扫频Chirp频率点数
#define SWEEPAMP								(S_REG_HOLDING_START_MOTION + 36) // 扫频幅值

#define WAVEREPTIMES							(S_REG_HOLDING_START_MOTION + 37) // 速度/电流梯形波重复次数
#define WAVEPOSTIME								(S_REG_HOLDING_START_MOTION + 38) // 速度/电流梯形波正向匀速时间
#define WAVENEGTIME								(S_REG_HOLDING_START_MOTION + 39) // 速度/电流梯形波反向匀速时间

//************** 力控模式参数 S_REG_HOLDING_INDEX_FORCECTRL (9) **************//
#define FCMOD									(S_REG_HOLDING_START_FORCECTRL + 0) // 力控功能模式选择
#define FCINITPOS_L								(S_REG_HOLDING_START_FORCECTRL + 1) // 力控模式初始位置
#define FCINITPOS_H								(S_REG_HOLDING_START_FORCECTRL + 2)
#define FCSAFPOS_L								(S_REG_HOLDING_START_FORCECTRL + 3) // 力控模式安全位置
#define FCSAFPOS_H								(S_REG_HOLDING_START_FORCECTRL + 4)
#define FCSLOWSPD								(S_REG_HOLDING_START_FORCECTRL + 5) // 力控模式慢速搜索速度
#define FCSLOWACC								(S_REG_HOLDING_START_FORCECTRL + 6) // 力控模式慢速搜索加速度
#define FCTHRESHOLD								(S_REG_HOLDING_START_FORCECTRL + 7) // 力控模式接触检测阈值
#define FCCURCMD								(S_REG_HOLDING_START_FORCECTRL + 8) // 力控模式目标力
#define FCCURINC								(S_REG_HOLDING_START_FORCECTRL + 9) // 力控模式目标力增量值
#define FCSAFPOSTIME							(S_REG_HOLDING_START_FORCECTRL + 10) // 力控模式到达安全位置后等待时间
#define FCREACHTIME								(S_REG_HOLDING_START_FORCECTRL + 11) // 力控模式接触位置等待时间
#define FCHOLDTIME								(S_REG_HOLDING_START_FORCECTRL + 12) // 力控模式保压时间
#define FCDWELLTIME								(S_REG_HOLDING_START_FORCECTRL + 13) // 力控模式完整工艺结束后停留时间
#define FCKP									(S_REG_HOLDING_START_FORCECTRL + 14) // 闭环力控比例增益
#define FCKI									(S_REG_HOLDING_START_FORCECTRL + 15) // 闭环力控积分增益
#define FCERRVALUE								(S_REG_HOLDING_START_FORCECTRL + 16) // 力控保护压力阈值
#define FCCOMPMODE                              (S_REG_HOLDING_START_FORCECTRL + 17) // 力控补偿模式
#define FCCLRCNT                                (S_REG_HOLDING_START_FORCECTRL + 18) // 力控传感器清除计时器
#define FCPEVALUE                               (S_REG_HOLDING_START_FORCECTRL + 19) // 力控快速下降位置保护阈值

//************** 电批模式参数 S_REG_HOLDING_INDEX_FORCECTRL  **************//
#define ESCMOD							        (S_REG_HOLDING_START_FORCECTRL + 20) // 电批模式 0-不开启该功能	1-开启该功能
#define ESCERRCODE                              (S_REG_HOLDING_START_FORCECTRL + 21) // 电批故障码显示
#define ESCSAMPLETIME                           (S_REG_HOLDING_START_FORCECTRL + 22) // 电批采样时间窗口 1ms
#define ESCAXISNUM                              (S_REG_HOLDING_START_FORCECTRL + 23) // 电批轴号

#define ESCLOWSPD1                              (S_REG_HOLDING_START_FORCECTRL + 24) // 电批入牙检测转速 rpm
#define ESCLOWTOQHOLD1                          (S_REG_HOLDING_START_FORCECTRL + 25) // 电批入牙电流阈值 A
#define ESCRATIOHOLD1                           (S_REG_HOLDING_START_FORCECTRL + 26) // 电批入牙成功检测比 0.01A/p
#define ESCNEARCNTHOLD1                         (S_REG_HOLDING_START_FORCECTRL + 27) // 电批入牙成功检测时间窗口 1ms
#define ESCNEAROVERTIMEHOLD1                    (S_REG_HOLDING_START_FORCECTRL + 28) // 电批入牙超时故障时间窗口 1ms
#define ESCLOWTOQLMT1                           (S_REG_HOLDING_START_FORCECTRL + 29) // 电批入牙转矩限制值 A
#define ESCHIGHPOS1_L                           (S_REG_HOLDING_START_FORCECTRL + 30) // 电批旋入位置圈数（低位） 机械角度
#define ESCHIGHPOS1_H						    (S_REG_HOLDING_START_FORCECTRL + 31) // 电批旋入位置圈数（高位） 机械角度
#define ESCHIGHSPD1                             (S_REG_HOLDING_START_FORCECTRL + 32) // 电批旋入高速转速 rpm
#define ESCHIGHTOQLMT1                          (S_REG_HOLDING_START_FORCECTRL + 33) // 电批旋入转矩限制值 A
#define ESCHIGHTOQHOLD1                         (S_REG_HOLDING_START_FORCECTRL + 34) // 电批旋入电流阈值 A
#define ESCENTERCNTHOLD1                        (S_REG_HOLDING_START_FORCECTRL + 35) // 电批旋入成功检测时间窗口 1ms
#define ESCENTEROVERTIMEHOLD1                   (S_REG_HOLDING_START_FORCECTRL + 36) // 电批旋入超时故障时间窗口 1ms
#define ESCFINALSPD1                            (S_REG_HOLDING_START_FORCECTRL + 37) // 电批拧紧持续转速 rpm
#define ESCFINALTOQHOLD1                        (S_REG_HOLDING_START_FORCECTRL + 38) // 电批拧紧电流阈值 A
#define ESCFINALTOQLMT1                         (S_REG_HOLDING_START_FORCECTRL + 39) // 电批拧紧转矩限制值 A
#define ESCFINALCNTHOLD1                        (S_REG_HOLDING_START_FORCECTRL + 40) // 电批拧紧成功检测时间窗口 1ms
#define ESCFINALSPDHOLD1                        (S_REG_HOLDING_START_FORCECTRL + 41) // 电批拧紧零速阈值 rpm
#define ESCFINALOVERTIMEHOLD1                   (S_REG_HOLDING_START_FORCECTRL + 42) // 电批拧紧超时故障时间窗口 1ms
#define ESCACTPOS1_L                            (S_REG_HOLDING_START_FORCECTRL + 43) // 电批拧紧成功的位置（低位） 机械角度
#define ESCACTPOS1_H                            (S_REG_HOLDING_START_FORCECTRL + 44) // 电批拧紧成功的位置（高位） 机械角度
#define ESCLOWACC1                              (S_REG_HOLDING_START_FORCECTRL + 45) // 电批入牙速度指令加速度
#define ESCHIGHACC1                             (S_REG_HOLDING_START_FORCECTRL + 46) // 电批旋入速度指令加速度
#define ESCHOLDACC1                             (S_REG_HOLDING_START_FORCECTRL + 47) // 电批拧紧速度指令加速度

#define ESCLOWSPD2                              (S_REG_HOLDING_START_FORCECTRL + 48) // 电批入牙检测转速 rpm
#define ESCLOWTOQHOLD2                          (S_REG_HOLDING_START_FORCECTRL + 49) // 电批入牙电流阈值 A
#define ESCRATIOHOLD2                           (S_REG_HOLDING_START_FORCECTRL + 50) // 电批入牙成功检测比 0.01A/p
#define ESCNEARCNTHOLD2                         (S_REG_HOLDING_START_FORCECTRL + 51) // 电批入牙成功检测时间窗口 1ms
#define ESCNEAROVERTIMEHOLD2                    (S_REG_HOLDING_START_FORCECTRL + 52) // 电批入牙超时故障时间窗口 1ms
#define ESCLOWTOQLMT2                           (S_REG_HOLDING_START_FORCECTRL + 53) // 电批入牙转矩限制值 A
#define ESCHIGHPOS2_L                           (S_REG_HOLDING_START_FORCECTRL + 54) // 电批旋入位置圈数（低位） 机械角度
#define ESCHIGHPOS2_H						    (S_REG_HOLDING_START_FORCECTRL + 55) // 电批旋入位置圈数（高位） 机械角度
#define ESCHIGHSPD2                             (S_REG_HOLDING_START_FORCECTRL + 56) // 电批旋入高速转速 rpm
#define ESCHIGHTOQLMT2                          (S_REG_HOLDING_START_FORCECTRL + 57) // 电批旋入转矩限制值 A
#define ESCHIGHTOQHOLD2                         (S_REG_HOLDING_START_FORCECTRL + 58) // 电批旋入电流阈值 A
#define ESCENTERCNTHOLD2                        (S_REG_HOLDING_START_FORCECTRL + 59) // 电批旋入成功检测时间窗口 1ms
#define ESCENTEROVERTIMEHOLD2                   (S_REG_HOLDING_START_FORCECTRL + 60) // 电批旋入超时故障时间窗口 1ms
#define ESCFINALSPD2                            (S_REG_HOLDING_START_FORCECTRL + 61) // 电批拧紧持续转速 rpm
#define ESCFINALTOQHOLD2                        (S_REG_HOLDING_START_FORCECTRL + 62) // 电批拧紧电流阈值 A
#define ESCFINALTOQLMT2                         (S_REG_HOLDING_START_FORCECTRL + 63) // 电批拧紧转矩限制值 A
#define ESCFINALCNTHOLD2                        (S_REG_HOLDING_START_FORCECTRL + 64) // 电批拧紧成功检测时间窗口 1ms
#define ESCFINALSPDHOLD2                        (S_REG_HOLDING_START_FORCECTRL + 65) // 电批拧紧零速阈值 rpm
#define ESCFINALOVERTIMEHOLD2                   (S_REG_HOLDING_START_FORCECTRL + 66) // 电批拧紧超时故障时间窗口 1ms
#define ESCACTPOS2_L                            (S_REG_HOLDING_START_FORCECTRL + 67) // 电批拧紧成功的位置（低位） 机械角度
#define ESCACTPOS2_H                            (S_REG_HOLDING_START_FORCECTRL + 68) // 电批拧紧成功的位置（高位） 机械角度
#define ESCLOWACC2                              (S_REG_HOLDING_START_FORCECTRL + 69) // 电批入牙速度指令加速度
#define ESCHIGHACC2                             (S_REG_HOLDING_START_FORCECTRL + 70) // 电批旋入速度指令加速度
#define ESCHOLDACC2                             (S_REG_HOLDING_START_FORCECTRL + 71) // 电批拧紧速度指令加速度

#define ESCLOWSPD3                              (S_REG_HOLDING_START_FORCECTRL + 72) // 电批入牙检测转速 rpm
#define ESCLOWTOQHOLD3                          (S_REG_HOLDING_START_FORCECTRL + 73) // 电批入牙电流阈值 A
#define ESCRATIOHOLD3                           (S_REG_HOLDING_START_FORCECTRL + 74) // 电批入牙成功检测比 0.01A/p
#define ESCNEARCNTHOLD3                         (S_REG_HOLDING_START_FORCECTRL + 75) // 电批入牙成功检测时间窗口 1ms
#define ESCNEAROVERTIMEHOLD3                    (S_REG_HOLDING_START_FORCECTRL + 76) // 电批入牙超时故障时间窗口 1ms
#define ESCLOWTOQLMT3                           (S_REG_HOLDING_START_FORCECTRL + 77) // 电批入牙转矩限制值 A
#define ESCHIGHPOS3_L                           (S_REG_HOLDING_START_FORCECTRL + 78) // 电批旋入位置圈数（低位） 机械角度
#define ESCHIGHPOS3_H						    (S_REG_HOLDING_START_FORCECTRL + 79) // 电批旋入位置圈数（高位） 机械角度
#define ESCHIGHSPD3                             (S_REG_HOLDING_START_FORCECTRL + 80) // 电批旋入高速转速 rpm
#define ESCHIGHTOQLMT3                          (S_REG_HOLDING_START_FORCECTRL + 81) // 电批旋入转矩限制值 A
#define ESCHIGHTOQHOLD3                         (S_REG_HOLDING_START_FORCECTRL + 82) // 电批旋入电流阈值 A
#define ESCENTERCNTHOLD3                        (S_REG_HOLDING_START_FORCECTRL + 83) // 电批旋入成功检测时间窗口 1ms
#define ESCENTEROVERTIMEHOLD3                   (S_REG_HOLDING_START_FORCECTRL + 84) // 电批旋入超时故障时间窗口 1ms
#define ESCFINALSPD3                            (S_REG_HOLDING_START_FORCECTRL + 85) // 电批拧紧持续转速 rpm
#define ESCFINALTOQHOLD3                        (S_REG_HOLDING_START_FORCECTRL + 86) // 电批拧紧电流阈值 A
#define ESCFINALTOQLMT3                         (S_REG_HOLDING_START_FORCECTRL + 87) // 电批拧紧转矩限制值 A
#define ESCFINALCNTHOLD3                        (S_REG_HOLDING_START_FORCECTRL + 88) // 电批拧紧成功检测时间窗口 1ms
#define ESCFINALSPDHOLD3                        (S_REG_HOLDING_START_FORCECTRL + 89) // 电批拧紧零速阈值 rpm
#define ESCFINALOVERTIMEHOLD3                   (S_REG_HOLDING_START_FORCECTRL + 90) // 电批拧紧超时故障时间窗口 1ms
#define ESCACTPOS3_L                            (S_REG_HOLDING_START_FORCECTRL + 91) // 电批拧紧成功的位置（低位） 机械角度
#define ESCACTPOS3_H                            (S_REG_HOLDING_START_FORCECTRL + 92) // 电批拧紧成功的位置（高位） 机械角度
#define ESCLOWACC3                              (S_REG_HOLDING_START_FORCECTRL + 93) // 电批入牙速度指令加速度
#define ESCHIGHACC3                             (S_REG_HOLDING_START_FORCECTRL + 94) // 电批旋入速度指令加速度
#define ESCHOLDACC3                             (S_REG_HOLDING_START_FORCECTRL + 95) // 电批拧紧速度指令加速度

#define ESCLOWSPD4                              (S_REG_HOLDING_START_FORCECTRL + 96) // 电批入牙检测转速 rpm
#define ESCLOWTOQHOLD4                          (S_REG_HOLDING_START_FORCECTRL + 97) // 电批入牙电流阈值 A
#define ESCRATIOHOLD4                           (S_REG_HOLDING_START_FORCECTRL + 98) // 电批入牙成功检测比 0.01A/p
#define ESCNEARCNTHOLD4                         (S_REG_HOLDING_START_FORCECTRL + 99) // 电批入牙成功检测时间窗口 1ms
#define ESCNEAROVERTIMEHOLD4                    (S_REG_HOLDING_START_FORCECTRL + 100) // 电批入牙超时故障时间窗口 1ms
#define ESCLOWTOQLMT4                           (S_REG_HOLDING_START_FORCECTRL + 101) // 电批入牙转矩限制值 A
#define ESCHIGHPOS4_L                           (S_REG_HOLDING_START_FORCECTRL + 102) // 电批旋入位置圈数（低位） 机械角度
#define ESCHIGHPOS4_H						    (S_REG_HOLDING_START_FORCECTRL + 103) // 电批旋入位置圈数（高位） 机械角度
#define ESCHIGHSPD4                             (S_REG_HOLDING_START_FORCECTRL + 104) // 电批旋入高速转速 rpm
#define ESCHIGHTOQLMT4                          (S_REG_HOLDING_START_FORCECTRL + 105) // 电批旋入转矩限制值 A
#define ESCHIGHTOQHOLD4                         (S_REG_HOLDING_START_FORCECTRL + 106) // 电批旋入电流阈值 A
#define ESCENTERCNTHOLD4                        (S_REG_HOLDING_START_FORCECTRL + 107) // 电批旋入成功检测时间窗口 1ms
#define ESCENTEROVERTIMEHOLD4                   (S_REG_HOLDING_START_FORCECTRL + 108) // 电批旋入超时故障时间窗口 1ms
#define ESCFINALSPD4                            (S_REG_HOLDING_START_FORCECTRL + 109) // 电批拧紧持续转速 rpm
#define ESCFINALTOQHOLD4                        (S_REG_HOLDING_START_FORCECTRL + 110) // 电批拧紧电流阈值 A
#define ESCFINALTOQLMT4                         (S_REG_HOLDING_START_FORCECTRL + 111) // 电批拧紧转矩限制值 A
#define ESCFINALCNTHOLD4                        (S_REG_HOLDING_START_FORCECTRL + 112) // 电批拧紧成功检测时间窗口 1ms
#define ESCFINALSPDHOLD4                        (S_REG_HOLDING_START_FORCECTRL + 113) // 电批拧紧零速阈值 rpm
#define ESCFINALOVERTIMEHOLD4                   (S_REG_HOLDING_START_FORCECTRL + 114) // 电批拧紧超时故障时间窗口 1ms
#define ESCACTPOS4_L                            (S_REG_HOLDING_START_FORCECTRL + 115) // 电批拧紧成功的位置（低位） 机械角度
#define ESCACTPOS4_H                            (S_REG_HOLDING_START_FORCECTRL + 116) // 电批拧紧成功的位置（高位） 机械角度
#define ESCLOWACC4                              (S_REG_HOLDING_START_FORCECTRL + 117) // 电批入牙速度指令加速度
#define ESCHIGHACC4                             (S_REG_HOLDING_START_FORCECTRL + 118) // 电批旋入速度指令加速度
#define ESCHOLDACC4                             (S_REG_HOLDING_START_FORCECTRL + 119) // 电批拧紧速度指令加速度

#define ESCLOWSPD5                              (S_REG_HOLDING_START_FORCECTRL + 120) // 电批入牙检测转速 rpm
#define ESCLOWTOQHOLD6                          (S_REG_HOLDING_START_FORCECTRL + 121) // 电批入牙电流阈值 A
#define ESCRATIOHOLD5                           (S_REG_HOLDING_START_FORCECTRL + 122) // 电批入牙成功检测比 0.01A/p
#define ESCNEARCNTHOLD5                         (S_REG_HOLDING_START_FORCECTRL + 123) // 电批入牙成功检测时间窗口 1ms
#define ESCNEAROVERTIMEHOLD5                    (S_REG_HOLDING_START_FORCECTRL + 124) // 电批入牙超时故障时间窗口 1ms
#define ESCLOWTOQLMT5                           (S_REG_HOLDING_START_FORCECTRL + 125) // 电批入牙转矩限制值 A
#define ESCHIGHPOS5_L                           (S_REG_HOLDING_START_FORCECTRL + 126) // 电批旋入位置圈数（低位） 机械角度
#define ESCHIGHPOS5_H						    (S_REG_HOLDING_START_FORCECTRL + 127) // 电批旋入位置圈数（高位） 机械角度
#define ESCHIGHSPD5                             (S_REG_HOLDING_START_FORCECTRL + 128) // 电批旋入高速转速 rpm
#define ESCHIGHTOQLMT5                          (S_REG_HOLDING_START_FORCECTRL + 129) // 电批旋入转矩限制值 A
#define ESCHIGHTOQHOLD5                         (S_REG_HOLDING_START_FORCECTRL + 130) // 电批旋入电流阈值 A
#define ESCENTERCNTHOLD5                        (S_REG_HOLDING_START_FORCECTRL + 131) // 电批旋入成功检测时间窗口 1ms
#define ESCENTEROVERTIMEHOLD5                   (S_REG_HOLDING_START_FORCECTRL + 132) // 电批旋入超时故障时间窗口 1ms
#define ESCFINALSPD5                            (S_REG_HOLDING_START_FORCECTRL + 133) // 电批拧紧持续转速 rpm
#define ESCFINALTOQHOLD5                        (S_REG_HOLDING_START_FORCECTRL + 134) // 电批拧紧电流阈值 A
#define ESCFINALTOQLMT5                         (S_REG_HOLDING_START_FORCECTRL + 135) // 电批拧紧转矩限制值 A
#define ESCFINALCNTHOLD5                        (S_REG_HOLDING_START_FORCECTRL + 136) // 电批拧紧成功检测时间窗口 1ms
#define ESCFINALSPDHOLD5                        (S_REG_HOLDING_START_FORCECTRL + 137) // 电批拧紧零速阈值 rpm
#define ESCFINALOVERTIMEHOLD5                   (S_REG_HOLDING_START_FORCECTRL + 138) // 电批拧紧超时故障时间窗口 1ms
#define ESCACTPOS5_L                            (S_REG_HOLDING_START_FORCECTRL + 139) // 电批拧紧成功的位置（低位） 机械角度
#define ESCACTPOS5_H                            (S_REG_HOLDING_START_FORCECTRL + 140) // 电批拧紧成功的位置（高位） 机械角度
#define ESCLOWACC5                              (S_REG_HOLDING_START_FORCECTRL + 141) // 电批入牙速度指令加速度
#define ESCHIGHACC5                             (S_REG_HOLDING_START_FORCECTRL + 142) // 电批旋入速度指令加速度
#define ESCHOLDACC5                             (S_REG_HOLDING_START_FORCECTRL + 143) // 电批拧紧速度指令加速度

//************** 柔顺模式参数 S_REG_HOLDING_INDEX_FORCECTRL  **************//
#define SOFTCTRLKP_L                            (S_REG_HOLDING_START_FORCECTRL + 144) // 柔顺刚度增益K
#define SOFTCTRLKP_H                            (S_REG_HOLDING_START_FORCECTRL + 145) // 柔顺刚度增益K
#define SOFTCTRLKI_L                            (S_REG_HOLDING_START_FORCECTRL + 146) // 柔顺阻尼增益B
#define SOFTCTRLKI_H                            (S_REG_HOLDING_START_FORCECTRL + 147) // 柔顺阻尼增益B
#define SOFTCTRLKD_L                            (S_REG_HOLDING_START_FORCECTRL + 148) // 柔顺质量增益M
#define SOFTCTRLKD_H                            (S_REG_HOLDING_START_FORCECTRL + 149) // 柔顺质量增益M
#define SOFTCTRLCMPMOD                          (S_REG_HOLDING_START_FORCECTRL + 150) // 柔顺补偿模式
#define SOFTCTRLXD                              (S_REG_HOLDING_START_FORCECTRL + 151) // 末端位置指令
#define SOFTCTRLXC                              (S_REG_HOLDING_START_FORCECTRL + 152) // 末端位置反馈
#define SOFTCTRLFD                              (S_REG_HOLDING_START_FORCECTRL + 153) // 末端力控指令
#define SOFTCTRLFC                              (S_REG_HOLDING_START_FORCECTRL + 154) // 末端力控反馈
#define SOFTCTRLWORMOD                          (S_REG_HOLDING_START_FORCECTRL + 155) // 柔顺模式 0：关闭 1：阻抗（本地） 2：导纳（本地）

//************** 数字输入输出参数 S_REG_HOLDING_INDEX_DIGITAL (10) **************//
#define DIGINOUTINV								(S_REG_HOLDING_START_DIGITAL + 0) // 数字输入输出取反开关，高8位：输出；低8位：输入
#define DIGINVIRTUALSWITCH						(S_REG_HOLDING_START_DIGITAL + 1) // 虚拟数字输入开关
#define DIGINVIRTUAL							(S_REG_HOLDING_START_DIGITAL + 2) // 虚拟数字输入电平
#define INMODE12								(S_REG_HOLDING_START_DIGITAL + 3) // 数字输入模式，高8位：IN2的模式；低8位：IN1的模式；
#define INMODE34								(S_REG_HOLDING_START_DIGITAL + 4) // 数字输入模式，高8位：IN4的模式；低8位：IN3的模式；
#define INMODE56								(S_REG_HOLDING_START_DIGITAL + 5) // 数字输入模式，高8位：IN6的模式；低8位：IN5的模式；
#define INMODE78								(S_REG_HOLDING_START_DIGITAL + 6) // 数字输入模式，高8位：IN8的模式；低8位：IN7的模式；
#define OUTMODE12								(S_REG_HOLDING_START_DIGITAL + 7) // 数字输出模式，高8位：OUT2的模式；低8位：OUT1的模式；
#define OUTMODE34								(S_REG_HOLDING_START_DIGITAL + 8) // 数字输出模式，高8位：OUT4的模式；低8位：OUT3的模式；
#define OUTMODE56								(S_REG_HOLDING_START_DIGITAL + 9) // 数字输出模式，高8位：OUT6的模式；低8位：OUT5的模式；
#define PROBECONFIG								(S_REG_HOLDING_START_DIGITAL + 10) // 探针设置

#define PCOM1CNTRL								(S_REG_HOLDING_START_DIGITAL + 11) // 位置比较输出1设置
#define PCOM1START_L							(S_REG_HOLDING_START_DIGITAL + 12) // 位置比较输出1起始位置
#define PCOM1START_H							(S_REG_HOLDING_START_DIGITAL + 13)
#define PCOM1END_L								(S_REG_HOLDING_START_DIGITAL + 14) // 位置比较输出1结束位置
#define PCOM1END_H								(S_REG_HOLDING_START_DIGITAL + 15)
#define PCOM1OFFSET_L							(S_REG_HOLDING_START_DIGITAL + 16) // 位置比较输出1位置间隔
#define PCOM1OFFSET_H							(S_REG_HOLDING_START_DIGITAL + 17)
#define PCOM1POS0_L								(S_REG_HOLDING_START_DIGITAL + 18) // 位置比较输出1表格位置0
#define PCOM1POS0_H								(S_REG_HOLDING_START_DIGITAL + 19)
#define PCOM1POS1_L								(S_REG_HOLDING_START_DIGITAL + 20) // 位置比较输出1表格位置1
#define PCOM1POS1_H								(S_REG_HOLDING_START_DIGITAL + 21)
#define PCOM1POS2_L								(S_REG_HOLDING_START_DIGITAL + 22) // 位置比较输出1表格位置2
#define PCOM1POS2_H								(S_REG_HOLDING_START_DIGITAL + 23)
#define PCOM1POS3_L								(S_REG_HOLDING_START_DIGITAL + 24) // 位置比较输出1表格位置3
#define PCOM1POS3_H								(S_REG_HOLDING_START_DIGITAL + 25)
#define PCOM1TABLELEN							(S_REG_HOLDING_START_DIGITAL + 26) // 位置比较输出1表格长度
#define PCOM1WIDTH								(S_REG_HOLDING_START_DIGITAL + 27) // 位置比较输出1脉冲宽度

//************** 模拟量输入参数 S_REG_HOLDING_INDEX_ANALOG (11) **************//
#define ANINOFFSET								(S_REG_HOLDING_START_ANALOG + 0) // 模拟量输入偏置电压
#define ANINDEADBAND							(S_REG_HOLDING_START_ANALOG + 1) // 模拟量输入死区范围
#define ANINLPFK								(S_REG_HOLDING_START_ANALOG + 2) // 模拟量输入一阶低通滤波器系数
#define ANINISCALE								(S_REG_HOLDING_START_ANALOG + 3) // 模拟量输入电流转换系数
#define ANINVSCALE								(S_REG_HOLDING_START_ANALOG + 4) // 模拟量输入速度转换系数
#define ANINFSCALE								(S_REG_HOLDING_START_ANALOG + 5) // 模拟量输入压力转换系数
#define ANINCOE									(S_REG_HOLDING_START_ANALOG + 6) // 模拟量输入电压转换系数


//************** 测试参数 S_REG_HOLDING_INDEX_TEST (12) **************//
#define RESERVED1								(S_REG_HOLDING_START_TEST + 0) // 测试寄存器
#define RESERVED2								(S_REG_HOLDING_START_TEST + 1)
#define RESERVED3								(S_REG_HOLDING_START_TEST + 2)
#define RESERVED4								(S_REG_HOLDING_START_TEST + 3)
#define RESERVED5								(S_REG_HOLDING_START_TEST + 4)
#define RESERVED6								(S_REG_HOLDING_START_TEST + 5)
#define RESERVED7								(S_REG_HOLDING_START_TEST + 6)
#define RESERVED8								(S_REG_HOLDING_START_TEST + 7)
#define RESERVED9								(S_REG_HOLDING_START_TEST + 8)
#define RESERVED10								(S_REG_HOLDING_START_TEST + 9)

//************** 测试参数 S_REG_HOLDING_INDEX_ERRORCOR (13) **************//
#define ERRCOREN								(S_REG_HOLDING_START_ERRCOR + 0) // 误差校准使能
#define ERRCORNUMPOINTS							(S_REG_HOLDING_START_ERRCOR + 1) // 误差校准点数
#define ERRCORUNITS								(S_REG_HOLDING_START_ERRCOR + 2) // 误差校准单位
#define ERRCORINTERVAL_L						(S_REG_HOLDING_START_ERRCOR + 3) // 误差校准间隔_低位
#define ERRCORINTERVAL_H						(S_REG_HOLDING_START_ERRCOR + 4) // 误差校准间隔_高位
#define ERRCORSTARTPOS_L						(S_REG_HOLDING_START_ERRCOR + 5) // 误差校准的开始位置_低位
#define ERRCORSTARTPOS_H						(S_REG_HOLDING_START_ERRCOR + 6) // 误差校准的开始位置_高位
#define ERRCORPROTARY_L							(S_REG_HOLDING_START_ERRCOR + 7) // 误差校准的开始位置_低位
#define ERRCORPROTARY_H							(S_REG_HOLDING_START_ERRCOR + 8) // 误差校准的开始位置_高位
#define ERRCORER1								(S_REG_HOLDING_START_ERRCOR + 9) // 误差校准位置1偏差
#define ERRCORER64								(S_REG_HOLDING_START_ERRCOR + 72) // 误差校准位置64偏差
// 64个误差校准位置

// Definition of register DRIVECTRL
#define CTRL_CLEARPHASEFIND							   0x0080          // rw-- clear phasefind succeed flag
#define CTRL_CLEARENC								   0x0040          // rw-- clear TMG encoder multiturn
#define CTRL_DOMOTOREST								   0x0020          // rw-- do motor parameter estimation
#define CTRL_DOPHASEFIND                               0x0010          // rw-- do phase find
#define CTRL_DOHOME                                    0x0008          // rw-- do home
#define CTRL_CLEARERR                                  0x0004          // rw-- clear error
#define CTRL_DISABLE                                   0x0002          // rw-- disable motor
#define CTRL_ENABLE                                    0x0001          // rw-- enable motor

// Definition of register DRIVEMODE
#define MODE_DISABLEMODE                               0x8000          // rw-- 0: Disable directly; 1: decelerate and Disable
#define MODE_PULSEMODE1                                0x4000          // rw-- 1x = A相+B相
#define MODE_PULSEMODE0                                0x2000          // rw-- 00 = 脉冲+方向；01 = 正负脉冲(CW+CCW)
#define MODE_XXX									   0x1000          // rw-- reserve
#define MODE_SFBANGDIR								   0x0800          // rw-- 0:负载编码器方向不取反; 1:负载编码器方向取反
#define MODE_MOTORTYPE                                 0x0400          // rw-- 0:Linear Motor; 1:Rotary Motor;
#define MODE_ANGDIR                                    0x0200          // rw-- 1:Encoder and ActPos direction are different
#define MODE_ELECANGDIR                                0x0100          // rw-- 1:Encoder and ElecAng direction are different
#define MODE_ENCABS									   0x0080          // rw-- 1:Absolute Encoder
#define MODE_AUTOPHASEFIND                             0x0040          // rw-- 1:Auto do phasefind when powerup
#define MODE_AUTOHOME                                  0x0020          // rw-- 1:Auto do home when powerup
#define MODE_AUTOENABLE                                0x0010          // rw-- 1:Auto enable when powerup
#define MODE_WORKMODE3                                 0x0008          // rw-- 7 = FORSERIAL; 8 = VELFRF; 9 = CURFRF;
#define MODE_WORKMODE2                                 0x0004          // rw-- 4 = PULSEDIR; 5 = POSSERIAL; 6 = EtherCAT
#define MODE_WORKMODE1                                 0x0002          // rw-- 2 = CURSERIAL; 3 = CURANALOG
#define MODE_WORKMODE0                                 0x0001          // rw-- 0 = VELSERIAL; 1 = VELANALOG

// Definition of register DRIVESWITCH
#define SW_MTMODE									   0x0001          // rw-- 0 = M method; 1 = MT method

// Definition of register PROFILECTRL
#define PROF_VELJOG									   0x0020          // rw-- 1:Jog; 0-No Jog
#define PROF_PROFILETYPE                               0x0010          // rw-- 1:S-curve; 0-T-curve
#define PROF_PROFILERND                                0x0008          // rw-- 1:move back and forth
#define PROF_PROFILEREP                                0x0004          // rw-- 1:repetively move
#define PROF_PROFILEABS                                0x0002          // rw-- 1:absolutely move
#define PROF_MOTIONEN                                  0x0001          // rw-- rising edge: Start move; falling edge: Stop move


/////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////// Input Register (read-only) /////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////
// 变量分组
#define S_REG_INPUT_INDEX_STATUS				(0)
#define S_REG_INPUT_INDEX_VERSION				(1)
#define S_REG_INPUT_INDEX_CONTROLLER			(2)
#define S_REG_INPUT_INDEX_DIGITAL				(3)
#define S_REG_INPUT_INDEX_OTHERS				(4)
#define S_REG_INPUT_INDEX_PROTECT				(5)
#define S_REG_INPUT_INDEX_TEST					(6)

#define S_REG_INPUT_INDEX_MAX  					(7)

// 每一组的变量个数
#define S_REG_INPUT_SIZE_STATUS					(2)
#define S_REG_INPUT_SIZE_VERSION				(18)
#define S_REG_INPUT_SIZE_CONTROLLER				(50)
#define S_REG_INPUT_SIZE_DIGITAL				(11)
#define S_REG_INPUT_SIZE_OTHERS					(30)
#define S_REG_INPUT_SIZE_PROTECT				(31)
#define S_REG_INPUT_SIZE_TEST					(9)


#define S_REG_INPUT_START_STATUS				(0)
#define S_REG_INPUT_START_VERSION				(S_REG_INPUT_START_STATUS + S_REG_INPUT_SIZE_STATUS)
#define S_REG_INPUT_START_CONTROLLER			(S_REG_INPUT_START_VERSION + S_REG_INPUT_SIZE_VERSION)
#define S_REG_INPUT_START_DIGITAL				(S_REG_INPUT_START_CONTROLLER + S_REG_INPUT_SIZE_CONTROLLER)
#define S_REG_INPUT_START_OTHERS				(S_REG_INPUT_START_DIGITAL + S_REG_INPUT_SIZE_DIGITAL)
#define S_REG_INPUT_START_PROTECT				(S_REG_INPUT_START_OTHERS + S_REG_INPUT_SIZE_OTHERS)
#define S_REG_INPUT_START_TEST					(S_REG_INPUT_START_PROTECT + S_REG_INPUT_SIZE_PROTECT)

#define S_REG_INPUT_SIZE_TOTAL					(S_REG_INPUT_START_TEST + S_REG_INPUT_SIZE_TEST)


//************** 状态信息 S_REG_INPUT_INDEX_STATUS (0) **************//
#define DRIVESTATUS								(S_REG_INPUT_START_STATUS + 0) // 状态字，详见下面定义
#define CONTROLSTATUS							(S_REG_INPUT_START_STATUS + 1) // 状态字2，详见下面定义

//************** 版本信息 S_REG_INPUT_INDEX_VERSION (1) **************//
#define FIRMWAREVERSION_L						(S_REG_INPUT_START_VERSION + 0) // 固件版本号
#define FIRMWAREVERSION_H						(S_REG_INPUT_START_VERSION + 1)
#define PWMFREQUENCY							(S_REG_INPUT_START_VERSION + 2) // 载波频率
#define CURCTRLFREQUENCY						(S_REG_INPUT_START_VERSION + 3) // 电流环频率
#define VELCTRLFREQUENCY						(S_REG_INPUT_START_VERSION + 4) // 速度环频率
#define POSCTRLFREQUENCY						(S_REG_INPUT_START_VERSION + 5) // 位置环频率
#define SERCURFREQ								(S_REG_INPUT_START_VERSION + 6) // 串口电流运行频率
#define SERVELFREQ								(S_REG_INPUT_START_VERSION + 7) // 串口速度运行频率
#define ANACURFREQ								(S_REG_INPUT_START_VERSION + 8) // 模拟电流运行频率
#define ANAVELFREQ								(S_REG_INPUT_START_VERSION + 9) // 模拟速度运行频率
#define SCOPEFREQ								(S_REG_INPUT_START_VERSION + 10) // 示波器采样频率
#define OUTFILTFREQ								(S_REG_INPUT_START_VERSION + 11) // 转矩滤波器运行频率
#define VELFEBFREQ								(S_REG_INPUT_START_VERSION + 12) // 速度反馈计算频率
#define POSREFFREQ								(S_REG_INPUT_START_VERSION + 13) // 位置指令滤波频率
#define DRIVERTYPE								(S_REG_INPUT_START_VERSION + 14) // 驱动器类型
#define MCUCLOCK								(S_REG_INPUT_START_VERSION + 15) // 系统时钟频率
#define FUNCMASK0								(S_REG_INPUT_START_VERSION + 16) // 功能开关
#define FUNCMASK1								(S_REG_INPUT_START_VERSION + 17)

//************** 控制器信息 S_REG_INPUT_INDEX_CONTROLLER (2) **************//
#define CMDPOS_L								(S_REG_INPUT_START_CONTROLLER + 0) // 位置指令(滤波后)
#define CMDPOS_H								(S_REG_INPUT_START_CONTROLLER + 1)
#define ACTPOS_L								(S_REG_INPUT_START_CONTROLLER + 2) // 实际位置(偏置+校准后)
#define ACTPOS_H								(S_REG_INPUT_START_CONTROLLER + 3)
#define POSERR_L								(S_REG_INPUT_START_CONTROLLER + 4) // 位置偏差
#define POSERR_H								(S_REG_INPUT_START_CONTROLLER + 5)
#define CMDVEL									(S_REG_INPUT_START_CONTROLLER + 6) // 命令速度
#define ACTVEL									(S_REG_INPUT_START_CONTROLLER + 7) // 实际速度
#define CMDCUR									(S_REG_INPUT_START_CONTROLLER + 8) // IQ命令电流(经过转矩滤波器前)
#define ACTCUR									(S_REG_INPUT_START_CONTROLLER + 9) // 实际电流
#define ELECANG									(S_REG_INPUT_START_CONTROLLER + 10) // 电角度(count) 
#define ELECANGOFFSET							(S_REG_INPUT_START_CONTROLLER + 11) // 电角度偏置(count) 
#define CMDPOSRAW_L								(S_REG_INPUT_START_CONTROLLER + 12) // 位置指令(滤波前)
#define CMDPOSRAW_H								(S_REG_INPUT_START_CONTROLLER + 13)
#define QEPPOS_L								(S_REG_INPUT_START_CONTROLLER + 14) // 编码器原始值
#define QEPPOS_H								(S_REG_INPUT_START_CONTROLLER + 15)
#define HALLS									(S_REG_INPUT_START_CONTROLLER + 16) // Hall信号
#define MB_IDREF								(S_REG_INPUT_START_CONTROLLER + 17) // D轴电流指令
#define MB_ID									(S_REG_INPUT_START_CONTROLLER + 18) // D轴实际电流
#define MB_UQ									(S_REG_INPUT_START_CONTROLLER + 19) // Q轴输出占空比
#define MB_UD									(S_REG_INPUT_START_CONTROLLER + 20) // D轴输出占空比
#define MB_IA									(S_REG_INPUT_START_CONTROLLER + 21) // IA实际电流
#define MB_IB									(S_REG_INPUT_START_CONTROLLER + 22) // IB实际电流
#define MB_IC									(S_REG_INPUT_START_CONTROLLER + 23) // IC实际电流
#define SPEEDFF									(S_REG_INPUT_START_CONTROLLER + 24) // 速度前馈
#define ACCFF									(S_REG_INPUT_START_CONTROLLER + 25) // 加速度前馈
#define PTPVCMD									(S_REG_INPUT_START_CONTROLLER + 26) // 位置指令速度
#define MB_IQREF								(S_REG_INPUT_START_CONTROLLER + 27) // IQ命令电流(经过转矩滤波器后)
#define CMDFRC									(S_REG_INPUT_START_CONTROLLER + 28) // 压力环压力指令
#define ACTFRC									(S_REG_INPUT_START_CONTROLLER + 29) // 压力环压力反馈
#define ESCRATIO								(S_REG_INPUT_START_CONTROLLER + 30) // 电批成功检测比
#define VELCTRLOUT								(S_REG_INPUT_START_CONTROLLER + 31) // 速度控制器的输出(滤波后), MB_IQREF = VELCTRLOUT + CURFF
#define CURFF									(S_REG_INPUT_START_CONTROLLER + 32) // 电流环前馈补偿 (加在滤波后)
#define VELERR									(S_REG_INPUT_START_CONTROLLER + 33) // 速度误差
#define ACTPOSRAW_L								(S_REG_INPUT_START_CONTROLLER + 34) // 实际位置(误差校准前)
#define ACTPOSRAW_H								(S_REG_INPUT_START_CONTROLLER + 35)
#define ERRCORSTATUS							(S_REG_INPUT_START_CONTROLLER + 36) // 误差校准状态
#define ERRCORINDEX								(S_REG_INPUT_START_CONTROLLER + 37) // 误差校准索引
#define SFBACTPOS_L								(S_REG_INPUT_START_CONTROLLER + 38) // 负载侧实际位置
#define SFBACTPOS_H								(S_REG_INPUT_START_CONTROLLER + 39) // 
#define MIXPOSERR_L                             (S_REG_INPUT_START_CONTROLLER + 40) // 混合位置偏差
#define MIXPOSERR_H                             (S_REG_INPUT_START_CONTROLLER + 41)
#define WARNMIXPOSERR_L                         (S_REG_INPUT_START_CONTROLLER + 42) // 监控混合位置偏差
#define WARNMIXPOSERR_H                         (S_REG_INPUT_START_CONTROLLER + 43)
#define LOADVEL_L                               (S_REG_INPUT_START_CONTROLLER + 44) // 外环速度
#define LOADVEL_H                               (S_REG_INPUT_START_CONTROLLER + 45)
#define SFBACTPOSRAW_L							(S_REG_INPUT_START_CONTROLLER + 46) // 负载侧实际位置(误差校准前)
#define SFBACTPOSRAW_H							(S_REG_INPUT_START_CONTROLLER + 47) // 

//************** 数字/模拟输入输出 S_REG_INPUT_INDEX_DIGITAL (3) **************//
#define DIGINSTATUS								(S_REG_INPUT_START_DIGITAL + 0) // 数字输入状态
#define DIGITALINPUT							(S_REG_INPUT_START_DIGITAL + 1) // 数字输入
#define DIGITALOUTPUT							(S_REG_INPUT_START_DIGITAL + 2) // 数字输出
#define ANALOGIN								(S_REG_INPUT_START_DIGITAL + 3) // 模拟输入信号(死区计算和低通滤波前)
#define PROBE1DATA_L							(S_REG_INPUT_START_DIGITAL + 4) // 探针1的锁存位置值
#define PROBE1DATA_H							(S_REG_INPUT_START_DIGITAL + 5)
#define PROBE2DATA_L							(S_REG_INPUT_START_DIGITAL + 6) // 探针2的锁存位置值
#define PROBE2DATA_H							(S_REG_INPUT_START_DIGITAL + 7)
#define PROBESTATUS								(S_REG_INPUT_START_DIGITAL + 8) // 探针状态
#define PCOMSTATUS								(S_REG_INPUT_START_DIGITAL + 9) // 位置比较输出的状态
#define DIGINSTAEN								(S_REG_INPUT_START_DIGITAL + 10) // 数字输入状态有效，定义同DIGINSTATUS


//************** 其他 S_REG_INPUT_INDEX_OTHERS (4) **************//
#define BUSVOLTAGE								(S_REG_INPUT_START_OTHERS + 0) // 母线电压
#define SCOPESTATUS							    (S_REG_INPUT_START_OTHERS + 1) // 示波器采样状态
#define SCOPETRIGSTA							(S_REG_INPUT_START_OTHERS + 2) // 示波器触发采样状态
#define MOTORTEMP								(S_REG_INPUT_START_OTHERS + 3) // 电机温度
#define DRIVETEMP								(S_REG_INPUT_START_OTHERS + 4) // 驱动器温度
#define ADCIA									(S_REG_INPUT_START_OTHERS + 5) // IA的ADC值
#define ADCIB									(S_REG_INPUT_START_OTHERS + 6) // IB的ADC值
#define HALLTHETA0								(S_REG_INPUT_START_OTHERS + 7) // Hall第0个变化沿对应的电角度值
#define HALLTHETA1								(S_REG_INPUT_START_OTHERS + 8) // Hall第1个变化沿对应的电角度值
#define HALLTHETA2								(S_REG_INPUT_START_OTHERS + 9) // Hall第2个变化沿对应的电角度值
#define HALLTHETA3								(S_REG_INPUT_START_OTHERS + 10) // Hall第3个变化沿对应的电角度值
#define HALLTHETA4								(S_REG_INPUT_START_OTHERS + 11) // Hall第4个变化沿对应的电角度值
#define HALLTHETA5								(S_REG_INPUT_START_OTHERS + 12) // Hall第5个变化沿对应的电角度值
#define HALLSTATUS01							(S_REG_INPUT_START_OTHERS + 13) // Hall变化沿对应的Hall值，高8位：第1个Hall值；低8位：第0个Hall值；
#define HALLSTATUS23							(S_REG_INPUT_START_OTHERS + 14) // Hall变化沿对应的Hall值，高8位：第3个Hall值；低8位：第2个Hall值；
#define HALLSTATUS45							(S_REG_INPUT_START_OTHERS + 15) // Hall变化沿对应的Hall值，高8位：第5个Hall值；低8位：第4个Hall值；
#define LMJRSTATUS								(S_REG_INPUT_START_OTHERS + 16) // 惯量辨识状态
#define LMJRRESULT_L							(S_REG_INPUT_START_OTHERS + 17) // 惯量辨识结果
#define LMJRRESULT_H							(S_REG_INPUT_START_OTHERS + 18)
#define ECCOMMSTATE								(S_REG_INPUT_START_OTHERS + 19) // EtherCAT从站状态，如OP
#define FBSYNCACT								(S_REG_INPUT_START_OTHERS + 20) // 总线同步周期
#define FBOPMODE								(S_REG_INPUT_START_OTHERS + 21) // 0x6061 Modes of operation Display
#define PCMDFBRAW_L								(S_REG_INPUT_START_OTHERS + 22) // 0x607A 位置给定，通讯变量传递给电机控制
#define PCMDFBRAW_H								(S_REG_INPUT_START_OTHERS + 23)
#define ESTSTATUS								(S_REG_INPUT_START_OTHERS + 24) // 电机参数辨识状态
#define CANCONTROLWORD							(S_REG_INPUT_START_OTHERS + 25) // 0x6040 CAN controlword
#define CANSTATUSWORD							(S_REG_INPUT_START_OTHERS + 26) // 0x6041 CAN statusword
#define FBOPMODERAW								(S_REG_INPUT_START_OTHERS + 27) // 0x6060 Modes of operation
#define ENCCALSTATUS							(S_REG_INPUT_START_OTHERS + 28) // 编码器标定状态
#define ENCSPISRC								(S_REG_INPUT_START_OTHERS + 29) // SPI编码器类型

//************** 报错信息 S_REG_INPUT_INDEX_PROTECT (5) **************//
#define CURRENTTIME								(S_REG_INPUT_START_PROTECT + 0) // 当前时间，从上电开始计数，最多可以记45.5天
#define ERRORSTATUS0							(S_REG_INPUT_START_PROTECT + 1) // 报错0，详见报错定义
#define ERRORSTATUS1							(S_REG_INPUT_START_PROTECT + 2) // 报错1，详见报错定义
#define ERRORSTATUS2							(S_REG_INPUT_START_PROTECT + 3) // 报错2，详见报错定义
#define ERRORTIME0								(S_REG_INPUT_START_PROTECT + 4) // 报错历史记录时间0，将报错时的CURRENTTIME锁存
#define ERRORHIST0								(S_REG_INPUT_START_PROTECT + 5) // 报错历史记录0
#define ERRORTIME1								(S_REG_INPUT_START_PROTECT + 6)
#define ERRORHIST1								(S_REG_INPUT_START_PROTECT + 7)
#define ERRORTIME2								(S_REG_INPUT_START_PROTECT + 8)
#define ERRORHIST2								(S_REG_INPUT_START_PROTECT + 9)
#define ERRORTIME3								(S_REG_INPUT_START_PROTECT + 10)
#define ERRORHIST3								(S_REG_INPUT_START_PROTECT + 11)
#define ERRORTIME4								(S_REG_INPUT_START_PROTECT + 12)
#define ERRORHIST4								(S_REG_INPUT_START_PROTECT + 13)
#define ERRORTIME5								(S_REG_INPUT_START_PROTECT + 14)
#define ERRORHIST5								(S_REG_INPUT_START_PROTECT + 15)
#define ERRORTIME6								(S_REG_INPUT_START_PROTECT + 16)
#define ERRORHIST6								(S_REG_INPUT_START_PROTECT + 17)
#define ERRORTIME7								(S_REG_INPUT_START_PROTECT + 18)
#define ERRORHIST7								(S_REG_INPUT_START_PROTECT + 19)
#define ERRORTIME8								(S_REG_INPUT_START_PROTECT + 20)
#define ERRORHIST8								(S_REG_INPUT_START_PROTECT + 21)
#define ERRORTIME9								(S_REG_INPUT_START_PROTECT + 22)
#define ERRORHIST9								(S_REG_INPUT_START_PROTECT + 23)
#define ERRORTIME10								(S_REG_INPUT_START_PROTECT + 24)
#define ERRORHIST10								(S_REG_INPUT_START_PROTECT + 25)
#define ENCODERERR								(S_REG_INPUT_START_PROTECT + 26) // 编码器具体报错
#define WARNSTATUS0								(S_REG_INPUT_START_PROTECT + 27) // 驱动器警告
#define WARNSTATUS1								(S_REG_INPUT_START_PROTECT + 28)
#define SFBENCERR								(S_REG_INPUT_START_PROTECT + 29) // 负载侧编码器具体报错
#define PHASEFINDERR							(S_REG_INPUT_START_PROTECT + 30) // 寻相具体报错

//************** 测试寄存器 S_REG_INPUT_INDEX_TEST (6) **************//
#define TESTVAR0								(S_REG_INPUT_START_TEST + 0) // 测试通道0
#define TESTVAR1								(S_REG_INPUT_START_TEST + 1) // 测试通道1
#define TESTVAR2								(S_REG_INPUT_START_TEST + 2)
#define TESTVAR3_L								(S_REG_INPUT_START_TEST + 3)
#define TESTVAR3_H								(S_REG_INPUT_START_TEST + 4)
#define TESTVAR4_L								(S_REG_INPUT_START_TEST + 5)
#define TESTVAR4_H								(S_REG_INPUT_START_TEST + 6)
#define TESTVAR5_L								(S_REG_INPUT_START_TEST + 7)
#define TESTVAR5_H								(S_REG_INPUT_START_TEST + 8)


// read only
// Definition of register DRIVESTATUS
#define STATUS_WARNING                                 0x0080          // rw-- 1:warning exist
#define STATUS_STOPPED                                 0x0020          // rw-- 0=运动曲线结束，1=在运动位置曲线
#define STATUS_INPOS                                   0x0010          // rw-- 1:In pos ok；0:In pos not ok
#define STATUS_PHASEFINDSUCCEED                        0x0008          // rw-- 1:phase find succeed
#define STATUS_HOMECOMPLETE                            0x0004          // rw-- 1:home complete
#define STATUS_FAULT                                   0x0002          // rw-- 1:fault exist
#define STATUS_ENABLE                                  0x0001          // rw-- 0: motor disable; 1: motor enable


// Definition of register CONTROLSTATUS
#define CTSTATUS_DATASTREAM                            0x0100          // rw-- 1:Data Stream mode；0:Modbus mode
#define CTSTATUS_FLASHSTATE2                           0x0080          // r-- 0 = FLASH_SUCCESS; 1 = FLASH_FAIL_FROZEN
#define CTSTATUS_FLASHSTATE1                           0x0040          // r-- 2 = FLASH_FAIL_UNLOCK; 3 = FLASH_FAIL_PREPROGRAM
#define CTSTATUS_FLASHSTATE0                           0x0020          // r-- 4 = FLASH_FAIL_ERASE; 5 = FLASH_FAIL_WRITE; 7 = FLASH_OPERATING
#define CTSTATUS_MCSTATE4                              0x0010          // r-- 0 = Ready：计算电流offset; 1 = Idle：空闲状态
#define CTSTATUS_MCSTATE3                              0x0008          // r-- 2 = Disable：去使能状态; 3 = PhaseFind：寻相
#define CTSTATUS_MCSTATE2                              0x0004          // r-- 4 = Home：回零; 5 = Start：使能
#define CTSTATUS_MCSTATE1                              0x0002          // r-- 6 = Run：运动; 7 = Stop：停止; 8 = Fault：报错
#define CTSTATUS_MCSTATE0                              0x0001          // r-- 9 = UpFlash：从Flash加载参数; 10 = DownFlash：下载参数到Flash




typedef struct
{
	USHORT Length[4];
	UCHAR * Addr[4]; // including head, data, CRC
	UCHAR Count; // 3 or 4
} SendFramePointerTypeDef;

extern SendFramePointerTypeDef SendFramePointer;

extern USHORT usSRegInBuf[S_REG_INPUT_NREGS];
extern const USHORT usSRegInStartArray[S_REG_INPUT_INDEX_MAX + 1];
extern USHORT usSRegHoldBuf[S_REG_HOLDING_NREGS];
extern const USHORT usSRegHoldStartArray[S_REG_HOLDING_INDEX_MAX + 1];
extern USHORT usSRegScopeBuf[S_REG_SCOPE_NREGS];

#endif
