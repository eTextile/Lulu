/*
   Lulu_1-Wire
   This file is originally part of onewire-leds from Kevin Cuzner : https://github.com/kcuzner/onewire-leds
   It has been modified to fit the Lulu project needs : http://lulu.eTextile.org

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
//#include <avr/wdt.h>
#include <util/delay.h>

int main(void) {

  //wdt_enable(WDTO_15MS);
  set_cpu_8Mhz();

  DDRB |= (1 << 0);   // Equivalent to pinMode(1, OUTPUT);
  DDRB |= (1 << 1);   // Equivalent to pinMode(2, OUTPUT);

  PORTB &= ~(1 << 0); // Equivalent to digitalWrite(1, LOW);
  PORTB &= ~(1 << 1); // Equivalent to digitalWrite(2, LOW);

  onewire_init();

  sei(); // Enabling interrupts
  //wdt_reset();

  while (1) {
    //wdt_reset();

    if (onewire_has_new_byte()) {
      uint8_t val = onewire_read_byte();
      if (val == 0xF0) {
        PORTB |= (1 << 1); // FIXME - Equivalent to digitalWrite(1, HIGH);
      }
      else {
      }
    }
  }
  return 0;
}
