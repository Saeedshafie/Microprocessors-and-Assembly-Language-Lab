#define LED6 6
#define LED5 5
#define LED4 4
#define LED3 3
#define LED2 2
#define LED1 1
#define BUTTON1 18
#define BUTTON2 19
#define BUTTON3 20

void setup() {
  // put your setup code here, to run once:
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(LED5, OUTPUT);
  pinMode(LED6, OUTPUT);
  pinMode(BUTTON1, INPUT);
  pinMode(BUTTON2, INPUT);
  pinMode(BUTTON3, INPUT);

  attachInterrupt(digitalPinToInterrupt(BUTTON1), BUTTON1_PRESSED, CHANGE);
  attachInterrupt(digitalPinToInterrupt(BUTTON2), BUTTON2_PRESSED, FALLING);
  attachInterrupt(digitalPinToInterrupt(BUTTON3), BUTTON3_PRESSED, CHANGE);
}

void loop() {
  // put your main code here, to run repeatedly:

}

void BUTTON1_PRESSED(){
    for (int i = 1 ; i < 7 ; i++) {
      digitalWrite(7 - i , HIGH);
      delay(90000);
    }
}

void BUTTON2_PRESSED(){
    int a = strlen("Saeed");

    for (int i = 0 ; i < 3 ; i++) {
      for (int j = 0 ; j < a ; j++) {
        digitalWrite(6 - j , HIGH);
      }
      delay(90000);
      for (int i = 0 ; i < a ; i++) {
        digitalWrite(6 - i , LOW);
      }
      delay(90000);
      for (int i = 0 ; i < a ; i++) {
        digitalWrite(6 - i , HIGH);
      }
    }
  
}

void BUTTON3_PRESSED(){
    for (int i = 1 ; i < 7 ; i++) {
      digitalWrite(i , LOW);
    }
}
