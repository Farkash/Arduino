#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif
#define PIN 0
long randomPixelLast = 0;
int randomIteration = 0;
int r, g, b;

int sensorPin = 5;    // select the input pin for the potentiometer
int sensorValue;  // variable to store the value coming from the sensor

Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, PIN, NEO_GRB + NEO_KHZ800);

void setup() 
{
  #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif  
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() 
{
  sensorValue = analogRead(sensorPin);
  randomPixel(500, 50);
}

long randomColorPicker(int a, int b)
{
  int rint = random(a,b);
  int diff = b - a;
  float interval = 255 / diff;
  int intervalInt = (int)interval;
  return rint * intervalInt;
}

void randomPixel(int count, int wait)
{
  if (millis() - randomPixelLast >= wait)
  {
    if (randomIteration == 0) // only change color at beginning of cycle
    {
      r = randomColorPicker(0,5);
      g = randomColorPicker(0,5);
      b = randomColorPicker(0,5);
    }
    float red = (r/10) * (sensorValue / 105);
    int redAdj = (int)red;
    float green = (g/10) * (sensorValue / 105);
    int greenAdj = (int)green;
    float blue = (b/10) * (sensorValue / 105);
    int blueAdj = (int)blue;
    int x = random(12);
    int state = random(2);
    if(state == 0)
    {
      strip.setPixelColor(x, strip.Color(0, 0, 0));
    }
    else
    {
      strip.setPixelColor(x, strip.Color(redAdj, greenAdj, blueAdj));
    }
    strip.show();
    if (randomIteration <= count)
    {
      randomIteration++;
    }
    else
    {
      randomIteration = 0;
    }
    randomPixelLast = millis();
  }
}



