/*  
    Obstacle_avoidance
    Frederick Feraco, NYS MASTER TEACHER PROGRAM, March 2023

    This program drives the Elegoo Smart Car forward until an obstacle is detected.
    It then looks around to find the most open area and turns towards it.
    
    Be sure to add the library for the devices:
    Sketch --> Include Library --> Add Zip Library --> HC-SR04.zip and servo.zip

    Place the car on the floor, press the mode switch, and it drives forward until it's too close to an object. 
    The car will then figure out the best way to go.

    Press the mode switch to start.
*/

// Include necessary libraries
#include "SR04.h"    // Library for the ultrasonic distance sensor
#include <Servo.h>   // Library for the servo motor

// Ultrasonic configuration
#define TRIG_PIN 13
#define ECHO_PIN 12 
SR04 sr04 = SR04(ECHO_PIN, TRIG_PIN);  // Create an instance of the ultrasonic class

// Servo configuration
#define servoPin 10
Servo servo1;  // Create an instance of the servo class

// Define motor IO pins
#define PWMA  5    // Controls power to the right motor
#define PWMB  6    // Controls power to the left motor
#define AIN   7    // Controls direction of the right motor, HIGH = FORWARD, LOW = REVERSE
#define BIN   8    // Controls direction of the left motor, HIGH = FORWARD, LOW = REVERSE
#define STBY  3    // Place H-Bridge in standby if LOW, Run if HIGH

// Variables
int speedLeft = 0;       // Holds the speed of the left wheels
int speedRight = 0;      // Holds the speed of the right wheels
int rightDistance = 0, leftDistance = 0, middleDistance = 0;  // Holds distances when it 'looks around'

#define modeSwitch 2  // Mode Switch input

// Initialize the car
void setup() {
  pinMode(PWMA, OUTPUT);     // Set IO pin mode to OUTPUT
  pinMode(PWMB, OUTPUT);
  pinMode(BIN, OUTPUT);
  pinMode(AIN, OUTPUT);
  pinMode(STBY, OUTPUT);
 
  analogWrite(PWMA, 0);       // Fully off for the Right motor
  analogWrite(PWMB, 0);       // Fully off for the Left motor
  digitalWrite(STBY, HIGH);   // Enable Motors to run

  servo1.attach(servoPin);    // Connect pin 10 with the control line of the servo 
  servo1.write(90);           // Move servos to the center position -> 90°

  waitForStart();             // Wait until the mode switch is pressed
  setSpeeds(100, 100);        // Sets speeds fairly high
}

// Main loop to drive forward until an object is detected
void loop() {
    servo1.write(90);                   // Look forward
    middleDistance = sr04.Distance();   // Get and store the distance from the ultrasonic sensor

    if (middleDistance <= 30) {          // If a nearby obstacle is in front...
      stop();
      delay(250);
      servo1.write(10);                  // Look right
      delay(1000);
      rightDistance = sr04.Distance();   // Get and store the distance from the ultrasonic sensor

      servo1.write(180);                // Look left
      delay(1000);
      leftDistance = sr04.Distance();   // Get and store the distance from the ultrasonic sensor

      servo1.write(90);                 // Look forward
      if ((rightDistance <= 30) || (leftDistance <= 30)) {  // If both sides are too close
        reverse();
        delay(500);
        spinLeft();
        delay(180);
      } else if (rightDistance > leftDistance) {   // If the right side is more open
        spinRight();
        delay(180);
      } else if (rightDistance < leftDistance) {  // If the left side is more open
        spinLeft();
        delay(180);
      } else {
        forward();
      }
    } else {
        forward();
    }
}

// Wait for the mode switch to be pressed
void waitForStart() {
  while (digitalRead(modeSwitch) == 1)  // Wait for the mode switch to be pressed (go to 0)
    ;  // Do nothing
  delay(2000);    // Delay for 2 seconds before starting
}

// Store speeds in variables to be used when driving
void setSpeeds(int leftSpeed, int rightSpeed) {
  speedLeft = leftSpeed;
  speedRight = rightSpeed;  
}

// Drive both motors in the forward direction at set speed
void forward() {
  digitalWrite(AIN, HIGH);
  digitalWrite(BIN, HIGH);
  analogWrite(PWMA, speedRight);
  analogWrite(PWMB, speedLeft);
}

// Drive both motors in the reverse direction at set speed
void reverse() {
  digitalWrite(AIN, LOW);
  digitalWrite(BIN, LOW);
  analogWrite(PWMA, speedRight);
  analogWrite(PWMB, speedLeft);
}

// Stop both motors
void stop() {
  analogWrite(PWMA, 0);
  analogWrite(PWMB, 0); 
}

// Turn left with 1/2 speed on the left motor going forward
void left() {
  digitalWrite(AIN, HIGH);
  digitalWrite(BIN, HIGH);
  analogWrite(PWMA, speedRight);
  analogWrite(PWMB, speedLeft / 2);
}

// Turn right with 1/2 speed on the right motor going forward
void right() {
  digitalWrite(AIN, LOW);
  digitalWrite(AIN, HIGH);
  analogWrite(PWMA, speedRight / 2);
  analogWrite(PWMB, speedLeft);    
}

// Spin left with the right motor forward and the left in reverse
void spinLeft() {
  digitalWrite(AIN, HIGH);
  digitalWrite(BIN, LOW);
  analogWrite(PWMA, speedRight);
  analogWrite(PWMB, speedLeft);
}

// Spin right with the left motor going forward and the right in reverse
void spinRight() {
  digitalWrite(AIN, LOW);
  digitalWrite(BIN, HIGH);
  analogWrite(PWMA, speedRight);
  analogWrite(PWMB, speedLeft);
}

// Function stopTime - accepts the time in milliseconds to go into standby for
void stopTime(int mS) {
  digitalWrite(STBY, LOW);    // Go into standby
  delay(mS);                  // Wait for the defined time
  digitalWrite(STBY, HIGH);   // Come out of standby
}
