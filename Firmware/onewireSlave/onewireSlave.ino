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

//#include "led.h"
#include "onewire.h"

#include <avr/pgmspace.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/wdt.h>

int main(void) {

  wdt_enable(WDTO_15MS);
  set_cpu_8Mhz();

  DDRB |= (1 << 0);   // Equivalent to pinMode(1, OUTPUT);
  DDRB |= (1 << 1);   // Equivalent to pinMode(2, OUTPUT);

  PORTB &= ~(1 << 0); // Equivalent to digitalWrite(PB0, LOW);
  PORTB &= ~(1 << 1); // Equivalent to digitalWrite(PB1, LOW);

  onewire_init();

  sei(); // Enabling interrupts
  wdt_reset();

  while (1) {
    wdt_reset();

    if (onewire_has_new_byte()) {
      uint8_t val = onewire_read_byte();
      if (val > 0) {
        for (uint8_t i = 0; i < val; i++) {
          PORTB |= (1 << 0); // Equivalent to digitalWrite(PB0, HIGH);
          _delay_ms(500);
          PORTB &= ~(1 << 0); // Equivalent to digitalWrite(PB0, LOW);
          _delay_ms(500);
        }
      }
      else {
        PORTB |= (1 << 1); // Equivalent to digitalWrite(PB1, HIGH);
        _delay_ms(500);
        PORTB &= ~(1 << 1); // Equivalent to digitalWrite(PB1, LOW);
      }
    }
  }
  return 0;
}
