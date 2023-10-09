/*
 * LEDFlashControl_IOPort.c
 *
 * Created: 2023-10-07 오후 4:58:33
 * Author : 유창현
 */ 
#define F_CPU 16000000L // 클럭 명시

#include <avr/io.h>
#include <util/delay.h>

#define _BV(bit) (1 << (bit))

int main(void)
{
	uint8_t i = 0;
	uint8_t led_pattern[4] = {_BV(2) | _BV(3), _BV(0) | _BV(3),_BV(0) | _BV(1),_BV(1) | _BV(2)}; // 이미지 위의 각 패턴에 대한 테이블
	
	DDRC = _BV(PC3) | _BV(PC2) | _BV(PC1) | _BV(PC0); // C 포트의 하위 4개 핀을 출력 모드로 설정
	PORTE = _BV(PE7); // E 포트의 7번 핀을 pull-up 상태로 설정
	PORTC = led_pattern[i]; // C 포트의 2번 핀과 1번 핀을 HIGH 상태로 설정

	while(1) {
		_delay_ms(1000); // ms 단위의 딜레이
		PORTC = (PORTC & 0xf0) | led_pattern[i++%4]; // 패턴 순환
	}
}