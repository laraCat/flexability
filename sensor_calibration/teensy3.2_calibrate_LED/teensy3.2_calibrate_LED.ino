/*
  Calibration LED output

  The circuit:
  Teensy 
  - sensor on A2
  - LED on for calibration time
  - LED for mapping calibrated min and mx to

  based on:
  http://www.arduino.cc/en/Tutorial/Calibration
*/

// These constants won't change:
const int sensorPin = A2;    // pin that the sensor is attached to
const int ledPin = 4;        // pin that the LED is attached to
const int ledMap = 3;

// variables:
int sensorValue = 0;         // the sensor value
int sensorMin = 1023;        // minimum sensor value
int sensorMax = 0;           // maximum sensor value


void setup() {

  Serial.begin(9600);

  // turn on LED to signal the start of the calibration period:
  pinMode(ledPin, OUTPUT);
  pinMode(ledMap, OUTPUT);
  digitalWrite(ledPin, HIGH);
  pinMode(18, OUTPUT);
  digitalWrite(18, LOW);
  pinMode(19, INPUT_PULLUP);


  // calibrate during the first five seconds
  while (millis() < 5000) {
    sensorValue = analogRead(sensorPin);

    // record the maximum sensor value
    if (sensorValue > sensorMax) {
      sensorMax = sensorValue;
    }

    // record the minimum sensor value
    if (sensorValue < sensorMax) {
      sensorMin = sensorValue;
    }
  }

  // signal the end of the calibration period
  digitalWrite(ledPin, LOW);
  delay(1000);
}

void loop() {
  // read the sensor:
  sensorValue = analogRead(sensorPin);
  Serial.println(sensorValue);
  
    // fade LED with new min and max values
    // apply the calibration to the sensor reading
    sensorValue = map(sensorValue, sensorMax, sensorMin, -10, 255);

    // in case the sensor value is outside the range seen during calibration
    sensorValue = constrain(sensorValue, 0, 255);

    // fade the LED using the calibrated value:
    analogWrite(ledPin, sensorValue);
  
/*
  // turn on led if recorded max is crossed
  if (sensorValue <= sensorMin) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }
*/
  //  Serial.print("sensorValue = ");
  //  Serial.println(sensorValue);
  Serial.print("sensorMin = ");
  Serial.println(sensorMin);
  Serial.print("sensorMax = ");
  Serial.println(sensorMax);

  delay(10);
}
