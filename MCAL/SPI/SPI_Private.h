/*
   SPI_private.h

    Created on: Jan 27, 2016
        Author: Kareem Galal
*/

#ifndef _SPI_PRIVATE_H_
#define _SPI_PRIVATE_H_

/*******************************************************/
/***************** Private Definitions  ****************/
/*******************************************************/

/*Comment!: ATMEGA32 SPI Registers */
#define SPI_u8UCSRA		(*(volatile u8*)(0x2B))
#define SPI_u8UCSRB		(*(volatile u8*)(0x2A))
#define SPI_u8UCSRC		(*(volatile u8*)(0x40))
#define SPI_u8UBRRL		(*(volatile u8*)(0x29))
#define SPI_u8UBRRH		(*(volatile u8*)(0x40))
#define SPI_u8UDR			(*(volatile u8*)(0x2C))

/*Comment!: Calculate the value of UBRR Register */
#define SPI_u16UBRR_VALUE ((F_OSC / 16UL / SPI_u32BAUD_RATE) - 1UL)


/*Comment!: SPI Baud Rate Options*/
#define SPI_u32BAUD_RATE_2400		2400UL
#define SPI_u32BAUD_RATE_4800		4800UL
#define SPI_u32BAUD_RATE_9600		9600UL
#define SPI_u32BAUD_RATE_14400		14400UL
#define SPI_u32BAUD_RATE_19200   	19200UL
#define SPI_u32BAUD_RATE_28800   	28800UL
#define SPI_u32BAUD_RATE_38400   	38400UL
#define SPI_u32BAUD_RATE_57600   	57600UL
#define SPI_u32BAUD_RATE_76800   	76800UL
#define SPI_u32BAUD_RATE_115200   	115200UL

/*Comment!: SPI Configuration Options*/
#define SPI_u8_5N1 		0x80
#define SPI_u8_6N1 		0x82
#define SPI_u8_7N1 		0x84
#define SPI_u8_8N1 		0x86
#define SPI_u8_5N2 		0x88
#define SPI_u8_6N2 		0x8A
#define SPI_u8_7N2 		0x8C
#define SPI_u8_8N2 		0x8E
#define SPI_u8_5E1 		0xA0
#define SPI_u8_6E1 		0xA2
#define SPI_u8_7E1 		0xA4
#define SPI_u8_8E1 		0xA6
#define SPI_u8_5E2 		0xA8
#define SPI_u8_6E2 		0xAA
#define SPI_u8_7E2 		0xAC
#define SPI_u8_8E2 		0xAE
#define SPI_u8_5O1 		0xB0
#define SPI_u8_6O1 		0xB2
#define SPI_u8_7O1 		0xB4
#define SPI_u8_8O1 		0xB6
#define SPI_u8_5O2 		0xB8
#define SPI_u8_6O2 		0xBA
#define SPI_u8_7O2 		0xBC
#define SPI_u8_8O2 		0xBE


/*Comment!: RXEN: Receiver Enable */
#define RXEN				4
/*Comment!: TXEN: Transmitter Enable */
#define TXEN				3
/*Comment!: SPI Data Register Empty */
#define UDRE				5
/*Comment!: SPI Receive Complete */
#define RXC					7


/*******************************************************/
/***************** Private Functions *******************/
/*******************************************************/


#endif /* _SPI_PRIVATE_H_ */
