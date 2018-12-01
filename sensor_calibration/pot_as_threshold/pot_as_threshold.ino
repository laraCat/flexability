/*
  Calibration


  The circuit:
  - analog sensor (potentiometer will do) attached to A0
  - LED attached from digital pin 9 to ground
  - pot to set threshold pin A1

  based on:
  created 29 Oct 2008
  by David A Mellis
  modified 30 Aug 2011
  by Tom Igoe

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/Calibration
*/

// These constants won't change:
const int sensorPin = A0;    // pin that the sensor is attached to
const int ledPin = 9;        // pin that the LED is attached to
const int potPin = A1;       // high threshold calibration pot pin

// smoothing variables
const int numReadings = 10;

int readings[numReadings];      // the readings from the analog input
int readIndex = 0;              // the index of the current reading
int total = 0;                  // the running total
int average = 0;                // the average

// calibration variables:
int sensorValue = 0;         // the sensor value
int sensorMin = 1023;        // minimum sensor value
int sensorMax = 0;           // maximum sensor value



void setup() {
  // turn on LED to signal the start of the calibration period:
  pinMode(ledPin, OUTPUT);
  //digitalWrite(13, HIGH);
  Serial.begin(9600);

  // initialize all the smoothing variables to 0:
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }
/*
  // calibrate during the first five seconds
  while (millis() < 5000) {
    sensorValue = analogRead(sensorPin);

    // record the maximum sensor value
    if (sensorValue > sensorMax) {
      sensorMax = sensorValue;
    }

    // record the minimum sensor value
    if (sensorValue < sensorMin) {
      sensorMin = sensorValue;
    }
  }

  // signal the end of the calibration period
  digitalWrite(13, LOW);
  */
}

void loop() {
  // read the sensor:
  sensorValue = analogRead(sensorPin);
  // read the threshold pot
  int thresholdPot = analogRead(potPin);
  // print threshold
  Serial.print("threshold: ");
  Serial.println(thresholdPot);
  
  // subtract the last reading:
  total = total - readings[readIndex];
  // read from the sensor:
  readings[readIndex] = sensorValue;
  // add the reading to the total:
  total = total + readings[readIndex];
  // advance to the next position in the array:
  readIndex = readIndex + 1;

  // if we're at the end of the array...
  if (readIndex >= numReadings) {
    // ...wrap around to the beginning:
    readIndex = 0;
  }

  // calculate the average:
  average = total / numReadings;
  // print sensor value
  Serial.print("sensor value: ");
  Serial.println(average);
  
if (average > thresholdPot){
  digitalWrite(ledPin, HIGH);
} else {
  digitalWrite(ledPin, LOW);
}

/*
  Serial.print("value is: ");
  Serial.println(average);
  Serial.print("sensorMin is: ");
  Serial.println(sensorMin);
  Serial.print("sensorMax is: ");
  Serial.println(sensorMax);
  delay(10);

  // apply the calibration to the sensor reading
  average = map(sensorValue, sensorMin, sensorMax, 0, 255);

  // in case the sensor value is outside the range seen during calibration
  average = constrain(average, 0, 255);

  // fade the LED using the calibrated value:
  analogWrite(ledPin, average);
  */
  delay(10);
}
