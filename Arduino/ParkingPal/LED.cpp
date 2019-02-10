#include "LED.h"

// Public
LED::LED() : _pixels(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800) {}

void LED::begin(void) {
    _pixels.begin();
    #if defined(LED_LOGGING) && defined(DEBUG)
    Serial.print("[LED] Begin: ");
    Serial.print(_pixels.numPixels());
    Serial.println(" LEDs");
    #endif
}

void LED::setMode(uint8_t mode) {
    #if defined(LED_LOGGING) && defined(DEBUG)
    Serial.print("[LED] Mode: ");
    Serial.println(mode);
    #endif
    _mode = mode;
}

void LED::setLEDBrightness(uint8_t brightness) {
    _brightness = brightness;
    _pixels.setBrightness(_brightness);
    _pixels.show();

    #if defined(LED_LOGGING) && defined(DEBUG)
    Serial.print("[LED] Brightness: ");
    Serial.println(_brightness);
    #endif
}

void LED::setDistance(int distance) {
    _distance = distance;
}

void LED::setParkDistance(int parkDistance) {
	_parkDistance = parkDistance;
}

void LED::update() {
    _pixels.clear();
    _pixels.setBrightness(_brightness);

    switch(_mode) {
        case LED_MODE_BAR:
        _barMode();
        break;

        case LED_MODE_RG:
        _RGMode();
        break;

        case LED_MODE_RYG:
        _RYGMode();
        break;

        case LED_MODE_STOPLIGHT:
        _StoplightMode();
        break;

        default:
        break;
    }

    _pixels.show();
    _idle = millis();
}

void LED::flash(uint8_t animation) {
    _pixels.clear();

    bool lightsOff = false;
    if (_pixels.getBrightness() == 0) {
        lightsOff = true;
        _pixels.setBrightness(_brightness);
    }

    #if defined(LED_LOGGING) && defined(DEBUG)
    Serial.print("[LED] Flash animation: ");
    Serial.println(animation);
    #endif

    switch (animation) {
        case LED_FLASH_WAVE:
        _wave();
        break;

        case LED_FLASH_BLUE:
        _blue();
        break;

        case LED_FLASH_STARTUP:
        _startup();
        break;

        case LED_FLASH_MODE:
        _flashMode();
        break;

        default:
        break;
    }

    if (lightsOff) {
        _pixels.setBrightness(0);
    }
}

uint8_t LED::getLEDBrightness(void) {
    return _brightness;
}

uint8_t LED::getMode(void) {
    return _mode;
}

bool LED::fade(void) {
    unsigned long t = millis() - _idle;
    if (t < LED_FADE_MS) {
        // Fade
        int b = max(_brightness * (1.0 - ((float)t/LED_FADE_MS)), 0);
        _pixels.setBrightness(b);
        _pixels.show();
        #if defined(LED_LOGGING) && defined(DEBUG)
        Serial.print("[LED] Fade brightness: ");
        Serial.println(b);
        #endif
        return true;
    }
    else return false;
}

// Private

void LED::_barMode() {
    // Fills the bar depending on distance
    float a = (NUM_LEDS - 1)*(_distance - DISTANCE_MAX_CM);
    float b = (SAFE_ZONE_CM + _parkDistance - DISTANCE_MAX_CM);
    float n = constrain((a/b) + 1, 1, NUM_LEDS);

    float d = _distance - (SAFE_ZONE_CM + _parkDistance);
    float r_raw = 510*(1 - (d/DISTANCE_MAX_CM));
    int r = constrain(r_raw, 0, 255);
    float g_raw = 510*(d/DISTANCE_MAX_CM);
    int g = constrain(g_raw, 0, 255);

    #if defined(LED_LOGGING) && defined(DEBUG)
    Serial.print("[LED] n:");
    Serial.print((int)n);
    Serial.print(" d:");
    Serial.print((int)d);
    Serial.print(" r:");
    Serial.print((int)r);
    Serial.print(" g:");
    Serial.println((int)g);
    #endif

    #if FLIP_LEDS
    for(int i=(int)n-1;i>=0;i--){
        _pixels.setPixelColor(i, _pixels.Color(r,g,0)); 
    }
    #else
    for(int i=0;i<(int)n;i++){
        _pixels.setPixelColor(i, _pixels.Color(r,g,0)); 
    }
    #endif
}

void LED::_RGMode(void) {
    // Green unless within park + SAFE_ZONE, then red.
    if (_distance < SAFE_ZONE_CM + _parkDistance) {
        for(int i=0;i<NUM_LEDS;i++){
            _pixels.setPixelColor(i, _pixels.Color(255,0,0)); 
        }
    } else {
        for(int i=0;i<NUM_LEDS;i++){
            _pixels.setPixelColor(i, _pixels.Color(0,255,0)); 
        }
    }
}

void LED::_RYGMode(void) {
    // Green between MAX and MAX/2, yellow between MAX/2 and park, red otherwise.
    int m2 = DISTANCE_MAX_CM - (SAFE_ZONE_CM + _parkDistance); //MAX/2
    if (_distance < SAFE_ZONE_CM + _parkDistance) {
        for(int i=0;i<NUM_LEDS;i++){
            _pixels.setPixelColor(i, _pixels.Color(255,0,0)); 
        }
    } else if (_distance < m2) {
        for(int i=0;i<NUM_LEDS;i++){
            _pixels.setPixelColor(i, _pixels.Color(255,255,0)); 
        }
    } else {
        for(int i=0;i<NUM_LEDS;i++){
            _pixels.setPixelColor(i, _pixels.Color(0,255,0)); 
        }
    }
}

void LED::_StoplightMode(void) {
    // Green between MAX and MAX/2, yellow between MAX/2 and park, red otherwise, with displacement
    int m2 = DISTANCE_MAX_CM - (SAFE_ZONE_CM + _parkDistance); //MAX/2
    int range = (NUM_LEDS - 2) / 3;
    if (_distance < SAFE_ZONE_CM + _parkDistance) {
        #if FLIP_LEDS
        for(int i=0;i<range;i++){
            _pixels.setPixelColor(i, _pixels.Color(255,0,0)); 
            
        }
        #else
        for(int i=3*range;i<NUM_LEDS;i++){
            _pixels.setPixelColor(i, _pixels.Color(255,0,0)); 
        }
        #endif
    } else if (_distance < m2) {
        for(int i=2*range-1;i<3*range-1;i++){
            _pixels.setPixelColor(i, _pixels.Color(255,255,0)); 
        }
    } else {
        #if FLIP_LEDS
        for(int i=3*range;i<NUM_LEDS;i++){ 
            _pixels.setPixelColor(i, _pixels.Color(0,255,0)); 
        }
        #else
        for(int i=0;i<range;i++){
            _pixels.setPixelColor(i, _pixels.Color(0,255,0)); 
        }
        #endif
    }
}

void LED::_wave() {
    #if FLIP_LEDS
    for(int i=NUM_LEDS-1;i>=0;i--){
        _pixels.setPixelColor(i, _pixels.Color(0, 255, 0));
        _pixels.show();
        delay(20);
    }
    #else
    for(int i=0;i<NUM_LEDS;i++){
        _pixels.setPixelColor(i, _pixels.Color(0, 255, 0));
        _pixels.show();
        delay(20);
    }
    #endif

    #if FLIP_LEDS
    for(int i=NUM_LEDS-1;i>=0;i--){
        _pixels.setPixelColor(i, _pixels.Color(255, 255, 0));
        _pixels.show();
        delay(20);
    }
    #else
    for(int i=0;i<NUM_LEDS;i++){
        _pixels.setPixelColor(i, _pixels.Color(255, 255, 0));
        _pixels.show();
        delay(20);
    }
    #endif

    #if FLIP_LEDS
    for(int i=NUM_LEDS-1;i>=0;i--){
        _pixels.setPixelColor(i, _pixels.Color(255, 0, 0));
        _pixels.show();
        delay(20);
    }
    #else
    for(int i=0;i<NUM_LEDS;i++){
        _pixels.setPixelColor(i, _pixels.Color(255, 0, 0));
        _pixels.show();
        delay(20);
    }
    #endif

    #if FLIP_LEDS
    for(int i=NUM_LEDS-1;i>=0;i--){
        _pixels.setPixelColor(i, _pixels.Color(0, 0, 0));
        _pixels.show();
        delay(50);
    }
    #else
    for(int i=0;i<NUM_LEDS;i++){
        _pixels.setPixelColor(i, _pixels.Color(0, 0, 0));
        _pixels.show();
        delay(50);
    }
    #endif
}

void LED::_blue() {
    #if FLIP_LEDS
    for (int i=NUM_LEDS-1;i>=0;i--){
        _pixels.setPixelColor(i, _pixels.Color(0, 0, 255)); 
        _pixels.show();
        delay(50);
    }
    #else 
    for (int i=0;i<NUM_LEDS;i++){
        _pixels.setPixelColor(i, _pixels.Color(0, 0, 255)); 
        _pixels.show();
        delay(50);
    }
    #endif

    #if FLIP_LEDS
    for (int i=NUM_LEDS-1;i>=0;i--){
        _pixels.setPixelColor(i, _pixels.Color(0, 0, 0)); 
        _pixels.show();
        delay(50);
    }
    #else 
    for (int i=0;i<NUM_LEDS;i++){
        _pixels.setPixelColor(i, _pixels.Color(0, 0, 0)); 
        _pixels.show();
        delay(50);
    }
    #endif
}

void LED::_flashMode(void) {
    //  Fill bar depending on mode
    for(int i=0;i<=_mode;i++){
        _pixels.setPixelColor(i, _pixels.Color(255, 255, 255)); 
        
    }
    _pixels.show();
    delay(1000);

    for(int i=0;i<NUM_LEDS;i++){
        _pixels.setPixelColor(i, _pixels.Color(0, 0, 0)); 
    }
    _pixels.show();
}

void LED::_startup() {
    for(int i=0;i<NUM_LEDS;i++){
        _pixels.setPixelColor(i, _pixels.Color(0, 255, 0));
    }
    _pixels.show();
    delay(750);

    for(int i=0;i<NUM_LEDS;i++){
        _pixels.setPixelColor(i, _pixels.Color(255, 255, 0));
    }
    _pixels.show();
    delay(750);

    for(int i=0;i<NUM_LEDS;i++){
        _pixels.setPixelColor(i, _pixels.Color(255, 0, 0));
    }
    _pixels.show();
    delay(750);

    for(int i=0;i<NUM_LEDS;i++){
        _pixels.setPixelColor(i, _pixels.Color(0, 0, 0));
    }
    _pixels.show();
}