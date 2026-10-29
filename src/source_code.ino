#include <Servo.h>

// Servo Motors
Servo baseServo;
Servo shoulderServo;
Servo elbowServo;
Servo gripperServo;

// Servo signal pins
int basePin = 3;
int shoulderPin = 5;
int elbowPin = 6;
int gripperPin = 9;

// IR Sensor 
int irPin = 2;

// Right Conveyor (Motor A)
int motorA1 = 8;
int motorA2 = 7;
int enaPin = 11;   // PWM

// Left Conveyor (Motor B)
int motorB1 = 12;
int motorB2 = 13;
int enbPin = 10;   // PWM

// Arm Angles
int basePick = 1;
int basePlace = 160;

int shoulderDown = 105;
int shoulderUp = 60;

int elbowDown = 55;
int elbowUp = 70;

int gripperOpen = 60;
int gripperClose = 100;

void setup() {
  Serial.begin(9600);

  // Attach servos (signal only)
  baseServo.attach(basePin);
  shoulderServo.attach(shoulderPin);
  elbowServo.attach(elbowPin);
  gripperServo.attach(gripperPin);

  // Motor pins
  pinMode(motorA1, OUTPUT);
  pinMode(motorA2, OUTPUT);
  pinMode(enaPin, OUTPUT);

  pinMode(motorB1, OUTPUT);
  pinMode(motorB2, OUTPUT);
  pinMode(enbPin, OUTPUT);

  // IR sensor
  pinMode(irPin, INPUT);

  // Arm start position
  shoulderServo.write(shoulderUp);
  elbowServo.write(elbowUp);
  gripperServo.write(gripperOpen);
  baseServo.write(90);

  // Start conveyors
  startLeftConveyor();
  delay(2000);
}

void loop() {
  int irState = digitalRead(irPin);

  if (irState == LOW) {
    Serial.println("Big object detected!");

    stopLeftConveyor();
    delay(500);

    startRightConveyor();

    pickObject();
    delay(2000);
    placeObject();
    delay(3000);

    startLeftConveyor();
    delay(500);
    stopRightConveyor();
  }
  else {
    Serial.println("Small object allowed");
  }

  delay(200);
}

// Conveyor Controls
void startRightConveyor() {
  digitalWrite(motorA1, HIGH);
  digitalWrite(motorA2, LOW);
  analogWrite(enaPin, 200);
}

void stopRightConveyor() {
  digitalWrite(motorA1, LOW);
  digitalWrite(motorA2, LOW);
  analogWrite(enaPin, 0);
}

void stopLeftConveyor() {
  digitalWrite(motorB1, LOW);
  digitalWrite(motorB2, LOW);
  analogWrite(enbPin, 0);
}

void startLeftConveyor() {
  digitalWrite(motorB1, LOW);
  digitalWrite(motorB2, HIGH);
  analogWrite(enbPin, 200);
}

// Robot Pick & Place
void pickObject() {
  // Move to pick position
  baseServo.write(basePick);
  delay(1000);

  shoulderServo.write(shoulderDown);
  elbowServo.write(elbowDown);
  delay(1000);

  // Close gripper to grab object
  gripperServo.write(gripperClose);
  delay(1000);

  // Lift object
  shoulderServo.write(shoulderUp);
  elbowServo.write(elbowUp);
  delay(1000);
}

void placeObject() {
  // Rotate base to place position
  baseServo.write(basePlace);
  delay(2000);

  // Lower arm
  shoulderServo.write(100);
  elbowServo.write(elbowDown);
  delay(2000);

  // Release object
  gripperServo.write(gripperOpen);
  delay(2000);

  // Lift arm back up
  shoulderServo.write(shoulderUp);
  elbowServo.write(elbowUp);
  delay(2000);

  // Return to start position
  baseServo.write(90);
}