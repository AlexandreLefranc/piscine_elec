#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define UBBR 8

void    uart_init()
{
    // Set Baudrate
    UBRR0H = (UBBR >> 8);
    UBRR0L = UBBR;

    // Enable Transmitter and Receiver
    UCSR0B = (1<<TXEN0) | (1<<RXEN0);

    // Set frame format: 8data, 2stop bit
    UCSR0C = (1<<USBS0) | (3<<UCSZ00);
}

void    uart_tx(char c)
{
    while ((UCSR0A & (1 << UDRE0)) == 0);
    UDR0 = c;
}

void    uart_printstr(const char* str)
{
    for (uint16_t i = 0; str[i]!='\0'; i++)
    {
        uart_tx(str[i]);
    }
}

char    uart_rx(void)
{
    while ((UCSR0A & (1<<RXC0)) == 0);
    return UDR0;
}

int main()
{
    uart_init();

    while (1)
    {
        char c = uart_rx();
        uart_printstr("Received: ");
        uart_tx(c);
        uart_printstr("\r\n");
    }

    return 0;
}