/*
 * LED_OUTPUT_BAI1.cpp
 *
 * Created: 6/19/2023 10:48:50 PM
 * Author : Ngoc Dai
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/delay.h>


int main(void)
{
    DDRA = 0x01;
    PORTA = 0x01;
	DDRB = 0x00; // port B = input
	PORTB = 0x01;
    while (1) 
    {
		if ((PINB & (1 << PINB0)) == 0) {
			PORTA = 0x01;
		}
		else {
			PORTA = 0x00;
		}
    }
}

