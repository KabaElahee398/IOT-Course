#define RELAY_PIN 7   // Relay control pin
#define SWITCH_PIN 2  // Switch input pin

void setup() {
  pinMode(RELAY_PIN, OUTPUT);       // Set relay as output
  pinMode(SWITCH_PIN, INPUT_PULLUP); // Enable internal pull-up resistor
}

void loop() {
  int switchState = digitalRead(SWITCH_PIN); // Read switch state

  if (switchState == LOW) {  // If switch is pressed
    digitalWrite(RELAY_PIN, LOW);  // Turn ON relay (LED ON)
  } else {
    digitalWrite(RELAY_PIN, HIGH); // Turn OFF relay (LED OFF)
  }
}
