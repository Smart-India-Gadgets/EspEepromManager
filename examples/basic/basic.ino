#include "EspEepromManager.h"

EspEepromManager eepromManager;

struct MyData {
    int id;
    float value;
};

void setup() {
  // your setup code here
  eepromManager.begin(256); // Initialize EEPROM with size 256 bytes

  eepromManager.write(0, 42); // Example write single byte to EEPROM
  uint8_t value = eepromManager.read(0); // Example read single byte from EEPROM

  eepromManager.writeStringToRom(10, "Hello EEPROM", 20); // Example write string to EEPROM
  char buf[20];
  eepromManager.readStringFromRom(10, buf, sizeof(buf)); // Example read string from EEPROM

  MyData data = {123, 45.67f};
  eepromManager.put(50, data); // Example write struct to EEPROM
  MyData readData;
  eepromManager.get(50, readData); // Example read struct from EEPROM

  eepromManager.reset(); // Example reset of EEPROM
}

void loop() {
  // your loop code here
  eepromManager.checkAndCommit(); // Must keep this inside loop to check if there are pending writes to commit
}