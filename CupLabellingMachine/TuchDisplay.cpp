#include "TuchDisplay.h"

void TuchDisplayClass::init()
{
	tft.reset();
	
	tft.begin(0x9341);
	tft.setRotation(2);
	tft.fillScreen(BLACK);
	tft.setCursor(0, 0);

  /**new**/
  tft.setCursor(0, 20);
  tft.setTextColor(GREEN);
  tft.setTextSize(2);
  tft.println("Glas Nachlauf");
  tft.setCursor(200, 25);
  tft.setTextSize(1);
  tft.println("[ms]");
  tft.drawRect(BOXSIZE*1, BOXSIZE*2, BOXSIZE, BOXSIZE, WHITE); //Box Minus
  tft.drawRect(BOXSIZE*4, BOXSIZE*2, BOXSIZE, BOXSIZE, WHITE); //Box Plus
  tft.setCursor(BOXSIZE*1+12, BOXSIZE*2+10);
  tft.setTextColor(WHITE);
  tft.setTextSize(3);
  tft.println("-");
  tft.setCursor(BOXSIZE*4+12, BOXSIZE*2+10);
  tft.setTextColor(WHITE);
  tft.setTextSize(3);
  tft.println("+");
  tft.setCursor(BOXSIZE*2+15, BOXSIZE*2+10);
  tft.setTextColor(WHITE);
  tft.setTextSize(3);
  tft.println(nachlauf_ultrasonicsensor);
  /**new**/  
	
	tft.setCursor(0, 150);
	tft.setTextColor(GREEN);
	tft.setTextSize(2);
	tft.println("Etikett Nachlauf");
	tft.setCursor(200, 155);
	tft.setTextSize(1);
	tft.println("[ms]");
	tft.drawRect(BOXSIZE*1, BOXSIZE*5, BOXSIZE, BOXSIZE, WHITE); //Box Minus
	tft.drawRect(BOXSIZE*4, BOXSIZE*5, BOXSIZE, BOXSIZE, WHITE); //Box Plus
	tft.setCursor(BOXSIZE*1+12, BOXSIZE*5+10);
	tft.setTextColor(WHITE);
	tft.setTextSize(3);
	tft.println("-");
	tft.setCursor(BOXSIZE*4+12, BOXSIZE*5+10);
	tft.setTextColor(WHITE);
	tft.setTextSize(3);
	tft.println("+");
	tft.setCursor(BOXSIZE*2+15, BOXSIZE*5+10);
	tft.setTextColor(WHITE);
	tft.setTextSize(3);
	tft.println(nachlauf_etikett);
		
	
	currentcolor = BLACK;
	
	pinMode(13, OUTPUT);
}

void TuchDisplayClass::runTouch()
{

	digitalWrite(13, HIGH);
	TSPoint p = ts.getPoint();
	digitalWrite(13, LOW);
	
	// if sharing pins, you'll need to fix the directions of the touchscreen pins
	//pinMode(XP, OUTPUT);
	pinMode(XM, OUTPUT);
	pinMode(YP, OUTPUT);
	//pinMode(YM, OUTPUT);
	// we have some minimum pressure we consider 'valid'
	// pressure of 0 means no pressing!


	if (p.z > MINPRESSURE && p.z < MAXPRESSURE) { //Touchscreen wird irgendwo gedr�ckt
		/*
		Serial.print("X = "); Serial.print(p.x);
		Serial.print("\tY = "); Serial.print(p.y);
		Serial.print("\tPressure = "); Serial.println(p.z);
		*/
		
		if (p.y < (TS_MINY-5)) {
			Serial.println("erase");
			// press the bottom of the screen to erase
			tft.fillRect(0, BOXSIZE, tft.width(), tft.height()-BOXSIZE, BLACK);
		}
		// scale from 0->1023 to tft.width
		p.x = map(p.x, TS_MINX, TS_MAXX, tft.width(), 0);
		//p.x = tft.width()-map(p.x, TS_MINX, TS_MAXX, tft.width(), 0);
		p.y = (tft.height()-map(p.y, TS_MINY, TS_MAXY, tft.height(), 0));
		//p.y = map(p.y, TS_MINY, TS_MAXY, tft.height(), 0);
		
		Serial.print("("); Serial.print(p.x);
		Serial.print(", "); Serial.print(p.y);
		Serial.println(")");
    
		// Box Minus  Infrarotsensor abfragen Position: BOXSIZE*4, BOXSIZE*5
		if (p.x < BOXSIZE*5 && p.x > BOXSIZE*4 && p.y < BOXSIZE*6 && p.y > BOXSIZE*5 ) {
			
				tft.setCursor(BOXSIZE*2+15, BOXSIZE*5+10);
				tft.setTextColor(BLACK);
				tft.setTextSize(3);
				tft.println(nachlauf_etikett);
				nachlauf_etikett = nachlauf_etikett +10;
				tft.setCursor(BOXSIZE*2+15, BOXSIZE*5+10);
				tft.setTextColor(WHITE);
				tft.setTextSize(3);
				tft.println(nachlauf_etikett);
				delay(100);
		}
				// Box Plus abfragen BOXSIZE*1, BOXSIZE*5
		if (p.x < BOXSIZE*2 && p.x > BOXSIZE*1 && p.y < BOXSIZE*6 && p.y > BOXSIZE*5 ) {
					
					tft.setCursor(BOXSIZE*2+15, BOXSIZE*5+10);
					tft.setTextColor(BLACK);
					tft.setTextSize(3);
					tft.println(nachlauf_etikett);
					nachlauf_etikett = nachlauf_etikett -10;
					tft.setCursor(BOXSIZE*2+15, BOXSIZE*5+10);
					tft.setTextColor(WHITE);
					tft.setTextSize(3);
					tft.println(nachlauf_etikett);
					delay(100);
		}


   
      // Box Minus Ulraschallsensor abfragen Position: BOXSIZE*4, BOXSIZE*2 
    if (p.x < BOXSIZE*5 && p.x > BOXSIZE*4 && p.y < BOXSIZE*3 && p.y > BOXSIZE*2 ) {
      
        tft.setCursor(BOXSIZE*2+15, BOXSIZE*2+10);
        tft.setTextColor(BLACK);
        tft.setTextSize(3);
        tft.println(nachlauf_ultrasonicsensor);
        nachlauf_ultrasonicsensor = nachlauf_ultrasonicsensor +10;
        tft.setCursor(BOXSIZE*2+15, BOXSIZE*2+10);
        tft.setTextColor(WHITE);
        tft.setTextSize(3);
        tft.println(nachlauf_ultrasonicsensor);
        delay(100);
    }
        // Box Plus abfragen BOXSIZE*1, BOXSIZE*2
    if (p.x < BOXSIZE*2 && p.x > BOXSIZE*1 && p.y < BOXSIZE*3 && p.y > BOXSIZE*2 ) {
          
          tft.setCursor(BOXSIZE*2+15, BOXSIZE*2+10);
          tft.setTextColor(BLACK);
          tft.setTextSize(3);
          tft.println(nachlauf_ultrasonicsensor);
          nachlauf_ultrasonicsensor = nachlauf_ultrasonicsensor -10;
          tft.setCursor(BOXSIZE*2+15, BOXSIZE*2+10);
          tft.setTextColor(WHITE);
          tft.setTextSize(3);
          tft.println(nachlauf_ultrasonicsensor);
          delay(100);
    }
    

	}
}

TuchDisplayClass TuchDisplay;
