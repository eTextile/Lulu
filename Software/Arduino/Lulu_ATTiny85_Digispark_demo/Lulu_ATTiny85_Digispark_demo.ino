/*
  Lulu MCU++ - Programing light into textile
  
*/

const int PWM_PIN = 1; // This LED is the smal SMD one on the Digispark Motherboard.

void setup() {
  pinMode(PWM_PIN, OUTPUT);
  digitalWrite(PWM_PIN, LOW);  // HIGH is OFF
}

void loop() {

  // Blink
  digitalWrite(PWM_PIN, HIGH);
  delay(2000);
  digitalWrite(PWM_PIN, LOW);
  delay(2000);

  // Fade
  for (int i = 0; i < 256; i++) {
    analogWrite(PWM_PIN, i);
    delay(15);
  }
  for (int i = 255; i >= 0; i--) {
    analogWrite(PWM_PIN, i);
    delay(15);
  }

}

