#include <Keypad.h>
#include <LiquidCrystal.h>
#include <Servo.h>
#include <stdlib.h>
#include <string.h>

#define PASSWORD "9831020"
#define LED_PIN 6
#define SERVO_PIN 7

Servo main_servo;
Servo childs[2];

const byte ROWS = 4; 
const byte COLS = 4; 
char keys[ROWS][COLS] = {
  {'7','8','9', '/'},
  {'4','5','6', '*'},
  {'1','2','3', '-'},
  {'R','0','=', '+'}
};
byte rowPins[ROWS] = {22, 23, 24, 25}; 
byte colPins[COLS] = {26, 27, 28, 29}; 
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

const int rs = 13, en = 12, d4 = 11, d5 = 10, d6 = 9, d7 = 8;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

String pass = "";
int request = 0;  // 0 means not ready for accepting request, 1 means ready for accepting request.
int door = 0; // 0 means is close, 1 means is open.

void setup(){
  pinMode(LED_PIN, OUTPUT);
  for (int i = 0; i < 2; i++){
    pinMode(4 - 2 * i, OUTPUT);
  }
  
  // attach servos and initialize them to 0 degree
  main_servo.attach(SERVO_PIN);
  main_servo.write(0);
  for (int i = 0; i < 2; i++){
    childs[i].attach(5 - 2 * i);
    childs[i].write(0);
  }
  
  lcd.begin(16, 2);
  lcd.print("password: ");
  lcd.setCursor(0, 1);
  keypad.addEventListener(keypadEvent);
  Serial.begin(9600);
}

void turn_on_and_off_LEDs(int sign){
    for (int i = 0; i < 2; i++){
      if (sign == 1){
        // turn on all lights
        digitalWrite(4 - 2 * i, HIGH);
      }
      else{
        // turn off all lights
        digitalWrite(4 - 2 * i, LOW);
      }
    }
}

void ResetSystem(){
    pass = "";
    door = 0;
    request = 0;
    lcd.clear();
    main_servo.write(0);
    for (int i = 0; i < 2; i++)
       childs[i].write(0);
    digitalWrite(LED_PIN, LOW);
    turn_on_and_off_LEDs(0);
    lcd.print("password: ");
    lcd.setCursor(0, 1);  
}

void setFoodID(){
  switch (pass.toInt()){
    case 11:
      lcd.print("milk");
      main_servo.write(90);
      break;
    case 12:
      lcd.print("chocolate cake");
      childs[0].write(90);
      break; 
    case 13:
      lcd.print("napkin");
      childs[1].write(90);
      break;  
    default:
      lcd.print("wrong number");  
      delay(500);
      lcd.clear();
      lcd.setCursor(0, 0);
      pass = "";
      // request = 1;
      //lcd.print("Enter number between 11 and 13"); 
      //lcd.setCursor(0, 1);
      break;
  }
  
  
}

void closeTheDoor(){
    main_servo.write(0); 
    for (int i = 0; i < 2; i++)
       childs[i].write(0);
    door = 0;
    request = 1;
    String foodNumber = "";
    digitalWrite(LED_PIN,HIGH);
    turn_on_and_off_LEDs(1);
    lcd.clear();
    pass = "";
    lcd.print("food id :");
    lcd.setCursor(0, 1);
}

void checkPassword(){
  if (pass == PASSWORD){
                lcd.print("correct");
                delay(500);
                lcd.clear();
                pass = "";
                lcd.print("door is open now");
                // opening door with servo motor.
                main_servo.write(90);
                for (int i = 0; i < 2; i++)
                  childs[i].write(90);    
                door = 1;
                delay(600);
                lcd.clear();
                lcd.print("press + to close");
  }
  else {
                lcd.print("incorrect");
                delay(500);
                lcd.clear();
                lcd.print("please retry");
                delay(500);
                lcd.clear();
                pass = "";
                lcd.print("password :");
                lcd.setCursor(0, 1);
   }  
}
void checkRequest(){
  if (request == 0) {
      checkPassword();
  }
  else {
      // lcd.print(pass);
      // main_servo.write(90); //opening door with servo motor and serving food.
      setFoodID();
      pass = "";
      delay(900);
      lcd.clear();
      lcd.print("press ON/C for");
      lcd.setCursor(0, 1);
      lcd.print("new request");
  }
}

void loop(){
  
  char key = keypad.getKey();
}

void keypadEvent(KeypadEvent key){
    switch (keypad.getState()){
    case PRESSED:
    
        lcd.print(key);
        if (key == 'R') {
          // reset system
          ResetSystem();
        } 
        else if (key == '+' && door == 1) {
          //closing with servo motor
          closeTheDoor();
        } 
        else if (key == '-') {
          int length = pass.length();
          pass = pass.substring(0, length - 1);
          lcd.setCursor(length - 1, 1);
          lcd.print("  ");
          lcd.setCursor(length - 1, 1);
        } 
        else if (key == '*') {
          lcd.clear();
          lcd.setCursor(0, 0);
          checkRequest();
        }
        else {
          pass += key;  
        }
        break;
    }

}
