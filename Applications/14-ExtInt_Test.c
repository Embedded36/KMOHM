#include "..\Utilities\Types.h"
#include "..\Utilities\Delay.h"
#include "..\MCAL\DIO\DIO_Interface.h"

#define ISR(vector, ...) \
	void vector(void) __attribute__ ((signal,used,externally_visible)) __VA_ARGS__;\
	void vector(void)

/* External Interrupt Request 0 */
#define INT0_vect			__VECTOR_1

#define MCUCR  	(*((volatile u8*)(0x55)))
#define MCUCSR	(*((volatile u8*)(0x54)))
#define GICR  	(*((volatile u8*)(0x5B)))
#define GIFR  	(*((volatile u8*)(0x5A)))

/* External Interrupt Request 0 */
//#define INT0_vect			_VECTOR(1)

/* External Interrupt Request 1 */
//#define INT1_vect			_VECTOR(2)

/* External Interrupt Request 2 */
//#define INT2_vect			_VECTOR(3)

/* Timer/Counter0 Overflow */
//#define TIMER0_OVF_vect			_VECTOR(11)

volatile u8 LEDFlag=0;
ISR(INT0_vect)
{
	u8 static Counter;
	Counter++;
	if(Counter==5)
	{
		LEDFlag = ! LEDFlag;
		Counter=0;
	}
}

int main(void) {
	__asm__("SEI");
	MCUCR |= (1<<0);//make it on change
	GICR |= (1<<6); // PIE for INT0

	DIO_u8WritePinDir(26,DIO_u8INPUT);
	DIO_u8WritePinDir(8,DIO_u8OUTPUT);
	DIO_u8WritePinDir(9,DIO_u8OUTPUT);

	while (1) {
		DIO_u8WritePinVal(8,LEDFlag);
		DIO_u8WritePinVal(9,DIO_u8HIGH);
		voidDELAY_MS(1000);
		DIO_u8WritePinVal(9,DIO_u8LOW);
		voidDELAY_MS(1000);
	}
	return 0;
}
