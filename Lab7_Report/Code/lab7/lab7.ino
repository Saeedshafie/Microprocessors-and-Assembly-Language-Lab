#include <LiquidCrystal.h>
#include <Keypad.h>
#include <Wire.h>

#define ADRS_MICRO 0b1010000
#define ADRS_EEPROM_SAVE  50

char keys[4][4] = {
  {'7', '8', '9', '/'},
  {'4', '5', '6', '*'},
  {'1', '2', '3', '-'},
  {'o', '0', '=', '+'}
};
byte rowPins[4] = {31, 33, 35, 37}; 
byte colPins[4] = {23, 25, 27, 29}; 
Keypad kp = Keypad( makeKeymap(keys), rowPins, colPins, 4, 4 );
LiquidCrystal lcd(13, 12, 8, 9, 10, 11);
const byte ledPins[4] = {53, 52, 51, 50};
String inp;
enum Status {workless, setting, work, stopped, finish} status = workless;
String states[] = {"workless", "Time Set ", " mode", "stopped", "finish"};
uint8_t modesTimes[4] = {1, 2, 1, 2};
int timerTime = modesTimes[0];
byte curMode = 0; 
byte changeTimeMode = 0;
bool showTimer = false;
float remainingTime;
long startTime = millis();
long lastSave = millis();

void printStatus(String mode = "") {
  lcd.clear();
  lcd.setCursor(0, 0);
  String modeTitle = "";
  switch (mode.toInt())
  {
  case 1:
      modeTitle="PreWash ";
      break;
  case 2:
      modeTitle="Wash ";
      break;
  case 3:
      modeTitle="WaterWash ";
      break;
  case 4:
      modeTitle="Dry ";
      break;
  }
  lcd.print(modeTitle + states[status]);
  inp = "";
}

void writeMem(uint16_t memAdrs, uint8_t* data, int sz) {
  Wire.beginTransmission(ADRS_MICRO);
  Wire.write((uint8_t)((memAdrs & 0xFF00) >> 8));
  Wire.write((uint8_t)((memAdrs & 0x00FF) >> 0));
  for (int i = 0; i < sz; i++) {
    Wire.write(data[i]);
     Serial.print("Transition: ");
     Serial.println(data[i]);
    delay(50);
  }
  Wire.endTransmission();
  delay(50);
}

void readMem(uint16_t memAdrs, uint8_t* data, int sz) {
  Wire.beginTransmission(ADRS_MICRO);
  Wire.write((uint8_t)((memAdrs & 0xFF00) >> 8));
  Wire.write((uint8_t)((memAdrs & 0x00FF) >> 0));
  Wire.endTransmission();

  Wire.requestFrom(ADRS_MICRO, sz);
  for (int i = 0; i < sz; i++) {
    data[i] = Wire.read();
  }
}

void loadStatus() {
  uint8_t fetchedData[10] = {0};
  readMem(ADRS_EEPROM_SAVE, fetchedData, 10);
  if (fetchedData[0] == 255)
    return;

  status = fetchedData[0];
  curMode = fetchedData[1];
  for (int i = 0; i < 4; i++){
    modesTimes[i] = fetchedData[2 + i];
    remainingTime = timerTime = *(float*)(fetchedData + 6);
  }
  if (status == work) {
    showTimer = true;
    digitalWrite(ledPins[curMode], HIGH);
    printStatus(String(curMode + 1));
  } else {
    if (status == finish) {
      for (int i = 0; i < 4; i++)
        digitalWrite(ledPins[i], HIGH);
    } else if (curMode == stopped) {
      digitalWrite(ledPins[curMode], HIGH);
    }

    printStatus();
  }
}

void saveStatus() {
  uint8_t pulledData[10] = {0};
  pulledData[0] = (uint8_t) status;
  pulledData[1] = (uint8_t) curMode;
  for (int i = 0; i < 4; i++)
    pulledData[2 + i] = modesTimes[i];
  *(float*)(pulledData + 6) = remainingTime;
  writeMem(ADRS_EEPROM_SAVE, pulledData, 10);
}

void nextMode() {
  curMode = (curMode + 1) % 4;
  if (curMode == 0) {
    showTimer = false;
    status = finish;
    for (int i = 0; i < 4; i++)
      digitalWrite(ledPins[i], HIGH);
    printStatus();
    return;
  }
  startTime = millis();
  timerTime = modesTimes[curMode];
  digitalWrite(ledPins[curMode - 1], LOW);
  digitalWrite(ledPins[curMode], HIGH);
  printStatus(String(curMode + 1));
}

float TimeRemains() {
  if (!showTimer) {
    return remainingTime;
  }
  long curTime = millis();
    Serial.println(curTime);
    Serial.println(timerTime);
    Serial.println(startTime);
  remainingTime = ((float) timerTime) - ((curTime - startTime) / 1000.0);
    Serial.println(remainingTime);
  if (remainingTime <= 0) {
    nextMode();
    remainingTime = 0;
  }
  Serial.println(remainingTime);
  return remainingTime;
}

void setup() {
  Serial.begin(9600);
  Wire.begin();
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);

  for (int i = 0; i < 4; i++)
    pinMode(ledPins[i], OUTPUT);

  loadStatus();
}

void loop() {
  float timer = TimeRemains();
  lcd.setCursor(0, 1);
  lcd.print("Timer " + String(timer) + "  ");
  char key = kp.getKey();
  if (key) {
    if (status == workless && (key >= '1' && key <= '4')) {
      status = setting;
      changeTimeMode = key - '0' - 1;
      printStatus();
    } else if (status == setting && key == '=') {
      status = workless;
      modesTimes[changeTimeMode] = inp.toInt();
      printStatus();
    } else if (status == work && key == '*') {
      status = stopped;
      showTimer = false;
      timerTime = remainingTime;
      printStatus();
    } else if (status == workless && key == '*') {
      status = work;
      timerTime = modesTimes[0];
      curMode = 0;
      startTime = millis();
      showTimer = true;
      digitalWrite(ledPins[0], HIGH);
      printStatus(String(curMode + 1));
    } else if (status == stopped && key == '*') {
      status = work;
      startTime = millis();
      showTimer = true;
      timerTime = remainingTime;
      printStatus(String(curMode + 1));
    } else if (status == finish && key == '*') {
      status = workless;
      for (int i = 0; i < 4; i++)
        digitalWrite(ledPins[i], LOW);
      printStatus();
    } else if (status == setting) {
      lcd.setCursor(states[status].length() + inp.length(), 0);
      lcd.print(key);
      inp += key;
    }
  }
  if ((millis() - lastSave) > 3000) {
    saveStatus();
    lastSave = millis();
  }
  delay(50);
}
