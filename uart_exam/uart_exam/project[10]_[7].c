/*
 * uart_exam.c
 *
 * Created: 2023-11-23 오전 12:28:03
 * Author : 유창현
 */ 

#include "board.h"
#include "uart.h"
#include <avr/io.h>

int main(void)
{
	uart_init();
	fdevopen(uart_putch, uart_getch);
	
    uint8_t ch;
    while(1) {
	    ch = uart_getch();

	    if(ch == 0x0D){
		    printf(">> UCSR0B: 0x%x\n",UCSR0B);
	    }
	    uart_putch(ch);
    }
}

