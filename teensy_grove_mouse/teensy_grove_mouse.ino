/*
  Teensy 2.0 with grove USB cursor and mouse clicks
  Select Serial + Keyboard + Mouse + Joystick for "USB Type:" under Tools menu
  On/off button for mouse functionality on pin 12

  Starting at right corner port side and going down:
  | 21, 20, 19, 18 | analog
  | 17, 16, 15, 14 | analog
  | 13, 12, 11, 22 | analog

  Starting at the bottom left corner and going up:
  | 23, 10, 9, 8 | digital
  | 7, 6, 5, 24 | digital
  | 3, 2, 1, 0 | digital

  LED - pin 4
  Cursor speed pot - pin 22/A11
  
  Last update 9/11/19
*/

#include <Bounce2.h>

const int debounceTime = 25;  //mS

const int led = 4;

int speedPot = A11;

int buttonPushCounter1 = 0;   // counter for the number of button presses
int buttonState1 = 0;         // current state of the button
int lastButtonState1 = 0;     // previous state of the button

int buttonPushCounter2 = 0;   // counter for the number of button presses
int buttonState2 = 0;         // current state of the button
int lastButtonState2 = 0;     // previous state of the button

// x/y
const int upButton = 5;
const int downButton = 23;
const int leftButton = 9;
const int rightButton = 7;

// diagonals
const int seButton = 18;
const int swButton = 14;
const int neButton = 20;
const int nwButton = 16;

//mouse click pins
Bounce mouseOn = Bounce(12, debounceTime); // mouse on/off
Bounce leftLock = Bounce(11, debounceTime); // left-click lock
Bounce rightClick = Bounce(1, debounceTime);
Bounce leftClick = Bounce(3, debounceTime);

int range = 8;              // output range of X or Y movement; affects movement speed
int responseDelay = 20;     // response delay of the mouse, in ms


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(upButton, INPUT_PULLUP);
  pinMode(downButton, INPUT_PULLUP);
  pinMode(leftButton, INPUT_PULLUP);
  pinMode(rightButton, INPUT_PULLUP);

  pinMode(seButton, INPUT_PULLUP);
  pinMode(swButton, INPUT_PULLUP);
  pinMode(neButton, INPUT_PULLUP);
  pinMode(nwButton, INPUT_PULLUP);

  //pinMode(20, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP); // right-click
  pinMode(1, INPUT_PULLUP); // left-click

  pinMode(12, INPUT_PULLUP); // mouse on/off
  pinMode(11, INPUT_PULLUP); // left-click lock

  // pull down on all pin pairs for switches
  pinMode(10, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(15, OUTPUT);
  pinMode(17, OUTPUT);
  pinMode(19, OUTPUT);
  pinMode(21, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(24, OUTPUT);
  pinMode(0, OUTPUT);
  pinMode(2, OUTPUT);
  digitalWrite(10, LOW);
  digitalWrite(13, LOW);
  digitalWrite(15, LOW);
  digitalWrite(17, LOW);
  digitalWrite(19, LOW);
  digitalWrite(21, LOW);
  digitalWrite(8, LOW);
  digitalWrite(6, LOW);
  digitalWrite(24, LOW);
  digitalWrite(0, LOW);
  digitalWrite(2, LOW);

  pinMode(4, OUTPUT); // LED
}

void loop() {

  buttonState1 = mouseOn.update();
  // buttonState2 = leftLock.update();


  if (buttonState1 != lastButtonState1) {
    if (mouseOn.fallingEdge()) {
      buttonPushCounter1++;
    } else {
      // if the current state is LOW then the button went from on to off:
      // Serial.println("off");
    }
  }
  lastButtonState1 = buttonState1;

  // turn off mouse every two pushes
  if (buttonPushCounter1 % 2 == 0) {
    mouseOff();
    digitalWrite(led, LOW);
  } else {
    //////////////// start of complete mouse move program ////////////////
    rightClick.update();
    leftClick.update();

    int upState = digitalRead(upButton);
    int downState = digitalRead(downButton);
    int rightState = digitalRead(rightButton);
    int leftState = digitalRead(leftButton);

    int seState = digitalRead(seButton);
    int swState = digitalRead(swButton);
    int neState = digitalRead(neButton);
    int nwState = digitalRead(nwButton);
    int cursorSpeed = analogRead(speedPot);
    //Serial.println(cursorSpeed);

    int speedSteps = map(cursorSpeed, 0, 1023, 1, 8); // map to 8 speed settings
    //Serial.println(speedSteps);

    range = speedSteps;

    if ((speedSteps == 1) | (speedSteps == 2)) {
      range = 2;
      Serial.println(range);
    }
    if ((speedSteps == 3) | (speedSteps == 4)) {
      range = 4;
      Serial.println(range);
    }
    if ((speedSteps == 5) | (speedSteps == 6)) {
      range = 6;
      Serial.println(range);
    }
    if ((speedSteps == 7) | (speedSteps == 8)) {
      range = 8;
      Serial.println(range);
    }

    ////////// left-click lock ////////////
    buttonState2 = leftLock.update();

    // put your main code here, to run repeatedly:
    if (buttonState2 != lastButtonState2) {
      if (leftLock.fallingEdge()) {
        buttonPushCounter2++;
      } else {
        // if the current state is LOW then the button went from on to off:
        Serial.println("off");
      }
    }
    lastButtonState2 = buttonState2;

    // Locks mouse left every two pushes
    if (buttonPushCounter2 % 2 == 0) {
      Mouse.release(MOUSE_LEFT);
      Serial.println("left off");
    } else {
      Mouse.press(MOUSE_LEFT);
      Serial.println("left on");
    }
    ////////// left-click lock ////////////

    if (rightClick.fallingEdge()) {
      Mouse.click(MOUSE_RIGHT);
      Serial.println("right click");
    }

    if (leftClick.fallingEdge()) {
      Mouse.click();
      Serial.println("left click");
    }

    // calculate the movement distance based on the button states:
    int  xDistance = (leftState - rightState) * range;
    int  yDistance = (upState - downState) * range;

    // if X or Y is non-zero, move:
    if ((xDistance != 0) || (yDistance != 0)) {
      Mouse.move(xDistance, yDistance, 0);
    }

    // NE
    if (neState == LOW) {
      Mouse.move(range, -range);
    }

    // NW
    if (nwState == LOW) {
      Mouse.move(-range, -range);
    }

    // SW
    if (swState == LOW) {
      Mouse.move(-range, range);
    }

    // SE
    if (seState == LOW) {
      Mouse.move(range, range);
    }

    delay(responseDelay);
    //////////////// end of complete program ////////////////

    Serial.println("left on");
    digitalWrite(led, HIGH);
  }
}

void mouseOff() {
  Serial.println("mouse off");
}
