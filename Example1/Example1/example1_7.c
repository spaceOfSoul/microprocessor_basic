/*
 * example1_7.c
 *
 * Created: 2023-09-21 오전 10:07:47
 *  Author: 유창현
 */ 

#include <avr/io.h>


int main(void)
{
    DDRC = 0x0f;
    PORTE = 0x80; // 0000 1000 : 현재 입력이므로, 7번비트 pull-up
	PORTC = 0x06; // 0000 0110
    while(1) {
	    if(PINE&0x80)
			PORTC |= 0x06;
	    else
			PORTC &= ~0x06;
    }
}

