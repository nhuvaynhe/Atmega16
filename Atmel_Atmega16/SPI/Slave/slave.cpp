/*
 * Ex17_SPI.cpp
 *
 * Created: 6/24/2023 3:35:57 PM
 * Author : Ngoc Dai
 */ 

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/sfr_defs.h>

#define cbi(port, bit)	((port) &= ~(1 << (bit)))
#define sbi(port, bit)	((port) |= (1 << (bit)))

#define SCK 7
#define SS 4
#define MOSI 5

void SPI_Slave_Init()
{
	DDRB |= (1<<MOSI);
	
	SPCR |= (1<<SPE) | (1<<SPIE);
	/*
		SPIE - 1: Enable Interrupt
		SPE - 1: Enable SPI
		DORD - 0: MSB of the data transmitted first
		MSTR - 0: Slave selected
		SPR0 - 1: SCK frequency /16
	*/
}

int main(void)
{
	DDRA = 0xff;
	SPI_Slave_Init();
	sei();
	
    while (1) 
    {
		
    }
}

ISR(SPI_STC_vect)
{
	if(SPDR == 10)
	{
		PORTA = 0x01;
	}
	else if(SPDR == 16)
	{
		PORTA = (1 << PINA1);
	}
}