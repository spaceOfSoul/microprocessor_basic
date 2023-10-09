/*
 * LEDFlashControl_IOPort.c
 *
 * Created: 2023-10-07 오후 4:58:33
 * Author : 유창현
 */ 
#define F_CPU 16000000L

#include <avr/io.h>
#include <util/delay.h>
#define _BV(bit) (1 << (bit))

uint8_t switch_hit(void);

int main(void)
{
	uint8_t i = 0;
	uint8_t direction = 0; // 0 : forward, 1: reverse
	uint8_t led_pattern[4] = {_BV(2) | _BV(3), _BV(0) | _BV(3),_BV(0) | _BV(1),_BV(1) | _BV(2)};  // 각 패턴에 대한 테이블
	uint16_t cycle; // 1ms만큼 딜레이할 횟수. 즉, 딜레이될 밀리초를 저장한다.
	
	DDRC = _BV(PC3) | _BV(PC2) | _BV(PC1) | _BV(PC0); // C 포트의 하위 4개 핀을 출력 모드로 설정
	PORTE = _BV(PE7); // E 포트의 7번 핀을 pull-up 상태로 설정
	PORTC = led_pattern[i]; // C 포트의 2번 핀과 1번 핀을 HIGH 상태로 설정

	while(1) {
		cycle = 1000;
		while(cycle--){ // cycle 만큼 반복 (1000번 반복)
			_delay_ms(1);
			if(switch_hit()){// 스위치가 눌릴시
				direction = !direction; // 방향전환
			}
		}
		
		if(direction){ // 방향이 역방향일 시
			i = (i == 0) ? 3 : i - 1; // 범위 이내에서 감소
		}else{ // 정방향일 시 ( direction = 0 )
			i++;
			i = i%4; // 범위 이내에서 증가
		}
		PORTC = (PORTC & 0xf0) | led_pattern[i]; // 패턴 순회
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