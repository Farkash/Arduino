// 24-LED NeoPixel ring, piezo buzzer, 8x7 Charlieplexed LED Matrix
#include <Adafruit_NeoPixel.h>
#include <Wire.h>
#include <SparkFun_LED_8x7.h>
#include <Chaplex.h>

int NP_COUNT = 24;
int NP_PIN = 3;
byte led_pins[] = {4, 5, 6, 7, 8, 9, 10, 11}; // Pins for Matrix
byte i;
byte x;
byte y;
byte radius;
int a;
int b;
int state;
const int buzzerPin = 2;
const float tempo = 0.8; 
unsigned long ringLast = 0;
const long ringInterval = 30;
int ringIndex = 0;
int ringWipeActive = 1;
unsigned long scrollStart = 0;
int scrollAway = 1;
unsigned long buzzLast = 0;
const long scrollInit = 10000;
const long scrollTime = 10000;
unsigned long randomStart = 0;
const long randomLimit = 30000;
const long randomWait = 27000;
unsigned long randomLast = 0;
const long randomInterval = 10;
uint16_t rainbowi = 0;
uint16_t rainbowj = 0;
unsigned long rainbowLast = 0;
const int rainbowInterval = 20;
//int x = 0;
//int y = 0;
int noteIndex = 0;

int E4 = 330;
int C5 = 523;
int B4 = 494;
int E5 = 659;
int D5 = 587;
int A_4 = 440;

int notes[] = {
  E4, A_4, C5, B4, 
  A_4, E5, D5, B4
};
int duration[] = {
  350, 530, 210, 350,
  700, 350, 1100, 1050
};

Adafruit_NeoPixel ring = Adafruit_NeoPixel(NP_COUNT, NP_PIN, NEO_GRB + NEO_KHZ800);
// ring color array
uint32_t red = ring.Color(100, 0, 0);
uint32_t green = ring.Color(0, 100, 0);
uint32_t blue = ring.Color(0, 0, 100);
uint32_t purple = ring.Color(100, 0, 100);
uint32_t teal = ring.Color(0, 100, 100);
uint32_t yellow = ring.Color(100, 100, 0);
uint32_t off = ring.Color(0, 0, 0);
uint32_t ringColors [] = {
  red, green, blue, purple, teal, yellow,
  red, green, blue, purple, teal, yellow,
  red, green, blue, purple, teal, yellow,
  red, green, blue, purple, teal, yellow,
  red, green, blue, purple, teal, yellow, off
};
int ringColorIndex = 0;

void setup() {
  // Setup print to console for debugging:
  Serial.begin(9600);

  ring.begin();
  ring.show(); // Initialize all pixels to 'off'

  Plex.init(led_pins);
  Plex.clear();
  Plex.display();

  // Seed our random number generator with an analog voltage read
  randomSeed(analogRead(0));
  
}

void loop() {
  
//////////////////// MATRIX /////////////////////

unsigned long matrixClock = millis();
// scroll text
if (matrixClock < 500)
{
  Plex.scrollText("Hello Marissa! Live long and prosper!  Your friend,   -Steve   :)", 1, true);
}

// Randomly light pixels
// Choose a random number between 0 and 7 for x coordinate
a = random(0, 8);
// Choose a random number between 0 and 6 for y coordinate
b = random(0, 7);
// Flip a coin for the state of the LED
state = random(0, 2);

if(matrixClock > randomWait && matrixClock - randomWait < randomLimit)
{
  unsigned long randomClock = millis();
  if(randomClock - randomLast > randomInterval)
  {
    Plex.pixel(a, b, state);
    Plex.display();
    randomLast = randomClock;
  }
}
else
{
  Plex.clear();
  Plex.display();
}



//////////////////// BUZZER /////////////////////



//  unsigned long buzzClock = millis();
//
//  if(noteIndex < 8)
//  {
//  tone(buzzerPin, notes[noteIndex]);
//  if(currMillisBuzz - prevMillisBuzz >= duration[noteIndex] * tempo) 
//  {
//  prevMillisBuzz = currMillisBuzz;
//  noteIndex++;
//  tone(buzzerPin, notes[noteIndex]);
//  }  
//  }
//  else
//  {
//    noTone(buzzerPin);
//  }

///////////////////// RING /////////////////////

unsigned long ringClock = millis();

// Ring color wipe
if(ringWipeActive == 1 && ringClock - ringLast > ringInterval)
{
  ring.setPixelColor(ringIndex, ringColors[ringColorIndex]);
//  ring.setPixelColor(ringIndex-1, 0, 0, 0);
  ringLast = ringClock;
  ring.show();
  if(ringIndex < 23)
  {
    ringIndex++;
  }
  else
  {
    ringIndex = 0;
    if(ringColorIndex < 30)
    {
      ringColorIndex++;
    }
    else 
    {
//      for(int i = 0; i < 24; i++)
//      {
//        ring.setPixelColor(i, 0, 0, 0);
//        ring.show();
//      }
      ringWipeActive = 0;
    }
  } 
}


// ring rainbow
//if(ringWipeActive == 0 && ringClock > 30000 && ringClock < 40000)
//{
//  ring.setPixelColor(rainbowi, Wheel((rainbowi+rainbowj) & 255));
//  ring.show();
//  rainbowLast = ringClock;
//  if(rainbowi < 23)
//  {
//    rainbowi++;
//  }
//  else
//  {
//    rainbowi = 0;
//    if(rainbowj < 256)
//    {
//      rainbowj++;
//    }
//    else
//    {
//      rainbowj = 0;
//    }
//  }
//}
//else
//{
//  if(ringWipeActive == 0 && ringClock > 40000)
//  {
//    ring.setPixelColor(rainbowi, Wheel(((rainbowi * 256 / ring.numPixels()) + rainbowj) & 255));
//    ring.show();
//    //  rainbowLast = ringClock;
//    if(rainbowi < 23)
//    {
//      rainbowi++;
//    }
//    else
//    {
//      rainbowi = 0;
//      if(rainbowj < 256*5)
//      {
//        rainbowj++;
//      }
//      else
//      {
//        rainbowj = 0;
//      }
//    }
//  }
//  else
//  {
//    for(int i = 0; i < 24; i++)
//    {
//      ring.setPixelColor(i, 0, 0, 0);
//      ring.show();
//    }
//  }
//}


// ring random




} //////////// END LOOP ///////////////



//void rainbow(uint8_t wait) {
//  uint16_t i, j;
//
//  for(j=0; j<256; j++) {
//    for(i=0; i<strip.numPixels(); i++) {
//      strip.setPixelColor(i, Wheel((i+j) & 255));
//    }
//    strip.show();
//    delay(wait);
//  }
//}
//
//
// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
//uint32_t Wheel(byte WheelPos) {
//  WheelPos = 255 - WheelPos;
//  if(WheelPos < 85) {
//    return ring.Color(255 - WheelPos * 3, 0, WheelPos * 3);
//  }
//  if(WheelPos < 170) {
//    WheelPos -= 85;
//    return ring.Color(0, WheelPos * 3, 255 - WheelPos * 3);
//  }
//  WheelPos -= 170;
//  return ring.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
//}



