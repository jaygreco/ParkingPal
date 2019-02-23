# ParkingPal
An open-source distance meter for easy garage parking. See [the thingiverse page](https://www.thingiverse.com/thing:3448336) for more info.

SolidWorks CAD and STL files will hosted in Thingiverse as well.

## How to use
Compile for the Arduino Pro Micro and upload. By default, the firmware is built for 8 LEDs (the NeoPixel Stick), and will poll the sensor at 3Hz until the read distance has been stable for roughly 10 seconds.

Single-pressing the button will change the operating mode. Double-clicking will cycle the brightness, and long-pressing will set the default parking distance. To set the default parking distance properly, park the car at the normal parking distance, and then long-press the button while making sure to stay clear of the ultrasonic sensor. Once set, the buzzer will beep once.

There are some configuration options in `config.h`. They should be pretty self-explanatory. There really isn't much need to change these unless you want to tweak some specific behavior. 
