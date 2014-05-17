// Maurin Donneaud for Lucette board
// upload with "Arduino Pro ou Pro Mini"
// Atmega328 (3.3V, 8MHz)

#include "Tlc5940.h"

#define  BAUDRATE         38400    // vitesse du port serie
#define  DATA             3        // nombre de d'octets par trame
#define  FOOTER           47       // flag (/) to stop recording incoming bytes
#define  LED              16       // nombre de LEDs
#define  FRAME            16       // nombre de frames

byte storedByte[DATA] = { 0,0,0 };
int pos = 0;
boolean stringComplete = false;  // whether the string is complete

int seq[LED][FRAME] = {
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
};
 
unsigned int bpm = 120;
float timeFrame = 0;
unsigned long lastMillis = 0;
byte frameIndex = 0;
boolean DEBUG = false;

/////////////////////// INITIALISATION
void setup(){
  timeFrame = 60000 / bpm;
  Serial.begin(BAUDRATE);   // initialize serial
  Tlc.init();
}

/////////////////////// BOUCLE PRINCIPALE
void loop(){
  
  ledUpdate();
  
  if ( DEBUG == true ) {
    for (int i=0; i<LED; i++){
      for (int j=0; j<FRAME; j++){
        Serial.print(seq[i][j]), Serial.print(" ");
      }
      Serial.println();
    }
    Serial.println();
  }
}

/////////////////////// Les Fonctions
/*
  SerialEvent occurs whenever a new data comes in the
 hardware serial RX. This routine is run between each
 time loop() runs, so using delay inside loop can delay
 response.  Multiple bytes of data may be available.
 */
 
void serialEvent() {
  
  byte incommingByte = 0;
  byte ledID = 0;
  byte frameID = 0;
  unsigned int LEDvalue = 0;
  
  if (Serial.available()) {

    incommingByte = Serial.read();
    
    if (incommingByte == FOOTER) {
      stringComplete = true;
    }
    else {
      storedByte[pos] = incommingByte;
      pos++;
    }
    if (stringComplete == true){
      ledID = storedByte[0] >> 4;
      frameID = storedByte[0] & 15;
      LEDvalue = (storedByte[1] << 8) + storedByte[2];
      
      seq[ledID][frameID] = LEDvalue;
      pos = 0;
      stringComplete = false;
    }
    /*
    if (stringComplete == true && pos == 1){
      bpm = storedByte[0];
      timeFrame = 60000 / bpm;
    }
    */
  }
}

////////////////////////////////////// Parser to read serial datas from an [2][16] array of bytes
void ledUpdate(){
  int val = 0;

  if (millis() - lastMillis >= timeFrame) {    
    lastMillis = millis();
    
    for (int ledIndex=0; ledIndex<LED; ledIndex++) {
      val = seq[ledIndex][frameIndex];
      Tlc.set(ledIndex, val);
    }
    Tlc.update();
    frameIndex++;
    frameIndex = frameIndex % FRAME;
    Serial.print('A');
  }
}
