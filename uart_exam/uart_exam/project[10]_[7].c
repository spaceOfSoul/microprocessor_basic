/*
 * uart_exam.c
 *
 * Created: 2023-11-23 오전 12:28:03
 * Author : 유창현
 */ 

#include "board.h"
#include "uart.h"
#include <avr/io.h>
#include <avr/interrupt.h>

ISR(USART0_RX_vect){ // 수신 버퍼를 비움
	UDR0 = UDR0; // data bus를 태움
}

int main(void)
{
	sei();
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

