#include <Keypad.h>

const byte ledpoints[9] = {A0, A1, A2, A3, A4, A5, A6, A7, A8};
const byte rowsnum = 4;
const byte colsnum = 4;
byte rowpoints[rowsnum] = {22, 23, 24, 25};
byte colpoints[colsnum] = {26, 27, 28, 29};
char keys[rowsnum][colsnum] = {
  {'7', '8', '9', '/'},
  {'4', '5', '6', '*'},
  {'1', '2', '3', '-'},
  {'o', '0', '=', '+'}
};


Keypad keypad = Keypad( makeKeymap(keys), rowpoints, colpoints, rowsnum, colsnum );

void setup() {
  Serial.begin(9600);
  for (byte i = 0; i < 9; i++)
    pinMode(ledpoints[i], OUTPUT);
}

void loop() {
  char key = keypad.getKey();
  if (key) {
    Serial.println(key);
  }
};
