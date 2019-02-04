/*
  Lulu-MCU 4.0.0
  This file is part of Lulu-MCU project: http://lulu.eTextile.org
  Lulu-MCU provide an addressable LED with oneWire communication bus system.
  This is implemented on a ATTiny10 MCU
*/

#include <OneWire.h>

OneWire net(10);  // OneWire on Arduino PIN 10

const int LED_PIN = 13;

void setup(void) {
  pinMode(LED_PIN, OUTPUT);
}

void loop(void) {
  /*
  delay(1000);
  digitalWrite(LED_PIN, LOW);
  delay(1000);
  digitalWrite(LED_PIN, HIGH);
  */
  net.reset();
  net.write(0xFF, 1);
}
