#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_IS31FL3731.h>

// If you're using the full breakout...
Adafruit_IS31FL3731 ledmatrix = Adafruit_IS31FL3731();
// If you're using the FeatherWing version
//Adafruit_IS31FL3731_Wing ledmatrix = Adafruit_IS31FL3731_Wing();


// The lookup table to make the brightness changes be more visible
uint8_t sweep[] = {1, 2, 3, 4, 6, 8, 10, 15, 20, 30, 40, 60, 60, 40, 30, 20, 15, 10, 8, 6, 4, 3, 2, 1};
int bright[] = {0, 0, 0, 0, 10, 50, 80, 255};

void setup() {
  Serial.begin(9600);
  Serial.println("ISSI swirl test");
  
  if (! ledmatrix.begin()) {
    Serial.println("IS31 not found");
    while (1);
  }
  Serial.println("IS31 found!");

  randomSeed(analogRead(0)); 
}

void loop() {
  for (int z = 0; z < 8; z++) {
    int x = random(0, 17);
    int y = random(0, 10);  
    ledmatrix.drawPixel(x, y, bright[z]);
    delay(10);  
  }
  
  

  }

