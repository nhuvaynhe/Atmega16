/*
 * Interrupt_Bai3.cpp
 *
 * Created: 6/20/2023 10:38:21 AM
 * Author : Ngoc Dai
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/delay.h>
#include <avr/interrupt.h>


int main(void)
{
    DDRA = 0xFF;
	PORTA = 0x00;
	DDRD = 0b00000001;	// led pin D0, button pin D2
	PORTD = (0 << PIND0);	// pin D0 output 0V
	// Interrupt 
	GICR |= (1 << INT0);	//sử dụng ngắt 0
	MCUCR |= (1 << ISC01);	// kích cạnh xuống
	sei();					//ngắt cục bộ
	
    while (1) 
    {
		PORTA = 0x01;
		_delay_ms(20);
		for(int i = 0; i < 7; i++){
			PORTA = PORTA << 1;
			_delay_ms(20);
		}
    }
}

ISR(INT0_vect) 
{
	if((PIND & (1 << PIND2)) == 0) {
		PORTD = 0x01;
		_delay_ms(50);
		PORTD = 0x00;
	}
}
