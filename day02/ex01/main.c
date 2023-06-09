#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define DEBOUNCE_TIME 25

double dutyCycle = 1;
int8_t dir = 1;



ISR(TIMER0_COMPA_vect)
{
    if (dutyCycle == 100 || dutyCycle == 0)
        dir *= -1;
    dutyCycle += (dir * 1);
    OCR1A = (uint16_t)((dutyCycle / 100) * 62500.0);

    // PORTB |= (1 << PB4);
}



void    init()
{
    // Set PB1 as output
    DDRB |= (1 << PB1);
    DDRB |= (1 << PB4);
}

void    init_timer0()
{
    // Set mode to 2 (CTC)
    TCCR0A |= (1 << WGM01);

    // Set TOP value / Match A compare
    OCR0A = 78;

    // Enable Match A interrupt
    TIMSK0 |= (1 << OCIE0A);

    // Set prescaler (1024)
    TCCR0B |= (1 << CS02) | (1 << CS00);
}

void    init_timer1()
{
    // Set mode to 14 (Fast PWM)
    TCCR1A |= (1 << WGM11);
    TCCR1B |= (1 << WGM12) | (1 << WGM13);

    // Set Compare Match Output A match action: set OC1A
    TCCR1A |= (1 << COM1A1);

    // Set Output Compare value (6250)
    OCR1A = 0;

    // Set TOP value (62500) 
    ICR1 = 62500;

    // Set prescaling (prescale 1)
    TCCR1B |= (1 << CS10);
}

int main()
{
    init();
    init_timer0();
    init_timer1();

    sei();

    while (1)
    {
        // OCR1A += 100;
        // _delay_ms(1);
    }

    return 0;
}
