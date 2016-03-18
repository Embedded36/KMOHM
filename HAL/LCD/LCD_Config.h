/*
   LCD_Config.h

    Created on: Feb 22, 2016
        Author: Kareem Galal
*/


#ifndef _LCD_CONFIG_H_
#define _LCD_CONFIG_H_

/*******************************************************/
/**************** Public Definitions *******************/
/*******************************************************/

/*Comment!: Data Bus Pins */
/*Range!  : DIO_u8PIN0 : DIO_u8PIN31 */
#define LCD_DATA0	 DIO_u8PIN24
#define LCD_DATA1    DIO_u8PIN25
#define LCD_DATA2    DIO_u8PIN26
#define LCD_DATA3    DIO_u8PIN27
#define LCD_DATA4    DIO_u8PIN28
#define LCD_DATA5    DIO_u8PIN29
#define LCD_DATA6    DIO_u8PIN30
#define LCD_DATA7    DIO_u8PIN31

/*Comment!: Data Bus Pins */
/*Range!  : DIO_u8PIN0 : DIO_u8PIN31 */
#define LCD_RS			 DIO_u8PIN21
#define LCD_RW           DIO_u8PIN22
#define LCD_ENABLE       DIO_u8PIN23


#endif	/* _LCD_CONFIG_H_ */
