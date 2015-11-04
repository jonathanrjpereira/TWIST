// Example testing sketch for various DHT humidity/temperature sensors
// Written by ladyada, public domain
//Modified by Jonathan Pereira on 4th November 2015 for the Tweeting Weather Iot STation aka TWIST platform http://www.instructables.com/id/TWIST-DIY-Tweeting-Weather-Station/

/* ___________________________________________________________________________________________________________________________________________________________________________
 *    TWIST SETUP
 * In order to use this code for TWIST follow the follwing steps:
 * Step 1: Copy all the pin declarations, variable declarations,library initalizations to the main TWIST code before the setup block.
 * Step 2: Copy all the statement from the setup block into the setup block of the main TWIST code.
 * Step 3: Copy all the statement from the loop block into the loop block of the main TWIST code.
 * Step 4: Copy the ' void dht11(){.............} ' function and paste it outside the the loop block of the main TWIST code.
 * ___________________________________________________________________________________________________________________________________________________________________________
 */

#include "DHT.h"
#define DHTPIN 3     // what digital pin we're connected to
// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  dht.begin();
}

void loop() {
 
  dht11();
   float h;
   float t;
   float f;
   
  //Humidity
  stringMsg += "  Humidity:";
  char dht11humidity[10];
  dtostrf(h,1,2,dht11humidity);
  stringMsg += dht11humidity;
  stringMsg += "%RH";

  //Temperature Celsius
  stringMsg += "  Temperature:";
  char dht11celsius[10];
  dtostrf(t,1,2,dht11celsius);
  stringMsg += dht11celsius;
  stringMsg += "°C";

    //Temperature Celsius
  stringMsg += "  Temperature:";
  char dht11farhen[10];
  dtostrf(f,1,2,dht11farhen);
  stringMsg += dht11farhen;
  stringMsg += "°F";
  
  
  
}
  void dht11() {
  // Wait a few seconds between measurements.
  delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

//  Serial.print("Humidity: ");
//  Serial.print(h);
//  Serial.print(" %\t");
//  Serial.print("Temperature: ");
//  Serial.print(t);
//  Serial.print(" *C ");
//  Serial.print(f);
//  Serial.print(" *F\t");
//  Serial.print("Heat index: ");
//  Serial.print(hic);
//  Serial.print(" *C ");
//  Serial.print(hif);
//  Serial.println(" *F");
}
