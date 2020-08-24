// Ultrasonicsensor.h

#ifndef _ULTRASONICSENSOR_h
#define _ULTRASONICSENSOR_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

class UltrasonicsensorClass
{
protected:

public:
	void init(const int TRIG_PIN_, const  int ECHO_PIN_);

	// Pins
	int TRIG_PIN;
	int ECHO_PIN;
	unsigned long t1;

	//Varibles
	unsigned long t2 = NULL;
	unsigned long pulse_width = NULL;
	float cm = NULL;

	void measure();
};

extern UltrasonicsensorClass Ultrasonicsensor;

#endif

