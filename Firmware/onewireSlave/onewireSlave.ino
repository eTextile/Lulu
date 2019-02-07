/*
   Lulu-MCU 4.0.0 / eTextile Light Interface Device

   This file is part of Lulu project: http://lulu.eTextile.org
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
#include <avr/wdt.h>

#define ID       3
#define BRODCAST 0

uint8_t ledPwm = 0;

int main(void) {

  set_cpu_8Mhz();

  // hardware_ledPin_setup(); // This is now done
  // hardware_onewirePin_setup(); // This is now done in the external interrupt called at falling edge

  hardware_onewire_setup();
  hardware_pwm_setup();

  wdt_enable(WDTO_15MS);

  sei(); // Enable interrupts

  while (1) {
    wdt_reset();

    if (onewire_has_new_bytes()) {
      uint16_t incomingBytes = onewire_get_bytes();
      uint8_t readID = (incomingBytes >> 4) & 0xF;     // Get the address
      uint8_t readMode = (incomingBytes & 0xF);        // Get the mode
      uint8_t readval =  (incomingBytes >> 8) & 0xFF;  // Get the value

      if (readID == ID || readID == BRODCAST) {

        switch (readMode) {
          case FADE_IN:
            fadeIn = readval;
            break;
          case TIME_ON:
            timeOn = readval;
            break;
          case FADE_OUT:
            fadeOut = readval;
            break;
          case TIME_OFF:
            timeOff = readval;
            break;
          case MAX_VAL:
            maxVal = readval;
            break;
          case MIN_VAL:
            minVal = readval;
            break;
          default:
            break;
        }
      }
      else {
        // The address is not matching
      }
      hardware_pwm_setup();
    }
    updatePWM();
  }
}
