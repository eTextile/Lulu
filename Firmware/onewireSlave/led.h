/**
   LED controller
*/
#ifndef _LED_H_
#define _LED_H_

#include <stdint.h>
#include <avr/io.h>

#define LED_PORT      PORTB
#define LED_DDR       DDRB
#define LED_PIN       0
#define LED_MASK      (1<<LED_PIN)

// Initializes the LED module
void led_init(void);

// Sets the current LED color
void led_set(uint8_t value);

// Turns the LED off for a set number of ticks
void led_begin_off(uint16_t period);

// Tick function for the LED
void led_tick(void);

#endif //_LED_H_
