#include <avr/io.h>
#include <util/delay.h>

#define DEBOUNCE_TIME 25

int main()
{
	OCR1AH = 0x3D;                      //Load higher byte of 15624 into output compare register
	OCR1AL = 0x08;                      //Load lower byte of 15624 into output compare register
	TCCR1A = 0b00000000;
	TCCR1B = 0b00001101; 				//Turn on CTC mode and prescaler of CLK/1024

	while (1)
	{}

	return 0;
}