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
#define SPI_u8SPCR		(*(volatile u8*)(0x2D)) //SPI Control Register  SPCR
#define SPI_u8SPSR		(*(volatile u8*)(0x2E)) //SPI Status Register  SPSR
#define SPI_u8SPDR		(*(volatile u8*)(0x2F)) //SPI Data Register  SPDR
#define SPI_u8DDR		(*(volatile u8*)(0x37)) //DDRB

/*Comment!: SPI Initial State & Interrupt options*/
#define SPI_DISABLE		0
#define SPI_ENABLE		1

/*Comment!: SPI Data Order Modes*/
#define SPI_MSB			0
#define SPI_LSB			1

/*Comment!: SPI Master/Slave Modes*/
#define SPI_MASTER		1
#define SPI_SLAVE		0

/*
 SPI Control Register SPCR
 Bit	7	 6	  5	 	4	 3	  2	   1	0
 	  SPIE 	SPE	 DORD MSTR CPOL CPHA SPR1 SPR0

 Bit 7 SPIE: SPI Interrupt Enable
 Bit 6 SPE: SPI Enable
 Bit 5 DORD: Data Order >>  one for LSB * zero for MSB
 Bit 4 MSTR: Master/Slave Select >>  Zero for Slave SPI mode & One for Master SPI mode
 Bit 3 CPOL: Clock Polarity
 Bit 2 CPHA: Clock Phase
 Bits 1, 0 SPR1, SPR0: SPI Clock Rate Select 1 and 0

 Relationship Between SCK and the Oscillator Frequency
 SPI2X SPR1 SPR0 SCK Frequency
 0 		0	0 	fosc/4
 0 		0 	1 	fosc/16
 0 		1 	0 	fosc/64
 0 		1 	1 	fosc/128
 1 		0 	0 	fosc/2
 1 		0 	1 	fosc/8
 1 		1 	0 	fosc/32
 1 		1 	1 	fosc/64
 */
/*
 SPI Status Register  SPSR
 Bit	  7    6  5 4 3 2 1  0
 SPIF WCOL - - - - - SPI2X

 Bit 7  SPIF: SPI Interrupt Flag
 Bit 6  WCOL: Write COLlision Flag
 Bit 0  SPI2X: Double SPI Speed Bit
 */
/*Comment!: SPI Prescaler*/
#define SPI_CLOCK_DIV4 		4
#define SPI_CLOCK_DIV16 	16
#define SPI_CLOCK_DIV64 	64
#define SPI_CLOCK_DIV128	128
#define SPI_CLOCK_DIV2 		2
#define SPI_CLOCK_DIV8		8
#define SPI_CLOCK_DIV32 	32
//#define SPI_CLOCK_DIV64 	11

/*Comment!: SPI Data Modes*/
#define SPI_MODE0 			00
#define SPI_MODE1 			01
#define SPI_MODE2 			10
#define SPI_MODE3 			11

#if (SPI_INITSTATE==SPI_ENABLE)	
#define SPI_SPE	 1
#elif (SPI_INITSTATE==SPI_ENABLE)	
#define SPI_SPE	 0
#else
#warning "The default for the SPI is DISABLE"
#define SPI_SPE	 0
#endif

#if (SPI_INT==SPI_ENABLE)	
#define SPI_SPIE	 1
#elif (SPI_INT==SPI_DISABLE)	
#define SPI_SPIE	 0
#else
#warning "The default for the SPI Interrupt is DISABLE"
#define SPI_SPIE	 0
#endif

#if (SPI_DATA_ORDER==SPI_LSB)	
#define SPI_DORD	 1
#elif (SPI_DATA_ORDER==SPI_MSB)	
#define SPI_DORD	 0
#else
#warning "The default for SPI Data Order is MSB"
#define SPI_DORD	 0
#endif

#if (SPI_MASTER_SLAVE_MODE==SPI_MASTER)
#define SPI_MSTR	 1
#elif (SPI_MASTER_SLAVE_MODE==SPI_SLAVE)
#define SPI_MSTR	 0
#else
#warning "The default for the SPI mode is MASTER"
#define SPI_MSTR	 0
#endif

#if (SPI_DATA_MODE==SPI_MODE0)	
#define SPI_CPOL	 0
#define SPI_CPHA	 0
#elif (SPI_DATA_MODE==SPI_MODE1)	
#define SPI_CPOL	 0
#define SPI_CPHA	 1
#elif (SPI_DATA_MODE==SPI_MODE2)	
#define SPI_CPOL	 1
#define SPI_CPHA	 0
#elif (SPI_DATA_MODE==SPI_MODE3)	
#define SPI_CPOL	 1
#define SPI_CPHA	 1
#else
#warning "The default mode for the SPI is MODE0"
#define SPI_CPOL	 0
#define SPI_CPHA	 0
#endif

#if (SPI_PRESCALE==SPI_CLOCK_DIV4)	
#define SPI_SPI2X	 0
#define SPI_SPR1	 0
#define SPI_SPR0	 0
#elif (SPI_PRESCALE==SPI_CLOCK_DIV16)	
#define SPI_SPI2X	 0
#define SPI_SPR1	 0
#define SPI_SPR0	 1
#elif (SPI_PRESCALE==SPI_CLOCK_DIV64)	
#define SPI_SPI2X	 0
#define SPI_SPR1	 1
#define SPI_SPR0	 0
#elif (SPI_PRESCALE==SPI_CLOCK_DIV128)	
#define SPI_SPI2X	 0
#define SPI_SPR1	 1
#define SPI_SPR0	 1
#elif (SPI_PRESCALE==SPI_CLOCK_DIV2)	
#define SPI_SPI2X	 1
#define SPI_SPR1	 0
#define SPI_SPR0	 0
#elif (SPI_PRESCALE==SPI_CLOCK_DIV8)	
#define SPI_SPI2X	 1
#define SPI_SPR1	 0
#define SPI_SPR0	 1
#elif (SPI_PRESCALE==SPI_CLOCK_DIV32)
#define SPI_SPI2X	 1
#define SPI_SPR1	 1
#define SPI_SPR0	 0
#else
#warning "The default PRESCALE for the SPI is CLOCK_DIV4"
#define SPI_SPI2X	 0
#define SPI_SPR1	 0
#define SPI_SPR0	 0
#endif

/*Comment!: Bits Identifications */
#define SPI2X		0
#define SPE			6
#define SPIF		7
#define SPI_MOSI	5
#define SPI_MISO	6
#define SPI_SCK		7

/*Comment!: ISR for Serial Transfer Complete*/
#define ISR(vector, ...) \
	void vector(void) __attribute__ ((signal,used,externally_visible)) __VA_ARGS__;\
	void vector(void)

#define SPI_STC			__vector_12 //Serial Transfer Complete
/*******************************************************/
/***************** Private Functions *******************/
/*******************************************************/

/*Comment!: Concatenate Function for SPCR Initial Value */
#define CONC_HELPER_SPCR(b7,b6,b5,b4,b3,b2,b1,b0)		0b##b7##b6##b5##b4##b3##b2##b1##b0
#define	CONC_SPCR(b7,b6,b5,b4,b3,b2,b1,b0)				CONC_HELPER_SPCR(b7,b6,b5,b4,b3,b2,b1,b0)
#define	SPI_u8SPCR_VALUE								CONC_SPCR(SPI_SPIE,SPI_SPE,SPI_DORD,SPI_MSTR,SPI_CPOL,SPI_CPHA,SPI_SPR1,SPI_SPR0)

#endif /* _SPI_PRIVATE_H_ */
