#ifndef _PINS_h
#define _PINS_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

//Ultraschallsensor PINS
const int TRIG_PIN_defined = 45;//7
const int ECHO_PIN_defined = 46;//8

//Drehgeber Pins
const int CLK_Drehgeber = 38;//2
const int DT_Drehgeber = 39; //3


//Pins allgemein 
const int ledRedPin = 25;//9
const int Labelengine_RelaisTrigger = 24; //PIN for Relais Motor  //4

const int ButtonGrenn = 22;
const int InfrarotsensorPin = 44;




//Variables
long newPosition = 0;
long old_Position = 0;
long Label1Counts = -1950;



#endif
