#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define UBBR 8

void    timer1_init()
{
    // CTC (mode 4)
    TCCR1B |= (1 << WGM12);

    // Set TOP / Match A value
    OCR1A = 15625 * 2;

    // Enable interrupt match A
    TIMSK1 |= (1 << OCIE1A);

    // Set Prescaler 1024
    TCCR1B |= (1 << CS12) | (1 << CS10);
}

void    uart_init()
{
    // Set Baudrate
    UBRR0H = (UBBR >> 8);
    UBRR0L = UBBR;

    // Enable Transmitter
    UCSR0B = (1<<TXEN0);

    // Set frame format: 8data, 2stop bit
    UCSR0C = (1<<USBS0) | (3<<UCSZ00);
}

void    uart_tx(char c)
{
    while ( (UCSR0A & (1 << UDRE0)) == 0 );
    UDR0 = c;
}

void    uart_printstr(const char* str)
{
    for (uint16_t i = 0; str[i]!='\0'; i++)
    {
        uart_tx(str[i]);
    }
}

int main()
{
    uart_init();
    timer1_init();
    sei();

    while (1)
    {}

    return 0;
}

ISR(TIMER1_COMPA_vect)
{
    uart_printstr("Hello World!\r\n");
}
