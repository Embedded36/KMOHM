/*
   LCD_Interface.h

    Created on: Feb 22, 2016
        Author: Kareem Galal
*/

#ifndef _LCD_INTERFACE_H_
#define _LCD_INTERFACE_H_

/*******************************************************/
/***************** Public Definitions ******************/
/*******************************************************/

/*Comment!: LCD Commands */
#define LCD_CLEARDISPLAY 0x01
#define LCD_RETURNHOME 	 0x02


/*******************************************************/
/*****************  Public Functions  ******************/
/*******************************************************/

/*Comment!: Function to Write Command to the LCD*/
extern void LCD_u8Write_Command(u8 Copy_u8Command);
/*Comment!: Function to Write Data on the LCD*/
extern void LCD_u8Write_Data(u8 Copy_u8Data);
/*Comment!: Function to Write String on the LCD*/
extern void LCD_u8Write_String(const u8 *Copy_u8StringOfCharacters);
/*Comment!: Initialize the LCD16*2*/
extern void LCD_voidInit(void);

#endif	/* _LCD_INTERFACE_H_ */
