/*
   Lulu-MCU 4.0.0
   This file is part of Lulu-MCU project: http://lulu.eTextile.org
   It has been foked from Kevin Cuzner : https://github.com/kcuzner/onewire-leds
   This code implement 1-Wire modified protocol for ATTiny10 - 1-Wire: https://en.wikipedia.org/wiki/1-Wire
*/

#include "onewire.h"

#include <avr/interrupt.h>

#define ONEWIRE_PIN_MASK (1<<ONEWIRE_PIN)
#define ONEWIRE_PIN_VALUE (ONEWIRE_INPUT & ONEWIRE_PIN_MASK)

// ATTiny10 internal clock is set to 8Mhz - 8000000
// Timer0 (16-bits) is used for our timing
// The presecaler is set at CLK/1
// RESET is 480uS LOW: 3840 ticks (480uS = 0,00048S -> 8000000 * 0,00048 = 3840)
// Sample time after a falling edge is 32uS: 256 ticks (32uS = 0,000032S -> 8000000 * 0,000032 = 256)
// Sample time after a falling edge is 26uS: 130 ticks (26uS = 0,000026S -> 8000000 * 0,000032 = 256)

const unsigned int ONEWIRE_RESET_TICKS  = 3840;
const unsigned int ONEWIRE_READ_TICKS = 256;
//const unsigned int ONEWIRE_READ_TICKS = 130;

// State machine - states
// TODO: Make sure that a reset during a read or immediately following another reset is registered as a reset
typedef enum {
  IDLE_STATE,
  BEGIN_RESET,
  RESET,
  READ,
  DONE
} state_t;

static volatile uint8_t byte_flag = 0;
static volatile uint8_t finished_byte = 0;
static volatile uint8_t current_byte = 0;
static volatile uint8_t next_bit = 0;

static volatile state_t state = IDLE_STATE;

void set_cpu_8Mhz(void) {
  // Set CPU speed by setting clock prescalar:
  // CCP register must first be written with the correct signature - 0xD8
  CCP = 0xD8;
  // CLKPS[3:0] sets the clock division factor
  CLKPSR = 0; // 0000 - system clock is set to 8 MHz
}

void onewire_init(void) {

  ONEWIRE_DDR &= ~ONEWIRE_PIN_MASK;      // Set the ONEWIRE pin as INPUT
  EICRA = ((1 << ISC01) | (0 << ISC00)); // Set external interrupt on falling edges INT0
  EIMSK = (1 << INT0);                   // Enable the external interrupt

  TCCR0A = 0; // Normal operation
  TCCR0B = ((0 << CS02) | (0 << CS01) | (1 << CS00)); // No prescaling: clock source is clk/1
  TIMSK0 = ((1 << OCIE0B) | (1 << OCIE0A) | (1 << TOIE0)); // Enable all interrupts for the timer

  // Since the timer is reset on a falling edge, we can use the following:
  // Interrupt A: time to sample!
  // Interrupt B: a reset has just occurred if the line is still low, otherwise its been too long since the last falling edge
  // Overflow: It's been too long since the last falling edge
  OCR0A = ONEWIRE_READ_TICKS;
  //OCR0AL = (char) ONEWIRE_READ_TICKS & 0xff;
  //OCR0AH = 0x00;

  OCR0B = ONEWIRE_RESET_TICKS;
  //OCR0BL = (char) ONEWIRE_RESET_TICKS & 0xff; // OCR0A[7:0]
  //OCR0BH = (char) (ONEWIRE_RESET_TICKS >> 8) & 0xff; // OCR0A[15:8]
}

uint8_t onewire_has_new_byte(void) {
  return byte_flag;
}

uint8_t onewire_read_byte(void) {
  byte_flag = 0;
  return finished_byte;
}

// External interrupt called at falling edge
ISR(INT0_vect) {

  TCNT0 = 0; // Reset the timer

  //if (!ONEWIRE_PIN_VALUE) { ///////////// <- FIXME!?
  switch (state) {
    case IDLE_STATE:
      state = BEGIN_RESET;
      break;
    case RESET:
      // We are now reading a byte
      state = READ;
      break;
    case DONE:
      // We are now idle
      state = IDLE_STATE;
      break;
    default:
      break;
  }
  //}
}

// Compare A: 32uS since last falling edge or since last timer overflow <-
// Compare A: 26uS since last falling edge or since last timer overflow
ISR(TIM0_COMPA_vect) {

  switch (state) {
    case READ:
      // It is time to sample
      if (!ONEWIRE_PIN_VALUE) { // Inverted values for our ground-based bus (LOW = 1)
        current_byte |= 0x80;   // Set the bit - LSB first
      }
      //current_byte >>= 1;
      current_byte = current_byte >> 1;

      next_bit++;
      if (next_bit > 7) {
        // Reading DONE - we can wait for the next reset
        state = DONE;
        finished_byte = current_byte;
        byte_flag = 1;
      }
      break;
    default:
      break;
  }
}

// Compare B: 480uS since last falling edge or since last timer overflow
ISR(TIM0_COMPB_vect) {

  switch (state) {

    case BEGIN_RESET:
      if (ONEWIRE_PIN_VALUE) {  // If the signal is HIGH after 480uS we had a reset!
        state = RESET;
        current_byte = 0;
        next_bit = 0;
      }
      else {
        state = IDLE_STATE;
      }
      break;

    default:
      // It's been too long since the last falling edge
      state = IDLE_STATE;
      break;
  }
}

ISR(TIM0_OVF_vect) {
  switch (state) {
    case RESET:
      // We don't mind overflowing the timer here
      break;
    default:
      // It's been too long since the last falling edge
      state = IDLE_STATE;
      break;
  }
}
