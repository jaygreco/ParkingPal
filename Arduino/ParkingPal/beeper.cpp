#include "beeper.h"

Beeper::Beeper() {
    //Do nothing
}
// Public

void Beeper::begin(uint16_t freq) {
    Timer3.initialize(1E6/freq);
}

void Beeper::handle(void) {
    if (_enabled) {
        unsigned long t = millis() - _lastBeep;
        if (t < BEEP_PERIOD_MS) {
            //do nothing
            return;
        } else if (t < 2*BEEP_PERIOD_MS) {
            //if beep turn off, else nothing
            if (_beeping) {
                _beepOff();
            }
            return;
        } else {
            //if not beep turn on, else nothing
            if (!_beeping) {
                _beepOn();
            }
            return;
        }
    } else {
        _stop();
    }
}

void Beeper::beep(uint16_t duration, uint8_t duty) {
    uint8_t d = (duty/100.)*1024;
    Timer3.pwm(BUZZ_PIN, d);
    delay(duration);
    Timer3.pwm(BUZZ_PIN, 0);
}

void Beeper::enable(void) {
    _enabled = true;
}

void Beeper::disable(void) {
    _enabled = false;
}

// Private

void Beeper::_stop(void) {
    if (_beeping) {
        _beepOff();
        _beeping = false;
    }
}

void Beeper::_beepOn(void) {
    uint8_t d = (BEEP_DUTY_ON/100.)*1024;
    Timer3.pwm(BUZZ_PIN, d);
    _beeping = true;
    _lastBeep = millis();
}

void Beeper::_beepOff(void) {
    Timer3.pwm(BUZZ_PIN, BEEP_DUTY_OFF);
    _beeping = false;
}