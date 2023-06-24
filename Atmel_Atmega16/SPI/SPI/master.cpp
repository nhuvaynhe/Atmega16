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

void SPI_Master_Init()
{
	DDRB |= (1<<SCK) | (1<<SS) | (1<<MOSI);
	
	SPCR |= (1<<SPE) | (1<<SPR0) | (1<<MSTR);
	/*
		SPE - 1: Enable SPI
		DORD - 0: MSB of the data transmitted first
		MSTR - 1: Master selected
		SPR0 - 1: SCK frequency /16
	*/
	
	sbi(PORTB, SS);
}

void SPI_Transmit(uint8_t data)
{
	SPDR = data;
	
	while(bit_is_clear(SPSR, SPIF));
	/* When a serial transfer is complete, the SPIF flag is set */
}


int main(void)
{
	SPI_Master_Init();
	
    while (1) 
    {
		if(bit_is_clear(PIND, 0))
		{
			cbi(PORTB, SS);	/* Set SS low to begin transmitting data */
			SPI_Transmit(10);
			_delay_ms(10);
			sbi(PORTB, SS);	/* Set SS high to stop transmitting */
		}
		
		else if(bit_is_clear(PIND, 1))
		{
			cbi(PORTB, SS);	/* Set SS low to begin transmitting data */
			SPI_Transmit(16);
			_delay_ms(10);
			sbi(PORTB, SS);	/* Set SS high to stop transmitting */
		}
    }
}

