#include "FastLED.h"
CRGB leds[64];
void setup() { FastLED.addLeds<NEOPIXEL, 6>(leds, 256); }
void loop() { 
  static uint8_t hue = 0;
  FastLED.showColor(CHSV(hue++, 255, 255)); 
  delay(10);
}
