// Maegan's First Box
// 24-LED NeoPixel ring, piezo buzzer, Adafruit 9x16 Charlieplexed LED Matrix

#include <Adafruit_NeoPixel.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_IS31FL3731.h>
const int buzzerPin = 5;
const float tempo = 0.8; 

#define E4  330
#define A4  440
#define C5  523
#define B4  494
#define A4  440
#define E5  659
#define D5  587
#define B4  494

int notes[] = {
  E4, A4, C5, B4, 
  A4, E5, D5, B4
};
int duration[] = {         //duration of each note (in ms) Quarter Note is set to 250 ms
  350, 530, 210, 350,
  700, 350, 1100, 1050
};

#define NP_COUNT 24   // Amount of neopixels in ring
#define NP_PIN    2   // Digital IO pin connected to the NeoPixels
Adafruit_NeoPixel ring = Adafruit_NeoPixel(NP_COUNT, NP_PIN, NEO_GRB + NEO_KHZ800);

unsigned long prevMillisRing = 0;
unsigned long prevMillisMatrix = 0;
unsigned long prevMillisBuzz = 0;

// constants won't change:
int ringCounter = 0;
const long ringInterval = 500;  
const long matrixInterval = 200;

// instantiate an LED matrix object using the constructor:
Adafruit_IS31FL3731 matrix = Adafruit_IS31FL3731();
int x = 0;
int y = 0;
int noteIndex = 0;

void setup() {
  // Setup print to console for debugging:
  Serial.begin(9600);

  ring.begin();
  ring.show(); // Initialize all pixels to 'off'

  if (! matrix.begin()) {
    Serial.println("IS31 not found");
    while (1);
  }
  Serial.println("IS31 found!");

//  delay(1000);
 
}

void loop() {

  // Ring
  unsigned long currMillisRing = millis();

  // just turn all the ring colors on to a teal for now:
  for(int a = 0; a < 24; a++)
  {
    ring.setPixelColor(a, 50, 50, 0);
  }
  
  if (currMillisRing - prevMillisRing >= ringInterval) {
    prevMillisRing = currMillisRing;
    Serial.println("ringInterval exceeded, lighting LED");
    ring.setPixelColor(ringCounter, 0, 50, 50);
    ring.setPixelColor(ringCounter-1, 50, 50, 0);
    ring.show();
    // increment the counter:
    if (ringCounter < NP_COUNT) {
      ringCounter++;
    } 
    else {
      ringCounter = 0;
        // use this loop if you want to clear all LEDs at once:
//      for (int i = 0; i < ring.numPixels(); i++) {
//        ring.setPixelColor(i, 0, 0, 0);
//      }
    }
    
  }

  // Matrix
  unsigned long currMillisMatrix = millis();
  if (currMillisMatrix - prevMillisMatrix >= matrixInterval) {
    prevMillisMatrix = currMillisMatrix;

    if (x < 16) {
      matrix.drawPixel(x, y, 50);
      matrix.drawPixel(x-1, y, 0);
      x++;
    }
    else {
      x = 0;
      if (y < 8) {
        y++;
      }
      else {
        y = 0;
      }
      matrix.drawPixel(x, y, 50);
      matrix.drawPixel(x-1, y, 0);
    }
    
  }

  // Buzzer
  unsigned long currMillisBuzz = millis();

  if(noteIndex < 8)
  {
  tone(buzzerPin, notes[noteIndex]);
  if(currMillisBuzz - prevMillisBuzz >= duration[noteIndex] * tempo) 
  {
  prevMillisBuzz = currMillisBuzz;
  noteIndex++;
  tone(buzzerPin, notes[noteIndex]);
  }  
  }
  else
  {
    noTone(buzzerPin);
  }
}
