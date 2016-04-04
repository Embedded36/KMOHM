/*
 * TIMER_Prog.c
 *
 *  Created on: Feb 2, 2016
 *      Author: KiMo
 */

#include "../../Utilities\Types.h"
#include "TIMER_Config.h"
#include "TIMER_Interface.h"
#include "TIMER_Private.h"

/*******************************************************/
/***************** Global Variables ********************/
/*******************************************************/

typedef void (*voidFuncPtr)(void);
static volatile voidFuncPtr Timer_IntFunc[TIMER_NUM_INTERRUPTS];

static volatile u32 Timer0_u32OverFlowNum;

/*******************************************************/
/***************** Public Functions ********************/
/*******************************************************/

/*Comment!: Initialization Function for Timer0*/
extern void TIMER0_voidInit(void) {
	TIMER_u8TCCR0 = TIMER_u8TCCR0_VALUE; //set up timer with selected prescaler
	TIMER_u8TCNT0 = 0x00; // // initialize counter
#if (TIMER_u8TIMSK_VALUE !=0b00000000)
	__asm__("SEI");
	TIMER_u8TIMSK = TIMER_u8TIMSK_VALUE; //// enable overflow interrupt
#endif
	return;
}

/*Comment!: Set the interrupt function to run for a specific interrupt*/
u8 TIMER_u8AttachInt(u8 Copy_u8InterruptNum, void (*UserFunc)(void)) {
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
u8 TIMER_u8DetachInt(u8 Copy_u8InterruptNum) {
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

/*Comment!: Function to clear the timer overflow counter*/
void TIMER0_voidClearOverflowCount(void) {
	// clear the timer overflow counter
	Timer0_u32OverFlowNum = 0; //
}

/*Comment!: Function to get the timer overflow counter*/
void TIMER0_u32GetOverflowCount(u32 *Copy_u32OverflowCount) {
	// return the current timer overflow count
	*Copy_u32OverflowCount = Timer0_u32OverFlowNum;
}

/*Comment!: ISR for Timer/Counter0 Overflow*/
ISR(TIMER0_OVF_vect) {
	Timer0_u32OverFlowNum++; // increment low-order counter
	// if a user function is defined, execute it too
	if (Timer_IntFunc[TIMER0_OVF])	Timer_IntFunc[TIMER0_OVF]();
}
