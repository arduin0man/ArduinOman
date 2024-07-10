// ArduinOman
//
#include <Adafruit_LiquidCrystal.h>

int t = 0;

Adafruit_LiquidCrystal lcd_1(0);

void setup()
{
  lcd_1.begin(16, 2);
}

void loop()
{
  lcd_1.setCursor(0, 0);
  lcd_1.print("hello ArduinOman");
  delay(1000); 
}