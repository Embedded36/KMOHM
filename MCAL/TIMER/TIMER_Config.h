/*
 * TIMER_Config.h
 *
 *  Created on: Feb 2, 2016
 *      Author: KiMo
 */

#ifndef TIMER_CONFIG_H_
#define TIMER_CONFIG_H_

/*
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
#define TIMER0_PRESCALE          TIMER0_CLK_DIV8

/*Comment!: Timer Interrupts */
/*Range!: TIMER_DISABLE or TIMER_ENABLE */
#define TIMER0_OVERFLOW_INT                      TIMER_ENABLE
#define TIMER0_OUTCOMPARE_INT                    TIMER_DISABLE
#define TIMER1_OVERFLOW_INT                      TIMER_DISABLE
#define TIMER1_OUTCOMPAREB_INT          		 TIMER_DISABLE
#define TIMER1_OUTCOMPAREA_INT        		   	 TIMER_DISABLE
#define TIMER1_INPUTCAPTURE_INT          		 TIMER_DISABLE
#define TIMER2_OVERFLOW_INT                      TIMER_DISABLE
#define TIMER2_OUTCOMPARE_INT            		 TIMER_DISABLE


#endif /* TIMER_CONFIG_H_ */

