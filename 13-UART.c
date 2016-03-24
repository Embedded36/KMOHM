/*
 main.c

 Created on: Feb 1, 2016
 Author: KiMo
 */

#include "Utilities\Types.h"
#include "Utilities\Delay.h"
#include "MCAL\UART\UART_Interface.h"

int main(void) {
	UART_voidInit();
	while (1) {
		//UART_u8TransmitOneByte("K");
		UART_u8TransmitString("KiMo\n");
	}
	return 0;
}
