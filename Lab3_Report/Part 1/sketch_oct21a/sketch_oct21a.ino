#include <LiquidCrystal.h>

const int rs = 13;
const int en = 12;
const int D4 = 8, D5 = 9, D6 = 10, D7 = 11;


int col = 0;
int row = 0;

LiquidCrystal LCD(rs, en, D4, D5, D6, D7);


void setup() {

 
  LCD.begin(16,2);
  LCD.clear();
}

void loop() {
  LCD.clear();
  LCD.setCursor(col,row);
  LCD.print("Saeed");
  col = col + 1;

  if (col == (16 - strlen("Saeed")) + 1)
  {
    col = 0;
    if(row == 0){
      row = row + 1;  
    }
    else{
      row = 0;
    }
  }

  
  delay(200);
}
  
