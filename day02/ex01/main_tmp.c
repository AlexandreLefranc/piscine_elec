#include <avr/io.h>

ISR(TIMER0_COMPA_vect)
{

}

int main()
{
    DDRB |= (1 << PB1);


	// Timer0 mode CTC (2)
	TCCR0A |= (1 << WGM01);

	// Enable interrupt on match A
	TIMSK0 |= (1 << OCIE0A);

    // Set TOP value / Match A compare
    OCR0A = 78;

	// Set prescaler (1024)
    TCCR0B |= (1 << CS02) | (1 << CS00);












    // Set mode to 14 (Fast PWM)
        // TOP ICR1
        // Update of OCR1x at BOTTOM
        // TOV1 Flag Set on TOP
    TCCR1A |= (1 << WGM11);
    TCCR1B |= (1 << WGM12) | (1 << WGM13);

    // Set Output Compare A Match flag to enable compare
    TIFR1 |= (1 << OCF1A);

    // Set Compare Match Output A match action on set OC1A
    TCCR1A |= (1 << COM1A1);

    // Set Output Compare value (6250)
    OCR1A = 0;

    // Set TOP value (62500) 
    ICR1 = 62500;

    // Set prescaling (prescale 1)
    TCCR1B |= (1 << CS10);

    while (1);

    return 0;
}
