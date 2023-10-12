/*
 * 7-SegmentLEDRun.c
 *
 * Created: 2023-10-09 오후 12:13:27
 * Author : 유창현
 */ 

#include "board.h"
#include "fnd.h"

#include <util/delay.h>

uint8_t switch_hit(void);

int main(void)
{
    ioport_init();
	fnd_init();
	uint16_t i = 0;
	uint8_t increase = 1;
	while (1)
	{
		if(i == 1000) {
			i = 0;
		}
		_delay_ms(100); // 0.1초
		
		if(switch_hit())
			increase = !increase;
		
		fnd_write_numbers(i); // 숫자 표시
		
		if(increase)
			i++;
	}
}
uint8_t switch_hit(void)
{
	static uint8_t prev_state= _BV(SW2);
	uint8_t cur_state;
	
	cur_state=PINE&_BV(SW2);
	if(prev_state != cur_state){
		prev_state = cur_state;
		if(!cur_state)
			return 1;
		else
			return 0;
	}
	else
		return 0;
}
