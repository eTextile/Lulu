/*
   Lulu_1-Wire
   This file is originally part of onewire-leds from Kevin Cuzner : https://github.com/kcuzner/onewire-leds
   It has been modified to fit the Lulu project needs : http://lulu.eTextile.org
*/

// #include "leds.h"
#include "onewire.h"

#include <avr/pgmspace.h>
#include <avr/io.h>
#include <avr/interrupt.h>
// #include <avr/wdt.h>
#include <util/delay.h>


#define OFF_TIME 0xFFFF

int main(void) {

  uint8_t val;
  uint16_t i;

  // wdt_enable(WDTO_15MS);
  set_cpu_8Mhz();
  // led_init();
  onewire_init();
  // Delay at the beginning to ensure we have a steady supply before turning on the LED
  for (i = 0; i < OFF_TIME; i++) {
    // wdt_reset();
  }

  DDRB |= (1 << 0); // PB0 as output
  DDRB |= (1 << 1); // PB1 as output

  sei();

  while (1) {
    // wdt_reset();
    // leds_tick();
    // _delay_ms(1000);

    if (onewire_has_new_byte()) {
    PORTB |= (1 << 1); // DEBUG PB1
    val = onewire_read_byte();

      if (val > 0) {
        PORTB |= (1 << 0); // DEBUG PB0
      } else
      {
        PORTB &= ~(1 << 0); // DEBUG PB0
      }
    }
  }
  return 0;
}
