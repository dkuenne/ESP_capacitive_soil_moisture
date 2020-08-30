# ESP capacitive soil moisture sensor

## About

This code is for testing / using capacitive soil moisture sensors with ESP based boards (ESP32 / ESP8266) in Arduino IDE.
It provides functions for getting calibration values and displays the information via 20x4 LCD and if enabled via serial monitor.





## Important

- You need to gather calibration data first to measure soil
- Needs to be calibrated for every sensor / ESP combination (ESP8266 has different ADC values than ESP32)
- Probably also needs to be calibrated for different power sources





## Usage

| Use                                                          | Function name         |
| ------------------------------------------------------------ | --------------------- |
| Measure dry calibration value (sensor in air) -> modify ```airVal``` to this value | ```measureAir();```   |
| Measure wet calibration value (sensor in water) -> modify ```waterVal``` to this value | ```measureWater();``` |
| Measure soil moisture based on calibration values gathered with the above functions | ```measureSoil();```  |
| Get raw values for debugging purposes                        | ```rawVals();```      |





## Hardware

- ESP8266 (NodeMCU V3)
- Capacitive soil moisture sensor v1.2
- 20x4 2004A blue LCD (HD44780) with I2C adapter module





## Pinout

| ESP8266     | Sensor  |
| ----------- | ------- |
| 3,3V        | VCC     |
| GND         | GND     |
| AD0         | AOUT    |
|             |         |
| **ESP8266** | **LCD** |
| 5V          | VCC     |
| GND         | GND     |
| D2          | SDA     |
| D1          | SCL     |





## License

The ESP capacitive soil moisture sensor project by Dominik Künne is licensed under CC BY-NC 4.0. To view a copy of this license, visit  https://creativecommons.org/licenses/by-nc/4.0

This project uses code from:

- how2electronics.com: Example code for sensor and LCD (https://how2electronics.com/interface-capacitive-soil-moisture-sensor-arduino/)
- tandembyte/LCD_I2C: Library (https://gitlab.com/tandembyte/LCD_I2C/-/tree/master)

Please see the LICENSE file for details.





## ToDos

- WLAN connection
- MQTT
- Offline calibration via buttons