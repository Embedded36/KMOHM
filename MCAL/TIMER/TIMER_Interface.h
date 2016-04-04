/*
 * TIMER_Interface.h
 *
 *  Created on: Feb 2, 2016
 *      Author: KiMo
 */

#ifndef TIMER_INTERFACE_H_
#define TIMER_INTERFACE_H_

/*******************************************************/
/***************** Public Definitions  *****************/
/*******************************************************/

/*Comment!: Interrupt Macros for attaching user functions to external interrupts*/

/* Timer/Counter2 Compare Match */
#define TIMER2_COMP		7

/* Timer/Counter2 Overflow */
#define TIMER2_OVF		6

/* Timer/Counter1 Capture Event */
#define TIMER1_CAPT		5

/* Timer/Counter1 Compare Match A */
#define TIMER1_COMPA	4

/* Timer/Counter1 Compare Match B */
#define TIMER1_COMPB	3

/* Timer/Counter1 Overflow */
#define TIMER1_OVF		2

/* Timer/Counter0 Compare Match */
#define TIMER0_COMP		1

/* Timer/Counter0 Overflow */
#define TIMER0_OVF		0

/*******************************************************/
/***************** Public Functions ********************/
/*******************************************************/

/*Comment!: Initialization Function for Timer0*/
extern void TIMER0_voidInit(void);
/*Comment!: TIMER0 Enable */
extern void TIMER0_voidEnable(void);//need to be implemented
/*Comment!: TIMER0 Disable */
extern void TIMER0_voidDisable(void);//need to be implemented
/*Comment!: Set the interrupt function to run for a specific interrupt*/
u8 TIMER_u8AttachInt(u8 Copy_u8InterruptNum, void (*UserFunc)(void));
/*Comment!: Detach the interrupt function from a specific interrupt*/
u8 TIMER_u8DetachInt(u8 Copy_u8InterruptNum);
/*Comment!: Function to clear the timer0 overflow counter*/
void TIMER0_voidClearOverflowCount(void);
/*Comment!: Function to get the timer0 overflow counter*/
void TIMER0_u32GetOverflowCount(u32 *Copy_u32OverflowCount);


#endif /* TIMER_INTERFACE_H_ */
