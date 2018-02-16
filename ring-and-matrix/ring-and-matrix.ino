#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN 6

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(24, PIN, NEO_GRB + NEO_KHZ800);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_IS31FL3731.h>  
#include "Myfont.h"
#include "Arduino.h"
#include <EEPROM.h>

Adafruit_IS31FL3731 matrix = Adafruit_IS31FL3731();

int toggleState;
int EEPROMaddress = 0;

// The lookup table to make the brightness changes be more visible
uint8_t sweep[] = {1, 2, 3, 4, 6, 8, 10, 15, 20, 30, 40, 60, 60, 40, 30, 20, 15, 10, 8, 6, 4, 3, 2, 1};


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
  
//  scan();
//  drawLines();
}

void loop() {
  colorWipe(strip.Color(32, 0, 0), 50); // Red
  matrix_show();
  colorWipe(strip.Color(0, 32, 0), 50); // Green
  matrix_show();
  colorWipe(strip.Color(0, 0, 32), 50); // Blue
  matrix_show();
//  theaterChase(strip.Color(127, 127, 127), 50); // White
//  matrix_show();
//  theaterChase(strip.Color(127, 0, 0), 50); // Red
//  matrix_show();
//  theaterChase(strip.Color(0, 0, 127), 50); // Blue
//  matrix_show();
  rainbow(20);
  matrix_show();
  rainbowCycle(20);
  matrix_show();
//  theaterChaseRainbow(50);
//  matrix_show();

}

void upToggleState(){
  toggleState++;
  if (toggleState > 4) toggleState = 1;
  EEPROM.write(EEPROMaddress, toggleState);
}

void matrix_show() {
  switch(toggleState){
  case 1:
    text1();
    break;
   case 2:
    smiley();
    break;
   case 3:
    kettle();
    break;
   case 4:
    smiley_drift();
    break;
  default:
    EEPROM.write(EEPROMaddress, 0);
  }
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
    B00011010,
    B00000000,
    B00000000 }
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
  matrix.clear();
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
