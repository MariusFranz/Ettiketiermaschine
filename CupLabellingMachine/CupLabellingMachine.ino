/*
 Name:		CupLabellingMachine.ino
 Created:	21.08.2020 13:23:28
 Author:	mariu
*/

// the setup function runs once when you press reset or power the board
#include <L298N.h>
#include <Encoder.h>
#include "Ultrasonicsensor.h"
#include "PINS.h"


Encoder Drehgeber_Class(CLK_Drehgeber, DT_Drehgeber);
//L298N Labelmotor(EN, IN1, IN2);

int buttonState = 0;         // variable for reading the pushbutton status

void setup() {
	Serial.begin(9600);
	Ultrasonicsensor.init(TRIG_PIN_defined, ECHO_PIN_defined);
	//Labelmotor.setSpeed(255);
	pinMode(EN, OUTPUT);
	pinMode(ledGreenPin, OUTPUT);
	pinMode(ledRedPin, OUTPUT);
  pinMode(ButtonGrenn, INPUT);
}

// the loop function runs over and over again until power down or reset
void loop() {
	
	Ultrasonicsensor.measure();
	Serial.print("Abstand: ");
	Serial.print(Ultrasonicsensor.cm);
	//digitalWrite(ledGreenPin, LOW);
	//digitalWrite(ledGreenPin, HIGH);
  buttonState = digitalRead(ButtonGrenn);

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
    // turn LED on:
    digitalWrite(ledGreenPin, LOW);
  } else {
    // turn LED off:
    digitalWrite(ledGreenPin, HIGH);
  }
  
	if (Ultrasonicsensor.cm <= 3) 
	{
		//digitalWrite(ledGreenPin, LOW);
		//digitalWrite(ledRedPin, LOW);
		delay(500);

		old_Position = Drehgeber_Class.readAndReset();
		Serial.print("Drehgeber start value: ");
		Serial.print(old_Position);
		//start MOtor
		newPosition = 0;
		while (newPosition >= Label1Counts)
		{
			newPosition = Drehgeber_Class.read();
			Serial.print("  drehgeber value: ");
			Serial.print(newPosition);
			digitalWrite(ledGreenPin, LOW);
			//Labelmotor.forward();
			//motor rennen lasssen
		}
		digitalWrite(ledGreenPin, HIGH);
		//Labelmotor.stop();
		//Stop motor
	}
  

	
}
