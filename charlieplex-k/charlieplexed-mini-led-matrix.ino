//Charlieplexing and Pulse-Width-Modulation with Adafruit IS31FL3731 Driver
//and Adafruit mini-led matrix

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_IS31FL3731.h>
#include "Myfont.h"
#include "Arduino.h"
#include <EEPROM.h>

//constructor for full-size breakout, not featherwing:
//constructor breakdown:
//first list the class (object type) that you want to create an instance of
//in this case, it is an object of type Adafruit_IS31FL3731
//then give that object an alias, given below as 'matrix.'
//then invoke the Adafruit_IS31FL3731 object constructor (special method from
//the Adafruit_IS31FL3731 library that instantiates an instance of the class.
//The constructor method does not need any arguments. 
Adafruit_IS31FL3731 matrix = Adafruit_IS31FL3731();
//Now we have an object titled 'matrix' of type Adafruit_IS31FL3731. It is a 
//Adafruit LED charlieplexed matrix object. 


//DESIGN THE METHODS YOU WANT FOR DISPLAY, THEN ADD ABILITY TO CYCLE WITH POWER
//how to have method that loop uses change by cycling power to give user different diplay loops?
//int toggleState;
//int EEPROMaddress = 0;
//int charLength[]={20, 14, 23, 30};
//unsigned char text0[]="My eyes are up there";
//unsigned char text1[]="Blinky or GTFO";
//unsigned char text2[]="Enjoying the lightshow?";
//unsigned char text3[]="Would you like to play a game?";
//
//void setup(){
//  toggleState = EEPROM.read(EEPROMaddress);
//  upToggleState();
//
//  if (1==toggleState || 7==toggleState){
//    LedSign::Init(GRAYSCALE);
//  }
//  else{
//    LedSign::Init();
//  }
//
//  for (int i = toggleState+1; i > 0; i--){
//    LedSign::Set(i-1, 0, 255);
//  }
//  delay(1000);
//  LedSign::Clear(0);
//
//}
//
//void loop(){
//  /*
// 0 "My eyes are up there"
//   1 *Plasma
//   2 "Blinky or GTFO"
//   3 *Game of Life
//   4 "Enjoying the lightshow?"
//   5 *Balls
//   6 "Would you like to play a game?"
//   7 *Double Helix
//   */
//  switch(toggleState){
//  case 0:
//    Myfont::Banner(charLength[0],text0);
//    break;
//  case 1:
//    plasma();
//    break;
//  case 2:
//    Myfont::Banner(charLength[1],text1);
//    break;
//  case 3:
//    life();
//  case 4:
//    Myfont::Banner(charLength[2],text2);
//    break;
//  case 5:
//    balls();
//    break;
//  case 6:
//    Myfont::Banner(charLength[3],text3);
//    break;
//  case 7:
//    DNA();
//    break;
//  default:
//    EEPROM.write(EEPROMaddress, 0);
//  }
//}
//
////Ups or resets the state counter
//void upToggleState(){
//  toggleState++;
//  if (toggleState > 7) toggleState = 0;
//  EEPROM.write(EEPROMaddress, toggleState);
//}

//uint8_t is a type of unsigned integer of length 8 bits
//static const uint8_t PROGMEM
//  smile_bmp[] =
//  { B00111100,
//    B01000010,
//    B10100101,
//    B10000001,
//    B10100101,
//    B10011001,
//    B01000010,
//    B00111100 },
//  neutral_bmp[] =
//  { B00111100,
//    B01000010,
//    B10100101,
//    B10000001,
//    B10111101,
//    B10000001,
//    B01000010,
//    B00111100 },
//  frown_bmp[] =
//  { B00111100,
//    B01000010,
//    B10100101,
//    B10000001,
//    B10011001,
//    B10100101,
//    B01000010,
//    B00111100 };


void setup() {

  Serial.begin(9600);
  Serial.println("ISSI manual animation test");
  if (! matrix.begin()) {
    Serial.println("IS31 not found");
    while (1);
  }
  Serial.println("IS31 Found!");
  
}


void loop() {
  matrix.setRotation(0);

//  matrix.clear();
//  matrix.drawBitmap(3, 0, smile_bmp, 8, 8, 255);
//  delay(500);
//  
//  matrix.clear();
//  matrix.drawBitmap(3, 0, neutral_bmp, 8, 8, 64);
//  delay(500);
//
//  matrix.clear();
//  matrix.drawBitmap(3, 0, frown_bmp, 8, 8, 32);
//  delay(500);

//light up every led one at a time in order
//  for (int y = 0; y < matrix.height(); y++) {
//    for(int x = 0; x < matrix.width(); x++){
//      matrix.clear();
//      matrix.drawPixel(x, y, 255);  
//      delay(50); 
//    }
//  }


//  matrix.clear();
//  matrix.drawLine(0,0, matrix.width()-1, matrix.height()-1, 127);
//  delay(500);
//
//  matrix.clear();
//  matrix.drawLine(0,8, matrix.width()-1, matrix.height()-1, 255);
//  delay(500);
//
// matrix.clear();
//  matrix.drawLine(0,8, matrix.width()-1, 0, 255);
//  delay(500);
//
// matrix.clear();
//  matrix.drawLine(0,0, matrix.width()-1, 0, 255);
//  delay(500);
//
// matrix.clear();
//  matrix.drawLine(0,0, 0, matrix.height()-1, 255);
//  delay(500);
//
// matrix.clear();
//  matrix.drawLine(15,0, matrix.width()-1, matrix.height()-1, 255);
//  delay(500);

  
//  matrix.clear();
//  matrix.drawRect(0,0, matrix.width(), matrix.height(), 255);
//  delay(100);
//  matrix.fillRect(2,2, matrix.width()-4, matrix.height()-4, 255);
//  delay(500);
//
//  matrix.clear();
//  matrix.drawCircle(8,4, 4, 64);
//  matrix.drawCircle(8,4, 2, 32);
//  delay(500);
//
//
  matrix.setTextSize(1);
  matrix.setTextWrap(false);  // we dont want text to wrap so it scrolls nicely
  matrix.setTextColor(50);
  for (int8_t x=0; x>=-48; x--) {
    matrix.clear();
    matrix.setCursor(x,0);
    matrix.print("Hey Sis!");
    delay(50);
  }
  for (int8_t x=0; x>=-48; x--) {
    matrix.clear();
    matrix.setCursor(x,0);
    matrix.print("Fun right?!");
    delay(50);
  }


//  matrix.setTextSize(2);
//  matrix.setTextWrap(false);  // we dont want text to wrap so it scrolls nicely
//  matrix.setTextColor(32);
//  matrix.setRotation(1);
//  for (int8_t x=7; x>=-64; x--) {
//    matrix.clear();
//    matrix.setCursor(x,0);
//    matrix.print("World");
//    delay(100);
//  }
}
