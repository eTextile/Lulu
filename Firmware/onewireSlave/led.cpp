/*
   Lulu-MCU 4.0.0
   This file is part of Lulu-MCU project: http://lulu.eTextile.org
   It has been foked from Kevin Cuzner : https://github.com/kcuzner/onewire-leds
   This code implement 1-Wire modified protocol for ATTiny10 - 1-Wire: https://en.wikipedia.org/wiki/1-Wire
*/

#include "led.h"

uint8_t ticks = 0;

void led_init(void) {

  DDRB |= (1 << 0);   // Equivalent to pinMode(1, OUTPUT);
  DDRB |= (1 << 1);   // Equivalent to pinMode(2, OUTPUT);

  PORTB &= ~(1 << 0); // Equivalent to digitalWrite(PB0, LOW); // Set by default
  PORTB &= ~(1 << 1); // Equivalent to digitalWrite(PB1, LOW); // Set by default
}

void led_ticks(uint8_t pwmValue) {

  ticks++;
  ticks = ticks % 256;

  if (ticks >= pwmValue) {
    PORTB &= ~(1 << 0); // Equivalent to digitalWrite(PB0, LOW);
  }
  else {
    PORTB |= (1 << 0); // Equivalent to digitalWrite(PB1, HIGH);
  }

}
