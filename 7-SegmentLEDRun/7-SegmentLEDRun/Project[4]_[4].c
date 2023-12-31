/*
 * 7-SegmentLEDRun.c
 *
 * Created: 2023-10-09 오후 12:13:27
 * Author : 유창현
 */ 

#include "board.h"
#include <avr/io.h>
#include <util/delay.h>
#include "fnd.h"

uint8_t switch_hit(void);

int main(void)
{
    ioport_init();
	fnd_init();
	uint16_t i = 0;
	while (1)
	{
		if(i == 1000) {
			i = 0;
		}
		_delay_ms(100); // 0.1초
		fnd_write_numbers(i++); // 숫자 표시
	}
}
uint8_t switch_hit(void)
{
	static uint8_t prev_state= _BV(SW2);
	uint8_t cur_state;
	
	cur_state=PINE&_BV(SW2);
	if(prev_state != cur_state){
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