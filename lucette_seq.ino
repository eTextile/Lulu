#include "Tlc5940.h"

//#define  PORT_SPEED        38400     // serial port speed
#define  PORT_SPEED        9600     // serial port speed

#define  LED               16        //
#define  FRAME             16        //

unsigned int timeLigne[LED][FRAME];
unsigned int lastTimeLigne[LED][FRAME];

unsigned int bpm = 120;
float timeFrame = 60000 / bpm;;
unsigned long currentMillis = 0;

int frameIndex = 0;

boolean toggel = false;
boolean DEBUG = true;

/////////////////////// INITIALISATION
void setup() {
  Serial.begin(PORT_SPEED);
  Tlc.init();
  delay(1000);
}

/////////////////////// BOUCLE PRINCIPALE
void loop() {
  serialEvent();
  vibroParcer();
}

//////////////////////////// Recuperation des données envoyées sur le port série
void serialEvent() {

  char ledId;
  char framePos;
  int value;

  if (Serial.available()) {

    ledId = Serial.read();     // A.....P
    framePos = Serial.read();  // a.....p

    if ( (ledId >= 'A' && ledId <= 'P') && (framePos >= 'a' && framePos <= 'p') ) {

      value = Serial.parseInt();

      if (DEBUG) Serial.print(ledId - 'A');
      if (DEBUG) Serial.print("\t");
      if (DEBUG) Serial.print(framePos - 'a');
      if (DEBUG) Serial.print("\t");
      if (DEBUG) Serial.println(value);
    }
  }
  if (value != 0) {
    timeLigne[ ledId - 'A' ][ framePos - 'a' ] = value;
    
    if (DEBUG) {
      for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 16; j++) {
          Serial.print( timeLigne[ i ][ j ] ), Serial.print(" ");
        }
        Serial.println();
      }
      Serial.println("-------------------");
    }
  }
}


////////////////////////////////////// Parser to read serial datas from an [2][16] array of bytes
void vibroParcer() {
  int val = 0;

  if ( millis() - currentMillis >= timeFrame && toggel == true ) {
    currentMillis = millis();
    toggel = false;

    for (int ledIndex = 0; ledIndex < LED; ledIndex++) {
      val = timeLigne[ledIndex][frameIndex];

      if (val > 0) {
        Tlc.set(ledIndex, val);
        Tlc.update();
      }
      else {
        Tlc.set(ledIndex, 0);
        Tlc.update();
      }
    }
  }

  if (toggel == false) {
    toggel = true;
    frameIndex++;
    frameIndex = frameIndex % FRAME;
  }
}
