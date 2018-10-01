/*
 *  Displays the temp returned by a Dallas One Wire DS18B20 on a SSD1306 OLED via I2C
 */

// Include required libraries.  These can all be added from the 'Manage Libraries' Feature of Arduino IDE
#include <OneWire.h>
#include <DallasTemperature.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

/*
 *  Setup the environment for the Dallas DS18B20
 */
 
// Data wire is plugged into port 2 on the Arduino
#define ONE_WIRE_BUS 2 

// Sensor supports 9,10,11,12 bits of resolution. 9 is one decimal place, 12 is four.        
#define TEMPERATURE_PRECISION 10

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);

// Number of temperature devices found
int numberOfDevices;

// Min & Max Temps
float MinTemp = 256.0;
float MaxTemp = 1.0;

// We'll use this variable to store a found device address
DeviceAddress tempDeviceAddress; 

/*
 *  Setup the Adafruit GFX Library for SSD1306
 */

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

void setup()   {               
  // Start up the library
  sensors.begin();
  
  // Grab a count of devices on the wire
  numberOfDevices = sensors.getDeviceCount();
  if(sensors.getAddress(tempDeviceAddress, 0))
  {
    sensors.setResolution(tempDeviceAddress, TEMPERATURE_PRECISION);
  } 

  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  // initialize with the I2C addr 0x3D (for the 128x64 from Adafruit, 0x3C for many clones)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextColor(WHITE);
}


void loop() {
  // Send the command to get temperatures
  sensors.requestTemperatures();
  
  // Search the wire for address
  if(sensors.getAddress(tempDeviceAddress, 0))
  {
    // Fetch the Temp in C, and convert to F
    float tempC = sensors.getTempC(tempDeviceAddress);
    if( tempC > MaxTemp && tempC < 85.0 ) MaxTemp = tempC ;
    if( tempC < MinTemp ) MinTemp = tempC ;

    // Clear the display, set the cursor to the top.
    display.clearDisplay();
    display.setTextSize(2);
    display.setCursor(0,0);
    display.print("C:");
    display.println(padString(tempC));
    display.setTextSize(1);
    display.print("Min:");
    display.print(MinTemp);
    display.print(" Max:");
    display.println(MaxTemp);
    display.println();
    display.setTextSize(2);
    display.print("F:");
    display.println(padString(DallasTemperature::toFahrenheit(tempC)));
    display.setTextSize(1);
    display.print("Min:");
    display.print(DallasTemperature::toFahrenheit(MinTemp));
    display.print(" Max:");
    display.println(DallasTemperature::toFahrenheit(MaxTemp));
    display.display();
  }
}

String padString ( float num )
{
  int    space  = 0;
  String spaces = "";
  
  //how large is this number?
  //always assumes value has 2 digits after the decimal point.
  if ( num < 10.00 ) space = 4; 
  else if ( num > 9.99 && 100.00 > num ) space = 3;
  else if ( num > 99.99 ) space = 2;
  
  //add the correct amount of spaces infront of our value
  for ( uint8_t s=0; s<space; s++ ) spaces += F(" ");
  
  //return value (or your code here)
  return spaces + String ( num );
}
