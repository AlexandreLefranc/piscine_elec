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
    // Set START condition
    uart_printstr("Set Start Cond\r\n");
    uart_printbinary(TWCR, "TWCR");
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
    uart_printbinary(TWCR, "TWCR");

    uart_printstr("Reset TWINT\r\n");
    i2c_reset_twint();
    uart_printbinary(TWCR, "TWCR");

    // Wait for TWINT Flag set
    // uart_printstr("Wait for TWINT Flag set\r\n");
    // while ((TWCR & (1<<TWINT)) == 0);

    // // Check TWI Status for START
    // uart_printstr("Check TWI Status for START\r\n");
    // if ((TWSR & 0xF8) != TW_START)
    //     uart_printstr("Status is not set to START\r\n");;

    // // Write SLA+W (Slave Address + Write) to TWDR
    // uart_printstr("SLA+W\r\n");
    // TWDR = 0x38;

    // /*
    // Wait for TWINT Flag set.
    // This indicates that the SLA+W has been transmitted, and ACK/NACK has been received.
    // */
    // uart_printbinary(TWCR, "TWCR");
    // uart_printstr("Wait for TWINT Flag Set\r\n");
    // while (!(TWCR & (1<<TWINT)));
    // uart_printbinary(TWCR, "TWCR");

    // /*
    // Check value of TWI Status Register. Mask prescaler bits.
    // If status different from MT_SLA_ACK print error
    // */
    // uart_printstr("Check value of TW_MT_SLA_ACK\r\n");
    // if ((TWSR & 0xF8) != TW_MT_SLA_ACK)
    //     uart_printstr("Status is not set to MT_SLA_ACK\r\n");

    // uart_printstr("Check value of TW_MT_SLA_NACK\r\n");
    // if ((TWSR & 0xF8) != TW_MT_SLA_NACK)
    //     uart_printstr("Status is not set to TW_MT_SLA_NACK\r\n");

    // uart_printstr("Check value of TW_MT_ARB_LOST\r\n");
    // if ((TWSR & 0xF8) != TW_MT_ARB_LOST)
    //     uart_printstr("Status is not set to TW_MT_ARB_LOST\r\n");
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
        if (((TWSR & 0x18) == 0x18) || ((TWSR & 0x20) == 0x20) || ((TWSR & 0x38) == 0x38))
            uart_printstr("Connection established\r\n");
        else
            uart_printstr("Connection NOT established\r\n");
        i2c_stop();
        uart_printbinary(TWSR, "TWSR");

        uart_printstr("\r\n");
        _delay_ms(2000);
    }

    return 0;
}
