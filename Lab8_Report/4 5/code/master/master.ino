
#include <SPI.h>

const int slave1 = 44, slave2 = 45, temp = A8, light = A9;

int anal;
uint8_t analogMap;

void setup() {
  Serial.begin(9600);
  Serial.println("Master:");
  pinMode(slave1, OUTPUT);
  digitalWrite(slave1, HIGH);
  pinMode(slave2, OUTPUT);
  digitalWrite(slave2, HIGH);
  pinMode(temp, INPUT);
  pinMode(light, INPUT);
  SPI.begin();
}

void loop() {
  delay(1000);
  anal = analogRead(light);
  analogMap = map(anal, 0, 1023, 0, 100);
  digitalWrite(slave1, LOW);
  SPI.transfer (analogMap);
  Serial.print("light: ");
  Serial.print(analogMap);
  Serial.println("%");
  delay(5);
  digitalWrite(slave1, HIGH);
  delay(1000);
  anal = analogRead(temp);
  analogMap = map(anal, 0, 306, 0, 150);
  digitalWrite(slave2, LOW);
  SPI.transfer (analogMap);
  Serial.print("temp: ");
  Serial.print(analogMap);
  delay(5);
  digitalWrite(slave2, HIGH);
  Serial.println();
}
