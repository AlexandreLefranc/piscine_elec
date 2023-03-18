#include <avr/io.h>
#include <util/twi.h>
#include <util/delay.h>

#define DEBOUNCE_TIME 25
#define UBBR 8

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

void    uart_printbinary(uint8_t data)
{
    uart_printstr("0b");
    for (int8_t i = 7; i >= 0; --i)
        uart_tx(((data >> i) & 0x01) + '0');
}

void    uart_printhex(uint8_t data)
{
    const char hex[] = "0123456789ABCDEF";

    uart_printstr("0x");
    uart_tx(hex[((data >> 4) & 0x0F)]);
    uart_tx(hex[((data >> 0) & 0x0F)]);
}

void uart_printTWSR()
{
    uint8_t reg = TWSR;

    uart_printstr("TWSR is ");
    uart_printbinary(reg);
    uart_printstr(" (");
    uart_printhex(reg);
    uart_printstr(")\r\n");
}


void    i2c_init()
{
    // i2c freq 100 000 Hz
    // TWBR = ((fcpu / fscl) - 16) * (1 / 2*prescaler)
    TWBR = 72;

    // Set prescaler (1) => nothing to change
    // TWSR |= (1 << TWPS0) | (1 << TWPS1);

    // Enable i2c
    TWCR = (1 << TWEN);
}

void    i2c_start()
{
    // 1/ Send START condition
    TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);

    // 2/ Wait for TWINT Flag set.
    while (!(TWCR &(1<<TWINT)));

    // 3/ Check value of TWI Status Register
    uart_printTWSR();
    if ((TWSR & 0xF8) != TW_START)
        uart_printstr("error1\r\n");

    // 3/ Load device address into TWDR Register.
    TWDR = (0x38 << 1) | TW_WRITE;
    TWCR = (1<<TWINT) | (1<<TWEN);

    // 4/ Wait for TWINT Flag set.
    while (!(TWCR &(1<<TWINT)));

    // 5/ Check value of TWI Status Register.
    uart_printTWSR();
    if ((TWSR & 0xF8) != TW_MT_SLA_ACK)
        uart_printstr("error2\r\n");

    // 5/ Load DATA into TWDR Register.
    TWDR = 0x00;
    TWCR = (1<<TWINT) | (1<<TWEN);

    // 6/ Wait for TWINT Flag set.
    while (!(TWCR & (1<<TWINT)));

    // 7/ Check value of TWI Status Register.
    uart_printTWSR();
    if ((TWSR & 0xF8) != TW_MT_DATA_ACK)
        uart_printstr("error3\r\n");

    // 7/ Transmit STOP condition
    // TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
}

void    i2c_stop()
{
    // 7/ Transmit STOP condition
    TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
}


void    init()
{
    i2c_init();
    uart_init();
}

int     main()
{
    init();

    while (1)
    {
        i2c_start();

        i2c_stop();

        uart_printstr("\r\n");
        _delay_ms(2000);
    }

    return 0;
}
