/*
 * Written by Jonathan Pereira on 24th October 2015 for public domain.
 * Manual Type-Casting block of code contributed by Nathan Neal Dmello.
*/

#include <SPI.h>
#include <Ethernet.h>
#include <Twitter.h>
#include <stdlib.h>
float temperatureSensor = A0;
float humiditySensor = A1;
int rainSensor = 2;

#define MQ_PIN                       (2)    //  define which analog input channel you are going to use
#define RL_VALUE                     (4.7)  //  define the load resistance on the board, in kilo ohms
#define RO_CLEAN_AIR_FACTOR          (9.83) //  RO_CLEAR_AIR_FACTOR=(Sensor resistance in clean air)/RO,
#define CALIBARAION_SAMPLE_TIMES     (50)   //  define how many samples you are going to take in the calibration phase
#define CALIBRATION_SAMPLE_INTERVAL  (500)  //  define the time interal(in milisecond) between each samples in the                                                     //cablibration phase
#define READ_SAMPLE_INTERVAL         (50)   //  define how many samples you are going to take in normal operation
#define READ_SAMPLE_TIMES            (5)    //  define the time interal(in milisecond) between each samples in
#define GAS_LPG                      (0)
#define GAS_CO                       (1)
#define GAS_SMOKE                    (2)
float LPGCurve[3] = {2.3,0.21,-0.47};
/*Two points are taken from the curve with these two points, a line is formed
which is "approximately equivalent to the original curve.
data format:{ x, y, slope}; point1: (lg200, 0.21), point2: (lg10000, -0.59) */
float COCurve[3] = {2.3,0.72,-0.34};  //  data format:{ x, y, slope}; point1: (lg200, 0.72), point2: (lg10000,  0.15)
float SmokeCurve[3] ={2.3,0.53,-0.44};  //  data format:{ x, y, slope}; point1: (lg200, 0.53), point2: (lg10000,  -0.22)
float Ro = 10;  //  Ro is initialized to 10 kilo ohms


void setup() {
  Serial.begin(115200);
  pinMode(temperatureSensor,INPUT);
  pinMode(humiditySensor,INPUT);
  pinMode(rainSensor, INPUT);

  Serial.print("Calibrating...\n");
  /*Calibrating the sensor. Please make sure the sensor is in clean air when you
  perform the calibration */
  Ro = MQCalibration(MQ_PIN);  Serial.print("Calibration is done...\n");
  Serial.print("Ro=");
  Serial.print(Ro);
  Serial.print("kohm");
  Serial.print("\n");
}


void loop() {
  tweetMessage(); // Tweet the Weather Update
  delay(900000);  //  1.5 hour delay

//  Manual Type-casting for sensor readings
char *dtostrf (double val, signed char width, unsigned char prec, char *sout)
{
  char fmt[100];
  sprintf(fmt, "%%%d.%df", width, prec);
  sprintf(sout, fmt, val);
  return sout;
}

//  Construct the Twitter Message
void tweetMessage() {
  Twitter twitter("Enter the token here");   // Enter your Twitter Token here

  humidity = getHumidity(); // Check current humidity
  String stringMsg = "Humidity:";
  dtostrf(humidity, 1, 2, tmpHumidity);
  char tmpHumidity[10];
  stringMsg += tmpHumidity;
  stringMsg += "%RH";

  temperature = getTemperature(); // Check current temperature
  stringMsg += "   Temperature:";
  char tmpTemperature[10];
  dtostrf(temperature, 1, 0, tmpTemperature);
  stringMsg += tmpTemperature;
  stringMsg += "°C";

  gas = getGas(); // Check CO levels
  stringMsg += "  CO level:";
  char tempGas[10];
  dtostrf(gas,1,2,tempGas);
  stringMsg += tempGas;
  stringMsg += "ppm";

  if(digitalRead(rainSensor)==HIGH) //  Check if it's raining
  {
    stringMsg += " Rain Alert";
  }

  stringMsg += " #City #State #Country #Weather"; //  Add location tags

  char msg[140];  //  Convert the message to a character array
  stringMsg.toCharArray(msg, 140);  //  Twiiter Character Limit. Converts/limits message to 140 characters.

  //  Post the message and check for errors
  if (twitter.post(msg))
  {
    int status = twitter.wait();
    if (status == 200)
    {
      Serial.println("OK.");
      Serial.println("Message Tweeted");
    }
    else
    {                                  //Connection Test
      Serial.print("failed : code ");
      Serial.println("Message not  Tweeted");
      Serial.println(status);
    }
  }
  else
  {
    Serial.println("connection failed.");
    Serial.println("Message not  Tweeted");
  }
}
