#include <avr/io.h>
#include <util/delay.h>

static void	delay_ms(uint32_t time)
{
	uint32_t divisor = (1000 / time) * 8;
	uint32_t n_op = F_CPU / divisor;
	uint32_t i = 0;

	while (i < n_op)
	{
		asm("nop");
		++i;
	}
}

int main()
{
	// Set Port B registry to write mode for pin PB0
	DDRB |= 1 << PB0;

	while (1)
	{
		// Turn on Port B, pin PB0
		PORTB |= 1 << PB0;
		// _delay_ms(500);
		delay_ms(500);
		PORTB &= ~(1 << PB0);
		// _delay_ms(500);
		delay_ms(500);
	}



	return 0;
}