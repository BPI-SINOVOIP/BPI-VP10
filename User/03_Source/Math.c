/*
 * Copyright (c) 2023-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : Math.c
 * Author        : wynn.wang
 * Date          : 2023-08-11
 * Description   : 数学库
 *
 * Record        :
 * V1.0, 2023-08-11, wynn.wang: Created file
 */


/********************************************************************************
 * Header Definition
 ********************************************************************************/
#include <Myproject.h>
/********************************************************************************
 * Macro & Structure Definition
 *******************************************************************************/


/********************************************************************************
 * Internal Routine Prototypes
 ********************************************************************************/
int16 SinCalc(int16 Theta, uint16 Vs);
int16 CosCalc(int16 Theta, uint16 Vs);
int32 TanCalc(int16 Theta);

/*---------------------------------------------------------------------------*/
/* Name     :   SinCalc
/* Input    :   Theta: 输入角度-32768~32767，对应的-pi～pi
/*				Vs: 输入幅值0-32767
/* Output   :   Value * 32768
/* Description: 正弦计算
/*---------------------------------------------------------------------------*/
int16 SinCalc(int16 Theta, uint16 Vs)
{
	int16 SinValue = 0;

	NFOC_THETA0 = Theta;
	NFOC_XI0 = Vs;
	NFOC_YI0 = 0;

	set_csr(ME_COR, 0x01);
	while (read_csr(ME_COR));

	SinValue = NFOC_YO0;

	return SinValue;
}

/*---------------------------------------------------------------------------*/
/* Name     :   CosCalc
/* Input    :   Theta: 输入角度-32768~32767，对应的-pi～pi
/*				Vs: 32767
/* Output   :   Value * 32768
/* Description: 余弦计算
/*---------------------------------------------------------------------------*/
int16 CosCalc(int16 Theta, uint16 Vs)
{
	int16 CosValue = 0;

	NFOC_THETA0 = Theta;
	NFOC_XI0 = 0;
	NFOC_YI0 = Vs;

	set_csr(ME_COR, 0x01);
	while (read_csr(ME_COR));

	CosValue = NFOC_YO0;

	return CosValue;
}

/*---------------------------------------------------------------------------*/
/* Name     :   TanCalc
/* Input    :   Theta: 输入角度-32768~32767，对应的-pi～pi
/* Output   :   Value * 32768
/* Description: tan计算
/*---------------------------------------------------------------------------*/
int32 TanCalc(int16 Theta)
{
	int16 SinValue = 0;
	int16 CosValue = 0;
	int32 TanValue = 0;

	SinValue = SinCalc(Theta, 32767);
	CosValue = CosCalc(Theta, 32767);
	TanValue = ((int32)SinValue << 15) / CosValue;

	return TanValue;
}


/*---------------------------------------------------------------------------*/
/* Name     :   uint16 Abs_F16(int16 value)
/* Input    :   value
/* Output   :   uint16
/* Description: 对16位的变量取绝对值
/*---------------------------------------------------------------------------*/
int16 Abs_F16(int16 value)
{
	if (value < 0) return (-value);
	else return (value);
}


/*---------------------------------------------------------------------------*/
/* Name     :   int32 Abs_F32(int32 value)
/* Input    :   value
/* Output   :   int32
/* Description: 对32位的变量取绝对值
/*---------------------------------------------------------------------------*/
int32 Abs_F32(int32 value)
{
	if (value < 0) return (-value);
	else return (value);
}


/*---------------------------------------------------------------------------*/
/* Name		:	void Log2_32(int32 x)
/* Input	:	x
/* Output	:	log2(x)
/* Description:	对32位的变量求对数, work faster and use less .text and .data than system log2.
/*---------------------------------------------------------------------------*/
int32 Log2_32(int32 x)
{
	int32 rst = 0;
	if (x & 0xffff0000U) rst += 16, x >>= 16;
	if (x & 0x0000ff00U) rst += 8, x >>= 8;
	if (x & 0x000000f0U) rst += 4, x >>= 4;
	if (x & 0x0000000cU) rst += 2, x >>= 2;
	if (x & 0x00000002U) rst += 1;
	return rst;
}

/*---------------------------------------------------------------------------*/
/* Name		:	void Log2_64(uint64 x)
/* Input	:	x
/* Output	:	log2(x)
/* Description:	对32位的变量求对数, work faster and use less .text and .data than system log2.
/*---------------------------------------------------------------------------*/
int32 Log2_64(uint64 x)
{
	int32 rst = 0;
	if (x & 0xffffffff00000000) { rst += 32; x >>= 32; }
	if (x & 0x00000000ffff0000) { rst += 16; x >>= 16; }
	if (x & 0x000000000000ff00) { rst += 8; x >>= 8; }
	if (x & 0x00000000000000f0) { rst += 4; x >>= 4; }
	if (x & 0x000000000000000c) { rst += 2; x >>= 2; }
	if (x & 0x0000000000000002) { rst += 1; x >>= 1; }
	return rst;
}

/*---------------------------------------------------------------------------*/
/* Name		:	void InvSqrt(void)
/* Input	:	x - float
/* Output	:	float
/* Description:	求开方，work faster and use less .text and .data than system sqrt.
/*				但是该函数调用了浮点数，会引入一些较大的库，一般不建议使用。
/*---------------------------------------------------------------------------*/
float InvSqrt(float x)
{
	float xhalf = 0.5f *x;
	int i = *(int*) & x; // get bits for floating VALUE
	i = 0x5f375a86 - (i >> 1); // gives initial guess y0
	x = *(float*) & i; // convert bits BACK to float
	x = x * (1.5f - xhalf * x * x); // Newton step, repeating increases accuracy
	x = x * (1.5f - xhalf * x * x); // Newton step, repeating increases accuracy
	x = x * (1.5f - xhalf * x * x); // Newton step, repeating increases accuracy

	return 1 / x;
}

/*---------------------------------------------------------------------------*/
/* Name		:	uint32 Sqrt_32(uint32 M)
/* Input	:	uint32
/* Output	:	uint32
/* Description:	对32位的变量求开方, work faster and use less .text and .data than system sqrt and InvSqrt.
/*---------------------------------------------------------------------------*/
uint32 Sqrt_32(uint32 M)
{
	uint32 N, i;
	uint32 tmp, ttp;

	if (M == 0)
	{
		return 0;
	}

	N = 0;
	tmp = (M >> 30);
	M <<= 2;

	if (tmp > 1)
	{
		N++;
		tmp -= N;
	}

	for (i = 15; i > 0; i--)
	{
		N <<= 1;
		tmp <<= 2;
		tmp += (M >> 30);

		ttp = N;
		ttp = (ttp << 1) + 1;

		M <<= 2;
		if (tmp >= ttp)
		{
			tmp -= ttp;
			N++;
		}
	}

	return N;
}

//
/*---------------------------------------------------------------------------*/
/* Name		:	uint32 Sqrt_64(uint64 M)
/* Input	:	H是64位整数的高32位，L是64位整数的低32位
/* Output	:	uint32
/* Description:	对64位的变量求开方, InvSqrt里面浮点数运算调用的库太大.
/*---------------------------------------------------------------------------*/
uint32 Sqrt_64(uint64 M)
{
	uint32 N, i;
	uint32 tmp, ttp;
	uint32 h = M >> 32;
	uint32 l = M & 0xFFFFFFFF;

	if (h == 0)
	{
		return Sqrt_32(l);
	}
	else
	{
		N = 0;
		tmp = (h >> 30);
		h <<= 2;

		if (tmp > 1)
		{
			N++;
			tmp -= N;
		}

		for (i = 15; i > 0; i--)
		{
			N <<= 1;
			tmp <<= 2;
			tmp += (h >> 30);

			ttp = N;
			ttp = (ttp << 1) + 1;

			h <<= 2;
			if (tmp >= ttp)
			{
				tmp -= ttp;
				N++;
			}
		}

		for (i = 16; i > 0; i--)
		{
			N <<= 1;
			tmp <<= 2;
			tmp += (l >> 30);

			ttp = N;
			ttp = (ttp << 1) + 1;

			l <<= 2;
			if (tmp >= ttp)
			{
				tmp -= ttp;
				N++;
			}
		}
		return N;
	}
}


/*---------------------------------------------------------------------------*/
/* Name		:	void MagicCubeRoot(void)
/* Input	:	x - float
/* Output	:	float
/* Description:	求立方，work faster and use less .text and .data than system pow.
/*				但是该函数调用了浮点数，会引入一些较大的库，一般不建议使用。
/*---------------------------------------------------------------------------*/
float MagicCubeRoot(float x)
{
	if (x < 0)
	{
		x = -x;

		float xthird = 0.333f *x;
		int i = *(int*) & x;
		i = (0x2a517d47 + (0.333f *i));//i = (int) (0x2a517d3c + (0.333f * i));
		x = *(float*) & i;
		x = 0.667f *x + xthird / (x * x);
		x = 0.667f *x + xthird / (x * x);

		x = -x;
	}
	else
	{
		float xthird = 0.333f *x;
		int i = *(int*) & x;
		i = (0x2a517d47 + (0.333f *i));//i = (int) (0x2a517d3c + (0.333f * i));
		x = *(float*) & i;
		x = 0.667f *x + xthird / (x * x);
		x = 0.667f *x + xthird / (x * x);
	}

	return x;
}

/*---------------------------------------------------------------------------*/
/* Name		:	uint32 Sqrt_32(uint32 M)
/* Input	:	uint32
/* Output	:	uint32
/* Description:	对32位的变量求立方.
/*---------------------------------------------------------------------------*/
uint32 CubeRoot_U32(uint32 x)
{
	if (x == 0 || x == 1)
		return x;
	else
	{
		uint32 min = 0;
		uint32 max = 1625; // 32位无符号整型输入数据开立方的最大解
		uint32 mid = 0;
		uint32 product = 0;
		
		if (max > (x >> 1))
			max = (x >> 1);

		while ((max - min) > 1)
		{
			mid = (max + min) >> 1;

			if (mid > 1625) mid = 1625; // 32位无符号整型输入数据开立方的最大解

			product = mid * mid * mid;
			if (product > x)
				max = mid;
			else if (product < x)
				min = mid;
			else
				return mid;
		}
		return min;
	}
}

/*---------------------------------------------------------------------------*/
/* Name		:	uint32 CubeRoot_U64(uint64 x)
/* Input	:	uint64
/* Output	:	uint32
/* Description:	对64位的变量求立方.
/*---------------------------------------------------------------------------*/
uint32 CubeRoot_U64(uint64 x)
{
	if (x == 0 || x == 1)
		return x;
	else
	{
		uint32 min = 0;
		uint32 max = 2642245; // 64位无符号整型输入数据开立方的最大解
		uint32 mid = 0;
		uint64 product = 0;
		
		if (x < 4294967295) // 32 位
			max = 1625;
		if (max > (x >> 1))
			max = (x >> 1);

		while ((max - min) > 1)
		{
			mid = (max + min) >> 1;

			product = (uint64)mid * mid * mid;
			if (product > x)
				max = mid;
			else if (product < x)
				min = mid;
			else
				return mid;
		}
		
		return min;
	}
}


/*---------------------------------------------------------------------------*/
/* Name		:	int64 Mul_64_32(int64 x, int32 y)
/* Input	:	uint32
/* Output	:	uint64
/* Description:	把 64 位被乘数拆成高 32 位和低 32 位，分别乘以 32 位乘数，再合并.
/*				为了避免引入较大的库moddi3(868 byte)
/*---------------------------------------------------------------------------*/
int64 Mul_64_32(int64 x, int32 y)
{
	/* 拆分 x 为高32位和低32位 */
	int32 x_hi = (int32)(x >> 32);          /* 有符号高32位 */
	uint32 x_lo = (uint32)(x & 0xFFFFFFFF);  /* 无符号低32位 */

	/*
	 * x * y = (x_hi * 2^32 + x_lo) * y
	 *       = x_hi * y * 2^32  +  x_lo * y
	 *
	 * 注意：
	 *   x_hi * y  用有符号32×32，结果放入64位（保留符号）
	 *   x_lo * y  低32位乘有符号32，结果用64位接收（防溢出）
	 */
	int64 hi_part = (int64)x_hi * (int64)y;   /* 32×32 -> 64 */
	int64 lo_part = (int64)x_lo * (int64)y;   /* 32×32 -> 64 */

	return (hi_part << 32) + lo_part;
}

/********************************* END OF FILE *********************************/

