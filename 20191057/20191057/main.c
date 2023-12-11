/*
 * 20191057.c
 *
 * Created: 2023-12-11 오후 3:06:05
 * Author : 유창현
 */ 
#include "sound.h" // F_CPU가 포함되어 있음.
#define __DELAY_BACKWARD_COMPATIBLE__
#define PRESCALER 32

#include "fnd.h"
#include "board.h"
#include "uart.h"
#include "musical_notes.h"
#include "music_data1.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define FND_ON 0
#define LED_FLAG 1
#define MUSIC_ON 2

volatile uint16_t fnd_num = 255;
volatile uint8_t Command;

// music
volatile uint8_t note_index = 0;
volatile uint16_t array_size = sizeof(m_notes) / sizeof(uint16_t); 

/************************************************************************/
// 0 : fnd_on / off;            
// 1 : led_on/off    
// 2 : music on/off                                                 
/************************************************************************/
volatile uint8_t flags = 0;

void ioport_init(){
	DDRE = _BV(SOUND_OUT);

	DDRC = 0xff;
	DDRG = _BV(PG0)|_BV(PG1)|_BV(PG2);
	
	PORTE = _BV(SW2);
}

void interrupt_init(void){
	EICRB = _BV(ISC71); // INT7 falling edge setting
	EIMSK = _BV(INT7); // Enable INT3, INT7 (SW2)
	sei(); // global interrupt enable
}

ISR(USART0_RX_vect){
	Command = uart_getch();
	if(Command=='O' || Command == 'o'){ // 6
		flags ^= (0x00) | _BV(LED_FLAG);
		if(flags & _BV(LED_FLAG)){
			led_write(0xff);
		}else{
			led_write(0x00);
		}
	}else if(Command=='S' || Command == 's' || (Command >= '0'&&Command <= '9')){ // 5
		if(Command=='S' || Command == 's'){
			flags ^= (0x00) | _BV(MUSIC_ON);
		}
		uart_putch(Command);
	}else if(Command == 0x0D){ // 7
		uart_putch('\r');
		uart_putch('\n');
	}
}

void timer_init(){
	TCCR3A = _BV(COM3A0); // toggle OC3A on compare
	TCCR3B = _BV(WGM32); // CTC
	OCR3A = 250; // compare match (250)
	
	// FND
	// Timer5 CTC mode
	TCCR5B = _BV(WGM52) | _BV(WGM50) | _BV(WGM51); // CTC
	OCR5A = (F_CPU / (PRESCALER * 10)); //100ms, 이때 F_CPU는 16000000
	TIMSK5 = _BV(OCIE5A); // compare match interrupt activate
}

ISR(INT7_vect){
	if(!(flags & _BV(FND_ON))){
		fnd_num = 255;
	}
	flags ^= (0x00) | _BV(FND_ON);
	
}

ISR(TIMER5_COMPA_vect){	if(flags & _BV(FND_ON)){		fnd_write_numbers(fnd_num);		fnd_num--; // FND 값 감소
	}
}

int main(void)
{
	ioport_init();
	fnd_init();
	interrupt_init();
	timer_init();
	
	uart_init();
	
	led_write(0xCC); // 리셋 후 상태
	
    while (1) 
    {
		if(flags&_BV(MUSIC_ON)){
			if(m_notes[note_index] != 0){ // 소리가 날시
				sound_set_frequency(m_notes[note_index]);
				} else { // 소리가 나지 않을 시
				sound_mute();
			}
			_delay_ms(m_duration[note_index] * music_tempo);
			note_index++;
			if(note_index == array_size){ // 노트 인덱스 초기화
				note_index = 0;
			}else{
				sound_mute();
			}
		}
		
    }
}

