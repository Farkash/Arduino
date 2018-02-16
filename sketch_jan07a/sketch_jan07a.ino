#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN 6

Adafruit_NeoPixel strip = Adafruit_NeoPixel(24, PIN, NEO_GRB + NEO_KHZ800);

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_IS31FL3731.h>  
#include "Myfont.h"
#include "Arduino.h"
#include <EEPROM.h>

Adafruit_IS31FL3731 matrix = Adafruit_IS31FL3731();

int toggleState;
int EEPROMaddress = 0;

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'

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
  
}

void loop() {
  wand_duel();
//  colorWipe(strip.Color(32, 0, 0), 50); // Red
//  colorWipe(strip.Color(0, 32, 0), 50); // Green
//  colorWipe(strip.Color(0, 0, 32), 50); // Blue
}

void upToggleState(){
  toggleState++;
  if (toggleState > 4) toggleState = 1;
  EEPROM.write(EEPROMaddress, toggleState);
}


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

static const uint8_t PROGMEM
  kettle_bmp[] =
  { B00000000,
    B00000000,
    B10011010,
    B01100101,
    B00100101,
    B00011010,
    B00000000,
    B00000000 }
;

static const uint8_t PROGMEM
  hallows_bmp[] =
  { B00010000,
    B00111000,
    B01010100,
    B10010010,
    B11111111,
    B00000000,
    B00000000,
    B00000000 }
;


// Draw circles
void circles() {
  matrix.clear();
  matrix.drawCircle(8,4, 4, 64);
  matrix.drawCircle(8,4, 2, 32);
  delay(2000);
}

//text
void text1() {
  matrix.setTextSize(1);
  matrix.setTextWrap(false);  // we dont want text to wrap so it scrolls nicely
  matrix.setTextColor(50);
  for (int8_t x=0; x>=-160; x--) {
    matrix.clear();
    matrix.setCursor(x,0);
    matrix.print("Maeg's fun light art :)");
    delay(40);
}
}

void smiley() {
  matrix.clear();
  matrix.drawBitmap(4, 1, smile_bmp, 8, 8, 32);
  delay(3000);
}

void smiley_drift() {
  for (int y = 0; y < matrix.height()-7; y++) {
    for(int x = -8; x < matrix.width(); x++){
      matrix.clear();
      matrix.drawBitmap(x, y, smile_bmp, 8, 8, 32);  
      matrix.clear();
      delay(30); 
    }
  }

  for (int x = 0; x < matrix.width()-7; x++) {
    for(int y = -4; y < matrix.height()-2; y++){
      matrix.clear();
      matrix.drawBitmap(x, y, smile_bmp, 8, 8, 32);  
      matrix.clear();
      delay(5); 
    }
  }
}

void kettle() {
  matrix.clear();
  matrix.drawBitmap(4, 1, kettle_bmp, 8, 8, 255);
  delay(3000);
} 

void wand_duel(){
  matrix.clear();
  matrix.drawLine(15,4,12,1,10);
  delay(1000);
//  matrix.clear();
//  matrix.drawLine(15,4,10,2,10);
//  delay(200);
//  matrix.clear();
//  matrix.drawLine(15,4,10,3,10);
//  delay(200);
  matrix.clear();
  matrix.drawLine(15,4,10,4,10);
  delay(300);
  matrix.drawCircle(10,4,1,10);
  delay(100);
  matrix.clear();
  matrix.drawCircle(9,4,1,10);
  delay(100);
  matrix.clear();
  matrix.drawCircle(8,4,1,10);
  delay(100);
  matrix.clear();
  matrix.drawCircle(7,4,1,10);
  delay(100);
  matrix.clear();
  matrix.drawCircle(6,4,1,10);
  delay(100);
  matrix.clear();
  matrix.drawCircle(5,4,1,10);
  delay(100);
  matrix.clear();
  matrix.drawCircle(4,4,1,10);
  delay(100);
  matrix.clear();
  matrix.drawCircle(3,4,1,10);
  delay(100);
  matrix.clear();
  matrix.drawCircle(2,4,1,10);
  delay(100);
  matrix.clear();
  matrix.drawCircle(1,4,1,10);
  delay(100);
  matrix.clear();
  matrix.drawCircle(0,4,1,10);
  delay(100);
  matrix.clear();

  
  matrix.drawCircle(0,4,2,10);
  delay(200);
  matrix.clear();
  matrix.drawCircle(0,4,3,10);
  delay(200);
  matrix.clear();
  matrix.drawCircle(0,4,4,10);
  delay(200);
  matrix.clear();
  matrix.drawCircle(0,4,5,10);
  delay(200);
  matrix.clear();




}




void hallows() {
  matrix.clear();
  matrix.drawLine(7,0,2,8,10);
  matrix.drawLine(7,0,12,8,10);
  matrix.drawLine(2,8,11,8,10);
  matrix.drawLine(7,0,7,8,10);
  matrix.drawCircle(7,5,2,10);
  delay(100);

  matrix.clear();
  matrix.drawLine(7,0,3,8,10);
  matrix.drawLine(7,0,11,8,10);
  matrix.drawLine(4,8,10,8,10);
  matrix.drawLine(7,0,7,8,10);
  matrix.drawCircle(7,5,2,10);
  delay(100);

  matrix.clear();
  matrix.drawLine(7,0,4,8,10);
  matrix.drawLine(7,0,10,8,10);
  matrix.drawLine(5,8,9,8,10);
  matrix.drawLine(7,0,7,8,10);
  matrix.drawCircle(7,5,1,10);
  delay(100);

matrix.clear();
  matrix.drawLine(7,0,5,8,10);
  matrix.drawLine(7,0,9,8,10);
  matrix.drawLine(6,8,8,8,10);
  matrix.drawLine(7,0,7,8,10);
//  matrix.drawCircle(7,5,2,10);
  delay(100);

matrix.clear();
  matrix.drawLine(7,0,6,8,10);
  matrix.drawLine(7,0,8,8,10);
  matrix.drawLine(6,8,8,8,10);
  matrix.drawLine(7,0,7,8,10);
//  matrix.drawCircle(7,5,2,10);
  delay(100);

matrix.clear();
  matrix.drawLine(7,0,7,8,10);
//  matrix.drawCircle(7,5,2,10);
  delay(100);

matrix.clear();
  matrix.drawLine(7,0,6,8,10);
  matrix.drawLine(7,0,8,8,10);
  matrix.drawLine(6,8,8,8,10);
  matrix.drawLine(7,0,7,8,10);
//  matrix.drawCircle(7,5,2,10);
  delay(100);

matrix.clear();
  matrix.drawLine(7,0,5,8,10);
  matrix.drawLine(7,0,9,8,10);
  matrix.drawLine(6,8,8,8,10);
  matrix.drawLine(7,0,7,8,10);
//  matrix.drawCircle(7,5,2,10);
  delay(100);

  matrix.clear();
  matrix.drawLine(7,0,4,8,10);
  matrix.drawLine(7,0,10,8,10);
  matrix.drawLine(5,8,9,8,10);
  matrix.drawLine(7,0,7,8,10);
  matrix.drawCircle(7,5,1,10);
  delay(100);

  matrix.clear();
  matrix.drawLine(7,0,3,8,10);
  matrix.drawLine(7,0,11,8,10);
  matrix.drawLine(4,8,10,8,10);
  matrix.drawLine(7,0,7,8,10);
  matrix.drawCircle(7,5,2,10);
  delay(100);

  matrix.clear();
  matrix.drawLine(7,0,2,8,10);
  matrix.drawLine(7,0,12,8,10);
  matrix.drawLine(2,8,11,8,10);
  matrix.drawLine(7,0,7,8,10);
  matrix.drawCircle(7,5,2,10);
  delay(100);

}

void hallows_small(){
  matrix.clear();
  matrix.drawBitmap(4, 1, hallows_bmp, 8, 8, 32);
}


// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
