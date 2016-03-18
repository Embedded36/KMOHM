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
#include "HAL\KEYPAD\KEYPAD_Interface.h"

//Stepper Configuration Pins
#define STEPPER_MOTOR_PIN1   	10
#define STEPPER_MOTOR_PIN2   	11
#define STEPPER_MOTOR_PIN3   	12
#define STEPPER_MOTOR_PIN4   	13

#define DELAY_FOR_STEPPER		5//5

#define STEPPER_STEP_A			1
#define STEPPER_STEP_B			2
#define STEPPER_STEP_C			3
#define STEPPER_STEP_D			4

#define	LEDMATRIX		HC595_u8NUM1

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

static const u8 Row_Num[] = { 1, 2, 4, 8, 16, 32, 64, 128 }; // Rows Number
static const u8 RL[2][8] = { { 0x9F, 0x9F, 0x9F, 0x9F, 0x9F, 0x9F, 0x81, 0x81 }, //L
		{ 0xFF, 0x87, 0xB7, 0x87, 0xAF, 0xB7, 0xBB, 0xBD } //R
};

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
	DIO_u8WritePinVal(DC_MOTOR_PIN1, DIO_u8HIGH);
	DIO_u8WritePinVal(DC_MOTOR_PIN2, DIO_u8HIGH);
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

void StepperOFF(void) {
	DIO_u8WritePinVal(STEPPER_MOTOR_PIN1, DIO_u8LOW);
	DIO_u8WritePinVal(STEPPER_MOTOR_PIN2, DIO_u8LOW);
	DIO_u8WritePinVal(STEPPER_MOTOR_PIN3, DIO_u8LOW);
	DIO_u8WritePinVal(STEPPER_MOTOR_PIN4, DIO_u8LOW);
}

void StepperRunning(u8 KeyValue, u8 MotorDirection) {
	static u8 Step = STEPPER_STEP_A; // 0,1,2,3
	static u16 DelayCounter = 0;
	switch (Step) {
	case STEPPER_STEP_A:
		DIO_u8WritePinVal(STEPPER_MOTOR_PIN1, DIO_u8HIGH);
		DIO_u8WritePinVal(STEPPER_MOTOR_PIN2, DIO_u8LOW);
		DIO_u8WritePinVal(STEPPER_MOTOR_PIN3, DIO_u8LOW);
		DIO_u8WritePinVal(STEPPER_MOTOR_PIN4, DIO_u8LOW);
		break;
	case STEPPER_STEP_B:
		DIO_u8WritePinVal(STEPPER_MOTOR_PIN2, DIO_u8HIGH);
		DIO_u8WritePinVal(STEPPER_MOTOR_PIN1, DIO_u8LOW);
		DIO_u8WritePinVal(STEPPER_MOTOR_PIN3, DIO_u8LOW);
		DIO_u8WritePinVal(STEPPER_MOTOR_PIN4, DIO_u8LOW);
		break;
	case STEPPER_STEP_C:
		DIO_u8WritePinVal(STEPPER_MOTOR_PIN3, DIO_u8HIGH);
		DIO_u8WritePinVal(STEPPER_MOTOR_PIN1, DIO_u8LOW);
		DIO_u8WritePinVal(STEPPER_MOTOR_PIN2, DIO_u8LOW);
		DIO_u8WritePinVal(STEPPER_MOTOR_PIN4, DIO_u8LOW);
		break;
	case STEPPER_STEP_D:
		DIO_u8WritePinVal(STEPPER_MOTOR_PIN4, DIO_u8HIGH);
		DIO_u8WritePinVal(STEPPER_MOTOR_PIN1, DIO_u8LOW);
		DIO_u8WritePinVal(STEPPER_MOTOR_PIN2, DIO_u8LOW);
		DIO_u8WritePinVal(STEPPER_MOTOR_PIN3, DIO_u8LOW);
		break;
	default:
		break;
	}
	DelayCounter++;
	switch (MotorDirection) {
	case RIGHT:
		if (DelayCounter > (DELAY_FOR_STEPPER * KeyValue)) {
			DelayCounter = 0;
			if (Step == STEPPER_STEP_D) {
				Step = STEPPER_STEP_A;
			} else {
				Step++;
			}
		}
		break;
	case LEFT:
		if (DelayCounter > (DELAY_FOR_STEPPER * KeyValue)) {
			DelayCounter = 0;
			if (Step == STEPPER_STEP_A) {
				Step = STEPPER_STEP_D;
			} else {
				Step--;
			}
		}
		break;
	default:
		break;
	}
}

int main(void) {
	u8 local_u8CurrentState = OFF_STATE; //initial state
	u8 local_u8OFF_Flag = FALSE; // Flag to OFF_STATE
	u8 local_u8CON_Flag = FALSE; // flag to CONTINUOUS_STATE
	u8 local_u8ON_CLICK_Flag = FALSE; // flag to ON_CLICK_STATE
	u16 Local_u16DelayCounter = 0; //Counter to adjust the delay

	u8 Local_u8SwitchValue; //To store the switch value
	u8 local_u8Switch_Flag = FALSE; //flag to run the SW in the single mode

	u8 local_u8DCMotorDirection = RIGHT;	//initial DC direction
	u8 local_u8StepperMotorDirection = RIGHT;//initial Stepper motor direction

	u8 Local_u8KeypadValue = 0; //Keypad Value
	u8 Previous_Value = 0; //Value to store the Keypad Previous Value

	DIO_voidInit();
	HC595_voidInit();
	TSW_voidInit();
	KEYPAD_voidInit();
	while (1) {
		switch (local_u8CurrentState) {
		case OFF_STATE:
			if (!local_u8OFF_Flag) {
				MotorOff();
				LedMatrixOff();
				local_u8OFF_Flag = TRUE;
			}
			TSW_u8CheckSwitch(TSW_u8NUM1, &Local_u8SwitchValue);
			if (Local_u8SwitchValue == TSW_u8PRESSED) {
				if ((local_u8Switch_Flag == FALSE)) {
					local_u8Switch_Flag = TRUE;
					local_u8CurrentState = CONTINUOUS_STATE;
					local_u8OFF_Flag = FALSE;
				}
			} else { //Local_u8SwitchValue == TSW_u8RELEASED
				if (local_u8Switch_Flag == TRUE) {
					local_u8Switch_Flag = FALSE;
				}
			}
			break;

		case CONTINUOUS_STATE:
//			if (!local_u8CON_Flag) {
				MotorMoving(local_u8DCMotorDirection);
//				local_u8CON_Flag = TRUE;
//			}
			TSW_u8CheckSwitch(TSW_u8NUM1, &Local_u8SwitchValue);
			if (Local_u8SwitchValue == TSW_u8PRESSED) {
				Local_u16DelayCounter++;
				if (Local_u16DelayCounter > DELAY_TIME_3SEC) {
					local_u8CurrentState = ON_CLICK_STATE;
					local_u8CON_Flag = FALSE;
				} else {
					if ((local_u8Switch_Flag == FALSE)) {
						local_u8Switch_Flag = TRUE;
						local_u8CurrentState = OFF_STATE;
						local_u8CON_Flag = FALSE;
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
//			if(!local_u8ON_CLICK_Flag){
			MotorMoving(local_u8DCMotorDirection);
//			local_u8ON_CLICK_Flag = TRUE;
//			}
			TSW_u8CheckSwitch(TSW_u8NUM1, &Local_u8SwitchValue);
			if (Local_u8SwitchValue == TSW_u8PRESSED) {
				//Do nothing!
			} else { //Local_u8SwitchValue == TSW_u8RELEASED
				Local_u16DelayCounter = 0;
				local_u8Switch_Flag = FALSE;
				local_u8ON_CLICK_Flag = FALSE;
				local_u8CurrentState = OFF_STATE;
				ChangeMotorDir(&local_u8DCMotorDirection);
			}
			break;
		default:
			break;
		}
		//read a key value from the KEYPAD then run the stepper motor on a specific speed regarding to the Key Value
		KEYPAD_u8Read(&Local_u8KeypadValue);
		//StepperRunning(1, local_u8StepperMotorDirection);
		switch(Local_u8KeypadValue){
		case 0:
			if (Previous_Value != 0) {
				StepperRunning(Previous_Value, local_u8StepperMotorDirection);
			}
			break;
		case 15:
			ChangeMotorDir(&local_u8StepperMotorDirection);
			break;
		case 16:
			StepperOFF();
			Previous_Value = 0;
			break;
		default:
			Previous_Value = Local_u8KeypadValue;
			StepperRunning(Previous_Value, local_u8StepperMotorDirection);
			break;
		}
	}
	return 0;
}
