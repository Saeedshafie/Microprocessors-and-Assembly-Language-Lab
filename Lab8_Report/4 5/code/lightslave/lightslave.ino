
#include <SPI.h>

int data;
volatile boolean endData = false;
const int miso = 50, mosi = 51, sck = 52, ss = 53;

void setup() {
  Serial.begin(9600);
  Serial.println("Light Slave:");
  pinMode(ss, INPUT_PULLUP);
  pinMode(mosi, INPUT);
  pinMode(miso, OUTPUT);
  pinMode(sck, INPUT);
  SPCR |= _BV(SPE);
  SPI.attachInterrupt();
}

void loop() {
  if (endData) {
    Serial.print("light: ");
    Serial.print(data);
    Serial.println("%");
    endData = false;
  }
}

ISR (SPI_STC_vect)
{
  byte n = SPDR;
  data = (uint8_t)n;
  endData = true;
}
