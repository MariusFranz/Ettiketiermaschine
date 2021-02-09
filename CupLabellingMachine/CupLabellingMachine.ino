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
volatile unsigned long currenttime = 0;
volatile unsigned long previoustime_ultrasonicsensor = 0;
unsigned long previoustime_nachlauflabel = 0;
bool ultrasonicstatus_glasda = false;
volatile bool aufziehmotor_status = false;
volatile bool etikettluecke_war_da = false;
bool glas_halten = false;
bool glas_gehen_lasen = false; 
bool glas_nachholen = false;
unsigned long previoustime_glashalten = 0;
volatile bool laserschranke_glas_da = false;

void setup() {
  Serial.begin(9600);
  Ultrasonicsensor.init(TRIG_PIN_defined, ECHO_PIN_defined);
  TuchDisplay.init();
  pinMode(Labelengine_RelaisTrigger, OUTPUT);
  pinMode(Pneumaticcylinder_1, OUTPUT);
  pinMode(Pneumaticcylinder_2, OUTPUT);
  pinMode(ledRedPin, OUTPUT);
  pinMode(ButtonGrenn, INPUT);
  pinMode(InfrarotsensorPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(InfrarotsensorPin), blink, CHANGE);
  pinMode(LaserschrankePin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(LaserschrankePin), lichtschranke_glas_loop, CHANGE);
}

// the loop function runs over and over again until power down or reset
void loop() {
  currenttime = millis();
  TuchDisplay.runTouch();
  /**
  if (ultrasonicstatus_glasda == false)
  {
    Ultrasonicsensor.measure(); 
    //Serial.print("Abstand: ");
    //Serial.print(Ultrasonicsensor.cm);
  }
  
  if (Ultrasonicsensor.cm <= 3)
  {
    ultrasonicstatus_glasda = true;
    //Serial.println("Etikett da");
  }

  **/
  if (laserschranke_glas_da == true){
    Serial.println(currenttime);
  }
  
  //delay(TuchDisplay.nachlauf_ultrasonicsensor);//Delay für Glasnachlauf!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  //if (currenttime - previoustime_ultrasonicsensor >= TuchDisplay.nachlauf_ultrasonicsensor && ultrasonicstatus_glasda == true) {
  if (currenttime - previoustime_ultrasonicsensor >= TuchDisplay.nachlauf_ultrasonicsensor && laserschranke_glas_da == true && aufziehmotor_status == false) {
    Serial.println("Motor an");
    Serial.println("time ");
    Serial.println(currenttime);
    previoustime_ultrasonicsensor = currenttime;
    digitalWrite(Labelengine_RelaisTrigger, LOW);//Motor an
    aufziehmotor_status = true;
    laserschranke_glas_da = false;
  }
  /**if (digitalRead(InfrarotsensorPin) == LOW && aufziehmotor_status == true) //while (digitalRead(InfrarotsensorPin)== HIGH motor an
  {
    etikettluecke_war_da = true;
  }**/
  if (currenttime - previoustime_ultrasonicsensor >= TuchDisplay.nachlauf_etikett && etikettluecke_war_da == true && aufziehmotor_status == true)
  {
    Serial.println("Motor aus");
    Serial.println("time ");
    Serial.println(currenttime);
    previoustime_ultrasonicsensor = currenttime;
    digitalWrite(Labelengine_RelaisTrigger, HIGH);  //Stop motor
    etikettluecke_war_da = false;
    aufziehmotor_status = false;
    //ultrasonicstatus_glasda = false;
    laserschranke_glas_da = false;
  }
  //delay(TuchDisplay.nachlauf_etikett); //Nachlauf Pause zum einstellen



//Penmatikzylinder ablauf

  if ( glas_halten == false && glas_nachholen == false && glas_gehen_lasen == false)//anfangszustand nach start
  {
    if (currenttime - previoustime_glashalten >= 1000) // Am Anfang 1 sec länger warten
    {
      glas_nachholen = true;
      previoustime_glashalten = currenttime;
    }
  } 
  
  if (glas_nachholen == true && currenttime - previoustime_glashalten>= 2000) //zeit glas gehen lassen aus lücke
  {
    digitalWrite(Pneumaticcylinder_1, HIGH);//Zylinder ausfahren
    digitalWrite(Pneumaticcylinder_2, LOW);//Zylinder einfahren
    glas_nachholen = false;
    glas_halten = true;
    previoustime_glashalten = currenttime;    
  }
  if (glas_halten == true && currenttime - previoustime_glashalten >= 2000) //zeit glas um in die lücke aufzuschliessen
  {
    digitalWrite(Pneumaticcylinder_1, HIGH);//Zylinder ausfahren
    digitalWrite(Pneumaticcylinder_2, HIGH);//Zylinder ausfahren
    glas_halten = false;
    previoustime_glashalten = currenttime; 
    glas_gehen_lasen = true;
  }
  if (glas_gehen_lasen == true && currenttime - previoustime_glashalten>= 2000) //zeit glas halten
  {
    digitalWrite(Pneumaticcylinder_1, LOW);//Zylinder einfahren
    glas_gehen_lasen = false;
    glas_nachholen = true;
    previoustime_glashalten = currenttime; 
  }




   
}

void lichtschranke_glas_loop()
{
  if ( laserschranke_glas_da == false )
  {
    laserschranke_glas_da = true;
    previoustime_ultrasonicsensor = currenttime;
  }
}

void blink() {
  if (aufziehmotor_status == true)
  {
    etikettluecke_war_da = true;
    previoustime_ultrasonicsensor = currenttime;
  }

}
