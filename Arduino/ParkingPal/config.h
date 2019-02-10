// ParkingPal defines and macros.

#ifndef CONFIG_H
#define CONFIG_H

// Hardware configuration
#define BTN_PIN 2
#define ECHO_PIN 3
#define TRIG_PIN 4
#define BUZZ_PIN 5
#define LED_PIN 6

// Beep configuration
#define BEEP_PERIOD_MS 500  // How long to beep for
#define BEEP_FREQ 2048      // Frequency to beep at
#define BEEP_DUTY_ON 50     // Buzzer duty cycle when on (percent)
#define BEEP_DUTY_OFF 0     // Buzzer duty cycle when off
#define BEEP_DUTY_SFX 10    // Duty cycle for sound effects (percent)

//Sensor configuration
#define PING_TIMEOUT 25000      // Sets maximum sensor distance
#define WINDOW_FILTER_TIME_S 10 // Window filter length in seconds
#define POLL_FREQ 3             // How frequently to poll the sensor
#define POLL_T_MS (1.0/POLL_FREQ)*1000
#define NUM_SEN_SAMPLES POLL_FREQ * WINDOW_FILTER_TIME_S
#define NUM_DIST_SAMPLES 3      // Distance window filter 

// LED configuration
#define FLIP_LEDS true		// Flip LED orientation
#define NUM_LEDS 8          // Number of LEDs in your light setup
#define MAX_LED_MODES 4     // Number of LED modes to switch through
#define BRIGHTNESS_MIN 50   // Lowest brightness setting
#define BRIGHTNESS_MAX 250  // Maximum allowable brightness of LEDs
#define BRIGHTNESS_INC 50   // Amount to increment brightness by
#define LED_FADE_MS 3000    // How long to fade out LEDs when going idle

// LED modes
#define LED_MODE_BAR 0
#define LED_MODE_RG 1
#define LED_MODE_RYG 2
#define LED_MODE_STOPLIGHT 3
#define LED_FLASH_WAVE 0
#define LED_FLASH_BLUE 1
#define LED_FLASH_STARTUP 2
#define LED_FLASH_MODE 3

// System configuration
#define DIST_THRESHOLD_CM 5     // Don't wake unless distance has changed this much
#define DISTANCE_MAX_CM 350     // Maximum distance to measure
#define SAFE_ZONE_CM 20         // Safe zone buffer ahead of beeping
#define LOOP_DELAY 50           // How frequently to poll the loop
#define USE_DEEP_SLEEP false     // Sleep using low power library

// Debug settings
//#define DEBUG
#define PARAM_LOGGING
#define LED_LOGGING
#define LOOP_LOGGING
#define EEPROM_LOGGING
#define PING_LOGGING
#define BUTTON_LOGGING

#endif