const byte ledpoints[9] = {A0, A1, A2, A3, A4, A5, A6, A7, A8};

void setup() {
  Serial.begin(9600);
  for (byte i = 0; i < 9; i++)
    pinMode(ledpoints[i], OUTPUT);
}

void loop() {
  if (Serial.available() > 0) {
   int var = Serial.parseInt();
    if (var > 9) {
      Serial.println("invalid number");
    } else {
      for (int i = 0; i < var; i++) {
        digitalWrite(ledpoints[i], HIGH);
      }
    }
  }
};
