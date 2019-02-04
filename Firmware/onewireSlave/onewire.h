/*
   Lulu-MCU 4.0.0
   This file is part of Lulu-MCU project: http://lulu.eTextile.org
   It has been foked from Kevin Cuzner : https://github.com/kcuzner/onewire-leds
   This code implement 1-Wire modified protocol for ATTiny10 - 1-Wire: https://en.wikipedia.org/wiki/1-Wire
*/

#ifndef _ONEWIRE_H_
#define _ONEWIRE_H_

#include <avr/io.h>

#define ONEWIRE_DDR   DDRB
#define ONEWIRE_INPUT PINB // Port B Input Pins Address
#define ONEWIRE_PIN   2    // 

void set_cpu_8Mhz(void);

// Initializes the one-wire bus
void onewire_init(void);

// Returns whether or not the 1-wire bus has decoded a new byte
uint8_t onewire_has_new_byte(void);

// Reads the last byte that has been read
uint8_t onewire_get_byte(void);

#endif //_ONEWIRE_H_
