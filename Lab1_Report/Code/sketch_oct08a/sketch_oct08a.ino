
int button1 = 12;
int button2 = 11;
int button3 = 10;

void setup() {
  // put your setup code here, to run once:
  pinMode(6, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(1, OUTPUT);
  pinMode(11, INPUT_PULLUP);
  pinMode(12, INPUT_PULLUP);
  pinMode(10, INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:



  if (digitalRead(button1)==false) {
    for (int i = 1 ; i < 7 ; i++) {
      digitalWrite(7 - i , HIGH);
      delay(500);
    }
  }
  if (digitalRead(button2)==false) {

    int a = strlen("Saeed");

    for (int i = 0 ; i < 3 ; i++) {
      for (int i = 0 ; i < a ; i++) {
        digitalWrite(6 - i , HIGH);
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
    digitalWrite(button2 , HIGH);
  } while (digitalRead(button2)==false);

  if (digitalRead(button3)==false) {
    for (int i = 1 ; i < 7 ; i++) {
      digitalWrite(i , LOW);
    }
  }

}
