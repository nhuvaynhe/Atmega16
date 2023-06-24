/*
 * Timer_Bai6.cpp
 *
 * Created: 6/20/2023 2:15:50 PM
 * Author : Ngoc Dai
 */ 

#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
volatile unsigned long dem = 0;


int main(void)
{
	TCCR0 = (1 << CS00) | (1 << CS01); // prescaler = 64
	TCNT0 = 130;	// thanh ghi luu gia tri dem cho phep ngat
	TIMSK |= (1 << TOIE0); // cho phep ngat
	sei();
	
	DDRA = 0x01;
	PORTA = 0x00;
    while (1) 
    {
		if(dem == 500)
		{
			PORTA = ~PORTA;
			dem = 0;
		}
    }
}

ISR(TIMER0_OVF_vect)
{
	TCNT0 = 130; // luu gia tri dem. neu khong co dong nay` no se~ dem tu 0
	dem++;
}