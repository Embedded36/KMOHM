/*
 BIST_Prog.c

 Created on: Feb 22, 2016
 Author: Kareem Galal
 */

#include "..\..\Utilities\Types.h"
#include "..\..\MCAL\DIO\DIO_interface.h"
#include "BIST_Config.h"
#include "BIST_Private.h"
#include "BIST_Interface.h"

/*Comment!: Begin the BIST (Buit-In Selt Test)*/
extern u8 BIST_u8Begin(void){
	u8 Local_u8RetrunStatus;
	    u8 Local_u8ControlPins;
		DIO_u8ReadPortVal(DIO_u8PORT0, &Local_u8ControlPins); //Read Port A
		switch ((Local_u8ControlPins &0x03)) { //check only on pin1 & pin0
		case 0:
			DIO_u8WritePortVal(DIO_u8PORT0, (BIST_u8PATTERN1&0xFC)); //Write Pattern 1 to Port 0, don't put 1 for pin0,1 as they are conrol pins
			DIO_u8WritePortVal(DIO_u8PORT1, BIST_u8PATTERN1);
			DIO_u8WritePortVal(DIO_u8PORT2, BIST_u8PATTERN1);
			DIO_u8WritePortVal(DIO_u8PORT3, BIST_u8PATTERN1);
			Local_u8RetrunStatus = u8OK;
			break;
		case 1:
			DIO_u8WritePortVal(DIO_u8PORT0, ((BIST_u8PATTERN2&0xFC)|0x01)); //Write Pattern 1 to Port 0, don't put 1 for pin0,1 as they are conrol pins
			DIO_u8WritePortVal(DIO_u8PORT1, BIST_u8PATTERN2);
			DIO_u8WritePortVal(DIO_u8PORT2, BIST_u8PATTERN2);
			DIO_u8WritePortVal(DIO_u8PORT3, BIST_u8PATTERN2);
			Local_u8RetrunStatus = u8OK;
			break;
		case 2:
			DIO_u8WritePortVal(DIO_u8PORT0, ((BIST_u8PATTERN3&0xFC)|0x02)); //Write Pattern 1 to Port 0, don't put 1 for pin0,1 as they are conrol pins
			DIO_u8WritePortVal(DIO_u8PORT1, BIST_u8PATTERN3);
			DIO_u8WritePortVal(DIO_u8PORT2, BIST_u8PATTERN3);
			DIO_u8WritePortVal(DIO_u8PORT3, BIST_u8PATTERN3);
			Local_u8RetrunStatus = u8OK;
			break;
		case 3:
			DIO_u8WritePortVal(DIO_u8PORT0, ((BIST_u8PATTERN4&0xFC)|0x03)); //Write Pattern 1 to Port 0, don't put 1 for pin0,1 as they are conrol pins
			DIO_u8WritePortVal(DIO_u8PORT1, BIST_u8PATTERN4);
			DIO_u8WritePortVal(DIO_u8PORT2, BIST_u8PATTERN4);
			DIO_u8WritePortVal(DIO_u8PORT3, BIST_u8PATTERN4);
			Local_u8RetrunStatus = u8OK;
			break;
		default:
			Local_u8RetrunStatus = u8ERROR;
			break;
		}
	return Local_u8RetrunStatus;
}

/*Comment!: Initialize the Tactile_Switch*/
extern void BIST_voidInit(void) {
/*Comment!: Write Port Direction */
/* DIO_u8WritePortDir(DIO_u8PORT0, (DIO_u8PORTHIGH&0xFC));
DIO_u8WritePortDir(DIO_u8PORT1, DIO_u8PORTHIGH);
DIO_u8WritePortDir(DIO_u8PORT2, DIO_u8PORTHIGH);
DIO_u8WritePortDir(DIO_u8PORT3, DIO_u8PORTHIGH); */
/*Comment!: Write Port Value */
/* DIO_u8WritePortVal(DIO_u8PORT0, DIO_u8PORTLOW);
DIO_u8WritePortVal(DIO_u8PORT1, DIO_u8PORTLOW);
DIO_u8WritePortVal(DIO_u8PORT2, DIO_u8PORTLOW);
DIO_u8WritePortVal(DIO_u8PORT3, DIO_u8PORTLOW); */
}

