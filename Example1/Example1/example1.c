/*
 * Example1.c
 *
 * Created: 2023-09-21 오전 4:58:41
 * Author : 유창현
 */ 

#include <avr/io.h>


int main(void)
{
    DDRC = 0x0f;
    PORTE = 0x80; // 0000 1000 : e번은 현재 입력이므로, 7번비트 pull-up
    while(1) {
	    if(PINE&0x80)
			PORTC |= 0x0f;
	    else
			PORTC &= ~0x0f;
    }
}

