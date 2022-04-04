#include <LiquidCrystal.h>
#include <Keypad.h>

const byte rowsnum = 4;
const byte colsnum = 4;

char KEYS[rowsnum][colsnum] = {
  {'7','8','9','/'},
  {'4','5','6','*'},
  {'1','2','3','-'},
  {'C','0','=','+'}
};

byte colPoints[colsnum] = {23, 25, 27, 29};
byte rowPoints[rowsnum] = {31, 33, 35, 37};

const int rs = 13;
const int en = 12;
const int D4 = 8, D5 = 9, D6 = 10, D7 = 11;

Keypad pad = Keypad( makeKeymap(KEYS), rowPoints, colPoints, rowsnum, colsnum );
LiquidCrystal LCD(rs, en, D4, D5, D6, D7);

const String Password = "9";
String inputpass;
int col = 0;

void setup(){
  Serial.begin(9600);
  LCD.begin(16,2);
  LCD.clear();
  LCD.setCursor(col,0);
  
}

void loop() {
  LCD.setCursor(col, 0);
  char key = pad.getKey();
  if(key){
    if (key == 'C'){
      LCD.clear();
      LCD.setCursor(0,0);
      col = 0;
      inputpass = "";
    }
    else{
      if (key != '*'){
        inputpass.concat(key);
        Serial.println(key);
        LCD.print(key);
        col++;
      }
      else{
          LCD.setCursor(0, 1);
          if (inputpass == Password) {
            LCD.print("Correct password");
          } else {
            LCD.print("Wrong password");
            }
          }
      }
    }
  }
