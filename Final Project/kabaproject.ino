#include <OneWire.h>
#include <DallasTemperature.h>
#include "DHT.h"
#include <UTFT.h> 
#include <URTouch.h>

// =====================
// DS18B20 Temperature Sensor (Soil Temperature)
// =====================
#define ONE_WIRE_BUS 9   // DS18B20 Data pin
#define DS18B20_POWER A2 // A2 as power source for DS18B20

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature ds18b20(&oneWire);

// =====================
// DHT11 Temperature & Humidity Sensor
// =====================
#define DHTPIN 8    
#define DHTTYPE DHT11  
DHT dht(DHTPIN, DHTTYPE);

// =====================
// Soil Moisture Sensor
// =====================
#define MOISTURE_SENSOR A3  // Soil moisture sensor connected to A3
#define MOISTURE_POWER A1   // A1 as power source for soil moisture sensor

// =====================
// TFT Display & Touchscreen
// =====================
UTFT myGLCD(ILI9341_16, 38, 39, 40, 41);
URTouch myTouch(6, 5, 4, 3, 2);

extern uint8_t SmallFont[];
extern uint8_t BigFont[];
extern uint8_t SevenSegNumFont[];

void setup() {
  Serial.begin(9600);

  // Initialize DS18B20
  pinMode(DS18B20_POWER, OUTPUT);
  digitalWrite(DS18B20_POWER, HIGH);
  ds18b20.begin();
  Serial.println("DS18B20 Sensor Initialized");

  // Initialize DHT11
  pinMode(A0, OUTPUT);
  digitalWrite(A0, HIGH); 
  dht.begin();
  Serial.println("DHT11 Sensor Initialized");

  // Initialize Soil Moisture Sensor
  pinMode(MOISTURE_POWER, OUTPUT);
  digitalWrite(MOISTURE_POWER, HIGH);
  Serial.println("Soil Moisture Sensor Initialized");

  // Initialize TFT Display
  myGLCD.InitLCD();
  myGLCD.clrScr();
  drawHomeScreen(); // Draw UI
}

void loop() {
  // =====================
  // Read Sensor Values
  // =====================

  // Read Soil Moisture and convert it to percentage
  int moistureValue = analogRead(MOISTURE_SENSOR);
  int moisturePercent = map(moistureValue, 1023, 300, 0, 100); // Adjust range if needed

  // Read DS18B20 (Soil Temperature)
  ds18b20.requestTemperatures();
  float soilTemp = ds18b20.getTempCByIndex(0);

  // Read DHT11 Temperature & Humidity
  float humidity = dht.readHumidity();
  float airTemp = dht.readTemperature();

  // =====================
  // Print Values to Serial Monitor
  // =====================
  Serial.println("\n------ Sensor Readings ------");
  Serial.print("Soil Moisture: ");
  Serial.print(moisturePercent);
  Serial.println(" %");

  Serial.print("Soil Temperature: ");
  if (soilTemp == DEVICE_DISCONNECTED_C) {
    Serial.println("Error: DS18B20 Not Detected!");
  } else {
    Serial.print(soilTemp);
    Serial.println(" °C");
  }

  Serial.print("DHT11 Temperature: ");
  if (isnan(airTemp)) {
    Serial.println("Error: DHT11 Not Detected!");
  } else {
    Serial.print(airTemp);
    Serial.println(" °C");
  }

  Serial.print("Humidity: ");
  if (isnan(humidity)) {
    Serial.println("Error: DHT11 Not Detected!");
  } else {
    Serial.print(humidity);
    Serial.println(" %");
  }
  Serial.println("----------------------------\n");

  // =====================
  // Update Display
  // =====================
  myGLCD.setFont(BigFont);
  myGLCD.setColor(255, 255, 255); // White color
  myGLCD.setBackColor(16, 167, 103); 

  // Soil Moisture (1st Button) - With Percentage
  myGLCD.printNumI(moisturePercent, 160, 56);
  myGLCD.print("%", 195, 56); 



  // Set font for condition text
  myGLCD.setFont(SmallFont);



  myGLCD.setColor(16, 167, 103);  // Background color
  myGLCD.fillRect(215, 45, 315, 75); 
  // Check moisture level and print corresponding message
  if (moisturePercent < 30) {
      myGLCD.setColor(255, 0, 0);  // Red color for low moisture
      myGLCD.print("[LOW]", 240, 47);
      myGLCD.print("[MOISTURE!]", 220, 60);
      myGLCD.setColor(255, 255, 255); 

  } 
  else if (moisturePercent >= 30 && moisturePercent <= 70) {
      myGLCD.setColor(255, 255, 255);  // White color for good moisture
      myGLCD.print("Good!", 240, 50);
  } 
  else {
      myGLCD.setColor(255, 0, 0);  // Red color for high moisture
           myGLCD.setColor(255, 0, 0);  // Red color for low moisture
      myGLCD.print("[High]", 240, 47);
      myGLCD.print("[MOISTURE!]", 220, 60);
      myGLCD.setColor(255, 255, 255); 

  }



   myGLCD.setFont(BigFont);
   myGLCD.setColor(255, 255, 255); 










  // Soil Temperature (2nd Button) - With °C
  if (soilTemp == DEVICE_DISCONNECTED_C) {
    myGLCD.print("Err", 160, 106); 
  } else {
    myGLCD.printNumF(soilTemp, 1, 160, 106); 
    myGLCD.print("C", 225, 106);
    myGLCD.setFont(SmallFont);
    myGLCD.print("[Good!]", 250, 105);
    myGLCD.setFont(BigFont);
  }

  // Air Temperature (DHT11) (3rd Button) - With °C
  if (isnan(airTemp)) {
    myGLCD.print("Err", 160, 156); 
  } else {
    myGLCD.printNumF(airTemp, 1, 160, 156); 
    myGLCD.print("C", 225, 156);
    myGLCD.setFont(SmallFont);
    myGLCD.print("[Good!]", 250, 156);
    myGLCD.setFont(BigFont);
   

  }

  // Humidity (DHT11) (4th Button) - With Percentage
  if (isnan(humidity)) {
    myGLCD.print("Err", 160, 206); 
  } else {
    myGLCD.printNumF(humidity, 1, 160, 206); 
    myGLCD.print("%", 225, 206);
    myGLCD.setFont(SmallFont);
    myGLCD.print("[Good!]", 250, 206);
  }

  delay(2000); // Delay before next updates
}

void drawHomeScreen() {
  myGLCD.setBackColor(0, 0, 0);
  myGLCD.setColor(255, 255, 255);
  myGLCD.setFont(BigFont);
  myGLCD.print("AGRO BOT", CENTER, 10);

  myGLCD.setColor(255, 0, 0);
  myGLCD.drawLine(0, 32, 319, 32);

  myGLCD.setFont(SmallFont);
  myGLCD.setColor(10, 167, 103);
  
  // Soil Moisture (1st Button)
  myGLCD.fillRoundRect(10, 40, 310, 80);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect(10, 40, 310, 80);
  myGLCD.setBackColor(16, 167, 103);
  myGLCD.print("SOIL", 20, 46);
  myGLCD.print("MOISTURE", 17, 60);
  myGLCD.drawLine(107, 40, 107, 80);

  // Soil Temperature (2nd Button)
  myGLCD.setColor(16, 167, 103);
  myGLCD.fillRoundRect(10, 90, 310, 130);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect(10, 90, 310, 130);
  myGLCD.setBackColor(16, 167, 103);
  myGLCD.print("SOIL", 20, 96);
  myGLCD.print("TEMPERATURE", 16, 108);
  myGLCD.drawLine(107, 90, 107, 130);

  // Air Temperature (DHT11) (3rd Button)
  myGLCD.setColor(16, 167, 103);
  myGLCD.fillRoundRect(10, 140, 310, 180);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect(10, 140, 310, 180);
  myGLCD.setBackColor(16, 167, 103);
  myGLCD.print("TEMPERATURE", 16, 156);
  myGLCD.drawLine(107, 140, 107, 180);

  // Humidity (DHT11) (4th Button)
  myGLCD.setColor(16, 167, 103);
  myGLCD.fillRoundRect(10, 190, 310, 230);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect(10, 190, 310, 230);
  myGLCD.setBackColor(16, 167, 103);
  myGLCD.print("HUMIDITY", 26, 202);
  myGLCD.drawLine(107, 190, 107, 230);
}