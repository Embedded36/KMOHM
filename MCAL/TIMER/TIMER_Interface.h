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


/*******************************************************/
/***************** Public Functions ********************/
/*******************************************************/

/*Comment!: Initialization Function for Timer0*/
extern void TIMER0_voidInit(void);

/*Comment!: Set the interrupt function to run for a specific interrupt*/
u8 TIMER_u8AttachInt(u8 Copy_InterruptNum, void (*UserFunc)(void));

/*Comment!: Detach the interrupt function from a specific interrupt*/
u8 TIMER_u8DetachInt(u8 Copy_InterruptNum);

/*Comment!: Function to clear the timer overflow counter*/
void TIMER0_voidClearOverflowCount(void);

/*Comment!: Function to get the timer overflow counter*/
u32 TIMER0_u32GetOverflowCount(void);


#endif /* TIMER_INTERFACE_H_ */
