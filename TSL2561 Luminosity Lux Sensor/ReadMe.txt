This branch was Created by Jonathan Pereira on 10th November 2015 for the TWIST platform. Open to the public domain.
Learn more about the sensor @ https://learn.adafruit.com/tsl2561/overview



This folder contains the Adafruit Sensor Library & Adafruit TSL2561 Library, code(TSL2561_TWIST) and Schematics, Breadboard view  for the inclusion of the TSL2561 sensor in the TWIST platform. The PCB view for this sensor is not correct.


Connections:
Connect the VCC/Vin pin to a 3.3V or 5v power source.
Note: Currently shipping sensors have a 3.3v regulator built-in.  If you have an older version of the sensor that does not have the voltage regulator, it cannot be used with anything higher than 3.3V!
Connect GND to the ground pin.
Connect the i2c SCL clock pin to your i2c clock pin. 
Connect the i2c SDA data pin to your i2c data pin.
Unfortunately, the i2c lines on most microcontrollers are fixed so you're going to have to stick with those pins

You may be wondering, how is it OK to connect a 3.3V chip like the TSL2561 to 5.0V data pins like the Arduino? Isn't that bad? Well, in this specific case its OK. I2c uses pullup lines to the 3.3V power pin, so the data is actually being sent at 3.3V. As long as all the sensors/device on the i2c bus are running on 3.3V power, we're fine. However, don't use a 5.0v powered i2c device (like the DS1307) with pullups at the same time as a 3.3V device like the TSL2561! If you want to use this sensor with a datalogger that uses the DS1307, remove any/all of the pullup resistors from the DS1307 SDA/SCL pins. The pullups built into the TSL2561 will then be active and keep the voltage at 3.3V which is safe for both the RTC and the sensor.

You don't need to connect the ADDR (i2c address change) or INT (interrupt output) pins.
The ADDR pin can be used if you have an i2c address conflict, to change the address. Connect it to ground to set the address to 0x29, connect it to 3.3V (vcc) to se t the address to 0x49 or leave it floating (unconnected) to use address 0x39.
The INT pin is an ouput from the sensor used when you have the sensor configured to signal when the light level has changed. We don't have that code written in this tutorial so you don't have to use it. If you do end up using it, use a 10K-100K pullup from INT to 3.3V (vcc/vin)


Read the ReadMe files in the library and code files too.