/*
   Lulu-MCU 4.0.0 /  eTextile Light Interface Device

   This file is part of Lulu project: http://lulu.eTextile.org
   This code implement 1-Wire modified protocol for ATTiny10 - 1-Wire: https://en.wikipedia.org/wiki/1-Wire
*/

#ifndef _LED_H_
#define _LED_H_

#include <stdint.h>

#define LED_PIN         0

#define ID              1 // Byte 0 [7:4] (MSB) <- SET BY USER!
#define BRODCAST        0 // Byte 0 [7:4] (MSB)

#define LED_OFF         0 // Byte 0 [3:0] (LSB)
#define LED_ON          1 // Byte 0 [3:0] (LSB)
#define MIN_VAL         2 // Byte 0 [3:0] (LSB)
#define MAX_VAL         3 // Byte 0 [3:0] (LSB)
#define TIME_ON         4 // Byte 0 [3:0] (LSB)
#define TIME_OFF        5 // Byte 0 [3:0] (LSB)
#define FADE_IN         6 // Byte 0 [3:0] (LSB)
#define FADE_OUT        7 // Byte 0 [3:0] (LSB)

extern uint8_t pwm_setup_flag;

extern uint8_t minVal;
extern uint8_t maxVal;
extern uint8_t timeOn;
extern uint8_t timeOff;
extern uint8_t fadeIn;
extern uint8_t fadeOut;

// void sensor_pin_setup(void); // TODO

// LED_PIN configuration
//inline void hardware_ledPin_setup(void); // FIXME
void hardware_ledPin_setup(void);

// Hardware PWM configuration
//inline void hardware_pwm_setup(void); // FIXME
void hardware_pwm_setup(void);

// This fonction is used to setup hardware PWM only one time after decodin 1-wire input values
uint8_t hardware_pwm_setup_flag(void);

// Apply all parameters to the LED
//inline void updatePWM(void); // FIXME
void updatePWM(void);

#endif //_LED_H_
