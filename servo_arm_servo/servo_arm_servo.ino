/////////////////
// Arduino Arm //
/////////////////

/*
 * The gripper the grips the grippable items.
 * 
 * By Adrian Tarantino 
 */

#include <Servo.h>

// The Servos that are used in the arm
Servo gripper;
Servo wristServo;
Servo elbowServo;

// The different set points for each servo
int gripGrab[2] = {0, 70};
int wristJoint[3] = {45, 90, 180};
int elbowJoint[3] = {90, 120, 180};

// The different buttons for controlling the arm
const int gripperButton = 6;
const int pos1Button = 7;
const int pos2Button = 8;
const int pos3Button = 9;

// Variables for controlling arms motion
int stage = 1;
bool isGrip = false;
bool buttonReleased = true;

void setup() {
  // Assigning roles to each pin 
  gripper.attach(4);
  wristServo.attach(3);
  elbowServo.attach(10);
  
  pinMode(gripperButton, INPUT);
  pinMode(pos1Button, INPUT);
  pinMode(pos2Button, INPUT);
  pinMode(pos3Button, INPUT);

  Serial.begin(9600);
}

// Position 1 is the closest point from the base of the arm.
void position1() {
  /*
   * Due to the position of the elbow joint at
   * position 3, the arm needs a greater delay to
   * move from position 3 to position 1 than position 2
   * to position 1.
   */ 
  int delayValue = 50;
  if(stage == 3) {
    delayValue = 150;
  }
  
  /*
   * Moves the arm's elbow and wrist joints to
   * the correct orrientations and sets the
   * position variable to be 1.
   */
  elbowServo.write(elbowJoint[0]);
  delay(delayValue);
  wristServo.write(wristJoint[0]); 
  stage = 1;
}

/*
 * Position 2 is the middle bewteen the arms max range,
 * and the arms base.
 */
void position2() {
  /*
   * Moves the arm's elbow and wrist joints to
   * the correct orrientations and sets the position
   * variable to be 2.
   */
  elbowServo.write(elbowJoint[1]); 
  delay(150);
  wristServo.write(wristJoint[1]);
  stage = 2;
}

/*
 * Position 3 is the farthest the arm can reach.
 */
void position3() {
  /*
   * If the claw is grabbing something, to
   * wrist must first move upward and then
   * the elbow can move upward.
   */
  if(buttonReleased) {
    wristServo.write(wristJoint[2]);
    delay(50);
  }
  
  /*
   * Moves the arm's elbow and wrist joints to
   * the correct orrientations and sets the position
   * variable to be 3.
   */
  elbowServo.write(elbowJoint[2]);
  delay(100);
  wristServo.write(wristJoint[2]);
  stage = 3;
}

/*
 * Grip checks if the gripperButton was clicked.
 * If the gripperButton is clicked then the
 * gripper grips.
 */
void grip() {
  /*
   * Opens the gripper unless the 
   * gripperButton was clicked.
   */
  gripper.write(gripGrab[0]);
  isGrip = false;

  if(digitalRead(gripperButton) == HIGH) {
    gripper.write(gripGrab[1]);
    isGrip = true;
  }

  delay(500);
}

void loop() {
  /*
   * Sets the position of the of the arm to
   * correspond with the inputs from the 
   * control buttons.
   */
  if(digitalRead(pos1Button) == HIGH) {
    position1();
    buttonReleased = false;
  }

  else if(digitalRead(pos2Button) == HIGH) {
    position2();
    buttonReleased = false;
  }

  else if(digitalRead(pos3Button) == HIGH) {
    position3();
    buttonReleased = false;
  }

  else {
    buttonReleased = true;
  }
  
  grip();
  delay(500);
}
