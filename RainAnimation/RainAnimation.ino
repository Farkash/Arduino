/**************************************
Rain animation for 8x7 Charlieplex LED matrix
Steve Farkas
January 13th, 2018

Hardware Connections:

IMPORTANT:  The Charlieplex LED board is designed for 2.0 - 5.2V!
            Higher voltages can damage the LEDs.

 Arduino Pin | Charlieplex Board
 ------------|------------------
      4      |         A
      5      |         B
      6      |         C
      7      |         D
      8      |         E
      9      |         F
      10     |         G
      11     |         H

Resources:
Include Chaplex.h, SparkFun_LED_8x7.h
The Chaplex library can be found at: 
http://playground.arduino.cc/Code/Chaplex

****************************************/
//Libraries to include
#include <SparkFun_LED_8x7.h>
#include <Chaplex.h>

// Global variables
byte led_pins[] = {4, 5, 6, 7, 8, 9, 10, 11}; // Pins for LEDs
int x;
int y;
int state;


void setup() {
  // Initialize and clear display
  Plex.init(led_pins);
  Plex.clear();
  Plex.display();
}

void loop() {
  Plex.pixel(x, y, state);
  Plex.display();
  delay(10);
}
