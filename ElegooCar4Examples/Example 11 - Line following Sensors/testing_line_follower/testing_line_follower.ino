/* 
  Testing Line Tracking Sensors
  Frederick Feraco, NYS MASTER TEACHER PROGRAM, October 2023

  This program is for testing line tracking sensors by running the code and observing different reflective surfaces 
  placed under the car's line tracking module on the bottom. The sensor values are displayed in the Serial Monitor.

  Suggestion for students: Develop your own code to follow a line based on sensor values.
*/

// Defines to replace code to read the sensors when using LT_R, LT_M, and LT_L
#define LT_R analogRead(A0)
#define LT_M analogRead(A1)
#define LT_L analogRead(A2)

void setup() {
  // Initialize the Serial communication for displaying sensor values
  Serial.begin(9600);
}

void loop() {
  // Display the values of sensors from 0 (full reflection) to 1023 (no reflection)
  Serial.print("Left Sensor Value = ");
  Serial.print(LT_L);
  Serial.print("  Middle Sensor Value = ");
  Serial.print(LT_M);
  Serial.print("  Right Sensor Value = ");
  Serial.println(LT_R);
  
  // Add code here to develop your own line-following algorithm based on sensor values
  
  delay(50); // Delay for a short time before taking another sensor reading
}

// Ideas for Students:
// 1. Create a function to interpret sensor values and make decisions on which direction to move.
// 2. Experiment with different threshold values to detect the line.
// 3. Implement a PID control algorithm for smoother line following.
// 4. Add additional sensors for more precise line tracking.
// 5. Incorporate motor control to make the car follow the line autonomously.
