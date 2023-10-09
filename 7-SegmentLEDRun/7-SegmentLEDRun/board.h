
/*
 * board.h
 *
 * Created: 2023-10-09 오후 12:13:52
 *  Author: 유창현
 */ 
#define F_CPU 16000000L

#include <avr/io.h>
#include <avr/interrupt.h>


// PORTC
#define LED1 PC0
#define LED2 PC1
#define LED3 PC2
#define LED4 PC3
// PORTB
#define LED_COLOR PB4
// PORTD
#define SW3 PD3
#define SW4 PD4
#define SW5 PD5
// PORTE
#define SW2 PE7

#define _BV(bit) 1<<(bit)

void ioport_init(void);