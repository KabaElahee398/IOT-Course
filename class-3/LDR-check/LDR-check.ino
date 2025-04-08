int ldrPin = A0; // Analog pin connected to LDR
int ldrValue = 0; // Variable to store LDR reading

void setup() {
  Serial.begin(9600); // Start serial communication
}

void loop() {
  ldrValue = analogRead(ldrPin); // Read the value from LDR
  Serial.print("LDR Value: ");
  Serial.println(ldrValue); // Print the value to the Serial Monitor
  
  delay(500); // Delay for stability
}
