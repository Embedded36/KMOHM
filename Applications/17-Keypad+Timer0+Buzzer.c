/*
 main.c

 Created on: Feb 1, 2016
 Author: KiMo
 */

#include "..\Utilities\Types.h"
#include "..\Utilities\Delay.h"
#include "..\MCAL\DIO\DIO_Interface.h"
#include "..\MCAL\TIMER\TIMER_Interface.h"
#include "..\HAL\KEYPAD\KEYPAD_Interface.h"

#define REDPIN			8
#define FixedBuzzerTone	1
int main(void) {
	//u8 Local_u8SwitchValue; //To store the switch value
	u8 Local_u8KeypadValue = 0; //Counter to adjust the delay
	u32 Local_u32TimeRightNow;
	u32 Local_u32TimeforREDLed = 0;
	u32 Local_u32BuzzerTone = 10;
	u8 Local_u8ToggleFlagforREDLed = 0;

	//u8 Local_u8WhichLed = REDLED;
	DIO_voidInit();
	__asm__("SEI");
	TIMER0_voidInit();
	KEYPAD_voidInit();
	while (1) {
		TIMER0_u32GetOverflowCount(&Local_u32TimeRightNow);
		if (Local_u32TimeRightNow - Local_u32TimeforREDLed >= Local_u32BuzzerTone) {
			TIMER0_u32GetOverflowCount(&Local_u32TimeforREDLed);
			Local_u8ToggleFlagforREDLed = !Local_u8ToggleFlagforREDLed;
			DIO_u8WritePinVal(REDPIN, Local_u8ToggleFlagforREDLed);
		}

		KEYPAD_u8Read(&Local_u8KeypadValue);
		switch (Local_u8KeypadValue) {
		case 1 ... 16:
			Local_u32BuzzerTone = FixedBuzzerTone * Local_u8KeypadValue;
			break;
//		case 2:
//			Local_u32BuzzerTone = 20;
//			break;
//		case 3:
//			Local_u32BuzzerTone = 30;
//			break;
//		case 4:
//			Local_u32BuzzerTone = 40;
//			break;
//		case 5:
//			Local_u32BuzzerTone = 50;
//			break;
//		case 6:
//			Local_u32BuzzerTone = 60;
//			break;
//		case 7:
//			Local_u32BuzzerTone = 70;
//			break;
//		case 8:
//			Local_u32BuzzerTone = 80;
//			break;
//		case 9:
//			Local_u32BuzzerTone = 90;
//			break;
//		case 10:
//			Local_u32BuzzerTone = 100;
//			break;
//		case 11:
//			Local_u32BuzzerTone = 110;
//			break;
//		case 12:
//			Local_u32BuzzerTone = 120;
//			break;
//		case 13:
//			Local_u32BuzzerTone = 130;
//			break;
//		case 14:
//			Local_u32BuzzerTone = 140;
//			break;
//		case 15:
//			Local_u32BuzzerTone = 150;
//			break;
//		case 16:
//			Local_u32BuzzerTone = 160;
//			break;
		default:
			break;
		}
	}
	return 0;
}
