// Sensor functions

#ifndef SENSOR_H
#define SENSOR_H

#include <Arduino.h>
#include <Ultrasonic.h> //Uses Ultrasonic: https://github.com/JRodrigoTech/Ultrasonic-HC-SR04
#include "config.h"
#include "FIFO.h"

class Sensor {
public:
    Sensor(uint16_t pollTime) : 
    ultrasonic(TRIG_PIN, ECHO_PIN, PING_TIMEOUT),
    _samples(NUM_SEN_SAMPLES),
    _distance(NUM_DIST_SAMPLES) 
    {
        _pollTime = pollTime;
    }

    void ping(void) {
        unsigned long t = millis() - _lastPing;

        if (t > _pollTime) {
            int d = ultrasonic.Ranging(CM);
            _distance.insert(ultrasonic.Ranging(CM));
            _samples.insert(_distance.average());

            #if defined(PING_LOGGING) && defined(DEBUG)
            Serial.print("[PING] Distance: ");
            Serial.print(_distance.average());
            Serial.print(" CM -- AVG: ");
            Serial.println(_samples.average());
            #endif

            _lastPing = millis();
        }
    }

    void setParkDistance(int parkDist) {
        _parkDist = parkDist;
    }

    int parkDistance(void) {
        return _parkDist;
    }

    int singlePing(void) {
        return ultrasonic.Ranging(CM);
    }

    int distance(void) {
        return _distance.average();
    }

    int average(void) {
        return _samples.average();
    }

private:
    Ultrasonic ultrasonic;
    
    FIFO
    _samples,
    _distance;

    unsigned long _lastPing = 0;
    uint16_t _pollTime;
    int _parkDist;
};

#endif