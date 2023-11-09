/*
 * timer_basic.c
 *
 * Created: 2023-11-01 오후 10:56:45
 * Author : 유창현
 */ 

#define F_CPU 16000000L
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
	TCCR5B = (_BV(CS51) | _BV(CS50) | _BV(WGM52));
	// 주파수가 100이 될 수 있도록
	OCR5A  = (F_CPU/(64*100))-1;
	
	TIMSK5 = _BV(OCIE5A); //overflow 인터럽트 활성화
}

void interrupt_init(){
	sei();
}

void ioport_init(void)
{
	DDRE = _BV(PE3);	// PE3 outout으로 설정
	DDRB = _BV(SOUND_OUT);		// PE5 outout으로 설정
}

ISR(TIMER5_COMPA_vect)
{
	TCNT5 = 0xF63B;
	PORTB ^= _BV(PB5);	// PB5 반전
}

int main(void)
{
	timer_init();
	ioport_init();
	interrupt_init();
	
	while(1)
	{
	}
}