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
#include "..\MCAL\ADC\ADC_Interface.h"
#include "..\MCAL\TIMER\TIMER_Interface.h"
#include <avr/io.h>

#define Timer0_Prescaller	1UL
#define Timefor38KHzInuS	((1000UL/38UL)*(clockCyclesPerMicrosecond)/(Timer0_Prescaller))

u8 OnTime = 25*Timefor38KHzInuS/100;
//u8 OffTime = Timefor38KHzInuS - OnTime;
u8 OffTime = 79;

u8 flag = TRUE;

void PWM38KHz(void){
	if(flag){TIMER0_voidSetOCR(OnTime);}
	else{TIMER0_voidSetOCR(OffTime);}
	PORTB ^= (1 << 3);    // toggles the led
	flag =!flag;
}

int main(void) {
	u16 Local_u16ADCValue;
	u16 Local_u16ADCValueP;
	u8 percentvalue;
	//DIO_voidInit();
	DDRB |= (1 << 3);
	ADC_voidInit();
	TIMER0_voidSetOCR(OffTime);
	TIMER_u8AttachInt(TIMER0_COMP, PWM38KHz);
	TIMER0_voidInit();
	Enable_Global_INT(); // enable global interrupt
	while (1) {
//		ADC_u8ReadChannel(ADC_u8CH0, &Local_u16ADCValue);
//		if (Local_u16ADCValue != Local_u16ADCValueP) {
//			percentvalue = Local_u16ADCValue/1023.00 * 100 ;
//			OnTime = percentvalue*Timefor38KHzInuS/100;
//			OffTime = Timefor38KHzInuS - OnTime;
//			Local_u16ADCValueP = Local_u16ADCValue;
//		}
	}
	return 0;
}

//#include <avr/io.h>
//#include <avr/interrupt.h>
//
////256 count = 64 us >> 4 count for each us so we need 4*13 = 52 for 13us
//
//unsigned char flag = 0;
//// initialize timer, interrupt and variable
//void timer0_init() {
//	// set up timer with prescaler = 1
//	TCCR0 |= (1 << CS00);
//
//	// initialize counter
//	TCNT0=0x00;
//	OCR0 = 78;
//
//	// enable overflow interrupt
//	TIMSK |= (1 << OCIE0);
//
//	// enable global interrupts
//	sei();
//}
//
//// TIMER0 overflow interrupt service routine
//// called whenever TCNT0 overflows
//ISR(TIMER0_COMP_vect) {
//	// keep a track of number of overflows
//	//tot_overflow++;
//	PORTB ^= (1 << 3);    // toggles the led
//	TCNT0 = 0x00;
//	if (flag)
//		OCR0 = 16;//26-10;
//	else
//		OCR0 = 50;//78-10;
//}
//
//int main(void) {
//	// connect led to pin PB0
//	DDRB |= (1 << 3);
//
//	// initialize timer
//	timer0_init();
//
//	// loop forever
//	while (1) {
//	}
//}
