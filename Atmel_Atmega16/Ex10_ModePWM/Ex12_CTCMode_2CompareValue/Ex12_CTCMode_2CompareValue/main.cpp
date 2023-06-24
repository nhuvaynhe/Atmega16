/*
 * Ex12_CTCMode_2CompareValue.cpp
 *
 * Created: 6/22/2023 11:09:01 AM
 * Author : Ngoc Dai
 */ 

#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

int main(void)
{
	DDRB = DDRB | (1<<3);
    while (1) 
    {
		//CTC mode on, set on match, no pre-scaler
		TCCR0 = (1<<WGM01) | (1<<COM01) | (1<<COM00) | (1<<CS00) | (1<<CS01);
		OCR0 = 69;
		while((TIFR & (0x02)) == 0);
		TIFR = 0x02;
		OCR0 = 99;
		// CTC mode on, clear on match, no pre-scaler
		TCCR0 = (1<<WGM01) | (1<<COM01) | (1<<CS00) | (1<<CS01);
		while((TIFR & (0x02)) == 0);
		TIFR = 0x02;
    }
}

