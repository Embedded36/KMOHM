/*
 main.c

 Created on: Feb 1, 2016
 Author: KiMo
 */
#include "Utilities\Types.h"
#include "Utilities\Delay.h"
#include "MCAL\DIO\DIO_Interface.h"
#include "MCAL\ADC\ADC_Interface.h"
#include "HAL\TSW\TSW_Interface.h"
#include "HAL\LCD\LCD_Interface.h"

#define ADC_VREF		5
#define ADC_RESOLUTION	10
#define ADC_STEP		((ADC_VREF)/(1024.00))

#define RELAYCONTROL	DIO_u8PIN19

void ftoa(u8 *buffer, f32 d, u8 precision) {

	u8 wholePart = (u8) d;

	// Deposit the whole part of the number.

	itoa(wholePart, buffer, 10);

	// Now work on the faction if we need one.

	if (precision > 0) {

		// We do, so locate the end of the string and insert
		// a decimal point.

		u8 *endOfString = buffer;
		while (*endOfString != '\0'){endOfString++;}
		*endOfString++ = '.';

		// Now work on the fraction, be sure to turn any negative
		// values positive.

		if (d < 0) {
			d *= -1;
			wholePart *= -1;
		}

		f32 fraction = d - wholePart;
		while (precision > 0) {

			// Multipleby ten and pull out the digit.

			fraction *= 10;
			wholePart = (u8) fraction;
			*endOfString++ = '0' + wholePart;

			// Update the fraction and move on to the
			// next digit.

			fraction -= wholePart;
			precision--;
		}

		// Terminate the string.

		*endOfString = '\0';
	}
}

void CalculateVlotage(u8 Copy_u8SwitchFlag, u16 Copy_u16ADCValue, f32 *Copy_f32VoltageValue) {

	if (!Copy_u8SwitchFlag) {
		*Copy_f32VoltageValue = ADC_STEP * Copy_u16ADCValue;
	} else {
		*Copy_f32VoltageValue = ADC_STEP * 3 * Copy_u16ADCValue;
	}
}

int main(void) {
	u8 Local_u8SwitchValue; // to store the Switch Value
	u8 Local_u8SwitchFlag = FALSE; // to run the switch in the single mode

	u16 Local_u16ADCValue; // to store the ADC Value
	u16 Local_u16PrevADCValue = 2000; // to store the Previous ADC Value
	f32 Local_f32VoltageValue;
	u8 Local_u8Buffer[5]; // to store the Volt value as characters

	DIO_voidInit();
	ADC_voidInit();
	ADC_voidEnable();
	LCD_voidInit();
	LCD_u8Write_String("Voltage:");
	//LCD_u8Write_Command(0x80); //go to First line and --0 is for 0th position
	while (1) {

		TSW_u8CheckSwitch(TSW_u8NUM1, &Local_u8SwitchValue);
		if (Local_u8SwitchValue == TSW_u8PRESSED) {
			if (!Local_u8SwitchFlag) {
				Local_u8SwitchFlag = TRUE;
				DIO_u8WritePinVal(RELAYCONTROL, DIO_u8HIGH);
			}

		} else { //Local_u8SwitchValue == TSW_u8RELEASED
			if (Local_u8SwitchFlag) {
				Local_u8SwitchFlag = FALSE;
				DIO_u8WritePinVal(RELAYCONTROL, DIO_u8LOW);
			}
		}
		//ADC_u8ReadChannel(ADC_u8CH7, &Local_u16ADCValue);
		ADC_u8ReadChannelFiltered(ADC_u8CH7, &Local_u16ADCValue);
		if (Local_u16ADCValue == Local_u16PrevADCValue) {
		} else { //Local_u16ADCValue != Local_u16PrevADCValue
			Local_u16PrevADCValue = Local_u16ADCValue;
			CalculateVlotage(Local_u8SwitchFlag, Local_u16ADCValue, &Local_f32VoltageValue);
			ftoa(Local_u8Buffer, Local_f32VoltageValue, 2);
			//Local_f32VoltageValue = Local_u16ADCValue * ADC_STEP;
//			Local_u8IntVoltageValue = Local_f32VoltageValue;
//			itoa(Local_u8IntVoltageValue, Local_u8PotienoValue, 10);
//			LCD_u8Write_Command(0xC0); //go to Second line and --0 is for 0th position
			//dtostrf(value, width, precision, char array)
			LCD_u8Write_Command(0xC0); //go to Second line and --0 is for 0th position
			LCD_u8Write_String(Local_u8Buffer);
			LCD_u8Write_String("  ");
//			LCD_u8Write_String(".");
//			Local_f32VoltageValue = Local_f32VoltageValue - Local_u8IntVoltageValue;
//			Local_u8IntVoltageValue = 100 * Local_f32VoltageValue;
//			itoa(Local_u8IntVoltageValue, Local_u8PotienoValue, 10);
//			LCD_u8Write_String(Local_u8PotienoValue);
		}
	}
	return 0;
}
