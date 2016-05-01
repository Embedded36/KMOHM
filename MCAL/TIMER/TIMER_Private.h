/*
 * TIMER_Private.h
 *
 *  Created on: Feb 2, 2016
 *      Author: KiMo
 */

#ifndef TIMER_PRIVATE_H_
#define TIMER_PRIVATE_H_

#include "..\..\Utilities\SystemClock.h"

/*******************************************************/
/***************** Private Definitions  ****************/
/*******************************************************/

#define Timer0_Prescale				(1UL)

/*Comment!: ATMEGA32 TIMERS Registers */
#define TIMER_u8SREG			*((volatile u8*)(0x5F))
#define TIMER_u8TIMSK			*((volatile u8*)(0x59))
/* Timer 0 */
#define TIMER_u8TCCR0			*((volatile u8*)(0x53))
#define TIMER_u8TCNT0  			*((volatile u8*)(0x52))
#define TIMER_u8OCR0			*((volatile u8*)(0x5C))
/* Timer 1 */
#define TIMER_u16ICR1    		*((volatile u16*)(0x46))
#define TIMER_u8ICR1L   		*((volatile u8*)(0x46))
#define TIMER_u8ICR1H   		*((volatile u8*)(0x47))
#define TIMER_u16OCR1B   		*((volatile u16*)(0x48))
#define TIMER_u8OCR1BL  		*((volatile u8*)(0x48))
#define TIMER_u8OCR1BH  		*((volatile u8*)(0x49))
#define TIMER_u16OCR1A   		*((volatile u16*)(0x4A))
#define TIMER_u8OCR1AL  		*((volatile u8*)(0x4A))
#define TIMER_u8OCR1AH  		*((volatile u8*)(0x4B))
#define TIMER_u16TCNT1   		*((volatile u16*)(0x4C))
#define TIMER_u8TCNT1L  		*((volatile u8*)(0x4C))
#define TIMER_u8TCNT1H  		*((volatile u8*)(0x4D))
#define TIMER_u8TCCR1B  		*((volatile u8*)(0x4E))
#define TIMER_u8TCCR1A  		*((volatile u8*)(0x4F))
/* Timer 2 */
#define TIMER_u8OCR2    		*((volatile u8*)(0x43))
#define TIMER_u8TCNT2   		*((volatile u8*)(0x44))
#define TIMER_u8TCCR2  			*((volatile u8*)(0x45))

/*Comment!: Prescaler Options*/
#define TIMER0_CLK_STOP                  000
#define TIMER0_CLK_DIV1                  001
#define TIMER0_CLK_DIV8                  010
#define TIMER0_CLK_DIV64                 011
#define TIMER0_CLK_DIV256                100
#define TIMER0_CLK_DIV1024               101
#define TIMER0_CLK_T0_FALL               110
#define TIMER0_CLK_T0_RISE               111

/*Comment!: Timer0 Operating Modes*/
#define TIMER0_NORMAL                  	00
#define TIMER0_PWM_PHASE_CORRECT       	01
#define TIMER0_CTC                     	10 //Timer on Compare Match
#define TIMER0_FAST_PWM                	11

/*Comment!: Compare Output Modes for Timer0*/
#define TIMER0_COM0                  	00
#define TIMER0_COM1    				   	01 //not in Phase Correct PWM Mode & Fast PWM Mode(1)
#define TIMER0_COM2    				   	10
#define TIMER0_COM3    				   	11

/*Comment!: Adjusting the value of Timer0 control register*/
#define FOC0_VALUE		0
#if (TIMER0_OPERATING_MODE==TIMER0_NORMAL)
	#define WGM01_VALUE	 0
	#define WGM00_VALUE	 0
	#if( (TIMER0_COMPARE_OUTPUT_MODE == TIMER0_COM0) || (TIMER0_COMPARE_OUTPUT_MODE == TIMER0_COM1) || (TIMER0_COMPARE_OUTPUT_MODE == TIMER0_COM2)  || (TIMER0_COMPARE_OUTPUT_MODE == TIMER0_COM3))
		#define COM0_VALUE	TIMER0_COMPARE_OUTPUT_MODE
	#else
		#warning "The default COMPARE_OUTPUT_MODE for Timer0 is Mode0 as you chose a wrong mode"
		#define COM0_VALUE	00
	#endif
	
#elif (TIMER0_OPERATING_MODE==TIMER0_PWM_PHASE_CORRECT)
	#define WGM01_VALUE	 0
	#define WGM00_VALUE	 1
	#if( (TIMER0_COMPARE_OUTPUT_MODE == TIMER0_COM0) || (TIMER0_COMPARE_OUTPUT_MODE == TIMER0_COM2)  || (TIMER0_COMPARE_OUTPUT_MODE == TIMER0_COM3))
		#define COM0_VALUE	TIMER0_COMPARE_OUTPUT_MODE
	#else
		#warning "The default COMPARE_OUTPUT_MODE for Timer0 is Mode0 as you chose a wrong mode"
		#define COM0_VALUE	00
	#endif
	
#elif (TIMER0_OPERATING_MODE==TIMER0_CTC)
	#define WGM01_VALUE	 1
	#define WGM00_VALUE	 0
	#if( (TIMER0_COMPARE_OUTPUT_MODE == TIMER0_COM0) || (TIMER0_COMPARE_OUTPUT_MODE == TIMER0_COM1) || (TIMER0_COMPARE_OUTPUT_MODE == TIMER0_COM2)  || (TIMER0_COMPARE_OUTPUT_MODE == TIMER0_COM3))
		#define COM0_VALUE	TIMER0_COMPARE_OUTPUT_MODE
	#else
		#warning "The default COMPARE_OUTPUT_MODE for Timer0 is Mode0 as you chose a wrong mode"
		#define COM0_VALUE	00
	#endif
	
#elif (TIMER0_OPERATING_MODE==TIMER0_FAST_PWM)	
	#define WGM01_VALUE	 1
	#define WGM00_VALUE	 1
	#if( (TIMER0_COMPARE_OUTPUT_MODE == TIMER0_COM0) || (TIMER0_COMPARE_OUTPUT_MODE == TIMER0_COM2)  || (TIMER0_COMPARE_OUTPUT_MODE == TIMER0_COM3))
		#define COM0_VALUE	TIMER0_COMPARE_OUTPUT_MODE
	#else
		#warning "The default COMPARE_OUTPUT_MODE for Timer0 is Mode0 as you chose a wrong mode"
		#define COM0_VALUE	00
	#endif
	
#else
	#warning "The default mode is Normal as you chose a wrong mode"
	#define WGM00_VALUE	 0	
	#define WGM01_VALUE	 0
	#if( (TIMER0_COMPARE_OUTPUT_MODE == TIMER0_COM0) || (TIMER0_COMPARE_OUTPUT_MODE == TIMER0_COM1) || (TIMER0_COMPARE_OUTPUT_MODE == TIMER0_COM2)  || (TIMER0_COMPARE_OUTPUT_MODE == TIMER0_COM3))
		#define COM0_VALUE	TIMER0_COMPARE_OUTPUT_MODE
	#else
		#warning "The default COMPARE_OUTPUT_MODE for Timer0 is Mode0 as you chose a wrong mode"
		#define COM0_VALUE	00
	#endif
#endif


#define	TIMER_DISABLE		0
#define	TIMER_ENABLE 		1

//TIMER0_OVERFLOW_INT
#if (TIMER0_OVERFLOW_INT==TIMER_ENABLE)	
	#define TOIE0_VALUE	 1
#elif (TIMER0_OVERFLOW_INT==TIMER_DISABLE)	
	#define TOIE0_VALUE	 0
#else
	#warning "The default for the TIMER0_OVERFLOW_INT is DISABLE"
	#define TOIE0_VALUE	 0
#endif

//TIMER0_OUTCOMPARE_INT
#if (TIMER0_OUTCOMPARE_INT==TIMER_ENABLE)	
	#define OCIE0_VALUE	 1
#elif (TIMER0_OUTCOMPARE_INT==TIMER_DISABLE)	
	#define OCIE0_VALUE	 0
#else
	#warning "The default for the TIMER0_OUTCOMPARE_INT is DISABLE"
	#define OCIE0_VALUE	 0
#endif

//TIMER1_OVERFLOW_INT
#if (TIMER1_OVERFLOW_INT==TIMER_ENABLE)	
	#define TOIE1_VALUE	 1
#elif (TIMER1_OVERFLOW_INT==TIMER_DISABLE)	
	#define TOIE1_VALUE	 0
#else
	#warning "The default for the TIMER1_OVERFLOW_INT is DISABLE"
	#define TOIE1_VALUE	 0
#endif

//TIMER1_OUTCOMPAREB_INT
#if (TIMER1_OUTCOMPAREB_INT==TIMER_ENABLE)	
	#define OCIE1B_VALUE	 1
#elif (TIMER1_OUTCOMPAREB_INT==TIMER_DISABLE)	
	#define OCIE1B_VALUE	 0
#else
	#warning "The default for the TIMER1_OUTCOMPAREB_INT is DISABLE"
	#define OCIE1B_VALUE	 0
#endif

//TIMER1_OUTCOMPAREA_INT   
#if (TIMER1_OUTCOMPAREA_INT==TIMER_ENABLE)	
	#define OCIE1A_VALUE	 1
#elif (TIMER1_OUTCOMPAREA_INT==TIMER_DISABLE)	
	#define OCIE1A_VALUE	 0
#else
	#warning "The default for the TIMER1_OUTCOMPAREA_INT is DISABLE"
	#define OCIE1A_VALUE	 0
#endif

//TIMER1_INPUTCAPTURE_INT 
#if (TIMER1_INPUTCAPTURE_INT==TIMER_ENABLE)	
	#define TICIE1_VALUE	 1
#elif (TIMER1_INPUTCAPTURE_INT==TIMER_DISABLE)	
	#define TICIE1_VALUE	 0
#else
	#warning "The default for the TIMER1_INPUTCAPTURE_INT is DISABLE"
	#define TICIE1_VALUE	 0
#endif

//TIMER2_OVERFLOW_INT     
#if (TIMER2_OVERFLOW_INT==TIMER_ENABLE)	
	#define TOIE2_VALUE	 1
#elif (TIMER2_OVERFLOW_INT==TIMER_DISABLE)	
	#define TOIE2_VALUE	 0
#else
	#warning "The default for the TIMER2_OVERFLOW_INT is DISABLE"
	#define TOIE2_VALUE	 0
#endif

//TIMER2_OUTCOMPARE_INT
#if (TIMER2_OUTCOMPARE_INT==TIMER_ENABLE)	
	#define OCIE2_VALUE	 1
#elif (TIMER2_OUTCOMPARE_INT==TIMER_DISABLE)	
	#define OCIE2_VALUE	 0
#else
	#warning "The default for the TIMER2_OUTCOMPARE_INT is DISABLE"
	#define OCIE2_VALUE	 0
#endif

/*Comment!: TCCR0 Pins*/
#define FOC0    7
#define WGM00   6
#define COM01   5
#define COM00   4
#define WGM01   3
#define CS02    2
#define CS01    1
#define CS00    0

/*Comment!: TCCR2 Pins*/
#define FOC2    7
#define WGM20   6
#define COM21   5
#define COM20   4
#define WGM21   3
#define CS22    2
#define CS21    1
#define CS20    0

/*Comment!: TIMSK Pins*/
#define OCIE2   7
#define TOIE2   6
#define TICIE1  5
#define OCIE1A  4
#define OCIE1B  3
#define TOIE1   2
#define OCIE0   1
#define TOIE0   0

/*Comment!: Number of Timer INTERRUPTS*/
#define TIMER_NUM_INTERRUPTS	8

/* Timer/Counter2 Compare Match */
#define TIMER2_COMP_vect		__vector_4

/* Timer/Counter2 Overflow */
#define TIMER2_OVF_vect			__vector_5

/* Timer/Counter1 Capture Event */
#define TIMER1_CAPT_vect		__vector_6

/* Timer/Counter1 Compare Match A */
#define TIMER1_COMPA_vect		__vector_7

/* Timer/Counter1 Compare Match B */
#define TIMER1_COMPB_vect		__vector_8

/* Timer/Counter1 Overflow */
#define TIMER1_OVF_vect			__vector_9

/* Timer/Counter0 Compare Match */
#define TIMER0_COMP_vect		__vector_10

/* Timer/Counter0 Overflow */
#define TIMER0_OVF_vect			__vector_11


/*******************************************************/
/***************** Private Functions *******************/
/*******************************************************/

//TCCR0 >> FOC0 WGM00 COM01 COM00 WGM01 CS02 CS01 CS00

/*Comment!: Concatenate Function for TCCR1A Initial Value */
#define CONC_HELPER_TCCR0(b7,b6,b54,b3,b210)		 0b##b7##b6##b54##b3##b210
#define	CONC_TCCR0(b7,b6,b54,b3,b210)				 CONC_HELPER_TCCR0(b7,b6,b54,b3,b210)
#define	TIMER_u8TCCR0_VALUE							 CONC_TCCR0(FOC0_VALUE,WGM00_VALUE,COM0_VALUE,WGM01_VALUE,TIMER0_PRESCALE)


/*Comment!: Concatenate Function for TIMSK Initial Value */
#define CONC_HELPER_TIMSK(b7,b6,b5,b4,b3,b2,b1,b0)	 0b##b7##b6##b5##b4##b3##b2##b1##b0
#define	CONC_TIMSK(b7,b6,b5,b4,b3,b2,b1,b0)			 CONC_HELPER_TIMSK(b7,b6,b5,b4,b3,b2,b1,b0)	
#define	TIMER_u8TIMSK_VALUE							 CONC_TIMSK(OCIE2_VALUE,TOIE2_VALUE,TICIE1_VALUE,OCIE1A_VALUE,OCIE1B_VALUE,TOIE1_VALUE,OCIE0_VALUE,TOIE0_VALUE)

#define ISR(vector, ...) \
	void vector(void) __attribute__ ((signal,used,externally_visible)) __VA_ARGS__;\
	void vector(void)

#endif /* TIMER_PRIVATE_H_ */  
