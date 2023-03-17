#include <avr/io.h>
#include <util/twi.h>
#include <util/delay.h>

#define DEBOUNCE_TIME 25
#define UBBR 8

/*******************************************************************************
    UART
*******************************************************************************/

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


/*******************************************************************************
    i2c
*******************************************************************************/

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
    // Set START condition
    uart_printstr("Set Start Cond\r\n");
    TWCR |= (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);

    // TWCR &= ~(1 << TWSTO);

    // Write SLA+W (Slave Address + Write) to TWDR
    uart_printstr("SLA+W\r\n");
    TWDR = 0x38;

    // Clear TWINT bit
    uart_printstr("CLEAR TWINT\r\n");
    TWCR |= (1 << TWINT);

    // Wait for Acknowledge
    uart_printstr("Aknowledge ? ");
    while ((TWCR & (1 << TWINT)) == 0);
    uart_printstr("Yes\r\n");
}

void    i2c_stop()
{
    TWCR |= (1 << TWINT) | (1 <<TWSTO) | (1 << TWEN);
}

void    i2c_write(uint8_t data)
{
// Send data
uart_printstr("Writing: ");
uart_tx((char)data);
uart_printstr("\r\n");
TWDR = data;

// Wait for Acknowledge
uart_printstr("Aknowledge ? ");
while ((TWCR & (1 << TWINT)) == 0);
uart_printstr("Yes\r\n");
}

void    i2c_read()
{

}

void    print_hex_value(uint8_t c)
{

}




/*******************************************************************************
    CORE
*******************************************************************************/

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
        if (((TWSR & 0x18) != 0) || ((TWSR & 0x20) != 0) || ((TWSR & 0x38) != 0))
            uart_printstr("Connection established\r\n");
        else
            uart_printstr("Connection NOT established\r\n");

        
        i2c_stop();

        _delay_ms(1000);
    }

    return 0;
}
