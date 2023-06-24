/*
 * LED_8_Bai2.cpp
 *
 * Created: 6/20/2023 9:35:55 AM
 * Author : Ngoc Dai
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/delay.h>


int main(void)
{
    /* Replace with your application code */
	DDRA = 0xFF;	// turn 8 led into the output
	PORTA = 0x00;	// 
	DDRB = 0x00;	// set the button as the input
	PORTB = 0x01;	// set 5V for the button
	int ite = 0;
    while (1) 
    {
		if((PINB & (1 << PINB0)) == 0)
		{
			while((PINB & (1 << PINB0)) == 0)
			{
				
			}
			
			if(ite == 0) 
				PORTA = 0x01;
			else 
				PORTA = PORTA << 1;
			
			++ite;
			if(ite == 9) {
				ite = 0;
				PORTA = 0x00;
			}
		}
    }
}

