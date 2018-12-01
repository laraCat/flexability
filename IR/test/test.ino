#include "IRLibAll.h"
#include <Adafruit_CircuitPlayground.h>
//Create a receiver object to listen on pin 2
IRrecvPCI myReceiver(2);

//Create a decoder object 
IRdecode myDecoder;   

void setup() {
  Serial.begin(9600);
   CircuitPlayground.begin();

  Serial.println(F("Ready to receive IR signals"));
}

void loop() {
  //Continue looping until you get a complete signal received
  if (myReceiver.getResults()) {
    myDecoder.decode();           //Decode it
    myDecoder.dumpResults(true);  //Now print results. Use false for less detail
    myReceiver.enableIRIn();      //Restart receiver
  }
}
