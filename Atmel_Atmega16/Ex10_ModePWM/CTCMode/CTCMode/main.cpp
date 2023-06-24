/*
 * CTCMode.cpp
 *
 * Created: 6/22/2023 10:58:31 AM
 * Author : Ngoc Dai
 */ 

// CTC: Clear Time on Compare match

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

int main(void)
{
	TCCR0 = (1<<WGM01) | (1<<COM00) | (1<<CS00);   /* CTC mode, toggle on compare match,
                      								clk- no pre-scaling */
	OCR0 = 10;					// compare value
	DDRB = DDRB | (1 << 3);		// set the Pin B3 as the output
    while (1);
}

