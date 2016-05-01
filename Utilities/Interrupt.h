/*
 * Interrupt.h
 *
 *  Created on: Apr 24, 2016
 *      Author: KiMo
 */

#ifndef UTILITIES_INTERRUPT_H_
#define UTILITIES_INTERRUPT_H_

#define Enable_Global_INT()       __asm("SEI")

#define Disable_Global_INT()      __asm("CLI")

#endif /* UTILITIES_INTERRUPT_H_ */
