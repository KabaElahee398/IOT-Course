#define PW_PIN 6 // Pin connected to PW output
long duration;
float distance;

void setup() {
  Serial.begin(9600); // Start Serial Monitor
  pinMode(PW_PIN, INPUT);
}

void loop() {
  duration = pulseIn(PW_PIN, HIGH); // Read pulse width
  distance = duration / 147.0;     // Convert pulse width to distance (in inches)
  
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" inches");

  delay(100); // Wait 100ms for stability
}
