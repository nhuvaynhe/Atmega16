/*
 * LED_7thanh_Bai5.cpp
 *
 * Created: 6/20/2023 12:25:06 PM
 * Author : Ngoc Dai
 */ 

#define F_CPU 8000000UL

#include <avr/io.h>
#include <avr/delay.h>
#include <avr/interrupt.h>
unsigned char led[10] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};

volatile unsigned long dem = 0;
int i = 0;

void hienthi(unsigned int x) 
{
	int temp, ch, dv;
	temp = x;
	ch = temp / 10;
	dv = temp % 10;
	for(int i = 0; i < 3; i++) {
		// hien thi hang chuc
		PORTB = 0x00;
		PORTB = (1 << PINB0);
		PORTA = led[ch];
		_delay_ms(0.5);
		// hien thi hang don vi
		PORTB = 0x00;
		PORTB = (1 << PINB1);
		PORTA = led[dv];
		_delay_ms(0.5);
	}
}

int main(void)
{
    DDRB = (1 << PINB0) | (1 << PINB1);
	PORTB = (0 << PINB0) | (0 << PINB1);
	DDRA = 0xFF;
	PORTA = 0x00;
	// timer
	TCCR0 = (1 << CS00) | (1 << CS01);
	TCNT0 = 130;
	TIMSK = (1 << TOIE0);
	sei();
	
	while(1) 
	{
		hienthi(i);
		if (dem >= 1000) {
			i++;
			hienthi(i);
			dem = 0;
		}
	}
}

ISR(TIMER0_OVF_vect)
{
	TCNT0 = 130;
	dem++;
}