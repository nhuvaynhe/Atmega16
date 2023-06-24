/*
 * Ex11_PhaseCorrectPWM.cpp
 *
 * Created: 6/21/2023 10:10:39 PM
 * Author : Ngoc Dai
 */ 

#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/delay.h>

void PhaseCorrectPWM() 
{
	TCCR0 = (1<<WGM00) | (1<<COM01) | (1<<CS01);
	DDRB |= (1<<PB3); 
}

int main(void)
{
    unsigned char duty;
	
	PhaseCorrectPWM();
    while (1) 
    {
		for(duty = 0; duty < 255; ++duty) {
			OCR0 = duty;
			_delay_ms(10);
		}
		
		for(duty = 255; duty > 1; --duty) {
			OCR0 = duty;
			_delay_ms(10);
		}
    }
}

