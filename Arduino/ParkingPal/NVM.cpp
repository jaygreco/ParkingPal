#include "NVM.h"

Eeprom::Eeprom()
{
    //Wait until begin() to start.
}

void Eeprom::begin(void) {
    if (!isConfigured()) {
        #if defined(EEPROM_LOGGING) && defined(DEBUG)
        Serial.println("[EEPROM] Not configured!");
        #endif
        configure();
    } else {
        #if defined(EEPROM_LOGGING) && defined(DEBUG)
        Serial.println("[EEPROM] OK");
        #endif
    }
}

void Eeprom::printParams(void) {
    Serial.println("[EEPROM] Configuration parameters:");
    Serial.print("[EEPROM] MAGIC_NUMBER:");
    Serial.println(read(MAGIC_NUMBER));
    Serial.print("[EEPROM] PARKED_DIST_CM:");
    Serial.println(read(PARKED_DIST_CM));
    Serial.print("[EEPROM] BRIGHTNESS:");
    Serial.println(read(BRIGHTNESS));
    Serial.print("[EEPROM] LED_MODE:");
    Serial.println(read(LED_MODE));
}

uint8_t Eeprom::getDefaultParkDist(void) {
    return read(PARKED_DIST_CM);
}

uint8_t Eeprom::getDefaultBrightness(void) {
    return read(BRIGHTNESS);
}

uint8_t Eeprom::getDefaultLEDMode(void) {
    return read(LED_MODE);
}

void Eeprom::setDefaultParkDist(uint8_t distance) {
    store(PARKED_DIST_CM, distance);
}

void Eeprom::setDefaultBrightness(uint8_t brightness) {
    store(BRIGHTNESS, brightness);
}

void Eeprom::setDefaultLEDMode(uint8_t mode) {
    store(LED_MODE, mode);
}

bool Eeprom::isConfigured(void) {
    return read(MAGIC_NUMBER) == EEPROM_MAGIC;
}

void Eeprom::configure(void) {
    #if defined(EEPROM_LOGGING) && defined(DEBUG)
    Serial.println("[EEPROM] Configuring with defaults...");
    #endif
    store(MAGIC_NUMBER, EEPROM_MAGIC);
    store(PARKED_DIST_CM, DEFAULT_DIST_CM);
    store(BRIGHTNESS, DEFAULT_BRIGHTNESS);
    store(LED_MODE, DEFAULT_LED_MODE);
    store(BEEP_EN, DEFAULT_BEEP_EN);
}

// Private
void Eeprom::store(uint8_t offset, uint8_t data) {
    #if defined(EEPROM_LOGGING) && defined(DEBUG)
    Serial.print("[EEPROM] Saving data: ");
    Serial.print(data);
    Serial.print(" at offset: ");
    Serial.println(offset);
    #endif
    EEPROM.put(offset, data);
}

uint8_t Eeprom::read(uint8_t offset) {
    uint8_t data = EEPROM.read(offset);
    #if defined(EEPROM_LOGGING) && defined(DEBUG)
    Serial.print("[EEPROM] Read data: ");
    Serial.print(data);
    Serial.print(" from offset: ");
    Serial.println(offset);
    #endif
    return data;
}