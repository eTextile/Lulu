/*
  Lulu - Programing light into textile

  Lulu & DIGISPARK / Arduino code / This sketch is an example that control a single Lulu

 **UNDER MACKINTOSH YOU WILL NEED A USB HUB TO PROGRAM THE DIGISPARK BOARD!**
  Instaling Digispark
    - Add this link to the Arduino Préférences : http://digistump.com/package_digistump_index.json
    - Look for Digispark into the Arduino bord manager.

  Digispark digital I/O PINs
    Pin 0 → I2C SDA, PWM (LED_BUILTIND on Model B)
    Pin 1 → PWM (LED_BUILTIN on Model A)
    Pin 2 → I2C SCK, Analog
    Pin 3 → Analog In (also used for USB+ when USB is in use)
    Pin 4 → PWM, Analog (also used for USB- when USB is in use)
    Pin 5 → Analog In
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

