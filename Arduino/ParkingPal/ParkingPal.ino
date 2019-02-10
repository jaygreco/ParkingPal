//#include <Adafruit_NeoPixel.h> //Uses AdafruitNeopixel: https://github.com/adafruit/Adafruit_NeoPixel
//#include <Ultrasonic.h> //Uses Ultrasonic: https://github.com/JRodrigoTech/Ultrasonic-HC-SR04
//#include <TimerThree.h> //Uses TimerThree: https://github.com/PaulStoffregen/TimerThree
#include <OneButton.h> //Uses Arduno_OneButton: https://github.com/mathertel/OneButton
#include <Narcoleptic.h> //Uses Narcoleptic library: https://github.com/brabl2/narcoleptic

#include "util.h"
#include "NVM.h"
#include "beeper.h"
#include "sensor.h"
#include "button.h"
#include "LED.h"

OneButton button(BTN_PIN, true);

void setup(void) {
    // Configure peripherals
    #if defined(DEBUG)
    Serial.begin(9600);
    delay(1000);
    #else
    TXLED1;
    delay(1000);
    RXLED1;
    #endif

    LEDs.begin();
    eeprom.begin();
    beeper.begin(BEEP_FREQ);

    // Disable things we don't need
    Narcoleptic.disableWire();
    Narcoleptic.disableSPI();
    ADCSRA &= ~(1<<ADEN); //Disable ADC
    ACSR = (1<<ACD); //Disable the analog comparator

    // Configure button handler
    button.attachClick(click);
    button.attachDoubleClick(doubleClick);
    button.attachLongPressStart(longPress);

    // Load defaults from EEPROM at startup
    sensor.setParkDistance(eeprom.getDefaultParkDist());
    LEDs.setParkDistance(eeprom.getDefaultParkDist());
    LEDs.setLEDBrightness(eeprom.getDefaultBrightness());
    LEDs.setMode(eeprom.getDefaultLEDMode());

    #if defined(PARAM_LOGGING) && defined(DEBUG)
    printParams();
    eeprom.printParams();
    #endif

    LEDs.flash(LED_FLASH_STARTUP);
}

void loop(void) {
    sensor.ping();
    button.tick();
    beeper.handle();

    #if defined(LOOP_LOGGING) && defined(DEBUG)
    // Loop logging statements go here
    // WARNING: This will absolutely blast the serial console if enabled
    #endif

    if (abs(sensor.distance() - sensor.average()) > DIST_THRESHOLD_CM) {
        // Active -- don't go to sleep.
        sensor.distance() <= sensor.parkDistance() ? beeper.enable() : beeper.disable();
        LEDs.setDistance(sensor.distance());
        LEDs.update();

    } else {
        if (!LEDs.fade()) {
            // Fading is done, we can go into sleep mode.
            #if USE_DEEP_SLEEP && !defined(DEBUG)
            Narcoleptic.delay(2*POLL_T_MS);
            #else
            #endif
        }
        beeper.disable();
    }
    delay(LOOP_DELAY);
}