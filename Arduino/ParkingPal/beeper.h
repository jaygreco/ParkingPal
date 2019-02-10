// Async beeper library using Timer3 library.

#ifndef BEEP_H
#define BEEP_H

#include <Arduino.h>
#include <TimerThree.h> //Uses TimerThree: https://github.com/PaulStoffregen/TimerThree
#include "config.h"

class Beeper {
public:
    Beeper();

    void
    begin(uint16_t freq),
    handle(void),
    beep(uint16_t duration, uint8_t duty),
    enable(void),
    disable(void);

    
private:
    void
    _stop(void),
    _beepOn(void),
    _beepOff(void);
    
    bool
    _enabled = false,
    _beeping = false;

    unsigned long _lastBeep = 0;
};

#endif