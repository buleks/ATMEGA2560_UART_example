
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>

//1152 000

void USART_init(void);
void USART_send( unsigned char data);
void print(char * str);


char string_buffer[100];

int main(void)
{
    USART_init();
    
    for(int i = 0; i < 10; i++)
    {      
        sprintf(string_buffer, "<%d>Hello!\n\r", i);
        print(string_buffer);
        _delay_ms(1000);        //Delay for 5 seconds so it will re-send the string every 5 seconds
    }

    return 0;
}

void USART_init(void)
{
    //Arduino Atmega2560 uses PE0(RX0) i PE1(TX0)
    UCSR0B = (1 << TXEN0);

    // set character data size to 8
    UCSR0C |= (1 << UCSZ00) | (1 << UCSZ01);

    //115200, crystal 16Mhz UBRR = 16000000/(16*baudrate)-1
    UBRR0 = 8;
}

unsigned char USART_receive(void)
{
    while(!(UCSR0A & (1<<RXC0)));
    return UDR0;
}

void USART_send( unsigned char data)
{
    while(!(UCSR0A & (1<<UDRE0)));
    UDR0 = data;
}

void print(char * str)
{
    int i = 0;
    while(str[i] != 0)
    {
        USART_send(str[i]);
        i++;
    }
}