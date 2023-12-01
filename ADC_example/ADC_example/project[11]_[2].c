/*
 * ADC_example.c
 *
 * Created: 2023-11-29 오후 10:18:30
 * Author : 유창현
 */ 

#include <avr/io.h>
#include <stdio.h>
#include "adc_util.h"
#include "board.h"
#include "uart.h"

void ioport_init(){
	PORTE = _BV(SW2);
	
	PORTD = _BV(SW3) |_BV(SW4) |_BV(SW5);
}

ISR(USART0_RX_vect‎){
	
}

int main(void)
{
	// initalization
	ioport_init();
	fnd_init();
	adc_init();
	uart_init();
	
	// print format function
	fdevopen(uart_putch, uart_getch);
	
	uint16_t result = 0;
	
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

