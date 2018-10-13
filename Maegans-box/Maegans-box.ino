// Maegan's First Box
// 24-LED NeoPixel ring, piezo buzzer, Adafruit 9x16 Charlieplexed LED Matrix

// TODO:
// Redesign board with capacitor and resistors and switch.
// Get multi-tasking working with millis() function instead of the delay() function
// https://learn.adafruit.com/multi-tasking-the-arduino-part-1/overview
// Get mode selector set up with momentary switch button. Look at example sketch, Button Cycler


// Import library for Neopixel ring:
#include <Adafruit_NeoPixel.h>
// Libraries for matrix:
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_IS31FL3731.h>
// None needed for buzzer

// Buzzer declarations:
const int buzzer = 5;
const int songspeed = 1.5; 

//*****************************************
#define E3  165
#define E4  330
#define E5  659
#define E6  1319
#define E7  2637

//*****************************************
int notes[] = {
  E3, E4, E5, E6, E7
  
};

//*****************************************
int duration[] = {         //duration of each note (in ms) Quarter Note is set to 250 ms
  500, 500, 500, 500, 500, 
};


// Instantiate a neopixel object using the constructor:
// Parameter 1 = number of pixels in ring
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_RGB     Pixels are wired for RGB bitstream
//   NEO_GRB     Pixels are wired for GRB bitstream, correct for neopixel stick
//   NEO_KHZ400  400 KHz bitstream (e.g. FLORA pixels)
//   NEO_KHZ800  800 KHz bitstream (e.g. High Density LED strip), correct for neopixel stick
#define NP_COUNT 24   // Amount of neopixels in ring
#define NP_PIN    6   // Digital IO pin connected to the NeoPixels
int ringCounter = 0;
Adafruit_NeoPixel ring = Adafruit_NeoPixel(NP_COUNT, NP_PIN, NEO_GRB + NEO_KHZ800);

unsigned long prevMillisRing = 0;        // will store last time LED was updated

// constants won't change:
const long ringInterval = 20;  


// instantiate an LED matrix object using the constructor:
//Adafruit_IS31FL3731 matrix = Adafruit_IS31FL3731();


// The lookup table to make the matrix brightness changes be more visible
uint8_t sweep[] = {1, 2, 3, 4, 6, 8, 10, 15, 20, 30, 40, 60, 60, 40, 30, 20, 15, 10, 8, 6, 4, 3, 2, 1};

void setup() {
  // Setup print to console for debugging:
  Serial.begin(9600);

  ring.begin();
  ring.show(); // Initialize all pixels to 'off'

//  if (! matrix.begin()) {
//    Serial.println("IS31 not found");
//    while (1);
//  }
//  Serial.println("IS31 found!");
 
}

void loop() {

  unsigned long currMillisRing = millis();

  Serial.println("currMillisRing:");
  Serial.println(currMillisRing);

  if (currMillisRing - prevMillisRing >= ringInterval) {
    prevMillisRing = currMillisRing;
    Serial.println("ringInterval exceeded, lighting LED");
    ring.setPixelColor(ringCounter, 50, 0, 0);
    ring.show();
    // increment the counter:
    if (ringCounter < NP_COUNT) {
      ringCounter++;
    } 
    else {
      ringCounter = 0;
      for (int i = 0; i < ring.numPixels(); i++) {
        ring.setPixelColor(i, 0, 0, 0);
      }
    }
    
  }

//  colorWipe(ring.Color(50, 0, 0), 10); // Red
//  colorWipe(ring.Color(50, 0, 0)); // Red
//  colorWipe(ring.Color(0, 32, 0), 10);
//  colorWipe(ring.Color(0, 32, 0));

  // Buzzer repeat:
//  for (int i=0;i<5;i++){              //203 is the total number of music notes in the song
//  int wait = duration[i] * songspeed;
//  tone(buzzer,notes[i],wait);          //tone(pin,frequency,duration)
//  delay(wait);}                        //delay is used so it doesn't go to the next loop before tone is finished playing
 

  //Matrix code:
  // animate over all the pixels, and set the brightness from the sweep table
//  for (uint8_t incr = 0; incr < 24; incr++)
//    for (uint8_t x = 0; x < 16; x++)
//      for (uint8_t y = 0; y < 9; y++)
//        matrix.drawPixel(x, y, sweep[(x+y+incr)%24]);
//  delay(20);
//  
}


// FUNCTION DEFINITIONS:

// For ring:

// Fill the dots one after the other with a color
//void colorWipe(uint32_t c, uint8_t wait) {
//void colorWipe(uint32_t c) {
//  for(uint16_t i=0; i < ring.numPixels(); i++) {
//    ring.setPixelColor(i, c);
//    ring.show();
//    delay(wait);
//  }
//}



