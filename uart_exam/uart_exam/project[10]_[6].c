/*
 * uart_exam.c
 *
 * Created: 2023-11-23 오전 12:28:03
 * Author : 유창현
 */ 

#include "board.h"
#include "uart.h"
#include <avr/io.h>

void ioport_init(){
	DDRE = _BV(PE0);
}

int main(void)
{
	uart_init();
	
	uint8_t ch;
    while(1) {
		ch = uart_getch();

		if(ch == 0x0D){
			uart_puts(">> UCSR0B: 0x");
			num2ascii(UCSR0B);
			uart_putch('\n');
		}
		uart_putch(ch);
    }
}

