/*
 * 7-SegmentLEDRun.c
 *
 * Created: 2023-10-09 오후 12:13:27
 * Author : 유창현
 */ 

#include <avr/io.h>
#include "board.h"
#include "fnd.h"
int main(void)
{
    ioport_init();
	fnd_init();
	while(1){
		fnd_write_numbers(948);
	}
}

