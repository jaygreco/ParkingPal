// Button click functions

#ifndef BUTTON_H
#define BUTTON_H

#include "NVM.h"
#include "beeper.h"
#include "sensor.h"
#include "LED.h"

Sensor sensor(POLL_T_MS);
LED LEDs;
Beeper beeper;
Eeprom eeprom;

void click(void) {
	// Single click changes LED mode
	beeper.beep(10, BEEP_DUTY_SFX);
    
	int mode = eeprom.getDefaultLEDMode();
    mode += 1;
    if (mode >= MAX_LED_MODES) {
        mode = 0;
    }

    LEDs.setMode(mode);
    eeprom.setDefaultLEDMode(mode);

    #if defined(BUTTON_LOGGING) && defined(DEBUG)
    Serial.println("[BTN] Click");
    Serial.print("[BTN] Setting new mode: ");
    Serial.println(mode);
    #endif

    LEDs.flash(LED_FLASH_MODE);
}

void doubleClick(void) {
    // Double click changes brightness
    beeper.beep(20, BEEP_DUTY_SFX);

    int brightness = eeprom.getDefaultBrightness();
    brightness += BRIGHTNESS_INC;
    if (brightness > BRIGHTNESS_MAX) {
        brightness = BRIGHTNESS_MIN;
    }

    #if defined(BUTTON_LOGGING) && defined(DEBUG)
    Serial.println("[BTN] Double click");
    Serial.print("[BTN] Setting new brightness: ");
    Serial.println(brightness);
    #endif
    LEDs.setLEDBrightness(brightness);
    eeprom.setDefaultBrightness(brightness);

    LEDs.flash(LED_FLASH_WAVE);
}

void longPress(void) {
    // Long press sets parkDistance
    // Beep
    beeper.beep(500, BEEP_DUTY_SFX);

    // Add SAFE_ZONE/2 to prevent beeping
    int d = sensor.singlePing();
    int parkDistance;
    if (d < SAFE_ZONE_CM) {
        parkDistance = SAFE_ZONE_CM;
    } else if (d > DISTANCE_MAX_CM) {
        parkDistance = DISTANCE_MAX_CM - SAFE_ZONE_CM;
    } else {
        parkDistance = d - (SAFE_ZONE_CM/2);
    }
    #if defined(BUTTON_LOGGING) && defined(DEBUG)
    Serial.println("[BTN] Long press");
    Serial.print("[BTN] Setting default parking dist: ");
    Serial.println(parkDistance);
    #endif
    eeprom.setDefaultParkDist(parkDistance);
    sensor.setParkDistance(parkDistance);
    LEDs.setParkDistance(parkDistance);

    LEDs.flash(LED_FLASH_BLUE);
}

#endif