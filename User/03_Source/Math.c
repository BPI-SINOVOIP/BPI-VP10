/*
 * Copyright (c) 2023-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : Math.c
 * Author        : wynn.wang
 * Date          : 2023-08-11
 * Description   : Math library
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

/*---------------------------------------------------------------------------
 * Name		:	SinCalc
 * Input	:	Theta - input angle -32768~32767, corresponds to -pi~pi
 *				Vs -  input amplitude 0-32767
 * Output	:	Vs * sin(Theta)
 * Description:	Sine calculation
 *---------------------------------------------------------------------------*/
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


/*---------------------------------------------------------------------------
 * Name		:	CosCalc
 * Input	:	Theta - input angle -32768~32767, corresponds to -pi~pi
 *				Vs -  input amplitude 0-32767
 * Output	:	Vs * cos(Theta)
 * Description:	Cosine calculation
 *---------------------------------------------------------------------------*/
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


/*---------------------------------------------------------------------------
 * Name		:	CosCalc
 * Input	:	Theta - input angle -32768~32767, corresponds to -pi~pi
 * Output	:	tan(Theta) * 32768
 * Description:	Tangent calculation
 *---------------------------------------------------------------------------*/
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


/*---------------------------------------------------------------------------
 * Name		:	Abs_F16
 * Input	:	value - input value, -32768~32767
 * Output	:	|value|
 * Description:	Take absolute value of 16-bit variable
 *---------------------------------------------------------------------------*/
int16 Abs_F16(int16 value)
{
	if (value < 0) return (-value);
	else return (value);
}


/*---------------------------------------------------------------------------
 * Name		:	Abs_F32
 * Input	:	value - input value
 * Output	:	|value|
 * Description:	Take absolute value of 32-bit variable
 *---------------------------------------------------------------------------*/
int32 Abs_F32(int32 value)
{
	if (value < 0) return (-value);
	else return (value);
}


/*---------------------------------------------------------------------------
 * Name		:	Log2_32
 * Input	:	x - input 32-bit integer
 * Output	:	log2(x)
 * Description:	Compute logarithm of 32-bit variable, works faster and uses less .text and .data 
 *				than system log2.
 *---------------------------------------------------------------------------*/
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

/*---------------------------------------------------------------------------
 * Name		:	Log2_64
 * Input	:	x - input 64-bit integer
 * Output	:	log2(x)
 * Description:	Compute logarithm of 64-bit variable, works faster and uses less .text and .data 
 *				than system log2.
 *---------------------------------------------------------------------------*/

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

/*---------------------------------------------------------------------------
 * Name		:	InvSqrt
 * Input	:	x - float
 * Output	:	sqrt(x)
 * Description:	Calculate square root; works faster and uses less .text and .data than system sqrt.
 *				However this function uses floating-point operations which may pull in larger libraries and is generally not recommended.
 *---------------------------------------------------------------------------*/
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

/*---------------------------------------------------------------------------
 * Name		:	Sqrt_32
 * Input	:	M - uint32
 * Output	:	uint32
 * Description:	Calculate the square root of a 32-bit variable, work faster and use less .text and .data than 
 *				InvSqrt and system sqrt.
 *---------------------------------------------------------------------------*/
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


/*---------------------------------------------------------------------------
 * Name		:	Sqrt_64
 * Input	:	M - uint64
 * Output	:	uint32
 * Description:	Calculate the square root of a 64-bit variable, work faster and use less .text and .data than 
 *				InvSqrt and system sqrt.
 *---------------------------------------------------------------------------*/
uint32 Sqrt_64(uint64 M)
{
	uint32 N, i;
	uint32 tmp, ttp;
	uint32 h = M >> 32; // High 32 bits of 64-bit integer
	uint32 l = M & 0xFFFFFFFF; // Low 32 bits of 64-bit integer

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


/*---------------------------------------------------------------------------
 * Name		:	MagicCubeRoot

* Input	:	x - float
 * Output	:	float
 * Description:	Compute cube root, work faster and use less .text and .data than system pow.
 *				However this function uses floating point operations, which will pull in some relatively large libraries; generally not recommended for use.
 *---------------------------------------------------------------------------*/
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


/*---------------------------------------------------------------------------
 * Name		:	CubeRoot_U32
 * Input	:	x - uint32
 * Output	:	uint32
 * Description:	Compute the cube root of a 32-bit integer, works faster and uses less .text and .data 
 *				than system pow.
 *---------------------------------------------------------------------------*/
uint32 CubeRoot_U32(uint32 x)
{
	if (x == 0 || x == 1)
		return x;
	else
	{
		uint32 min = 0;
		uint32 max = 1625; // maximum solution for cube root of 32-bit unsigned integer input
		uint32 mid = 0;
		uint32 product = 0;
		
		if (max > (x >> 1))
			max = (x >> 1);

		while ((max - min) > 1)
		{
			mid = (max + min) >> 1;

			if (mid > 1625) mid = 1625; // maximum solution for cube root of 32-bit unsigned integer input

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


/*---------------------------------------------------------------------------
 * Name		:	CubeRoot_U64
 * Input	:	x - uint64
 * Output	:	uint32
 * Description:	Compute the cube root of a 64-bit integer, works faster and uses less .text and .data 
 *				than system pow.
 *---------------------------------------------------------------------------*/
uint32 CubeRoot_U64(uint64 x)
{
	if (x == 0 || x == 1)
		return x;
	else
	{
		uint32 min = 0;
		uint32 max = 2642245; // maximum solution for cube root of 64-bit unsigned integer input
		uint32 mid = 0;
		uint64 product = 0;
		
		if (x < 4294967295) // 32-bit
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


/*---------------------------------------------------------------------------
 * Name		:	Mul_64_32
 * Input	:	x - 64-bit input value, y - 32-bit input value
 * Output	:	x * y
 * Description:	Split the 64-bit multiplicand into high 32 bits and low 32 bits, multiply each by the 32-bit multiplier, then combine.
 *				To avoid bringing in the relatively large moddi3 library (868 bytes)
 *---------------------------------------------------------------------------*/
int64 Mul_64_32(int64 x, int32 y)
{
	/* Split x into high 32 bits and low 32 bits */
	int32 x_hi = (int32)(x >> 32);          /* signed high 32 bits */
	uint32 x_lo = (uint32)(x & 0xFFFFFFFF);  /* unsigned low 32 bits */

	/*
	 * x * y = (x_hi * 2^32 + x_lo) * y
	 *       = x_hi * y * 2^32  +  x_lo * y
	 *
	 * Note:
	 *   x_hi * y  uses signed 32×32, result stored in 64 bits (preserve sign)
	 *   x_lo * y  low 32 bits multiplied by signed 32, result received into 64 bits (to avoid overflow)
	 */
	int64 hi_part = (int64)x_hi * (int64)y;   /* 32×32 -> 64 */
	int64 lo_part = (int64)x_lo * (int64)y;   /* 32×32 -> 64 */

	return (hi_part << 32) + lo_part;
}

/********************************* END OF FILE *********************************/