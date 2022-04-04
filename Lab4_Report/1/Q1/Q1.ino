#include <Servo.h>

int angle = 0; // servo angle
Servo ser;
void setup() {
  ser.attach(9);
}
void loop() {
  for (angle = 0; angle <= 180; angle += 1) {
    ser.write(angle);
    delay(10);
  }
  for (angle = 180; angle>= 0; angle-= 1) {
    ser.write(angle);
    delay(10);
  }
}
