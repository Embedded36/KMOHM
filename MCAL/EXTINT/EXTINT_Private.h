/*
 * EXTINT_Private.h
 *
 *  Created on: Feb 2, 2016
 *      Author: KiMo
 */

#ifndef EXTINT_PRIVATE_H_
#define EXTINT_PRIVATE_H_

/*******************************************************/
/***************** Private Definitions  ****************/
/*******************************************************/

/*Comment!: External Interrupt Sense Control modes*/
#define EXTINT_LEVEL_LOW                0x00
#define EXTINT_EDGE_ANY                 0x01
#define EXTINT_EDGE_FALLING             0x02
#define EXTINT_EDGE_RISING              0x03

//for ExtInt2
//#define EXTINT2_EDGE_FALLING             0
//#define EXTINT2_EDGE_RISING              1

/*Comment!: ATMEGA32 EXTINTS Registers */
#define EXTINT_u8MCUCR			*((volatile u8*)(0x55)) //MCU Control Register, SET the operating mode for EXTINT0,1 >> bit1,0 , bit3,2
#define EXTINT_u8MCUCSR			*((volatile u8*)(0x54)) //MCU Control and Status Register, SET the operating mode for ExtInt2 >> bit6
#define EXTINT_u8GICR  			*((volatile u8*)(0x5B)) // General Interrupt Control Register, To Enable ExtInt >> Bit 7 – INT1, Bit 6 – INT0, Bit 5 – INT2
#define EXTINT_u8GIFR			*((volatile u8*)(0x5A)) //General Interrupt Flag Register, >> Bit 7 – INTF1, Bit 6 – INTF0, Bit 5 – INTF2

/*Comment!: Interrupt Macros for using inside attaching external interrupts*/
#define EXTINT0			0    
#define EXTINT1			1    
#define EXTINT2			2

/*Comment!: Number of External Interrupts */
#define EXTINT_NUM_INTERRUPTS   3

/* External Interrupt Request 0 */
#define INT0_vect			__vector_1

/* External Interrupt Request 1 */
#define INT1_vect			__vector_2

/* External Interrupt Request 2 */
#define INT2_vect			__vector_3

#define	EXTINT_DISABLE		0
#define	EXTINT_ENABLE 		1

/* MCUCR */
#define ISC11   3
#define ISC10   2
#define ISC01   1
#define ISC00   0

/* MCUCSR */
#define ISC2    6

/* GICR */
#define INT1    7
#define INT0    6
#define INT2    5

/*******************************************************/
/***************** Private Functions *******************/
/*******************************************************/

/*Comment!: Concatenate Function for TCCR1A Initial Value */
//#define CONC_HELPER_TCCR0(b7,b6,b54,b3,b210)		 0b##b7##b6##b54##b3##b210
//#define	CONC_TCCR0(b7,b6,b54,b3,b210)				 CONC_HELPER_TCCR0(b7,b6,b54,b3,b210)
//#define	EXTINT_u8TCCR0_VALUE							 CONC_TCCR0(FOC0_VALUE,WGM00_VALUE,COM0_VALUE,WGM01_VALUE,EXTINT0_PRESCALE)

#define ISR(vector, ...) \
	void vector(void) __attribute__ ((signal,used,externally_visible)) __VA_ARGS__;\
	void vector(void)

#endif /* EXTINT_PRIVATE_H_ */  
