#include "bitmap7x11.h"
//OutPut0 of all shift registers is connected to first row leds and so one
//So We Need 8 Shift Register
//                   
#define OUTPUT_1 21 
#define OUTPUT_2 20
#define OUTPUT_3 19 
#define OUTPUT_4 18 
#define OUTPUT_5 17 
#define OUTPUT_6 16 
#define OUTPUT_7 15 


String input_string ;
int ports[7] = {OUTPUT_1, OUTPUT_2, OUTPUT_3, OUTPUT_4, OUTPUT_5, OUTPUT_6, OUTPUT_7}; // Shows a single row 

void setup() {
  Serial.begin(9600); // opens serial port, sets data rate to 9600 bps
  for (int i = 0; i < 7; i++)
    pinMode(ports[i], OUTPUT);
  Serial.setTimeout(2000);
}

void loop() {
  if (Serial.available() > 0) {
    //Serial.println("Enter A Unicode:\n");
    input_string = Serial.readStringUntil('\n'); // read the incoming String:
    Serial.println("User Input: " + input_string);
    for (int i = 0; i < input_string.length(); i++){
      char character = input_string[i];
      int ascii = int(character);
      if (ascii - 33 >= 0){
        Serial.print(character);
        Serial.println(" (" + String(ascii) + ") :");
        activate_leds(ascii - 33); // because in "bitmap7x11" the first 33 ascii characters are not implemented
        Serial.println("-------");
      }
      
    }
    // clear the LEDs for the last line
    for (int j = 6; j >= 0 ; j--)
      digitalWrite(ports[j], LOW);
  }
}

// sending a character to the LEDs
void activate_leds(int index){
  for (int i = 10; i >= 0 ; i--){ // For Better View Print from bottom to top
    for (int j = 0; j < 7 ; j++){
      if (bitmap[index][7 * i + j] == 0){ // the LED is going to be deactive if FALSE
        digitalWrite(ports[j], LOW); // 7 Led's Get Data , then goes to next row
        Serial.print(" ");  
      }else{
        digitalWrite(ports[j], HIGH); // the LED is going to be active if TRUE
        Serial.print("*");
      }
    } // inner for loop
    Serial.println(); // Go to new Line for Next Line
    delay(500); // waiting 0.5 s for showing the next row on the LEDs
  } // outer for loop
}
