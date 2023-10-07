/*
 * lecture2.c
 *
 * Created: 2023-09-27 오후 10:36:03
 * Author : 유창현
 */ 

#include <avr/io.h>
#include <util/delay.h>
#define F_CPU 16000000UL // 16 MHz

#define _BV(bit) (1 << (bit))

#define LED1 PC0


int main(void)
{
	DDRC |= _BV(LED1);

	while (1)
	{
		PORTC |= _BV(LED1); // LED1 켜기
		_delay_ms(1000);     // 1초 딜레이
		PORTC &= ~_BV(LED1); // LED1 끄기
	}

	return 0;
}

//#define SW2 PE7
//#define LED2 PC1
//#define LED3 PC2
//#define LED4 PC3

//uint8_t switch_hit(void) {
//static uint8_t prev_state = _BV(SW2);
//
//uint8_t cur_state;
//
//cur_state = PINE&_BV(SW2);
//
//if(prev_state != cur_state) {
//prev_state = cur_state;
//
//if(!cur_state)
//return 1;
//else
//return 0;
//}
//else
//return 0;
//}