/*  
    Servo_Motion_Demo
    Frederick Feraco, NYS MASTER TEACHER PROGRAM, March 2023

    This program demonstrates servo motor control.
    
    Be sure to add the library for the servo motor:
    Sketch --> Include Library --> Add Zip Library --> Servo.zip
*/

#include <Servo.h>

Servo servo1;  // Create an object for the servo motor

void setup(){
  // Attach the servo motor to pin 10
  servo1.attach(10);   // Connect pin 10 with the control line of the servo
  servo1.write(90);    // Move the servo to the center position (90°)
} 

void loop(){
  // Example 1: Move the servo to the center position (90°) and wait for 1 second
  servo1.write(90);
  delay(1000);

  // Example 2: Move the servo to position 30° and wait for 1 second
  servo1.write(30);
  delay(1000);

  // Example 3: Move the servo back to the center position (90°) and wait for 1 second
  servo1.write(90);
  delay(1000);

  // Example 4: Move the servo to position 150° and wait for 1 second
  servo1.write(150);
  delay(1000);
}
