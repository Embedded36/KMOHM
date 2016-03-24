/*
 main.c

 Created on: Feb 1, 2016
 Author: KiMo
 */

#include "Utilities\Types.h"
#include "Utilities\Delay.h"
#include "MCAL\DIO\DIO_Interface.h"
#include "HAL\74HC595\74HC595_Interface.h"
#include "HAL\TSW\TSW_Interface.h"

#define	LEDMATRIX		HC595_u8NUM1

static const u8 Row_Num[] = { 1, 2, 4, 8, 16, 32, 64, 128 }; // Rows Number
static const u8 RL[2][8] = { { 0x9F, 0x9F, 0x9F, 0x9F, 0x9F, 0x9F, 0x81, 0x81 }, //L
							{ 0xFF, 0x87, 0xB7, 0x87, 0xAF, 0xB7, 0xBB, 0xBD } //R
};
#define OFF_STATE			0
#define CONTINUOUS_STATE	1
#define ON_CLICK_STATE		2

#define DELAY_TIME_3SEC   	100

#define DC_MOTOR_PIN1   	8
#define DC_MOTOR_PIN2   	9


#define RIGHT	0
#define LEFT	1

#define PRINT_L   			0
#define PRINT_R  			1


void LedMatrixOff(void) {
	//Turn off all Leds
	HC595_u8WriteByte(LEDMATRIX, DIO_u8PORTHIGH);	//column
	HC595_u8WriteByte(LEDMATRIX, DIO_u8PORTLOW);	//row
	HC595_u8LatchPulse(LEDMATRIX);
}

void PrintOnLEDMatrix(u8 Copy_u8Charcter) {
	u8 Local_u8RowNumber; //Row Number ?
	for (Local_u8RowNumber = 0; Local_u8RowNumber < 8; Local_u8RowNumber++) {
		HC595_u8WriteByte(LEDMATRIX, RL[Copy_u8Charcter][Local_u8RowNumber]); //column
		HC595_u8WriteByte(LEDMATRIX, Row_Num[Local_u8RowNumber]); //row
		HC595_u8LatchPulse(LEDMATRIX);
	}
}

void MotorOff(void) {
	DIO_u8WritePinVal(DC_MOTOR_PIN1, DIO_u8LOW);
	DIO_u8WritePinVal(DC_MOTOR_PIN2, DIO_u8LOW);
}

void MotorLeft(void) {
	DIO_u8WritePinVal(DC_MOTOR_PIN1, DIO_u8HIGH);
	DIO_u8WritePinVal(DC_MOTOR_PIN2, DIO_u8LOW);
}

void MotorRight(void) {
	DIO_u8WritePinVal(DC_MOTOR_PIN1, DIO_u8LOW);
	DIO_u8WritePinVal(DC_MOTOR_PIN2, DIO_u8HIGH);
}

void MotorMoving(u8 MotorDirection) {
	if (MotorDirection == RIGHT) {
		MotorRight();
		PrintOnLEDMatrix(PRINT_R);
	} else { //MotorDirection == LEFT
		MotorLeft();
		PrintOnLEDMatrix(PRINT_L);
	}
}

void ChangeMotorDir(u8 *MotorDirection) {
	if (*MotorDirection == RIGHT) {
		*MotorDirection = LEFT;
	} else { //MotorDirection == LEFT
		*MotorDirection = RIGHT;
	}
}

int main(void) {
	u16 Local_u16DelayCounter = 0; //Counter to adjust the delay
	u8 Local_u8SwitchValue; //To store the switch value
	u8 local_u8Switch_Flag = FALSE; //flag to run the SW in the single mode
	u8 local_u8MotorDirection = RIGHT;	//initial direction
	u8 local_u8CurrentState = OFF_STATE; //initial state
	//u16 Local_u8KeypadValue = 0; //Counter to adjust the delay
	DIO_voidInit();
	HC595_voidInit();
	TSW_voidInit();
	//KEYPAD_voidInit();
	while (1) {
		//KEYPAD_u16Read(u16* Local_u8KeypadValue);
		//Local_u8KeypadValue=0x01;
		switch (local_u8CurrentState) {
		case OFF_STATE:
			MotorOff();
			LedMatrixOff();
			TSW_u8CheckSwitch(TSW_u8NUM1, &Local_u8SwitchValue);
			if (Local_u8SwitchValue == TSW_u8PRESSED) {
				//Local_u16DelayCounter++;
//				if (Local_u16DelayCounter > DELAY_TIME_3SEC) {
//					local_u8CurrentState = ON_CLICK_STATE;
//				} else {
					if ((local_u8Switch_Flag == FALSE)) {
						local_u8Switch_Flag = TRUE;
						local_u8CurrentState = CONTINUOUS_STATE;
//					}
				}
			} else { //Local_u8SwitchValue == TSW_u8RELEASED
				if (local_u8Switch_Flag == TRUE) {
					//Local_u16DelayCounter = 0;
					local_u8Switch_Flag = FALSE;
				}
			}
			break;

		case CONTINUOUS_STATE:
			MotorMoving(local_u8MotorDirection);
			TSW_u8CheckSwitch(TSW_u8NUM1, &Local_u8SwitchValue);
			if (Local_u8SwitchValue == TSW_u8PRESSED) {
				Local_u16DelayCounter++;
				if (Local_u16DelayCounter > DELAY_TIME_3SEC) {
					local_u8CurrentState = ON_CLICK_STATE;
				} else {
					if ((local_u8Switch_Flag == FALSE)) {
						local_u8Switch_Flag = TRUE;
						local_u8CurrentState = OFF_STATE;
					}
				}
			} else { //Local_u8SwitchValue == TSW_u8RELEASED
				if (local_u8Switch_Flag == TRUE) {
					Local_u16DelayCounter = 0;
					local_u8Switch_Flag = FALSE;
				}
			}
			break;

		case ON_CLICK_STATE:
			MotorMoving(local_u8MotorDirection);
			TSW_u8CheckSwitch(TSW_u8NUM1, &Local_u8SwitchValue);
			if (Local_u8SwitchValue == TSW_u8PRESSED) {
				//Do nothing!
			} else { //Local_u8SwitchValue == TSW_u8RELEASED
				Local_u16DelayCounter = 0;
				local_u8Switch_Flag = FALSE;
				local_u8CurrentState = OFF_STATE;
				ChangeMotorDir(&local_u8MotorDirection);
			}
			break;

		default:
			break;
		}
	}
	return 0;
}
