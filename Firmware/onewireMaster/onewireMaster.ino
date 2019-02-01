/*
   Lulu_1-Wire
   This file is part of Lulu-MCU project: http://lulu.eTextile.org
*/

#include <OneWire.h>

OneWire net(10);  // on pin 10

const int LED_PIN = 13;

void setup(void) {
  pinMode(LED_PIN, OUTPUT);
}

void loop(void) {

  delay(1000);
  digitalWrite(LED_PIN, LOW);
  delay(1000);
  digitalWrite(LED_PIN, HIGH);
  net.reset();
  net.write_bytes(0xFF, 1); // 255 // 1111 1111

}
