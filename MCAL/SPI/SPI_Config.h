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

/*Comment!:  CPU frequency  */
#define F_OSC	4000000UL

/*Comment!:  Voltage Reference Selection For SPI */
/*Range!  : SPI_u8AREF or SPI_u8AVCC or SPI_u8INTERNAL */
#define SPI_u32BAUD_RATE			SPI_u32BAUD_RATE_9600	

/*Comment!: SPI Configuration Options*/
/*Range!  : SPI_u8_5N1 or SPI_u8_6N1 or SPI_u8_7N1 or SPI_u8_8N1 or SPI_u8_5N2 or SPI_u8_6N2 or SPI_u8_7N2 or SPI_u8_8N2
			SPI_u8_5E1 or SPI_u8_6E1 or SPI_u8_7E1 or SPI_u8_8E1 or SPI_u8_5E2 or SPI_u8_6E2 or SPI_u8_7E2 or SPI_u8_8E2
			SPI_u8_5O1 or SPI_u8_6O1 or SPI_u8_7O1 or SPI_u8_8O1 or SPI_u8_5O2 or SPI_u8_6O2 or SPI_u8_7O2 or SPI_u8_8O2*/
#define SPI_u8CONFIGURATION		SPI_u8_8N1	



#endif /* _SPI_CONFIG_H_ */
