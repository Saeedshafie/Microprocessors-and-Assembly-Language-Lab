#include <Keypad.h>
#include <Servo.h>

const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'7', '8', '9', '/'},
  {'4', '5', '6', '*'},
  {'1', '2', '3', '-'},
  {'o', '0', '=', '+'}
};
byte rowPins[ROWS] = {31, 33, 35, 37};
byte colPins[COLS] = {23, 25, 27, 29};

Keypad kp = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
Servo ser;
String deg;
void setup() {
  Serial.begin(9600);
  ser.attach(9);
}

void loop() {
  char key = kp.getKey();

  if (key) {
    if (key == '=')
    {
      Serial.println();
      Serial.print(deg);
      Serial.println();
      ser.write(deg.toInt());
      deg = "";
    }
    else if (key >= '0' && key <= '9')
    {
      deg.concat(key);
      Serial.print(key);
    }
  }
}
