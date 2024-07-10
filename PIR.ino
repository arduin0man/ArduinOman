// ArduinOman
int n = 0;

void setup()
{
  pinMode(8, INPUT);
  pinMode(13, OUTPUT);
}

void loop()
{
  n = digitalRead(8);
  if (n == 1) {
    digitalWrite(13, HIGH);
  } else {
    digitalWrite(13, LOW);
  }
}