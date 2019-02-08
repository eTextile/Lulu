/*
  Lulu-MCU 4.0.0 / eTextile Light Interface Device

  This file is part of Lulu project: http://lulu.eTextile.org
  This code implement 1-Wire modified protocol for ATTiny10 - 1-Wire: https://en.wikipedia.org/wiki/1-Wire
  And an LED fading pattern generator embedded in the Lulu-MCU.
  This fading pattern generator is controlled by predefined commands that can be transmitted over the 1-Wire bus.
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

int main(void) {

  set_cpu_8Mhz();

  setupOnewirePin();
  setupLedPin();

  //wdt_enable(WDTO_15MS);

  while (1) {
    //wdt_reset();

    if (onewire_has_new_bytes()) {

      uint16_t incomingBytes = onewire_get_bytes();     // Copy & free the byteBuffer for the next bytes to decode
      uint8_t readID = ((incomingBytes >> 12) & 0xF);   // Get the address
      uint8_t readMode = ((incomingBytes >> 8) & 0xF);  // Get the mode
      uint8_t readval = (incomingBytes & 0xFF);         // Get the value

      if (readID == ID || readID == BRODCAST) {
        switch (readMode) {
          case MIN_VAL:
            minVal = readval;
            break;
          case MAX_VAL:
            maxVal = readval;
            break;
          case TIME_ON:
            timeOn = readval;
            break;
          case TIME_OFF:
            timeOff = readval;
            break;
          case FADE_IN:
            fadeIn = readval;
            break;
          case FADE_OUT:
            fadeOut = readval;
            break;
          default:
            break;
        }
        setupPwmMode();
      }
      else {
        // The address is not matching
      }
    }
    updatePwm(); // Fading pattern generator controlled by 1-Wire input parameters
  }

}
