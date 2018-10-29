#include <Adafruit_NeoPixel.h>
#include <Wire.h>
#include <SparkFun_LED_8x7.h>
#include <Chaplex.h>
int neoPixelCount = 24;
int neoPixelPin = 3;
byte led_pins[] = {4, 5, 6, 7, 8, 9, 10, 11}; 
unsigned long colorWipeLast = 0;
int i = 0;
unsigned long colorFadeLast = 0;
int j = 0;
int colorFadeTop = 0;
uint32_t c;
unsigned long randomPixelLast;
int randomIteration = 0;
int cycleTracker = 0;
int a;
int b;
int state;
unsigned long MatrixRandomLast = 0;
int colorFadeIteration = 0;
int randomColorWipeIteration = 0;
int randomPixelIteration = 0;


Adafruit_NeoPixel strip = Adafruit_NeoPixel(neoPixelCount, neoPixelPin, NEO_GRB + NEO_KHZ800);

bool oldState = HIGH;
int showType = 0;

void setup() 
{
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  Plex.init(led_pins);
  Plex.clear();
  Plex.display();

  // Seed our random number generator with an analog voltage read
  randomSeed(analogRead(0));
}

void loop() {

if(millis() < 10)
{
  Plex.scrollText("Live long and prosper Marissa! -Steve", 1);
}

if(millis() > 7000)
{
  randomMatrix(10);
}


switch(cycleTracker)
{
  case 0: colorWipe(strip.Color(150, 0, 0), 20, 0);
    break;
  case 1: colorWipe(strip.Color(0, 150, 0), 20, 0);
    break;
  case 2: colorWipe(strip.Color(0, 0, 150), 20, 0);
    break;
  case 3: colorWipe(strip.Color(150, 150, 0), 20, 0);
    break;
  case 4: colorWipe(strip.Color(150, 0, 150), 20, 0);
    break;
  case 5: colorWipe(strip.Color(0, 150, 150), 20, 0);
    break;
  case 6: colorFade(1, 10, 2);
    break;
  case 7: randomPixel(20, 100, 50);
    break;
  case 10: randomColorWipe(20, 0, 3);
    break;
}

} // end loop

void randomMatrix(int wait) 
{
  unsigned long matrixRandomClock = millis();
  a = random(0, 8);
  b = random(0, 7);
  state = random(0, 2);
  if(matrixRandomClock - MatrixRandomLast > wait)
  {
    Plex.pixel(a, b, state);
    Plex.display();
    MatrixRandomLast = matrixRandomClock;
  }
}



void colorWipe(uint32_t c, uint8_t wait, int d) 
{
  unsigned long colorWipeClock = millis();
  if(colorWipeClock - colorWipeLast >= wait)
  {
    Serial.println(colorWipeClock);
    Serial.println(colorWipeLast);
    strip.setPixelColor(i, c);
    if(d != 0)
    {
      strip.setPixelColor(i-d, strip.Color(0,0,0));
    }
    strip.show();
    colorWipeLast = colorWipeClock;
    if(i < strip.numPixels())
    {
      i++;
    }
    else
    {
      i = 0;
      cycleTracker++;
    }
  } 
}


void colorFade(int colorType, uint8_t wait, int iterations) 
{
  unsigned long colorFadeClock = millis();
  switch(colorType)
  {
    case 0: c = strip.Color(j, 0, 0); // colorType 0 = red;
      break;
    case 1: c = strip.Color(0, j, 0); // colorType 1 = green;
      break;
    case 2: c = strip.Color(0, 0, j); // colorType 2 = blue;
      break;
    case 3: c = strip.Color(j, j, 0); // colorType 3 = yellow;
      break;
    case 4: c = strip.Color(j, 0, j); // colorType 4 = purple;
      break;
    case 5: c = strip.Color(0, j, j); // colorType 5 = teal;
      break;
  }
  if(colorFadeTop == 0)
  {
    if(colorFadeClock - colorFadeLast >= wait)
    {
      for(uint16_t i=0; i<strip.numPixels(); i++) 
      {
        strip.setPixelColor(i, c);
        strip.show();
      }
      colorFadeLast = colorFadeClock;
      if(j < 255)
      {
        j+=5;
      }
      else
      {
        colorFadeTop = 1;
      }
    }
  }

  if(colorFadeTop == 1)
  {
    if(colorFadeClock - colorFadeLast >= wait)
    {
      for(uint16_t i=0; i<strip.numPixels(); i++) 
      {
        strip.setPixelColor(i, c);
        strip.show();
      }
      colorFadeLast = colorFadeClock;
      if(j > 0)
      {
        j-=5;
      }
      else
      {
        colorFadeTop = 0;
        colorFadeIteration++;
      }
    }
  }

  if(colorFadeIteration >= iterations)
  {
    cycleTracker ++;
  }
}


void randomColorWipe(uint8_t wait, int d, int iterations) 
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
    if(i < strip.numPixels())
    {
      i++;
    }
    else
    {
      i = 0;
      randomColorWipeIteration++;
    }
  } 

  if(randomColorWipeIteration >= iterations)
  {
    for(int t = 0; t<strip.numPixels(); t++)
    {
      strip.setPixelColor(t, strip.Color(0, 0, 0));
    }
    cycleTracker++;
  }
}


long randomColorPicker(int a, int b)
{
  int rint = random(a,b);
  int diff = b - a;
  float interval = 256 / diff;
  int intervalInt = (int)interval;
  return rint * intervalInt;
}


// random pixels, controlled color sequence.
// random pixels contantly 
// random color for x iterations
// Randomly pick a pixel with random(0,24).
// Randomly pick a state, on or off, with random(0,2).
// Have a counter that's tracking how many times a pixel is targeted.
// Utilize randomColorPicker. Cuz that's cool
void randomPixel(uint8_t wait, int x, int iterations) 
{
  unsigned long colorWipeClock = millis();
  if(colorWipeClock - randomPixelLast >= wait)
  {
    if(randomIteration == 0) // only change the color at beginning of cycle
    {
      long randomRed = randomColorPicker(0,5);
      long randomGreen = randomColorPicker(0,5);
      long randomBlue = randomColorPicker(0,5);
      c = strip.Color(randomRed, randomGreen, randomBlue);
    }
    // Random pixel indexing logic goes here
    int pixel = random(24);
    int state = random(2);
    if(state == 0) // pixel off
    {
      strip.setPixelColor(pixel, strip.Color(0, 0, 0));
    }
    else
    {
      strip.setPixelColor(pixel, c);
    }
    strip.show();
    randomPixelLast = colorWipeClock;
    if(randomIteration < x)
    {
      randomIteration++;
    }
    else
    {
      randomIteration = 0;
      randomPixelIteration++;
    }
  } 

  if(randomPixelIteration > iterations)
  {
    cycleTracker++;
  }
}



