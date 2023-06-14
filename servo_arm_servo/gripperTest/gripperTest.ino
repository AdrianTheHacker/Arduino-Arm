#include <Servo.h>

Servo gripper;
int gripperPin = 6;
bool grip = false;
bool gripReleased = true;

void setup() {
  // put your setup code here, to run once:
  gripper.attach(4);

  pinMode(gripperPin, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  gripper.write(70);

  if(digitalRead(gripperPin) == HIGH) {
    gripper.write(70);
  }
  else {
    gripper.write(0);
  }

  delay(500);
}
