#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_IS31FL3731.h>

// If you're using the full breakout...
Adafruit_IS31FL3731 ledmatrix = Adafruit_IS31FL3731();
// If you're using the FeatherWing version
//Adafruit_IS31FL3731_Wing ledmatrix = Adafruit_IS31FL3731_Wing();


// The lookup table to make the brightness changes be more visible
uint8_t sweep[] = {1, 2, 3, 4, 6, 8, 10, 15, 20, 30, 40, 60, 60, 40, 30, 20, 15, 10, 8, 6, 4, 3, 2, 1};
unsigned long randomLast = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("ISSI swirl test");

  if (! ledmatrix.begin()) {
    Serial.println("IS31 not found");
    while (1);
  }
  Serial.println("IS31 found!");
  randomSeed(analogRead(0));
}

void loop() {
  // animate over all the pixels, and set the brightness from the sweep table
//  for (uint8_t incr = 0; incr < 24; incr++)
//    for (uint8_t x = 0; x < 16; x++)
//      for (uint8_t y = 0; y < 9; y++)
//        ledmatrix.drawPixel(x, y, sweep[(x+y+incr)%24]);
//  delay(20);

randomPixel(10);
  

}

void randomPixel(int wait)
{
  unsigned long randomClock = millis();
  if(randomClock - randomLast > wait)
  {
    int x = random(0,16);
    int y = random(0,9);
    int state = random(2);
    int bright = random(1, 4);
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
    Serial.println(bright);
    Serial.println(brightLevel);
    if(state == 0)
      ledmatrix.drawPixel(x, y, brightLevel);
    else
      ledmatrix.drawPixel(x, y, 0);
    randomLast = randomClock;
  }

}


