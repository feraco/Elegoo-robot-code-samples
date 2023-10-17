/*  
    Drive_until_object
    Frederick Feraco, NYS MASTER TEACHER PROGRAM, March 2023

    This program drives the Elegoo Smart Car forward until an obstacle is detected.
    It then takes appropriate actions to avoid the obstacle.
    
    Be sure to add the library for the sensor:
    Sketch --> Include Library --> Add Zip Library --> HC-SR04.zip

    Place the car on the floor, press the mode switch, and it drives forward until it's too close to an object. 
    The car will then figure out the best way to go.

    Press the mode switch to start.
*/

// Include necessary libraries
#include "SR04.h"    // Library for the ultrasonic distance sensor

// Ultrasonic configuration
#define TRIG_PIN 13
#define ECHO_PIN 12 
SR04 sr04 = SR04(ECHO_PIN, TRIG_PIN);  // Create an instance of the ultrasonic class

// Define motor IO pins
#define PWMA  5    // Controls power to the right motor
#define PWMB  6    // Controls power to the left motor
#define AIN   7    // Controls direction of the right motor, HIGH = FORWARD, LOW = REVERSE
#define BIN   8    // Controls direction of the left motor, HIGH = FORWARD, LOW = REVERSE
#define STBY  3    // Place H-Bridge in standby if LOW, Run if HIGH

#define modeSwitch 2 // Mode Switch input

// Variables
int speedLeft = 0;  // Holds the speed of the left wheels
int speedRight = 0; // Holds the speed of the right wheels
long distance;      // Holds distance from sensor

// Initialize the car
void setup() {
  pinMode(PWMA, OUTPUT);     // Set IO pin mode to OUTPUT
  pinMode(PWMB, OUTPUT);
  pinMode(BIN, OUTPUT);
  pinMode(AIN, OUTPUT);
  pinMode(STBY, OUTPUT);
 
  analogWrite(PWMA, 0);       // Fully off for Right
  analogWrite(PWMB, 0);       // Fully off for Left
  digitalWrite(STBY, HIGH);   // Enable Motors to run

  waitForStart();             // Wait until the mode switch is pressed
  setSpeeds(100, 100);        // Sets moderate speed

  // Additional Example: Blink the built-in LED
  pinMode(LED_BUILTIN, OUTPUT);
}

// Main loop to drive forward until an object is detected
void loop() {
  forward();                  // Drive forward 
  distance = sr04.Distance(); // Get and store the distance from the ultrasonic sensor
  if (distance < 40) {        // If too close, stop, reverse, and turn
    stop();
    delay(500);
    reverse();
    delay(500);
    spinLeft();
    delay(250);

    // Additional Exercise: Make the LED blink when the car detects an obstacle
    digitalWrite(LED_BUILTIN, HIGH);
    delay(200);
    digitalWrite(LED_BUILTIN, LOW);
    delay(200);
  }

  // Additional Exercise: Implement a condition to play a sound when an obstacle is detected
  // Hint: Use a buzzer or speaker module and the tone() function
}

void waitForStart() {
  while (digitalRead(modeSwitch) == 1)  // Wait for mode switch to be pressed (go to 0)
    ;  // Do nothing
  delay(2000);    // Delay 2 seconds before starting
}

void setSpeeds(int leftSpeed, int rightSpeed) {
  speedLeft = leftSpeed;
  speedRight = rightSpeed;  
}

void forward() {
  digitalWrite(AIN, HIGH);
  digitalWrite(BIN, HIGH);
  analogWrite(PWMA, speedRight);
  analogWrite(PWMB, speedLeft);
}

void reverse() {
  digitalWrite(AIN, LOW);
  digitalWrite(BIN, LOW);
  analogWrite(PWMA, speedRight);
  analogWrite(PWMB, speedLeft);
}

void stop() {
  analogWrite(PWMA, 0);
  analogWrite(PWMB, 0); 
}

void left() {
  digitalWrite(AIN, HIGH);
  digitalWrite(BIN, HIGH);
  analogWrite(PWMA, speedRight);
  analogWrite(PWMB, speedLeft / 2);
}

void right() {
  digitalWrite(AIN, LOW);
  digitalWrite(AIN, HIGH);
  analogWrite(PWMA, speedRight / 2);
  analogWrite(PWMB, speedLeft);    
}

void spinLeft() {
  digitalWrite(AIN, HIGH);
  digitalWrite(BIN, LOW);
  analogWrite(PWMA, speedRight);
  analogWrite(PWMB, speedLeft);
}

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
