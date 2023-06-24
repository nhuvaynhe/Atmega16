/*
 * TimerThayDelay.cpp
 *
 * Created: 6/21/2023 4:17:24 PM
 * Author : Ngoc Dai
 */ 

#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>


int main(void)
{
    DDRB = 0xFF;
	TCNT0 = 177;	// running from 177 to 255
	TCCR0 = (1 << CS02) | (1 << CS00);
	TIMSK = (1 << TOIE0);
	sei();
    while (1) 
    {
		
    }
}

ISR(TIMER0_OVF_vect)
{
	TCNT0 = 177;
	PORTB = ~PORTB;
}

