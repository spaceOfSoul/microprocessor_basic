/*
 * ADC_example.c
 *
 * Created: 2023-11-29 오후 10:18:30
 * Author : 유창현
 */ 

#include <avr/io.h>
#include <stdio.h>
#include "adc_util.h"
#include "board.h"
#include "uart.h"

void ioport_init(){
	PORTD = _BV(SW3);
}

int main(void)
{
	// initalization
	ioport_init();
	fnd_init();
	adc_init();
}

