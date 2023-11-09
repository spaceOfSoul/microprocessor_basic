/*
 * sound.c
 *
 * Created: 2023-11-08 오후 9:31:33
 *  Author: 유창현
 */ 
#include "board.h"

void sound_set_frequency(uint16_t freq_hz)
{
	OCR3A = ( (F_CPU / (16*freq_hz)) - 1 ); // OCR3A값 설정
	TCCR3B |= _BV(CS31); // 타이머 precaler
}

void sound_mute(void)
{
	// Timer3의 동작을 정지
	TCCR3B &= ~(_BV(CS31));
	
	// SOUND_OUT이 설정되어 있다면 FOC3A를 설정하여 강제 비교 일치를 발생
	//if(PINE & _BV(SOUND_OUT))
		//TCCR3C |= _BV(FOC3A);
}