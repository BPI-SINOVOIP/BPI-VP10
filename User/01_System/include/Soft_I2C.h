/*
 * Copyright (c) 2025-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : Soft_I2C.h
 * Author        : Zougi.Zou
 * Date          : 2025-8-18
 * Description   : define SPI
 *
 * Record        :
 * V1.0, 2025-8-18, Zougi.Zou: Created file
 */

#ifndef __SOFT_I2C_H__
#define __SOFT_I2C_H__


//IIC
typedef enum
{
	I2C_IDLE,						//空闲
	I2C_START,					//开始操作
	I2C_SEND_BIT,			//发送数据
	I2C_READ_BIT,				//读数据
	I2C_ACK,						//应答位
	I2C_NACK,					//报错位
	I2C_STOP					//结束为
} I2C_State;


typedef struct
{

	I2C_State State;
	uint8 Adress;
	uint8 ReadData;
	uint8 SendData;

} SoftI2C;

extern SoftI2C SC7A20H;

extern void IIC_W_SCL(uint8 bit1);
extern void IIC_W_SDA(uint8 bit1);
extern uint8 IIC_R_SDA(void);
//extern uint8 IIC_Start(void);
//extern uint8 IIC_Stop(void);
extern uint8 IIC_Send_Data(uint8 data1);
extern uint8 IIC_Receive_data(uint8* data1);
extern uint8 IIC_Send_Ack(uint8 bit1);
extern uint8 IIC_Receive_Ack(uint8* Ack);
extern uint8 Sensor_WriteByte(uint8 Sensor_Adress, uint8 Reg_Adress, uint8 byte);
extern uint8 Sensor_Receive_Data(uint8 Sensor_Adress, uint8 Reg_Adress, uint8* byte);
extern uint8 Sensor_Write_Array(uint8 Sensor_Adress, uint8 Reg_Adress, uint8* array, uint8 length);
extern uint8 Sensor_Receive_Array(uint8 Sensor_Adress, uint8 Reg_Adress, uint8* Array, uint8 length);

extern void IIC_Delay(void);
extern void IIC_Start(void);
extern void IIC_Stop(void);
extern uint8 IIC_Send_Byte(uint8 data);
extern uint8 IIC_Read_Byte(uint8 ack);
extern uint8 AT24C16_Read_Array(uint16 addr, uint8* data, uint16 len);
extern uint8 AT24C16_Read_Array_Step1(uint16 addr);
extern uint8 AT24C16_Read_Array_Step2(uint8* data, uint16 len, uint8 mode);
extern uint8 AT24C16_Read_Array_Step3();
extern uint8 AT24C16_Write_Array(uint16 addr, uint8* data, uint16 len);

#endif//__SOFT_I2C_H__

/*** (C) Copyright 2011-2022 Fortior Technology Co., Ltd. ***/
