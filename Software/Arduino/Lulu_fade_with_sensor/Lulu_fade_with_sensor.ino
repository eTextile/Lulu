/*
  Lulu - Programing light into textile

  Lulu-star / Arduino code / This sketch is an example that fading the Lulu in combination with a light sensor.

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

const int PWM_PIN = 6; // This PIN is also connected to the Digispark Motherboard BUILTIN_LED.

void setup() {
  pinMode(PWM_PIN, OUTPUT);    // Set PIN as OUTPUT PIN
  digitalWrite(PWM_PIN, LOW);  // Set PIN LOW (GND)
  randomBlink(10, 20);
}

void loop() {

}

///////////////////////////////////// Fonctions

}
