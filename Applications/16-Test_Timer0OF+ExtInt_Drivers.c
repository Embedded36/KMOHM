#include "..\Utilities\Types.h"
#include "..\Utilities\Delay.h"
#include "..\MCAL\DIO\DIO_Interface.h"
#include "..\MCAL\TIMER\TIMER_Interface.h"
#include "..\MCAL\EXTINT\EXTINT_Interface.h"
#define OneSec	(1953)
volatile u8 LEDFlag = 0;

void ToggleLedStatus(void) {
		LEDFlag = !LEDFlag;
}

int main(void) {
	u32 Timer0_u32OverFlowNum;
	u8 SignalFlag = 0;

	__asm__("SEI");

	EXTINT_voidInit();
	EXTINT_u8AttachInt(EXTINT0, ToggleLedStatus);
	TIMER0_voidInit();

	DIO_u8WritePinDir(26, DIO_u8INPUT);
	DIO_u8WritePinDir(8, DIO_u8OUTPUT);
	DIO_u8WritePinDir(9, DIO_u8OUTPUT);
	DIO_u8WritePinVal(9, SignalFlag);

	while (1) {
		DIO_u8WritePinVal(8, LEDFlag);
		Timer0_u32OverFlowNum = TIMER0_u32GetOverflowCount();
		if (Timer0_u32OverFlowNum == OneSec) {
			TIMER0_voidClearOverflowCount();
			SignalFlag = !SignalFlag;
			DIO_u8WritePinVal(9, SignalFlag);
		}
	}
	return 0;
}
