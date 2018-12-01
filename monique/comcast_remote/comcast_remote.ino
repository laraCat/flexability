/*
    Feather M0 Basic
    IR emitter: pin 9

    grove connectors from top left going CCW:
    | 16/A2, 17/A3, 18/A4, 19/A5 |
    | GND, 13, GND, 12 |
    | GND, 11, GND, 10 |
    | 20, GND, 21, GND |
    | 5, GND, 6, GND |


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
#include <Bounce2.h>

#define POWER 0x5006
#define VOLUME_UP 0xB00C
#define VOLUME_DOWN 0x7004
#define CHANNEL_UP 0xD00A
#define CHANNEL_DOWN 0x3002
#define PAGE_UP 0x2C09
#define GUIDE 0xC0B

const int debounceTime = 25;  //mS
const int powerPin = 13;
const int volUpPin = 12;
const int volDwnPin = 11;
const int chUpPin = 10;
const int chDwnPin = 20;
const int pageUpPin = 21;
const int guidePin = 5;

Bounce power = Bounce(powerPin, debounceTime);
Bounce volUp = Bounce(volUpPin, debounceTime);
Bounce volDwn = Bounce(volDwnPin, debounceTime);
Bounce chUp = Bounce(chUpPin, debounceTime);
Bounce chDwn = Bounce(chDwnPin, debounceTime);
Bounce pageUp = Bounce(pageUpPin, debounceTime);
Bounce guide = Bounce(guidePin, debounceTime);

IRsend mySender;

void setup() {
  Serial.begin(9600);
  pinMode(powerPin, INPUT_PULLUP);
  pinMode(volUpPin, INPUT_PULLUP);
  pinMode(volDwnPin, INPUT_PULLUP);
  pinMode(chUpPin, INPUT_PULLUP);
  pinMode(chDwnPin, INPUT_PULLUP);
  pinMode(pageUpPin, INPUT_PULLUP);
  pinMode(guidePin, INPUT_PULLUP);
}

void loop() {
  power.update();
  volUp.update();
  volDwn.update();
  chUp.update();
  chDwn.update();
  pageUp.update();
  guide.update();

  if (power.risingEdge()) {
    mySender.send(GICABLE, POWER, 16);
    Serial.println("power");
  }
  if (volUp.risingEdge()) {
    mySender.send(GICABLE, VOLUME_UP, 16);
    Serial.println("volume up");
  }
  if (volDwn.risingEdge()) {
    mySender.send(GICABLE, VOLUME_DOWN, 16);
    Serial.println("volume down");
  }
  if (chUp.risingEdge()) {
    mySender.send(GICABLE, CHANNEL_UP, 16);
    Serial.println("channel up");
  }
  if (chDwn.risingEdge()) {
    mySender.send(GICABLE, CHANNEL_DOWN, 16);
    Serial.println("channel down");
  }
  if (pageUp.risingEdge()) {
    mySender.send(GICABLE, PAGE_UP, 16);
    Serial.println("page up");
  }
  if (guide.risingEdge()) {
    mySender.send(GICABLE, GUIDE, 16);
    Serial.println("guide");
  }
}
