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

void    uart_printbinary(uint8_t data, const char* str)
{
    uart_printstr(str);
    uart_printstr(" = ");
    uart_printstr("0b");
    for (int8_t i = 7; i >= 0; --i)
        uart_tx(((data >> i) & 0x01) + '0');
    uart_printstr("\r\n");
}

void    uart_printhex(uint8_t data)
{
    const char hex[] = "0123456789ABCDEF";
    uart_tx(hex[((data >> 4) & 0x0F) % 16]);
    uart_tx(hex[((data >> 0) & 0x0F) % 16]);
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

void    i2c_reset_twint()
{
    TWCR |= (1 << TWINT);
}

void    i2c_start()
{
    // 1/ Send START condition
    TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);

    // 2/ Wait for TWINT Flag set.
    while (!(TWCR &(1<<TWINT)));

    // 3/ Check value of TWI Status Register
    if ((TWSR & 0xF8) != TW_START)
        uart_printstr("error1\r\n");
    
    // 3/ Load 0x38 into TWDR Register.
    TWDR = (0x38 << 1) | TW_WRITE;
    TWCR = (1<<TWINT) | (1<<TWEN);

    // 4/ Wait for TWINT Flag set.
    while (!(TWCR &(1<<TWINT)));

    // 5/ Check value of TWI Status Register.
    if ((TWSR & 0xF8) != TW_MT_SLA_ACK)
        uart_printstr("error2\r\n");

    // 5/ Load DATA into TWDR Register.
    TWDR = 0x00;
    TWCR = (1<<TWINT) | (1<<TWEN);

    // 6/ Wait for TWINT Flag set.
    while (!(TWCR & (1<<TWINT)));

    // 7/ Check value of TWI Status Register.
    if ((TWSR & 0xF8) != TW_MT_DATA_ACK)
        uart_printstr("error3\r\n");

    // 7/ Transmit STOP condition
    TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
}

void    i2c_stop()
{
    TWCR = (1 << TWINT) | (1 <<TWSTO) | (1 << TWEN);
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
        uart_printbinary(TWSR, "TWSR (after start)");
        // if (((TWSR & 0x18) == 0x18) || ((TWSR & 0x20) == 0x20) || ((TWSR & 0x38) == 0x38))
        //     uart_printstr("Connection established\r\n");
        // else
        //     uart_printstr("Connection NOT established\r\n");
        // i2c_stop();
        // uart_printbinary(TWSR, "TWSR");

        uart_printstr("\r\n");
        _delay_ms(2000);
    }

    return 0;
}
