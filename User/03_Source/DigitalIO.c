/*
 * Copyright (c) 2021-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : DigitalIO.c
 * Author        : Summer
 * Date          : 2021-11-13
 * Description   : This file define some function for Digital IO.
 *
 * Record        :
 * V1.0, 2021-11-13, Summer: Created file
 */

/********************************************************************************
* Header Definition
********************************************************************************/
#include <Myproject.h>


/********************************************************************************
* Macro & Structure Definition
*******************************************************************************/
/* An array of Digital Input functions handlers which associates function codes with INMODE. */
pxInModeHandler        pxInModeHandlers[INMODE_HANDLERS_MAX] = {
    eInModeIdle,             // INMODE_IDLE,                 // do nothing
    eInModeEnable,	         // INMODE_ENABLE,               // enable motor
    eInModeClearFault,       // INMODE_CLEARFAULT,           // clear fault
    eInModeEmergencyStop,    // INMODE_EMERGENCYSTOP,        // Emergency stop, activates Active Disable
    eInModeStopOnInput,      // INMODE_STOPONINPUT,          // decelerate to velocity zero
    eInModeHomeCommand,      // INMODE_HOMECOMMAND,          // home begin
    eInModePosiLimitSwitch,  // INMODE_POSILIMITSWITCH       // home Positive Limit Switch
    eInModeNegaLimitSwitch,  // INMODE_NEGALIMITSWITCH       // home Negative Limit Switch
    eInModeHomeSwitch,       // INMODE_HOMESWITCH,           // home Switch
    eInModeGainSwitch,       // INMODE_GainSWITCH,           // gain Switch
    eInModeOpModeChange1,    // INMODE_OPMODECHANGE1,        // Operation mode change while drive enabled 1
	eInModeOpModeChange2	 // INMODE_OPMODECHANGE2,        // Operation mode change while drive enabled 2
};


/********************************************************************************
* Internal Routine Prototypes
********************************************************************************/
/*---------------------------------------------------------------------------*/
/* Name		:	void UpdateDigitalIO(void)
/* Input	:	NO
/* Output	:	NO
/* Description:	Update Digital IO.
/*---------------------------------------------------------------------------*/
void UpdateDigitalIO(void)
{
    uint8  i, DigInput = 0;
    uint16  DigOutput = 0, DigInEn = 0;;
    uint8  *pMode = (uint8*)&usSRegHoldBuf[INMODE12];
    uint8 DigInArray[DIGITAL_INPUT_MAX];
    

#if (DIGITAL_INPUT_MAX >= 1)
    DigInArray[0] = readbit_csr(IN1_GPIO, IN1_PIN);
#endif
#if (DIGITAL_INPUT_MAX >= 2)
    DigInArray[1] = readbit_csr(IN2_GPIO, IN2_PIN);
#endif
#if (DIGITAL_INPUT_MAX >= 3)
    DigInArray[2] = readbit_csr(IN3_GPIO, IN3_PIN);
#endif
#if (DIGITAL_INPUT_MAX >= 4)
    DigInArray[3] = readbit_csr(IN4_GPIO, IN4_PIN);
#endif
#if (DIGITAL_INPUT_MAX >= 5)
    DigInArray[4] = readbit_csr(IN5_GPIO, IN5_PIN);
#endif
#if (DIGITAL_INPUT_MAX >= 6)
    DigInArray[5] = readbit_csr(IN6_GPIO, IN6_PIN);
#endif
#if (DIGITAL_INPUT_MAX >= 7)
    DigInArray[6] = readbit_csr(IN7_GPIO, IN7_PIN);
#endif
#if (DIGITAL_INPUT_MAX >= 8)
    DigInArray[7] = readbit_csr(IN8_GPIO, IN8_PIN);
#endif

    /* ------ Digital Input ------ */
    for( i = 0; i < DIGITAL_INPUT_MAX; i++ )
    {
        if(!GetReg(usSRegHoldBuf[DIGINVIRTUALSWITCH], (1 << i)))    // read IO status
        {
            SetReg(DigInput, (1 << i), (DigInArray[i] << i));
        }
        else
        {
        	SetReg(DigInput, (1 << i), usSRegHoldBuf[DIGINVIRTUAL]);
        }      
    }
    usSRegInBuf[DIGITALINPUT] = (DigInput ^ usSRegHoldBuf[DIGINOUTINV]) & 0xFF;

    for( i = 0; i < DIGITAL_INPUT_MAX; i++ )
    {		
    	if (*pMode > 0 && *pMode < INMODE_HANDLERS_MAX)
    	{
    		SetReg(DigInEn, (1 << (*pMode - 1)), (1 << (*pMode - 1)));
    		if (((mcFocCtrl.DigitalInPre >> i) & 0x01) != ((DigInput >> i) & 0x01))
    		{
    			pxInModeHandlers[*pMode]((usSRegInBuf[DIGITALINPUT] >> i) & 0x01);
    		}	
    	}
        pMode++;
    }
    mcFocCtrl.DigitalInPre = DigInput;
    usSRegInBuf[DIGINSTAEN] = DigInEn;
    
    
    /* ------ Digital Output ------ */
    pMode = (uint8*)&usSRegHoldBuf[OUTMODE12];
    for( i = 0; i < DIGITAL_OUTPUT_MAX; i++ )
    {
        if(*pMode > 0 && *pMode < OUTMODE_HANDLERS_MAX)
            SetReg(DigOutput, (1 << i), (((usSRegInBuf[DRIVESTATUS] >> (*pMode - 1)) & 0x01) << i));
        else
            SetReg(DigOutput, (1 << i), 0);
        pMode++;
    }
    usSRegInBuf[DIGITALOUTPUT] = DigOutput ^ (usSRegHoldBuf[DIGINOUTINV] >> 8);
    
    // output to pin
#if (DIGITAL_OUTPUT_MAX >= 1)
    if(usSRegInBuf[DIGITALOUTPUT] & 0x01)
    	set_csr(OUT1_GPIO, OUT1_PIN);
    else
    	clr_csr(OUT1_GPIO, OUT1_PIN);
#endif
 
#if (DIGITAL_OUTPUT_MAX >= 2)
    if (usSRegInBuf[DIGITALOUTPUT] & 0x02)
    	set_csr(OUT2_GPIO, OUT2_PIN);
    else
    	clr_csr(OUT2_GPIO, OUT2_PIN);
#endif
    
#if (DIGITAL_OUTPUT_MAX >= 3)
    if (usSRegInBuf[DIGITALOUTPUT] & 0x04)
    	set_csr(OUT3_GPIO, OUT3_PIN);
    else
    	clr_csr(OUT3_GPIO, OUT3_PIN);
#endif

#if (DIGITAL_OUTPUT_MAX >= 4)
    if (usSRegInBuf[DIGITALOUTPUT] & 0x08)
    	set_csr(OUT4_GPIO, OUT4_PIN);
    else
    	clr_csr(OUT4_GPIO, OUT4_PIN);
#endif
    
#if (DIGITAL_OUTPUT_MAX >= 5)
    if (usSRegInBuf[DIGITALOUTPUT] & 0x10)
    	set_csr(OUT5_GPIO, OUT5_PIN);
    else
    	clr_csr(OUT5_GPIO, OUT5_PIN);
#endif

#if (DIGITAL_OUTPUT_MAX >= 6)
    if (usSRegInBuf[DIGITALOUTPUT] & 0x20)
    	set_csr(OUT6_GPIO, OUT6_PIN);
    else
    	clr_csr(OUT6_GPIO, OUT6_PIN);
#endif
}



/*---------------------------------------------------------------------------*/
/* Name		:	void eInModeIdle(uint8 DigInput)
/* Input	:	Digital Input - IO_HIGH or IO_LOW.
/* Output	:	NO
/* Description:	do nothing.
/*---------------------------------------------------------------------------*/
void eInModeIdle(uint8 DigInput)
{
    // do nothing
}


/*---------------------------------------------------------------------------*/
/* Name		:	void eInModeEnable(uint8 DigInput)
/* Input	:	Digital Input - IO_HIGH or IO_LOW.
/* Output	:	NO
/* Description:	enable motor.
/*---------------------------------------------------------------------------*/
void eInModeEnable(uint8 DigInput)
{
    if(DigInput == IO_HIGH)
        SetBit(usSRegInBuf[DIGINSTATUS], INSTATUS_ENABLE);
    else
        ClrBit(usSRegInBuf[DIGINSTATUS], INSTATUS_ENABLE);
}


/*---------------------------------------------------------------------------*/
/* Name		:	void eInModeClearFault(uint8 DigInput)
/* Input	:	Digital Input - IO_HIGH or IO_LOW.
/* Output	:	NO
/* Description:	clear fault
/*---------------------------------------------------------------------------*/
void eInModeClearFault(uint8 DigInput)
{
    if(DigInput == IO_HIGH)
    	SetBit(usSRegInBuf[DIGINSTATUS], INSTATUS_CLEARFAULT);
    else
    	ClrBit(usSRegInBuf[DIGINSTATUS], INSTATUS_CLEARFAULT);
}


/*---------------------------------------------------------------------------*/
/* Name		:	void eInModeEmergencyStop(uint8 DigInput)
/* Input	:	Digital Input - IO_HIGH or IO_LOW.
/* Output	:	NO
/* Description:	Emergency stop, activates Active Disable.
/*---------------------------------------------------------------------------*/
void eInModeEmergencyStop(uint8 DigInput)
{
    if(DigInput == IO_HIGH)
    {   
    	SetBit(usSRegInBuf[DIGINSTATUS], INSTATUS_EMERGENCYSTOP);
    }
    else
    	ClrBit(usSRegInBuf[DIGINSTATUS], INSTATUS_EMERGENCYSTOP);
}


/*---------------------------------------------------------------------------*/
/* Name		:	void eInModeStopOnInput(uint8 DigInput)
/* Input	:	Digital Input - IO_HIGH or IO_LOW.
/* Output	:	NO
/* Description:	decelerate to velocity zero.
/*---------------------------------------------------------------------------*/
void eInModeStopOnInput(uint8 DigInput)
{
    if(DigInput == IO_HIGH)
    	SetBit(usSRegInBuf[DIGINSTATUS], INSTATUS_STOPONINPUT);
    else
    	ClrBit(usSRegInBuf[DIGINSTATUS], INSTATUS_STOPONINPUT);
}


/*---------------------------------------------------------------------------*/
/* Name		:	void eInModeHomeCommand(uint8 DigInput)
/* Input	:	Digital Input - IO_HIGH or IO_LOW.
/* Output	:	NO
/* Description:	home begin.
/*---------------------------------------------------------------------------*/
void eInModeHomeCommand(uint8 DigInput)
{
    if(DigInput == IO_HIGH)
    	SetBit(usSRegInBuf[DIGINSTATUS], INSTATUS_HOMECOMMAND);
    else
    	ClrBit(usSRegInBuf[DIGINSTATUS], INSTATUS_HOMECOMMAND);
}


/*---------------------------------------------------------------------------*/
/* Name		:	void eInModePosiLimitSwitch(uint8 DigInput)
/* Input	:	Digital Input - IO_HIGH or IO_LOW.
/* Output	:	NO
/* Description:	home positive limit switch.
/*---------------------------------------------------------------------------*/
void eInModePosiLimitSwitch(uint8 DigInput)
{
    if(DigInput == IO_HIGH)
    	SetBit(usSRegInBuf[DIGINSTATUS], INSTATUS_POSILIMITSWITCH);
    else
    	ClrBit(usSRegInBuf[DIGINSTATUS], INSTATUS_POSILIMITSWITCH);
}

/*---------------------------------------------------------------------------*/
/* Name		:	void eInModeNegaLimitSwitch(uint8 DigInput)
/* Input	:	Digital Input - IO_HIGH or IO_LOW.
/* Output	:	NO
/* Description:	home negative limit switch.
/*---------------------------------------------------------------------------*/
void eInModeNegaLimitSwitch(uint8 DigInput)
{
	if(DigInput == IO_HIGH)
		SetBit(usSRegInBuf[DIGINSTATUS], INSTATUS_NEGALIMITSWITCH);
	else
		ClrBit(usSRegInBuf[DIGINSTATUS], INSTATUS_NEGALIMITSWITCH);
}

/*---------------------------------------------------------------------------*/
/* Name		:	void eInModeNegaLimitSwitch(uint8 DigInput)
/* Input	:	Digital Input - IO_HIGH or IO_LOW.
/* Output	:	NO
/* Description:	home switch.
/*---------------------------------------------------------------------------*/
void eInModeHomeSwitch(uint8 DigInput)
{
	if(DigInput == IO_HIGH)
		SetBit(usSRegInBuf[DIGINSTATUS], INSTATUS_HOMESWITCH);
	else
		ClrBit(usSRegInBuf[DIGINSTATUS], INSTATUS_HOMESWITCH);
}

/*---------------------------------------------------------------------------*/
/* Name		:	void eInModeGainSwitch(uint8 DigInput)
/* Input	:	Digital Input - IO_HIGH or IO_LOW.
/* Output	:	NO
/* Description:	gain switch.
/*---------------------------------------------------------------------------*/
void eInModeGainSwitch(uint8 DigInput)
{
	if (DigInput == IO_HIGH)
		SetBit(usSRegInBuf[DIGINSTATUS], INSTATUS_GAINSWITCH);
	else
		ClrBit(usSRegInBuf[DIGINSTATUS], INSTATUS_GAINSWITCH);
}

/*---------------------------------------------------------------------------*/
/* Name		:	void eInModeOpModeChange(uint8 DigInput)
/* Input	:	Digital Input - IO_HIGH or IO_LOW.
/* Output	:	NO
/* Description:	Operation mode change while drive enabled.
/*---------------------------------------------------------------------------*/
void eInModeOpModeChange1(uint8 DigInput)
{
    if(DigInput == IO_HIGH)
    	SetBit(usSRegInBuf[DIGINSTATUS], INSTATUS_OPMODECHANGE1);
    else
    	ClrBit(usSRegInBuf[DIGINSTATUS], INSTATUS_OPMODECHANGE1);
}

void eInModeOpModeChange2(uint8 DigInput)
{
	if (DigInput == IO_HIGH)
		SetBit(usSRegInBuf[DIGINSTATUS], INSTATUS_OPMODECHANGE2);
	else
		ClrBit(usSRegInBuf[DIGINSTATUS], INSTATUS_OPMODECHANGE2);
}
