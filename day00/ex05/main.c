#include <avr/io.h>
#include <util/delay.h>

#define DEBOUNCE_TIME 25

// https://stackoverflow.com/questions/65083398/toggling-blink-led-program-on-and-off
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

static uint8_t	sw2_pressed_transition()
{
	static uint8_t	prev_state = 0;
	uint8_t			curr_state = (PIND & (1 << PD4));

	if (prev_state != curr_state)
	{
		_delay_ms(25);

		if (prev_state != 0 && (PIND & (1 << PD4)) == 0)
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

// static uint8_t	pressed_transition(uint8_t reg, uint8_t spot)
// {
// 	static uint8_t	prev_state = 0;
// 	uint8_t			curr_state = (reg & (1 << spot));

// 	if (prev_state != curr_state)
// 	{
// 		_delay_ms(25);

// 		if (prev_state != 0 && (reg & (1 << spot)) == 0)
// 		{
// 			prev_state = curr_state;
// 			return 1;
// 		}
// 		else
// 		{
// 			prev_state = curr_state;
// 		}
// 	}

// 	return 0;
// }

int main()
{
	DDRB |= 1 << PB0;
	DDRB |= 1 << PB1;
	DDRB |= 1 << PB2;
	DDRB |= 1 << PB4;

	uint8_t	counter = 0;

	while (1)
	{
		if (sw1_pressed_transition(PIND, PD2) != 0)
			++counter;

		if (sw2_pressed_transition(PIND, PD4) != 0)
			--counter;

		if ((counter & 0b00000001) != 0)
			PORTB |= (1 << PB0);
		else
			PORTB &= ~(1 << PB0);

		if ((counter & 0b00000010) != 0)
			PORTB |= (1 << PB1);
		else
			PORTB &= ~(1 << PB1);

		if ((counter & 0b00000100) != 0)
			PORTB |= (1 << PB2);
		else
			PORTB &= ~(1 << PB2);

		if ((counter & 0b00001000) != 0)
			PORTB |= (1 << PB4);
		else
			PORTB &= ~(1 << PB4);
	}

	return 0;
}