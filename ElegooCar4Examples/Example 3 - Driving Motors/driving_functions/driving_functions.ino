// define IO pin
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

// Function to move the car forward for a specified duration in milliseconds
void moveForward(int duration) {
  digitalWrite(AIN, HIGH);    // Forward direction on Right
  digitalWrite(BIN, HIGH);    // Forward direction on Left
  digitalWrite(PWMA, HIGH);   // Full power on Right
  digitalWrite(PWMB, HIGH);   // Full power on Left
  delay(duration);
  stopMotors();
}

// Function to move the car backward for a specified duration in milliseconds
void moveBackward(int duration) {
  digitalWrite(AIN, LOW);    // Reverse direction on Right
  digitalWrite(BIN, LOW);    // Reverse direction on Left
  digitalWrite(PWMA, HIGH);  // Full power on Right
  digitalWrite(PWMB, HIGH);  // Full power on Left
  delay(duration);
  stopMotors();
}

// Function to make the car turn left for a specified duration in milliseconds
void turnLeft(int duration) {
  digitalWrite(AIN, LOW);     // Reverse direction on Right
  digitalWrite(BIN, HIGH);    // Forward direction on Left
  digitalWrite(PWMA, HIGH);   // Full power on Right
  digitalWrite(PWMB, HIGH);   // Full power on Left
  delay(duration);
  stopMotors();
}

// Function to make the car turn right for a specified duration in milliseconds
void turnRight(int duration) {
  digitalWrite(AIN, HIGH);    // Forward direction on Right
  digitalWrite(BIN, LOW);     // Reverse direction on Left
  digitalWrite(PWMA, HIGH);   // Full power on Right
  digitalWrite(PWMB, HIGH);   // Full power on Left
  delay(duration);
  stopMotors();
}

// Function to stop the motors
void stopMotors() {
  digitalWrite(PWMA, LOW);   // No power on Right
  digitalWrite(PWMB, LOW);   // No power on Left
}

// Function - accepts the time in milli-Seconds to go into standby for
void stopTime(int mS) {
  digitalWrite(STBY, LOW);   // Go into standby
  delay(mS);                // Wait defined time
  digitalWrite(STBY, HIGH);  // Come out of standby
}

// Function to make the car perform a 180-degree turn
void turnAround() {
  turnLeft(1000);  // Turn left for 1 second (adjust as needed)
}

// Function to move the car forward at a reduced speed for a specified duration
void moveSlowForward(int duration) {
  digitalWrite(AIN, HIGH);    // Forward direction on Right
  digitalWrite(BIN, HIGH);    // Forward direction on Left
  analogWrite(PWMA, 150);     // Reduced power on Right (adjust as needed)
  analogWrite(PWMB, 150);     // Reduced power on Left (adjust as needed)
  delay(duration);
  stopMotors();
}

// Function to create a custom movement pattern
void customMovement(int ainState, int binState, int pwmaPower, int pwmbPower, int duration) {
  digitalWrite(AIN, ainState);
  digitalWrite(BIN, binState);
  analogWrite(PWMA, pwmaPower);
  analogWrite(PWMB, pwmbPower);
  delay(duration);
  stopMotors();
}

// Main loop
void loop() {
  while (digitalRead(modeSwitch) == 1)  // Wait for mode switch to be pressed (go to 0)
    ;  // Do nothing

  delay(2000);

  moveForward(2000);         // Move forward for 2 seconds
  delay(2000);

  turnLeft(2000);            // Turn left for 2 seconds
  delay(2000);

  moveSlowForward(3000);     // Move forward at reduced speed for 3 seconds
  delay(2000);

  customMovement(HIGH, HIGH, 200, 200, 1500);  // Custom movement pattern
  delay(2000);

  stopMotors();              // Stop the car
}
