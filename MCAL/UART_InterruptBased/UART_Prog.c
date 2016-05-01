/*
 * UART_prog.c
 *
 *  Created on: Jan 27, 2016
 *      Author: Kareem Galal
 */

#include "..\..\Utilities\Types.h"
#include "..\..\Utilities\Util.h"
#include "UART_Config.h"
#include "UART_Private.h"
#include "UART_Interface.h"

static volatile u8 UART_RX_Buffer_Head;
static volatile u8 UART_RX_Buffer_Tail;
static volatile u8 UART_TX_Buffer_Head;
static volatile u8 UART_TX_Buffer_Tail;

static u8 UART_RX_Buffer[SERIAL_RX_BUFFER_SIZE];
static u8 UART_TX_Buffer[SERIAL_TX_BUFFER_SIZE];

ISR(USART_RXC_vect) {
	//_rx_complete_irq();
//if (bit_is_clear(UART_u8UCSRA, FE)){
	if (GET_BIT(UART_u8UCSRA, FE)) { // if one so Parity error, read byte but discard it
		UART_u8UDR;
	} else {
		// No Parity error, read byte and store it in the buffer if there is
		// room
		//u8 c = UART_u8UDR;
		u8 Local_u8Index = (UART_RX_Buffer_Head + 1) % SERIAL_RX_BUFFER_SIZE;

		// if we should be storing the received character into the location
		// just before the tail (meaning that the head would advance to the
		// current location of the tail), we're about to overflow the buffer
		// and so we don't write the character or advance the head.
		if (Local_u8Index != UART_RX_Buffer_Tail) {
			UART_RX_Buffer[UART_RX_Buffer_Head] = UART_u8UDR;
			UART_RX_Buffer_Head = Local_u8Index;
		}
	}
}
ISR(USART_UDRE_vect) {
	//_tx_udr_empty_irq();

	u8 Local_u8Data = UART_TX_Buffer[UART_TX_Buffer_Tail];
	UART_TX_Buffer_Tail = (UART_TX_Buffer_Tail + 1) % SERIAL_TX_BUFFER_SIZE;

	/* Put data into buffer, sends the data */
	UART_u8UDR = Local_u8Data;

	// clear the TXC bit -- "can be cleared by writing a one to its bit
	// location". This makes sure flush() won't return until the bytes
	// actually got written
	SET_BIT(UART_u8UCSRA, TXC);

	if (UART_TX_Buffer_Head == UART_TX_Buffer_Tail) {
		// Buffer empty, so disable interrupts
		CLR_BIT(UART_u8UCSRB, UDRIE);
	}
}
/*Comment!: UART Initialization */
extern void UART_voidInit(void) {

	// Try u2x mode first
	// uint16_t baud_setting = (F_CPU / 4 / baud - 1) / 2;
	// *_ucsra = 1 << U2X0;
	// Adjust the BaudRate
	UART_u8UBRRH = (u8) (UART_u16UBRR_VALUE >> 8);
	UART_u8UBRRL = (u8) UART_u16UBRR_VALUE;

	UART_u8UCSRC = UART_u8CONFIGURATION; //Assign the desired configuration

	//UART_voidEnable();
	SET_BIT(UART_u8UCSRB, RXEN);//Rx Enable
	SET_BIT(UART_u8UCSRB, TXEN);	//Tx Enable
	SET_BIT(UART_u8UCSRB, RXCIE); //UART RX Complete Interrupt Enable
	//SET_BIT(UART_u8UCSRB, UDRIE); //UART Data Register Empty Interrupt Enable
	return;
}
/*Comment!: UART Enable */
extern void UART_voidEnable(void) {
	/* Enable receiver and transmitter */
	//UCSRB = (1<<RXEN)|(1<<TXEN);
	SET_BIT(UART_u8UCSRB, RXEN); //Rx Enable
	SET_BIT(UART_u8UCSRB, TXEN);	//Tx Enable
	SET_BIT(UART_u8UCSRB, RXCIE); //UART RX Complete Interrupt Enable
	//CLR_BIT(UART_u8UCSRB,UDRIE); //UART Data Register Empty Interrupt Enable
	return;
}
/*Comment!: Flush bytes waiting the receive buffer. */
extern void UART_voidFlush() {
	// If we have never written a byte, no need to flush. This special
	// case is needed since there is no way to force the TXC (transmit
	// complete) bit to 1 during initialization
	// if (!_written)
	// return;

	// while (bit_is_set(*_ucsrb, UDRIE0) || bit_is_clear(*_ucsra, TXC0)) {
	// if (bit_is_clear(SREG, SREG_I) && bit_is_set(*_ucsrb, UDRIE0))
	// Interrupts are globally disabled, but the DR empty
	// interrupt should be enabled, so poll the DR empty flag to
	// prevent deadlock
	// if (bit_is_set(*_ucsra, UDRE0))
	// _tx_udr_empty_irq();
	// }
	while (UART_TX_Buffer_Head != UART_TX_Buffer_Tail) {
		SET_BIT(UART_u8UCSRB, UDRIE);
	}
	// If we get here, nothing is queued anymore (DRIE is disabled) and
	// the hardware finished tranmission (TXC is set).
}
/*Comment!: UART Disable */
extern void UART_voidDisable(void) {
	// wait for transmission of outgoing data
	UART_voidFlush();

	//UCSRB &= ~((1<<RXEN)|(1<<TXEN));
	CLR_BIT(UART_u8UCSRB, RXEN);//Rx Disable
	CLR_BIT(UART_u8UCSRB, TXEN);	//Tx Disable
	CLR_BIT(UART_u8UCSRB, RXCIE); //UART RX Complete Interrupt Disable
	//CLR_BIT(UART_u8UCSRB,UDRIE); //UART Data Register Empty Interrupt Enable

	// clear any received data
	UART_RX_Buffer_Head = UART_RX_Buffer_Tail;

	return;
}
/*Comment!: UART Available Bytes */
extern u16 UART_u16AvailableBytes(void) {
	//u16 Local_u16AvailableBytes = 
	//return how many bytes are available to read
	return ((u16) (SERIAL_RX_BUFFER_SIZE + UART_RX_Buffer_Head
			- UART_RX_Buffer_Tail)) % SERIAL_RX_BUFFER_SIZE;
}
/*Comment!: Transmit One Byte to the UART*/
extern u8 UART_u8WriteOneByte(u8 Copy_u8Data) {
	u8 Local_u8Status = u8OK;
	//_written = TRUE;
	// If the buffer and the data register is empty, just write the byte
	// to the data register and be done. 
	if (UART_TX_Buffer_Head
			== UART_TX_Buffer_Tail&& GET_BIT(UART_u8UCSRA,UDRE)) {
		/* Put data into buffer, sends the data */
		UART_u8UDR = Copy_u8Data;
		// clear the TXC bit -- "can be cleared by writing a one to its bit
		// location"
		SET_BIT(UART_u8UCSRA, TXC);
	} else {
		u8 Local_u8Index = (UART_TX_Buffer_Head + 1) % SERIAL_TX_BUFFER_SIZE;
		// If the output buffer is full, there's nothing for it other than to 
		// wait for the interrupt handler to empty it a bit
		while (Local_u8Index == UART_TX_Buffer_Tail) {
			SET_BIT(UART_u8UCSRB, UDRIE); //UART Data Register Empty Interrupt Enable
			// if (bit_is_clear(SREG, SREG_I)) { ??
			// Interrupts are disabled, so we'll have to poll the data
			// register empty flag ourselves. If it is set, pretend an
			// interrupt has happened and call the handler to free up
			// space for us.
			// if(GET_BIT(UART_u8UCSRA,UDRE))
			// _tx_udr_empty_irq();
		}
		UART_TX_Buffer[UART_TX_Buffer_Head] = Copy_u8Data;
		UART_TX_Buffer_Head = Local_u8Index;
		SET_BIT(UART_u8UCSRB, UDRIE); //UART Data Register Empty Interrupt Enable
	}
	return Local_u8Status;
}
/*Comment!: Receive One Byte from the UART */
extern u8 UART_u8ReadOneByte(u8 *Copy_u8Data) {
	u8 Local_u8Status = u8OK;
	// if the head isn't ahead of the tail, we don't have any characters
	if (UART_RX_Buffer_Head == UART_RX_Buffer_Tail) {
		Local_u8Status = u8ERROR;
	} else {
		*Copy_u8Data = UART_RX_Buffer[UART_RX_Buffer_Tail];
		UART_RX_Buffer_Tail = (UART_RX_Buffer_Tail + 1) % SERIAL_RX_BUFFER_SIZE;
	}
	return Local_u8Status;
}
/*Comment!: Transmit a String to the UART */
extern u8 UART_u8TransmitString(u8 *Copy_u8String) {
	u8 Local_u8Status = u8OK;
	while (*(Copy_u8String)) {
		UART_u8WriteOneByte(*Copy_u8String++);
	}
	return Local_u8Status;
}
