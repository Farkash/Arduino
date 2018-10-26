// EXISING PROBLEMS:
// The functions are only called if the state of the switch changes.
// Need to get it to call every time the main loop runs. 
// The switch should only change the function that it calls. 

// The loop only calls startShow() when the button pin reads LOW (switch is
// pressed). I need it to call startShow() every time the loop runs,
// and the button press only increments the showType.

// Iron Man Arc Reactor
#include <Adafruit_NeoPixel.h>
#define BUTTON_PIN   2
int neoPixelCount = 24;
int neoPixelPin = 6;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(neoPixelCount, neoPixelPin, NEO_GRB + NEO_KHZ800);

bool oldState = HIGH;
int showType = 0;
unsigned long colorWipeLast = 0;
int i = 0;
unsigned long colorFadeLast = 0;
int j = 0;
int colorFadeTop = 0;
uint32_t c;
unsigned long randomPixelLast;
int randomIteration = 0;

void setup() 
{
  Serial.begin(9600);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  randomSeed(analogRead(0));
}

void loop() 
{
  // Get current button state.
  bool newState = digitalRead(BUTTON_PIN);
  Serial.println(newState);

  // Check if state changed from high to low (button press).
  if (newState == LOW && oldState == HIGH) 
  {
    // Short delay to debounce button.
    delay(20);
    // Check if button is still low after debounce.
    newState = digitalRead(BUTTON_PIN);
    if (newState == LOW) 
    {
      showType++;
      if (showType > 8)
        showType=0;
//      startShow(showType);
      Serial.print("newState:");
      Serial.println(newState);
      Serial.print("showType:");
      Serial.println(showType);
    }
  }
  // Set the last button state to the old state.
  oldState = newState;
  
  startShow(showType);
}

void startShow(int i) {
  switch(i){
    case 0: colorWipe(strip.Color(0, 0, 0), 20, 1); // Black/off
            break;
    case 1: colorFade(0,20);
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

// Fill the  one after the other with a color
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


void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
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
// random color for 100 iterations
// once 100 is done, clean all quickly so there isn't any color overlap
// Randomly pick a pixel with random(0,24).
// Randomly pick a state, on or off, with random(0,2).
// Have a counter that's tracking how many times a pixel is targeted.
// Utilize randomColorPicker if possible. Cuz that's cool
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


// Wipe through colors sequentially, each round gets brighter, then down 
// to zero. Then switch color and go up and down again.
void colorStreakVaryBright()
{

  
}


