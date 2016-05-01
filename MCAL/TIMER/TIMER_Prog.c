/*
 * TIMER_Prog.c
 *
 *  Created on: Feb 2, 2016
 *      Author: KiMo
 */

#include "..\..\Utilities\Types.h"
#include "..\..\Utilities\Interrupt.h"
#include "TIMER_Config.h"
#include "TIMER_Private.h"
#include "TIMER_Interface.h"

/*******************************************************/
/***************** Global Variables ********************/
/*******************************************************/

typedef void (*voidFuncPtr)(void); // pointer to function

static volatile voidFuncPtr Timer_IntFunc[TIMER_NUM_INTERRUPTS]; // array of pointer to function for Timer interrupts

// global variable to count the number of overflows
static volatile u32 Timer0_u32Overflow_Counts;
// global variable to count the number of system clocks
static volatile u32 Timer0_Clock_Cycles;
// global variable to count the number mS since the system powered on
static volatile u32 Timer0_Millis;

/*******************************************************/
/***************** Public Functions ********************/
/*******************************************************/

/*Comment!: Initialization Function for Timer0*/
extern void TIMER0_voidInit(void) {
	TIMER_u8TCNT0 = 0x00; // // initialize counter
#if (TIMER_u8TIMSK_VALUE !=0b00000000)
	TIMER_u8TIMSK = TIMER_u8TIMSK_VALUE; //// enable overflow interrupt
#endif
	TIMER_u8TCCR0 = TIMER_u8TCCR0_VALUE; //set up timer with selected prescaler
	return;
}

/*Comment!: TIMER0 Enable */
extern void TIMER0_voidEnable(void){}

/*Comment!: TIMER0 Disable */
extern void TIMER0_voidDisable(void){}

/*Comment!: Function to Set Output Compare Register for timer0 */
extern void TIMER0_voidSetOCR(u8 Copy_u8OCRValue){
	TIMER_u8OCR0 = Copy_u8OCRValue;
	return;
}

/*Comment!: Function to return MicroSeconds since the MCU powered up*/
extern u32 TIMER0_u32Micros(void){
	u32 Local_u32MicroSeconds;
	u8 Local_u8oldSREG = TIMER_u8SREG; // Store the Status Register value
	Disable_Global_INT(); //disable global interrupt
	Local_u32MicroSeconds = ((Timer0_u32Overflow_Counts << 8) + TIMER_u8TCNT0) *(Timer0_Prescale/clockCyclesPerMicrosecond);
	TIMER_u8SREG = Local_u8oldSREG; // Restore the Status Register value
	return Local_u32MicroSeconds; // Number of counters * time per each tick
}

/*Comment!: Function to return MilliSeconds since the MCU powered up*/
extern u32 TIMER0_u32Millis(void){
	u32 Local_u32MilliSeconds;
	u8 Local_u8oldSREG = TIMER_u8SREG; // Store the Status Register value
	// disable interrupts while we read timer0_millis or we might get an
	// inconsistent value (e.g. in the middle of the timer0_millis++)
	Disable_Global_INT(); //disable global interrupt
	Local_u32MilliSeconds = Timer0_Millis;
	TIMER_u8SREG = Local_u8oldSREG; // Restore the Status Register value
	return Local_u32MilliSeconds;
}

/*Comment!: Blocking Delay, Max delay 2^32 MS*/
extern void TIMER0_voidDelayMS(u32 Copy_MS) {
	u32 Local_u32StartTime = TIMER0_u32Millis();
	while (TIMER0_u32Millis() - Local_u32StartTime <= Copy_MS);
}

/*
void delayMicroseconds(u16 us) {
	// calling avrlib's delay_us() function with low values (e.g. 1 or
	// 2 microseconds) gives delays longer than desired.
	//delay_us(us);
	// for the 16 MHz clock on most Arduino boards

	// for a one-microsecond delay, simply return.  the overhead
	// of the function call yields a delay of approximately 1 1/8 us.
	if (--us == 0)
		return;

	// the following loop takes a quarter of a microsecond (4 cycles)
	// per iteration, so execute it four times for each microsecond of
	// delay requested.
	//us <<= 2;

	// account for the time taken in the preceeding commands.
	us -= 1;

	// busy wait
	__asm__ __volatile__ (
			"1: sbiw %0,1" "\n\t" // 2 cycles
			"brne 1b" : "=w" (us) : "0" (us)// 2 cycles
	);
}

void NonBlockingDelayms(u32 t) {
	iTimeout = millis() + t;
	return;
}

u8 Timeout(void) {
	return (iTimeout < millis());
}
*/

/*Comment!: Set the interrupt function to run for a specific interrupt*/
extern u8 TIMER_u8AttachInt(u8 Copy_u8InterruptNum, void (*UserFunc)(void)) {
	u8 Local_u8Status = u8OK;
	// make sure the interrupt number is within bounds
	if (Copy_u8InterruptNum < TIMER_NUM_INTERRUPTS) {
		// set the interrupt function to run
		// the supplied user's function
		Timer_IntFunc[Copy_u8InterruptNum] = UserFunc;
	} else {
		Local_u8Status = u8ERROR;
	}
	return Local_u8Status;
}

/*Comment!: Detach the interrupt function from a specific interrupt*/
extern u8 TIMER_u8DetachInt(u8 Copy_u8InterruptNum) {
	u8 Local_u8Status = u8OK;
	// make sure the interrupt number is within bounds
	if (Copy_u8InterruptNum < TIMER_NUM_INTERRUPTS) {
		// set the interrupt function to run nothing
		Timer_IntFunc[Copy_u8InterruptNum] = 0;
	} else {
		Local_u8Status = u8ERROR;
	}
	return Local_u8Status;
}

/*Comment!: ISR for Timer/Counter0 Overflow*/
ISR(TIMER0_OVF_vect) {
	Timer0_u32Overflow_Counts++; // increment low-order counter
	// timer 0 prescale factor is 1 and the timer overflows at 256
	Timer0_Clock_Cycles += Timer0_Prescale * 256UL;
	while (Timer0_Clock_Cycles > clockCyclesPerMillisecond) {
		Timer0_Clock_Cycles -= clockCyclesPerMillisecond;
		Timer0_Millis++;
	}
	// if a user function is defined, execute it too
	if (Timer_IntFunc[TIMER0_OVF])	Timer_IntFunc[TIMER0_OVF]();
}

/*Comment!: ISR for Timer/Counter0 Compare Match */
ISR(TIMER0_COMP_vect) {

	if (Timer_IntFunc[TIMER0_COMP])	Timer_IntFunc[TIMER0_COMP]();
}
