/*
 * extern_interrupt_example.c
 *
 * Created: 2023-10-18 오후 9:48:56
 * Author : 유창현
 */ 

#include "board.h"
#include <avr/io.h>
#include <util/delay.h>
#include "fnd.h"

uint16_t fnd_num;

void interrupt_init(void);

ISR(INT3_vect){
	fnd_num++;
	if(fnd_num == 1000) // 999를 넘지 않도록 제한
	fnd_num = 0;
	fnd_write_numbers(fnd_num); // fnd에 숫자 쓰기
}
ISR(INT7_vect){
	if(fnd_num == 0) // 0일 경우 999에서 내려오도록 제한
	fnd_num = 999;
	else
	fnd_num--; // fnd_num 감소
	fnd_write_numbers(fnd_num); // fnd에 숫자 쓰기
}

int main(void)
{
    ioport_init();
    interrupt_init();
    fnd_init();
    fnd_write_numbers(0);
	
	uint8_t led_patterns[] = { 0x81, 0xc3, 0xe7, 0xff, 0x7e, 0x3c, 0x18, 0x00};
	uint8_t pattern_num = 0;
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

void interrupt_init(void){
	EICRA = _BV(ISC31); // INT3 falling edge setting
	
	EIMSK = _BV(INT7) | _BV(INT3); // Enable INT3, INT7
	sei(); // global interrupt enable
}

