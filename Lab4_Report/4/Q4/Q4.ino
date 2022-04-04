#include <Servo.h>

Servo ser;
const int potentio = A0;  // pin of potentiometer
int a; // amount of potentiometer transform
void setup() {
  ser.attach(9);
}
void loop() {
  a = analogRead(potentio);
  a = map(a, 0, 1023, 0, 180);
  ser.write(a);
  delay(10);
}
