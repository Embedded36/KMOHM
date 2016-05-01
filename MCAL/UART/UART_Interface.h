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
/*Comment!: UART Disable */
extern void UART_voidDisable(void);
/*Comment!: Read UART on a specific channel, just one shot */
extern u8 UART_u8TransmitOneByte(u8 Copy_u8Data);
/*Comment!: Read UART on a specific channel, Filtered Reading */
extern u8 UART_u8ReceiveOneByte(u8 *Copy_u8Data);
/*Comment!: Read UART on a specific channel, Filtered Reading */
extern u8 UART_u8TransmitString(u8 *Copy_u8String);

#endif /* _UART_INTERFACE_H_ */
