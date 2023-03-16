#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define DEBOUNCE_TIME 25

uint8_t counter = 0;
uint8_t x = -1;

void    update()
{
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

ISR(INT0_vect)
{
    ++counter;
    update();
    _delay_ms(DEBOUNCE_TIME);
}

ISR(PCINT2_vect)
{
    ++x;
    if (x % 2 == 0)
    {
        --counter;
        update();
        _delay_ms(DEBOUNCE_TIME);
    }
}

void    init()
{
    DDRB |= 1 << PB0;
    DDRB |= 1 << PB1;
    DDRB |= 1 << PB2;
    DDRB |= 1 << PB4;

    // Enable INT0 interrupt
    EIMSK |= (1 << INT0);

    // Set behavior: interrupt on press only
    EICRA |= (1 << ISC01);

    // Enable PCINT20 interrupt
    PCMSK2 |= (1 << PCINT20);

    // Pin Change Interrupt Enable 2
    PCICR |= (1 << PCIE2);

    // Enable global interrupt
    sei();

}

int     main()
{
    init();

    while (1);

    return 0;
}
