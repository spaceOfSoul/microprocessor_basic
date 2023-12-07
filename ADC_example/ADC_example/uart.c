/*
 * uart.c
 *
 * Created: 2023-11-23 오전 2:47:53
 *  Author: 유창현
 */ 
#include "board.h"
#include <avr/io.h>

void uart_init(void) {
	#define BAUDRATE 115200L
	UBRR0 = (F_CPU/8.)/BAUDRATE - 0.5;  // UBRR0H 설정

	UCSR0A |= _BV(U2X0);  // U2X0를 1로 설정

	UCSR0B = _BV(RXEN0) | _BV(TXEN0) | _BV(RXCIE0);   // 수신과 송신 enable, 수신완료 인터럽트 활성화
	UCSR0C = _BV(UCSZ01) | _BV(UCSZ00); // 8 데이터 비트, 1 스톱 비트, no parity
}

int8_t uart_getch(void) {
	while (!(UCSR0A & _BV(RXC0))); // 수신 버퍼가 찰 때까지 기다림
	return UDR0; // 수신한 값 반환
}

void uart_putch(int8_t ch) {
	while (!(UCSR0A & _BV(UDRE0))); // 송신 버퍼가 빌 때까지 기다림
	UDR0 = ch; // ch 값을 송신
}

void uart_puts(int8_t *str) {
	while (*str) {
		uart_putch(*(str++));
	}
}

void num2ascii(int8_t ch) {
	int8_t tmp;

	// 상위 4 비트 처리
	tmp = (ch >> 4) & 0x0f;
	if (tmp >= 0 && tmp <= 9)
	uart_putch(tmp + '0');  // 0-9 사이의 값
	else
	uart_putch(tmp + 'A' - 10);  // A-F 사이의 값

	// 하위 4 비트 처리
	tmp = ch & 0x0f;
	if (tmp >= 0 && tmp <= 9){
		uart_putch(tmp + '0');  // 0-9 사이의 값	
	}
	else{
		uart_putch(tmp + 'A' - 10);  // A-F 사이의 값	
	}
}
