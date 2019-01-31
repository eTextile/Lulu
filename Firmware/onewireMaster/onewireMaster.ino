#include <OneWire.h>

OneWire net(10);  // on pin 10

const int LED_PIN = 13;
const int ONEWIRE_PIN = 10;

void setup(void) {
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
  pinMode(ONEWIRE_PIN, OUTPUT);
}

void loop(void) {
  digitalWrite(LED_PIN, LOW);
  net.reset();
  net.write_bytes(0xF0, 1);
  Serial.println("WRITE_BYTE");
  delay(1000);
  digitalWrite(LED_PIN, HIGH);
  delay(1000);
}
