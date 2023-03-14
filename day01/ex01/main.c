#include <avr/io.h>

int main()
{
    DDRB |= (1 << PB1);

    // Set mode to 15 (Fast PWM)
    TCCR1A |= (1 << WGM10) | 
    TCCR1B |= (1 << WGM12);

    // Set Output Compare A Match flag
    TIFR1 |= (1 << OCF1A);

    // Set Compare Match Output A on toggling OC1A
    TCCR1A |= (1 << COM1A0);

    // Set TOP value (31250 aka 0111 1010 0001 0010 aka 16000000 / (prescale * 2)) 
    OCR1AH = 0b01111010;
    OCR1AL = 0b00010010;

    // Set prescaling (prescale 256)
    TCCR1B |= (1 << CS12);

    while (1);

    return 0;
}
