/*
   Lulu-MCU 4.0.0
   This file is part of Lulu-MCU project: http://lulu.eTextile.org
   It has been foked from Kevin Cuzner : https://github.com/kcuzner/onewire-leds
   This code implement 1-Wire modified protocol for ATTiny10 - 1-Wire: https://en.wikipedia.org/wiki/1-Wire

             (PCINT0/TPIDATA/OC0A/ADC0/AIN0) PB0 -|    |- PB3 (RESET/PCINT3/ADC3)
                                             GND -|    |- VCC
    (PCINT1/TPICLK/CLKI/ICP0/OC0B/ADC1/AIN1) PB1 -|    |- PB2 (T0/CLKO/PCINT2/INT0/ADC2)
*/

#define F_CPU 8000000UL

#include "led.h"
#include "onewire.h"

#include <avr/pgmspace.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/wdt.h>

const uint8_t ID_LULU = 3;
const uint8_t ID_BRODCAST = 255;

uint8_t ledPwm = 0;

int main(void) {

  set_cpu_8Mhz();

  led_init();
  onewire_init();

  wdt_enable(WDTO_15MS);
  sei(); // Enabling interrupts

  while (1) {
    wdt_reset();
    // Serial.print(); is not hear :-(
    if (onewire_has_new_bytes()) {
      uint16_t incomingBytes = onewire_get_bytes();
      uint8_t adress = incomingBytes & 0xFF; // Get the address
      if (adress == ID_LULU || adress == ID_BRODCAST){
        uint8_t value =  (incomingBytes >> 8) & 0xFF; // Get the value
        ledPwm = value;
      }
      else {
        // The address is not matching!
      }
    }
    led_ticks(ledPwm);
  }
}
