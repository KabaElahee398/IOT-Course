#include <Keypad.h>

const byte ROWS = 4; // four rows
const byte COLS = 4; // four columns

char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {9, 8, 7, 6}; // connect to the row pinouts of the keypad
byte colPins[COLS] = {5, 4, 3, 2}; // connect to the column pinouts of the keypad

// Create an object of Keypad
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

String input = "";       // To store the sequence of keys pressed
const String password = "1320"; // Correct password

void setup() {
  Serial.begin(9600);
  Serial.println("Please enter the password and press '#' to submit:");
}

void loop() {
  char key = keypad.getKey(); // Read the key
  
  if (key) { // If a key is pressed
    if (key == '#') { // When '#' is pressed, validate the input
      if (input == password) {
       Serial.print("\n");
        Serial.println("Access Granted!");
      } else {
        Serial.print("\n");
        Serial.println("Error: Wrong Password");
      }
      // Reset the input and prompt the user again
      input = "";
      Serial.println("Please enter the password and press '#' to submit:");
    } else if (key == '*') { // Clear input when '*' is pressed
      input = "";
      Serial.println("Input cleared. Please enter the password and press '#' to submit:");
    } else { // Append the key to the input
      input += key;
     // Serial.print("Key Pressed: ");
      Serial.print(key);
    }
  }
}
