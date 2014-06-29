// Maurin Donneaud for Lucette board
// upload with "Arduino Pro ou Pro Mini"
// Atmega328 (3.3V, 8MHz)

#include "Tlc5940.h"

#define  BAUDRATE         9600     // vitesse du port serie
#define  DATA             512      // nombre de d'octets par trame

#define  FOOTER_DATA      255      // flag (/) to stop recording incoming bytes
#define  FOOTER_TEMPO     127      // flag ( ) to stop recording incoming bytes

#define  LED              16       // nombre de LEDs
#define  FRAME            16       // nombre de frames
#define  XERR             2        // pin to trigger TLC error (PD2)
#define  ledPin           5        // pin to display TLC error


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
 { 4095,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
 { 0,4095,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
 { 0,0,4095,0,0,0,0,0,0,0,0,0,0,0,0,0 },
 { 0,0,0,4095,0,0,0,0,0,0,0,0,0,0,0,0 },
 { 0,0,0,0,4095,0,0,0,0,0,0,0,0,0,0,0 },
 { 0,0,0,0,0,4095,0,0,0,0,0,0,0,0,0,0 },
 { 0,0,0,0,0,0,4095,0,0,0,0,0,0,0,0,0 },
 { 0,0,0,0,0,0,0,4095,0,0,0,0,0,0,0,0 },
 { 0,0,0,0,0,0,0,0,4095,0,0,0,0,0,0,0 },
 { 0,0,0,0,0,0,0,0,0,4095,0,0,0,0,0,0 },
 { 0,0,0,0,0,0,0,0,0,0,4095,0,0,0,0,0 },
 { 0,0,0,0,0,0,0,0,0,0,0,4095,0,0,0,0 },
 { 0,0,0,0,0,0,0,0,0,0,0,0,4095,0,0,0 },
 { 0,0,0,0,0,0,0,0,0,0,0,0,0,4095,0,0 },
 { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,4095,0 },
 { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4095 }
};


byte bpm = 300;
float timeFrame = 1000;
unsigned long lastMillis = 0;
unsigned int frameIndex = 0;

boolean ledError[LED];
boolean lastLedError[LED];
boolean DEBUG = false;

/////////////////////// INITIALISATION
void setup(){
  Serial.begin(BAUDRATE);   // initialize serial
  pinMode(XERR, INPUT);     //
  pinMode(ledPin, OUTPUT);  //
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

    if(inputValue == 255){
      for (int i=0; i<DATA; i=i+2){
        highBit = (int)serialData[i] << 6;
        lowBit = serialData[i+1];
        seqValue = highBit + lowBit;
        ledId = (int)i/32;
        seqPos = ((int)i/2) % 16;
        seq[ledId][seqPos] = seqValue;
      }
    }
    else if(inputValue == 127){
      highBit = (int)serialData[0] << 6;
      lowBit = serialData[1];
      bpm = highBit + lowBit;
      timeFrame = 60000 / bpm;
    }
    else {
      serialData[index] = inputValue;
      index++;
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

      /////////// ERROR
      lastLedError[ledIndex] = ledError[ledIndex];
      ledError[ledIndex] = digitalRead(XERR); // XERR is ERROR pin
      if( ledError[ledIndex] != lastLedError[ledIndex] && lastLedError[ledIndex] == LOW){
        digitalWrite(ledPin, HIGH);
        if(DEBUG){
          Serial.println(F("ERROR : "));
          for (int j=0; j< LED; j++){
            Serial.println(j);
          }
          digitalWrite(ledPin, LOW);
        }
      }
    }    
    Tlc.update();
    frameIndex++;
    frameIndex = frameIndex % FRAME;

  }
}
