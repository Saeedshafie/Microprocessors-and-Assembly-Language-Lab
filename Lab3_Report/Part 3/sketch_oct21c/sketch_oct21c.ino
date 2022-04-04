#include <LiquidCrystal.h>
#include <Keypad.h>

const byte ROWS = 4; 
const byte COLS = 4; 
char keys[ROWS][COLS] = {
  {'7','8','9', '/'},
  {'4','5','6', '*'},
  {'1','2','3', '-'},
  {'C','0','=', '+'}
};
byte rowPins[ROWS] = {31, 33, 35, 37}; 
byte colPins[COLS] = {23, 25, 27, 29};

const int rs = 13; 
const int en = 12;
const int D4 = 8, D5 = 9, D6 = 10, D7 = 11;


Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
LiquidCrystal LCD(rs, en, D4, D5, D6, D7);

String op1,op2;
String result;
char operatorEntered;
boolean flag = false;


void setup() {
  Serial.begin(9600);
  LCD.begin(16, 2);
  LCD.print("Calculator");
  delay(1000);
  LCD.clear();
  LCD.setCursor(0, 0);
  
}

void loop() {

  char key = keypad.getKey();
  
  if (key){
    LCD.print(key);

    if (key == 'C')
    {
      op1 = "";
      op2 = "";
      flag = false;
      LCD.clear();
      LCD.setCursor(0,0);
    }
    else if ( !flag && (key == '+' || key == '-' || key == '*' || key == '/'))
    {
      operatorEntered = key;
      flag = true;
    }
    else if (key == '=')
    {
      LCD.setCursor(0,1);
      int A = op1.toInt();
      int B = op2.toInt();
      
      switch (operatorEntered)
      {

        case '+':
          LCD.print(A + B);
          break;
       case '-':
          LCD.print(A - B);
          break;
       case '*':
          LCD.print(A * B);
          break;
       case '/':
          LCD.print(A / B);
          break;
      }
    }
    else if (flag == false)
    {
      op1.concat(key);
    }
    else
    {
      op2.concat(key);
    }
  }
    
}
