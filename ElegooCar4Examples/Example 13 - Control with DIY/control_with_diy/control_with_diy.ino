/*  
    Driving_with_DIY
    Frederick Feraco, NYS MASTER TEACHER PROGRAM, 

    Demonstrates driving with the ElegooKit App, DIY Screen.

    To assign a button, hold a button in the app
    Enter Name as "Forward"
    Enter a Message to send (this code only uses a single character enclosed in braces)
    {F} - with the braces for forward

    Enter a Message to send 
    {R} - with the braces for reverse

    Add more buttons below to control additional features

    Save your configuration in the upper right corner

    Connect on WiFi with the App, ensure UPLOAD/CAM is in CAM for control,
    Press your buttons for control.
*/

// Define IO pin
#define PWMA  5    // Controls power to the right motor
#define PWMB  6    // Controls power to the left motor
#define AIN   7    // Controls direction of the right motor, HIGH = FORWARD, LOW = REVERSE
#define BIN   8    // Controls direction of the left motor, HIGH = FORWARD, LOW = REVERSE
#define STBY  3    // Place H-Bridge in standby if LOW, Run if HIGH

// Define variables
int speedLeft = 0;  // Holds the speed of the left wheels
int speedRight = 0; // Holds the speed of the right wheels

// Initialize the car
void setup() {
  pinMode(PWMA, OUTPUT);     // Set IO pin mode OUTPUT
  pinMode(PWMB, OUTPUT);
  pinMode(BIN, OUTPUT);
  pinMode(AIN, OUTPUT);
  pinMode(STBY, OUTPUT);

  Serial.begin(9600);
  
  analogWrite(PWMA, 0);      // Fully off for the Right motor
  analogWrite(PWMB, 0);      // Fully off for the Left motor
  digitalWrite(STBY, HIGH);  // Enable Motors to run
  setSpeeds(150, 150);       // Set initial moderate speed
}

// Main loop to drive by calling functions for car functions based on the message sent
void loop() {
  delay(100);
  Serial.println("...");
  if (Serial.available()){
    char c = Serial.read();
      switch (c) {
        case 'F':     // Receive an F, drive forward
          forward();
          delay(1000);
          stop();
          break;

        case 'R':     // Receive an R, drive reverse
          reverse();
          delay(1000);
          stop();
          break;
      }
    }
}

void setSpeeds(int leftSpeed, int rightSpeed){    // Stores speeds in variables to be used when driving
  speedLeft = leftSpeed;
  speedRight = rightSpeed;  
}

void forward(){             // Drives both motors in the forward direction at set speed
  digitalWrite(AIN, HIGH);
  digitalWrite(BIN, HIGH);
  analogWrite(PWMA, speedRight);
  analogWrite(PWMB, speedLeft);
}

void reverse(){             // Drives both motors in the reverse direction at set speed
  digitalWrite(AIN, LOW);
  digitalWrite(BIN, LOW);
  analogWrite(PWMA, speedRight);
  analogWrite(PWMB, speedLeft);
}

void stop(){                // Stops drive on both motors
  analogWrite(PWMA, 0);
  analogWrite(PWMB, 0); 
}

void left(){                // Turns left with 1/2 speed on the left motor going forward
  digitalWrite(AIN, HIGH);
  digitalWrite(BIN, HIGH);
  analogWrite(PWMA, speedRight);
  analogWrite(PWMB, speedLeft / 2);
}

void right(){               // Turns right with 1/2 speed on the right motor going forward
  digitalWrite(AIN, LOW);
  digitalWrite(AIN, HIGH);
  analogWrite(PWMA, speedRight / 2);
  analogWrite(PWMB, speedLeft);    
}

void spinLeft(){            // Spins left with the right motor forward and the left in reverse
  digitalWrite(AIN, HIGH);
  digitalWrite(BIN, LOW);
  analogWrite(PWMA, speedRight);
  analogWrite(PWMB, speedLeft);
}

void spinRight(){           // Spins right with the left motor going forward and the right in reverse
  digitalWrite(AIN, LOW);
  digitalWrite(BIN, HIGH);
  analogWrite(PWMA, speedRight);
  analogWrite(PWMB, speedLeft);
}

// Function stopTime - accepts the time in milliseconds to go into standby for, returns nothing
void stopTime(int mS){
  digitalWrite(STBY, LOW);    // Go into standby
  delay(mS);                  // Wait for the defined time
  digitalWrite(STBY, HIGH);   // Come out of standby
}
