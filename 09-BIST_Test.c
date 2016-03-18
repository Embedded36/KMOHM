/*
 * main.c
 *
 *  Created on: Feb 1, 2016
 *      Author: KiMo
 */

#include "Utilities\Types.h"
#include "Utilities\Delay.h"
#include "MCAL\DIO\DIO_Interface.h"
#include "HAL\BIST\BIST_Interface.h"

int main(void) {
	DIO_voidInit();
	while (1) {
		BIST_u8Begin();
	}
	return 0;
}
