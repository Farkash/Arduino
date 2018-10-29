// Iron Man Repulsor
#include <Adafruit_NeoPixel.h>
#define BUTTON_PIN1   4
#define BUTTON_PIN2   3
int LASER_PIN = 2;
int neoPixelCount = 12;
int neoPixelPin = 6;
int state = HIGH;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(neoPixelCount, neoPixelPin, NEO_GRB + NEO_KHZ800);

bool oldState1 = HIGH;
bool oldState2 = HIGH;
int showType = 0;
unsigned long colorWipeLast = 0;
int i = 0;
unsigned long colorFadeLast = 0;
int j = 0;
int colorFadeTop = 0;
uint32_t c;
unsigned long randomPixelLast;
int randomIteration = 0;
unsigned long pulsorLast = 0;

void setup() 
{
  Serial.begin(9600);
  pinMode(BUTTON_PIN1, INPUT_PULLUP);
  pinMode(BUTTON_PIN2, INPUT_PULLUP);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  randomSeed(analogRead(0));
}

void loop() 
{

  digitalWrite(LASER_PIN, HIGH);
  delay(100);
  // Get current button state.
  bool newState1 = digitalRead(BUTTON_PIN1);
  bool newState2 = digitalRead(BUTTON_PIN2);

  // Check if state changed from high to low (button press).
  if (newState1 == LOW && oldState1 == HIGH) 
  {
    // Short delay to debounce button.
    delay(20);
    // Check if button is still low after debounce.
    newState1 = digitalRead(BUTTON_PIN1);
    if (newState1 == LOW) 
    {
      showType++;
      if (showType > 10)
        showType=0;
//      startShow(showType);
    }
  }
  // Set the last button state to the old state.
  oldState1 = newState1;
  
  startShow(showType);

  //laser
  if (newState2 == LOW && oldState2 == HIGH) 
  {
    // Short delay to debounce button.
    delay(20);
    // Check if button is still low after debounce.
    newState2 = digitalRead(BUTTON_PIN2);
    if (newState2 == LOW) 
    {
      if (state == HIGH)
        state = LOW;
      else
        state = HIGH;
    }
    digitalWrite(LASER_PIN, state);
  }



  
}

void startShow(int i) {
  switch(i){
    case 0: colorWipe(strip.Color(0, 0, 0), 20, 1); // Black/off
            break;
    case 1: colorFade(6,20);
            break;
    case 2: colorFade(1,20);
            break;
    case 3: colorFade(2,20);
            break;
    case 4: colorFade(3,20);
            break;
    case 5: colorFade(4,20);
            break;
    case 6: colorFade(5,20);
            break;
    case 7: randomColorWipe(20, 0);
            break;
    case 8: randomPixel(20, 100);
            break;
    case 9: randomPixel(10, 200);
            break;
    case 10: randomPixel(5, 400);
            break;
//    case 5: colorWipe(strip.Color(0, 0, 255), 20);
//            break;
//    case 6: colorWipe(strip.Color(255, 255, 0), 20);
//            break;
//    case 7: rainbow(20);
//            break;
//    case 8: rainbowCycle(20);
//            break;
//    case 9: theaterChaseRainbow(50);
//            break;
  }
}


// Repulsor
//void pulsor(uint32_t c, uint8_t wait)
//{
//  unsigned long pulsorClock = millis();
//  if(pulsorClock - pulsorLast < wait)
//  {
//    for(int q = 0; q < strip.numPixels(); q++)
//    {
//      strip.setPixelColor(q, c);
//      strip.show();
//    }
//    pulsorLast = pulsorClock;
//  }
//}




//// Fill the  one after the other with a color
void colorWipe(uint32_t c, uint8_t wait, int d) 
{
  unsigned long colorWipeClock = millis();
  if(colorWipeClock - colorWipeLast >= wait)
  {
    Serial.println(colorWipeClock);
    Serial.println(colorWipeLast);
    strip.setPixelColor(i, c);
    strip.setPixelColor(i-d, strip.Color(0,0,0));
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


// colorFade
void colorFade(int colorType, uint8_t wait) 
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
    case 6: c = strip.Color(j, j, j); // colorType 6 = white;
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
      }
    }
  }
}


// random colorWipe 
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




