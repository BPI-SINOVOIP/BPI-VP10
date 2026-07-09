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
// Add delay function
void IIC_Delay(void) 
{
	for (volatile int i = 0; i < 1; i++); // Adjust according to the actual clock
}

void IIC_W_SCL(uint8 bit1) 
{
	if (bit1 == 0) {
		set_csr(SCL_OE, SCL_PIN); // Enable output
		clr_csr(SCL_GPIO, SCL_PIN);
	} else {
		clr_csr(SCL_OE, SCL_PIN); // Disable output (high-impedance, pulled up by pull-up resistor)
	}
	IIC_Delay();
}

void IIC_W_SDA(uint8 bit1) 
{
	if (bit1 == 0) {
		set_csr(SDA_OE, SDA_PIN); // Enable output
		clr_csr(SDA_GPIO, SDA_PIN);
	} else {
		clr_csr(SDA_OE, SDA_PIN); // Disable output (high-impedance, pulled up by pull-up resistor)
	}
	IIC_Delay();
}

uint8 IIC_R_SDA(void)
{
	clr_csr(SDA_OE, SDA_PIN); // Input mode
	IIC_Delay();
	uint8_t bit1 = readbit_csr(SDA_GPIO, SDA_PIN);
	return bit1;
}

// Simplified start signal function
void IIC_Start(void)
{
	IIC_W_SDA(1);
	IIC_W_SCL(1);
	IIC_W_SDA(0);
	IIC_W_SCL(0);
}

// Simplified stop signal function
void IIC_Stop(void) 
{
	IIC_W_SDA(0);
	IIC_W_SCL(1);
	IIC_W_SDA(1);
}

// Simplified send byte function
uint8 IIC_Send_Byte(uint8 data)
{
	for (uint8 i = 0; i < 8; i++) 
	{
		IIC_W_SDA((data & 0x80) ? 1 : 0);
		IIC_W_SCL(1);
		IIC_W_SCL(0);
		data <<= 1;
	}

	// Release SDA line and read ACK
	IIC_W_SDA(1);
	IIC_W_SCL(1);
	uint8 ack = IIC_R_SDA();
	IIC_W_SCL(0);

	return ack == 0; // Return whether ACK was received
}

// Simplified receive byte function
uint8 IIC_Read_Byte(uint8 ack) 
{
	uint8 data = 0;

	IIC_W_SDA(1); // Release SDA line

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

	// Send ACK or NACK
	IIC_W_SDA(ack ? 0 : 1);
	IIC_W_SCL(1);
	IIC_W_SCL(0);

	return data;
}

// Read multiple bytes from AT24C16
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

// Read multiple bytes from AT24C16
uint8 AT24C16_Read_Array_Step1(uint16 addr)
{
	// The device address of AT24C16 is 0xA0, and the memory address is divided into two parts
	uint8 dev_addr = 0xA0 | ((addr >> 7) & 0x0E);
	uint8 mem_addr = addr & 0xFF;

	// Send start signal
	IIC_Start();

	// Send device address (write mode)
	if (!IIC_Send_Byte(dev_addr)) 
	{
		IIC_Stop();
		return 0; // No device response
	}

	// Send memory address
	if (!IIC_Send_Byte(mem_addr)) {
		IIC_Stop();
		return 0; // No device response
	}

	// Send repeated start signal
	IIC_Start();

	// Send device address (read mode)
	if (!IIC_Send_Byte(dev_addr | 0x01))
	{
		IIC_Stop();
		return 0; // No device response
	}

	return 1; // Read successful
}

// Read multiple bytes from AT24C16
// mode: 0 - send NACK for the last byte, send ACK for others; 1 - always send ACK
uint8 AT24C16_Read_Array_Step2(uint8* data, uint16 len, uint8 mode)
{
	// Read data
	for (uint16 i = 0; i < len; i++)
	{
		// Send NACK for the last byte, send ACK for others
		data[i] = IIC_Read_Byte(i < (len - 1) || (mode == 1));
	}

	return 1; // Read successful
}

// Read multiple bytes from AT24C16
uint8 AT24C16_Read_Array_Step3()
{
	// Send stop signal
	IIC_Stop();

	return 1; // Read successful
}

// Write multiple bytes to AT24C16 (Note: AT24C16 page size is 16 bytes)
uint8 AT24C16_Write_Array(uint16 addr, uint8 * data, uint16 len)
{
	// The device address of AT24C16 is 0xA0
	uint8 dev_addr = 0xA0 | ((addr >> 7) & 0x0E);
	uint8 mem_addr = addr & 0xFF;

	// Check if crossing a page
	uint16 page_start = addr & 0xFFF0;
	uint16 page_end = page_start + 16;
	uint16 bytes_in_page = (addr + len > page_end) ? (page_end - addr) : len;

	// Send start signal
	IIC_Start();

	// Send device address (write mode)
	if (!IIC_Send_Byte(dev_addr)) 
	{
		IIC_Stop();
		return 0; // No device response
	}

	// Send memory address
	if (!IIC_Send_Byte(mem_addr)) 
	{
		IIC_Stop();
		return 0; // No device response
	}

	// Write data
	for (uint16 i = 0; i < bytes_in_page; i++) 
	{
		if (!IIC_Send_Byte(data[i])) 
		{
			IIC_Stop();
			return 0; // No device response
		}
	}

	// Send stop signal
	IIC_Stop();

	// Wait for write to complete
	// An appropriate delay is needed here, typically 5-10 ms
	Delay_ms(6);
	IWDT_Refresh(); // Refresh the watchdog in time

	// If there is remaining data to write to the next page
	if (bytes_in_page < len) 
	{
		return AT24C16_Write_Array(addr + bytes_in_page, data + bytes_in_page, len - bytes_in_page);
	}

	return 1; // Write successful
}

#endif // #if FUNC_SOFT_EEPROM_ENABLED