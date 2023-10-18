/*
 * Project_4___3_.c
 *
 * Created: 2023-10-18 오후 12:48:12
 *  Author: 유창현
 */ 
#include "board.h"
#include <avr/io.h>
#include <util/delay.h>
#include "fnd.h"

uint8_t switch_hit(void)
{
	static uint8_t prev_state= _BV(SW2); // 이전 상태 저장
	uint8_t cur_state;
	
	cur_state=PINE&_BV(SW2);
	if(prev_state != cur_state){ // 상태가 변화하였는지
		prev_state = cur_state;
		if(!cur_state)
			return 1;
		else
			return 0;
	}
	else
		return 0;
}

void ioport_init(void){
	DDRC = _BV(LED1) | _BV(LED2) | _BV(LED3) | _BV(LED4); // DDRC를 출력으로
	PORTC = _BV(LED1) | _BV(LED2) | _BV(LED3) | _BV(LED4); // LED를 모두 끈다.
	
	PORTE = _BV(SW2); // MCU 보드의 SW2가 연결된 Pin의 내부 pull-up 저항을 Enable 시킨다.
	
	// 확장 보드의 SW3, SW4, SW5가 연결된 pin의 내부 pull-up 저항을 Enable 시킨다.
	PORTD = _BV(SW3) |_BV(SW4) |_BV(SW5);
}

int main(void)
{
	// initialize on-chip pheriperals 17
	ioport_init(); // initialize gpio
	
	// initialize extension board pheriperals
	fnd_init(); // initialize FNDs and LEDs
	while(1) {
		
	}
}