/*
 main.c

 Created on: Feb 1, 2016
 Author: KiMo
 */

#include "..\Utilities\Types.h"
//#include "..\Utilities\Delay.h"
#include "..\MCAL\UART\UART_Interface.h"

int main(void) {
	u8 data;
	UART_voidInit();
	__asm__("SEI");
	UART_u8TransmitString("Hello,\r\nit's me, Kimo\r\n");
	while (1) {
		if(UART_u16AvailableBytes()>0)
		{
			UART_u8ReadOneByte(&data);
			UART_u8WriteOneByte(data);
		}
		//UART_u8TransmitOneByte("K");
		//UART_u8TransmitString("KiMo\r\n");
		//voidDELAY_MS(1000);
	}
	return 0;
}
