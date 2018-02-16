/****************************************************************
Demo.ino
LED Array 8x7 Charlieplex
Shawn Hymel @ SparkFun Electronics
February 10, 2015
https://github.com/sparkfun/LED_Array_8x7_Charlieplex

Gives a demo of all the functions of the LED array. Once
uploaded, click Tools -> Serial Monitor to see debugging
information.

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

Development environment specifics:
Written in Arduino 1.6.7
Tested with SparkFun RedBoard and BadgerStick (Interactive Badge)

This code is released under the [MIT License](http://opensource.org/licenses/MIT).

Please review the LICENSE.md file included with this example. If you have any questions 
or concerns with licensing, please contact techsupport@sparkfun.com.

Distributed as-is; no warranty is given.
****************************************************************/

#include <SparkFun_LED_8x7.h>
#include <Chaplex.h>

byte led_pins[] = {4, 5, 6, 7, 8, 9, 10, 11}; // Pins for LEDs
byte i;
byte x;
byte y;
byte radius;
int a;
int b;
int state;
const byte sparkfun_logo[] = { 0,0,0,0,1,0,0,0,
                               0,0,0,0,1,0,1,0,
                               0,0,1,0,1,1,1,0,
                               0,0,1,1,1,1,1,0,
                               0,0,1,1,1,1,0,0,
                               0,0,1,1,0,0,0,0,
                               0,0,1,0,0,0,0,0 };

void setup() {
  Serial.begin(9600);
  Serial.println(F("-----------------------"));
  Serial.println(F("SparkFun LED 8x7 - Demo"));
  Serial.println(F("-----------------------"));

  // Initialize and clear display
  Plex.init(led_pins);
  Plex.clear();
  Plex.display();
  
  // Seed our random number generator with an analog voltage read
  randomSeed(analogRead(0));

}

void loop() {

  // Show a bitmap
//  Serial.println(F("Draw a bitmap"));
  Plex.clear();
//  Plex.drawBitmap(sparkfun_logo);
//  Plex.display(); 
//  delay(2000);
  
  // Scroll some text
  Serial.println(F("Scroll some text"));
  Plex.scrollText("DATA SCIENCE & ENGINEERING", 1);
  delay(15000);

  Plex.clear();

  Plex.pixel(6,2,1);
  Plex.display();
  Plex.pixel(4,2,1);
  Plex.display();
  Plex.pixel(7,4,1);
  Plex.display();
  Plex.pixel(6,5,1);
  Plex.display();
  Plex.pixel(5,5,1);
  Plex.display();
  Plex.pixel(4,5,1);
  Plex.display();
  Plex.pixel(3,4,1);
  Plex.display();
  delay(500);
  Plex.clear();

  Plex.pixel(5,2,1);
  Plex.display();
  Plex.pixel(3,2,1);
  Plex.display();
  Plex.pixel(6,4,1);
  Plex.display();
  Plex.pixel(5,5,1);
  Plex.display();
  Plex.pixel(4,5,1);
  Plex.display();
  Plex.pixel(3,5,1);
  Plex.display();
  Plex.pixel(2,4,1);
  Plex.display();
  delay(500);
  Plex.clear();
  
  Plex.pixel(4,2,1);
  Plex.display();
  Plex.pixel(2,2,1);
  Plex.display();
  Plex.pixel(5,4,1);
  Plex.display();
  Plex.pixel(4,5,1);
  Plex.display();
  Plex.pixel(3,5,1);
  Plex.display();
  Plex.pixel(2,5,1);
  Plex.display();
  Plex.pixel(1,4,1);
  Plex.display();
  delay(500);
  Plex.clear();

  Plex.pixel(3,2,1);
  Plex.display();
  Plex.pixel(1,2,1);
  Plex.display();
  Plex.pixel(4,4,1);
  Plex.display();
  Plex.pixel(3,5,1);
  Plex.display();
  Plex.pixel(2,5,1);
  Plex.display();
  Plex.pixel(1,5,1);
  Plex.display();
  Plex.pixel(0,4,1);
  Plex.display();
  delay(500);
  Plex.clear();

  for(int k; k<1000; k++){
      // Choose a random number between 0 and 7 for x coordinate
    a = random(0, 8);
    
    // Choose a random number between 0 and 6 for y coordinate
    b = random(0, 7);
    
    // Flip a coin for the state of the LED
    state = random(0, 2);
    
    // Write to the LED display and wait before doing it again
    Plex.pixel(a, b, state);
    Plex.display();
    delay(10);
  }

  // Explosions!
  Serial.println(F("Display an animation"));
  for ( i = 0; i < 15; i++ ) {
    x = random(0, 8);
    y = random(0, 7);
    for ( radius = 0; radius < 12; radius++ ) {
      Plex.clear();
      Plex.circle(x, y, radius);
      Plex.circle(x, y, radius + 1);
      Plex.display();
      delay(30);
    }
  }

  // Draw a line (x0, x0, y1, y1)
  Plex.clear();
  Plex.line(0, 0, 7, 0);
  Plex.display();
  delay(200);

  Plex.clear();
  Plex.line(0, 0, 7, 6);
  Plex.display();
  delay(200);

  Plex.clear();
  Plex.line(0, 0, 0, 6);
  Plex.display();
  delay(200);

  Plex.clear();
  Plex.line(0, 0, 7, 0);
  Plex.display();
  delay(200);

  Plex.clear();
  Plex.line(0, 6, 7, 0);
  Plex.display();
  delay(200);

  Plex.clear();
  Plex.line(7, 0, 7, 6);
  Plex.display();
  delay(200);

  Plex.clear();
  Plex.line(0, 6, 7, 6);
  Plex.display();
  delay(200);




  Plex.clear();
  Plex.line(0, 0, 7, 0);
  Plex.display();
  delay(200);

  Plex.line(0, 0, 7, 6);
  Plex.display();
  delay(200);

  Plex.line(0, 0, 0, 6);
  Plex.display();
  delay(200);

  Plex.line(0, 6, 7, 0);
  Plex.display();
  delay(200);

  Plex.line(7, 0, 7, 6);
  Plex.display();
  delay(200);

  Plex.line(0, 6, 7, 6);
  Plex.display();
  delay(200);

  
  for(int i; i<10; i++){ 
    // Draw a rectangle (x, y, width, height)
    Plex.clear();
    Plex.rect(0, 0, 8, 7);
    Plex.display();
    delay(200);
  
    Plex.clear();
    Plex.rect(1, 1, 6, 5);
    Plex.display();
    delay(200);

    Plex.clear();
    Plex.rect(2, 2, 4, 3);
    Plex.display();
    delay(200);
  
    Plex.clear();
    Plex.rect(3, 3, 2, 1);
    Plex.display();
    delay(200);
  }

    for(int k; k<1000; k++){
      // Choose a random number between 0 and 7 for x coordinate
    a = random(0, 8);
    
    // Choose a random number between 0 and 6 for y coordinate
    b = random(0, 7);
    
    // Flip a coin for the state of the LED
    state = random(0, 2);
    
    // Write to the LED display and wait before doing it again
    Plex.pixel(a, b, state);
    Plex.display();
    delay(10);
  }
  
}



