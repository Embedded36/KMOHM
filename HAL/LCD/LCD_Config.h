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
#define LCD_DATA0	 		DIO_u8PIN24
#define LCD_DATA1    		DIO_u8PIN25
#define LCD_DATA2    		DIO_u8PIN26
#define LCD_DATA3    		DIO_u8PIN27
#define LCD_DATA4    		DIO_u8PIN28
#define LCD_DATA5    		DIO_u8PIN29
#define LCD_DATA6    		DIO_u8PIN30
#define LCD_DATA7    		DIO_u8PIN31

/*Comment!: Data Bus Pins */
/*Range!  : DIO_u8PIN0 : DIO_u8PIN31 */
#define LCD_RS			 	DIO_u8PIN21
#define LCD_RW           	DIO_u8PIN22
#define LCD_ENABLE       	DIO_u8PIN23

/*Comment!: LCD Mode */
/*Range!  : LCD_8BITMODE or LCD_4BITMODE */
#define LCD_MODE				LCD_4BITMODE

/*Comment!: LCD Number of Lines */
/*Range!  : LCD_1LINE or LCD_2LINE */
#define LCD_LINES				LCD_2LINE

/*Comment!: LCD Char Shape */
/*Range!  : LCD_5x10DOTS or LCD_5x8DOTS */
#define LCD_CHAR_SHAPE			LCD_5x8DOTS

/*Comment!: Intial state for LCD Display */
/*Range!  : LCD_DISPLAYON or LCD_DISPLAYOFF */
#define LCD_DISPLAY_STATE		LCD_DISPLAYON

/*Comment!: Intial state for LCD Cursor */
/*Range!  : LCD_CURSORON or LCD_CURSOROFF */
#define LCD_CURSOR_STATE		LCD_CURSOROFF

/*Comment!: Intial state for LCD BLINK */
/*Range!  : LCD_BLINKON or LCD_BLINKOFF */
#define LCD_BLINK_STATE			LCD_BLINKOFF

/*Comment!: LCD ENTRY Direction */
/*Range!  : LCD_ENTRYRIGHT or LCD_ENTRYLEFT */
#define LCD_ENTRY_DIR			LCD_ENTRYLEFT

/*Comment!: Intial state for LCD ENTRY SHIFT */
/*Range!  : LCD_ENTRYSHIFTON or LCD_ENTRYSHIFTOFF */
#define LCD_ENTRYSHIFT_STATE	LCD_ENTRYSHIFTOFF



#endif	/* _LCD_CONFIG_H_ */
