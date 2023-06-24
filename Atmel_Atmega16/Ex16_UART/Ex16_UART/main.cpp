/*
 * Ex16_UART.cpp
 *
 * Created: 6/23/2023 9:51:43 AM
 * Author : Ngoc Dai
 */ 

#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/delay.h>
#include <avr/sfr_defs.h>
#include <avr/interrupt.h>

void send(unsigned char c)
{
	while(bit_is_clear(UCSRA, UDRE));	
	UDR = c;
}

unsigned char receive()
{
	while(bit_is_clear(UCSRA, RXC));
	return UDR;
}

int main(void)
{	
	DDRA = 0xFF;
	PORTA = 0x00;
	
	UBRRL = 51;	// baud rate 9600

	UCSRC = (1<<UCSZ1) | (1<<UCSZ0); // set 8-bit character size
	UCSRB = (1<<RXEN) | (1<<TXEN);	//Receiver enable & Transmitter enable
    while (1) 
    {
		send('5');
		_delay_ms(100);
		
		if(receive() == 'A')
		{
			PORTA = 0x01;
			_delay_ms(100);
		}
		
		PORTA = 0x00;
    }
}

