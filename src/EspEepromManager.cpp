#include "EspEepromManager.h"

// Private helper functions
void EspEepromManager::_commit() {
    if (this->pendingCommit) {
        delay(20);
        EEPROM.commit(); // Store data to EEPROM
        this->pendingCommit = false;
    }
}

// Public methods
void EspEepromManager::begin() {
    EEPROM.begin(this->romSize);
}
void EspEepromManager::begin(int size) {
    this->romSize = size;
    EEPROM.begin(this->romSize);
}

void EspEepromManager::forceCommit() {
    _commit();
}

void EspEepromManager::checkAndCommit() {
    if (this->pendingCommit && (millis() - this->lastWriteTime >= COMMIT_DELAY_MS)) {
        _commit();
    }
}

void EspEepromManager::write(int addr, uint8_t val) {
    EEPROM.write(addr, val);
    this->pendingCommit = true;
    this->lastWriteTime = millis();
}

uint8_t EspEepromManager::read(int addr) {
    return EEPROM.read(addr);
}

void EspEepromManager::reset() {
    for (int i = 0; i < romSize; i++) {
        write(i, 0);
    }
    _commit();
}

void EspEepromManager::writeString(int addr, const char *str, size_t maxLen) {
    size_t len = strlen(str);
    if (len > maxLen - 1) {
        len = maxLen - 1; // truncate to fit
    }

    write(addr, len);

    for (size_t i = 0; i < len; i++) {
        write(addr + 1 + i, (uint8_t)str[i]);
    }

    // clear remaining bytes (optional, keeps consistent state)
    for (size_t i = len; i < maxLen - 1; i++) {
        write(addr + 1 + i, 0);
    }
}

void EspEepromManager::readString(int addr, char *buf, size_t bufSize) {
    int newStrLen = read(addr);
    if (newStrLen < 0)
        newStrLen = 0;

    if ((size_t)newStrLen > bufSize - 1)
        newStrLen = bufSize - 1;

    for (int i = 0; i < newStrLen; i++) {
        buf[i] = (char)read(addr + 1 + i);
    }
    buf[newStrLen] = '\0'; // end (null) character
}
