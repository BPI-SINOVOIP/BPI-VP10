/*
 * Copyright (c) 2022-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : Driver.c
 * Author        : Fortior Application Team
 * Date          : 2022-09-21
 * Description   : define Driver FOC
 *
 * Record        :
 * V1.0, 2022-09-21, Fortior Application Team: Created file
 */


#include <Myproject.h>


void Driver1_Init(void)
{
	/*配置PWM周期值和死区时间*/
	write_csr(DRV1_ARR, PWM_VALUE_LOAD);		// 载波频率的周期值，三角波从0加到ARR-1，再从ARR减到1
	write_csr(DRV1_DTR, ((uint32)usSRegHoldBuf[DEADTIME] * MCU_CLOCK) >> 10); // 死区时间
	write_csr(DRV1_DR, 0);
	write_csr(DRV1_CMR, 0x003f);				// 六管使能
	write_csr(DRV1_OUT, HW_PWM_IDLELEVEL);		// 空闲电平
	
	// 不赋初值的话双采样速度自动模式下第一次上电后使能前速度计算会有异常
	write_csr(DRV1_TRG1, 0x00);					// 第1次采样的DR值，赋初值
	write_csr(DRV1_TRG2, PWM_VALUE_LOAD);		// 第2次采样的DR值，赋初值


	/*驱动最终输出极性选择*/
#if(HW_PWM_LEVEL_MODE == LOW_LEVEL)
	{
		set_csr(DRV1_OUT, HREV_EN);
		set_csr(DRV1_OUT, LREV_EN);
	}
#elif(HW_PWM_LEVEL_MODE == UP_H_DOWN_L)
	{
		set_csr(DRV1_OUT, LREV_EN);
	}
#elif(HW_PWM_LEVEL_MODE == UP_L_DOWN_H)
	{
		set_csr(DRV1_OUT, HREV_EN);
	}
#endif


	/*清中断标志位，使能中断，配置比较值，设置中断优先级*/
	clr_csr(DRV1_IER, FGIE);			//FG中断使能			0-->Disable		1-->Enable
	clr_csr(DRV1_IFR, FGIF);			//清除FG中断标志位

	clr_csr(DRV1_IER, THIE);
	clr_csr(DRV1_IFR, THIF);

	clr_csr(DRV1_IFR, DCIF);			//清除DRV中断标志位

	/**************************************************
	DRV比较匹配中断模式
	当计数值等于DRV1_COMR时，根据DCIM的设置判断是否产生中断标记
	00：不产生中断       01：上升方向
	10：下降方向         11：上升/下降方向
	*************************************************/
	set_csr(DRV1_IER, DCIM1);
	clr_csr(DRV1_IER, DCIM0);

	/*设置DRV计数器的比较匹配值，当DRV计数值与COMR相等时，根据DRV_SR寄存器的DCIM是否产生比较匹配事件*/
	write_csr(DRV1_COMR, PWM_VALUE_DOWNLOAD);


	write_csr(IP8, FOC_INT_PRI);		// DRV1中断(中断号8) 优先级别为5，优先级低于过流保护

	clr_csr(DRV1_IER, DCIP);			// 0-->1个计数周期产生中断  1-->2个计数周期产生中断

	set_csr(DRV1_FCR1, CT_SEL);         // 计算FOC时机 0:电流采样后下次上溢点计算FOC  1:电流采样后立刻计算FOC

	set_csr(DRV1_CR, DRVEN);			// 计数器使能		0-->Disable		1-->Enable
//	set_csr(DRV1_CR, DRVOE);			// Driver输出使能	0-->Disable		1-->Enable

	clr_csr(DRV1_FCR0, NCALEN);			// FOC计算使能，相当于开FOC


	// 电流采样------------------------------------------------------------
#if DOUBLESAMP_ENABLE_SWITCH
	set_csr(DRV1_FCR0, NCSAMMD3);	// 双电阻两次采样(1001)，同时CT_SEL必须置一
	clr_csr(DRV1_FCR0, NCSAMMD2);
	clr_csr(DRV1_FCR0, NCSAMMD1);
	set_csr(DRV1_FCR0, NCSAMMD0);
	NFOC_CSAM = 0x09; // 采样模式初值
#else
	clr_csr(DRV1_FCR0, NCSAMMD3);	// 双电阻单次采样(0001)
	clr_csr(DRV1_FCR0, NCSAMMD2);
	clr_csr(DRV1_FCR0, NCSAMMD1);
	set_csr(DRV1_FCR0, NCSAMMD0);
	NFOC_CSAM = 0x01; // 采样模式初值
#endif
	set_csr(DRV1_FCR4, CUR_SAM_EN);		// 强制电流采样使能，无论是否使能cal_en
	
#if (HW_ADC_SYNC == ADCSAM_SYNC)
	set_csr(ME_CR, TRIG_MD);			// 开启双ADC同步采样
#endif

	// M/MT法测速------------------------------------------------------------
	clr_csr(DRV1_FCR4, MMT_SEL);			// M/MT法选择  0:M法  1:MT法

	clr_csr(DRV1_FCR4, MMT_CAL_CYCLE1);		// M/MT法计算周期选择  00:每1个载波中断 01:每2个载波中断
	clr_csr(DRV1_FCR4, MMT_CAL_CYCLE0);		// M/MT法计算周期选择  10:每4个载波中断 11:每8个载波中断

	NFOC_MBASE = usSRegHoldBuf[QEPSPEEDCOE];
	NFOC_MSHFT = usSRegHoldBuf[SPEEDCOERANK];
	NFOC_MARR = VELCTRL_TS;

	// 速度自动计算------------------------------------------------------------
	set_csr(DRV1_FCR4, SPEED_AUTO);		// 速度自动计算使能 cal_en=0: 只算MMT和均值滤波 cal_en=1:电流环只算MMT和均值滤波，外环算PDFF

	clr_csr(DRV1_FCR4, UDQ_LPF_EN);     // UDQ低通滤波器使能	0:不使能  1:使能



	// 保护------------------------------------------------------------
	write_csr(DRV1_PER, 0x0000);

#if PROT_HARDWARE_ENABLED
	write_csr(IP6, DRVPIF_INT_PRI);		// DRV1保护中断(中断号6) 优先级别为5
	set_csr(DRV1_PER, PER_MD);		// 0-报错灵敏; 1-灵敏度降低
#endif

#if PROT_OUVP_HARDWARE_ENABLED
	/**************过欠压检测参数设置************/
	clr_csr(DRV1_PER, OUVP_AUTO1);       // 00: 不使能  01: 载波周期计算一次 10: SYSTICK计算一次 11:禁止
	clr_csr(DRV1_PER, OUVP_AUTO0);
	clr_csr(DRV1_PSR, OVPIF);        // 中断标志清零
	clr_csr(DRV1_PSR, UVPIF);        // 中断标志清零

    NFOC_OVP = 0x7FFF;    // 过压保护阈值
    NFOC_UVP = 0x00;    // 欠压保护阈值
    NFOC_OVPARR = 0xFF; // 过压保护计数目标值
    NFOC_UVPARR = 0xFF; // 欠压保护计数目标值

#endif // #if PROT_OUVP_HARDWARE_ENABLED

#if PROT_SOCP_HARDWARE_ENABLED
	/**************软件过流检测参数设置************/
	NFOC_SOCP = 0x7FFF; 
	NFOC_SOCPARR = 0xFF;// 过流保护计数目标值
	clr_csr(DRV1_PSR, SOCPIF);
	set_csr(DRV1_PER, SOCP_AUTO); // 每个载波周期自动使能一次软件过流计算
#endif // #if PROT_SOCP_HARDWARE_ENABLED
	
#if PROT_OVEL_HARDWARE_ENABLED
	/**************速度超差检测参数设置************/
	NFOC_OVEL = 0x7FFF; // 速度超差保护阈值
	NFOC_OVELARR = 0xFF; // 速度超差目标值
	NFOC_OVELCNT = 0;
	clr_csr(DRV1_PSR, OVELIF);
	set_csr(DRV1_PER, OVEL_AUTO); // 每个外环周期自动使能一次速度超差计算
#endif // #if PROT_SOCP_HARDWARE_ENABLED
	
#if PROT_OSPD_HARDWARE_ENABLED
	/**************速度过超检测参数设置************/
	NFOC_OSPD = 0x7FFF; // 速度过超保护阈值
	NFOC_OSPDARR = 0xFF; // 速度过超目标值
	NFOC_OSPDCNT = 0;
	clr_csr(DRV1_PSR, OSPDIF);
	set_csr(DRV1_PER, OSPD_AUTO); // 每个载波周期自动使能一次速度过超计算
#endif // #if PROT_OSPD_HARDWARE_ENABLED
	
#if PROT_STALL_HARDWARE_ENABLED
	/**************堵转检测参数设置************/
	NFOC_LKSTH = 0x7FFF; // 堵转保护速度阈值
	NFOC_LKITH = 0x7FFF; // 堵转保护电流阈值
	NFOC_LKARR = 0xFFFF; // 堵转保护目标值
	NFOC_LKCNT = 0;
	clr_csr(DRV1_PSR, LOCKIF);
	set_csr(DRV1_PER, LOCK_MD); // 使能伺服堵转保护
	set_csr(DRV1_PER, LOCK_AUTO); // 每个载波周期自动使能一次堵转保护计算
#endif // #if PROT_STALL_HARDWARE_ENABLED
	
#if PROT_PLOSS_HARDWARE_ENABLED
	/**************缺相保护参数设置************/
	NFOC_PLTTH = 0x7FFF; // 缺相保护角度变化阈值
	NFOC_PLRTH = 0x7FFF; // 缺相保护电流命令阈值
	NFOC_PLITH = 0x7FFF; // 缺相保护相电流阈值

	clr_csr(DRV1_PSR, PLIF);
	set_csr(DRV1_PER, PL_MD); // 使能缺相保护
	set_csr(DRV1_PER, PL_AUTO); // 每个载波周期自动使能一次缺相保护计算
#endif // #if PROT_PLOSS_HARDWARE_ENABLED
	
#if PROT_CARINTOT_HARDWARE_ENABLED
	/**************载波中断超时保护参数设置************/
	clr_csr(DRV1_PSR, ODCIF_IF);
	set_csr(DRV1_PER, ODCIF_EN); // 使能载波中断超时保护
#endif // #if PROT_CARINTOT_HARDWARE_ENABLED


#if FUNC_DUTYUPDATENOW_ENABLED
	/*占空比立即更新*/
	set_csr(DRV1_CR, IMM_UPDATE);

#endif

}


