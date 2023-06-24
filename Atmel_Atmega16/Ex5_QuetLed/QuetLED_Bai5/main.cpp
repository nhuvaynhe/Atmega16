/*
 * QuetLED_Bai5.cpp
 *
 * Created: 6/20/2023 12:40:30 PM
 * Author : Ngoc Dai
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/delay.h>
unsigned char led[10] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};

void hienthi(unsigned int x) 
{
	uint16_t temp, ch, dv;
	// tach va luu vao cac bien hang chuc va don vi
	temp = x;
	dv = temp %10;
	temp = temp /10;
	ch = temp;	
	// hien thi led so 1
	PORTA = 0x00;
	PORTA = 0x01;
	PORTB = led[ch];
	_delay_ms(1);
	// hien thi led so 2
	PORTA = 0x00;
	PORTA = 0x02;
	PORTB = led[dv];
	_delay_ms(1);
}

int main(void)
{
	DDRB = 0xFF;
	PORTB = 0xFF;
	
	DDRA = (1 << PINA0) | (1 << PINA1);
	PORTA = 0x00;
	
	DDRC = (0 << PINA0) | (0 << PINA1);
		
	int i = 0;
    while (1) 
    {	
		hienthi(i);
		
		// nut bam tang
		if((PINC & (1 << PINC0)) == 0)
		{
			while((PINC & (1 << PINC0)) == 0)
			{
				hienthi(i);
			}
			++i;
			hienthi(i);
			if(i > 99)
			{
				i = 0;
				hienthi(i);
			}
		}
		
		// nut bam giam
		if((PINC & (1 << PINC1)) == 0)
		{
			while((PINC & (1 << PINC1)) == 0)
			{
				hienthi(i);
			}
			--i;
			hienthi(i);
			if(i < 0)
			{
				i = 99;
				hienthi(i);
			}
		}
    }
}

