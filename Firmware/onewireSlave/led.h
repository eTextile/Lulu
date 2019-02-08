/*
  Lulu-MCU 4.0.0 / eTextile Light Interface Device

  This file is part of Lulu project: http://lulu.eTextile.org
  This part of the code implement an LED fading pattern generator embedded in the Lulu-MCU.
  This fading pattern generator is controlled by predefined commands that can be transmitted over the 1-Wire bus.
*/

#ifndef _LED_H_
#define _LED_H_

#include <stdint.h>

#define LED_PIN         PB1

#define ID              1 // Byte 0 [7:4] (MSB) <- SET BY USER!
#define BRODCAST        0 // Byte 0 [7:4] (MSB)

#define MIN_VAL         2 // Byte 0 [3:0] (LSB)
#define MAX_VAL         3 // Byte 0 [3:0] (LSB)
#define TIME_ON         4 // Byte 0 [3:0] (LSB)
#define TIME_OFF        5 // Byte 0 [3:0] (LSB)
#define FADE_IN         6 // Byte 0 [3:0] (LSB)
#define FADE_OUT        7 // Byte 0 [3:0] (LSB)

extern uint8_t minVal;
extern uint8_t maxVal;
extern uint8_t timeOn;
extern uint8_t timeOff;
extern uint8_t fadeIn;
extern uint8_t fadeOut;

// void sensor_pin_setup(void); // TODO

// LED_PIN configuration
//inline void hardware_ledPin_setup(void); // FIXME
void setupLedPin(void);

// Hardware PWM configuration
//inline void hardware_pwm_setup(void); // FIXME
void setupPwmMode(void);

// Apply all parameters to the LED
//inline void updatePWM(void); // FIXME
void updatePwm(void);

#endif //_LED_H_
