// See https://www.edaboard.com/showthread.php?370521-PWM-using-controller/page2&p=1590578&viewfull=1#post1590578
#include <avr/io.h>
#include <avr/interrupt.h>
//#include <util/delay.h>

#define F_CPU 8000000UL

volatile uint16_t curentTime = 0;
uint16_t dutyCycle = 0;

uint8_t minVal = 0;
uint8_t maxVal = 255;
uint8_t timeOn = 0;
uint8_t timeOff = 0;
uint8_t fadeIn = 20;
uint8_t fadeOut = 20;

typedef enum {
  FADEIN,
  FADEOUT,
  STAY_ON,
  STAY_OFF
} led_t;

led_t ledState = FADEIN;

int main(void) {

  CCP = 0xD8;
  CLKPSR = (0 << CLKPS0) | (0 << CLKPS1) | (0 << CLKPS2) | (0 << CLKPS3);            // System clock is set to 8 MHz

  TCCR0A = (1 << WGM01) | (1 << WGM00) | (1 << COM0B1) | (0 << COM0B0);              // PWM, Phase and Frequency Correct - Compare Output Modes: non-inverted
  TCCR0B = (0 << WGM03) | (1 << WGM02) | (0 << CS02) | (0 << CS01) | (1 << CS00);    // Set Timer0 clock speed to 1Mhz (clock-source/8111
  TIMSK0 = (1 << TOIE0);                                                             // Overflow Interrupt Enable
  //TIMSK0 = (1 << ICIE0);                                                           // Enable the Input Capture interrupt (TIM0_CAPT) - NOT_WORKING

  DDRB |= (1 << PB1);   // Equivalent to pinMode(1, OUTPUT);

  sei(); // Enable global interrupts

  while (1) {
    // Timer0 (TCNT0) is couning at 1Mhz
    // Timer0 (TCNT0) is set to 10-bit (0-1024)
    // PWM frequency: 1000000 / 1024*2 = 488,3Hz

    switch (ledState) {

      case FADEIN:
        if (curentTime >= fadeIn) {
          curentTime = 0;
          dutyCycle += 1;              // Increment dutyCycle
          cli();                       // Disable interrupts
          OCR0B = dutyCycle;           // Update dutyCycle
          sei();                       // Enable global interrupts
          if (dutyCycle >= (maxVal << 2)) {
            ledState = STAY_ON;
          }
        }
        break;

      case FADEOUT:
        if (curentTime >= fadeOut) {
          curentTime = 0;
          dutyCycle -= 1;                   // Decrement dutyCycle
          cli();                            // Disable interrupts
          OCR0B = dutyCycle;                // Update dutyCycle
          sei();                            // Enable global interrupts
          if (dutyCycle <= (minVal << 2)) {
            ledState = STAY_OFF;
          }
        }
        break;

      case STAY_ON:
        if (curentTime >= (timeOn << 8)) {
          curentTime = 0;
          ledState = FADEOUT;
        }
        break;

      case STAY_OFF:
        if (curentTime >= (timeOff << 8)) {
          curentTime = 0;
          ledState = FADEIN;
        }
        break;

      default:
        break;
    }

  }
}

ISR(TIM0_OVF_vect) {
  curentTime += 1;
}
