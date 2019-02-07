/*
   Lulu-LID 4.0.0 / Light Interface Device

  This file is part of Lulu project: http://lulu.eTextile.org
  Lulu-LID provide an addressable LED with 1-Wire communication bus system implemented on ATTiny10 MCU
*/

#include <OneWire.h>

#define ONEWIRE_PIN     10 // 1-Wire on Arduino PIN

OneWire net(ONEWIRE_PIN);

#define ID              0 // Byte 0 [7:4] (MSB) 0 for brodcast / 1-15 for address

#define SLEEP_MODE      0 // Byte 0 [3:0] (LSB)
#define SWITCH_ON       1 // Byte 0 [3:0] (LSB)
#define SWITCH_OFF      2 // Byte 0 [3:0] (LSB)
#define FADE_IN         3 // Byte 0 [3:0] (LSB)
#define TIME_ON         4 // Byte 0 [3:0] (LSB)
#define FADE_OUT        5 // Byte 0 [3:0] (LSB)
#define TIME_OFF        6 // Byte 0 [3:0] (LSB)
#define MAX_VAL         7 // Byte 0 [3:0] (LSB)
#define MIN_VAL         8 // Byte 0 [3:0] (LSB)
#define OFSET           9 // Byte 0 [3:0] (LSB)
#define SYNC            10 // Byte 0 [3:0] (LSB)

void setup(void) {

  net.reset();
  net.write(concatenate(ID, FADE_IN), 1);
  net.write(val, 1); // Lulu-MCU DEFAULT 0
  net.reset();
  net.write(concatenate(ID, TIME_ON), 1);
  net.write(val, 1); // Lulu-MCU DEFAULT 50
  net.reset();
  net.write(concatenate(ID, FADE_OUT), 1);
  net.write(val, 1); // Lulu-MCU DEFAULT 0
  net.reset();
  net.write(concatenate(ID, TIME_OFF), 1);
  net.write(val, 1); // Lulu-MCU DEFAULT 255
  net.reset();
  net.write(concatenate(ID, MAX_VAL), 1);
  net.write(val, 1); // Lulu-MCU DEFAULT 255
  net.reset();
  net.write(concatenate(ID, MIN_VAL), 1);
  net.write(val, 1); // Lulu-MCU DEFAULT 0
}

void loop(void) {
}

uint8_t concatenate(uint8_t id, uint8_t mode) {
  uint8_t concatenated
  concatenated = (id << 4);
  return concatenated;
}
