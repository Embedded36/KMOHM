/*
 main.c

 Created on: Feb 1, 2016
 Author: KiMo
 */

#include "..\Utilities\Types.h"
#include "..\Utilities\Delay.h"
#include "..\MCAL\DIO\DIO_Interface.h"
#include "..\MCAL\TIMER\TIMER_Interface.h"
#include "..\MCAL\EXTINT\EXTINT_Interface.h"
//#include "..\HAL\TSW\TSW_Interface.h"
#include "..\HAL\KEYPAD\KEYPAD_Interface.h"

#define OneHalfSec	(976)

#define REDPIN		8
#define BLUEPIN		9
#define GREENPIN	10

#define REDLED			1
#define BLUELED			2
#define GREENLED		3

volatile u8 OnOffFlag = 0;

void ToggleLedStatus(void) {
	//__asm__("CLI");
	OnOffFlag = !OnOffFlag;
	//__asm__("SEI");
}

int main(void) {
	//u8 Local_u8SwitchValue; //To store the switch value
	u8 Local_u8KeypadValue = 0; //Counter to adjust the delay
	u32 Local_u32Timer0OverFlowNum;
	u8 Local_u8LEDONOFF = 0;
	u8 Local_u8WhichLed = REDLED;
	DIO_voidInit();
	EXTINT_voidInit();
	__asm__("SEI");
	TIMER0_voidInit();
	KEYPAD_voidInit();
	EXTINT_u8AttachInt(EXTINT0, ToggleLedStatus);
	while (1) {
		switch (Local_u8WhichLed) {
		case REDLED:
			if (!OnOffFlag) {
				DIO_u8WritePinVal(REDPIN, DIO_u8LOW);
			} else {
				Local_u32Timer0OverFlowNum = TIMER0_u32GetOverflowCount();
				if (Local_u32Timer0OverFlowNum >= OneHalfSec) {
					TIMER0_voidClearOverflowCount();
					Local_u8LEDONOFF = !Local_u8LEDONOFF;
					DIO_u8WritePinVal(REDPIN, Local_u8LEDONOFF);
				}
			}
			break;
		case BLUELED:
			if (!OnOffFlag) {
				DIO_u8WritePinVal(BLUEPIN, DIO_u8LOW);
			} else {
				Local_u32Timer0OverFlowNum = TIMER0_u32GetOverflowCount();
				if (Local_u32Timer0OverFlowNum >= OneHalfSec) {
					TIMER0_voidClearOverflowCount();
					Local_u8LEDONOFF = !Local_u8LEDONOFF;
					DIO_u8WritePinVal(BLUEPIN, Local_u8LEDONOFF);
				}
			}
			break;
		case GREENLED:
			if (!OnOffFlag) {
				DIO_u8WritePinVal(GREENPIN, DIO_u8LOW);
			} else {
				Local_u32Timer0OverFlowNum = TIMER0_u32GetOverflowCount();
				if (Local_u32Timer0OverFlowNum >= OneHalfSec) {
					TIMER0_voidClearOverflowCount();
					Local_u8LEDONOFF = !Local_u8LEDONOFF;
					DIO_u8WritePinVal(GREENPIN, Local_u8LEDONOFF);
				}
			}
			break;
		default: break;
		}

		KEYPAD_u8Read(&Local_u8KeypadValue);
		switch (Local_u8KeypadValue) {
		case 1:
			Local_u8WhichLed = REDLED;
			break;
		case 2:
			Local_u8WhichLed = BLUELED;
			break;
		case 3:
			Local_u8WhichLed = GREENLED;
			break;
		default:
			break;
		}
	}
	//TSW_u8CheckSwitch(TSW_u8NUM1, &Local_u8SwitchValue);
	return 0;
}
