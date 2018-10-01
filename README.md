# ArduinoTempDisplay
Arduino based Dallas DS18B20 Temperature Sensor with SSD1306 OLED Display.

This is a simple temp sensor that can be whacked up quickly.  The MCU is an Arduino Nano, the temperature sensor is a Dallas DS18B20, and the display is an SSD1306 based I2C 128x64 mono OLED.  The Nano is my choice because it is cheap, small, and comes with a useful USB port.

# Parts List
1. Arduino Nano, will work with pretty much any Arduino, including Digisparks and the like.
2. Dallas DS18B20 Temperature Sensor.
3. 128x64 OLED display with SSD1306 controller using I2C.
4. 4.7K Ohm Resister.

# Build Instructions
1. Attach the display SCL/SDA to the MCU.  For an Arduino Nano, SDA is A4 and SCL is A5.
2. Attach the display power to the MCU.  Check the power requirements of your display for 3.3v vs 5v.  GND to GND.
3. Attach the temp sensor to 5v, GND, and D2.  For my waterproof DS18B20, Red it 5v, Black is GND, and Yellow is Data(D2).
4. Place the 4.7K resistor between D2 and 5v as a pullup.
5. Add the following libraries using the Arduino Library Manager:
* OneWire
* DallasTemperature
* Adafruit GFX
* Adafruit SSD1306
6. You will also need SPI & Wire, but these should be included by default.
7. Verify the code, modify as desired, and compile and upload to MCU.


