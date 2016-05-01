/*
   LCD_Private.h

    Created on: Feb 22, 2016
        Author: Kareem Galal
*/

#ifndef _LCD_PRIVATE_H_
#define _LCD_PRIVATE_H_

/*******************************************************/
/**************** Private Definitions ******************/
/*******************************************************/


/*Comment!: LCD Registers */
#define LCD_ENTRYMODESET	0x04
#define LCD_DISPLAYCONTROL	0x08
#define LCD_CURSORSHIFT		0x10
#define LCD_FUNCTIONSET		0x20
#define LCD_SETCGRAMADD		0x40
#define LCD_SETDDRAMADDR	0x80

/*Comment!: flags for function set */
#define LCD_8BITMODE		0x10
#define LCD_4BITMODE		0x00
#define LCD_2LINE			0x08
#define LCD_1LINE			0x00
#define LCD_5x10DOTS		0x04
#define LCD_5x8DOTS			0x00

/*Comment!: flags for display on/off control */
#define LCD_DISPLAYON		0x04
#define LCD_DISPLAYOFF		0x00
#define LCD_CURSORON		0x02
#define LCD_CURSOROFF		0x00
#define LCD_BLINKON			0x01
#define LCD_BLINKOFF		0x00

/*Comment!: flags for display entry mode */
#define LCD_ENTRYRIGHT 			0x00
#define LCD_ENTRYLEFT 			0x02
#define LCD_ENTRYSHIFTON		0x01
#define LCD_ENTRYSHIFTOFF		0x00

/*Comment!: Numbers*/
#define LCD_u8NUM_ZERO	0
#define LCD_u8NUM_ONE	1
#define LCD_u8NUM_FOUR	4
#define LCD_u8NUM_EIGHT	8

#define WRITE_DATA		DIO_u8HIGH
#define WRITE_COMMAND	DIO_u8LOW

#define FUNCTIONSET		(LCD_FUNCTIONSET | LCD_MODE | LCD_LINES | LCD_CHAR_SHAPE) //Function Set: 4-bit, 2 Line, 5x8 DOTS >> 0x28
#define DISPLAYCONTROL  (LCD_DISPLAYCONTROL | LCD_DISPLAY_STATE | LCD_CURSOR_STATE | LCD_BLINK_STATE) // Display ON/OFF Control Display on Cursor off >> 0x0C
#define ENTRYMODESET	(LCD_ENTRYMODESET | LCD_ENTRY_DIR | LCD_ENTRYSHIFT_STATE)	//Entry Mode Set, Automatic Increment - No Display shift >> 0x06

/*******************************************************/
/*****************  Private Functions  *****************/
/*******************************************************/

/*Comment!: */

#endif	/* _LCD_PRIVATE_H_ */
