/*
 * SPI_prog.c
 *
 *  Created on: Jan 27, 2016
 *      Author: Kareem Galal
 */

#include "..\..\Utilities\Types.h"
#include "..\..\Utilities\Util.h"
#include "SPI_Private.h"
#include "SPI_Config.h"
#include "SPI_Interface.h"


/*Comment!: SPI Initialization */
extern void SPI_voidInit(void){
	SPI_u8UBRRH = (SPI_u16UBRR_VALUE>>8);
	SPI_u8UBRRL = SPI_u16UBRR_VALUE;
	//SPI_voidEnable();  
	//SPI_u8UCSRA = 0; //SPI_u8CONFIGURATION;
	SET_BIT(SPI_u8UCSRB,RXEN);
	SET_BIT(SPI_u8UCSRB,TXEN);
	SPI_u8UCSRC = SPI_u8CONFIGURATION;
	return;
}
/*Comment!: SPI Enable */
extern void SPI_voidEnable(void){
	/* Enable receiver and transmitter */
	//UCSRB = (1<<RXEN)|(1<<TXEN);
	SET_BIT(SPI_u8UCSRB,RXEN);
	SET_BIT(SPI_u8UCSRB,TXEN);
	//sbi(*_ucsrb, RXCIE0);
    //cbi(*_ucsrb, UDRIE);
	return;
}
/*Comment!: SPI Disable */
extern void SPI_voidDisable(void){
	//UCSRB &= ~((1<<RXEN)|(1<<TXEN));
	CLR_BIT(SPI_u8UCSRB,RXEN);
	CLR_BIT(SPI_u8UCSRB,TXEN);
	//cbi(*_ucsrb, RXEN);
    //cbi(*_ucsrb, TXEN);
	//cbi(*_ucsrb, RXCIE0);
	//cbi(*_ucsrb, UDRIE0);
	return;
}
/*Comment!: Transmit One Byte to the SPI*/
extern u8 SPI_u8TransmitOneByte(u8 Copy_u8Data){
	u8 Local_u8Status = u8OK;
	/* Wait for empty transmit buffer */
	while (!(GET_BIT(SPI_u8UCSRA,UDRE)));
	/* Put data into buffer, sends the data */
	SPI_u8UDR = Copy_u8Data;
	return Local_u8Status;
}
/*Comment!: Receive One Byte from the SPI */
extern u8 SPI_u8ReceiveOneByte(u8 *Copy_u8Data){
	u8 Local_u8Status = u8OK;
	/* Wait for data to be received */
	while (!(GET_BIT(SPI_u8UCSRA,RXC)));
	/* Get and return received data from buffer */
	*Copy_u8Data = SPI_u8UDR;
	return Local_u8Status;
}
/*Comment!: Transmit a String to the SPI */
extern u8 SPI_u8TransmitString(u8 *Copy_u8String){
	u8 Local_u8Status = u8OK;
	while(*(Copy_u8String))
	{
		SPI_u8TransmitOneByte(*Copy_u8String++);
	}
	return Local_u8Status;
}
