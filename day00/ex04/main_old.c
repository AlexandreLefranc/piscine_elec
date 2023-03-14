#include <avr/io.h>
#include <util/delay.h>

// https://stackoverflow.com/questions/23174714/invert-specific-bits-using-bitwise-not-no-xor

int main()
{
	// Set Port B registry to write mode for pin PB0
	DDRB |= 1 << PB0;

	uint8_t prev_state = 0;
	uint8_t curr_state = 0;
	while (1)
	{
		curr_state = (PIND & (1 << PD2));

		if (prev_state != 0 && curr_state == 0)
		{
			PORTB = (PORTB & ~(1 << PB0)) | (~PORTB & (1 << PB0));
			_delay_ms(10);
		}

		if (prev_state == 0 && curr_state != 0)
		{
			_delay_ms(10);
		}

		prev_state = curr_state;
	}


	return 0;
}