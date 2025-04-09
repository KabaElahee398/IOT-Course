#define RELAY_PIN 7   // Relay control pin
#define SWITCH_PIN 2  // Switch input pin

bool ledState = false;  // Stores LED state (ON/OFF)
bool lastButtonState = HIGH; // Stores last button state

void setup() {
  pinMode(RELAY_PIN, OUTPUT);       
  pinMode(SWITCH_PIN, INPUT_PULLUP); // Enable internal pull-up resistor
}

void loop() {
  bool buttonState = digitalRead(SWITCH_PIN); // Read switch state

  // Detect button press (LOW) and state change
  if (buttonState == LOW && lastButtonState == HIGH) {
    ledState = !ledState;  // Toggle LED state
    digitalWrite(RELAY_PIN, ledState ? LOW : HIGH); // Control relay
    delay(200);  // Debounce delay
  }

  lastButtonState = buttonState;  // Update last button state
}
