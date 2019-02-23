# ParkingPal
An open-source distance meter for easy garage parking. See [the thingiverse page](https://www.thingiverse.com/thing:3448336) for more info.

## How to use
Compile for the Arduino Pro Micro and upload. By default, the firmware is built for 8 LEDs (the NeoPixel Stick), and will poll the sensor at 3Hz until the read distance has been stable for roughly 10 seconds.

Single-pressing the button will change the operating mode. Double-clicking will cycle the brightness, and long-pressing will set the default parking distance. To set the default parking distance properly, park the car at the normal parking distance, and then long-press the button while making sure to stay clear of the ultrasonic sensor. Once set, the buzzer will beep once.

There are some configuration options in `config.h`. They should be pretty self-explanatory. There really isn't much need to change these unless you want to tweak some specific behavior. 

## Parts list
There's a more detailed BOM [here](https://github.com/jaygreco/ParkingPal/blob/master/PCB/0.1/MCU/MCU_BOM.xlsx).
### Required
| Qty | Part              | Link                                                                |
|-----|-------------------|---------------------------------------------------------------------|
| 1   | Arduino Pro Micro | [SparkFun](https://www.sparkfun.com/products/12640)                 |
| 1   | NeoPixel Stick    | [SparkFun](https://www.sparkfun.com/products/12661)                 |
| 1   | HC-SR04 Sensor    | [SparkFun](https://www.sparkfun.com/products/13959)                 |
| 1   | SMT Pushbutton    | [SparkFun](https://www.sparkfun.com/products/8720)                  |
| 1   | USB A Connector   | [Digikey](https://www.digikey.com/products/en?keywords=380-1412-ND) |
| 1   | PCB - MCU         | [OSHPark](https://oshpark.com/shared_projects/L5AVMKPm)             |
| 1   | PCB - SMU         | [OSHPark](https://oshpark.com/shared_projects/UerOD9Ji)             |

### Optional (to include buzzer)
| Qty | Part            | Link                                                                        |
|-----|-----------------|-----------------------------------------------------------------------------|
| 1   | 12mm Buzzer     | [SparkFun](https://www.sparkfun.com/products/7950)                          |
| 1   | 10k Resistor    | [Digikey](https://www.digikey.com/products/en?keywords=RMCF0201FT10K0CT-ND) |
| 1   | 2N7002 N-Ch Fet | [Digikey](https://www.digikey.com/products/en?keywords=2N7002-TPMSCT-ND)    |
