/*
 * EXTINT_Config.h
 *
 *  Created on: Feb 2, 2016
 *      Author: KiMo
 */

#ifndef EXTINT_CONFIG_H_
#define EXTINT_CONFIG_H_

/*Comment!: EXTINT Interrupts Initial State*/
/*Range!: EXTINT_DISABLE or EXTINT_ENABLE */
#define EXTINT0_INITSTATE		EXTINT_ENABLE
#define EXTINT1_INITSTATE		EXTINT_DISABLE
#define EXTINT2_INITSTATE		EXTINT_DISABLE

/*Comment!: Sense Control mode for External Interrupt #0 , #1 */
/*Range!:  EXTINT_LEVEL_LOW or EXTINT_EDGE_ANY or EXTINT_EDGE_FALLING or EXTINT_EDGE_RISING */
#define EXTINT0_SENSE_CON_MODE          EXTINT_EDGE_ANY
#define EXTINT1_SENSE_CON_MODE          EXTINT_EDGE_ANY

/*Comment!: Sense Control mode for External Interrupt #2 */
/*Range!:   EXTINT_EDGE_FALLING or EXTINT_EDGE_RISING */
#define EXTINT2_SENSE_CON_MODE          EXTINT_EDGE_RISING

#endif /* EXTINT_CONFIG_H_ */

