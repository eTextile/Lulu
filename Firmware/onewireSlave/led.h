/*
   Lulu-MCU 4.0.0
   This file is part of Lulu-MCU project: http://lulu.eTextile.org
   It has been foked from Kevin Cuzner : https://github.com/kcuzner/onewire-leds
   This code implement 1-Wire modified protocol for ATTiny10 - 1-Wire: https://en.wikipedia.org/wiki/1-Wire
*/

#ifndef _LED_H_
#define _LED_H_

#include <stdint.h>
#include <avr/io.h>

// Initializes the LED module
void led_init(void);

// Sets the current LED color
void led_tick(uint8_t fadeValue);

#endif //_LED_H_
