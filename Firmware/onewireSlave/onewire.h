/*
   Lulu-MCU 4.0.0 / eTextile Light Interface Device

   This file is part of Lulu project: http://lulu.eTextile.org
   It has been foked from Kevin Cuzner : https://github.com/kcuzner/onewire-leds
   This code implement 1-Wire modified protocol for ATTiny10 - 1-Wire: https://en.wikipedia.org/wiki/1-Wire
*/

#ifndef _ONEWIRE_H_
#define _ONEWIRE_H_

#include <avr/io.h>

#define ONEWIRE_PIN     2

//extern volatile uint32_t curentMillis; // Will be used in led.cpp
extern volatile uint8_t onewire_setup_flag; // Will be used in led.cpp

void set_cpu_8Mhz(void);

// 1-Wire PIN configuration
//inline void hardware_onewirePin_setup(void); // FIXME
void hardware_onewirePin_setup(void);

// 1-Wire decoder hardware configuration
//inline void hardware_onewire_setup(void); // FIXME
void hardware_onewire_setup(void);

// This fonction is used to setup hardware 1-Wire decoder only one time
// after an external interrupt (called at falling edge)
uint8_t hardware_onewire_setup_flag(void);

// Returns whether or not the 1-Wire decoder has received new bytes
uint8_t onewire_has_new_bytes(void);

// Returns the bytes that has been decoded from the 1-Wire data line
uint16_t onewire_get_bytes(void);

#endif //_ONEWIRE_H_
