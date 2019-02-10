// LED functions

#ifndef LED_H
#define LED_H

#include <Arduino.h>
#include <Adafruit_NeoPixel.h> //Uses AdafruitNeopixel: https://github.com/adafruit/Adafruit_NeoPixel
#include "config.h"

class LED {
public:
    LED();

    void
    begin(void),
    setMode(uint8_t mode),
    setLEDBrightness(uint8_t brightness),
    flash(uint8_t animation),
    setDistance(int distance),
    setParkDistance(int parkDistance),
    update(void);

    uint8_t
    getLEDBrightness(void),
    getMode(void);

    bool fade(void);

private:
    void
    _barMode(void),
    _RGMode(void),
    _RYGMode(void),
    _StoplightMode(void),
    _wave(void),
    _blue(void),
    _startup(void),
    _flashMode(void);

    Adafruit_NeoPixel _pixels;

    uint8_t
    _mode = 0,
    _brightness = 100;

    int
    _distance = 0,
    _parkDistance = 0;

    unsigned long _idle = 0;
};

#endif