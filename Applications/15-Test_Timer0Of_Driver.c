#include "..\Utilities\Types.h"
#include "..\Utilities\Delay.h"
#include "..\MCAL\DIO\DIO_Interface.h"
#include "..\MCAL\TIMER\TIMER_Interface.h"

int main(void) {
	u8 LEDFlag = DIO_u8HIGH;
	u32 Timer0_u32OverFlowNum;
	__asm__("SEI");
	TIMER0_voidInit();
	DIO_u8WritePinDir(8, DIO_u8OUTPUT);
	while (1) {
		DIO_u8WritePinVal(8, LEDFlag);
		Timer0_u32OverFlowNum = TIMER0_u32GetOverflowCount();
		if (Timer0_u32OverFlowNum == 1953) {
			TIMER0_voidClearOverflowCount();
			LEDFlag = !LEDFlag;
		}
		//voidDELAY_MS(1000);
	}
	return 0;
}
