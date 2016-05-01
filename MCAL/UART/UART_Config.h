/*
 * UART_config.h
 *
 *  Created on: Jan 27, 2016
 *      Author: Kareem Galal
 */

#ifndef _UART_CONFIG_H_
#define _UART_CONFIG_H_

/*******************************************************/
/***************** Public Definitions  *****************/
/*******************************************************/

/*Comment!:  CPU frequency  */
#define F_OSC	4000000UL

/*Comment!:  Voltage Reference Selection For UART */
/*Range!  : UART_u8AREF or UART_u8AVCC or UART_u8INTERNAL */
#define UART_u32BAUD_RATE			UART_u32BAUD_RATE_9600	

/*Comment!: UART Configuration Options*/
/*Range!  : UART_u8_5N1 or UART_u8_6N1 or UART_u8_7N1 or UART_u8_8N1 or UART_u8_5N2 or UART_u8_6N2 or UART_u8_7N2 or UART_u8_8N2
			UART_u8_5E1 or UART_u8_6E1 or UART_u8_7E1 or UART_u8_8E1 or UART_u8_5E2 or UART_u8_6E2 or UART_u8_7E2 or UART_u8_8E2
			UART_u8_5O1 or UART_u8_6O1 or UART_u8_7O1 or UART_u8_8O1 or UART_u8_5O2 or UART_u8_6O2 or UART_u8_7O2 or UART_u8_8O2*/
#define UART_u8CONFIGURATION		UART_u8_8N1	



#endif /* _UART_CONFIG_H_ */
