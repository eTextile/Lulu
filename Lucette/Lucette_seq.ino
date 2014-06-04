// Maurin Donneaud for Lucette board
// upload with "Arduino Pro ou Pro Mini"
// Atmega328 (3.3V, 8MHz)

#include "Tlc5940.h"

#define  BAUDRATE         38400    // vitesse du port serie
#define  DATA             512      // nombre de d'octets par trame

#define  FOOTER_DATA      255      // flag (/) to stop recording incoming bytes
#define  FOOTER_TEMPO     127      // flag ( ) to stop recording incoming bytes

#define  LED              16       // nombre de LEDs
#define  FRAME            16       // nombre de frames

byte serialData[DATA] = {
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
};
 
 int index = 0;
 
int seq[LED][FRAME] = {
 { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
 { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
 { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
 { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
 { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
 { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
 { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
 { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
 { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
 { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
 { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
 { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
 { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
 { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
 { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
 { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 }
};

byte bpm = 300;
float timeFrame = 1000;
unsigned long lastMillis = 0;
unsigned int frameIndex = 0;
boolean DEBUG = false;

/////////////////////// INITIALISATION
void setup(){
  Serial.begin(BAUDRATE);   // initialize serial
  Tlc.init();
}

/////////////////////// BOUCLE PRINCIPALE
void loop(){
  ledUpdate();
}

/////////////////////// Les Fonctions
void serialEvent(){
  byte inputValue = 0;
  int highBit = 0;
  int lowBit = 0;
  int ledId = 0;
  int seqPos = 0;
  int seqValue = 0;

  if (Serial.available() > 0){
    inputValue = Serial.read();

    if (inputValue != 255){
      serialData[index] = inputValue;
      index++;
    }
    else{
      index = 0;
      for (int i=0; i<DATA; i=i+2){
        highBit = (int)serialData[i] << 6;
        lowBit = serialData[i+1];
        seqValue = highBit + lowBit;
        ledId = (int)i/32;
        seqPos = ((int)i/2) % 16;
        seq[ledId][seqPos] = seqValue;
      }
    }
  }
}

////////////////////////////////////// Parser to read serial datas from an [2][16] array of bytes
void ledUpdate(){
  int val = 0;

  if (millis() - lastMillis >= timeFrame){    
    lastMillis = millis();

    for (int ledIndex=0; ledIndex<LED; ledIndex++){
      val = seq[ledIndex][frameIndex];
      Tlc.set(ledIndex, val);
    }
    Tlc.update();
    frameIndex++;
    frameIndex = frameIndex % FRAME;
  }
}
