/*
  Teensy 2.0 with LED
  Used for demo vids
  Digital and analog pins grove connections
  starting at top right corner while USB port is away from you:
  | 21/A0, 20/A1, 19/A2, 18/A3 |
  | 17/A4, 16/A5, 15/A6, 14/A7 |
  | 13/A8, 12/A9, 11/A10, 22/A11 |

  Digital pins:
  | 23, 10, 9, 8 |
  | 7, 6, 5, 24 |
  | 3, 2, 1, 0 |
*/

#include <Bounce2.h>


const int debounceTime = 25;  //mS
//Bounce object handles contact chatter or "bounce", and simplifies state changes

//Bounce button0 = Bounce(0, debounceTime);


int buttonPushCounter1 = 0;   // counter for the number of button presses
int buttonState1 = 0;         // current state of the button
int lastButtonState1 = 0;     // previous state of the button

Bounce button1 = Bounce(19, debounceTime);

int range = 5;              // output range of X or Y movement; affects movement speed
int responseDelay = 20;     // response delay of the mouse, in ms
int LED = 4;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  pinMode(18, OUTPUT);
  digitalWrite(18, LOW);
  pinMode(19, INPUT_PULLUP);

}

void loop() {

  //button0.update();
  buttonState1 = button1.update();

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

  // turns on the LED every two button pushes
  if (buttonPushCounter1 % 2 == 0) {
    digitalWrite(LED, LOW);
  } else {
    digitalWrite(LED, HIGH);
  }

  /*
    if (rightClick.fallingEdge()) {
      Mouse.click(MOUSE_RIGHT);
      Serial.println("right click");
    }


    if (leftClick.fallingEdge()) {
      Mouse.click();
      Serial.println("left click");
    }
  */

  delay(responseDelay);
}
