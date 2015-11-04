This branch was Created by Jonathan Pereira on 4th November 2015 for the TWIST platform. Open to the public domain.
Shoutout to Instructables Member: Scribble73 for requesting the DHT11 sensors inclusion in this repository.


This folder contains the library(DHT11 Library), code(DHT11_TWIST) and Schematics, Breadboard view and PCB Layout for the inclusion of the DHT11 sensor in the TWIST platform.


Connections:
DHT11 has four pins:
Pin1:VCC (3 to 5V power)
Pin2:Data out
Pin3:Not connected
Pin4:Ground

Simply ignore pin 3, its not used. You will want to place a 10K resistor between VCC and the data pin, to act as a medium-strength pull up on the data line.
This diagram shows how we will connect for the testing sketch. Connect data to pin 3, you can change it later to any pin.


Read the ReadMe files in the library and code files too.