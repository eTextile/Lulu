/**
 * Modified 1-wire protocol
 */
#ifndef _ONEWIRE_H_
#define _ONEWIRE_H_

#include <avr/io.h>

#define ONEWIRE_DDR   DDRB
#define ONEWIRE_INPUT PINB
#define ONEWIRE_PIN   2

/**
 * Initializes the one-wire bus
 */
void onewire_init(void);

/**
 * Returns whether or not the 1-wire bus has decoded a new byte
 */
uint8_t onewire_has_new_byte(void);

/**
 * Reads the last byte that has been read
 */
uint8_t onewire_read_byte(void);

#endif //_ONEWIRE_H_
