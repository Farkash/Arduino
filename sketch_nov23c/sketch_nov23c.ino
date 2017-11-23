//Charlieplexing and Pulse-Width-Modulation with Adafruit IS31FL3731 Driver
//and Adafruit mini-led matrix

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_IS31FL3731.h>
#include "Myfont.h"
#include "Arduino.h"
#include <EEPROM.h>

Adafruit_IS31FL3731 matrix = Adafruit_IS31FL3731();


void setup(){
  Serial.begin(9600);
  Serial.println("ISSI manual animation test");
  if (! matrix.begin()) {
    Serial.println("IS31 not found");
    while (1);
  }
  Serial.println("IS31 Found!");
  }

void loop(){
  greeting();
}

void greeting() {
  matrix.setTextSize(1);
  matrix.setTextWrap(false);  // we dont want text to wrap so it scrolls nicely
  matrix.setTextColor(50);
  for (int8_t x=0; x>=-48; x--) {
    matrix.clear();
    matrix.setCursor(x,0);
    matrix.print("Hey Sis!");
    delay(50);
  }
  for (int8_t x=0; x>=-48; x--) {
    matrix.clear();
    matrix.setCursor(x,0);
    matrix.print("Fun right?!");
    delay(50);
  }
}

