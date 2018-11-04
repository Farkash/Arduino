// Box for Maegan
// 24-LED NeoPixel strip, piezo buzzer, Adafruit 9x16 Charlieplexed LED Matrix

#include <Adafruit_NeoPixel.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_IS31FL3731.h>
const int buzzerPin = 5;
const float tempo = 0.8; 

// notes for Harry Potter theme song
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

#define NP_COUNT 24   // Amount of neopixels in strip
#define NP_PIN    2   // Digital IO pin connected to the NeoPixels
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NP_COUNT, NP_PIN, NEO_GRB + NEO_KHZ800);

unsigned long prevMillisstrip = 0;
unsigned long prevMillisMatrix = 0;
unsigned long prevMillisBuzz = 0;

// constants won't change:
int stripCounter = 0;

// instantiate an LED matrix object using the constructor:
Adafruit_IS31FL3731 matrix = Adafruit_IS31FL3731();
int fillx = 2;
int filly = 0;
long minute = 60000;
unsigned long lastMinute = 0;
long lastPixel = 0;
int fillMax = 5;
int fillMin = 2;
int slideMax = 13;
int fillGoFlag = 1;
long perimeterLast = 0;
int pxit = 0;
int pyit = 0;
long perimeterWait = 1277;
//long perimeterWait = 10;
int perimeterMode = 1; // 1 == on, 0 == off.
int perimeterx[] =
{
  0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
  15, 15, 15, 15, 15, 15, 15, 15, 14, 13, 12, 11, 10,
  9, 8, 7, 6, 5, 4, 3, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0
};
int perimetery[] =
{
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  1, 2, 3, 4, 5, 6, 7, 8, 8 ,8, 8, 8, 8, 8, 8, 8, 
  8, 8, 8, 8, 8, 8, 8, 7, 6, 5, 4, 3, 2, 1, 0
};
long radiusLast = 0;
int expx = random(16);
int expy = random(9);
int radius = 0;
unsigned long randomPixelLast;
int randomIteration = 0;
uint32_t c;
unsigned long colorWipeLast = 0;
int i = 0;

int noteIndex = 0;

void setup() {
  // Setup print to console for debugging:
  Serial.begin(9600);

  strip.begin();
  strip.show(); // Initialize all pixels to 'off'

  if (! matrix.begin()) {
    Serial.println("IS31 not found");
    while (1);
  }
  Serial.println("IS31 found!");

//  delay(1000);
 
}

void loop() 
{  
  timeFiller(300);
  perimeter();
  randomColorWipe(80, 0);
  harryPotterSong();
//  stripMagic(500, 0);
//  randomPixel(20, 100);
}


////////////////function declaration section////////////////

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
    if(i < strip.numPixels())
    {
      i++;
    }
    else
    {
      i = 0;
    }
  } 
}

long randomColorPicker(int a, int b)
{
  int rint = random(a,b);
  int diff = b - a;
  float interval = 15 / diff;
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
void randomPixel(uint8_t wait, int x) 
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
    }
  } 
}

void explosions(int wait)
{
  if(millis() - radiusLast > wait)
  {
    matrix.clear();
    matrix.drawCircle(expx, expy, radius, 255);
    matrix.drawCircle(expx, expy, radius +1, 100);
    matrix.drawCircle(expx, expy, radius +2, 10);
    radiusLast = millis();
    if(radius < 12)
    {
      radius++;
    }
    else
    {
      radius = 0;
      expx = random(16);
      expy = random(9);
    }
  }
}


void timeFiller(int pixelWait)
{
  if(fillGoFlag == 1)
  {
      // count a full minute since start:
    if(millis() - lastMinute >= minute)
    {
      if(millis() - lastPixel > pixelWait)
      {
        matrix.drawPixel(fillx, filly, 50); // turn on pixel
        matrix.drawPixel(fillx, filly-1, 0); // turn off one behind it
        lastPixel = millis();
        if(filly <= fillMax)
        {
          filly++; // make the pixels fall down
        }
        else
        {
          filly = 0;
          if(fillMax >= fillMin)
          {
            fillMax--;
            lastMinute = millis();
            Serial.println(lastMinute);
          }
          else
          {
            fillMax = 5;
            lastMinute = millis();
            if(fillx < slideMax)
            {
              fillx++;
            }
            else
            {
              fillGoFlag = 0; // don't do anything if the max range of the graph is filled
            }
          }
        }
      }
    }
  }
  else
  {
    explosions(5);
  }
}


void perimeter()
{
  if(fillGoFlag == 1)
  {
    if(millis() - perimeterLast > perimeterWait)
    {
      if(perimeterMode == 1)
      {
        matrix.drawPixel(perimeterx[pxit], perimetery[pyit], 50); // turn on pixel
      }
      else
      {
        matrix.drawPixel(perimeterx[pxit], perimetery[pyit], 0);
      }
  //    matrix.drawPixel(fillx, filly-1, 0); // turn off one behind it
      perimeterLast = millis();
      if(pxit < 48)
      {
        pxit++;
        pyit++;
      }
      else
      {
        pxit = 0;
        pyit = 0;
        if(perimeterMode == 1)
        {
          perimeterMode = 0;
        }
        else
        {
          perimeterMode = 1;
        }
      }
    }
  }
}

void harryPotterSong()
{
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


void stripMagic(int wait, int nLag)
{
  unsigned long currMillisstrip = millis();
  // just turn all the strip colors on to a teal for now:
  for(int a = 0; a < 24; a++)
  {
    strip.setPixelColor(a, 50, 50, 0);
  }
  if (currMillisstrip - prevMillisstrip >= wait) 
  {
    strip.setPixelColor(stripCounter, 0, 50, 50);
    if(nLag != 0)
    {
      strip.setPixelColor(stripCounter-nLag, 0, 0, 0);
    }
    strip.show();
    prevMillisstrip = currMillisstrip;
    if (stripCounter < NP_COUNT) 
    {
      stripCounter++;
    } 
    else 
    {
      stripCounter = 0;
    } 
  }
}


