#include "..\Utilities\Types.h"
#include "..\Utilities\Delay.h"
#include "..\MCAL\DIO\DIO_Interface.h"
#include "..\MCAL\TIMER\TIMER_Interface.h"

#define ISR(vector, ...) \
	void vector(void) __attribute__ ((signal,used,externally_visible)) __VA_ARGS__;\
	void vector(void)

/* External Interrupt Request 0 */
#define INT0_vect			__vector_1

#define MCUCR  	(*((volatile u8*)(0x55)))
#define MCUCSR	(*((volatile u8*)(0x54)))
#define GICR  	(*((volatile u8*)(0x5B)))
#define GIFR  	(*((volatile u8*)(0x5A)))

#define OneSec	(1953)

volatile u8 LEDFlag = 0;

ISR(INT0_vect) {
		LEDFlag = !LEDFlag;
}

int main(void) {
	u32 Timer0_u32OverFlowNum;
	u8 SignalFlag = 0;
	__asm__("SEI");
	MCUCR |= (1 << 0); //make it on change
	GICR |= (1 << 6); // PIE for INT0

	DIO_u8WritePinDir(26, DIO_u8INPUT);
	DIO_u8WritePinDir(8, DIO_u8OUTPUT);
	DIO_u8WritePinDir(9, DIO_u8OUTPUT);
	DIO_u8WritePinVal(9, SignalFlag);
	TIMER0_voidInit();
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
