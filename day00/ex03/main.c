#include <avr/io.h>
#include <util/delay.h>

int main()
{
	// Set Port B registry to write mode for pin PB0
	DDRB |= 1 << PB0;
	// DDRB |= 1 << PB1;

	while (1)
	{
		if ((PIND & (1 << PD2)) != 0)
			PORTB |= 1 << PB0;
		else
			PORTB &= ~(1 << PB0);

		// Turn on Port B, pin PB0
		// PORTB |= 1 << PB0;
		// _delay_ms(500);
		// PORTB &= ~(1 << PB0);
		// _delay_ms(500);
	}


	return 0;
}