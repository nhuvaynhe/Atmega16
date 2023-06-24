/*
 * Test.cpp
 *
 * Created: 6/21/2023 4:44:35 PM
 * Author : Ngoc Dai
 */ 

#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>

void Delay();
	
int main(void)
{
    DDRB = 0xFF;
	PORTB = 0;
    while (1) 
    {
		PORTB = ~PORTB;
		Delay();
    }
}

void Delay()
{
	TCCR0 = (1 << CS02) | (1 << CS00);
	TCNT0 = 177;
	// TIFR : interrupt flag register
	while((TIFR&0x01)==0);
	TCCR0 = 0;
	TIFR = 0x01;
}

