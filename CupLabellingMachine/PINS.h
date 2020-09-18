#ifndef _PINS_h
#define _PINS_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

//Ultraschallsensor PINS
const int TRIG_PIN_defined = 7;
const int ECHO_PIN_defined = 8;

//Drehgeber Pins
const int CLK_Drehgeber = 2;//2
const int DT_Drehgeber = 3; //3

// L298N Motor Pin definition
//const unsigned int IN2 = 13;
const unsigned int EN = 11;
//const unsigned int IN1 =12;

//Pins allgemein 
const int ledRedPin = 9;
const int ledGreenPin = 24;

const int ButtonGrenn = 22;



//Variables
long newPosition = 0;
long old_Position = 0;
long Label1Counts = -2000;

#endif
