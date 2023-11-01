/*
 * timer_basic.c
 *
 * Created: 2023-11-01 오후 10:56:45
 * Author : 유창현
 */ 

#include <avr/io.h>
#define _BV(n) (1<<n)

void timer_init(void)
{
	// Timer3 설정
	TCCR3B = _BV(WGM32) | _BV(CS31);  // CTC 모드, prescaler 8
	OCR3A = 249;  // 250 클럭 마다 compare match 발생

	// Timer5 설정
	TCCR5B = _BV(CS51) | _BV(CS50);  // Normal 모드, prescaler 64
}


#include <avr/io.h>

//int main(void)
//{
	//DDRE = _BV(PE3);  // PE3를 출력으로 설정
	//timer_init();
	//while (1)
	//{
		//if (TIFR3 & _BV(OCF3A))  // Timer3 compare match check
		//{
			//PORTE ^= _BV(PE3);  // PE3의 값을 반전
			//TIFR3 |= _BV(OCF3A);  // 플래그 초기화
		//}
	//}
//}

ISR(TIMER5_OVF_vect)
{
	PORTB ^= _BV(PB5);  // PB5의 값을 반전
	TCNT5 = 0xC350;
}


int main(void)
{
	DDRB = _BV(PB5);  // PB5를 출력으로 설정
	timer_init();
	TCNT5 = 0xC350; // overflow value set

	while (1)
	{
		if (TIFR5 & _BV(TOV5))  // Timer5 overflow check
		{
			PORTB ^= _BV(PB5);  // PB5의 값을 반전
			TIFR5 |= _BV(TOV5);  // 플래그 초기화
		}
	}
}
