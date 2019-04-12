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

typedef enum {
  FADEIN,
  FADEOUT,
  STAY_ON,
  STAY_OFF
} led_t;

led_t ledState = FADEIN;

uint8_t minVal = 0;
uint8_t maxVal = 255;
uint8_t timeOn = 0;
uint8_t timeOff = 50;
uint8_t fadeIn = 20;
uint8_t fadeOut = 20;

volatile uint16_t timer = 0;

void setupLedPin(void) {
  DDRB |= (1 << LED_PIN);   // Equivalent to pinMode(1, OUTPUT);
}

uint16_t dutyCycle = 0;

void setupPwmMode(void) {
  //getCommande = 0;
  cli();                                                                           // Disable interrupts
  TCCR0A = (1 << WGM01) | (1 << WGM00) | (1 << COM0B1) | (0 << COM0B0);            // Fast PWM, 10-bit - Compare Output Modes: non-inverted
  TCCR0B = (0 << WGM03) | (1 << WGM02) | (0 << CS02) | (0 << CS01) | (1 << CS00);  // Fast PWM, 10-bit - set Timer0 clock speed to 8Mhz (clock-source/1 - No prescaling)
  TIMSK0 = (0 << OCIE0B) | (0 << OCIE0A) | (1 << TOIE0);                           // Disable COMPA & COMPB triggered by the timer0 - Enable overflow Interrupt
  TCNT0 = 0;
  timer = 0;
  sei();                                                                           // Enable global interrupts
}

// Fading pattern generator controlled by 1-Wire input parameters
void updatePwm(void) {
  // Timer0 (TCNT0) is couning at 8Mhz
  // Timer0 (TCNT0) is set to 10-bit (0-1024)
  // PWM frequency: 8000000 / 1024*2 = TO FAST - This cause time shifting between each Lulu-MCU - FIXME!

  switch (ledState) {

    case FADEIN:
      if (timer >= fadeIn) {
        timer = 0;
        dutyCycle += 1;     // Increment dutyCycle
        if (dutyCycle >= (maxVal << 2)) {
          ledState = STAY_ON;
        }
      }
      break;

    case FADEOUT:
      if (timer >= fadeOut) {
        timer = 0;
        dutyCycle -= 1;     // Decrement dutyCycle
        if (dutyCycle <= (minVal << 2)) {
          ledState = STAY_OFF;
        }
      }
      break;

    case STAY_ON:
      if (timer >= (timeOn << 8)) {
        timer = 0;
        ledState = FADEOUT;
      }
      break;

    case STAY_OFF:
      if (timer >= (timeOff << 8)) {
        timer = 0;
        ledState = FADEIN;
      }
      break;

    default:
      break;
  }
  OCR0B = dutyCycle;  // Update dutyCycle
}

ISR(TIM0_OVF_vect) {
  timer += 1;
}

/*
  TODO
  // The PIN PB0 can be used to connect a phototransistor.
  // This sensor will be used to sens 1-Wire light signals.
  // This can be use to set the Lulu-MCU ID or directly program the fading pattern generator

  void sensor_pin_setup(void) {
  //DDRB  &= ~(1 << 0);   // Equivalent to pinMode(1, INPUT);
  //PORTB &= ~(1 << 0);   // Equivalent to digitalRead(1, LOW);
  }
*/
