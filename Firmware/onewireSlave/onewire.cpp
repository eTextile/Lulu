/*
  Lulu-MCU 4.0.0 / eTextile Light Interface Device

  This file is part of Lulu project: http://lulu.eTextile.org
  It has been foked from Kevin Cuzner : https://github.com/kcuzner/onewire-leds
  This part of the code implement 1-Wire modified protocol for ATTiny10 - 1-Wire: https://en.wikipedia.org/wiki/1-Wire
*/

#include "onewire.h"
#include "led.h"

#include <avr/interrupt.h>

#define ONEWIRE_PIN_VALUE (PINB & (1 << ONEWIRE_PIN))

// ATTiny10 clock-source is set to 8Mhz
// Timer0 is used in two different mode for decoding 1-wire trames and fading the LED

// TIM0_COMPB_vect
// Catch RESET after 480uS: 8000000 * 0,00048 = 3840 ticks (480uS = 0,00048S)
#define ONEWIRE_RESET_TICKS  3840

// TIM0_COMPA_vect
// Sample time after a falling edge is 25uS: 8000000 * 0,000025 = 200 ticks (25uS = 0,000025S)
#define ONEWIRE_READ_TICKS  200

// State machine - states
// TODO: Make sure that a reset during a read or immediately following another reset is registered as a reset
typedef enum {
  WAIT_RESET,
  BEGIN_RESET,
  RESET,
  READ
} state_t;

volatile state_t state = WAIT_RESET;
volatile uint8_t getCommande = 0;

volatile uint16_t byteBuffer = 0;
volatile uint8_t flagBuffer = 0;
volatile uint8_t nextBit = 0;

void set_cpu_8Mhz(void) {
  // Set CPU speed by setting clock prescalar
  // CCP register must first be written with the correct signature - 0xD8
  CCP = 0xD8;
  // CLKPS[3:0] sets the clock division factor
  CLKPSR = (0 << CLKPS0) | (0 << CLKPS1) | (0 << CLKPS2) | (0 << CLKPS3); // Set the system clock speed to 8 MHz
}

// ONEWIRE_PIN configuration
void setupOnewirePin(void) {
  DDRB &= ~(1 << ONEWIRE_PIN);            // Equivalent to pinMode(ONEWIRE_PIN, INPUT);
  EICRA = (1 << ISC01) | (0 << ISC00);    // Called the INT0 interrupt on falling edge
  EIMSK = (1 << INT0);                    // Enable the external interrupt
  sei();                                  // Enable global interrupts
}

// External interrupt called at falling edge
ISR(INT0_vect) {

  //sleep_disable(); // TODO

  switch (state) {

    case WAIT_RESET:
      getCommande = 1;

      // 1-Wire decoder hardware configuration
      TCCR0A = (0 << COM0B1) | (0 << COM0B0) | (0 << WGM01) | (0 << WGM00);            // Set Timer0 (TCNT0) to Normal operation - Compare Output Modes: disconnected
      TCCR0B = (0 << WGM03) | (0 << WGM02) | (0 << CS02) | (0 << CS01) | (1 << CS00);  // Set Timer0 clock speed to 8Mhz (clock-source/1 - No prescaling)
      TIMSK0 = (1 << OCIE0B) | (1 << OCIE0A) | (0 << TOIE0);                           // Enable COMPA & COMPB triggered by the timer0 - Disable overflow Interrupt
      OCR0A = ONEWIRE_READ_TICKS;                                                      // TIM0_COMPA: sample the 1-Wire bits values
      OCR0B = ONEWIRE_RESET_TICKS;                                                     // TIM0_COMPB: catch the 1-Wire RESET
      state = BEGIN_RESET;
      break;

    case RESET:
      // We are now reading a byte
      state = READ;
      break;

    default:
      break;
  }
  TCNT0 = 0; // Reset the timer0
}

// Compare A: 25uS since last falling edge or since last timer overflow
//interrupt [TIM0_COMPA] void timer0_compa_isr(void) {
ISR(TIM0_COMPA_vect) {

  switch (state) {

    case READ:
      // It is time to sample
      if (ONEWIRE_PIN_VALUE) {
        //byteBuffer |= 0x80;  // Set the bit - LSB first - Used to decode one byte
        byteBuffer |= 0x8000;  // Set the bit - LSB first - Used to decode two bytes
      }

      if (nextBit < 15) {
        byteBuffer >>= 1;
      }
      else {
        // Reading DONE - we can WAIT_RESET for the next reset
        state = WAIT_RESET;
        flagBuffer = 1;
        break;
      }
      nextBit++;
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
        nextBit = 0;
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
