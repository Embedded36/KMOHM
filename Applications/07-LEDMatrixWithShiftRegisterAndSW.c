/*
 * main.c
 *
 *  Created on: Feb 1, 2016
 *      Author: KiMo
 */

#include "Utilities\Types.h"
#include "Utilities\Delay.h"
#include "MCAL\DIO\DIO_Interface.h"
#include "HAL\74HC595\74HC595_Interface.h"
#include "HAL\TSW\TSW_Interface.h"

#define	LEDMATRIX		HC595_u8NUM1

static const u8 MyName[6][8] = {
		{ 0xBB,0xB7,0xAF,0x9F,0x9F,0xAF,0xB7,0xBB }, //K
		{ 0xE7,0xDB,0xBD,0xBD,0x81,0xBD,0xBD,0xBD }, //A
		{ 0xFF,0x87,0xB7,0x87,0xAF,0xB7,0xBB,0xBD }, //R
		{ 0x83,0xBF,0xBF,0x83,0xBF,0xBF,0xBF,0x83 }, //E
		{ 0x83,0xBF,0xBF,0x83,0xBF,0xBF,0xBF,0x83 }, //E
		{ 0xBD,0x99,0xA5,0xBD,0xBD,0xBD,0xBD,0xBD } }; //M
static const u8 Row_Num[] = {1, 2, 4, 8, 16, 32, 64, 128}; // Rows Number

int main(void) {
	u8 Local_u8Row;	//Row Number ?
	u8 Local_u8Character=0;
	u8 Local_u8SwitchValue=TSW_u8RELEASED;	//To store the switch value
	u8 local_u8SwitchPressed = FALSE; //flag to run the SW in the single mode
	DIO_voidInit();
	HC595_voidInit();
	TSW_voidInit();
    /************************** Turn On 1st LED ***************************/
	 HC595_u8WriteByte(LEDMATRIX, 0x7F);//column
	 HC595_u8WriteByte(LEDMATRIX, 1);//row
	 HC595_u8LatchPulse(LEDMATRIX);
	voidDELAY_MS(2000);	// Delay 2 Sec
    /************************** Turn On 2nd LED ***************************/
	HC595_u8WriteByte(LEDMATRIX, 0xBF);//column
	  HC595_u8WriteByte(LEDMATRIX, 2);//row
	  HC595_u8LatchPulse(LEDMATRIX);
	voidDELAY_MS(2000);	//Delay 2 Sec

	while (1) {

		for (Local_u8Row = 0; Local_u8Row < 8; Local_u8Row++)
		  {
		    /************To increase the ON time of LEDs ten times more than
		      OFF time to increase the brightness of LEDs*************/
//		    for (Local_u8Brightness = 0; Local_u8Brightness < 10; Local_u8Brightness++)
//		    {
		      /*************************  TURN ON DIAGONAL LEDs ONLY  ***************************/
		      HC595_u8WriteByte(LEDMATRIX, MyName[Local_u8Character][Local_u8Row]); //column
		      HC595_u8WriteByte(LEDMATRIX, Row_Num[Local_u8Row]);//row
		      HC595_u8LatchPulse(LEDMATRIX);

//		    }
		    /**************************  TURN OFF ALL LEDs  ***************************/

//		    // take the latchPin low so the LEDs don't change while you're sending in bits:
//		    HC595_u8WriteByte(LEDMATRIX, 255);//column
//		    HC595_u8WriteByte(LEDMATRIX, 0);//row
//		    HC595_u8LatchPulse(LEDMATRIX);
		  }

		TSW_u8CheckSwitch(TSW_u8NUM1, &Local_u8SwitchValue);
		//DIO_u8ReadPinVal(DIO_u8PIN31, &Local_u8SwitchValue);
		if (Local_u8SwitchValue == TSW_u8PRESSED) {
			if (!local_u8SwitchPressed) {
				local_u8SwitchPressed = TRUE;
				Local_u8Character++; // increment the counter
				if (Local_u8Character > 5) {
					Local_u8Character = 0;
				}
			}
		} else {
			if (local_u8SwitchPressed) {
				local_u8SwitchPressed = FALSE;
			}
		}
	}
	return 0;
}
