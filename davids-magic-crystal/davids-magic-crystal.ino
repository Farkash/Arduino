#include <Adafruit_NeoPixel.h>

#define neoPin 6
#define buttonPin 4
int buzzerPin = 2;
int potPin = A0;
bool oldState = HIGH;
int mode = 0;
unsigned long randomLast = 0;
int wait = 100;
unsigned long colorWipeLast = 0;
unsigned long colorCycleLast = 0;
int i = 0;
unsigned long colorFadeLast = 0;
int j = 0;
int colorFadeTop = 0;
uint32_t c;
int colorCounter = 0;
int cycleColor;
unsigned long rainbowLast = 0;
int rainbowx = 0;
int rainbowy = 0;

//Constructor
Adafruit_NeoPixel strip = Adafruit_NeoPixel(12, neoPin, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  Serial.begin(9600);
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() 
{
  
  bool newState = digitalRead(buttonPin);
  if (newState == LOW && oldState == HIGH) 
  {
    // Short delay to debounce button.
    delay(20);
    // Check if button is still low after debounce.
    newState = digitalRead(buttonPin);
    if (newState == LOW) 
    {
      mode++;
      if (mode > 4)
        mode = 0;
    }

  }
  // Set the last button state to the old state.
  oldState = newState;
  Serial.print("mode:");
  Serial.println(mode);

  int potValue = analogRead(potPin);
  int brightness = map(potValue, 0, 1023, 0, 255);


  // the button controls the mode
  switch(mode)
  {
    case 0: colorCycle(brightness, wait);
            break;
    case 1: colorCycle(brightness, wait*2);
            break;
    case 2: colorFade(0, 50);
            break;
    case 3: rainbow(50);
            break;
    case 4: rainbowCycle(50);
            break;
    
  }

}





// Fill the dots one after the other with a color
void colorCycle(int brightness, uint8_t wait) 
{
  unsigned long colorCycleClock = millis();
  if(colorCycleClock - colorCycleLast >= wait)
  {
    
    switch(colorCounter)
    {
      case 0: strip.setPixelColor(i, strip.Color(brightness, 0, 0));
              break;
      case 1: strip.setPixelColor(i, strip.Color(0, brightness, 0));
              break;
      case 2: strip.setPixelColor(i, strip.Color(0, 0, brightness));
              break;
    }
 
    strip.show();
    colorCycleLast = colorCycleClock;
    if(i < strip.numPixels()-1)
    {
      i++;
    }
    else
    {
      i = 0;
      if(colorCounter < 2)
      {
        colorCounter++;
      }
      else
      {
        colorCounter = 0;
      }
      
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



void rainbow(uint8_t wait) {
  
  unsigned long rainbowClock = millis();

  if(rainbowClock - rainbowLast >= wait)
  {

    strip.setPixelColor(rainbowy, Wheel((rainbowy+rainbowx) & 255));
    strip.show();
    
    if(rainbowx < 256)
    {
      rainbowx++;
    }
    else
    {
      rainbowx = 0;
    }

    if(rainbowy < strip.numPixels())
    {
      rainbowy++;
    }
    else
    {
      rainbowy = 0;
    }
    
    rainbowLast = rainbowClock;
  }

}









// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {

//  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
//    for(i=0; i< strip.numPixels(); i++) {
//      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
//    }
//    strip.show();
//    delay(wait);
//  }


  unsigned long rainbowClock = millis();

  if(rainbowClock - rainbowLast >= wait)
  {

    strip.setPixelColor(rainbowy, Wheel(((rainbowy * 256 / strip.numPixels()) + rainbowx) & 255));
    strip.show();
    
    if(rainbowx < 256*5)
    {
      rainbowx++;
    }
    else
    {
      rainbowx = 0;
    }

    if(rainbowy < strip.numPixels())
    {
      rainbowy++;
    }
    else
    {
      rainbowy = 0;
    }
    
    rainbowLast = rainbowClock;
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
