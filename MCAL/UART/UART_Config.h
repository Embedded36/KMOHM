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

/*Comment!: UART Baud Rate */
/*Range!  : UART_u32BAUD_RATE_2400 or UART_u32BAUD_RATE_4800 or UART_u32BAUD_RATE_9600 or UART_u32BAUD_RATE_14400 or UART_u32BAUD_RATE_19200 or
			UART_u32BAUD_RATE_28800 or UART_u32BAUD_RATE_38400 or UART_u32BAUD_RATE_57600 or UART_u32BAUD_RATE_76800 or UART_u32BAUD_RATE_115200 */
#define UART_u32BAUD_RATE			UART_u32BAUD_RATE_9600	



/*Comment!: UART Configuration Options*/
/*Range!  : UART_u8_5N1 or UART_u8_6N1 or UART_u8_7N1 or UART_u8_8N1 or UART_u8_5N2 or UART_u8_6N2 or UART_u8_7N2 or UART_u8_8N2
			UART_u8_5E1 or UART_u8_6E1 or UART_u8_7E1 or UART_u8_8E1 or UART_u8_5E2 or UART_u8_6E2 or UART_u8_7E2 or UART_u8_8E2
			UART_u8_5O1 or UART_u8_6O1 or UART_u8_7O1 or UART_u8_8O1 or UART_u8_5O2 or UART_u8_6O2 or UART_u8_7O2 or UART_u8_8O2*/
/*UART_u8_8N1: 8 data bist , No parity, 1 Stop bit*/
#define UART_u8CONFIGURATION		UART_u8_8N1	


/*Comment!: UART Buffer Size*/
#define SERIAL_RX_BUFFER_SIZE	128
#define SERIAL_TX_BUFFER_SIZE	128


#endif /* _UART_CONFIG_H_ */