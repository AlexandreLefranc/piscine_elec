#include <avr/io.h>
#include <util/delay.h>

void    uart_init()
{
    // Set Baudrate
    UBRR0H = 0;
    UBRR0L = 8;

    // Enable Transmitter
    UCSR0B = (1<<TXEN0);

    // Set frame format: 8data, 2stop bit
    UCSR0C = (1<<USBS0) | (3<<UCSZ00);
}

void    uart_tx(char c)
{
    while (( UCSR0A & (1 << UDRE0)) == 1);
    UDR0 = c;
}

int main()
{
    uart_init();

    while (1)
    {
        uart_tx('Z');
        _delay_ms(1000);
    }

    return 0;
}

