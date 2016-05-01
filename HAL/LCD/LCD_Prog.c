/*
 LCD_Prog.c

 Created on: Feb 22, 2016
 Author: Kareem Galal
 */

#include "..\..\Utilities\Types.h"
#include "..\..\Utilities\Util.h"
#include "..\..\Utilities\Delay.h"
#include "..\..\MCAL\DIO\DIO_Interface.h"
#include "LCD_Private.h"
#include "LCD_Config.h"
#include "LCD_Interface.h"


#if (LCD_MODE == LCD_4BITMODE)
static const u8 LCD_u8DataPins[LCD_u8NUM_FOUR] = { LCD_DATA4, LCD_DATA5, LCD_DATA6, LCD_DATA7 };
#else
static const u8 LCD_u8DataPins[LCD_u8NUM_EIGHT] = {LCD_DATA0, LCD_DATA1, LCD_DATA2, LCD_DATA3, LCD_DATA4, LCD_DATA5, LCD_DATA6, LCD_DATA7};
#endif

/*Comment!: Function to Write Command/Data to the LCD*/
static void LCD_u8Write(u8 Copy_u8Value, u8 Copy_u8Mode) {
	u8 Local_u8LoopIndex;
	DIO_u8WritePinVal(LCD_RS, Copy_u8Mode);
	DIO_u8WritePinVal(LCD_RW, DIO_u8LOW);

#if (LCD_MODE == LCD_4BITMODE)
	for (Local_u8LoopIndex = LCD_u8NUM_ZERO; Local_u8LoopIndex < LCD_u8NUM_FOUR;
			Local_u8LoopIndex++) {
		DIO_u8WritePinVal(LCD_u8DataPins[Local_u8LoopIndex],
				GET_BIT(Copy_u8Value, Local_u8LoopIndex));
	}
#else
	for (Local_u8LoopIndex = LCD_u8NUM_ZERO; Local_u8LoopIndex < LCD_u8NUM_EIGHT; Local_u8LoopIndex++) {
		DIO_u8WritePinVal(LCD_u8DataPins[Local_u8LoopIndex],GET_BIT(Copy_u8Value,Local_u8LoopIndex));
	}
#endif
	DIO_u8WritePinVal(LCD_ENABLE, DIO_u8HIGH);   // enable pulse must be >450ns
	//voidDELAY_MS(1);
	DIO_u8WritePinVal(LCD_ENABLE, DIO_u8LOW); // commands need > 37us to settle
	//voidDELAY_MS(1); // >100 US
}

/*Comment!: Function to Write Command to the LCD*/
extern void LCD_u8Write_Command(u8 Copy_u8Command) {

#if (LCD_MODE == LCD_4BITMODE)
	LCD_u8Write(GET_HIGH_NIB(Copy_u8Command), WRITE_COMMAND);
	LCD_u8Write(GET_LOW_NIB(Copy_u8Command), WRITE_COMMAND);
#else
	LCD_u8Write(Copy_u8Command, WRITE_COMMAND);
#endif
	return;
}

/*Comment!: Function to Write Data on the LCD*/
extern void LCD_u8Write_Data(u8 Copy_u8Data) {
#if (LCD_MODE == LCD_4BITMODE)
	LCD_u8Write(GET_HIGH_NIB(Copy_u8Data), WRITE_DATA);
	LCD_u8Write(GET_LOW_NIB(Copy_u8Data), WRITE_DATA);
#else
	LCD_u8Write(Copy_u8Data, WRITE_DATA);
#endif
	return;
}

extern void LCD_u8Write_String(const u8 *Copy_u8StringOfCharacters) {
	while (*Copy_u8StringOfCharacters > 0) {
		LCD_u8Write_Data(*(Copy_u8StringOfCharacters++));
	}
}

  /********** high level commands, for the user! */
void LCD_voidClearDisplay(){
  // command(LCD_CLEARDISPLAY);  // clear display, set cursor position to zero
  // delayMicroseconds(2000);  // this command takes a long time!
}

void LCD_voidReturnHome(){
  // command(LCD_RETURNHOME);  // set cursor position to zero
  // delayMicroseconds(2000);  // this command takes a long time!
}

// Turn the display off (quickly)
void LCD_voidDisplayOff() {
  
}

void LCD_voidDisplayOn() {
  // _displaycontrol |= LCD_DISPLAYON;
  // command(LCD_DISPLAYCONTROL | _displaycontrol);
}

// Turns the underline cursor on/off
void LCD_voidCursorOff() {
  // _displaycontrol &= ~LCD_CURSORON;
  // command(LCD_DISPLAYCONTROL | _displaycontrol);
}
void LCD_voidCursorOn() {
  // _displaycontrol |= LCD_CURSORON;
  // command(LCD_DISPLAYCONTROL | _displaycontrol);
}
// Turn on and off the blinking cursor
void LCD_voidBlinkOff() {
  // _displaycontrol &= ~LCD_BLINKON;
  // command(LCD_DISPLAYCONTROL | _displaycontrol);
}
void LCD_voidBlinkOn() {
  // _displaycontrol |= LCD_BLINKON;
  // command(LCD_DISPLAYCONTROL | _displaycontrol);
}
// This is for text that flows Left to Right
void LCD_voidleftToRight(void) {
  // _displaymode |= LCD_ENTRYLEFT;
  // command(LCD_ENTRYMODESET | _displaymode);
}
// This is for text that flows Right to Left
void LCD_voidrightToLeft(void) {
  // _displaymode &= ~LCD_ENTRYLEFT;
  // command(LCD_ENTRYMODESET | _displaymode);
}
// Allows us to fill the first 8 CGRAM locations
// with custom characters
void LCD_voidcreateChar(u8 location, u8 charmap[]) {
  // location &= 0x7; // we only have 8 locations 0-7
  // command(LCD_SETCGRAMADDR | (location << 3));
  // for (int i=0; i<8; i++) {
    // write(charmap[i]);
  // }
}

/*Comment!: Initialize the LCD 16*2*/
extern void LCD_voidInit(void) {
	voidDELAY_MS(15);
#if (LCD_MODE == LCD_4BITMODE)
	LCD_u8Write(0x3, WRITE_COMMAND);
	voidDELAY_MS(5);//>4.1
	LCD_u8Write(0x3, WRITE_COMMAND);
	voidDELAY_MS(1);// >100 US
	LCD_u8Write(0x3, WRITE_COMMAND);
	LCD_u8Write(0x2, WRITE_COMMAND);
	LCD_u8Write_Command(FUNCTIONSET);    //Function Set: 4-bit, 2 Line, 5x8 DOTS >> 0x28
	LCD_u8Write_Command(DISPLAYCONTROL); // Display ON/OFF Control Display on Cursor off >> 0x0C
	LCD_u8Write_Command(ENTRYMODESET);	//Entry Mode Set, Automatic Increment - No Display shift >> 0x06
#else
	//in  8-bit mode
	LCD_u8Write_Command(0x30);
	voidDELAY_MS(5);//>4.1
	LCD_u8Write_Command(0x30);
	voidDELAY_MS(1);// >100 US
	LCD_u8Write_Command(0x30);
	voidDELAY_MS(1);// >100 US
	LCD_u8Write_Command(FUNCTIONSET);//Function Set: 8-bit, 2 Line, 5x8 Dots >> 0x38
	LCD_u8Write_Command(DISPLAYCONTROL); // Display ON/OFF Control Display on Cursor off >> 0x0C
	LCD_u8Write_Command(ENTRYMODESET);	//Entry Mode Set, Automatic Increment - No Display shift >> 0x06

#endif	
	//	LCD_cmd(0x80);        // ---8 go to first line and --0 is for 0th position

}
