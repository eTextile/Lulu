    // Lucette V1.0
    // 08/10/2011
    #include "Tlc5940.h"
    #include "tlc_fades.h"
    TLC_CHANNEL_TYPE channel;
    #define minValue  0
    #define maxValue  4000
    #define duration  15000
    #define XERR      2     // pin to trigger TLC error (PD2)
    #define ledPin    5     // pin to display TLC error
    unsigned int ErrorVal;
    int rowPin[] = {          // mapping to re-organize row pins order
      15, 14, 13, 5, 4, 3, 2, 1, 8, 15, 14, 13, 12, 11, 10, 9
    };
    boolean DEBUG = false;
    void setup(){
      Serial.begin(9600);
      pinMode(XERR, INPUT);
      pinMode(ledPin, OUTPUT);
      Tlc.init();
      channel = 0;
    }
    void loop(){
      ErrorVal = digitalRead(XERR);   // XERR is ERROR pin
     
      if(change(ErrorVal)==true && ErrorVal==LOW){
        digitalWrite(ledPin, HIGH);
        if(DEBUG) Serial.print(channel, DEC), Serial.println(" : ERROR");
        digitalWrite(ledPin, LOW);
      }
      if(tlc_fadeBufferSize < TLC_FADE_BUFFER_LENGTH){
        if(!tlc_isFading(rowPin[channel])){
          uint32_t startMillis = millis() + 1000;
          uint32_t endMillis = startMillis + duration;
          tlc_addFade(rowPin[channel], minValue, maxValue, startMillis, endMillis);
          tlc_addFade(rowPin[channel], maxValue, minValue, endMillis, endMillis + duration);
        }
       
        if(channel == 15){
           channel = 0;
         }
    channel++ ;
       
      }
      tlc_updateFades();
    }
    ///////////// if input values change output is true
    int change(int val){
      static int lastVal = 0;
      if(val != lastVal){
        lastVal = val;
        return true;
      }
      else {
        return false;
      }
    }
