/*
 main.c


 Created on: April 25, 2016
 Author: KiMo

 We want to generate a PWM signal with a frequency of 38KHz and intial value Duty Cycle = 25%
 we can use OV interrupt or output compare match interrupt or just use PWM mode
 Here we will use OCM

 1-our system working on 4MHz
 2-calculate the time we need t = 1/38kHz = 26.3uS, On time = 26.3*0.25 = 6.6uS, Off time = 26.3-6.6 = 19.7uS
 3-OCR for on time = 6.6*4 = 26
 4-OCR for Off time = 19.7*4 = 79
 2-Set timer 0 to work on output compare match and enable Compare Match interrupt
 4-Take a ADC Reading and map it to 0->100
 5-Cal the Ontime & Offtime values according to the ADC value
 */

#include "..\Utilities\Types.h"
#include "..\Utilities\SystemClock.h"
#include "..\Utilities\Interrupt.h"
#include "..\MCAL\DIO\DIO_Interface.h"
#include "..\MCAL\TIMER_RTOS\TIMER_Interface.h"
#include "..\HAL\RTOS\RTOS_Interface.h"

void Task1(void);
void Task2(void);
void Task3(void);

u8 pin0val = 0;
u8 pin1val = 0;
u8 pin2val = 0;

int main(void) {
	DIO_voidInit();
	//RTOS_voidSetTask(Copy_u8TaskCounter,Copy_u8TaskPeriodicity,Task1);
	RTOS_voidSetTask(1, 2, Task1);
	RTOS_voidSetTask(1, 4, Task2);
	RTOS_voidSetTask(1, 3, Task3);
	/*Comment!: RTOS timer0 */
	RTOS_voidInit();
	/*Comment!: enable global interrupt*/
	Enable_Global_INT();
	while (1) {
	}
}

void Task1(void) {
	pin0val = !pin0val;
	DIO_u8WritePinVal(0, pin0val);

}

void Task2(void) {
	pin1val = !pin1val;
	DIO_u8WritePinVal(1, pin1val);
}

void Task3(void) {
	pin2val = !pin2val;
	DIO_u8WritePinVal(2, pin2val);
}
