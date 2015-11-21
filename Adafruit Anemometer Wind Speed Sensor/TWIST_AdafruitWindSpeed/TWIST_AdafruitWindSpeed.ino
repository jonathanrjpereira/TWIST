/*Example testing sketch for Adafruit's Anemometer Wind Speed Sensor w/Analog Voltage Output
 Written by Jonathan Pereira on 21st November 2015 public domain
 for the Tweeting Weather Iot STation aka TWIST platform
 http://www.instructables.com/id/TWIST-DIY-Tweeting-Weather-Station/
*/

/* ___________________________________________________________________________________________________________________________________________________________________________
 *    TWIST SETUP
 * In order to use this code for TWIST follow the follwing steps:
 * Step 1: Copy all the pin declarations, variable declarations,library initalizations to the main TWIST code before the setup block.
 * Step 2: Copy all the statement from the setup block into the setup block of the main TWIST code.
 * Step 3: Copy all the statement from the loop block into the loop block of the main TWIST code.
 * Step 4: Copy the ' void adaanemometer(){.............} ' function and paste it outside the the loop block of the main TWIST code.
 * ___________________________________________________________________________________________________________________________________________________________________________
 */

/* 
 Hardware Connections (Breakoutboard to Intel Edison):
-Pin1(Brown):VCC/5V
-Pin2(Black):Ground
-Pin3(Blue)(Signal):Analog Pin A0
*/ 



int adawind= A0;
void setup()
{
pinMode(A0,INPUT);
}

void loop()
{
  adaanemometer();
  float windspeed;
  
  String stringMsg = "Wind Speed:";
  char wind[10];
  dtostrf(windspeed,1,0,wind);
  stringMsg += wind;
  stringMsg += "m";
}

// the loop routine runs over and over again forever:
void adaanemometer() {
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  float voltage = sensorValue * (5.0 / 1023.0);
  float windspeed =map(voltage,0.4,2.0,0,32.4);
  Serial.println(windspeed);
}
