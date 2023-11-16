/*
 * project_9___1_.c
 *
 * Created: 2023-11-16 오후 12:10:19
 *  Author: 유창현
 */ 
#include "board.h"
#include "fnd.h"
#include "signal_table.h"
#include <util/delay.h>
#include <avr/io.h>

// global var
uint8_t index;
uint16_t fnd_num;

// function definition
void ioport_init(void)
{
	DDRC = ( _BV(LED1) | _BV(LED2) | _BV(LED3) | _BV(LED4) );
	PORTC = ( _BV(LED1) | _BV(LED2) | _BV(LED3) | _BV(LED4) );
	DDRB = _BV(LED_COLOR);
	DDRE = _BV(SOUND_OUT);
}

void set_timer3_dutycycle(uint8_t dutycycle)
{
	OCR3A = (ICR3/100) * dutycycle; // ICR3 = top
}

void interrupt_init(void)
{
	sei();
}

void timer_init(void)
{
	// Timer2 설정: Fast PWM 모드, Mode 3, Prescaler = 1, COM2A1 = 1, COM2A0 = 0
	TCCR2A = _BV(COM2A1) | _BV(WGM21) | _BV(WGM20); // Fast PWM mode
	TCCR2B = _BV(CS20); // Prescaler = 1
	OCR2A = 127; // Duty Cycle 50%

	// Timer3 설정: Phase Correct PWM 모드, Mode 10, Prescaler = 8, COM3A1 = 1, COM3A0 = 0
	TCCR3A = _BV(COM3A1) | _BV(WGM31); // Mode 10: Phase Correct PWM
	TCCR3B = _BV(WGM33) | _BV(CS31); // Prescaler = 8
	ICR3 = 1000; // 1 KHz 주파수 설정
	OCR3A = 500; // Duty Cycle 50%

	// Timer5 설정: CTC 모드, Prescaler = 8
	TCCR5A = 0; // CTC 모드 설정
	TCCR5B = _BV(WGM52) | _BV(CS51); // Prescaler = 8
	TIMSK5 = _BV(OCIE5A); // OCR5A 비교 일치 인터럽트 활성화
	OCR5A = F_CPU/(8*256*4-1); ; // 256×4 Hz 주파수 설정
}

// ISR section

ISR(TIMER5_COMPA_vect){
	OCR2A = signal_table[index++];
}

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