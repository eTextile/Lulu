/*
  Lulu - Programing light into textile
  Lulu-star / Arduino code / This sketch is an example that control a single Lulu.

    Lulu circuitry
    _________________________________
   |              |                  |
   |            __|__                |
   | +         |  +  |              / \
 __|__         |  M  |             / L \
  ---          |  C  |--- PWM --> /  U  \
   | -         |  U  |           /   L   \
   |           |__-__|          /____U____\
   |              |                  |
   |______________|__________________|

   (+) is 3.3 to 5V 200 mA
*/
#include <elapsedMillis.h> // https://github.com/pfeerick/elapsedMillis

elapsedMillis timer;

const int PWM_PIN = 6; // This PIN is also connected to the Digispark Motherboard BUILTIN_LED.

void setup() {
  pinMode(PWM_PIN, OUTPUT);    // Set PIN as OUTPUT PIN
  digitalWrite(PWM_PIN, LOW);  // Set PIN LOW (GND)
}

void loop() {
  lulu_blink(100, 50, timer);
}


void lulu_blink(int timeON, int timeOFF, elapsedMillis theTimer) {
  
  if (theTimer <= timeON) {
    digitalWrite(PWM_PIN, HIGH);
  }
  if (timer > timeON) {
    digitalWrite(PWM_PIN, LOW);
  }
  if (timer > timeON + timeOFF) {
    theTimer = 0;
  }
}
