
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>

void serial_init(void);
int serial_send( char data, FILE *stream);

static FILE out_stream = FDEV_SETUP_STREAM(serial_send, NULL, _FDEV_SETUP_WRITE);

int main(void)
{
    serial_init();
    stdout = &out_stream;
    
    for(int i = 0; i < 10; i++)
    {      
        printf("<%d>Hello!\n\r", i);
        _delay_ms(1000);
    }

    return 0;
}

void serial_init(void)
{
    //Arduino Atmega2560 uses PE0(RX0) i PE1(TX0)
    UCSR0B = (1 << TXEN0);

    // set character data size to 8
    UCSR0C |= (1 << UCSZ00) | (1 << UCSZ01);

    //115200, crystal 16Mhz UBRR = 16000000/(16*baudrate)-1
    UBRR0 = 8;
}

unsigned char serial_receive(void)
{
    while(!(UCSR0A & (1<<RXC0)));
    return UDR0;
}

int serial_send( char data, FILE *stream)
{
    while(!(UCSR0A & (1<<UDRE0)));
    UDR0 = data;
    return 0;
}