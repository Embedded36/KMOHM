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
/*Comment!: Read SPI on a specific channel, just one shot */
extern u8 SPI_u8TransmitOneByte(u8 Copy_u8Data);
/*Comment!: Read SPI on a specific channel, Filtered Reading */
extern u8 SPI_u8ReceiveOneByte(u8 *Copy_u8Data);
/*Comment!: Read SPI on a specific channel, Filtered Reading */
extern u8 SPI_u8TransmitString(u8 *Copy_u8String);

#endif /* _SPI_INTERFACE_H_ */
