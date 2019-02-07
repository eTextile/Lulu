/*
   Lulu-MCU 4.0.0 / eTextile Light Interface Device

   This file is part of Lulu project: http://lulu.eTextile.org
   It has been foked from Kevin Cuzner : https://github.com/kcuzner/onewire-leds
   This code implement 1-Wire modified protocol for ATTiny10 - 1-Wire: https://en.wikipedia.org/wiki/1-Wire
*/

#include "onewire.h"
#include "led.h"

#include <avr/interrupt.h>

#define ONEWIRE_PIN_VALUE (PINB & (1 << ONEWIRE_PIN))

// ATTiny10 internal clock is set to 8Mhz
// Timer0 (16-bits) is used for our timing
// The presecaler is set at CLK/1
// 1-Wire RESET is 480uS LOW

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

volatile uint8_t onewire_setup_flag = 0;

volatile uint8_t byte_flag = 0;
volatile uint16_t finished_bytes = 0;
volatile uint16_t byteBuffer = 0;
volatile uint8_t next_bit = 0;

volatile state_t state = WAIT_RESET;

//volatile uint8_t curentMicros = 0;
//volatile uint32_t curentMillis = 0;

void set_cpu_8Mhz(void) {
  // Set CPU speed by setting clock prescalar:
  // CCP register must first be written with the correct signature - 0xD8
  CCP = 0xD8;
  // CLKPS[3:0] sets the clock division factor
  CLKPSR = 0; // 0000 - system clock is set to 8 MHz
}

// ONEWIRE_PIN configuration
void hardware_onewirePin_setup(void) {
  DDRB &= ~(1 << ONEWIRE_PIN);             // Equivalent to pinMode(ONEWIRE_PIN, INPUT);
  EICRA = ((1 << ISC01) | (0 << ISC00));   // called the INT0 interrupt on falling edge
  EIMSK = (1 << INT0);                     // Enable the external interrupt
}

uint8_t hardware_onewire_setup_flag(void) {
  return onewire_setup_flag;
}

void hardware_onewire_setup(void) {
  pwm_setup_flag = 0; // Reset the flag
  
  // Configure the timer0 - TCNT0
  TCCR0A = 0; // Normal operation
  TCCR0B = ((0 << CS02) | (0 << CS01) | (1 << CS00)); // No prescaling: clock source is clk/1

  // Configure the internal interrupts
  TIMSK0 = ((1 << OCIE0B) | (1 << OCIE0A) | (1 << TOIE0)); // Enable all interrupts for the timer
  OCR0A = ONEWIRE_READ_TICKS;                              // TIM0_COMPA: sample the 1-Wire bits values
  OCR0B = ONEWIRE_RESET_TICKS;                             // TIM0_COMPB: catch the 1-Wire RESET
  // TIM0_OVERFLOW: It's been too long since the last falling edge
  
  onewire_setup_flag = 1;
}

uint8_t onewire_has_new_bytes(void) {
  return byte_flag;
}

uint16_t onewire_get_bytes(void) {
  byte_flag = 0;
  return finished_bytes;
}

// External interrupt called at falling edge
ISR(INT0_vect) {

  // TODO sleep_disable(); // Wake up!
  if (!hardware_onewire_setup_flag) hardware_onewire_setup(); // Setup hardware for 1-Wire communication

  TCNT0 = 0; // Reset the timer on a falling edge

  //PORTB |= (1 << 0); // Equivalent to digitalWrite(PB0, HIGH);

  switch (state) {
    case WAIT_RESET:
      state = BEGIN_RESET;
      break;
    case RESET:
      // We are now reading a byte
      state = READ;
      break;
    default:
      break;
  }
}

// Compare A: 25uS since last falling edge or since last timer overflow
ISR(TIM0_COMPA_vect) {

  //PORTB &= ~(1 << 0); // Equivalent to digitalWrite(PB0, LOW);

  switch (state) {
    case READ:
      // It is time to sample
      if (ONEWIRE_PIN_VALUE) {
        //byteBuffer |= 0x80;      // Set the bit - LSB first - Used to decode one byte
        byteBuffer |= 0x8000;      // Set the bit - LSB first - Used to decode two bytes
      }
      if (next_bit < 15) {
        byteBuffer >>= 1;
      }
      else {
        // Reading DONE - we can WAIT_RESET for the next reset
        state = WAIT_RESET;
        finished_bytes = byteBuffer;
        byte_flag = 1;
        break;
      }
      next_bit++;
      break;
    default:
      break;
  }

  //curentMicros++; // Updated every 25 uS = 0,025 millisecondes
  //curentMicros %= 40; // Reset counterMicros every millisecondes (40 * 0,025)
  //if (curentMicros == 0) curentMillis++;
}

// Compare B: 480uS since last falling edge or since last timer overflow (ONEWIRE_PIN_VALUE)
ISR(TIM0_COMPB_vect) {

  switch (state) {

    case BEGIN_RESET:
      if (ONEWIRE_PIN_VALUE) { // The signal is HIGH after 480uS we had a reset!
        state = RESET;
        byteBuffer = 0;
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
