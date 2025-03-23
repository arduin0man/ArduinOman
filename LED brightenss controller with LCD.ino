#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Initialize the I2C LCD display (2x16)
LiquidCrystal_I2C lcd(0x27, 16, 2); // Change the address (0x27) if necessary

int ledPin = 6; // LED connected to pin 6

void setup() {
  // Initialize the LCD display
  lcd.init();
  lcd.backlight(); // Turn on the backlight

  // Display "arduinoman.store" for 1 second
  lcd.setCursor(0, 0);
  lcd.print("arduinoman.store");
  delay(1000); // Wait for 1 second

  // Clear the display
  lcd.clear();

  // Initialize analog input pin A0
  pinMode(A0, INPUT);

  // Initialize LED pin as output
  pinMode(ledPin, OUTPUT);

  // Display initial message
  lcd.setCursor(0, 0);
  lcd.print("LED Brightness:");
}

void loop() {
  // Read the analog value from the potentiometer (0-1023)
  int sensorValue = analogRead(A0);

  // Map the sensor value to the LED brightness (0-255)
  int ledBrightness = map(sensorValue, 0, 1023, 0, 255);

  // Set the LED brightness using PWM
  analogWrite(ledPin, ledBrightness);

  // Map the sensor value to the progress bar length (0-16)
  int progress = map(sensorValue, 0, 1023, 0, 16);

  // Clear the second row of the LCD
  lcd.setCursor(0, 1);
  lcd.print("                "); // Clear the line

  // Display the progress bar on the second row
  lcd.setCursor(0, 1);
  for (int i = 0; i < progress; i++) {
    lcd.write(255); // Use block character (custom character) for the progress bar
  }

  // Optional: Add delay for better visualization
  delay(100);
}