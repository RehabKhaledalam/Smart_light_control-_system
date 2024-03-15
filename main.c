/*
 * main.c

 *
 *  Created on: Mar 4, 2024
 *      Author: Rehab Khald
 */

#include"MCAL/DIO/DIO_int.h"
#include <util/delay.h>
#include "LIB/BIT_Utils.h"
#include "LIB/STD_Types.h"

#include "HAL/LCD_cfg.h"
#include "HAL/LCD_int.h"

#include "HAL/KEY_PAD/KEY_PAD_interface.h"
#include "HAL/SEV_SEG/SEV_SEG_int.h"

#include "MCAL/ADC/ADC_interface.h"
#define NOTPRESSED_KEYPAD   'z'

int main(void)
{
	u16  Digital_value=0;
    u8 Pressedvalue;
	DIO_vidInit();
	LCD_voidInit();
	KEYPAD_VidInit();
	ADC_voidInit(ADC_REFERENCE_AVCC);


	// Set threshold value using keypad
	 u16 Threshold=0;
	 LCD_voidClear();
	 LCD_SetCursor(0,0);
	 LCD_voidWriteString(" put Threshold value =");
	 LCD_SetCursor(1,0);


	while (1)
	{
		//# is condation to getout from loop with out look in else
		 KEYPAD_vidGetPressed_Key(&Pressedvalue );
		if(Pressedvalue!= NOTPRESSED_KEYPAD )
		{

			if (Pressedvalue == '#')
			 break;

			            else
			            {

			    			Threshold =  Threshold * 10 + (Pressedvalue - '0');
			    	   	 LCD_voidWriteNumber(Threshold);


			            }
		}

	}

while(1)
{
	// Read LDR value using ADC

	ADC_voidGetDigitalValue(0,& Digital_value);

	// Calculate percentage of light

	 u16 lightPercentage = (Digital_value * (u32)100) / 1023;

	 // Display light percentage on LCD
	 LCD_voidClear();
	 LCD_SetCursor(0,0);
	 LCD_voidWriteString("The value of Light: ");
	 LCD_voidWriteNumber(lightPercentage);
	 LCD_voidWriteString("%");
	 // Adapt room light accordingly using LED

	 if (lightPercentage > Threshold)
	 {
        //led on
		 DIO_enuSetPinValue(DIO_u8_PORTA,  DIO_u8_PIN1, DIO_u8_HIGH	);
	 }
		 else
		 {
			 //led off
			 DIO_enuSetPinValue(DIO_u8_PORTA,  DIO_u8_PIN1, DIO_u8_LOW	);
	     }
	        _delay_ms(500); // Delay for stability the screen value
	     }

	     return 0;
	 }

















