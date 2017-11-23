//Charlieplexing and Pulse-Width-Modulation with Adafruit IS31FL3731 Driver
//and Adafruit mini-led matrix

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_IS31FL3731.h>
#include "Myfont.h"
#include "Arduino.h"
#include <EEPROM.h>

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


int toggleState;
int EEPROMaddress = 0;

// The lookup table to make the brightness changes be more visible
uint8_t sweep[] = {1, 2, 3, 4, 6, 8, 10, 15, 20, 30, 40, 60, 60, 40, 30, 20, 15, 10, 8, 6, 4, 3, 2, 1};

void setup(){
  toggleState = EEPROM.read(EEPROMaddress);
  upToggleState();

  Serial.begin(9600);
  Serial.println(toggleState);
  Serial.println("ISSI manual animation test");
  if (! matrix.begin()) {
    Serial.println("IS31 not found");
    while (1);
  }
  Serial.println("IS31 Found!");
  
  scan();
  drawLines();
}

void loop(){
  switch(toggleState){
  case 1:
    greeting();
    break;
   case 2:
    swirl();
    break;
  default:
    EEPROM.write(EEPROMaddress, 0);
  }
}

//declare methods here:

//Ups or resets the state counter
void upToggleState(){
  toggleState++;
  if (toggleState > 2) toggleState = 1;
  EEPROM.write(EEPROMaddress, toggleState);
}
//bitmap images (emojis here)
//uint8_t is a type of unsigned integer of length 8 bits
static const uint8_t PROGMEM
  smile_bmp[] =
  { B00111100,
    B01000010,
    B10100101,
    B10000001,
    B10100101,
    B10011001,
    B01000010,
    B00111100 }
;

void swirl() {
  // animate over all the pixels, and set the brightness from the sweep table
  for (uint8_t incr = 0; incr < 24; incr++)
    for (uint8_t x = 0; x < 16; x++)
      for (uint8_t y = 0; y < 9; y++)
        matrix.drawPixel(x, y, sweep[(x+y+incr)%24]);
  delay(20);
}

  //  light up every led one at a time in order
void scan() {
  for (int y = 0; y < matrix.height(); y++) {
    for(int x = 0; x < matrix.width(); x++){
      matrix.clear();
      matrix.drawPixel(x, y, 255);  
      delay(1); 
    }
  }
}

void drawLines() {
  matrix.clear();
  matrix.drawLine(0,0, matrix.width()-1, matrix.height()-1, 127);
  delay(100);
  
  matrix.clear();
  matrix.drawLine(0,8, matrix.width()-1, matrix.height()-1, 255);
  delay(100);
  
  matrix.clear();
  matrix.drawLine(0,8, matrix.width()-1, 0, 255);
  delay(100);
  
  matrix.clear();
  matrix.drawLine(0,0, matrix.width()-1, 0, 255);
  delay(100);
  
  matrix.clear();
  matrix.drawLine(0,0, 0, matrix.height()-1, 255);
  delay(100);
  
  matrix.clear();
  matrix.drawLine(15,0, matrix.width()-1, matrix.height()-1, 255);
  delay(100);
}

// draw rectangles
//  matrix.clear();
//  matrix.drawRect(0,0, matrix.width(), matrix.height(), 255);
//  delay(100);
//  matrix.fillRect(2,2, matrix.width()-4, matrix.height()-4, 255);
//  delay(500);

// Draw circles
void circles() {
  matrix.clear();
  matrix.drawCircle(8,4, 4, 64);
  matrix.drawCircle(8,4, 2, 32);
  delay(2000);
}

//text
void greeting() {
  matrix.setTextSize(1);
  matrix.setTextWrap(false);  // we dont want text to wrap so it scrolls nicely
  matrix.setTextColor(50);
  for (int8_t x=0; x>=-48; x--) {
    matrix.clear();
    matrix.setCursor(x,0);
    matrix.print("Hey Sis!");
    delay(40);
  }
  for (int8_t x=0; x>=-96; x--) {
    matrix.clear();
    matrix.setCursor(x,0);
    matrix.print("Happy Birthday!");
    delay(40);
  }
  for (int8_t x=0; x>=-96; x--) {
    matrix.clear();
    matrix.setCursor(x,0);
    matrix.print("Nov 20th, 2017");
    delay(40);
  }
  for (int8_t x=0; x>=-100; x--) {
    matrix.clear();
    matrix.setCursor(x,0);
    matrix.print("Love, your little ");
    delay(40);
  }
  for (int8_t x=0; x>=-100; x--) {
    matrix.clear();
    matrix.setCursor(x,0);
    matrix.print(" brother, Steve");
    delay(40);
  }
  matrix.clear();
  matrix.drawBitmap(3, 0, smile_bmp, 8, 8, 255);
  delay(3000);
}
