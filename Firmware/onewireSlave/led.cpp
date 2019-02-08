/*
  Lulu-MCU 4.0.0 / eTextile Light Interface Device

  This file is part of Lulu project: http://lulu.eTextile.org
  This part of the code implement an LED fading pattern generator embedded in the Lulu-MCU.
  This fading pattern generator is controlled by predefined commands that can be transmitted over the 1-Wire bus.
*/

#include "led.h"
#include "onewire.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

uint8_t pwm_setup_flag = 0;

uint8_t minVal = 0;
uint8_t maxVal = 255;
uint8_t timeOn = 0;
uint8_t timeOff = 10;
uint8_t fadeIn = 20;
uint8_t fadeOut = 30;

int8_t inc = 1;
uint16_t duty = 0;

void setupLedPin(void) {
  DDRB |= (1 << LED_PIN);   // Equivalent to pinMode(1, OUTPUT);
}

void setupPwmMode(void) {
  TCCR0A = (1 << WGM00) | (0 << WGM01) | (1 << COM0B1) | (1 << COM0B0); // PWM, Phase Correct, 8-bit - Compare Output Modes: non-inverted
  TCCR0B = (0 << WGM02) | (0 << WGM03) | (0 << CS02) | (0 << CS01) | (1 << CS00); // No prescaling: clock source is clk/1
}

/*
  TODO
  // The PIN PB1 can be used to connect a phototransistor.
  // This sensor will be used to sens 1-Wire light signals.
  // This can be use to set the Lulu-MCU ID or directly program the fading pattern generator

  void sensor_pin_setup(void) {
  //DDRB  &= ~(1 << 1);   // Equivalent to pinMode(1, INPUT);
  //PORTB &= ~(1 << 1); // Equivalent to digitalRead(1, LOW); // Set by default
  }
*/

/*
  Fading pattern generator controlled by 1-Wire input parameters
  const PROGMEM  uint16_t lut[]  = { ... };  // Look-Up Table

  minVal;   //
  maxVal;   //
  timeOn;   //
  timeOff;  //
  fadeIn;   //
  fadeOut;  //
*/

void updatePwm() {

  switch (inc) {
    case 1:
      for (uint8_t i = 0; i <= fadeIn; i++) {
        _delay_ms(1);
      }
      break;
    case -1:
      for (uint8_t i = 0; i <= fadeOut; i++) {
        _delay_ms(1);
      }
      break;
    default:
      break;
  }

  OCR0B = (duty += inc);

  if (duty >= maxVal) {
    inc = -1;
    for (uint8_t i = 0; i < timeOn; i++) {
      _delay_ms(1);
    }
  }
  if (duty <= minVal) {
    inc = 1;
    for (uint8_t i = 0; i < timeOff; i++) {
      _delay_ms(1);
    }
  }
}
