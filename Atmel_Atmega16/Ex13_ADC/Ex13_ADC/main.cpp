/*
 * Ex13_ADC.cpp
 *
 * Created: 6/22/2023 12:24:45 PM
 * Author : Ngoc Dai
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/delay.h>
#include <avr/sfr_defs.h>

unsigned char led[12] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90, 0x9C, 0xC6};
int adc_val;

void hienthi(int x) 
{
	uint16_t temp, dv, ch;
	temp = x;
	dv = temp%10;
	ch = temp/10;
	for(int i = 0; i < 20; i++)
	{
		// ten
		PORTD = 0x00;
		PORTD = (1 << PIND0);
		PORTC = led[ch];
		_delay_ms(1);
		// unit
		PORTD = 0x00;
		PORTD = (1 << PIND1);
		PORTC = led[dv];
		_delay_ms(1);
		// celcius notation
		PORTD = 0x00;
		PORTD = (1 << PIND2);
		PORTC = led[10];
		_delay_ms(5);
		// celcius symbol
		PORTD = 0x00;
		PORTD = (1 << PIND3);
		PORTC = led[11];
		_delay_ms(5);
		}	
	
}

uint16_t read_adc(unsigned int kenh_adc)
{
	ADMUX = kenh_adc | (1<<REFS0);
	ADCSRA |= (1 << ADSC);		// ADSC: ADC start conversion
	loop_until_bit_is_set(ADCSRA, ADIF);	
	// ADIF: ADC Interrupt Flag
	return ADCW;
	// Save the value
}

int main(void)
{	
	ADMUX |= (1<<REFS0);		// Select ADC reference voltage
	ADCSRA |= (1<<ADEN)|(1<<ADPS1)|(1<<ADPS0);
	/*
		ADEN: ADC enable
		ADPSx: ADC prescaler select bits
	*/
	DDRC = 0xFF;
	DDRD = (1<<PIND0) | (1<<PIND1) | (1<<PIND2) | (1<<PIND3); 
    while (1) 
    {
		adc_val = (int)(read_adc(0)/3.41);
		hienthi(adc_val);
    }
}

