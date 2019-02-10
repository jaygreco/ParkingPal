// Nonvolatile memory controls and functions.

#ifndef NVM_H
#define NVM_H

#include <Arduino.h>
#include <EEPROM.h>
#include "config.h"

#define EEPROM_MAGIC 0x01
#define DEFAULT_DIST_CM 80
#define DEFAULT_BRIGHTNESS 100
#define DEFAULT_LED_MODE 0
#define DEFAULT_BEEP_EN ((uint8_t) true)

enum offsets : uint8_t {
    MAGIC_NUMBER = 0,   // 1 byte
    PARKED_DIST_CM = 1, // 1 byte
    BRIGHTNESS = 2,     // 1 byte
    LED_MODE = 3,       // 1 byte
    BEEP_EN = 4         // 1 byte
};

class Eeprom {
public:
    Eeprom();

    void
    begin(void),
    setDefaultParkDist(uint8_t distance),
    setDefaultBrightness(uint8_t brightness),
    setDefaultLEDMode(uint8_t mode),
    printParams(void);

    uint8_t
    getDefaultParkDist(void),
    getDefaultBrightness(void),
    getDefaultLEDMode(void);

private:
    void
    configure(void),
    store(uint8_t offset, uint8_t data);

    uint8_t
    read(uint8_t offset);

    bool
    isConfigured(void);
};

#endif