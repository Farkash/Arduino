//Charlieplexing and Pulse-Width-Modulation with Adafruit IS31FL3731 Driver
//and Adafruit mini-led matrix

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_IS31FL3731.h>
#include "Myfont.h"
#include "Arduino.h"
#include <EEPROM.h>

Adafruit_IS31FL3731 matrix = Adafruit_IS31FL3731();

int toggleState;
int EEPROMaddress = 0;

void setup(){
  toggleState = EEPROM.read(EEPROMaddress);
  upToggleState();

  Serial.begin(9600);
  Serial.println("ISSI manual animation test");
  if (! matrix.begin()) {
    Serial.println("IS31 not found");
    while (1);
  }
  Serial.println("IS31 Found!");
  }

void loop(){
  switch(toggleState){
  case 1:
    greeting();
    break;
  case 2:
    circles();
    break;
  default:
    EEPROM.write(EEPROMaddress, 0);
  }
}

//declare methods here:
//Ups or resets the state counter
void upToggleState(){
  toggleState++;
  if (toggleState > 2) toggleState = 1;
  EEPROM.write(EEPROMaddress, toggleState);
}


// Draw circles
void circles() {
  matrix.clear();
  matrix.drawCircle(8,4, 4, 64);
  matrix.drawCircle(8,4, 2, 32);
  delay(2000);
}

//text
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

