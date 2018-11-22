// TODO:
// Add color transition logic

#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#define PIN 6
long randomPixelLast = 0;
int randomIteration = 0;
int r, g, b;

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix
  (
    8, 8, PIN,
    NEO_MATRIX_TOP     + NEO_MATRIX_RIGHT +
    NEO_MATRIX_COLUMNS + NEO_MATRIX_PROGRESSIVE,
    NEO_GRB            + NEO_KHZ800
  );

const uint16_t colors[] = 
{
  matrix.Color(255, 0, 0), 
//  matrix.Color(128, 64, 0), 
  matrix.Color(255, 255, 0), matrix.Color(0, 255, 0), 
  matrix.Color(0, 255, 255),  matrix.Color(255, 0, 255)
};

int sensorPin = A0;    // select the input pin for the potentiometer
int sensorValue;  // variable to store the value coming from the sensor

//  red, orange, yellow, green, teal, dark purple, violet, red, yellow. 

void setup() 
{
  Serial.begin(9600);
  matrix.begin();
  matrix.setTextWrap(false);
//  matrix.setBrightness(40);
  matrix.setTextColor(colors[0]);
  //for random:
//  randomSeed(analogRead(1));
}

void loop() 
{
  sensorValue = analogRead(sensorPin);
//  Serial.println(sensorValue);
  randomPixel(500, 5);
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
    int x = random(8);
    int y = random(8);
    int state = random(2);
    if(state == 0)
    {
      matrix.drawPixel(x, y, matrix.Color(0, 0, 0));
    }
    else
    {
      matrix.drawPixel(x, y, matrix.Color(redAdj, greenAdj, blueAdj));
    }
    matrix.show();
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


//  example of how I used to transition from one color to the next
//  for(int i = 0; i < 256;)
//    {
//      int x = random(0,8);
//      int y = random(0,8);
//      int state = random(0,2);
//      if(state == 0) {
//          matrix.drawPixel(x,y,matrix.Color(255-i,i,0));
//          i++;
//        }
//        else {
//          matrix.drawPixel(x,y,matrix.Color(0,0,0));
//        }
//        matrix.show();
//        delay(5);
//    }




