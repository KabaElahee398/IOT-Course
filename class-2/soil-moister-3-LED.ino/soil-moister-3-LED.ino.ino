// Moisture Sensor Arduino Code
// By Circuitdigest

#define sensorPin A0

// LED pins
#define led1Pin 6 // For range 0 to 400
#define led2Pin 5 // For range 401 to 700
#define led3Pin 3 // For range 701 to 1023

void setup() {
  Serial.begin(9600);
  
  // Set LED pins as output
  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);
  pinMode(led3Pin, OUTPUT);
  
  // Turn off all LEDs initially
  digitalWrite(led1Pin, LOW);
  digitalWrite(led2Pin, LOW);
  digitalWrite(led3Pin, LOW);
}

void loop() {
  int sensorValue = analogRead(sensorPin); // Read the analog value from the sensor
  Serial.print("Sensor Value: ");
  Serial.println(sensorValue);
  
  // Light up LEDs based on ranges
  if (sensorValue >= 0 && sensorValue <= 400) {
    activateLED(led1Pin); // Turn on LED 1
  } else if (sensorValue >= 401 && sensorValue <= 700) {
    activateLED(led2Pin); // Turn on LED 2
  } else if (sensorValue >= 701 && sensorValue <= 1023) {
    activateLED(led3Pin); // Turn on LED 3
  }
  
  delay(500); // Add a small delay
}

// Function to activate one LED and turn off others
void activateLED(int activeLedPin) {
  digitalWrite(led1Pin, activeLedPin == led1Pin ? HIGH : LOW);
  digitalWrite(led2Pin, activeLedPin == led2Pin ? HIGH : LOW);
  digitalWrite(led3Pin, activeLedPin == led3Pin ? HIGH : LOW);
}
