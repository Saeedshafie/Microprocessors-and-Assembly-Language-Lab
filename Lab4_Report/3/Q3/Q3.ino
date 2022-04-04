#include <Servo.h>

Servo ser;
String deg;
void setup() {
  Serial.begin(9600);
  ser.attach(9);
}
void loop() {
  if (Serial.available() > 0) {
    char in = Serial.read();
    if (in == 13) {
      ser.write(deg.toInt());
      Serial.println();
      deg = "";
    } else {
      Serial.print(in);
      deg += in;
    }
  }
}
