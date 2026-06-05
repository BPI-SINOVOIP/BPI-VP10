/*
 * Copyright (c) 2025-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : Soft_I2C.c
 * Author        : Zougi.Zou
 * Date          : 2025-8-18
 * Description   : define SPI
 *
 * Record        :
 * V1.0, 2025-8-18, Zougi.Zou: Created file
 */

#include <Myproject.h>
#include <Soft_I2C.h>

#if FUNC_SOFT_EEPROM_ENABLED
// 添加延时函数
void IIC_Delay(void) 
{
	for (volatile int i = 0; i < 1; i++); // 根据实际时钟调整
}

void IIC_W_SCL(uint8 bit1) 
{
	if (bit1 == 0) {
		set_csr(SCL_OE, SCL_PIN); // 开启输出
		clr_csr(SCL_GPIO, SCL_PIN);
	} else {
		clr_csr(SCL_OE, SCL_PIN); // 关闭输出（高阻态，依靠上拉电阻拉高）
	}
	IIC_Delay();
}

void IIC_W_SDA(uint8 bit1) 
{
	if (bit1 == 0) {
		set_csr(SDA_OE, SDA_PIN); // 开启输出
		clr_csr(SDA_GPIO, SDA_PIN);
	} else {
		clr_csr(SDA_OE, SDA_PIN); // 关闭输出（高阻态，依靠上拉电阻拉高）
	}
	IIC_Delay();
}

uint8 IIC_R_SDA(void)
{
	clr_csr(SDA_OE, SDA_PIN); // 输入模式
	IIC_Delay();
	uint8_t bit1 = readbit_csr(SDA_GPIO, SDA_PIN);
	return bit1;
}

// 简化起始信号函数
void IIC_Start(void)
{
	IIC_W_SDA(1);
	IIC_W_SCL(1);
	IIC_W_SDA(0);
	IIC_W_SCL(0);
}

// 简化停止信号函数
void IIC_Stop(void) 
{
	IIC_W_SDA(0);
	IIC_W_SCL(1);
	IIC_W_SDA(1);
}

// 简化发送字节函数
uint8 IIC_Send_Byte(uint8 data)
{
	for (uint8 i = 0; i < 8; i++) 
	{
		IIC_W_SDA((data & 0x80) ? 1 : 0);
		IIC_W_SCL(1);
		IIC_W_SCL(0);
		data <<= 1;
	}

	// 释放SDA线，读取ACK
	IIC_W_SDA(1);
	IIC_W_SCL(1);
	uint8 ack = IIC_R_SDA();
	IIC_W_SCL(0);

	return ack == 0; // 返回是否收到ACK
}

// 简化接收字节函数
uint8 IIC_Read_Byte(uint8 ack) 
{
	uint8 data = 0;

	IIC_W_SDA(1); // 释放SDA线

	for (uint8 i = 0; i < 8; i++) 
	{
		data <<= 1;
		IIC_W_SCL(1);
		if (IIC_R_SDA()) 
		{
			data |= 0x01;
		}
		IIC_W_SCL(0);
	}

	// 发送ACK或NACK
	IIC_W_SDA(ack ? 0 : 1);
	IIC_W_SCL(1);
	IIC_W_SCL(0);

	return data;
}

// 从AT24C16读取多个数据
uint8 AT24C16_Read_Array(uint16 addr, uint8 * data, uint16 len) 
{
	uint8 ret = 0;
	if (AT24C16_Read_Array_Step1(addr) == 1)
	{
		ret = AT24C16_Read_Array_Step2(data, len, 0);
		AT24C16_Read_Array_Step3();
		return ret;
	}
	else
	{
		return ret;
	}
}

// 从AT24C16读取多个数据
uint8 AT24C16_Read_Array_Step1(uint16 addr)
{
	// AT24C16的设备地址是0xA0，内存地址分为两部分
	uint8 dev_addr = 0xA0 | ((addr >> 7) & 0x0E);
	uint8 mem_addr = addr & 0xFF;

	// 发送起始信号
	IIC_Start();

	// 发送设备地址（写模式）
	if (!IIC_Send_Byte(dev_addr)) 
	{
		IIC_Stop();
		return 0; // 设备无应答
	}

	// 发送内存地址
	if (!IIC_Send_Byte(mem_addr)) {
		IIC_Stop();
		return 0; // 设备无应答
	}

	// 发送重复起始信号
	IIC_Start();

	// 发送设备地址（读模式）
	if (!IIC_Send_Byte(dev_addr | 0x01))
	{
		IIC_Stop();
		return 0; // 设备无应答
	}

	return 1; // 读取成功
}

// 从AT24C16读取多个数据
// mode: 0-最后一个字节发送NACK，其他发送ACK; 1-一直发送ACK
uint8 AT24C16_Read_Array_Step2(uint8* data, uint16 len, uint8 mode)
{
	// 读取数据
	for (uint16 i = 0; i < len; i++)
	{
		// 最后一个字节发送NACK，其他发送ACK
		data[i] = IIC_Read_Byte(i < (len - 1) || (mode == 1));
	}

	return 1; // 读取成功
}

// 从AT24C16读取多个数据
uint8 AT24C16_Read_Array_Step3()
{
	// 发送停止信号
	IIC_Stop();

	return 1; // 读取成功
}

// 向AT24C16写入多个数据（注意：AT24C16页大小为16字节）
uint8 AT24C16_Write_Array(uint16 addr, uint8 * data, uint16 len)
{
	// AT24C16的设备地址是0xA0
	uint8 dev_addr = 0xA0 | ((addr >> 7) & 0x0E);
	uint8 mem_addr = addr & 0xFF;

	// 检查是否跨页
	uint16 page_start = addr & 0xFFF0;
	uint16 page_end = page_start + 16;
	uint16 bytes_in_page = (addr + len > page_end) ? (page_end - addr) : len;

	// 发送起始信号
	IIC_Start();

	// 发送设备地址（写模式）
	if (!IIC_Send_Byte(dev_addr)) 
	{
		IIC_Stop();
		return 0; // 设备无应答
	}

	// 发送内存地址
	if (!IIC_Send_Byte(mem_addr)) 
	{
		IIC_Stop();
		return 0; // 设备无应答
	}

	// 写入数据
	for (uint16 i = 0; i < bytes_in_page; i++) 
	{
		if (!IIC_Send_Byte(data[i])) 
		{
			IIC_Stop();
			return 0; // 设备无应答
		}
	}

	// 发送停止信号
	IIC_Stop();

	// 等待写入完成
	// 这里需要添加适当的延时，通常5-10ms
	Delay_ms(6);
	IWDT_Refresh(); // 及时喂狗

	// 如果还有剩余数据需要写入下一页
	if (bytes_in_page < len) 
	{
		return AT24C16_Write_Array(addr + bytes_in_page, data + bytes_in_page, len - bytes_in_page);
	}

	return 1; // 写入成功
}

#endif // #if FUNC_SOFT_EEPROM_ENABLED