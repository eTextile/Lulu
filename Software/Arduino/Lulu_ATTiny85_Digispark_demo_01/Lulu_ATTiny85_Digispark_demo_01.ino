/*
  Lulu - Programing light into textile

  Lulu & DIGISPARK / Arduino code / This sketch is an example that control a single Lulu.

  ** DIGISPARK ARDUINO **
  UNDER MACKINTOSH YOU WILL NEED A USB HUB TO PROGRAM THE DIGISPARK BOARD!
  Instaling Digispark support for Arduino
   - Add this link to the Arduino Préférences : http://digistump.com/package_digistump_index.json
   - Look for Digispark into the Arduino bord manager

  Digispark digital I/O PINs
    Pin 0 → I2C SDA, PWM (LED_BUILTIND on Model B)
    Pin 1 → PWM (LED_BUILTIN on Model A)
    Pin 2 → I2C SCK, Analog
    Pin 3 → Analog In (also used for USB+ when USB is in use)
    Pin 4 → PWM, Analog (also used for USB- when USB is in use)
    Pin 5 → Analog In

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

   (+) is 3.3 to 5V - 200 mA

*/

const int PWM_PIN = 6; // This PIN is also connected to the Digispark Motherboard BUILTIN_LED.

void setup() {
  pinMode(PWM_PIN, OUTPUT);    // Set PIN as OUTPUT PIN
  digitalWrite(PWM_PIN, LOW);  // Set PIN LOW (GND)
  blink_A();
}

void loop() {
  fade(0);
  fade(3);
  fade(2);
  fade(0);
  fade(1);
  blink_A();
  blink_B();
}

///////////////////////////////////// Fonctions

void fade(int _speed) {
  for (int i = 0; i < 256; i++) {
    analogWrite(PWM_PIN, i);
    delay(2 * _speed);
  }
  for (int i = 255; i >= 0; i--) {
    analogWrite(PWM_PIN, i);
    delay(1 * _speed);
  }
}
void blink_A() {
  for (int i = 0; i < 10; i++) {
    digitalWrite(PWM_PIN, HIGH);
    delay(random(10));
    digitalWrite(PWM_PIN, LOW);
    delay(random(20));
  }
}

void blink_B() {
  for (int i = 0; i < 10; i++) {
    digitalWrite(PWM_PIN, HIGH);
    delay(random(80));
    digitalWrite(PWM_PIN, LOW);
    delay(random(100));
  }

}
