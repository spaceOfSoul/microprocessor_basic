/*
 * timer_speakerFunction.c
 *
 * Created: 2023-11-06 오후 9:59:28
 * Author : 유창현
 */ 

#include <avr/io.h>
#include "musical_notes.h"

#define _BV(n) (1<<n)

#define F_CPU 16000000L
#define PRESCALER 64
#define TIMER3_COMPARE_VALUE 250
#define TIMER5_COMPARE_VALUE (F_CPU / (PRESCALER * 10))

void timer_init(void) {
	// Timer3 CTC mode
	TCCR3A = _BV(COM3A0); // toggle OC3A on compare
	TCCR3B = _BV(WGM32); // CTC
	OCR3A = TIMER3_COMPARE_VALUE; // compare match (250)

	// Timer5 CTC mode
	TCCR5B = _BV(WGM52);  // CTC
	OCR5A = TIMER5_COMPARE_VALUE; //100ms (F_CPU / (PRESCALER * 10))
	TIMSK5 =  _BV(OCIE5A); // compare match interrupt activate
}

void interrupt_init(void) {
	// INT3, INT7 falling edge setting
	EICRA |=  _BV(ISC31);
	EICRB |=  _BV(ISC71);
	EIMSK |=  _BV(INT3) |  _BV(INT7); // INT3, INT7 activcate

	// interupt activate
	sei();
}

int main(void)
{
    /* Replace with your application code */
    while (1) 
    {
    }
}

