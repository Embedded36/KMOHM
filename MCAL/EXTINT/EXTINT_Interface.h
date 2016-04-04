/*
 * EXTINT_Interface.h
 *
 *  Created on: Feb 2, 2016
 *      Author: KiMo
 */

#ifndef EXTINT_INTERFACE_H_
#define EXTINT_INTERFACE_H_

/*******************************************************/
/***************** Public Definitions  *****************/
/*******************************************************/

/*Comment!: Interrupt Macros for attaching user functions to external interrupts*/
#define EXTINT0			0
#define EXTINT1			1
#define EXTINT2			2

/*******************************************************/
/***************** Public Functions ********************/
/*******************************************************/

/*Comment!: Initialization Function for EXTINTs*/
extern void EXTINT_voidInit(void);
/*Comment!: EXTINT0 Enable */
extern u8 EXTINT_voidEnable(u8 Copy_ExtInterrupt);
/*Comment!: SPI Disable */
extern u8 EXTINT_voidDisable(u8 Copy_ExtInterrupt);
/* EXTINT_u8AttachInt and EXTINT_u8DetachInt commands
              These functions allow the attachment (or detachment) of any user
              function to an external interrupt.  "Attaching" one of your own
              functions to an interrupt means that it will be called whenever
              that interrupt is triggered.  Example usage:

              EXTINT_u8AttachInt(EXTINT0, myInterruptHandler);
              EXTINT_u8DetachInt(EXTINT0);

              extintAttach causes the myInterruptHandler() to be attached, and therefore
              execute, whenever the corresponding interrupt occurs.  extintDetach removes
              the association and executes no user function when the interrupt occurs.
              myInterruptFunction must be defined with no return value and no arguments:

              void myInterruptHandler(void) { ... }*/
/*Comment!: "Attaching" one of your own functions to an interrupt means that it will be called whenever that interrupt is triggered*/
u8 EXTINT_u8AttachInt(u8 Copy_ExtInterrupt, void (*UserFunc)(void));
/*Comment!: Remove the association and executes no user function when the interrupt occurs*/
u8 EXTINT_u8DetachInt(u8 Copy_ExtInterrupt);

#endif /* EXTINT_INTERFACE_H_ */
