// Define the built-in LED pin
#define BUILTIN_LED LED_BUILTIN  // LED_BUILTIN is GPIO2 for most ESP8266 boards

void setup() {
  pinMode(BUILTIN_LED, OUTPUT); // Set the LED pin as an output
}

void loop() {
  digitalWrite(BUILTIN_LED, LOW);  // Turn the LED ON (LOW is ON for built-in LED)
  delay(1000);                    // Wait for 1 second
  digitalWrite(BUILTIN_LED, HIGH); // Turn the LED OFF (HIGH is OFF for built-in LED)
  delay(1000);                    // Wait for 1 second
}