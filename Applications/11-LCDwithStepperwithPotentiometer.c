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
#include "HAL\TSW\TSW_Interface.h"
#include "HAL\LCD\LCD_Interface.h"

//Stepper Configuration Pins
#define STEPPER_MOTOR_PIN1   	16
#define STEPPER_MOTOR_PIN2   	17
#define STEPPER_MOTOR_PIN3   	18
#define STEPPER_MOTOR_PIN4   	19

#define DELAY_FOR_STEPPER		10//5

#define STEPPER_STEP_0			0
#define STEPPER_STEP_A			1
#define STEPPER_STEP_B			2
#define STEPPER_STEP_C			3
#define STEPPER_STEP_D			4

#define STEPPER_SPEED1			1
#define STEPPER_SPEED2			3
#define STEPPER_SPEED3			5
#define STEPPER_SPEED4			7
#define STEPPER_SPEED5			10

#define RIGHT					0
#define LEFT					1
#define STOP					2

static const u8 MyNameInArabic[4][8] = { { 0x0, 0x7, 0x4, 0x4, 0x1c, 0x0, 0x0,
		0x0 }, //я
		{ 0x0, 0x0, 0x0, 0x2, 0x3, 0x4, 0x8, 0x10 }, //я—
		{ 0x0, 0x0, 0x2, 0x2, 0x1e, 0x0, 0x6, 0x0 }, //нг
		{ 0x0, 0x0, 0xe, 0xa, 0x1f, 0x10, 0x10, 0x10 } }; //нг

void StepperRunning(u8 KeyValue, u8 MotorDirection) {
	static u8 Step = STEPPER_STEP_A; // 0,1,2,3
	static u16 DelayCounter = 0;
	switch (MotorDirection) {
	case STOP:
		Step = STEPPER_STEP_0;
		DelayCounter = 0;
		break;
	case RIGHT:
		if (DelayCounter > (DELAY_FOR_STEPPER * KeyValue)) {
			DelayCounter = 0;
			if (Step == STEPPER_STEP_D || Step == STEPPER_STEP_0) {
				Step = STEPPER_STEP_A;
			} else {
				Step++;
			}
		}
		break;
	case LEFT:
		if (DelayCounter > (DELAY_FOR_STEPPER * KeyValue)) {
			DelayCounter = 0;
			if (Step == STEPPER_STEP_A || Step == STEPPER_STEP_0) {
				Step = STEPPER_STEP_D;
			} else {
				Step--;
			}
		}
		break;
	default:
		break;
	}
	switch (Step) {
	case STEPPER_STEP_0:
		DIO_u8WritePinVal(STEPPER_MOTOR_PIN1, DIO_u8LOW);
		DIO_u8WritePinVal(STEPPER_MOTOR_PIN2, DIO_u8LOW);
		DIO_u8WritePinVal(STEPPER_MOTOR_PIN3, DIO_u8LOW);
		DIO_u8WritePinVal(STEPPER_MOTOR_PIN4, DIO_u8LOW);
		break;
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
}

int main(void) {
	u8 Local_u8RowNumber; // using in creating custom char for LCD
	s8 Local_u8CharNumber;	// using in creating custom char for LCD
	u8 Local_u8SwitchValue; // to store the Switch Value
	u8 Local_u8SwitchFlag = FALSE; // to run the switch in the single mode
	u16 Local_u16ADCValue; // to store the ADC Value
	u16 Local_u16PrevADCValue = 2000; // to store the Previous ADC Value
	//u8 Local_u8PotienoValue[4]; // to store the value of the ADC as characters
	u8 Local_u8StepperDir = STOP;
	u8 Local_u8StepperSpeed;
	DIO_voidInit();
	ADC_voidInit();
	LCD_voidInit();
	//LCD_u8Write_String("KiMo");
	LCD_u8Write_Command(0x40);
	for (Local_u8CharNumber = 3; Local_u8CharNumber >= 0;
			Local_u8CharNumber--) {
		for (Local_u8RowNumber = 0; Local_u8RowNumber < 8;
				Local_u8RowNumber++) {
			LCD_u8Write_Data(
					MyNameInArabic[Local_u8CharNumber][Local_u8RowNumber]);
		}
	}
	ADC_voidEnable();
	while (1) {
		LCD_u8Write_Command(0x80); //go to First line and --0 is for 0th position
		TSW_u8CheckSwitch(TSW_u8NUM1, &Local_u8SwitchValue);
		if (Local_u8SwitchValue == TSW_u8PRESSED) {
			if (!Local_u8SwitchFlag) {
				//LCD_u8Write_Command(0x01);//CLEAR LCD
				// Print My Arabic Name
				LCD_u8Write_Data(0);
				LCD_u8Write_Data(1);
				LCD_u8Write_Data(2);
				LCD_u8Write_Data(3);
				LCD_u8Write_String("     ");
				LCD_u8Write_Command(0xC0); //go to Second line and --0 is for 0th position
				LCD_u8Write_String("            ");
				Local_u8SwitchFlag = TRUE;
				Local_u16PrevADCValue = 2000;
			}
		} else { //Local_u8SwitchValue == TSW_u8RELEASED
			Local_u8SwitchFlag = FALSE;
			ADC_u8ReadChannel(ADC_U8CH0, &Local_u16ADCValue);
			//ADC_u8ReadChannelFiltered(ADC_u8Ch0, &Local_u16ADCValue);
			if (Local_u16ADCValue == Local_u16PrevADCValue) {
			} else { //Local_u16ADCValue != Local_u16PrevADCValue
				Local_u16PrevADCValue = Local_u16ADCValue;
				LCD_u8Write_String("Dir:");
//				itoa(Local_u16ADCValue, Local_u8PotienoValue, 10);
//				LCD_u8Write_String(Local_u8PotienoValue);
				if (Local_u16ADCValue == 512) {
					LCD_u8Write_String("Stop ");
					LCD_u8Write_Command(0xC0); //go to Second line and --0 is for 0th position
					LCD_u8Write_String("Speed: Zero");
					Local_u8StepperDir = STOP;
					Local_u8StepperSpeed = STEPPER_SPEED5;
				} else if (Local_u16ADCValue < 512) {
					LCD_u8Write_String("Left ");
					LCD_u8Write_Command(0xC0); //go to Second line and --0 is for 0th position
					Local_u8StepperDir = LEFT;
					if (Local_u16ADCValue < 102) {
						LCD_u8Write_String("Speed: 1   ");
						Local_u8StepperSpeed = STEPPER_SPEED1;
					} else if (Local_u16ADCValue < 204) {
						LCD_u8Write_String("Speed: 2   ");
						Local_u8StepperSpeed = STEPPER_SPEED2;
					} else if (Local_u16ADCValue < 306) {
						LCD_u8Write_String("Speed: 3   ");
						Local_u8StepperSpeed = STEPPER_SPEED3;
					} else if (Local_u16ADCValue < 408) {
						LCD_u8Write_String("Speed: 4   ");
						Local_u8StepperSpeed = STEPPER_SPEED4;
					} else if (Local_u16ADCValue < 512) {
						LCD_u8Write_String("Speed: 5   ");
						Local_u8StepperSpeed = STEPPER_SPEED5;
					} else {
					}
				} else { // (Local_u16ADCValue > 512)
					LCD_u8Write_String("Right");
					LCD_u8Write_Command(0xC0); //go to Second line and --0 is for 0th position
					Local_u8StepperDir = RIGHT;
					if (Local_u16ADCValue < 614) {
						LCD_u8Write_String("Speed: 5   ");
						Local_u8StepperSpeed = STEPPER_SPEED5;
					} else if (Local_u16ADCValue < 716) {
						LCD_u8Write_String("Speed: 4   ");
						Local_u8StepperSpeed = STEPPER_SPEED4;
					} else if (Local_u16ADCValue < 818) {
						LCD_u8Write_String("Speed: 3   ");
						Local_u8StepperSpeed = STEPPER_SPEED3;
					} else if (Local_u16ADCValue < 920) {
						LCD_u8Write_String("Speed: 2   ");
						Local_u8StepperSpeed = STEPPER_SPEED2;
					} else if (Local_u16ADCValue <= 1023) {
						LCD_u8Write_String("Speed: 1   ");
						Local_u8StepperSpeed = STEPPER_SPEED1;
					} else {
					}
				}
			}
		}
		StepperRunning(Local_u8StepperSpeed, Local_u8StepperDir);
	}
	return 0;
}
