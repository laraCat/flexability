/*
  Teensy 2.0 with grove USB cursor and mouse click
  Digital and analog pins grove connections:
  | 21, 20, 19, 18 |
  | 17, 16, 15, 14 |
  | 13, 12, 11, 22 |

  Digital pins:
  | 23, 10, 9, 8 |
  | 7, 6, 5, 24 |
  | 3, 2, 1, 0 |
*/

#include <Bounce2.h>
#include "Mouse.h"

const int debounceTime = 25;  //mS

int buttonPushCounter1 = 0;   // counter for the number of button presses
int buttonState1 = 0;         // current state of the button
int lastButtonState1 = 0;     // previous state of the button

int buttonPushCounter2 = 0;   // counter for the number of button presses
int buttonState2 = 0;         // current state of the button
int lastButtonState2 = 0;     // previous state of the button

// x/y
const int upButton = 22;
const int downButton = 12;
const int leftButton = 14;
const int rightButton = 16;

// diagonals
const int seButton = 3;
const int swButton = 5;
const int neButton = 7;
const int nwButton = 9;

//mouse click pins
Bounce button1 = Bounce(1, debounceTime); // left lock on/off
Bounce rightClick = Bounce(20, debounceTime);
Bounce leftClick = Bounce(18, debounceTime);

int range = 5;              // output range of X or Y movement; affects movement speed
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

  pinMode(20, INPUT_PULLUP);
  pinMode(18, INPUT_PULLUP);
  pinMode(1, INPUT_PULLUP);

  // pull down on all pin pairs for switches
  pinMode(11, OUTPUT);
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
  digitalWrite(11, LOW);
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


}

void loop() {


  buttonState1 = button1.update();
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


  // compare the buttonState to its previous state
  if (buttonState1 != lastButtonState1) {
    // if the state has changed, increment the counter
    if (button1.fallingEdge()) {
      // if the current state is HIGH then the button
      // wend from off to on:
      buttonPushCounter1++;
      Serial.println("on");
      Serial.print("number of button pushes:  ");
      Serial.println(buttonPushCounter1);
    }
    else {
      // if the current state is LOW then the button
      // wend from on to off:
      Serial.println("off");
    }
  }
  lastButtonState1 = buttonState1;

  // Locks on mouse left every two pushes
  if (buttonPushCounter1 % 2 == 0) {
    Mouse.release(MOUSE_LEFT);
    Serial.println("left off");
  } else {
    Mouse.press(MOUSE_LEFT);
    Serial.println("left on");
  }

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
}
