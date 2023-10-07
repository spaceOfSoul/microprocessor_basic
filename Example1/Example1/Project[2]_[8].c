/*
 * Example1.c
 *
 * Created: 2023-09-21 오전 4:58:41
 * Author : 유창현
 */ 

#include <avr/io.h>
#define _BV(bit) (1 << (bit))

int main(void)
{
	DDRC = _BV(PC3) | _BV(PC2) | _BV(PC1) | _BV(PC0); // C 포트의 하위 4개 핀을 출력 모드로 설정
	PORTE = _BV(PE7); // E 포트의 7번 핀을 pull-up 상태로 설정
	PORTC = _BV(PC2) | _BV(PC1); // C 포트의 2번 핀과 1번 핀을 HIGH 상태로 설정

	while(1) {
		if (PINE & _BV(PE7))
			PORTC = (PORTC & 0xf0) | (_BV(PC2) | _BV(PC1)); // PORTC의 상위 네비트 유지, 하위 네 비트를 0110으로 설정
		else
			PORTC = (PORTC & 0xf0) | (_BV(PC3) | _BV(PC0)); // PORTC의 상위 네비트 유지, 하위 네 비트를 1001으로 설정
	}
}

