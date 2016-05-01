#include <avr/io.h>
#include <avr/interrupt.h>
#include "..\Utilities\Types.h"

#define F_CPU 						4000000UL  // 1 MHz
#define clockCyclesPerMicrosecond	(F_CPU/1000000UL)
#define clockCyclesPerMillisecond	(clockCyclesPerMicrosecond * 1000UL)
#define Timer0_Prescale				(1UL)

// global variable to count the number of overflows
static volatile u32 timer0_overflow_count;
// global variable to count the number of system clocks
static volatile u32 timer0_clock_cycles = 0;
// global variable to count the number mS since the system powered on
static volatile u32 timer0_millis = 0;
static u32 iTimeout;

u32 micros() {
	//  return((timer0_overflow_count << 8) + TCNT0)*(prescale/clockCyclesPerMicrosecond );
	u32 m;
	uint8_t oldSREG = SREG, t;

	cli();
	m = timer0_overflow_count;
	t = TCNT0;

	if ((TIFR & _BV(TOV0)) && (t < 255))
		m++;

	SREG = oldSREG;

	return ((m << 8) + t)
			* ((f32) Timer0_Prescale / clockCyclesPerMicrosecond()); // Number of counters * time per each tick
}

u32 millis() {
	u32 m;
	u8 oldSREG = SREG;
	// disable interrupts while we read timer0_millis or we might get an
	// inconsistent value (e.g. in the middle of the timer0_millis++)
	cli();
	m = timer0_millis;
	SREG = oldSREG;
	return m;
}

void delayMS(u32 ms) {
	u32 start = millis();
	while (millis() - start <= ms)
		;
}

void delayMicroseconds(u16 us) {
	// calling avrlib's delay_us() function with low values (e.g. 1 or
	// 2 microseconds) gives delays longer than desired.
	//delay_us(us);
	// for the 16 MHz clock on most Arduino boards

	// for a one-microsecond delay, simply return.  the overhead
	// of the function call yields a delay of approximately 1 1/8 us.
	if (--us == 0)
		return;

	// the following loop takes a quarter of a microsecond (4 cycles)
	// per iteration, so execute it four times for each microsecond of
	// delay requested.
	//us <<= 2;

	// account for the time taken in the preceeding commands.
	us -= 1;

	// busy wait
	__asm__ __volatile__ (
			"1: sbiw %0,1" "\n\t" // 2 cycles
			"brne 1b" : "=w" (us) : "0" (us)// 2 cycles
	);
}

void NonBlockingDelayms(u32 t) {
	iTimeout = millis() + t;
	return;
}

u8 Timeout(void) {
	return (iTimeout < millis());
}

// initialize timer, interrupt and variable
void timer0_init() {
	// set up timer with prescaler = 1
	TCCR0 |= (1 << CS00);

	//256 count = 64 us >> 4 count for each us so we need 4*13 = 52 for 13us
	// initialize counter
	//TCNT0 = 204;
	TCNT0 = 0;
	// enable overflow interrupt
	TIMSK |= (1 << TOIE0);

	// enable global interrupts
	sei();

	// initialize overflow counter variable
	timer0_overflow_count = 0;
}

// TIMER0 overflow interrupt service routine
// called whenever TCNT0 overflows
ISR(TIMER0_OVF_vect) {
//	timer0_overflow_count++;
//	// timer 0 prescale factor is 1 and the timer overflows at 256
//	timer0_clock_cycles += Timer0_Prescale * 256UL;
//	while (timer0_clock_cycles > clockCyclesPerMillisecond) {
//		timer0_clock_cycles -= clockCyclesPerMillisecond;
//		timer0_millis++;
//	}
	PORTB ^= (1 << 0);    // toggles the led
	TCNT0 = 252;
}

int main(void) {
	// connect led to pin PB0
	DDRB |= (1 << 0);

	// initialize timer
	timer0_init();

	// loop forever
	while (1) {
		//PORTB ^= (1 << 0);    // toggles the led
		//delay(1000); //blocking delay
//		if (Timeout()) {
//			PORTB ^= (1 << 0);    // toggles the led
//			NonBlockingDelayms(1000); //Non blocking delay
//		}
		//do other stuff

	}
}
