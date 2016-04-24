#include <avr/io.h>
#include <avr/interrupt.h>

//256 count = 64 us >> 4 count for each us so we need 4*13 = 52 for 13us

// global variable to count the number of overflows
volatile uint8_t tot_overflow;

// initialize timer, interrupt and variable
void timer0_init()
{
    // set up timer with prescaler = 1
    TCCR0 |= (1 << CS00);

    // initialize counter
    TCNT0 = 204;

    // enable overflow interrupt
    TIMSK |= (1 << TOIE0);

    // enable global interrupts
    sei();

    // initialize overflow counter variable
    tot_overflow = 0;
}

// TIMER0 overflow interrupt service routine
// called whenever TCNT0 overflows
ISR(TIMER0_OVF_vect)
{
    // keep a track of number of overflows
    //tot_overflow++;
	PORTB ^= (1 << 0);    // toggles the led
	TCNT0 = 204;          // reset counter
}

int main(void)
{
    // connect led to pin PB0
    DDRB |= (1 << 0);

    // initialize timer
     timer0_init();

    // loop forever
    while(1)
    {
      /*   // check if no. of overflows = 12
        if (tot_overflow >= 12)  // NOTE: '>=' is used
        {
            // check if the timer count reaches 53
            if (TCNT0 >= 53)
            {
                PORTC ^= (1 << 0);    // toggles the led
                TCNT0 = 0;            // reset counter
                tot_overflow = 0;     // reset overflow counter
            }
        } */
    }
}
