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

void timer_init(void)
{
	TCCR3A = _BV(COM3A0); // Control Register A
	TCCR5A = _BV(COM5B0); // Control Register A

	// 타이머가 OCR3와 일치할때 OC3A(PE3)를 토글
	
	// Timer3 설정
	TCCR3B = _BV(WGM32) | _BV(CS31);  // CTC 모드, prescaler 8
	OCR3A = 249;  // 250 클럭 마다 compare match 발생

	// Timer5 설정
	TCCR5B = (_BV(CS31) | _BV(WGM32));
	OCR3A = OCR3A;
	// 절반으로 나누어 90도만큼의 위상차.
	OCR5B = OCR3A/2;
	
	TIMSK5 = _BV(OCIE5A); //overflow 인터럽트 활성화
}

void interrupt_init(){
	sei();
}

void ioport_init(void)
{
	DDRE = _BV(PE3); // PE3 outout으로 설정
	//DDRB = _BV(PB5); // PE5 outout으로 설정
	DDRE = _BV(PE4); // PE4 핀은 OC3B로서의 기능도 가지고 있다는 것
}

ISR(TIMER5_COMPB_vect)
{
	PORTB ^= _BV(PE3);	// PB3 반전
}

ISR(TIMER3_COMPA_vect)
{
	PORTB ^= _BV(PE4);	// PB4 반전
}

int main(void)
{
	ioport_init();
	timer_init();
	interrupt_init();
	
	while(1)
	{
	}
}