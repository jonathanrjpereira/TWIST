/*Example testing sketch for MPL3115A2 Barometric Pressure & Altitude Sensor
 Written by Nathan Seidle on September 24th, 2013, public domain
 Modified by Jonathan Pereira on 20th November 2015 public domain
 for the Tweeting Weather Iot STation aka TWIST platform
 http://www.instructables.com/id/TWIST-DIY-Tweeting-Weather-Station/
*/

/* ___________________________________________________________________________________________________________________________________________________________________________
 *    TWIST SETUP
 * In order to use this code for TWIST follow the follwing steps:
 * Step 1: Copy all the pin declarations, variable declarations,library initalizations to the main TWIST code before the setup block.
 * Step 2: Copy all the statement from the setup block into the setup block of the main TWIST code.
 * Step 3: Copy all the statement from the loop block into the loop block of the main TWIST code.
 * Step 4: Copy the ' void MPL3115A2(){.............} ' function and paste it outside the the loop block of the main TWIST code.
 * ___________________________________________________________________________________________________________________________________________________________________________
 */

/* 
 Hardware Connections (Breakoutboard to Intel Edison):
 -VCC = 3.3V
 -SDA = A4 (use inline 10k resistor if your board is 5V)
 -SCL = A5 (use inline 10k resistor if your board is 5V)
 -INT pins can be left unconnected for this demo
*/ 

#include <Wire.h>
#include "SparkFunMPL3115A2.h"

//Create an instance of the object
MPL3115A2 myPressure;

void setup()
{
  Wire.begin();        // Join i2c bus
  Serial.begin(9600);  // Start serial for output

  myPressure.begin(); // Get sensor online

  // Configure the sensor
  //myPressure.setModeAltimeter(); // Measure altitude above sea level in meters
  myPressure.setModeBarometer(); // Measure pressure in Pascals from 20 to 110 kPa
  
  myPressure.setOversampleRate(7); // Set Oversample to the recommended 128
  myPressure.enableEventFlags(); // Enable all three pressure and temp event flags 
}

void loop()
{
  MPL3115A2();
  float altitude,pressure;
  
  String stringMsg = "Altitude:";
  char MPL3115A2alt[10];
  dtostrf(altitude,1,0,MPL3115A2alt);
  stringMsg += MPL3115A2alt;
  stringMsg += "m";
  
  String stringMsg = "Atmsp Pressure:";
  char MPL3115A2pre[10];
  dtostrf(pressure,1,0,MPL3115A2pre);
  stringMsg += MPL3115A2pre;
  stringMsg += "Pa";
    
}


void  MPL3115A2()
{
  float altitude = myPressure.readAltitude();
  Serial.print("Altitude(m):");
  Serial.print(altitude, 2);

  float pressure = myPressure.readPressure();
  Serial.print("Pressure(Pa):");
  Serial.print(pressure, 2);

}
