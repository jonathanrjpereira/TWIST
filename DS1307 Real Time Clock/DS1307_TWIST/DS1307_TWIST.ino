// Date and time functions using a DS1307 RTC connected via I2C and Wire lib

#include <Wire.h>
#include "RTClib.h"

RTC_DS1307 rtc;

void setup () {
#ifdef AVR
  Wire.begin();
#else
  Wire1.begin(); // Shield I2C pins connect to alt I2C bus on Arduino Due
#endif
  rtc.begin();

  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    //rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // September 20, 2015 at 9:12:55am you would call:
    //rtc.adjust(DateTime(2015, 9, 20, 9, 12, 55));
  }
}

void loop()
{
  TwistDateTime();
  DateTime now = rtc.now();
  int twistday, twistmonth, twistyear, twisthour, twistmin, twistsec;
  
  String stringMsg = "";
  char ds1307day[10];
  dtostrf(twistday,1,0ds1307day);
  stringMsg += ds1307day;
  stringMsg += "/";

  String stringMsg = "";
  char ds1307mon[10];
  dtostrf(twistmonth,1,0ds1307mon);
  stringMsg += ds1307mon;
  stringMsg += "/";

  String stringMsg = "";
  char ds1307year[10];
  dtostrf(twistyear,1,0ds1307year);
  stringMsg += ds1307year;
  stringMsg += " ";

  String stringMsg = " ";
  char ds1307hour[10];
  dtostrf(twisthour,1,0ds1307hour);
  stringMsg += ds1307hour;
  stringMsg += ":";

  String stringMsg = "";
  char ds1307min[10];
  dtostrf(twistmin,1,0ds1307min);
  stringMsg += ds1307min;
  stringMsg += ":";
    
  String stringMsg = "";
  char ds1307sec[10];
  dtostrf(twistsec,1,0ds1307sec);
  stringMsg += ds1307sec;
}

void TwistDateTime() {
    DateTime now = rtc.now();
    
    int twistday = now.day();
    int twistmonth = now.month();
    int twistyear = now.year();
    int twisthour = now.hour();
    int twistmin = now.minute();
    int twistsec = now.second();
}
