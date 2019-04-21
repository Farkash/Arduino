#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_IS31FL3731.h>
#include <Adafruit_NeoPixel.h>
#include <TimerOne.h>
#include "TM1637.h"
#define ON 1
#define OFF 0
int neoPixelCount = 12;
int neoPixelPin = 13;
#define BUTTON_PIN   5
bool oldState = HIGH;
int showType = 0;
int8_t TimeDisp[] = {0x00,0x00,0x00,0x00};
unsigned char ClockPoint = 1;
unsigned char Update;
unsigned char halfsecond = 0;
unsigned char second;
unsigned char minute = 0;
unsigned char hour = 12;
#define DIO 2
#define CLK 3  //pins definitions for TM1637 and can be changed to other ports
int r, g, b;
TM1637 tm1637(CLK,DIO);

// If you're using the full breakout...
Adafruit_IS31FL3731 ledmatrix = Adafruit_IS31FL3731();
// If you're using the FeatherWing version
//Adafruit_IS31FL3731_Wing ledmatrix = Adafruit_IS31FL3731_Wing();
Adafruit_NeoPixel strip = Adafruit_NeoPixel(neoPixelCount, neoPixelPin, NEO_GRB + NEO_KHZ800);


// The lookup table to make the brightness changes be more visible
uint8_t sweep[] = {1, 2, 3, 4, 6, 8, 10, 15, 20, 30, 40, 60, 60, 40, 30, 20, 15, 10, 8, 6, 4, 3, 2, 1};
unsigned long randomLast = 0;
unsigned long colorWipeLast = 0;
int i = 0;
uint32_t c;
int cycleTracker = 0;
int sensorPin = A0;    // select the input pin for the potentiometer
long rawPot;
int cleanPot;
unsigned long randomPixelLast;
int randomIteration = 0;

void setup() {
  Serial.begin(9600);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  if (! ledmatrix.begin()) {
    Serial.println("IS31 not found");
    while (1);
  }
  Serial.println("IS31 found!");
//  randomSeed(analogRead(1));
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  tm1637.set();
  tm1637.init();
  Timer1.initialize(500000);//timing for 500ms
  Timer1.attachInterrupt(TimingISR);//declare the interrupt serve routine:TimingISR

}

void loop() {
  if(Update == ON)
  {
    TimeUpdate();
    tm1637.display(TimeDisp);
  }
  
  bool newState = digitalRead(BUTTON_PIN);
//  Serial.println(newState);
  rawPot = analogRead(sensorPin);
  if(rawPot >= 0 && rawPot < 100)
  {
    cleanPot = 1;
  }
  else if(rawPot >= 100 && rawPot < 200)
  {
    cleanPot = 2;
  }
  else if(rawPot >= 200 && rawPot < 300)
  {
    cleanPot = 3;
  }
  else if(rawPot >= 300 && rawPot < 400)
  {
    cleanPot = 4;
  }
  else if(rawPot >= 400 && rawPot < 500)
  {
    cleanPot = 5;
  }
  else if(rawPot >= 500 && rawPot < 600)
  {
    cleanPot = 6;
  }
  else if(rawPot >= 600 && rawPot < 700)
  {
    cleanPot = 7;
  }
  else if(rawPot >= 700 && rawPot < 800)
  {
    cleanPot = 8;
  }
  else if(rawPot >= 800 && rawPot < 900)
  {
    cleanPot = 9;
  }
  else
  {
    cleanPot = 10;
  }
              
//  Serial.println(rawPot);
  if (newState == LOW && oldState == HIGH) 
  {
    // Short delay to debounce button.
    delay(20);
    // Check if button is still low after debounce.
    newState = digitalRead(BUTTON_PIN);
    if (newState == LOW) 
    {
      showType++;
      if (showType > 2)
        showType=0;
//    startShow(showType);
      Serial.print("newState:");
      Serial.println(newState);
      Serial.print("showType:");
      Serial.println(showType);
    }
  }
  // Set the last button state to the old state.
  oldState = newState;
  
  // animate over all the pixels, and set the brightness from the sweep table
//  for (uint8_t incr = 0; incr < 24; incr++)
//    for (uint8_t x = 0; x < 16; x++)
//      for (uint8_t y = 0; y < 9; y++)
//        ledmatrix.drawPixel(x, y, sweep[(x+y+incr)%24]);
//  delay(20);
randomPixel(10);
//randomColorWipe(100, 0);
randomColorPixel(30, 10);
}

long randomColorPicker(int a, int b)
{
  int rint = random(a,b);
  int diff = (b-1) - a;
  float interval = 255 / diff;
  int intervalInt = (int)interval;
  return rint * intervalInt;
}

void randomPixel(int wait)
{
  if(millis() - randomLast > wait)
  {
    int x = random(0,16);
    int y = random(0,9);
    int state = random(2);
    int bright = random(1, 4);
//    Serial.println(rawPot);
//    float brightness = (rawPot / 10);
//    int brightLevel = (int)brightness;
//    Serial.println(brightness);
//    Serial.println(brightLevel);
//    int brightLevel = bright * 127;
    int brightLevel;
    switch(bright)
    {
      case 1: brightLevel = 10;
        break;
      case 2: brightLevel = 50;
        break;
      case 3: brightLevel = 100;
        break;
//      case 4: brightLevel = 150;
//        break;
    }
    if(state == 0)
      ledmatrix.drawPixel(x, y, brightLevel);
    else
      ledmatrix.drawPixel(x, y, 0);
    randomLast = millis();
  }
}

void randomColorPixel(uint8_t wait, int count) 
{
  if(millis() - randomPixelLast >= wait)
  {
    if(randomIteration == 0) // only change the color at beginning of cycle
    {
      r = randomColorPicker(0,5);
      g = randomColorPicker(0,5);
      b = randomColorPicker(0,5);
    }
    float red = (r/10) * cleanPot;
    int redAdj = (int)red;
    float green = (g/10) * cleanPot;
    int greenAdj = (int)green;
    float blue = (b/10) * cleanPot;
    int blueAdj = (int)blue;
    Serial.print(rawPot);
    Serial.print("    ");
    Serial.print(cleanPot);
    Serial.print("    ");
    Serial.print(r);
    Serial.print("    ");
    Serial.println(redAdj);
//    Serial.print(redAdj);
//    Serial.print("    ");
//    Serial.print(greenAdj);
//    Serial.print("    ");
//    Serial.print(blueAdj);
//    Serial.println("");
    int pixel = random(12);
    int state = random(2);
    if(state == 0) // pixel off
    {
      strip.setPixelColor(pixel, strip.Color(0, 0, 0));
    }
    else
    {
      strip.setPixelColor(pixel, strip.Color(redAdj, greenAdj, blueAdj));
    }
    strip.show();
    randomPixelLast = millis();
    if(randomIteration < count)
    {
      randomIteration++;
    }
    else
    {
      randomIteration = 0;
    }
  } 
}



void randomColorWipe(uint8_t wait, int d) 
{
  unsigned long colorWipeClock = millis();
  if(colorWipeClock - colorWipeLast >= wait)
  {
    if(i == 0) // only change the color at beginning of cycle
    {
      long randomRed = randomColorPicker(0,5);
      long randomGreen = randomColorPicker(0,5);
      long randomBlue = randomColorPicker(0,5);
      c = strip.Color(randomRed, randomGreen, randomBlue);
    }
    strip.setPixelColor(i, c);
    if(d != 0)
    {
      strip.setPixelColor(i-d, strip.Color(0,0,0));
    }
    strip.show();
    colorWipeLast = colorWipeClock;
    if(i < strip.numPixels()-1)
    {
      i++;
    }
    else
    {
      i = 0;
    }
  } 
}

void TimingISR()
{
  halfsecond ++;
  Update = ON;
  if(halfsecond == 2){
    second ++;
    if(second == 60)
    {
      minute ++;
      if(minute == 60)
      {
        hour ++;
        if(hour == 24)hour = 0;
        minute = 0;
      }
      second = 0;
    }
    halfsecond = 0;
  }
 // Serial.println(second);
  ClockPoint = (~ClockPoint) & 0x01;
}
void TimeUpdate(void)
{
  if(ClockPoint)tm1637.point(POINT_ON);
  else tm1637.point(POINT_OFF);
  TimeDisp[0] = hour / 10;
  TimeDisp[1] = hour % 10;
  TimeDisp[2] = minute / 10;
  TimeDisp[3] = minute % 10;
  Update = OFF;
}
