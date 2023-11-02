/*
 * timer_basic.c
 *
 * Created: 2023-11-01 오후 10:56:45
 * Author : 유창현
 */ 

#include <avr/io.h>
#include "board.h"
#include "fnd.h"
#define _BV(n) (1<<n)

void timer_init(void)
{
	TCCR3A = _BV(COM3A0); // Control Register A
	// 타이머가 OCR3와 일치할때 OC3A(PE3)를 토글
	
	// Timer3 설정
	TCCR3B = _BV(WGM32) | _BV(CS31);  // CTC 모드, prescaler 8
	OCR3A = 249;  // 250 클럭 마다 compare match 발생

	// Timer5 설정
	TCCR5B = _BV(CS51) | _BV(CS50);  // Normal 모드, prescaler 64
	TCNT5 = 0xF63B;
	
	TIMSK5 = _BV(TOIE5); //overflow 인터럽트 활성화
}

void interrupt_init(){
	sei();
}

void ioport_init(void)
{
	DDRE = _BV(PE3);	// PE3 outout으로 설정
	DDRB = _BV(PB5);		// PE5 outout으로 설정
}

ISR(TIMER5_OVF_vect)
{
	TCNT5 = 0xF63B;
	PORTB ^= _BV(PB5);	// PB5 반전
}

int main(void)
{
	timer_init();
	ioport_init();
	sei();
	
	while(1)
	{
	}
}