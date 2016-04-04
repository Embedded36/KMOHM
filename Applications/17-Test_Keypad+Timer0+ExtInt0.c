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
#include "..\HAL\KEYPAD\KEYPAD_Interface.h"

#define OneHalfSec	(976)
#define TenMSec		(10) //0.512 for each overflow

#define REDPIN			8
#define BLUEPIN			9
#define GREENPIN		10

#define REDLED			1
#define BLUELED			2
#define GREENLED		3

volatile u8 OnOffFlag_RedLed = FALSE;
volatile u8 OnOffFlag_BlueLed = FALSE;
volatile u8 OnOffFlag_GreenLed = FALSE;

volatile u8 HandelINTFlag = TRUE;
u32 Local_u32TimeforHandelINTFlag;

void ToggleRedLedStatus(void) {
	if (HandelINTFlag) {
		HandelINTFlag = FALSE;
		OnOffFlag_RedLed = !OnOffFlag_RedLed;
		TIMER0_u32GetOverflowCount(&Local_u32TimeforHandelINTFlag);
	}
	//EXTINT_voidDisable(EXTINT0);
}

void ToggleBlueLedStatus(void) {
	if (HandelINTFlag) {
		HandelINTFlag = FALSE;
		OnOffFlag_BlueLed = !OnOffFlag_BlueLed;
		TIMER0_u32GetOverflowCount(&Local_u32TimeforHandelINTFlag);
	}
	//EXTINT_voidDisable(EXTINT0);
}

void ToggleGreenLedStatus(void) {
	if (HandelINTFlag) {
		HandelINTFlag = FALSE;
		OnOffFlag_GreenLed = !OnOffFlag_GreenLed;
		TIMER0_u32GetOverflowCount(&Local_u32TimeforHandelINTFlag);
	}
	//EXTINT_voidDisable(EXTINT0);
}

int main(void) {
	//u8 Local_u8SwitchValue; //To store the switch value
	u8 Local_u8KeypadValue = 0; //Counter to adjust the delay
	u32 Local_u32TimeRightNow;
	u32 Local_u32TimeforREDLed = 0;
	u32 Local_u32TimeforBlueLed = 0;
	u32 Local_u32TimeforGreenLed = 0;

	u8 Local_u8ToggleFlagforREDLed = 0;
	u8 Local_u8ToggleFlagforBlueLed = 0;
	u8 Local_u8ToggleFlagforGreenLed = 0;

	//u8 Local_u8WhichLed = REDLED;
	DIO_voidInit();
	EXTINT_voidInit();
	__asm__("SEI");
	TIMER0_voidInit();
	KEYPAD_voidInit();
	EXTINT_u8AttachInt(EXTINT0, ToggleRedLedStatus);
	TIMER0_u32GetOverflowCount(&Local_u32TimeforHandelINTFlag);
	while (1) {
//		switch (Local_u8WhichLed) {
//		case REDLED:
		if (!OnOffFlag_RedLed) {
			DIO_u8WritePinVal(REDPIN, DIO_u8LOW);
		} else {
			TIMER0_u32GetOverflowCount(&Local_u32TimeRightNow);
			if (Local_u32TimeRightNow - Local_u32TimeforREDLed >= OneHalfSec) {
				//TIMER0_voidClearOverflowCount();
				TIMER0_u32GetOverflowCount(&Local_u32TimeforREDLed);
				Local_u8ToggleFlagforREDLed = !Local_u8ToggleFlagforREDLed;
				DIO_u8WritePinVal(REDPIN, Local_u8ToggleFlagforREDLed);
			}
		}
//			break;
//		case BLUELED:
		if (!OnOffFlag_BlueLed) {
			DIO_u8WritePinVal(BLUEPIN, DIO_u8LOW);
		} else {
			TIMER0_u32GetOverflowCount(&Local_u32TimeRightNow);
			if (Local_u32TimeRightNow - Local_u32TimeforBlueLed >= OneHalfSec) {
				//TIMER0_voidClearOverflowCount();
				TIMER0_u32GetOverflowCount(&Local_u32TimeforBlueLed);
				Local_u8ToggleFlagforBlueLed = !Local_u8ToggleFlagforBlueLed;
				DIO_u8WritePinVal(BLUEPIN, Local_u8ToggleFlagforBlueLed);
			}
		}
//			break;
//		case GREENLED:
		if (!OnOffFlag_GreenLed) {
			DIO_u8WritePinVal(GREENPIN, DIO_u8LOW);
		} else {
			TIMER0_u32GetOverflowCount(&Local_u32TimeRightNow);
			if (Local_u32TimeRightNow - Local_u32TimeforGreenLed >= OneHalfSec) {
				//TIMER0_voidClearOverflowCount();
				TIMER0_u32GetOverflowCount(&Local_u32TimeforGreenLed);
				Local_u8ToggleFlagforGreenLed = !Local_u8ToggleFlagforGreenLed;
				DIO_u8WritePinVal(GREENPIN, Local_u8ToggleFlagforGreenLed);
			}
		}
//			break;
//		default:
//			break;
//		}

		KEYPAD_u8Read(&Local_u8KeypadValue);
		switch (Local_u8KeypadValue) {
		case 1:
			EXTINT_u8AttachInt(EXTINT0, ToggleRedLedStatus);
			break;
		case 2:
			EXTINT_u8AttachInt(EXTINT0, ToggleBlueLedStatus);
			break;
		case 3:
			EXTINT_u8AttachInt(EXTINT0, ToggleGreenLedStatus);
			break;
		default:
			break;
		}

		if (!HandelINTFlag) {
			TIMER0_u32GetOverflowCount(&Local_u32TimeRightNow);
			if (Local_u32TimeRightNow - Local_u32TimeforHandelINTFlag >= TenMSec) {
				//EXTINT_voidEnable(EXTINT0);
				HandelINTFlag = TRUE;
			}
		}

	}
	return 0;
}
