/* 	Twist.h - Library for the TWIST platform.
   	Created Jonathan Pereira. Beta Start: 5th November 2015.
	Released into public domain as a Beta Test & not for application or implementation.
*/

#include "Arduino.h"
#include "Twist.h"

Ldr::Ldr(int ldrpin)
{
	pinMode(ldrpin,INPUT);
	_ldr = ldrpin;
}

void Ldr::ldr()
{
	if(digitalRead(ldrpin)==HIGH)
	Serial.println("Light");
	else
	Serial.println("No light");
}