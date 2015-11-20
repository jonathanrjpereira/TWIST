/*Example testing sketch for various LMV324 Microphone/Sound Sensor
 Written by ladyada, public domain
 Modified by Jonathan Pereira on 4th November 2015 
 for the Tweeting Weather Iot STation aka TWIST platform
 http://www.instructables.com/id/TWIST-DIY-Tweeting-Weather-Station/
*/

/* ___________________________________________________________________________________________________________________________________________________________________________
 *    TWIST SETUP
 * In order to use this code for TWIST follow the follwing steps:
 * Step 1: Copy all the pin declarations, variable declarations,library initalizations to the main TWIST code before the setup block.
 * Step 2: Copy all the statement from the setup block into the setup block of the main TWIST code.
 * Step 3: Copy all the statement from the loop block into the loop block of the main TWIST code.
 * Step 4: Copy the ' void LMV324(){.............} ' function and paste it outside the the loop block of the main TWIST code.
 * ___________________________________________________________________________________________________________________________________________________________________________
 */

 /*  Connections
  *   (Sound Detector → Arduino )
  *   GND → Supply Ground
  *   VCC → Power supply voltage between 3.5 and 5.5 Volts
  *   Envelope → A0
  */

int Sound_In=A0;

void setup()
{
  pinMode(Sound_In,INPUT);
}

void loop()
{
  LMV324();
  int value;
  String stringMsg = "Sound lvl:";
  char LMV324sound[10];
  dtostrf(value,1,0,LMV324sound);
  stringMsg += LMV324sound;
  stringMsg += "dB";

}

void LMV324()
{
  int value;

  // Check the envelope input
  value = analogRead(Sound_In);

  if(value <= 10)
  {
    Serial.println("Quiet.");
  }
  else if( (value > 10) && ( value <= 30) )
  {
    Serial.println("Moderate.");
  }
  else if(value > 30)
  {
    Serial.println("Loud.");
  }

}
