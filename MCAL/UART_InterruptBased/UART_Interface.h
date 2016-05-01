/*
 * UART_interface.h
 *
 *  Created on: Jan 27, 2016
 *      Author: Kareem Galal
 */

#ifndef _UART_INTERFACE_H_
#define _UART_INTERFACE_H_

/*******************************************************/
/***************** Public Definitions  *****************/
/*******************************************************/

/*******************************************************/
/***************** Public Functions ********************/
/*******************************************************/

/*Comment!: UART Initialization */
extern void UART_voidInit(void);
/*Comment!: UART Enable */
extern void UART_voidEnable(void);
/*Comment!: Flush bytes waiting the receive buffer. */
extern void UART_voidFlush();
/*Comment!: UART Disable */
extern void UART_voidDisable(void);
/*Comment!: UART Available Bytes */
extern u16 UART_u16AvailableBytes(void);
/*Comment!: Transmit One Byte to the UART*/
extern u8 UART_u8WriteOneByte(u8 Copy_u8Data);
/*Comment!: Receive One Byte from the UART */
extern u8 UART_u8ReadOneByte(u8 *Copy_u8Data);
/*Comment!: Transmit a String to the UART */
extern u8 UART_u8TransmitString(u8 *Copy_u8String);


#endif /* _UART_INTERFACE_H_ */
