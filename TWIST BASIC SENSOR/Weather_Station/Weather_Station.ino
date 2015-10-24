#include <SPI.h>
#include <Ethernet.h>
#include <Twitter.h>
#include <stdlib.h>
float thermsen = A0;
float humidsen = A1;
int rainsen = 2;
int indicator=13;

#define         MQ_PIN                       (2)     //define which analog input channel you are going to use
#define         RL_VALUE                     (4.7)     //define the load resistance on the board, in kilo ohms
#define         RO_CLEAN_AIR_FACTOR          (9.83)  //RO_CLEAR_AIR_FACTOR=(Sensor resistance in clean air)/RO,
                                                     //which is derived from the chart in datasheet
 
/***********************Software Related Macros************************************/
#define         CALIBARAION_SAMPLE_TIMES     (50)    //define how many samples you are going to take in the calibration phase
#define         CALIBRATION_SAMPLE_INTERVAL  (500)   //define the time interal(in milisecond) between each samples in the
                                                     //cablibration phase
#define         READ_SAMPLE_INTERVAL         (50)    //define how many samples you are going to take in normal operation
#define         READ_SAMPLE_TIMES            (5)     //define the time interal(in milisecond) between each samples in 
                                                     //normal operation
 
/**********************Application Related Macros**********************************/
#define         GAS_LPG                      (0)
#define         GAS_CO                       (1)
#define         GAS_SMOKE                    (2)
 
/*****************************Globals***********************************************/
float           LPGCurve[3]  =  {2.3,0.21,-0.47};   //two points are taken from the curve. 
                                                    //with these two points, a line is formed which is "approximately equivalent"
                                                    //to the original curve. 
                                                    //data format:{ x, y, slope}; point1: (lg200, 0.21), point2: (lg10000, -0.59) 
float           COCurve[3]  =  {2.3,0.72,-0.34};    //two points are taken from the curve. 
                                                    //with these two points, a line is formed which is "approximately equivalent" 
                                                    //to the original curve.
                                                    //data format:{ x, y, slope}; point1: (lg200, 0.72), point2: (lg10000,  0.15) 
float           SmokeCurve[3] ={2.3,0.53,-0.44};    //two points are taken from the curve. 
                                                    //with these two points, a line is formed which is "approximately equivalent" 
                                                    //to the original curve.
                                                    //data format:{ x, y, slope}; point1: (lg200, 0.53), point2: (lg10000,  -0.22)                                                     
float           Ro           =  10;                 //Ro is initialized to 10 kilo ohms
 

void setup() {
  Serial.begin(115200);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(2, INPUT);
  pinMode(13,OUTPUT);
 /**********************************************************/
  Serial.print("Calibrating...\n");                
  Ro = MQCalibration(MQ_PIN);                       //Calibrating the sensor. Please make sure the sensor is in clean air 
                                                    //when you perform the calibration                    
  Serial.print("Calibration is done...\n"); 
  Serial.print("Ro=");
  Serial.print(Ro);
  Serial.print("kohm");
  Serial.print("\n");
}


void loop() {
  tweetMessage();
  delay(900000);
}
//Manual Type-casting for sensor readings
char *dtostrf (double val, signed char width, unsigned char prec, char *sout) 
{
  char fmt[100];
  sprintf(fmt, "%%%d.%df", width, prec);
  sprintf(sout, fmt, val);
  return sout;
}
//Twitter Message
void tweetMessage() {
  Twitter twitter("Enter the token here");   //Twitter Token

  humidity();
  float humid;
  //Twitter message
  String stringMsg = "Humidity:";
  char tmp[10];
  dtostrf(humid, 1, 2, tmp);
  stringMsg += tmp;
  stringMsg += "%RH";

  temp_now();
  int Temperature;
  //Twitter message
  stringMsg += "   Temperature:";
  char nowtemp[10];
  dtostrf(Temperature, 1, 0, nowtemp);
  stringMsg += nowtemp;
  stringMsg += "°C";

   MQ2printval();
   float MQ2tweet;
  //Twitter message
  stringMsg += "  CO level:";
  char nowMQ2[10];
  dtostrf(MQ2tweet,1,2,nowMQ2);
  stringMsg += nowMQ2;
  stringMsg += "ppm";

    if(digitalRead(2)==HIGH)
  {
    stringMsg += " Rain Alert";
  }
  

  
  stringMsg += " #Betatesting #raintest  #IOTweatherstation #Mumbai #Bandra #CarterRoad ";

  //Convert our message to a character array  //Twiiter Character Limit. Converts/limits message to 140 characters.
  char msg[140];
  stringMsg.toCharArray(msg, 140);

  //Tweet that sucker!
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
    digitalWrite(13,HIGH);// LED Indicator Feedback Code Working.

}
/********Serial print MQ2 Value****************/
void MQ2printval()
{
   float MQ2tweet= (MQGetGasPercentage(MQRead(MQ_PIN)/Ro,GAS_LPG));
   Serial.print("LPG:"); 
   Serial.print(MQGetGasPercentage(MQRead(MQ_PIN)/Ro,GAS_LPG) );
   Serial.print( "ppm" );
   Serial.print("    ");   
   Serial.print("CO:"); 
   Serial.print(MQGetGasPercentage(MQRead(MQ_PIN)/Ro,GAS_CO) );
   Serial.print( "ppm" );
   Serial.print("    ");   
   Serial.print("SMOKE:"); 
   Serial.print(MQGetGasPercentage(MQRead(MQ_PIN)/Ro,GAS_SMOKE) );
   Serial.print( "ppm" );
   Serial.print("\n");
}

/****************** MQResistanceCalculation ****************************************
Input:   raw_adc - raw value read from adc, which represents the voltage
Output:  the calculated sensor resistance
Remarks: The sensor and the load resistor forms a voltage divider. Given the voltage
         across the load resistor and its resistance, the resistance of the sensor
         could be derived.
************************************************************************************/ 
float MQResistanceCalculation(int raw_adc)
{
  return ( ((float)RL_VALUE*(1023-raw_adc)/raw_adc));
}
 
/***************************** MQCalibration ****************************************
Input:   mq_pin - analog channel
Output:  Ro of the sensor
Remarks: This function assumes that the sensor is in clean air. It use  
         MQResistanceCalculation to calculates the sensor resistance in clean air 
         and then divides it with RO_CLEAN_AIR_FACTOR. RO_CLEAN_AIR_FACTOR is about 
         10, which differs slightly between different sensors.
************************************************************************************/ 
float MQCalibration(int mq_pin)
{
  int i;
  float val=0;
 
  for (i=0;i<CALIBARAION_SAMPLE_TIMES;i++) {            //take multiple samples
    val += MQResistanceCalculation(analogRead(mq_pin));
    delay(CALIBRATION_SAMPLE_INTERVAL);
  }
  val = val/CALIBARAION_SAMPLE_TIMES;                   //calculate the average value
 
  val = val/RO_CLEAN_AIR_FACTOR;                        //divided by RO_CLEAN_AIR_FACTOR yields the Ro 
                                                        //according to the chart in the datasheet 
 
  return val; 
}
/*****************************  MQRead *********************************************
Input:   mq_pin - analog channel
Output:  Rs of the sensor
Remarks: This function use MQResistanceCalculation to caculate the sensor resistenc (Rs).
         The Rs changes as the sensor is in the different consentration of the target
         gas. The sample times and the time interval between samples could be configured
         by changing the definition of the macros.
************************************************************************************/ 
float MQRead(int mq_pin)
{
  int i;
  float rs=0;
 
  for (i=0;i<READ_SAMPLE_TIMES;i++) {
    rs += MQResistanceCalculation(analogRead(mq_pin));
    delay(READ_SAMPLE_INTERVAL);
  }
 
  rs = rs/READ_SAMPLE_TIMES;
 
  return rs;  
}
 
/*****************************  MQGetGasPercentage **********************************
Input:   rs_ro_ratio - Rs divided by Ro
         gas_id      - target gas type
Output:  ppm of the target gas
Remarks: This function passes different curves to the MQGetPercentage function which 
         calculates the ppm (parts per million) of the target gas.
************************************************************************************/ 
int MQGetGasPercentage(float rs_ro_ratio, int gas_id)
{
  if ( gas_id == GAS_LPG ) {
     return MQGetPercentage(rs_ro_ratio,LPGCurve);
  } else if ( gas_id == GAS_CO ) {
     return MQGetPercentage(rs_ro_ratio,COCurve);
  } else if ( gas_id == GAS_SMOKE ) {
     return MQGetPercentage(rs_ro_ratio,SmokeCurve);
  }    
 
  return 0;
}
 
/*****************************  MQGetPercentage **********************************
Input:   rs_ro_ratio - Rs divided by Ro
         pcurve      - pointer to the curve of the target gas
Output:  ppm of the target gas
Remarks: By using the slope and a point of the line. The x(logarithmic value of ppm) 
         of the line could be derived if y(rs_ro_ratio) is provided. As it is a 
         logarithmic coordinate, power of 10 is used to convert the result to non-logarithmic 
         value.
************************************************************************************/ 
int  MQGetPercentage(float rs_ro_ratio, float *pcurve)
{
  return (pow(10,( ((log(rs_ro_ratio)-pcurve[1])/pcurve[2]) + pcurve[0])));
}
/******Humidity***********/
void humidity()
{
  int humidSensorValue = analogRead(A1);
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  // Multiply by 1000 so that map() function can work properly. map() does not count numbers after the decimal.
  float humidvoltage = humidSensorValue * (5.0 / 1023.0) * 1000;
  // When Humidity is 20%RH Voltage is 660mV. When Humidity is 95%RH Voltage is 3135mV.
  float humid = map(humidvoltage, 660, 3135, 20, 95);
  // print out the value of humidity:
    Serial.print("Humidity:");  
  Serial.print(humid);
  Serial.println();
  
}

/**************Temperature*************/
void temp_now()
{
  float tempSensorValue = analogRead(A0);
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  float voltage = tempSensorValue * (5.0 / 1023.0);
  // print out the value you read:
  //Serial.print("Voltage(V)=  ");
  //Serial.print(voltage);
  //Serial.println();
  int Temperature;
  if ((voltage > 2.521) && (voltage < 2.585))
  {
    Temperature = 0;

  }
  if ((voltage > 2.585) && (voltage < 2.648))
  {
    Temperature = 1 ;
  }
  if ((voltage > 2.648) && (voltage < 2.711))
  {
    Temperature = 2;

  }
  if ((voltage > 2.711) && (voltage < 2.773))
  {
    Temperature = 3;
    ;
  }
  if ((voltage > 2.773) && (voltage < 2.834))
  {
    Temperature = 4;
  }
  if ((voltage > 2.834) && (voltage < 2.894))
  {
    Temperature = 5;

  }
  if ((voltage > 2.894) && (voltage < 2.95))
  {
    Temperature = 6;

  }
  if ((voltage > 2.95) && (voltage < 3.01))
  {
    Temperature = 7;

  }
  if ((voltage > 3.01) && (voltage < 3.07))
  {
    Temperature = 8;

  }
  if ((voltage > 3.07) && (voltage < 3.13))
  {
    Temperature = 9;

  }
  if ((voltage > 3.13) && (voltage < 3.18))
  {
    Temperature = 10;

  }
  if ((voltage > 3.18) && (voltage < 3.24))
  {
    Temperature = 11;

  }
  if ((voltage > 3.24) && (voltage < 3.29))
  {
    Temperature = 12;

  }
  if ((voltage > 3.29) && (voltage < 3.34))
  {
    Temperature = 13;
  }
  if ((voltage > 3.34) && (voltage < 3.40))
  {
    Temperature = 14;

  }
  if ((voltage > 3.40) && (voltage < 3.45))
  {
    Temperature = 15;

  }
  if ((voltage > 3.45) && (voltage < 3.5))
  {
    Temperature = 16;

  }
  if ((voltage > 3.5) && (voltage < 3.54))
  {
    Temperature = 17;

  }
  if ((voltage > 3.54) && (voltage < 3.59))
  {
    Temperature = 18;

  }
  if ((voltage > 3.59) && (voltage < 3.64))
  {
    Temperature = 19;

  }
  if ((voltage > 3.64) && (voltage < 3.68))
  {
    Temperature = 20;

  }
  if ((voltage > 3.68) && (voltage < 3.72))
  {
    Temperature = 21;

  }
  if ((voltage > 3.72) && (voltage < 3.76))
  {
    Temperature = 22;

  }
  if ((voltage > 3.76) && (voltage < 3.81))
  {
    Temperature = 23;

  }
  if ((voltage > 3.81) && (voltage < 3.85))
  {
    Temperature = 24;

  }
  if ((voltage > 3.85) && (voltage < 3.88))
  {
    Temperature = 25;

  }
  if ((voltage > 3.88) && (voltage < 3.92))
  {
    Temperature = 26;

  }
  if ((voltage > 3.92) && (voltage < 3.96))
  {
    Temperature = 27;

  }
  if ((voltage > 3.96) && (voltage < 3.99))
  {
    Temperature = 28;

  }
  if ((voltage > 3.99) && (voltage < 4.03))
  {
    Temperature = 29;

  }
  if ((voltage > 4.03) && (voltage < 4.06))
  {
    Temperature = 30;

  }
  if ((voltage > 4.06) && (voltage < 4.09))
  {
    Temperature = 31;

  }
  if ((voltage > 4.09) && (voltage < 4.12))
  {
    Temperature = 32;

  }
  if ((voltage > 4.12) && (voltage < 4.15))
  {
    Temperature = 33;

  }
  if ((voltage > 4.15) && (voltage < 4.18))
  {
    Temperature = 34;

  }
  if ((voltage > 4.18) && (voltage < 4.21))
  {
    Temperature = 35;

  }
  if ((voltage > 4.21) && (voltage < 4.24))
  {
    Temperature = 36;

  }
  if ((voltage > 4.24) && (voltage < 4.26))
  {
    Temperature = 37;
  }
  if ((voltage > 4.26) && (voltage < 4.29))
  {
    Temperature = 38;

  }
  if ((voltage > 4.29) && (voltage < 4.31))
  {
    Temperature = 39;

  }
  if ((voltage > 4.31) && (voltage < 4.34))
  {
    Temperature = 40;

  }
  if ((voltage > 4.34) && (voltage < 4.36))
  {
    Temperature = 41;

  }
  if ((voltage > 4.36) && (voltage < 4.38))
  {
    Temperature = 42;

  }
  if ((voltage > 4.38) && (voltage < 4.4))
  {
    Temperature = 43;
    
  }
  if ((voltage > 4.4) && (voltage < 4.42))
  {
    Temperature = 44;

  }
  if ((voltage > 4.42) && (voltage < 4.44))
  {
    Temperature = 45;

  }
  if ((voltage > 4.44) && (voltage < 4.46))
  {
    Temperature = 46;

  }
  if ((voltage > 4.46) && (voltage < 4.48))
  {
    Temperature = 47;

  }
  if ((voltage > 4.48) && (voltage < 4.5))
  {
    Temperature = 48;

  }
  if ((voltage > 4.5) && (voltage < 4.51))
  {
    Temperature = 49;

  }
  if ((voltage > 4.51) && (voltage < 4.52))
  {
    Temperature = 50;

  }
  Serial.print("Temperature:");  
  Serial.print(Temperature);
  Serial.println();
  

}
