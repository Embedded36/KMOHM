/*
 * SystemClock.h
 *
 *  Created on: Apr 24, 2016
 *      Author: KiMo
 */

#ifndef UTILITIES_SYSTEMCLOCK_H_
#define UTILITIES_SYSTEMCLOCK_H_

/*Comment!: System clock */
#define F_CPU 						4000000UL
#define clockCyclesPerMicrosecond	(F_CPU/1000000UL)
#define clockCyclesPerMillisecond	(F_CPU/1000UL)

#endif /* UTILITIES_SYSTEMCLOCK_H_ */
