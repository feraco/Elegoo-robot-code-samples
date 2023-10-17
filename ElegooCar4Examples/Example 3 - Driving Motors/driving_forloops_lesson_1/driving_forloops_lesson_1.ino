// Lesson 2: Basic Motor Control with For Loops
// In this lesson, we will learn how to control the Elegoo smart car's motors using 'for' loops.

// Define IO pin
#define PWMA  5     // Controls power to right motor
#define PWMB  6     // Controls power to left motor
#define AIN   7     // Controls direction of right motor, HIGH = FORWARD, LOW = REVERSE
#define BIN   8     // Controls direction of right motor, HIGH = FORWARD, LOW = REVERSE
#define STBY  3     // Place H-Bridge in standby if LOW, Run if HIGH
#define modeSwitch 2 // Mode Switch input

// Initialize the car
void setup() {
  pinMode(PWMA, OUTPUT);     // Set IO pin mode OUTPUT
  pinMode(PWMB, OUTPUT);
  pinMode(BIN, OUTPUT);
  pinMode(AIN, OUTPUT);
  pinMode(STBY, OUTPUT);
  digitalWrite(PWMA, LOW);   // Fully Off
  digitalWrite(STBY, HIGH);  // Enable Motors to run
}

// Function to move the car forward for a specified number of steps using 'for' loop
void moveForwardSteps(int steps) {
  digitalWrite(AIN, HIGH);    // Forward direction on Right
  digitalWrite(BIN, HIGH);    // Forward direction on Left
  digitalWrite(PWMA, HIGH);   // Full power on Right
  digitalWrite(PWMB, HIGH);   // Full power on Left

  // Use a 'for' loop to move the car for the specified number of steps
  for (int i = 0; i < steps; i++) {
    // Adjust the delay to control the speed and distance covered in each step
    delay(1000);  // 1-second delay (adjust as needed)
  }

  // Stop the car after the loop completes
  stopMotors();
}

// Function to stop the motors
void stopMotors() {
  digitalWrite(PWMA, LOW);   // No power on Right
  digitalWrite(PWMB, LOW);   // No power on Left
}

// Main loop
void loop() {
  while (digitalRead(modeSwitch) == 1)  // Wait for mode switch to be pressed (go to 0)
    ;  // Do nothing

  delay(2000);

  // Example 1: Move the car forward for 3 steps
  moveForwardSteps(3);  // Move forward for 3 seconds
  delay(2000);

  // Example 2: Move the car forward for 5 steps
  moveForwardSteps(5);  // Move forward for 5 seconds
  delay(2000);

  // Example 3: Move the car forward for 2 steps
  moveForwardSteps(2);  // Move forward for 2 seconds
  delay(2000);

  stopMotors();  // Stop the car

  // Task for Students:
  // Create a new function that makes the car move backward for a specified number of steps using a 'for' loop.
  // Test your function by making the car move backward for different numbers of steps.
}
