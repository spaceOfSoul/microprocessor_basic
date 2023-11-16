/*
 * PWM_moter_control.c
 *
 * Created: 2023-11-15 오후 6:51:31
 * Author : 유창현
 */ 

#include <avr/io.h>

uint8_t signal_table[256];
uint8_t index;

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

ISR(TIMER5_COMPA_vect){
	OCR2A = signal_table[index];
}

void set_timer3_dutycycle(uint8_t dutycycle)
{
	OCR3A = ICR3 * dutycycle; // ICR3 = top
}

int main(void)
{
    while (1) 
    {
    }
}

