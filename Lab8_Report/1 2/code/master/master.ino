#include <SPI.h>
#define DATA "Hassannejadi9831020\r"
const int ss = 46;
void setup() {
  Serial.begin(9600);
  Serial.println("Master:");
  pinMode(ss, OUTPUT);
  digitalWrite(ss, HIGH);  
  SPI.begin();
}
void loop() {
  digitalWrite(ss, LOW);
  delay(10);
  for (const char *i = DATA ; char ch = *i; i++) {
    SPI.transfer(ch);
    Serial.print(ch);
    delay(5);
  }
  Serial.println();
  digitalWrite(ss, HIGH);
  delay(1000);
}
