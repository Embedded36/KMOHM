/*
 main.c

 Created on: Feb 1, 2016
 Author: KiMo
 */
#include <stdlib.h>
#include "Utilities\Types.h"
#include "Utilities\Delay.h"
#include "MCAL\DIO\DIO_Interface.h"
#include "MCAL\ADC\ADC_Interface.h"
#include "MCAL\UART\UART_Interface.h"
#include "HAL\TSW\TSW_Interface.h"
#include "HAL\LCD\LCD_Interface.h"

#define ADC_VREF		5
#define ADC_RESOLUTION	10
#define ADC_STEP		((ADC_VREF)/(1024.00))
#define RES1		1

// Implementation of itoa()
void IntToASCI(s16 Num, u8* Buffer, u8 Base) {
	u8 StartIndex = 0;
	u8 LastIndex = 0;
	u8 TempValue;
	u8 isNegative = FALSE;

	/* Handle 0 explicitly, otherwise empty string is printed for 0 */
	if (Num != 0) {
		// In standard itoa(), negative numbers are handled only with
		// base 10. Otherwise numbers are considered unsigned.
		if (Num < 0 && Base == 10) {
			isNegative = TRUE;
			Num = -Num;
		}

		// Process individual digits
		while (Num != 0) {
			u8 Rem = Num % Base;
			Buffer[LastIndex++] = (Rem > 9) ? (Rem - 10) + 'A' : Rem + '0';
			Num = Num / Base;
		}

		// If number is negative, append '-'
		if (isNegative)
			Buffer[LastIndex++] = '-';

		Buffer[LastIndex] = '\0'; // Append string terminator

		// Reverse the string
		LastIndex -= 1;
		for (; StartIndex < LastIndex; StartIndex++, LastIndex--) {
			TempValue = Buffer[LastIndex];
			Buffer[LastIndex] = Buffer[StartIndex];
			Buffer[StartIndex] = TempValue;
		}
	} else {
		Buffer[LastIndex++] = '0';
		Buffer[LastIndex] = '\0';
	}
}

int main(void) {
	u8 Local_u8SwitchValue; // to store the Switch Value
	u8 Local_u8SwitchFlag = FALSE; // to run the switch in the single mode

	u16 Local_u16ADCValue; // to store the ADC Value
	u16 Local_u16PrevADCValue = 2000; // to store the Previous ADC Value
	f32 Local_f32VoltageValue;
	u8 Local_u8ResValue;
	u8 Local_u8Buffer[5]; // to store the Volt value as characters

	DIO_voidInit();
	ADC_voidInit();
	ADC_voidEnable();
	UART_voidInit();
	LCD_voidInit();
	LCD_u8Write_String("Resistor:");
	//LCD_u8Write_Command(0x80); //go to First line and --0 is for 0th position

	while (1) {
		//ADC_u8ReadChannel(ADC_u8CH7, &Local_u16ADCValue);
		ADC_u8ReadChannelFiltered(ADC_u8CH0, &Local_u16ADCValue);
		if (Local_u16ADCValue == Local_u16PrevADCValue) {
		} else { //Local_u16ADCValue != Local_u16PrevADCValue
			Local_u16PrevADCValue = Local_u16ADCValue;
			Local_f32VoltageValue = ADC_STEP * Local_u16ADCValue;
			Local_u8ResValue = (( ADC_VREF / Local_f32VoltageValue) - 1) * RES1;
			IntToASCI(Local_u8ResValue, Local_u8Buffer, 10);
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
			UART_u8TransmitString("KIMO\n");
		}
	}
	return 0;
}
