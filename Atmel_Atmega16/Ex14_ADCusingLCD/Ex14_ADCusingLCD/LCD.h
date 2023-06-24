/*
 * LCD.h
 *
 * Created: 6/22/2023 1:27:48 PM
 * Author : Ngoc Dai
 */ 

#ifdef  _LCD_H_
#define _LCD_H_

#define F_CPU 8000000UL
#include <avr/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sfr_defs.h>

#define sbi(PORT, bit) {PORT |= (1<<bit);}
#define cbi(PORT, bit) {PORT &= ~(1<<bit);}

#define EN				2
#define RW				1
#define	RS				0
#define CTRL		PORTB
#define DDR_CTRL	DDRB

#define DATA_O		PORTB
#define DATA_I		PINB
#define DDR_DATA	DDRB
/*
#define LCD8BIT
#define DATA_O		PORTD
#define DATA_I		PIND
#define DDR_DATA	DDRD
*/

char Read2Nib();
void Write2Nib(uint8_t);
void Write8bit(uint8_t);
void wait_LCD();
void init_LCD();
void clr_LCD();
void move_LCD(uint8_t, uint8_t);
void putChar_LCD(uint8_t);
void print_LCD(char*);


#endif