#define RELAY_PIN 7  // Define the pin connected to the relay

void setup() {
  pinMode(RELAY_PIN, OUTPUT);  // Set relay pin as output
  digitalWrite(RELAY_PIN, LOW);  // Activate relay (turn LED ON)
}

void loop() {
  // No loop action needed as LED stays ON
}
