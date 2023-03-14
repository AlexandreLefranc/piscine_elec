#include <avr/io.h>
#include <util/delay.h>

#define DEBOUNCE_TIME 25

// https://stackoverflow.com/questions/65083398/toggling-blink-led-program-on-and-off
// https://stackoverflow.com/questions/23174714/invert-specific-bits-using-bitwise-not-no-xor

static void	portb_turn_on_only(uint8_t spot)
{
	PORTB = 0;
	PORTB |= (1 << spot);
}

enum {
	
}

int main()
{
	DDRB |= 1 << PB0;
	DDRB |= 1 << PB1;
	DDRB |= 1 << PB2;
	DDRB |= 1 << PB4;

	while (1)
	{
		if ()
		portb_turn_on_only(PB0);
		_delay_ms(100);
		portb_turn_on_only(PB1);
		_delay_ms(100);
		portb_turn_on_only(PB2);
		_delay_ms(100);
		portb_turn_on_only(PB4);
		_delay_ms(100);
		portb_turn_on_only(PB2);
		_delay_ms(100);
		portb_turn_on_only(PB1);
		_delay_ms(100);
	}

	return 0;
}