/*
 * LEDFlashControl_IOPort.c
 *
 * Created: 2023-10-07 오후 4:58:33
 * Author : 유창현
 */ 

#include <avr/io.h>
#define _BV(bit) (1 << (bit))

uint8_t switch_hit(void);

int main(void)
{
	DDRC = _BV(PC3) | _BV(PC2) | _BV(PC1) | _BV(PC0); // C 포트의 하위 4개 핀을 출력 모드로 설정
	PORTE = _BV(PE7); // E 포트의 7번 핀을 pull-up 상태로 설정
	PORTC = _BV(PC2) | _BV(PC1); // C 포트의 2번 핀과 1번 핀을 HIGH 상태로 설정

	while(1) {
		if (switch_hit())
			PORTC ^=  _BV(PC3) | _BV(PC2) | _BV(PC1) | _BV(PC0); // pc1~pc3 반전
	}
}

uint8_t switch_hit(void) {
	static uint8_t prev_state = _BV(PE7);
	uint8_t cur_state;
	cur_state = PINE&_BV(PE7);
	if(prev_state != cur_state) {
		prev_state = cur_state;
		if(!cur_state) 
			return 1;
		else
			 return 0;
	}
	else
	return 0;
}