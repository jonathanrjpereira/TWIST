/* 	Twist.h - Library for the TWIST platform.
   	Created Jonathan Pereira. Beta Start: 5th November 2015.
	Released into public domain as a Beta Test & not for application or implementation.
*/

#ifndef Twist_h
#define Twist_h

#include "Arduino.h"

class Ldr
{
	public:
		Ldr(int ldrpin);
		void ldr();
	private:
		int _ldr
};

#endif
			   