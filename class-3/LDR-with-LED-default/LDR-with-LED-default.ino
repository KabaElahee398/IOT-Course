int ldrPin = A0; // Analog pin connected to LDR
int ledPin = 9;  // Digital pin connected to LED
int ldrValue = 0; // Variable to store LDR reading
int threshold = 800; // Set threshold for light level (adjust based on your setup)

void setup() {
  pinMode(ledPin, OUTPUT); // Set LED pin as output
  Serial.begin(9600);      // Start serial communication
}

void loop() {
  ldrValue = analogRead(ldrPin); // Read LDR value
  Serial.print("LDR Value: ");
  Serial.println(ldrValue); // Print LDR value to Serial Monitor

  if (ldrValue < threshold) {
    digitalWrite(ledPin, HIGH); // Turn LED on in the dark
  } else {
    digitalWrite(ledPin, LOW);  // Turn LED off in bright light
  }

  delay(500); // Delay for stability
}
