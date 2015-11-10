// Example testing sketch for the Si1145 UV/IR/Visible Light Sensor
// Written by ladyada, public domain
//Modified by Jonathan Pereira on 10th November 2015 for the Tweeting Weather Iot STation aka TWIST platform http://www.instructables.com/id/TWIST-DIY-Tweeting-Weather-Station/

/* ___________________________________________________________________________________________________________________________________________________________________________
 *    TWIST SETUP
 * In order to use this code for TWIST follow the follwing steps:
 * Step 1: Copy all the pin declarations, variable declarations,library initalizations to the main TWIST code before the setup block. Download & Install the Adafruit SI1145 Library.
 * Step 2: Copy all the statement from the setup block into the setup block of the main TWIST code.
 * Step 3: Copy all the statement from the loop block into the loop block of the main TWIST code.
 * Step 4: Copy the ' void dht11(){.............} ' function and paste it outside the the loop block of the main TWIST code.
 * ___________________________________________________________________________________________________________________________________________________________________________
 */

#include <Wire.h>
#include "Adafruit_SI1145.h"

Adafruit_SI1145 uv = Adafruit_SI1145();


void setup() {
  Serial.println("Adafruit SI1145 test");
  
  if (! uv.begin()) {
    Serial.println("Didn't find Si1145");
    while (1);
  }

  Serial.println("OK!");
}


void loop() {
 
SI11451twist();
  float Visiblelight=uv.readVisible();
  float IRlight=uv.readIR();
  float UVindex = uv.readUV();


    //UV light
  stringMsg += " UV Light:";
  char SI1145uv[10];
  dtostrf(UVindex,1,2,SI1145uv);
  stringMsg += SI1145uv;
   
  //Visible Light
  stringMsg += "  Visible Light:";
  char SI1145vis[10];
  dtostrf(Visiblelight,1,2,SI1145vis);
  stringMsg += SI1145vis;


    //Infrared(IR) light
  stringMsg += " IR Light:";
  char SI1145ir[10];
  dtostrf(IRlight,1,2,SI1145ir);
  stringMsg += SI1145ir;


}
  
  void SI11451twist() {
  Serial.println("===================");
  Serial.print("Vis: "); Serial.println(uv.readVisible());
  Serial.print("IR: "); Serial.println(uv.readIR());
  
  // Uncomment if you have an IR LED attached to LED pin!
  //Serial.print("Prox: "); Serial.println(uv.readProx());
  float Visiblelight=uv.readVisible();
  float IRlight=uv.readIR();
  float UVindex = uv.readUV();
  // the index is multiplied by 100 so to get the
  // integer index, divide by 100!
  UVindex /= 100.0;  
  Serial.print("UV: ");  Serial.println(UVindex);

  delay(1000);
}
