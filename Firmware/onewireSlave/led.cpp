/*
   Lulu_1-Wire
   This file is originally part of onewire-leds from Kevin Cuzner : https://github.com/kcuzner/onewire-leds
   It has been modified to fit the Lulu project needs : http://lulu.eTextile.org
*/

#include "led.h"

static uint8_t led_value = 0x80;
static uint16_t off_timer = 0;

void led_set(uint8_t value) {
  led_value = value;
}

void led_begin_off(uint16_t period) {
  off_timer = period;
}

void led_tick(void) {
  static uint8_t count = 0;

  if (off_timer > 0) {
    LED_PORT |= LED_MASK;
  }
  else {
    if (count < led_value) {
      LED_PORT &= ~LED_MASK;
    }
    else {
      LED_PORT |= LED_MASK;
    }
  }
  count++;
  if (off_timer > 0)
    off_timer--;
}
