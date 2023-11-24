/*
 * uart_exam.c
 *
 * Created: 2023-11-23 오전 12:28:03
 * Author : 유창현
 */ 

#include "board.h"
//#include "fnd.h"
#include "uart.h"
#include <avr/io.h>
#include <avr/interrupt.h>

ISR(USART0_RX_vect){
	UDR0 = UDR0;
}

int main(void)
{
	uart_init();
	sei();

	fdevopen(uart_putch, uart_getch);
	
	while(1);
}

