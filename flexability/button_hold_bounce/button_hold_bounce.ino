#include <Bounce.h>
Bounce buttonRecord = Bounce(0, 8);

unsigned long time = 0;

void setup() {
  pinMode(0, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  buttonRecord.update();

  if (buttonRecord.fallingEdge()) {
    time = millis();
  }

  if (buttonRecord.risingEdge()) {
    // check if the switch is pressed for longer than 1 second.
    if (time - millis() > 1000)
    {
      Serial.println("long press");
    } else {
      Serial.println("short press");
    }
  }

}
