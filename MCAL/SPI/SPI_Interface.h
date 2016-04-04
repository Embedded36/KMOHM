/*
 * SPI_interface.h
 *
 *  Created on: Jan 27, 2016
 *      Author: Kareem Galal
 */

#ifndef _SPI_INTERFACE_H_
#define _SPI_INTERFACE_H_

/*******************************************************/
/***************** Public Definitions  *****************/
/*******************************************************/


/*******************************************************/
/***************** Public Functions ********************/
/*******************************************************/

/*Comment!: SPI Initialization */
extern void SPI_voidInit(void);
/*Comment!: SPI Enable */
extern void SPI_voidEnable(void);
/*Comment!: SPI Disable */
extern void SPI_voidDisable(void);
/*Comment!: Transmit & Receive One Byte to/From the SPI*/
extern u8 SPI_u8Transfer(u8 Copy_u8TxData, u8 *Copy_u8RxData);
/*Comment!:  Transmit & Receive a String to/From the SPI*/
extern u8 SPI_u8TransferString(u8 *Copy_u8TxString, u8 *Copy_u8RxString);

#endif /* _SPI_INTERFACE_H_ */
