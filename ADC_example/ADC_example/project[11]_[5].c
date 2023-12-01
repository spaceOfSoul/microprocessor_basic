/*
 * ADC_example.c
 *
 * Created: 2023-11-29 오후 10:18:30
 * Author : 유창현
 */ 

#include "board.h"
#include "adc_util.h"
#include "uart.h"
#include "fnd.h"

#include <avr/io.h>
#include <util/delay.h>

uint16_t adc_val = 0;;

void ioport_init(){
	DDRC = _BV(LED1) | _BV(LED2) | _BV(LED3) | _BV(LED4); // DDRC를 출력으로
	PORTC = _BV(LED1) | _BV(LED2) | _BV(LED3) | _BV(LED4); // LED를 모두 끈다.
	
	PORTE = _BV(SW2);
	
	PORTD = _BV(SW3) |_BV(SW4) |_BV(SW5);
}

ISR(USART0_RX_vect){
	if(uart_getch()==0x61){
		uart_puts("it is 'a'\r\n");
		adc_get_result(3);
	}else{
		uart_puts("it's not 'a'\r\n");
	}
}

ISR(ADC_vect){
	fnd_write_numbers(ADC);
}

int main(void)
{
	// initalization
	ioport_init();
	fnd_init();
	adc_init();
	uart_init();
	sei();
	
	uint16_t result = 0;
	
    uint8_t led_patterns[] = { 0x81, 0xc3, 0xe7, 0xff, 0x7e, 0x3c, 0x18, 0x00};
    uint8_t pattern_num = 0;
    uint8_t pattern = 0;
    
    while (1)
    {
	   	_delay_ms(1000); // 250ms 딜레이
	   	pattern = led_patterns[pattern_num++%8]; // 패턴 순회
	   	led_write(pattern); // pattern_num번째의 패턴 출력
    }
}

