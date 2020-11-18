/*
 Name:		CupLabellingMachine.ino
 Created:	21.08.2020 13:23:28
 Author:	mariu
*/

// the setup function runs once when you press reset or power the board
#include "Ultrasonicsensor.h"
#include "PINS.h"
#include "TuchDisplay.h"


int buttonState = LOW;         // variable for reading the pushbutton status

void setup() {
	Serial.begin(9600);
	Ultrasonicsensor.init(TRIG_PIN_defined, ECHO_PIN_defined);
	TuchDisplay.init();
	pinMode(Labelengine_RelaisTrigger, OUTPUT);
  pinMode(Pneumaticcylinder_1, OUTPUT);
  pinMode(Pneumaticcylinder_2, OUTPUT);
	pinMode(ledRedPin, OUTPUT);
	pinMode(ButtonGrenn, INPUT);
	pinMode(InfrarotsensorPin, INPUT);
}

// the loop function runs over and over again until power down or reset
void loop() {
	TuchDisplay.runTouch();
	
	Ultrasonicsensor.measure(); //Uncomment for use with 
	Serial.print("Abstand: ");
	Serial.print(Ultrasonicsensor.cm);
	buttonState = digitalRead(ButtonGrenn);

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (TuchDisplay.etikett_aufziehen == true) {
    // turn LED on:
    digitalWrite(Labelengine_RelaisTrigger, LOW);
  } else {
    // turn LED off:
    digitalWrite(Labelengine_RelaisTrigger, HIGH);
  }
  
	if (Ultrasonicsensor.cm <= 3) 
	{
		Serial.println("Etikett da");
		delay(TuchDisplay.nachlauf_ultrasonicsensor);//Delay für Glasnachlauf!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
   
		digitalWrite(Labelengine_RelaisTrigger, LOW);//Motor an
    

		//start MOtor
		newPosition = 0;
		while (digitalRead(InfrarotsensorPin)== HIGH)
		{
			//motor rennen lasssen
		}
		delay(TuchDisplay.nachlauf_etikett); //Nachlauf Pause zum einstellen
		digitalWrite(Labelengine_RelaisTrigger, HIGH);	//Stop motor
	}
  

	
}
