#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdbool.h>

#define UBBR 8

#define BUFFER_SIZE 64

const char* g_usr = "Bob";
const char* g_pw = "boB";

void    uart_init()
{
    // Set Baudrate
    UBRR0H = (UBBR >> 8);
    UBRR0L = UBBR;

    // Enable Transmitter and Receiver
    UCSR0B |= (1 << TXEN0) | (1 << RXEN0);

    // Set frame format: 8data, 2stop bit
    UCSR0C |= (1 << USBS0) | (3 << UCSZ00);

    // Enable interrupt on Receive
    UCSR0B |= (1 << RXCIE0);
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
    // While there is nothing to receive, loop
    while ((UCSR0A & (1<<RXC0)) == 0);
    return UDR0;
}

int main()
{
    DDRB |= (1 << PB0);

    uart_init();
    sei();

    uint8_t done = 0;

    while (1);

    return 0;
}

ISR(USART_RX_vect)
{
    char    c = uart_rx();
    if (c >= 'A' && c <= 'Z')
        uart_tx(c + 32);
    else if (c >= 'a' && c <= 'z')
        uart_tx(c - 32);
    else
        uart_tx(c);

    PORTB ^= (1 << PB0);
}