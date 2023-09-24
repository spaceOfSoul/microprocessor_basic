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
    PORTE = 0x80; // 0000 1000 : 현재 입력이므로, 7번비트 pull-up
	PORTC = 0x06; // 0000 0110
    while(1) {
	    if(PINE&0x80)
			PORTC = (PORTC & 0xf0) | 0x06; // PORTC의 상위 네비트 유지, 하위 네 비트 =0
			// 이후 0110 켜기
	    else
			PORTC = (PORTC & 0xf0) | 0x09; // 1001 켜기
    }
}

