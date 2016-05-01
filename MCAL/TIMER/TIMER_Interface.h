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
/*Comment!: Function to Reset timer0 */
//void TIMER0_voidReset(void);
/*Comment!: Function to Set Output Compare Register for timer0 */
extern void TIMER0_voidSetOCR(u8 Copy_u8OCRValue);
/*Comment!: Function to return MicroSeconds since the MCU powered up*/
extern u32 TIMER0_u32Micros(void);
/*Comment!: Function to return MilliSeconds since the MCU powered up*/
extern u32 TIMER0_u32Millis(void);
/*Comment!: Blocking Delay, Max delay 2^32 MS*/
extern void TIMER0_voidDelayMS(u32 Copy_MS);
/*Comment!: Set the interrupt function to run for a specific interrupt*/
extern u8 TIMER_u8AttachInt(u8 Copy_u8InterruptNum, void (*UserFunc)(void));
/*Comment!: Detach the interrupt function from a specific interrupt*/
extern u8 TIMER_u8DetachInt(u8 Copy_u8InterruptNum);



#endif /* TIMER_INTERFACE_H_ */
