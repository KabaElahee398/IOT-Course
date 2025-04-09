const int mqPin = A0;   // Analog pin for MQ-9 sensor (AO)
const int buzzerPin = 8;
const int DO_Pin=12; // Digital pin for buzzer

// Define gas detection range (adjust based on testing)
const int LOW_THRESHOLD = 100;  // Minimum gas concentration to trigger
const int HIGH_THRESHOLD = 200; // Maximum safe level

void setup() {
    pinMode(buzzerPin, OUTPUT);
    Serial.begin(9600);
}

void loop() {
    int sensorValue = analogRead(mqPin); 
    int threshold= digitalRead(DO_Pin);

    Serial.print("threshold_value: ");

    Serial.print(threshold);                      //prints the threshold_value reached as either LOW or HIGH (above or underneath)

    Serial.print(", "); // Read analog gas concentration

    Serial.print("Sensor Value: ");
    Serial.println(sensorValue);

    // If sensor value is within the danger range, turn the buzzer ON
    if (sensorValue >= LOW_THRESHOLD && sensorValue <= HIGH_THRESHOLD) {
        digitalWrite(buzzerPin, HIGH); // Turn on buzzer
        delay(500); // Buzzer duration (adjustable)
        digitalWrite(buzzerPin, LOW);  // Turn off buzzer
    }

    delay(100); // Short delay for stability
}
