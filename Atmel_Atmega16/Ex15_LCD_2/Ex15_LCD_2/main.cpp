/*
 * Ex15_LCD_2.cpp
 *
 * Created: 6/22/2023 9:14:57 PM
 * Author : Ngoc Dai
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/delay.h>
#include <stdio.h>
#include <avr/sfr_defs.h>

#define  DC   DDRC
#define  DD   DDRD
#define  PC   PORTC
#define  PD   PORTD
#define  RS   PINC0
#define  RW   PINC1
#define  RE   PINC2

void setup_lcd(unsigned char x)
{
	PD = x;
	PC &= ~(1<<RS);
	PC &= ~(1<<RW);
	PC |= (1<<RE);
	_delay_ms(1);
	PC &= ~(1<<RE);
	_delay_ms(3);
}

void display_char(unsigned char x)
{
	PD = x;
	PC |= (1<<RS);	
	PC &= ~(1<<RW);
	PC |= (1<<RE);
	_delay_us(1);
	PC &= ~(1<<RE);
	_delay_ms(2);
}

void khoitao(void)
{
	DD = 0xFF;
	DC = 0xFF;
	_delay_ms(20);
	setup_lcd(0x38);		// truyền 8 bit và sử dụng 2 hàng
	setup_lcd(0x0C);		// bật màn hình và tắt con trỏ
	setup_lcd(0x06);		// con trỏ dịch phải
	setup_lcd(0x01);		// xoá màn hình
	setup_lcd(0x80);		// đưa con trỏ về vị trí ban đầu
}

void display_string(char *str)
{
	for(int i = 0; str[i] != 0; i++)
	{
		display_char(str[i]);
	}
}

void display_stringxy(char row, char pos, char *str)
{
	if(row == 0 && pos < 16)
	{
		setup_lcd((pos && 0x0F)|0x80);
	}
	else if (row == 1 && pos < 16)
	{
		setup_lcd((pos&0x0F)|0xC0);
	}
	display_string(str);
}

void clear_lcd()
{
	setup_lcd(0x01);
	setup_lcd(0x80);
}

uint16_t read_adc(unsigned int kenh_adc)
{
	ADMUX = kenh_adc|(1<<REFS0);
	ADCSRA |= (1<<ADSC);
	loop_until_bit_is_set(ADCSRA, ADIF);
	return ADCW;
}


int main(void)
{
	khoitao();
	ADMUX |= (1<<REFS0);
	ADCSRA |= (1<<ADEN)|(1<<ADPS1)|(1<<ADPS0);
	int celcius;
	char nhietdo[7];
	
    while (1) 
    {
		display_stringxy(0, 0, "nhiet do ");
		
		celcius = (float) read_adc(0)/3.41;
		
		sprintf(nhietdo, "%d \377 C", (int) celcius);		
		display_stringxy(1, 0, nhietdo);
    }
}

