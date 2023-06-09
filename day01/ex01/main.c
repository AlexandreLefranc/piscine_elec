#include <avr/io.h>

int main()
{
    DDRB |= (1 << PB1);

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
    OCR1A = 6250;
    // OCR1AH = 0b00011000;
    // OCR1AL = 0b01101010;

    // Set TOP value (62500) 
    ICR1 = 62500;
    // ICR1H = 0b11110100;
    // ICR1L = 0b00010100;

    // Set prescaling (prescale 256)
    TCCR1B |= (1 << CS12);

    while (1);

    return 0;
}
