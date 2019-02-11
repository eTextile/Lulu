/*
   Lulu-MCU 4.0.0 / Light Interface Device

  This file is part of Lulu project: http://lulu.eTextile.org
  Lulu-MCU provide an addressable LED with 1-Wire communication bus system implemented on ATTiny10 MCU

  This code is used to control the LED fading pattern generator embedded in the Lulu-MCU
  This by brodcasting predefined commands on the 1-Wire bus
*/

#include <OneWire.h>

#define ONEWIRE_PIN     10 // 1-Wire on Arduino PIN

OneWire net(ONEWIRE_PIN);

#define ID              0 // Byte 0 [7:4] (MSB) - 0 for brodcast / 1-15 for address

#define MIN_VAL         2 // Byte 0 [3:0] (LSB) - DO NOT CHANGE
#define MAX_VAL         3 // Byte 0 [3:0] (LSB) - DO NOT CHANGE
#define TIME_ON         4 // Byte 0 [3:0] (LSB) - DO NOT CHANGE
#define TIME_OFF        5 // Byte 0 [3:0] (LSB) - DO NOT CHANGE
#define FADE_IN         6 // Byte 0 [3:0] (LSB) - DO NOT CHANGE
#define FADE_OUT        7 // Byte 0 [3:0] (LSB) - DO NOT CHANGE

void setup(void) {
  // The net.write(); is writing LSB first
  net.reset();
  net.write(0, 1); // Lulu-MCU DEFAULT 0
  net.write(concatenate(ID, MIN_VAL), 1);

  net.reset();
  net.write(255, 1); // MIN-0 MAX-255
  net.write(concatenate(ID, MAX_VAL), 1);

  net.reset();
  net.write(10, 1); // Lulu-MCU DEFAULT 0
  net.write(concatenate(ID, TIME_ON), 1);

  net.reset();
  net.write(10, 1); // Lulu-MCU DEFAULT 100
  net.write(concatenate(ID, TIME_OFF), 1);

  net.reset();
  net.write(0, 1); // Lulu-MCU DEFAULT 10
  net.write(concatenate(ID, FADE_IN), 1);

  net.reset();
  net.write(0, 1); // Lulu-MCU DEFAULT 30
  net.write(concatenate(ID, FADE_OUT), 1);
}

void loop(void) {

}

uint8_t concatenate(uint8_t id, uint8_t mode) {
  uint8_t concatenated = 0;
  concatenated = (((id & 0xF) << 4) | mode);
  return concatenated;
}
