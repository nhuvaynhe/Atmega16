/*
 * Ex10.cpp
 *
 * Created: 6/21/2023 9:59:19 PM
 * Author : Ngoc Dai
 */ 

#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/delay.h>

void PWM_unit()
{
	/* See Fast PWM mode with non-inverted output
	   prescaler = 8 */
	TCCR0 = (1<<WGM00) | (1<<WGM01) | (1<<COM01) | (1<<CS01);
	DDRB = (1<<PB3);
}

int main(void)
{
    unsigned char duty;
	
	PWM_unit();
    while (1) 
    {
		for(duty = 0; duty < 255; ++duty) {
			OCR0 = duty;	// increase the LED light intensity
			_delay_ms(8);
		} 
		
		for(duty = 255; duty > 1; duty--) {
			OCR0 = duty;	// decrease the LED light intensity
			_delay_ms(8);
		}
		
    }
}

