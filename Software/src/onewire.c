/**
   Modified 1-Wire Protocol
*/
#include "onewire.h"

#include <avr/interrupt.h>
#include <util/delay.h>

#define ONEWIRE_PIN_MASK (1<<ONEWIRE_PIN)
#define ONEWIRE_PIN_VALUE (ONEWIRE_INPUT & ONEWIRE_PIN_MASK)

// ATTiny10 internal clock is set to 8Mhz
// Timer0 (16-bits) is used for our timing
// The presecaler is set at CLK/1
// 70uS: 280 ticks
// 480uS: 3840 ticks
// 4 ticks is our sample time after a falling edge, landing at about 26uS
// - NOTE: This is equivalent to 256 clock cycles, giving us ample
//   computation time
#define ONEWIRE_RESET_TICKS 3840
#define ONEWIRE_READ_TICKS  208

// state machine states
// TODO: Make sure that a reset during a read or immediately following another reset is registered as a reset
typedef enum {
    ST_IDLE,
    ST_BEGIN_RESET,
    ST_RESET,
    ST_READ,
    ST_DONE
} state_t;

static volatile uint8_t byte_flag = 0;
static volatile uint8_t finished_byte = 0;
static volatile uint8_t current_byte = 0;
static volatile uint8_t next_bit = 0;

static volatile state_t state = ST_IDLE;

void set_cpu_8Mhz(void) {
  // Set CPU speed by setting clock prescalar:
  // CCP register must first be written with the correct signature - 0xD8
  CCP = 0xD8;
  // CLKPS[3:0] sets the clock division factor
  CLKPSR = 0; // 0000 - system clock is set to 8 MHz
}

void onewire_init(void) {

  ONEWIRE_DDR &= ~ONEWIRE_PIN_MASK; // We want an input on our pin

  EICRA = (1 << ISC01) | (1 << ISC00); // Set external interrupt on falling edges INT0
  EIMSK = (1 << INT0); // Enable the external interrupt

  TCCR0A = 0; // Normal operation
  TCCR0B = (0 << CS02) | (0 << CS01) | (1 << CS00) ; // No prescaling: clock source is clk/1
  TIMSK0 = (1 << OCIE0B) | (1 << OCIE0A) | (1 << TOIE0); // Enable all interrupts for the timer

  // since the timer is reset to 0 on a falling edge, we can use the following:
  // Interrupt A: time to sample!
  // Interrupt B: a reset has just occurred if the line is still low, otherwise its been too long since the last falling edge
  // Overflow: It's been too long since the last falling edge
  OCR0AL = ONEWIRE_READ_TICKS;
  OCR0AH = 0;

  OCR0BL = (char)ONEWIRE_RESET_TICKS; // OCR0A[7:0]
  OCR0BH = (char)(ONEWIRE_RESET_TICKS >> 8); // OCR0A[15:8]

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

	// Same than : if (PINB & (1 << 2))
  if (ONEWIRE_PIN_VALUE) {
    // Every falling edge resets the timer
    // TCNT0H = 0;
    // TCNT0L = 0;
    TCNT0 = 0x0;
    switch (state) {
      case ST_IDLE:
        state = ST_BEGIN_RESET;
        break;
      case ST_RESET:
        // we are now reading a byte
        state = ST_READ;
        break;
      case ST_DONE:
        // we are now idle
        state = ST_IDLE;
        break;
      default:
        break;
    }
  }
}

// Compare A: 70uS since last falling edge
ISR(TIM0_COMPA_vect) {

  switch (state) {
    case ST_READ:
      // It is time to sample
      current_byte >>= 1;
      if (!ONEWIRE_PIN_VALUE) // Inverted values for our ground-based bus (0 = 1)
        current_byte |= 0x80; // LSB first
      next_bit++;
      if (next_bit > 7) {
        // Reading DONE - we can wait for the next reset.
        state = ST_DONE;
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

  // PORTB |= (1 << 1); // PB1 DEBUG
  switch (state) {
    case ST_BEGIN_RESET:
      if (ONEWIRE_PIN_VALUE) {
        // PORTB |= (1 << 0); // PB0 DEBUG
        // PORTB &= ~(1 << 1); // PB1 DEBUG
        // Still high? we have a reset
        state = ST_RESET;
        current_byte = 0;
        next_bit = 0;
      }
      else {
        state = ST_IDLE;
      }
      break;
    default:
      // It's been too long since the last falling edge
      state = ST_IDLE;
      break;
  }
}

ISR(TIM0_OVF_vect) {

  // PORTB |= (1 << 0); // PB0 DEBUG
  switch (state) {
    case ST_RESET:
      // We don't mind overflowing the timer here
      break;
    default:
      // It's been too long since the last falling edge
      state = ST_IDLE;
      break;
  }
}
