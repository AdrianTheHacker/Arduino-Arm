#include <Servo.h>

Servo gripper;
Servo wrist_servo;
Servo elbow_servo;

int gripGrab[2] = {0, 70};
int wristJoint[3] = {45, 90, 180};
int elbowJoint[3] = {90, 120, 180};

const int gripperPin = 6;
const int pos1 = 7;
const int pos2 = 8;
const int pos3 = 9;

int stage = 1;
bool isGrip = false;
bool buttonReleased = true;

void setup() {
  // put your setup code here, to run once:
  gripper.attach(4);
  wrist_servo.attach(3);
  elbow_servo.attach(10);
  
  pinMode(gripperPin, INPUT);
  pinMode(pos1, INPUT);
  pinMode(pos2, INPUT);
  pinMode(pos3, INPUT);

  Serial.begin(9600);
}

void position1() {
  if(stage == 3) {
    elbow_servo.write(elbowJoint[0]);
    delay(150);
    wrist_servo.write(wristJoint[0]);
    
    stage = 1;
    return;
  }
  
  elbow_servo.write(elbowJoint[0]);
  delay(50);
  wrist_servo.write(wristJoint[0]); 

  stage = 1;
}

void position2() {
  elbow_servo.write(elbowJoint[1]); 
  delay(150);
  wrist_servo.write(wristJoint[1]);

  stage = 2;
}

void position3() {
  if(buttonReleased) {
    wrist_servo.write(wristJoint[2]);
    delay(50);
  }
  
  elbow_servo.write(elbowJoint[2]);
  delay(100);
  wrist_servo.write(wristJoint[2]);

  stage = 3;
}

void grip() {
  gripper.write(gripGrab[0]);
  isGrip = false;

  if(digitalRead(gripperPin) == HIGH) {
    gripper.write(gripGrab[1]);
    isGrip = true;
  }

  delay(500);
}

void loop() {
  if(digitalRead(pos1) == HIGH) {
    position1();
    buttonReleased = false;
  }

  else if(digitalRead(pos2) == HIGH) {
    position2();
    buttonReleased = false;
  }

  else if(digitalRead(pos3) == HIGH) {
    position3();
    buttonReleased = false;
  }

  else {
    buttonReleased = true;
  }
  
  grip();
  delay(500);
}
