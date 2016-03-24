/*
 * UART_prog.c
 *
 *  Created on: Jan 27, 2016
 *      Author: Kareem Galal
 */

#include "..\..\Utilities\Types.h"
#include "..\..\Utilities\Util.h"
#include "UART_Private.h"
#include "UART_Config.h"
#include "UART_Interface.h"


/*Comment!: UART Initialization */
extern void UART_voidInit(void){
	UART_u8UBRRH = (UART_u16UBRR_VALUE>>8);
	UART_u8UBRRL = UART_u16UBRR_VALUE;
	//UART_voidEnable();  
	//UART_u8UCSRA = 0; //UART_u8CONFIGURATION;
	SET_BIT(UART_u8UCSRB,RXEN);
	SET_BIT(UART_u8UCSRB,TXEN);
	UART_u8UCSRC = 0x86; //UART_u8CONFIGURATION;
	return;
}
/*Comment!: UART Enable */
extern void UART_voidEnable(void){
	/* Enable receiver and transmitter */
	//UCSRB = (1<<RXEN)|(1<<TXEN);
	SET_BIT(UART_u8UCSRB,RXEN);
	SET_BIT(UART_u8UCSRB,TXEN);
	//sbi(*_ucsrb, RXCIE0);
    //cbi(*_ucsrb, UDRIE);
	return;
}
/*Comment!: UART Disable */
extern void UART_voidDisable(void){
	//UCSRB &= ~((1<<RXEN)|(1<<TXEN));
	CLR_BIT(UART_u8UCSRB,RXEN);
	CLR_BIT(UART_u8UCSRB,TXEN);
	//cbi(*_ucsrb, RXEN);
    //cbi(*_ucsrb, TXEN);
	//cbi(*_ucsrb, RXCIE0);
	//cbi(*_ucsrb, UDRIE0);
	return;
}
/*Comment!: Transmit One Byte to the UART*/
extern u8 UART_u8TransmitOneByte(u8 Copy_u8Data){
	u8 Local_u8Status = u8OK;
	/* Wait for empty transmit buffer */
	while (!(GET_BIT(UART_u8UCSRA,UDRE)));
	/* Put data into buffer, sends the data */
	UART_u8UDR = Copy_u8Data;
	return Local_u8Status;
}
/*Comment!: Receive One Byte from the UART */
extern u8 UART_u8ReceiveOneByte(u8 *Copy_u8Data){
	u8 Local_u8Status = u8OK;
	/* Wait for data to be received */
	while (!(GET_BIT(UART_u8UCSRA,RXC)));
	/* Get and return received data from buffer */
	*Copy_u8Data = UART_u8UDR;
	return Local_u8Status;
}
/*Comment!: Transmit a String to the UART */
extern u8 UART_u8TransmitString(u8 *Copy_u8String){
	u8 Local_u8Status = u8OK;
	while(*(Copy_u8String))
	{
		UART_u8TransmitOneByte(*Copy_u8String++);
	}
	return Local_u8Status;
}
