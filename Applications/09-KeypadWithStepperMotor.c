/*
 main.c

 Created on: Feb 1, 2016
 Author: KiMo
 */

#include "Utilities\Types.h"
#include "Utilities\Delay.h"
#include "MCAL\DIO\DIO_Interface.h"
//#include "HAL\74HC595\74HC595_Interface.h"
#include "HAL\KEYPAD\KEYPAD_Interface.h"

#define STEPPER_MOTOR_PIN1   	10
#define STEPPER_MOTOR_PIN2   	11
#define STEPPER_MOTOR_PIN3   	12
#define STEPPER_MOTOR_PIN4   	13

#define DELAY_FOR_STEPPER		1

#define STEPPER_STEP_A			1
#define STEPPER_STEP_B			2
#define STEPPER_STEP_C			3
#define STEPPER_STEP_D			4

void StepperOFF(void) {
	DIO_u8WritePinVal(STEPPER_MOTOR_PIN1, DIO_u8LOW);
	DIO_u8WritePinVal(STEPPER_MOTOR_PIN2, DIO_u8LOW);
	DIO_u8WritePinVal(STEPPER_MOTOR_PIN3, DIO_u8LOW);
	DIO_u8WritePinVal(STEPPER_MOTOR_PIN4, DIO_u8LOW);
}

void StepperRunning(u8 KeyValue) {
	static u8 Step = STEPPER_STEP_A; // 0,1,2,3
	static u8 DelayCounter = 0;
	DelayCounter++;
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
	if (DelayCounter > (DELAY_FOR_STEPPER * KeyValue)) {
		DelayCounter = 0;
		if (Step == STEPPER_STEP_D)
			Step = STEPPER_STEP_A;
		else {
			Step++;
		}
	}
}

int main(void) {
	//u8 Local_u8SwitchValue; //To store the switch value
	u8 Local_u8KeypadValue = 0; //Counter to adjust the delay
	u8 Previous_Value = 0;
	DIO_voidInit();
	KEYPAD_voidInit();
	while (1) {
		KEYPAD_u8Read(&Local_u8KeypadValue);
		switch (Local_u8KeypadValue) {
		case 0:
			if(Previous_Value == 0) StepperOFF();
			else StepperRunning(Previous_Value);
			break; //0
//		case 1:
//			StepperRunning(Local_u8KeypadValue);
//			break; //1
//		case 2:
//			StepperRunning(Local_u8KeypadValue);
//			break; //2
//		case 3:
//			StepperRunning(Local_u8KeypadValue);
//			break; //3
//		case 4:
//			StepperRunning(Local_u8KeypadValue);
//			break; //4
//		case 5:
//			StepperRunning(Local_u8KeypadValue);
//			break; //5
//		case 6:
//			StepperRunning(Local_u8KeypadValue);
//			break; //6
//		case 7:
//			StepperRunning(Local_u8KeypadValue);
//			break; //7
//		case 8:
//			StepperRunning(Local_u8KeypadValue);
//			break; //8
//		case 9:
//			StepperRunning(Local_u8KeypadValue);
//			break; //9
//		case 10:
//			StepperRunning(Local_u8KeypadValue);
//			break; //10
//		case 11:
//			StepperRunning(Local_u8KeypadValue);
//			break; //11
//		case 12:
//			StepperRunning(Local_u8KeypadValue);
//			break; //12
//		case 13:
//			StepperRunning(Local_u8KeypadValue);
//			break; //13
//		case 14:
//			StepperRunning(Local_u8KeypadValue);
//			break; //14
//		case 15:
//			StepperRunning(Local_u8KeypadValue);
//			break; //15
		case 16:
			StepperOFF();
			Previous_Value = 0;
			break; //16
		default:
			Previous_Value = Local_u8KeypadValue;
			StepperRunning(Local_u8KeypadValue);
			break;
		}
	}
	return 0;
}
