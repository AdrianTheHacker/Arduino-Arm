#include <Servo.h>

Servo wrist_servo;
Servo elbow_servo;

int wristJoint[3] = {45, 90, 180};
int elbowJoint[3] = {90, 45, 0};

void setup() {
  // put your setup code here, to run once:
  wrist_servo.attach(3);
  elbow_servo.attach(2);
}

void position1() {
  wrist_servo.write(wristJoint[0]);
  elbow_servo.write(elbowJoint[0]);  
}

void position2() {
  wrist_servo.write(wristJoint[1]);
  elbow_servo.write(elbowJoint[1]);  
}

void position3() {
  wrist_servo.write(wristJoint[2]);
  elbow_servo.write(elbowJoint[2]);
}

void loop() {
  // put your main code here, to run repeatedly:
  position2();
}
