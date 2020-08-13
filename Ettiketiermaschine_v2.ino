// Visual Micro is in vMicro>General>Tutorial Mode
// 
/*
    Name:       Ettiketiermaschine_v2.ino
    Created:	15.06.2020 18:27:56
    Author:     DESKTOP-EJOVTU3\mariu
*/

//third party libraries
#include <Metro.h>
#include <Encoder.h>
//eigene Classes
#include "Drehgeber.h"
#include "Poti_Geschwindigkeit.h"
#include "Einschaltbutton.h"
#include "Ultraschallsensor_v2.h"
#include "BasicStepperDriver.h"

//Poti_Geschwindigkeit Pins
const int CLK_Drehgeber = 2;
const int DT_Drehgeber = 3;
Encoder Drehgeber_Class(CLK_Drehgeber, DT_Drehgeber);

//Poti_Geschwindigkeit Pins
const int CLK_Geschw_Poti = 5;
const int DT_Gesch_Poti = 6;
const int SW_Poti = 0;
boolean status_Pushbutton_Pot;
Encoder Geschw_Poti_Class(CLK_Geschw_Poti, DT_Gesch_Poti);


//Ultraschallsensor PINS
const int TRIG_PIN_defined = 7;
const int ECHO_PIN_defined = 8;

//Pins allgemein 
const int ledRedPin = 9;
const int ledGreenPin = 4;
const int buttonEinschaltenPin = 12;

//Stepper MOtor pins
const int dirPin_definded = 10;
const int stepPin_definded = 11;
BasicStepperDriver stepper(200, dirPin_definded, stepPin_definded);

//TEst metro
int state = HIGH;
Metro ledMetro = Metro(100);

// L298N Motor Pin definition
//const unsigned int EN = 11;
//const unsigned int IN1 =12;
//const unsigned int IN2 = 13;

//globale Variablen
int DrehgeberValueAtStart;


// The setup() function runs once each time the micro-controller starts
void setup()
{
    // initialize serial communication at 9600 bits per second:
    Serial.begin(9600);

    Ultraschallsensor_v2.init(TRIG_PIN_defined, ECHO_PIN_defined);
    Einschaltbutton.init(buttonEinschaltenPin);
    Poti_Geschwindigkeit.init(CLK_Geschw_Poti, DT_Gesch_Poti);
    Drehgeber.init(CLK_Drehgeber, DT_Drehgeber);
    pinMode(ledGreenPin, OUTPUT);
    pinMode(ledRedPin, OUTPUT);
    pinMode(SW_Poti, INPUT);

    stepper.begin(600, 1);
    //digitalWrite(dirPin_definded, HIGH);
}

// Add the main program code into the continuous loop() function
void loop()
{
    //IF machine is turned on: 
    //Serial.println("Maschine ist ausgeschlatet :(  ");
    Einschaltbutton.checkstatus();
    stepper.enable();
    // energize coils - the motor will hold position
    if (ledMetro.check() == 1) { // check if the metro has passed its interval .
        if (state == HIGH)  state = LOW;
        else state = HIGH;
        digitalWrite(ledRedPin, state);
        //digitalWrite(stepPin_definded, state);
        //stepper.enable();
        //stepper.move(1);
        //stepper.enable();
    }

    status_Pushbutton_Pot = digitalRead(0);
    Poti_Geschwindigkeit.measure(Geschw_Poti_Class);
    //Serial.println("Status Pushbutton: ");
    //Serial.println(status_Pushbutton_Pot);

    //Serial.println("Status Poti: ");
    Serial.println(Poti_Geschwindigkeit.currentPotiwert);


    while (HIGH == Einschaltbutton.machine_state )
    {
        stepper.enable();
        //Grüne LED anschalten
        digitalWrite(ledGreenPin, 255);
        //Serial.print("Maschine ist eingeschlatet :)  ");
        Poti_Geschwindigkeit.measure(Geschw_Poti_Class);
        Drehgeber.measure(Drehgeber_Class);
		Ultraschallsensor_v2.measure();
		// read the input on analog pin 0:
		//int sensorValue = analogRead(A0);
		// print out the value you read:
		//int engine_speed = sensorValue / 4;
		//Serial.print("Engine Speed Poti_Wert: ");
		//Serial.println(engine_speed);
		//motor.setSpeed(engine_speed);

		if (Ultraschallsensor_v2.cm < 3)
		{
			//motor.forward();
            //Rote LED anschalten
            digitalWrite(ledRedPin, 255);
            DrehgeberValueAtStart = Drehgeber.currentPosition;
            //stepper.rotate(1);
            //stepper.begin(1, 1);
            //stepper.move(1);
            while (Drehgeber.currentPosition <(DrehgeberValueAtStart + 100))
            {
                Drehgeber.measure(Drehgeber_Class);
                stepper.move(1);
                delay(1);

            }
            

		}
		else if (Ultraschallsensor_v2.cm > 3)
		{
			//motor.stop();
            //Rote LED ausschalten
            digitalWrite(ledRedPin, 0);
            //stepper.begin(60, 1);
		}

        



        Serial.println("Potiwert: ");
        Serial.print(Drehgeber.currentPosition);
    }

}
