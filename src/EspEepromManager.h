#ifndef ESP_EEPROM_MANAGER_H
#define ESP_EEPROM_MANAGER_H

#include <Arduino.h>
#include <ESP_EEPROM.h> // https://github.com/jwrw/ESP_EEPROM.git

class EspEepromManager {
private:
    int romSize = 256; // default size, can be overridden in begin(size)
    const unsigned long COMMIT_DELAY_MS = 3000; // 3 second delay before commit
    unsigned long lastWriteTime = 0;
    bool pendingCommit = false;

    void _commit();

public:
    void begin();
    void begin(int size);
    void reset();
    void checkAndCommit(); // handle delayed commits
    void forceCommit(); // force immediate commit

    void write(int addr, uint8_t val);
    uint8_t read(int addr);

    template <typename T>
    void put(int idx, T &data) {
        const uint8_t *ptr = (const uint8_t *)&data;
        for (int count = sizeof(T); count; --count) {
            write(idx++, *ptr++);
        }
    }

    template <typename T>
    void get(int idx, T &data) {
        uint8_t *ptr = (uint8_t *)&data;
        for (int count = sizeof(T); count; --count) {
            *ptr++ = read(idx++);
        }
    }

    void writeString(int addr, const char *str, size_t maxLen);
    void readString(int addr, char *buf, size_t bufSize);
};

#endif