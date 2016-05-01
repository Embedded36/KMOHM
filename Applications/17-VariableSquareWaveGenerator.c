/*
 main.c


 Created on: April 25, 2016
 Author: KiMo
 Prerequisite:
 1-We have to set the OC0 pin an Output pin
 2-Set timer 0 to work on output compare match and COM to toggle OC0
 3-Make sure you Disabled all Timers Interrupt or just disable Global Interrupt
 4-Take a ADC Reading and map it to 0->255
 5-Assign this value to OCR: O/P compare Register
 */



#include "..\Utilities\Types.h"
#include "..\Utilities\Interrupt.h"
#include "..\MCAL\DIO\DIO_Interface.h"
#include "..\MCAL\ADC\ADC_Interface.h"
#include "..\MCAL\TIMER\TIMER_Interface.h"
//#include "..\HAL\PotentioMeter\PotentioMeter_Interface.h"

int main(void) {
	//f32 Local_f32PotentioVal;
	u8 Local_u8OutputCompareValue;
	u16 Local_u16ADCValue;
	u16 Local_u16ADCValueP;
	DIO_voidInit();
	ADC_voidInit();
	TIMER0_voidInit();
	TIMER0_voidSetOCR(255);
	//TIMER_u8AttachInt(TIMER0_COMP, VariableSquareWave);
	//Enable_Global_INT();
	// enable global interrupt
	while (1) {
		//PotentioMeter_u8GetVoltageVal(POTENTIOMETER_u8NUM1, &Local_f32PotentioVal);
		ADC_u8ReadChannel(ADC_u8CH0, &Local_u16ADCValue);
		if (Local_u16ADCValue != Local_u16ADCValueP) {
			Local_u8OutputCompareValue = (u8)(Local_u16ADCValue >> 2);
			TIMER0_voidSetOCR(Local_u8OutputCompareValue);
			Local_u16ADCValueP = Local_u16ADCValue;
		}
	}
	return 0;
}
