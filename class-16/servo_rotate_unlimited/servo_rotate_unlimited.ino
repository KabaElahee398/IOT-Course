#include <Servo.h>

// Create a Servo object
Servo myServo;

// Define the PWM pin
const int servoPin = 10;

void setup() {
  // Attach the servo to the specified pin
  myServo.attach(servoPin);
  Serial.begin(9600);
}

void loop() {
  // Rotate the servo to 0 degrees
  myServo.write(0);
  Serial.println("Servo at 0 degrees");
  delay(1000); // Wait for 1 second

  // Rotate the servo to 90 degrees
  myServo.write(90);
  Serial.println("Servo at 90 degrees");
  delay(1000); // Wait for 1 second

  // Rotate the servo to 180 degrees
  myServo.write(180);
  Serial.println("Servo at 180 degrees");
  delay(1000); // Wait for 1 second
}
