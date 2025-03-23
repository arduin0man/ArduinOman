#include "U8glib.h"

U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_DEV_0 | U8G_I2C_OPT_NO_ACK | U8G_I2C_OPT_FAST); // Fast I2C / TWI

int progress = 0;
int ledPin = 6; // LED connected to pin 6

void setup() {
  // Initialize the OLED display
  u8g.setFont(u8g_font_tpssb);
  u8g.setColorIndex(1);
  
  // Initialize analog input pin A0
  pinMode(A0, INPUT);
  
  // Initialize LED pin as output
  pinMode(ledPin, OUTPUT);

  // Show startup screen
  showStartupScreen();
}

void loop() {
  // Read the analog value from the potentiometer (0-1023)
  int sensorValue = analogRead(A0);
  
  // Map the sensor value to the progress bar width (0-108)
  progress = map(sensorValue, 0, 1023, 0, 108);
  
  // Ensure progress stays within valid range
  if (progress < 0) progress = 0;
  if (progress > 108) progress = 108;

  // Map the sensor value to the LED brightness (0-255)
  int ledBrightness = map(sensorValue, 0, 1023, 0, 255);
  
  // Set the LED brightness using PWM
  analogWrite(ledPin, ledBrightness);

  // Clear the display
  u8g.firstPage();
  do {
    // Draw the progress bar title
    u8g.drawStr(25, 44, "LED Brightness");
    u8g.drawStr(15, 63, "arduinoman.store");
    // Draw the progress bar frame
    u8g.drawFrame(0, 10, 128, 20);
    // Draw the progress box
    u8g.drawBox(10, 15, progress, 10);
  } while (u8g.nextPage());
  
  // Optional: Add delay for better visualization
  delay(50);
}

void showStartupScreen() {
  u8g.firstPage();
  do {
    // Set font and draw the startup text
    u8g.setFont(u8g_font_tpssb);
    u8g.drawStr(25, 32, "arduino.store");
  } while (u8g.nextPage());
  
  // Display the startup screen for 1 second
  delay(1000);
}