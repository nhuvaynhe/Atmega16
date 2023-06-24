/*
 * Dongho_Bai8.cpp
 *
 * Created: 6/21/2023 10:31:26 AM
 * Author : Ngoc Dai
 */ 

#define F_CPU 8000000UL

#include <avr/io.h>
#include <avr/delay.h>
#include <avr/interrupt.h>
unsigned char led[10] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};

volatile unsigned long dem = 0;
int sec = 0;
int min = 0;
int hr = 0;

void Second(unsigned int x)
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

void Minute(unsigned int x)
{
	int temp, ch, dv;
	temp = x;
	ch = temp / 10;
	dv = temp % 10;
	for(int i = 0; i < 3; i++) {
		// hien thi hang chuc
		PORTB = 0x00;
		PORTB = (1 << PINB2);
		PORTC = led[ch];
		_delay_ms(0.5);
		// hien thi hang don vi
		PORTB = 0x00;
		PORTB = (1 << PINB3);
		PORTC = led[dv];
		_delay_ms(0.5);
	}
}

void Hour(unsigned int x)
{
	int temp, ch, dv;
	temp = x;
	ch = temp / 10;
	dv = temp % 10;
	for(int i = 0; i < 3; i++) {
		// hien thi hang chuc
		PORTB = 0x00;
		PORTB = (1 << PINB4);
		PORTD = led[ch];
		_delay_ms(0.5);
		// hien thi hang don vi
		PORTB = 0x00;
		PORTB = (1 << PINB5);
		PORTD = led[dv];
		_delay_ms(0.5);
	}
}

int main(void)
{	
	//For the transistor
	DDRB = 0b00111111; 
	PORTB = 0x00;
	// Second
	DDRA = 0xFF;
	PORTA = 0x00;
	// Minute
	DDRC = 0xFF;
	PORTC = 0x00;
	// Hour
	DDRD = 0xFF;
	PORTD = 0x00;
	// Timer
	TCCR0 = (1 << CS00) | (1 << CS01);	// prescaler = 64
	TCNT0 = 130;
	TIMSK = (1 << TOIE0);
	sei();
	
	while(1)
	{
		Second(sec);
		Minute(min);
		Hour(hr);
		if (dem >= 5) {
			sec++;
			dem = 0;
			if(sec < 60) {
				Second(sec);
				Minute(min);
				Hour(hr);
			}
			else {
				min++;
				if (!(min < 60)) {
					min = 0;
					hr = (hr < 60) ? ++hr : 0;
				}
				sec = 0;
				Hour(hr);
				Second(sec);
				Minute(min);
			}
		}	
	}
}

ISR(TIMER0_OVF_vect)
{
	TCNT0 = 130;
	dem++;
}

