// TuchDisplay.h

#include <Elegoo_GFX.h>    // Core graphics library
#include <TouchScreen.h>
#include <registers.h>
#include <pin_magic.h>
#include <Elegoo_TFTLCD.h>


#ifndef _TUCHDISPLAY_h
#define _TUCHDISPLAY_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


#define YP A3  // must be an analog pin, use "An" notation!
#define XM A2  // must be an analog pin, use "An" notation!
#define YM 9   // can be a digital pin
#define XP 8   // can be a digital pin


//Touch For New ILI9341 TP
#define TS_MINX 120
#define TS_MAXX 900

#define TS_MINY 70
#define TS_MAXY 920

// For better pressure precision, we need to know the resistance
// between X+ and X- Use any multimeter to read it
// For the one we're using, its 300 ohms across the X plate


#define LCD_CS A3
#define LCD_CD A2
#define LCD_WR A1
#define LCD_RD A0
// optional
#define LCD_RESET A4

// Assign human-readable names to some common 16-bit color values:
#define	BLACK   0x0000
#define	BLUE    0x001F
#define	RED     0xF800
#define	GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF




#define BOXSIZE 40
#define PENRADIUS 3


#define MINPRESSURE 10
#define MAXPRESSURE 1000

class TuchDisplayClass
{
 protected:
//	TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);
//	Elegoo_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);


 public:
	void init();
	int oldcolor, currentcolor;
	TouchScreen ts = TouchScreen(8, PIN_A3, PIN_A2, 9, 300);
	//Elegoo_TFTLCD tft(PIN_A3, PIN_A2, PIN_A1, PIN_A0, PIN_A4);
	Elegoo_TFTLCD tft = Elegoo_TFTLCD(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);
	bool etikett_aufziehen = false;
	int nachlauf_etikett = 70; //in ms !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	
	void runTouch();
};

extern TuchDisplayClass TuchDisplay;

#endif
