#include <Keypad.h>
#include "pitches.h"
#include "OdetoJoy.h"
#include "TheImperialMarch.h"
#include "ey_iran.h"
//#include "jingle_bells.h"
#include "mario.h"
//#include "melody.h"

int flag = 0;
float scale = 0;

const byte rowsnum = 4;
const byte colsnum = 4;
byte rowpoints[rowsnum] = {7, 6, 5, 4};
byte colpoints[colsnum] = {3, 2, 1, 0};
char keys[rowsnum][colsnum] = {
  {'7', '8', '9', '/'},
  {'4', '5', '6', '*'},
  {'1', '2', '3', '-'},
  {'o', '0', '=', '+'}
};

Keypad keypad = Keypad( makeKeymap(keys), rowpoints, colpoints, rowsnum, colsnum );


void setup() {  
  pinMode(9 , INPUT);
}

void loop() {
  char key = keypad.getKey();
  //Note Fixed , Working Perfectly
  if(key == '1'){
    //Divided to Sizeof(Int) , cause each not has int size.
    for (int thisNote = 0; thisNote < sizeof(IRmelody)/sizeof(int); thisNote++) {
      if(digitalRead(9) == HIGH){
        exit(0);
      }
      //Gives a Value Between 0-2 , Cause on 1 it gives the normal Pitch
      scale = analogRead(A0)/512.0;
      //Better Experience By Changing the note time
      int noteDuration = 400 / IRnoteDurations[thisNote];
      //Creates a Square Ware Signal with DT = 50% , with diffrent Frequency's
      tone(8, IRmelody[thisNote]*scale, noteDuration);
      //Multiply to 1.3 for better experience with Sound
      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);
    }
  }
  if(key == '2'){
    for (int thisNote = 0; thisNote < sizeof(mariomelody)/sizeof(int); thisNote++) {
      if(digitalRead(9) == HIGH){
        exit(0);
      }
      scale = analogRead(A0)/512.0;
      int noteDuration = 500 / marionoteDurations[thisNote];
      tone(8, mariomelody[thisNote]*scale, noteDuration);
      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);

    }
  }
  //Note Fixed , Working Perfectly
  if(key == '3'){
    for (int thisNote = 0; thisNote < sizeof(Odemelody)/sizeof(int); thisNote++) {
      if(digitalRead(9) == HIGH){
        exit(0);
      }
      scale = analogRead(A0)/512.0;
      int noteDuration = 500 / OdenoteDurations[thisNote];
      tone(8, Odemelody[thisNote]*scale, noteDuration);
      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);
    }
  }
  //Note Fixed , Working Perfectly
  if(key == '4'){
    for (int thisNote = 0; thisNote < sizeof(IMPmelody)/sizeof(int); thisNote++) {
      if(digitalRead(9) == HIGH){
        exit(0);
      }
      scale = analogRead(A0)/512.0;
      int noteDuration = 600 / IMPnoteDurations[thisNote];
      tone(8, IMPmelody[thisNote]*scale, noteDuration);
      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);
    }
  }
}
