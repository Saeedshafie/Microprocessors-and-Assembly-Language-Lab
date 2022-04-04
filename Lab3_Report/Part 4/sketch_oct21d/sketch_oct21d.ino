#include <LiquidCrystal.h>

const int rs = 13, en = 12, d4 = 8, d5 = 9, d6 = 10, d7 = 11;

LiquidCrystal LCD(rs, en, d4, d5, d6, d7);

byte col = 0;
byte row = 0;
void setup() {
  LCD.begin(16, 2);
  LCD.clear();
}

void loop() {
  LCD.clear();
  LCD.setCursor(col, row);
  LCD.print("A");

  col++;
  row = 1 - row;
  if (col == 15)
  {
    col = 0;
    //row = 1 - row;
  }
  delay(200);
}
