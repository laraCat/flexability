
int buttonPin = 0;

void setup() {
  // Configure the pushbutton pins
  pinMode(buttonPin, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  if (digitalRead(buttonPin) == LOW) {
    int time = millis();
    delay(200); //debounce
    // check if the switch is pressed for longer than 1 second.
    if (digitalRead(buttonPin) == LOW && time - millis() > 1000)
    {
      Serial.println("long press");
    } else {
      Serial.println("short press");
    }



  }
}
