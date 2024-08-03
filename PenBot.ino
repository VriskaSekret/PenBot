#include <Servo.h>
#include <ezButton.h>

//servo variables
Servo myservo;
Servo balls;
int ballOnePos = 70;
int ballTwoPos = 30;
int ballOne = 5;
int ballTwo = 2;
bool penIsDown = false;
bool changed = false;

//motor variables
int leftPos = 9;
int leftNeg = 8;
int rightPos = 7;
int rightNeg = 6;

bool hasStopped = false;

//limit switches
ezButton leftSwitch(3);
ezButton rightSwitch(4);

void setup() {
  // put your setup code here, to run once:
  pinMode (leftPos, OUTPUT);
  pinMode(leftNeg, OUTPUT);
  pinMode (rightPos, OUTPUT);
  pinMode(rightNeg, OUTPUT);
  leftSwitch.setDebounceTime(10);
  rightSwitch.setDebounceTime(10);
  myservo.attach(ballOne);
  balls.attach(ballTwo);
}

void Forward(int timeToMove){
  digitalWrite(rightNeg, LOW);
  digitalWrite(rightPos, HIGH);
  digitalWrite(leftNeg, LOW);
  digitalWrite(leftPos, HIGH);
  delay(timeToMove);
  myservo.write(ballOnePos);
  balls.write(ballTwoPos);
}

void Right(int timeToMove){
  digitalWrite(rightPos, LOW);
  digitalWrite(rightNeg, HIGH);
  digitalWrite(leftNeg, LOW);
  digitalWrite(leftPos, HIGH);
  delay(timeToMove);
}

void Left(int timeToMove){
  digitalWrite(rightNeg, LOW);
  digitalWrite(rightPos, HIGH);
  digitalWrite(leftPos, LOW);
  digitalWrite(leftNeg, HIGH);
  delay(timeToMove);
}

void Backward(int timeToMove){
  digitalWrite(rightPos, LOW);
  digitalWrite(rightNeg, HIGH);
  digitalWrite(leftPos, LOW);
  digitalWrite(leftNeg, HIGH);
  delay(timeToMove);
}

void Stop(int time){
  digitalWrite(rightPos, LOW);
  digitalWrite(rightNeg, LOW);
  digitalWrite(leftPos, LOW);
  digitalWrite(leftNeg, LOW);
  delay(time);
}


void PenDown(){
  ballOnePos = 30;
  ballTwoPos = 70;
  myservo.write(ballOnePos);
  balls.write(ballTwoPos);
  changed = false;
}

void PenUp(){
  ballOnePos = 70;
  ballTwoPos = 30;
  myservo.write(ballOnePos);
  balls.write(ballTwoPos);
  changed = false;
}

void loop() {
  //idk why but I need to run this loop first
  leftSwitch.loop();
  rightSwitch.loop();

  if (penIsDown){
    PenDown();
  }
  else{
    PenUp();
  }

  // put your main code here, to run repeatedly:
  Forward(0);


  if (leftSwitch.isPressed() and !hasStopped){
    hasStopped = true;
    Stop(1000);
    Backward(1000);
    Stop(1000);
    Right(2000);
    Stop(1000);
    if (penIsDown){
      penIsDown = false;
    }
    else{
      penIsDown = true;
    }
  }
  if (rightSwitch.isPressed() and !hasStopped){
    hasStopped = true;
    Stop(1000);
    Backward(1000);
    Stop(1000);
    Left(2000);
    Stop(1000);
    if (penIsDown){
      penIsDown = false;
    }
    else{
      penIsDown = true;
    }
  }
  if(leftSwitch.isReleased() || rightSwitch.isReleased()){
    hasStopped = false;
  }
  // Backward(1000);
  // Stop(1000);
  //   for (ballOnePos = 0; ballOnePos <= 180; ballOnePos += 1) { // goes from 0 degrees to 180 degrees
  //   // in steps of 1 degree
  //   myservo.write(ballOnePos);              // tell servo to go to position in variable 'ballOnePos'
  //   delay(15);                       // waits 15ms for the servo to reach the position
  // }
  // for (ballOnePos = 180; ballOnePos >= 0; ballOnePos -= 1) { // goes from 180 degrees to 0 degrees
  //   myservo.write(ballOnePos);              // tell servo to go to position in variable 'ballOnePos'
  //   delay(15);                       // waits 15ms for the servo to reach the position
  // }
}
