/*
 * adc_util.c
 *
 * Created: 2023-11-29 오후 10:19:55
 *  Author: 유창현
 */ 

#include <avr/io.h>
#include "adc_util.h"

uint16_t num = 0;

void adc_init(void) {
	// ADC enable, single conversion 모드
	ADCSRA = _BV(ADEN);

	// AD 변환 범위는 0 ~ AVCC
	//ADMUX = 0;
	ADMUX |= _BV(REFS0);

	// F_CPU / ADC clock = Prescaler value.
	// 16,000,000 Hz / 200,000 Hz = 80
	// 16,000,000 Hz / 50,000 Hz = 320
	// ADC clock prescaler 설정: 16MHz / 128 = 125 KHz
	ADCSRA |= _BV(ADPS2) | _BV(ADPS1) | _BV(ADPS0);
	
	 // Free Running 모드 설정
    //ADCSRA |= _BV(ADATE);
	ADCSRA |= _BV(ADIE);
}

uint16_t adc_get_result(uint8_t channel_num) {
	// channel_num이 0 ~ 7 사이인 경우, ADMUX 설정
	ADMUX = (ADMUX & 0xF8) | (channel_num & 0x07);

	// AD 변환 시작
	ADCSRA |= _BV(ADSC);

	// AD 변환이 끝날 때까지 기다림
	while (ADCSRA & _BV(ADSC));

	// 변환 결과 반환
	return ADC;
}
