/*
   This code is used to control the robotic arm based on the inputs from the
   Raspberry Pi. The Raspberry Pi will detect the recycle and will tell the Arduino
   to move the robotic arm in the location the object is detected at. Based on
   the material, the robotic arm will place the object in the correct loaction.
*/

// add Servo library
#include <Servo.h>

// create variables to store data from RPI
int numBlink = 0;
int distance = 0;
int material = 0;
int angle = 90;

// create variables to store servo posistions
int shoulderPos = 90;
int elbowPos = 90;
int wrist1Pos = 90;
int wrist2Pos = 90;
int handPos = 90;
int basePos = 90;

// create Servo objects to control servos
Servo shoulder;
Servo elbow;
Servo wrist1;
Servo wrist2;
Servo hand;
Servo base;

// create flash function (will flash Arduino LED by the number you input)
//void flash(int n) {
//  for (int i = 0; i < n; i++) {
//    digitalWrite(13, HIGH);
//    delay(500);
//    digitalWrite(13, LOW);
//    delay(500);
//  }
//}

void setup() {
  // begin serial communication with RPI and send default string to RPI to confirm connection
  Serial.begin(9600);
  Serial.println("Connected to Arduino");

  // assign Arduino LED to pin 13
//  pinMode(13, OUTPUT);

  // attach servo objects to correct pin number
  shoulder.attach(11);
  elbow.attach(10);
  wrist1.attach(9);
  wrist2.attach(6);
  hand.attach(5);
  base.attach(3);

  // move arm to home position to face camera down
  homeState();
}

void loop() {
  // send default string to RPI to confirm connection
  Serial.println("Connected to Arduino");

  // if the RPI sends a signal to Arduino
  if (Serial.available()) {
    // change values of variables to what the RPI sends
    numBlink = Serial.parseInt();
    material = Serial.parseInt();
    angle = 90;

    // flash LED and move the arm to pick and drop the object based on its material
    //flash(numBlink);
    pickUp();
    delay(500);
    dropOff();

    // go back to home state
    homeState();

    // send string to let RPI know that the arm is done moving
    Serial.println("Done Moving");
    Serial.flush();
  }
  delay(1000);
}

/*
   sweep function to make servos move slowly!

   input the servo object, the current servo angle, the angle you
   want the servo to move to, and the speed at which you want to turn
   the servo. Bigger number ==> slower speed. Smaller number ==> faster speed.
*/
void sweep(Servo servo, int oldPos, int newPos, int servoSpeed) {
  if (oldPos <= newPos) {
    for (oldPos; oldPos <= newPos; oldPos += 1) {
      servo.write(oldPos);
      delay(servoSpeed);
    }
  }

  else if (oldPos >= newPos) {
    for (oldPos; oldPos >= newPos; oldPos -= 1) {
      servo.write(oldPos);
      delay(servoSpeed);
    }
  }
  servo.write(newPos);
  delay(1000);
}

// pickUp function that will move robotic arm to specified distance and angle sent from RPI
void pickUp() {  
  Serial.println("pickupppp");
//    sweep(hand, handPos, 160, 30);
//    handPos = 160;
//    sweep(shoulder, shoulderPos,145, 30);
//    shoulderPos = 145;
//    sweep(wrist2, wrist2Pos, 25, 30);
//    wrist2Pos = 25;
//    sweep(elbow, elbowPos,0, 30);
//    elbowPos = 0;
//    sweep(hand, handPos,5, 30);
//    handPos = 5;
    sweep(hand, handPos, 160, 10);
    handPos = 160;
    sweep(shoulder, shoulderPos,155, 30);
    shoulderPos = 155;
    sweep(elbow, elbowPos, 0, 30);
    elbowPos = 0;
    hand.write(5);
    delay(500);
    handPos = 5;
  
}

// dropOff function that will drop off the object to a location based off its material
void dropOff() {
  // if the material detected was cardboard
  if (material == 1) {
    Serial.println("Wrong Place!");
  }

  // if the material detected was glass
  else if (material == 2) {
    Serial.println("drop glass");
      sweep(shoulder, shoulderPos,120, 30);
    shoulderPos = 120;
    sweep(elbow, elbowPos,20, 30);
    elbowPos = 20;
    sweep(base, basePos,50, 30);//glass
    basePos = 50;
    sweep(shoulder, shoulderPos,150, 30);
    shoulderPos = 150;
    sweep(hand, handPos, 160, 10);
    handPos = 160;
    material = 0;
  }

  // if the material detected was metal
  else if (material == 3) {
    Serial.println("drop metal");
sweep(shoulder, shoulderPos,120, 30);
    shoulderPos = 120;
    sweep(elbow, elbowPos,20, 30);
    elbowPos = 20;
    sweep(base, basePos,90, 30);//metal
    basePos = 90;
    sweep(shoulder, shoulderPos,150, 30);
    shoulderPos = 150;
    sweep(hand, handPos, 160, 10);
    handPos = 160;
    material = 0;
  }

  // if the material detected was paper
  else if (material == 4) {
    Serial.println("drop paper");
sweep(shoulder, shoulderPos,120, 30);
    shoulderPos = 120;
    sweep(elbow, elbowPos,20, 30);
    elbowPos = 20;
    sweep(base, basePos,170, 30);//paper
    basePos = 170;
    sweep(shoulder, shoulderPos,150, 30);
    shoulderPos = 150;
    sweep(hand, handPos, 160, 10);
    handPos = 160;
    material = 0;
  }

  // if the material detected was plastic
  else if (material == 5) {
    Serial.println("drop plastic");
sweep(shoulder, shoulderPos,120, 30);
    shoulderPos = 120;
    sweep(elbow, elbowPos,20, 30);
    elbowPos = 20;
    sweep(base, basePos,130, 30);//plastic
    basePos = 130;
    sweep(shoulder, shoulderPos,150, 30);
    shoulderPos = 150;
    sweep(hand, handPos, 160, 10);
    handPos = 160;
    material = 0;
  }
}

// homeState function that will hold the camera facing down to perform obejct detection
void homeState() {
   sweep(base, basePos,0, 30);
  basePos = 0;
  sweep(elbow, elbowPos,20, 30);
  elbowPos = 20;
  sweep(shoulder, shoulderPos, 85, 30);
  shoulderPos = 85;
  sweep(wrist2, wrist2Pos, 48, 10);
  wrist2Pos = 48;
  sweep(wrist1, wrist1Pos, 55, 30);
  wrist1Pos = 55;

}
