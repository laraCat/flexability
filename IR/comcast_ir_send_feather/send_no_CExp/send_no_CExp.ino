/* 
 *  Feather M0 Basic
 *  IR emitter: pin 9
 *  
 *  grove connectors from top left going CCW:
 *  [16/A2, 17/A3, 18/A4, 19/A5]
 *  [GND, 13, GND, 12]
 *  [GND, 11, GND, 10]
 *  [20, GND, 21, GND]
 *  [5, GND, 6, GND]
 *  
 *  
 */
#include <IRLibSendBase.h>    // First include the send base
//Now include only the protocols you wish to actually use.
//The lowest numbered protocol should be first but remainder 
//can be any order.

#include <IRLib_P09_GICable.h>

#include <IRLibCombo.h>     // After all protocols, include this
// All of the above automatically creates a universal sending
// class called "IRsend" containing only the protocols you want.
// Now declare an instance of that sender.

#define POWER 0x5006
#define VOLUME_UP 0xB00C
#define VOLUME_DOWN 0x7004
#define CHANNEL_UP 0xD00A
#define CHANNEL_DOWN 0x3002
#define PAGE_UP 0x2C09
#define GUIDE 0xC0B

IRsend mySender;

void setup() {
  Serial.begin(9600);
}

void loop() {
  if (Serial.read() != -1) {
    //send a code every time a character is received from the 
    // serial port. You could modify this sketch to send when you
    // push a button connected to an digital input pin.
    //Substitute values and protocols in the following statement
    // for device you have available.
   
    mySender.send(GICABLE,POWER,16);
   
    Serial.println(F("Sent signal."));
  }
}
