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

uint8_t I2C_ADDRES = 0xFF;

int main(void) {

  set_cpu_8Mhz();

  DDRB |= (1 << 0);   // Equivalent to pinMode(1, OUTPUT);
  DDRB |= (1 << 1);   // Equivalent to pinMode(2, OUTPUT);

  PORTB &= ~(1 << 0); // Equivalent to digitalWrite(PB0, LOW); // Set by default
  PORTB &= ~(1 << 1); // Equivalent to digitalWrite(PB1, LOW); // Set by default

  onewire_init();

  wdt_enable(WDTO_15MS);
  sei(); // Enabling interrupts

  while (1) {
    wdt_reset();
    // Serial.print(); is not hear ;-)
    if (onewire_has_new_byte()) {
      uint8_t incomingByte = onewire_get_byte();
      if (incomingByte == 0xFF) {
        PORTB |= (1 << 1); // Equivalent to digitalWrite(PB1, HIGH);
        _delay_ms(50);
        PORTB &= ~(1 << 1); // Equivalent to digitalWrite(PB1, LOW);
      }
      else {
      }
    }
  }
}
