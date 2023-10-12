/*
 * board.c
 *
 * Created: 2023-10-09 오후 12:17:23
 *  Author: 유창현
 */ 

#include "board.h"
#include <avr/io.h>
#include <avr/interrupt.h>

void ioport_init(void){
	DDRC = _BV(LED1) | _BV(LED2) | _BV(LED3) | _BV(LED4); // DDRC를 출력으로
	PORTC = _BV(LED1) | _BV(LED2) | _BV(LED3) | _BV(LED4); // LED를 모두 끈다.
	
	PORTE = _BV(SW2); // MCU 보드의 SW2가 연결된 Pin의 내부 pull-up 저항을 Enable 시킨다.
	
	// 확장 보드의 SW3, SW4, SW5가 연결된 pin의 내부 pull-up 저항을 Enable 시킨다.
	PORTD = _BV(SW3) |_BV(SW4) |_BV(SW5);
}