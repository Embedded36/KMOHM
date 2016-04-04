/*
 main.c

 Created on: Feb 1, 2016
 Author: KiMo
 */

#include "..\Utilities\Types.h"
#include "..\Utilities\Util.h"
#include "..\Utilities\Delay.h"
#include "..\MCAL\SPI\SPI_Interface.h"

int main(void) {
	SPI_voidInit();
	while (1) {
		u8 Local_u8RxData;
		SPI_u8Transfer('A', &Local_u8RxData);
		voidDELAY_MS(1000);
		SPI_u8Transfer('B', &Local_u8RxData);
		voidDELAY_MS(1000);
		SPI_u8Transfer(Local_u8RxData, &Local_u8RxData);
	}
	return 0;
}
