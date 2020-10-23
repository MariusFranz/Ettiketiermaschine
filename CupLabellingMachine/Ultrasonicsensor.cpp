#include "Ultrasonicsensor.h"

void UltrasonicsensorClass::init(const int TRIG_PIN_, const  int ECHO_PIN_)
{
	// The Trigger pin will tell the sensor to range find
	TRIG_PIN = TRIG_PIN_;
	ECHO_PIN = ECHO_PIN_;
	pinMode(TRIG_PIN, OUTPUT);
	digitalWrite(TRIG_PIN, LOW);

	//Set Echo pin as input to measure the duration of 
	//pulses coming back from the distance sensor
	pinMode(ECHO_PIN, INPUT);

}

void UltrasonicsensorClass::measure()
{
	// Hold the trigger pin high for at least 10 us
	digitalWrite(TRIG_PIN, HIGH);
	delayMicroseconds(10);
	digitalWrite(TRIG_PIN, LOW);

	// Wait for pulse on echo pin
	while (digitalRead(ECHO_PIN) == 0);

	// Measure how long the echo pin was held high (pulse width)
	// Note: the micros() counter will overflow after ~70 min
	t1 = micros();
	while (digitalRead(ECHO_PIN) == 1);
	t2 = micros();
	pulse_width = t2 - t1;

	// Calculate distance in centimeters and inches. The constants
	// are found in the datasheet, and calculated from the assumed speed
	//of sound in air at sea level (~340 m/s).
	cm = pulse_width / 58.0;
	//delay(60);
}

UltrasonicsensorClass Ultrasonicsensor;

