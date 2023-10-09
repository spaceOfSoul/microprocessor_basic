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
		if (switch_hit()) // switch click
			PORTC ^=  _BV(PC3) | _BV(PC2) | _BV(PC1) | _BV(PC0); // pc1~pc3 반전
	}
}

uint8_t switch_hit(void) {
	static uint8_t prev_state = _BV(PE7); // 이전상태를 저장하는 정적 변수. 초기화 시 PE7 위치의 비트는 1, 나머지는 0으로 초기화.
	
	uint8_t cur_state; // 현재 상태

	cur_state = PINE & _BV(PE7); // PE7의 상태만을 추출

	if(prev_state != cur_state) { // 이전 상태와 현재 상태가 다른지 검사
		prev_state = cur_state; // 현재 상태를 이전 상태로 업데이트

		// 현재 상태가 0 (스위치가 눌린 상태)이면 1을 반환
		if(!cur_state)
			return 1;
		else // 그렇지 않으면 0을 반환
			return 0;
	}
	else
		return 0; // 이전 상태와 현재 상태가 같다면 0을 반환
}