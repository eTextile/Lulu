/*
  Lulu-MCU 4.0.0
  This file is part of Lulu-MCU project: http://lulu.eTextile.org
  Lulu-MCU provide an addressable LED with oneWire communication bus system.
  This is implemented on a ATTiny10 MCU
*/

#include <OneWire.h>

OneWire net(10);  // OneWire on Arduino PIN 10

const uint8_t LULU_ID = 3;
const uint8_t LED_PIN = 13;

void setup(void) {
  pinMode(LED_PIN, OUTPUT);
}

void loop(void) {

  for (int val = 0; val < 256; val++) {
    net.reset();
    net.write(LULU_ID, 1);
    net.write(val, 1);
    delay(10);
  }
}
