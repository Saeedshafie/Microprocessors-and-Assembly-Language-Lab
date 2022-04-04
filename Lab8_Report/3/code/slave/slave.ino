#include <SPI.h>

volatile int index = 0;
volatile boolean endData = false;
char data[30];
const int miso = 50, mosi = 51, sck = 52, ss = 53;

void setup() {
  Serial.begin(9600);
  Serial.println("Slave:");
  pinMode(miso, INPUT);
  pinMode(mosi, OUTPUT);
  pinMode(sck, INPUT);
  pinMode(ss, INPUT_PULLUP);
  SPCR |= _BV(SPE);
  SPI.attachInterrupt();
}

void loop() {
  if (endData) {
    Serial.println(data);
    index = 0;
    endData = false;
  }
}

ISR (SPI_STC_vect)
{
  byte ch = SPDR;
  if (index < sizeof data) {
    data[index++] = ch;

    if (ch == '\r') {
      endData = true;
    }
  }
}
