/*
 main.c

 Created on: Feb 1, 2016
 Author: KiMo
 */
#include "..\Utilities\Types.h"
#include "..\Utilities\Delay.h"
#include "..\MCAL\DIO\DIO_Interface.h"
#include "..\HAL\LCD\LCD_Interface.h"

int main(void) {
	DIO_voidInit();
	LCD_voidInit();
	//LCD_u8Write_Data('H');
	LCD_u8Write_String("Hello, World");
	//LCD_u8Write_String("KiMo");
	//LCD_u8Write_Command(0x40);
	while (1) {
	}
	return 0;
}
