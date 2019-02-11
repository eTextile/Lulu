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

  DDRB |= (1 << PB0);   // Equivalent to pinMode(0, OUTPUT);

  //wdt_enable(WDTO_15MS);
  setupPwmMode();

  while (1) {
    //wdt_reset();

    if (flagBuffer) {
      flagBuffer = 0; // Clear the byteBuffer

      uint8_t readID = ((byteBuffer >> 12) & 0xF);   // Get the address
      uint8_t readMode = ((byteBuffer >> 8) & 0xF);  // Get the mode
      uint8_t readVal = (byteBuffer & 0xFF);         // Get the value

      if (readID == ID || readID == BRODCAST) {

        switch (readMode) {
          case MIN_VAL:
            minVal = readVal;
            break;
          case MAX_VAL:
            maxVal = readVal;
            break;
          case TIME_ON:
            timeOn = readVal;
            break;
          case TIME_OFF:
            timeOff = readVal;
            break;
          case FADE_IN:
            fadeIn = readVal;
            break;
          case FADE_OUT:
            fadeOut = readVal;
            if (fadeOut == 20) PORTB |= (1 << 0); // Equivalent to digitalRead(1, LOW);
            break;
          default:
            break;
        }
        getCommande = 0;
        setupPwmMode();
      }
    }
    else {
      if (!getCommande) updatePwm(); // Fading pattern generator controlled by 1-Wire input parameters
    }
  }
}
