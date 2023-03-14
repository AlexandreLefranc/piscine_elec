#define __AVR_ATmega328P__
#define F_CPU 200000
#include <avr/io.h>

int main()
{
	// Set Port B registry to write mode for pin PB0
	DDRB |= 1 << PB0;

	// Turn on Port B, pin PB0
	PORTB |= 1 << PB0;

	return 0;
}