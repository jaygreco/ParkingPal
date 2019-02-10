// Basic utility functions.

#ifndef UTIL_H
#define UTIL_H

#include <Arduino.h>
#include "config.h"

void printParams(void) {
    // Beep configuration
    Serial.println("[PARAM] Configuration parameters:");
    Serial.print("[PARAM] BEEP_PERIOD_MS:");
    Serial.println(BEEP_PERIOD_MS);
    Serial.print("[PARAM] BEEP_FREQ:");
    Serial.println(BEEP_FREQ);
    Serial.print("[PARAM] BEEP_DUTY_ON:");
    Serial.println(BEEP_DUTY_ON);
    Serial.print("[PARAM] BEEP_DUTY_SFX:");
    Serial.println(BEEP_DUTY_SFX);

    //Sensor configuration
    Serial.print("[PARAM] PING_TIMEOUT:");
    Serial.println(PING_TIMEOUT);
    Serial.print("[PARAM] WINDOW_FILTER_TIME_S:");
    Serial.println(WINDOW_FILTER_TIME_S);
    Serial.print("[PARAM] POLL_FREQ:");
    Serial.println(POLL_FREQ);
    Serial.print("[PARAM] POLL_T_MS:");
    Serial.println(POLL_T_MS);
    Serial.print("[PARAM] NUM_SEN_SAMPLES:");
    Serial.println(NUM_SEN_SAMPLES);
    Serial.print("[PARAM] NUM_DIST_SAMPLES:");
    Serial.println(NUM_DIST_SAMPLES);

    // LED configuration
    Serial.print("[PARAM] FLIP_LEDS:");
    Serial.println(FLIP_LEDS);
    Serial.print("[PARAM] NUM_LEDS:");
    Serial.println(NUM_LEDS);
    Serial.print("[PARAM] MAX_LED_MODES:");
    Serial.println(MAX_LED_MODES);
    Serial.print("[PARAM] BRIGHTNESS_MIN:");
    Serial.println(BRIGHTNESS_MIN);
    Serial.print("[PARAM] BRIGHTNESS_MAX:");
    Serial.println(BRIGHTNESS_MAX);
    Serial.print("[PARAM] BRIGHTNESS_INC:");
    Serial.println(BRIGHTNESS_INC);
    Serial.print("[PARAM] LED_FADE_MS:");
    Serial.println(LED_FADE_MS);

    // System configuration
    Serial.print("[PARAM] DIST_THRESHOLD_CM:");
    Serial.println(DIST_THRESHOLD_CM);
    Serial.print("[PARAM] DISTANCE_MAX_CM:");
    Serial.println(DISTANCE_MAX_CM);
    Serial.print("[PARAM] SAFE_ZONE_CM:");
    Serial.println(SAFE_ZONE_CM);
    Serial.print("[PARAM] LOOP_DELAY:");
    Serial.println(LOOP_DELAY);
    Serial.print("[PARAM] USE_DEEP_SLEEP:");
    Serial.println(USE_DEEP_SLEEP);
}

#endif