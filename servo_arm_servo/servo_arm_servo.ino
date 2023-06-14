#include <Servo.h>

Servo wrist_servo;
Servo elbow_servo;

int wristJoint[3] = {45, 90, 180};
int elbowJoint[3] = {90, 120, 180};

const int grab = 6;
const int pos1 = 7;
const int pos2 = 8;
const int pos3 = 9;

void setup() {
  // put your setup code here, to run once:
  wrist_servo.attach(3);
  elbow_servo.attach(2);
  
  pinMode(grab, INPUT);
  pinMode(pos1, INPUT);
  pinMode(pos2, INPUT);
  pinMode(pos3, INPUT);

  Serial.begin(9600);
}

void position1() {
  wrist_servo.write(wristJoint[0]);
  delay(50);
  elbow_servo.write(elbowJoint[0]);  
}

void position2() {
  wrist_servo.write(wristJoint[1]);
  delay(50);
  elbow_servo.write(elbowJoint[1]);  
}

void position3() {
  wrist_servo.write(wristJoint[2]);
  delay(50);
  elbow_servo.write(elbowJoint[2]);
}

void loop() {
//  if(digitalRead(grab) == HIGH) {
//    closeClaw();
//  }
  
  if(digitalRead(pos1) == HIGH) {
    position1();
    continue;
  }

  else if(digitalRead(pos2) == HIGH) {
    position2();
  }

  else if(digitalRead(pos3) == HIGH) {
    position3();
  }

  Serial.println(elbow_servo.read());
  delay(500);
}
