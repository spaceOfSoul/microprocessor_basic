/*
 * sound.h
 *
 * Created: 2023-11-08 오후 9:31:54
 *  Author: 유창현
 */ 

#include <avr/io.h>

#ifndef SOUND_H
#define SOUND_H
#define F_CPU 16000000L

void sound_set_frequency(uint16_t freq_hz);
void sound_mute(void);

#endif