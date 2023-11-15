/*
 * timer_speakerFunction.c
 *
 * Created: 2023-11-06 오후 9:59:28
 * Author : 유창현
 */ 

#define F_CPU 16000000L
#define PRESCALER 64
#define TIMER3_COMPARE_VALUE 250
#define TIMER5_COMPARE_VALUE (F_CPU / (PRESCALER * 10))
#define __DELAY_BACKWARD_COMPATIBLE__ // 딜레이의 매개인자로 변수를 넘기기 위함.
#define _BV(n) (1<<n)

#include "board.h"
#include "fnd.h"
#include "musical_notes.h"
#include "music_data.h"
#include <avr/io.h>
#include <util/delay.h>

uint16_t fnd_value = 0;
uint8_t note_index = 0;
uint16_t array_size =  sizeof(m_notes) / sizeof(uint16_t); // 악보의 길아

void timer_init(void) {
	// Timer3 CTC mode
	TCCR3A = _BV(COM3A0); // toggle OC3A on compare
	TCCR3B = _BV(WGM32); // CTC
	OCR3A = 250; // compare match (250)

	// Timer5 CTC mode
	TCCR5B = _BV(WGM52) | _BV(WGM50) | _BV(WGM51);  // CTC
	OCR5A = (F_CPU / (PRESCALER * 10)); //100ms, 이때 F_CPU는 16000000
	TIMSK5 =  _BV(OCIE5A); // compare match interrupt activate
}

void interrupt_init(void) {
	// INT3, INT7 falling edge setting
	EICRA |=  _BV(ISC31);
	EICRB |=  _BV(ISC71);
	EIMSK |=  _BV(INT3) |  _BV(INT7); // INT3, INT7 activcate

	// global interupt activate
	sei();
}

void ioport_init(void)
{
	DDRE = _BV(SOUND_OUT);
	
	PORTE = _BV(SW2); // MCU 보드의 SW2가 연결된 Pin의 내부 pull-up 저항을 Enable 시킨다.
	
	PORTD = _BV(SW3);
}

ISR(TIMER5_COMPA_vect){
	fnd_value++; // FND 값 증가
	if (fnd_value > 999) {
		fnd_value = 0; // 다시 0으로
	}

	// write number
	fnd_write_numbers(fnd_value);
}


int main(void)
{
    ioport_init();
    fnd_init();
    timer_init();
    interrupt_init();
    fnd_write_numbers(0);
	
	uint8_t count = 0;

    while (1) 
    {
		if(m_notes[note_index] != 0){ // 소리가 날시
			sound_set_frequency(m_notes[note_index]);
		} else { // 소리가 나지 않을 시
			sound_mute();
		}
		_delay_ms(m_duration[note_index] * 95);
		note_index++;
		if(note_index == array_size){ // 노트 인덱스 초기화
			note_index = 0;
		}
    }
}

