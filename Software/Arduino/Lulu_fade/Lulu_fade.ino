/*
  Lulu - Programing light into textile

  Lulu-star / Arduino code / This sketch is an example that control a single Lulu.

  Lulu-star circuitry
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

   (+) is 3.3 to 5V

*/
#include <elapsedMillis.h>

elapsedMillis timer;

const int PWM_PIN = 13; // This PIN is also connected to the Digispark Motherboard LED_BUILTIN.

void setup() {
  Serial.begin(9600);
  pinMode(PWM_PIN, OUTPUT);    // Set PIN as OUTPUT PIN
  digitalWrite(PWM_PIN, LOW);  // Set PIN LOW (GND)
}

void loop() {
  Serial.println(timer);
  // arg-0 the PWM pin
  // arg-1 the fade IN time
  // arg-1 the fade OUT time
  lulu_fade(13, 1000, 1000);
}

///////////////////////////////////// Fonction
// TODO adding timer as argument
void lulu_fade(uint8_t pwmPin, uint32_t fadeSpeedUp, uint32_t fadeSpeedDown) {
  static int pwmValue = 0;
  static int intervalUp = (int)(fadeSpeedUp / 255);
  static int intervalDown = (int)(fadeSpeedDown / 255);
  static boolean dir = true;

  // Fade In
  if (dir == true && timer > intervalUp) {
    timer = 0;
    analogWrite(pwmPin, pwmValue);
    pwmValue++;
    if (pwmValue >= 255) {
      dir = false;
    }
  }

  // Fade Out
  if (dir == false && timer > intervalDown) {
    timer = 0;
    analogWrite(pwmPin, pwmValue);
    pwmValue--;
    if (pwmValue <= 0) {
      dir = true;
    }
  }

}
