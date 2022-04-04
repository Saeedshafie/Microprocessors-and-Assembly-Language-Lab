#include <SPI.h>

volatile int index = 0;
volatile boolean dataEnd = false;
char data[20];
const int miso = 50, mosi = 51, sck = 52, ss = 53;

void setup() {
  Serial.begin(9600);
  Serial.println("Slave:");
  pinMode(sck, INPUT);
  pinMode(ss, INPUT_PULLUP);
  pinMode(miso, OUTPUT);
  pinMode(mosi, INPUT);
  SPCR |= _BV(SPE);
  SPI.attachInterrupt();
}

void loop() {
  if (dataEnd) {
    Serial.println(data);
    index = 0;
    dataEnd = false;
  }
}

ISR (SPI_STC_vect)
{
  byte chr = SPDR;
  if (index < sizeof data) {
    data[index++] = chr;

    if (chr == '\r') {
      dataEnd = true;
    }
  }
}
