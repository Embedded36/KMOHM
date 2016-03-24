/*
   UART_private.h

    Created on: Jan 27, 2016
        Author: Kareem Galal
*/

#ifndef _UART_PRIVATE_H_
#define _UART_PRIVATE_H_

/*******************************************************/
/***************** Private Definitions  ****************/
/*******************************************************/

/*Comment!: ATMEGA32 UART Registers */
#define UART_u8UCSRA		(*(volatile u8*)(0x2B))
#define UART_u8UCSRB		(*(volatile u8*)(0x2A))
#define UART_u8UCSRC		(*(volatile u16*)(0x40))
#define UART_u8UBRRL		(*(volatile u8*)(0x29))
#define UART_u8UBRRH		(*(volatile u8*)(0x40))
#define UART_u8UDR			(*(volatile u8*)(0x2C))

/*Comment!: Calculate the value of UBRR Register */
#define UART_u16UBRR_VALUE ((F_OSC / 16UL / UART_u32BAUD_RATE) - 1UL)


/*Comment!: UART Baud Rate Options*/
#define UART_u32BAUD_RATE_2400		2400UL
#define UART_u32BAUD_RATE_4800		4800UL
#define UART_u32BAUD_RATE_9600		9600UL
#define UART_u32BAUD_RATE_14400		14400UL
#define UART_u32BAUD_RATE_19200   	19200UL
#define UART_u32BAUD_RATE_28800   	28800UL
#define UART_u32BAUD_RATE_38400   	38400UL
#define UART_u32BAUD_RATE_57600   	57600UL
#define UART_u32BAUD_RATE_76800   	76800UL
#define UART_u32BAUD_RATE_115200   	115200UL

/*Comment!: UART Configuration Options*/
#define UART_u8_5N1 		0x80
#define UART_u8_6N1 		0x82
#define UART_u8_7N1 		0x84
#define UART_u8_8N1 		0x86
#define UART_u8_5N2 		0x88
#define UART_u8_6N2 		0x8A
#define UART_u8_7N2 		0x8C
#define UART_u8_8N2 		0x8E
#define UART_u8_5E1 		0xA0
#define UART_u8_6E1 		0xA2
#define UART_u8_7E1 		0xA4
#define UART_u8_8E1 		0xA6
#define UART_u8_5E2 		0xA8
#define UART_u8_6E2 		0xAA
#define UART_u8_7E2 		0xAC
#define UART_u8_8E2 		0xAE
#define UART_u8_5O1 		0xB0
#define UART_u8_6O1 		0xB2
#define UART_u8_7O1 		0xB4
#define UART_u8_8O1 		0xB6
#define UART_u8_5O2 		0xB8
#define UART_u8_6O2 		0xBA
#define UART_u8_7O2 		0xBC
#define UART_u8_8O2 		0xBE


/*Comment!: RXEN: Receiver Enable */
#define RXEN				4
/*Comment!: TXEN: Transmitter Enable */
#define TXEN				3
/*Comment!: UART Data Register Empty */
#define UDRE				5
/*Comment!: UART Receive Complete */
#define RXC					7


/*******************************************************/
/***************** Private Functions *******************/
/*******************************************************/


#endif /* _UART_PRIVATE_H_ */
