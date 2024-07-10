// ArduinOman
//
#include <Adafruit_LiquidCrystal.h>

int t = 0;

Adafruit_LiquidCrystal lcd_1(0);

long readUltrasonicDistance(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT);  // Clear the trigger
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  // Sets the trigger pin to HIGH state for 10 microseconds
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  // Reads the echo pin, and returns the sound wave travel time in microseconds
  return pulseIn(echoPin, HIGH);
}

void setup()
{
  lcd_1.begin(16, 2);
}

void loop()
{
  t = 0.01723 * readUltrasonicDistance(0, 1);
  lcd_1.setCursor(0, 0);
  lcd_1.print("Distance=");
  lcd_1.setCursor(9, 0);
  lcd_1.print(t);
  lcd_1.setCursor(12, 0);
  lcd_1.print("cm");
}