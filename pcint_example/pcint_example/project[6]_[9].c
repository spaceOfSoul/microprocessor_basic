/*
 * project_6___9_.c
 *
 * Created: 2023-10-26 오후 3:27:42
 *  Author: 유창현
 */ 
/*
 * pcint_example.c
 *
 * Created: 2023-10-26 오전 12:11:32
 * Author : 유창현
 */ 
#include "board.h"
#include "fnd.h"
#include <util/delay.h>
#include <avr/io.h>

void ioport_init(void);
void interrupt_init(void);

uint16_t fnd_num;
uint8_t pattern_num = 0;
uint8_t led_patterns[] = { 0x81, 0xc3, 0xe7, 0xff, 0x7e, 0x3c, 0x18, 0x00};

ISR(PCINT0_vect)
{
	static uint8_t prev_pb5 = _BV(PINB5); // 각 스위치들의 이전 상태
	static uint8_t prev_pb6 = _BV(PINB6); 
	
	uint8_t cur_state_5 = PINB & _BV(PINB5);
	uint8_t cur_state_6 = PINB & _BV(PINB6);
	
	if(cur_state_5!=prev_pb5){
		if(cur_state_5){
			fnd_num++;  // FND숫자 증가
			if(fnd_num == 1000)
				fnd_num = 0;
		}
		prev_pb5=cur_state_5;
	}else if(cur_state_6!=prev_pb6){
		if(cur_state_6){
			if(fnd_num == 0) // 0일 경우 999에서 내려오도록 제한
				fnd_num = 999;
			else
				fnd_num--;
		}
		prev_pb6=cur_state_6;
	}
	fnd_write_numbers(fnd_num);
}


int main(void)
{
	ioport_init();
	interrupt_init();
	fnd_init();
	fnd_write_numbers(0);
	
	uint8_t pattern = 0;
	
	while (1)
	{
		_delay_ms(250); // 250ms 딜레이
		pattern = led_patterns[pattern_num++%8]; // 패턴 순회
		led_write(pattern); // pattern_num번째의 패턴 출력
	}
}
void ioport_init(void){
	DDRC = _BV(LED1) | _BV(LED2) | _BV(LED3) | _BV(LED4); // DDRC를 출력으로
	PORTC = _BV(LED1) | _BV(LED2) | _BV(LED3) | _BV(LED4); // LED를 모두 끈다.
	
	PORTE = _BV(SW2); // MCU 보드의 SW2가 연결된 Pin의 내부 pull-up 저항을 Enable 시킨다.
	
	// 확장 보드의 SW3, SW4, SW5가 연결된 pin의 내부 pull-up 저항을 Enable 시킨다.
	PORTD = _BV(SW3) |_BV(SW4) |_BV(SW5);
}

void interrupt_init(void)
{
	// PCINT5와 PCINT6을 PCINT 입력으로 사용하도록 PCMSK0 레지스터를 설정.
	PCMSK0 = _BV(PCINT5) | _BV(PCINT6);
	// PCINT0 활성화(PCIE0 비트를 설정)
	PCICR = _BV(PCIE0);
	// 전역 인터럽트 활성화
	sei();
}