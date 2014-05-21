// Maurin Donneaud for Lucette board
// upload with "Arduino Pro ou Pro Mini"
// Atmega328 (3.3V, 8MHz)

#include "Tlc5940.h"

#define  BAUDRATE         38400    // vitesse du port serie
#define  DATA             32       // nombre de d'octets par trame

#define  FOOTER_DATA      255      // flag (/) to stop recording incoming bytes
#define  FOOTER_TEMPO     127      // flag (/) to stop recording incoming bytes

#define  LED              16       // nombre de LEDs
#define  FRAME            16       // nombre de frames

char serialData[DATA] = {
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 
};
  
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


byte bpm = 300;
float timeFrame = 100;
unsigned long lastMillis = 0;
byte frameIndex = 0;
boolean DEBUG = false;

/////////////////////// INITIALISATION
void setup(){
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
  int highBit = 0;
  int lowBit = 0;
  int frameID = 0;
  int LEDvalue = 0;

  if (Serial.available()) {
    
      Serial.readBytesUntil(FOOTER_DATA, serialData, DATA);
    
    for (int i=0; i<32; i=i+2){
      
      highBit = serialData[i];
      lowBit = serialData[i+1];
      
      Serial.print(highBit), Serial.print(" "),  Serial.println(lowBit);
      
      LEDvalue = (highBit << 6) + lowBit;

      seq[frameID][ i/2 ] = LEDvalue;
    }
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
    // if ( !DEBUG ) Serial.print('A');
  }
}

