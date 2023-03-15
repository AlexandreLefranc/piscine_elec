#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define DEBOUNCE_TIME 25

ISR(INT0_vect)
{
    PORTB ^= (1 << PB1);
    _delay_ms(DEBOUNCE_TIME);
}

int main()
{
    // Set PB1 as output
    DDRB |= (1 << PB1);

    // Enable INT0 interrupt
    EIMSK |= (1 << INT0);

    // Set behavior: interrupt on press only
    EICRA |= (1 << ISC01);

    // Enable global interrupt
    sei();

    while (1);

    return 0;
}
