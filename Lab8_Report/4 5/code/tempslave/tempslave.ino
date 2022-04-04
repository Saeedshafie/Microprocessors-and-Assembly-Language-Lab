#include <SPI.h>

int data;
volatile boolean endData = false;
const int miso = 50, mosi = 51, sck = 52, ss = 53;
void setup() {
  Serial.begin(9600);
  Serial.println("Temp Slave:");
  pinMode(ss, INPUT_PULLUP);
  pinMode(miso, OUTPUT);
  pinMode(mosi, INPUT);
  pinMode(sck, INPUT);
  SPCR |= _BV(SPE);
  SPI.attachInterrupt();
}
void loop() {
  if (endData) {
    Serial.print("temp: ");
    Serial.println(data);
    endData = false;
  }
}
ISR (SPI_STC_vect)
{
  byte n = SPDR;
  data = (uint8_t)n;
  endData = true;
}
