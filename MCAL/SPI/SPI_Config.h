/*
 * SPI_config.h
 *
 *  Created on: Jan 27, 2016
 *      Author: Kareem Galal
 */

#ifndef _SPI_CONFIG_H_
#define _SPI_CONFIG_H_

/*******************************************************/
/***************** Public Definitions  *****************/
/*******************************************************/

/*Comment!: SPI Initial State*/
/*Range!: SPI_DISABLE or SPI_ENABLE */
#define SPI_INITSTATE				SPI_ENABLE

/*Comment!: SPI Interrupts */
/*Range!: SPI_DISABLE or SPI_ENABLE */
#define SPI_INT						SPI_DISABLE

/*Comment!: SPI Data Order */
/*Range!: SPI_MSB or SPI_LSB */
#define SPI_DATA_ORDER				SPI_MSB

/*Comment!: SPI Master/Slave Mode*/
/*Range!: SPI_MASTER or SPI_SLAVE */
#define SPI_MASTER_SLAVE_MODE		SPI_MASTER

/*
Mode Conditions 	Leading Edge 		Trailing Edge
 0 	CPOL=0,CPHA=0 	read on rising 		change on falling
 1 	CPOL=0,CPHA=1 	change on rising 	read on falling
 2 	CPOL=1,CPHA=0 	read on falling 	change on rising
 3 	CPOL=1,CPHA=1 	change on falling 	read on rising
*/

/*Comment!: SPI Data Mode*/
/*Range!  : SPI_MODE0 or SPI_MODE1 or SPI_MODE2 or SPI_MODE3*/
#define SPI_DATA_MODE		SPI_MODE0

/*Comment!: SPI Default Prescaler */
/*Range!: SPI_CLOCK_DIV4 or SPI_CLOCK_DIV16 or SPI_CLOCK_DIV64 or SPI_CLOCK_DIV128 or SPI_CLOCK_DIV2 or SPI_CLOCK_DIV8 or SPI_CLOCK_DIV32 */
#define SPI_PRESCALE          SPI_CLOCK_DIV16



#endif /* _SPI_CONFIG_H_ */
