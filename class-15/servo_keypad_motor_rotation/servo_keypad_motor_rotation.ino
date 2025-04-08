#include <Keypad.h>
#include <Servo.h> // Include the Servo library

// Keypad setup
const byte ROWS = 4; // Four rows
const byte COLS = 4; // Four columns

char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {9, 8, 7, 6}; // Connect to the row pinouts of the keypad
byte colPins[COLS] = {5, 4, 3, 2}; // Connect to the column pinouts of the keypad

// Create an object for the keypad
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// Servo setup
Servo myServo; // Create a servo object

void setup() {
  myServo.attach(10); // Attach the servo to pin 10
  Serial.begin(9600); // Start serial communication
}

void loop() {
  char key = keypad.getKey(); // Read the key from the keypad

  if (key) { // If a key is pressed
    Serial.print("Key Pressed: ");
    Serial.println(key);

    // Ensure the key is numeric before converting
    if (key >= '0' && key <= '9') {
      int k = key - '0'; // Convert char to its numeric value
      
      // Rotate the servo `k` times
      for (int i = 0; i < k; i++) {
        myServo.write(0);   // Rotate to 0°
        delay(500);         // Wait for 500ms
        myServo.write(90);  // Rotate to 90°
        delay(500);         // Wait for 500ms
        myServo.write(180); // Rotate to 180°
        delay(500);         // Wait for 500ms
      }
    } else {
      Serial.println("Non-numeric key pressed.");
    }
  }
}
