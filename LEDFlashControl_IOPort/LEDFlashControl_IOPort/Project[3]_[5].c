﻿/*
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
	uint8_t led_pattern[4] = { _BV(PC1) | _BV(PC0),  _BV(PC2) | _BV(PC1),  _BV(PC3) | _BV(PC2),  _BV(PC0) | _BV(PC3)};
	
	DDRC = _BV(PC3) | _BV(PC2) | _BV(PC1) | _BV(PC0); // C 포트의 하위 4개 핀을 출력 모드로 설정
	PORTE = _BV(PE7); // E 포트의 7번 핀을 pull-up 상태로 설정
	PORTC = _BV(PC2) | _BV(PC1); // C 포트의 2번 핀과 1번 핀을 HIGH 상태로 설정

	while(1) {
		uint16_t cycle = 1000;
		while(cycle--){
			_delay_ms(1);
			if(switch_hit()){
				direction = !direction;
				break;
			}
		}
		PORTC = (PORTC & 0xf0) | led_pattern[i]; // 패턴 순환
		
		if(direction){
			i = (i == 0) ? 3 : i - 1;
		}else{
			i++;
			i = i%4;
		}
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