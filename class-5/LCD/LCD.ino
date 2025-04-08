#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Initialize LCD (Adjust the I2C address if needed)
LiquidCrystal_I2C lcd(0x27, 16, 2);

// LM35 temperature sensor pin
const int lm35_pin = A1;

void setup() {
  // Initialize Serial communication
  Serial.begin(9600);
  while (!Serial); // Wait for Serial Monitor (useful for Leonardo)

  // Initialize LCD
  lcd.init();
  lcd.backlight();
  lcd.clear();

  // Display initializing message
  lcd.setCursor(0, 0);
  lcd.print("Initializing...");
  delay(2000);

  lcd.clear();
}

void loop() {
  static unsigned long previousMillis = 0;
  static int scrollIndex = 0;
  const unsigned long scrollInterval = 150; // Adjust scroll speed
  const char* names = "Abu_Said   Palash   Runa   Jhuma Nova Jui  ";

  // Display temperature on the first line
  int temp_adc_val = analogRead(lm35_pin);  // Read LM35 output
  float temp_val = (temp_adc_val * 4.88) / 10.0;  // Convert ADC to °C
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temp_val);
  lcd.print(" C   "); // Clear leftover characters
   delay(2000);

  // Scroll names on the second line
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= scrollInterval) {
    previousMillis = currentMillis;

    // Scroll names by printing a substring of the names array
    lcd.setCursor(0, 1); // Set cursor to the second line
    for (int i = 0; i < 16; i++) {
      lcd.print(names[(scrollIndex + i) % strlen(names)]);
    }

    // Increment scroll index
    scrollIndex++;
    if (scrollIndex >= strlen(names)) {
      scrollIndex = 0; // Reset scrolling when the end is reached
    }
  }
}
