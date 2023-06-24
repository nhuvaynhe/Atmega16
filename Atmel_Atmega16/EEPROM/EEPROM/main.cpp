/*
 * EEPROM.cpp
 *
 * Created: 6/24/2023 7:30:39 PM
 * Author : Ngoc Dai
 */ 

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/sfr_defs.h>


void EEPROM_write(unsigned int uiAdress, unsigned char ucData)
{
	/* Wait for completion of previous write */
	while(EECR & (1<<EEWE));
	
	/* Set up address and data registers */
	EEAR = uiAdress;
	EEDR = ucData;
	/* Write logical one to EEMWE */
	EECR |= (1<<EEMWE);
	/* Start eeprom write by setting EEWE */
	EECR |= (1<<EEWE);
}

unsigned char EEPROM_read(unsigned int uiAddress)
{
	/* Wait for completion of previous write */
	while(EECR & (1<<EEWE));
	
	/* Set up address register */	
	EEAR = uiAddress;
	/* Start eeprom read by writing EERE */
	EECR |= (1<<EERE);
	/* Return data from data register */
	return EEDR;
}


	
int main(void)
{
    DDRB = 0x00;
	DDRC = 0xFF;
	DDRD = 0xFF;
	
	int ite = 0;
	
    while (1) 
    {
		if(bit_is_clear(PINB, 0))
		{
			while(bit_is_clear(PINB,0));
			++ite;
			PORTC = ite;
		}
		else if(bit_is_clear(PINB, 1))
		{
			while(bit_is_clear(PINB,1));
			--ite;
			PORTC = ite;
		}
		else if(bit_is_clear(PINB, 2))
		{
			while(bit_is_clear(PINB,2));
			EEPROM_write(ite, 5);
			PORTC = ite;
		}
		else if(bit_is_clear(PINB, 3))
		{
			while(bit_is_clear(PINB, 3));
			PORTD = EEPROM_read(ite);
		}
    }
}

