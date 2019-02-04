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

// ATTiny10 internal clock is set to 8Mhz
// Timer0 (16-bits) is used for our timing
// The presecaler is set at CLK/1
// OneWire RESET is 480uS LOW

// TIM0_COMPB_vect
// Catch RESET after 480uS: 8000000 * 0,00048 = 3840 ticks (480uS = 0,00048S)
const unsigned int ONEWIRE_RESET_TICKS  = 3840;

// TIM0_COMPA_vect
// Sample time after a falling edge is 25uS: 8000000 * 0,000025 = 200 ticks (25uS = 0,000025S)
const unsigned int ONEWIRE_READ_TICKS = 200;

// State machine - states
// TODO: Make sure that a reset during a read or immediately following another reset is registered as a reset
typedef enum {
  WAIT_RESET,
  BEGIN_RESET,
  RESET,
  READ,
  DONE
} state_t;

volatile uint8_t byte_flag = 0;
volatile uint16_t finished_byte = 0;
volatile uint16_t current_byte = 0;
volatile uint8_t next_bit = 0;

volatile state_t state = WAIT_RESET;

void set_cpu_8Mhz(void) {
  // Set CPU speed by setting clock prescalar:
  // CCP register must first be written with the correct signature - 0xD8
  CCP = 0xD8;
  // CLKPS[3:0] sets the clock division factor
  CLKPSR = 0; // 0000 - system clock is set to 8 MHz
}

void onewire_init(void) {

  ONEWIRE_DDR &= ~ONEWIRE_PIN_MASK;        // Set the ONEWIRE pin as INPUT
  EICRA = ((1 << ISC01) | (0 << ISC00));   // Set interrupt INT0 on falling edge

  EIMSK = (1 << INT0);                     // Enable the external interrupt

  TCCR0A = 0; // Normal operation
  TCCR0B = ((0 << CS02) | (0 << CS01) | (1 << CS00)); // No prescaling: clock source is clk/1

  TIMSK0 = ((1 << OCIE0B) | (1 << OCIE0A) | (1 << TOIE0)); // Enable all interrupts for the timer

  // External interrupt INT0 is called at falling edge

  // TIM0_COMPA: sample the oneWire bits values
  OCR0A = ONEWIRE_READ_TICKS;

  // TIM0_COMPB: catch the oneWire RESET
  OCR0B = ONEWIRE_RESET_TICKS;

  // TIM0_OVERFLOW: It's been too long since the last falling edge

}

uint8_t onewire_has_new_bytes(void) {
  return byte_flag;
}

uint16_t onewire_get_bytes(void) {
  byte_flag = 0;
  return finished_byte;
}

// External interrupt called at falling edge
ISR(INT0_vect) {

  TCNT0 = 0; // Reset the timer on a falling edge

  //PORTB |= (1 << 0); // Equivalent to digitalWrite(PB1, HIGH);

  switch (state) {
    case WAIT_RESET:
      state = BEGIN_RESET;
      break;
    case RESET:
      // We are now reading a byte
      state = READ;
      break;
    case DONE:
      // We are now idle
      state = WAIT_RESET;
      break;
    default:
      break;
  }
}

// Compare A: 25uS since last falling edge or since last timer overflow
ISR(TIM0_COMPA_vect) {

  //PORTB &= ~(1 << 0); // Equivalent to digitalWrite(PB1, LOW);

  switch (state) {
    case READ:
      // It is time to sample
      if (ONEWIRE_PIN_VALUE) {
        //current_byte |= 0x80;        // Set the bit - LSB first
        current_byte |= 0x8000;      // Set the bit - LSB first

      }
      if (next_bit < 15) {
        current_byte >>= 1;
      }
      else {
        // Reading DONE - we can WAIT_RESET for the next reset
        state = DONE;
        finished_byte = current_byte;
        byte_flag = 1;
        break;
      }
      next_bit++;
      break;
    default:
      break;
  }
}

// Compare B: 480uS since last falling edge or since last timer overflow (ONEWIRE_PIN_VALUE)
ISR(TIM0_COMPB_vect) {

  switch (state) {

    case BEGIN_RESET:
      if (ONEWIRE_PIN_VALUE) { // The signal is HIGH after 480uS we had a reset!
        state = RESET;
        current_byte = 0;
        next_bit = 0;
      }
      else {
        state = WAIT_RESET;
      }
      break;

    default:
      // It's been too long since the last falling edge
      state = WAIT_RESET;
      break;
  }
}

ISR(TIM0_OVF_vect) {
  state = WAIT_RESET;
}
