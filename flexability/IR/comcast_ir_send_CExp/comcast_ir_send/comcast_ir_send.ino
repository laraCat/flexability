/* Infrared_Send.ino Example sketch for IRLib2 and Circuit Playground Express
   Illustrates how to transmit an IR signal whenever you do push one of the
   built-in pushbuttons.
   Sends Samsung on/off code for Stochastic Labs TV
*/
#include <Adafruit_CircuitPlayground.h>

#if !defined(ADAFRUIT_CIRCUITPLAYGROUND_M0)
#error "Infrared support is only for the Circuit Playground Express, it doesn't work with the Classic version"
#endif

void setup() {
  CircuitPlayground.begin();
  Serial.begin(9600);
}

//Defines for a Comcast Universal remote using GI Cable protocol
#define MY_PROTOCOL GICABLE
#define MY_BITS 16
#define MY_POWER 0x5006
#define VOLUME_UP 0xB00C


void loop() {
  // If the right button is pressed send a power code.
  if (CircuitPlayground.rightButton()) {
    CircuitPlayground.irSend.send(MY_PROTOCOL, MY_POWER, MY_BITS);
    Serial.println("power pressed");
    //CircuitPlayground.irSend.send(MY_PROTOCOL, REPEAT_CODE, MY_BITS);
    while (CircuitPlayground.rightButton()) {}//wait until button released
  }

  if (CircuitPlayground.leftButton()) {
    CircuitPlayground.irSend.send(MY_PROTOCOL, VOLUME_UP, MY_BITS);
    Serial.println("volume up");
    //CircuitPlayground.irSend.send(MY_PROTOCOL, REPEAT_CODE, MY_BITS);
    while (CircuitPlayground.leftButton()) {}//wait until button released
  }

}
