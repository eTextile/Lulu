/*
   Lulu-MCU 4.0.0 / eTextile Light Interface Device

   This file is part of Lulu project: http://lulu.eTextile.org
   This code implement 1-Wire modified protocol for ATTiny10 - 1-Wire: https://en.wikipedia.org/wiki/1-Wire
*/

#include "led.h"
#include "onewire.h"

#include <util/delay.h>

uint8_t pwm_setup_flag = 0;

uint8_t maxVal = 255;
uint8_t minVal = 0;
uint8_t timeOn = 0;
uint8_t timeOff = 5;
uint8_t fadeIn = 10;
uint8_t fadeOut = 20;
uint8_t ofset = 0;

void hardware_ledPin_setup(void) {
  DDRB |= (1 << LED_PIN);   // Equivalent to pinMode(0, OUTPUT);
  PORTB &= ~(1 << LED_PIN); // Equivalent to digitalWrite(0, LOW);
}

uint8_t hardware_pwm_setup_flag(void) {
  return pwm_setup_flag;
}

void hardware_pwm_setup(void) {
  onewire_setup_flag = 0; // Reset the flag
  TCCR0A |= (1 << WGM00) | (1 << COM0B1);
  TCCR0B |= (1 << WGM02) | (1 << CS00);
  pwm_setup_flag = 1;
}

/*
  TODO
  // The PIN PB1 can be used to set the Lulu-MCU ID
  // The idea is to use a phototransistor to talk 1-Wire by sending light signals.
  void sensor_pin_setup(void) {

  //DDRB  &= ~(1 << 1);   // Equivalent to pinMode(1, INPUT);
  //PORTB &= ~(1 << 1); // Equivalent to digitalRead(1, LOW); // Set by default
  }
*/

/*
  Fading pattern generator controlled by 1-Wire input parameters
  16 bits PWM hardware setup
  look-Up Table (LUT) // NA - ther is no EEPROM on ATTiny-10
  
  minVal;   //
  maxVal;   //
  timeOn;   //
  timeOff;  //
  fadeIn;   //
  fadeOut;  //
*/

void updatePWM() {

  for (uint8_t i = minVal; i < maxVal; i++) {
    OCR0B = i;
    //_delay_ms(fadeIn);
  }
  //_delay_ms(timeOn);
  for (uint8_t i = maxVal; i >= minVal; i--) {
    OCR0B = i;
    //_delay_ms(fadeOut);
  }
  //_delay_ms(timeOff);
}
