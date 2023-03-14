#include <avr/io.h>
#include <util/delay.h>

// https://stackoverflow.com/questions/23174714/invert-specific-bits-using-bitwise-not-no-xor

static uint8_t	sw1_pressed_transition()
{
	static uint8_t	prev_state = 0;
	uint8_t			curr_state = (PIND & (1 << PD2));

	if (prev_state != curr_state)
	{
		_delay_ms(25);

		if (prev_state != 0 && (PIND & (1 << PD2)) == 0)
		{
			prev_state = curr_state;
			return 1;
		}
		else
		{
			prev_state = curr_state;
		}
	}

	return 0;
}

int main()
{
	DDRB |= 1 << PB0;
	DDRD &= ~(1 << PD2);

	while (1)
	{
		if (sw1_pressed_transition() == 1)
			PORTB ^= (1 << PB0);
	}


	return 0;
}