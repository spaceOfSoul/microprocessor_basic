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
	
    while (1) 
    {
		if(!(PIND & _BV(SW3))){
			result = adc_get_result(3);
			printf("adc result : %d \n", result);
			fnd_write_numbers(result);
		}
    }
}

