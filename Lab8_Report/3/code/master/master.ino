#include <SPI.h>

#define DATA1 " Hello Mohammad\r"
#define DATA2 "Mohammad\r"
const int slave1 = 44, slave2 = 45;

void dataTransform(const char *data) {
  for (const char *i = data ; char ch = *i; i++) {
    SPI.transfer(ch);
    Serial.print(ch);
    delay(5);
  }
  Serial.println();
}

void setup() {
  Serial.begin(9600);
  Serial.println("Master:");
  pinMode(slave1, OUTPUT);
  digitalWrite(slave1, HIGH);
  pinMode(slave2, OUTPUT);
  digitalWrite(slave2, HIGH);
  SPI.begin();
}
void loop() {
  digitalWrite(slave2, LOW);
  dataTransform(DATA2);
  digitalWrite(slave2, HIGH);
  delay(1000);
  digitalWrite(slave1, LOW);
  dataTransform(DATA1);
  digitalWrite(slave1, HIGH);
  delay(1000);
}
