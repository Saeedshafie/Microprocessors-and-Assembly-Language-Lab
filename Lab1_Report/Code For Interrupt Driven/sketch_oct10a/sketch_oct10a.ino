volatile boolean state1 = false;
volatile boolean state2 = false;
volatile boolean state3 = false;

void setup() {
  // put your setup code here, to run once:
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(18, INPUT_PULLUP);
  pinMode(19, INPUT_PULLUP);
  pinMode(20, INPUT_PULLUP);
  attachInterrupt(18, buttonPressed1, CHANGE);
  attachInterrupt(19, buttonPressed2, CHANGE);
  attachInterrupt(20, buttonPressed3, CHANGE);

}

void loop() {
  // put your main code here, to run repeatedly:
  if (state1 == true) {
    for (int i = 1 ; i < 7 ; i++) {
      digitalWrite(7 - i , HIGH);
      delay(500);
    }
    //state1 = !state1;
  }
  if (state2 == true) {

    int a = strlen("Saeed");

    for (int i = 0 ; i < 3 ; i++) {
      for (int j = 0 ; j < a ; j++) {
        digitalWrite(6 - j , HIGH);
      }
      delay(500);
      for (int i = 0 ; i < a ; i++) {
        digitalWrite(6 - i , LOW);
      }
      delay(500);
      for (int i = 0 ; i < a ; i++) {
        digitalWrite(6 - i , HIGH);
      }
    }
    //state2 = !state2;
  }

  if (state3 == true) {
    for (int i = 1 ; i < 7 ; i++) {
      digitalWrite(i , LOW);
    }
    //state3 = !state3;
  }
}
void buttonPressed1() {
  state1 = !state1;

}
void buttonPressed2(){
  state2 = !state2;
 

}
void buttonPressed3() {
  state3 = !state3;
}
