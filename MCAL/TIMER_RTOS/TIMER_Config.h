/*
 * TIMER_Config.h
 *
 *  Created on: Feb 2, 2016
 *      Author: KiMo
 */

#ifndef TIMER_CONFIG_H_
#define TIMER_CONFIG_H_

/*

 fOCn = fclk_I/O  /  2 * N (1 + OCRn)
 The N variable represents the prescale factor (1, 8, 64, 256, or 1024).

 fOCnPWM = fclk_I/O  /  N * 256

 fOCnPCPWM= fclk_I/O  / N * 510

 for 4MHz crystal
 0 = STOP (Timer not counting)
 1 = CLOCK            tics= 4MHz                      8bitoverflow= 15625Hz           16bit=  61.035Hz
 2 = CLOCK/8          tics= 500kHz            		 8bitoverflow= 1953.125Hz        16bit=   7.629Hz
 3 = CLOCK/64         tics= 62500Hz           		 8bitoverflow=  244.141Hz        16bit=   0.954Hz
 4 = CLOCK/256        tics= 15625Hz           		 8bitoverflow=   61.035Hz        16bit=   0.238Hz
 5 = CLOCK/1024       tics= 3906.25Hz         		 8bitoverflow=   15.259Hz        16bit=   0.060Hz
 6 = External Clock on T(x) pin (falling edge)
 7 = External Clock on T(x) pin (rising edge)
 */

/*Comment!: Default Prescale Settings For Timer 0 */
/*Range!: TIMER0_CLK_STOP or TIMER0_CLK_DIV1 or TIMER0_CLK_DIV8  or TIMER0_CLK_DIV64 or TIMER0_CLK_DIV256 or TIMER0_CLK_DIV1024or TIMER0_CLK_T0_FALLor TIMER0_CLK_T0_RISE */
#define TIMER0_PRESCALE					TIMER0_CLK_DIV1

/*Comment!: Operation mode for Timer 0 */
/*Range!: TIMER0_NORMAL or TIMER0_PWM_PHASE_CORRECT or TIMER0_CTC or TIMER0_FAST_PWM */
#define TIMER0_OPERATING_MODE			TIMER0_NORMAL

/*Comment!: Compare Output Mode for Timer0*/
/*Range!: if the operation mode is Normal or CTC then the range will be 
 TIMER0_COM0 or TIMER0_COM1 or TIMER0_COM2 or TIMER0_COM3
 else if operation mode is FastPWM or PWM_PHASE_CORRECT then the range will be
 TIMER0_COM0 or TIMER0_COM2 or TIMER0_COM3

 Compare Output Mode for TIMER0

 Compare Output Mode, non-PWM Mode (normal or CTC mode)
 Mode Name	 	Description
 TIMER0_COM0 	Normal port operation, OC0 disconnected.
 TIMER0_COM1 	Toggle OC0 on compare match
 TIMER0_COM2 	Clear OC0 on compare match
 TIMER0_COM3 	Set OC0 on compare match
 ******************************************************************************************************
 Compare Output Mode, Phase Correct PWM Mode
 Mode Name		Description
 TIMER0_COM0	Normal port operation, OC0 disconnected.
 TIMER0_COM2	Clear OC0 on compare match when up-counting. Set OC0 on compare match when downcounting.
 TIMER0_COM3	Set OC0 on compare match when up-counting. Clear OC0 on compare match when downcounting.
 ******************************************************************************************************
 Compare Output Mode, Fast PWM Mode(1)
 Mode Name		Description
 TIMER0_COM0		Normal port operation, OC0 disconnected.
 TIMER0_COM2		Clear OC0 on compare match, set OC0 at BOTTOM,(nin-inverting mode)
 TIMER0_COM3		Set OC0 on compare match, clear OC0 at BOTTOM,(inverting mode)
 ******************************************************************************************************
 */
#define TIMER0_COMPARE_OUTPUT_MODE		TIMER0_COM0

/*Comment!: Timer Interrupts */
/*Range!: TIMER_DISABLE or TIMER_ENABLE */
#define TIMER0_OVERFLOW_INT				TIMER_ENABLE
#define TIMER0_OUTCOMPARE_INT			TIMER_DISABLE
#define TIMER1_OVERFLOW_INT				TIMER_DISABLE
#define TIMER1_OUTCOMPAREB_INT			TIMER_DISABLE
#define TIMER1_OUTCOMPAREA_INT			TIMER_DISABLE
#define TIMER1_INPUTCAPTURE_INT			TIMER_DISABLE
#define TIMER2_OVERFLOW_INT				TIMER_DISABLE
#define TIMER2_OUTCOMPARE_INT			TIMER_DISABLE

#endif /* TIMER_CONFIG_H_ */

