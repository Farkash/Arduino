#include <SparkFun_LED_8x7.h>
#include <Chaplex.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif


// to do:
// how to multitask arduino, so not dependent on other processes completing first. 
// https://learn.adafruit.com/multi-tasking-the-arduino-part-1/overview
// Add sound with piezo?
// Use switch to cycle through songs/turn sound off
// Use switch to power off board

byte led_pins[] = {2, 3, 4, 5, 6, 7, 8, 9}; // Pins for LEDs
const int buzz_pin = 10;
#define PIN 11
byte i;
byte x;
byte y;p
byte radius;
int a;
int b;
int state;
const int songspeed = 1.5; //Change to 2 for a slower version of the song, the bigger the number the slower the song

#define NOTE_C4  262   //Defining note frequency
#define NOTE_D4  294
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_G4  392
#define NOTE_A4  440
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_D5  587
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_G5  784
#define NOTE_A5  880
#define NOTE_B5  988

int notes[] = {       //Note of the song, 0 is a rest/pulse
   NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0, 
   NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0, 
   NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, 0,
   NOTE_A4, NOTE_G4, NOTE_A4, 0,
   
   NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0, 
   NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0, 
   NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, 0,
   NOTE_A4, NOTE_G4, NOTE_A4, 0,
   
   NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0, 
   NOTE_A4, NOTE_C5, NOTE_D5, NOTE_D5, 0, 
   NOTE_D5, NOTE_E5, NOTE_F5, NOTE_F5, 0,
   NOTE_E5, NOTE_D5, NOTE_E5, NOTE_A4, 0,
   
   NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0, 
   NOTE_D5, NOTE_E5, NOTE_A4, 0, 
   NOTE_A4, NOTE_C5, NOTE_B4, NOTE_B4, 0,
   NOTE_C5, NOTE_A4, NOTE_B4, 0,

   NOTE_A4, NOTE_A4, 
   //Repeat of first part
   NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0, 
   NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, 0,
   NOTE_A4, NOTE_G4, NOTE_A4, 0,

   NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0, 
   NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0, 
   NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, 0,
   NOTE_A4, NOTE_G4, NOTE_A4, 0,
   
   NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0, 
   NOTE_A4, NOTE_C5, NOTE_D5, NOTE_D5, 0, 
   NOTE_D5, NOTE_E5, NOTE_F5, NOTE_F5, 0,
   NOTE_E5, NOTE_D5, NOTE_E5, NOTE_A4, 0,
   
   NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0, 
   NOTE_D5, NOTE_E5, NOTE_A4, 0, 
   NOTE_A4, NOTE_C5, NOTE_B4, NOTE_B4, 0,
   NOTE_C5, NOTE_A4, NOTE_B4, 0,
   //End of Repeat

   NOTE_E5, 0, 0, NOTE_F5, 0, 0,
   NOTE_E5, NOTE_E5, 0, NOTE_G5, 0, NOTE_E5, NOTE_D5, 0, 0,
   NOTE_D5, 0, 0, NOTE_C5, 0, 0,
   NOTE_B4, NOTE_C5, 0, NOTE_B4, 0, NOTE_A4,

   NOTE_E5, 0, 0, NOTE_F5, 0, 0,
   NOTE_E5, NOTE_E5, 0, NOTE_G5, 0, NOTE_E5, NOTE_D5, 0, 0,
   NOTE_D5, 0, 0, NOTE_C5, 0, 0,
   NOTE_B4, NOTE_C5, 0, NOTE_B4, 0, NOTE_A4
};

int duration[] = {         //duration of each note (in ms) Quarter Note is set to 250 ms
  125, 125, 250, 125, 125, 
  125, 125, 250, 125, 125,
  125, 125, 250, 125, 125,
  125, 125, 375, 125, 
  
  125, 125, 250, 125, 125, 
  125, 125, 250, 125, 125,
  125, 125, 250, 125, 125,
  125, 125, 375, 125, 
  
  125, 125, 250, 125, 125, 
  125, 125, 250, 125, 125,
  125, 125, 250, 125, 125,
  125, 125, 125, 250, 125,

  125, 125, 250, 125, 125, 
  250, 125, 250, 125, 
  125, 125, 250, 125, 125,
  125, 125, 375, 375,

  250, 125,
  //Rpeat of First Part
  125, 125, 250, 125, 125,
  125, 125, 250, 125, 125,
  125, 125, 375, 125, 
  
  125, 125, 250, 125, 125, 
  125, 125, 250, 125, 125,
  125, 125, 250, 125, 125,
  125, 125, 375, 125, 
  
  125, 125, 250, 125, 125, 
  125, 125, 250, 125, 125,
  125, 125, 250, 125, 125,
  125, 125, 125, 250, 125,

  125, 125, 250, 125, 125, 
  250, 125, 250, 125, 
  125, 125, 250, 125, 125,
  125, 125, 375, 375,
  //End of Repeat
  
  250, 125, 375, 250, 125, 375,
  125, 125, 125, 125, 125, 125, 125, 125, 375,
  250, 125, 375, 250, 125, 375,
  125, 125, 125, 125, 125, 500,

  250, 125, 375, 250, 125, 375,
  125, 125, 125, 125, 125, 125, 125, 125, 375,
  250, 125, 375, 250, 125, 375,
  125, 125, 125, 125, 125, 500
};

Adafruit_NeoPixel strip = Adafruit_NeoPixel(24, PIN, NEO_GRB + NEO_KHZ800);


void setup() {
  Serial.begin(9600);

  // Initialize and clear display
  Plex.init(led_pins);
  Plex.clear();
  Plex.display();

  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  
  // Seed our random number generator with an analog voltage read
  randomSeed(analogRead(0));


 for (int i=0;i<203;i++){              //203 is the total number of music notes in the song
  int wait = duration[i] * songspeed;
  tone(buzzer,notes[i],wait);          //tone(pin,frequency,duration)
  delay(wait);}                        //delay is used so it doesn't go to the next loop before tone is finished playing
  //You can click reset on Arduino to replay the song
  

}

void loop() {

//  Plex.clear();
//  Plex.pixel(0,1,1);
//  Plex.pixel(1,0,1);
//  Plex.pixel(1,2,1);
//  Plex.pixel(2,1,1);
//  Plex.pixel(6,0,1);
//  Plex.pixel(5,1,1);
//  Plex.pixel(7,1,1);
//  Plex.pixel(6,2,1);
//  Plex.pixel(0,4,1);
//  Plex.pixel(1,5,1);
//  Plex.pixel(2,6,1);
//  Plex.pixel(3,6,1);
//  Plex.pixel(4,6,1);
//  Plex.pixel(5,6,1);
//  Plex.pixel(6,5,1);
//  Plex.pixel(7,4,1);
//  Plex.display();

//  for(int i = 0; 1 < 256; i++){
//    for(int j = 0; j < 16; j++){
//      strip.setPixelColor(j, strip.Color(i, 0, 255-i));
//      strip.show();
//    }
//  }
  

  colorWipe(strip.Color(0, 255, 0), 50); // Green
  colorWipe(strip.Color(255, 0, 0), 50); // Red
//  rainbow(20);
//  theaterChaseRainbow(10);
  
  // Explosions
//  for (i = 0; i < 5; i++) {
//    x = random(0, 8);
//    y = random(0, 7);
//    for ( radius = 0; radius < 12; radius++ ) {
//      Plex.clear();
//      Plex.circle(x, y, radius);
//      Plex.circle(x, y, radius + 1);
//      Plex.display();
//      delay(30);
//    }
//  }
  
  Plex.clear();
  Plex.scrollText("Live long and prosper", 1);
  delay(11000);
//  rainbowCycle(2);
//  rainbowCycle(2);
//  rainbowCycle(2);

//  Plex.clear();
//  Plex.pixel(0,1,1);
//  Plex.pixel(1,0,1);
//  Plex.pixel(1,2,1);
//  Plex.pixel(2,1,1);
//  Plex.pixel(6,0,1);
//  Plex.pixel(5,1,1);
//  Plex.pixel(7,1,1);
//  Plex.pixel(6,2,1);
//  Plex.pixel(0,4,1);
//  Plex.pixel(1,5,1);
//  Plex.pixel(2,6,1);
//  Plex.pixel(3,6,1);
//  Plex.pixel(4,6,1);
//  Plex.pixel(5,6,1);
//  Plex.pixel(6,5,1);
//  Plex.pixel(7,4,1);
//  Plex.display();

//  theaterChase(strip.Color(0, 127, 0), 50); // Green
//  colorWipe(strip.Color(0, 0, 255), 20);
//  colorWipe(strip.Color(0, 255, 0), 20);
//  colorWipe(strip.Color(255, 0, 0), 20);

//  for(int k; k<300; k++){
//      // Choose a random number between 0 and 7 for x coordinate
//    a = random(0, 8);
//    
//    // Choose a random number between 0 and 6 for y coordinate
//    b = random(0, 7);
//    
//    // Flip a coin for the state of the LED
//    state = random(0, 2);
//    
//    // Write to the LED display and wait before doing it again
//    Plex.pixel(a, b, state);
//    Plex.display();
//    delay(10);
//  }

//  for(int i; i<5; i++){ 
//    // Draw a rectangle (x, y, width, height)
//    Plex.clear();
//    Plex.rect(0, 0, 8, 7);
//    Plex.display();
//    delay(100);
//  
//    Plex.clear();
//    Plex.rect(1, 1, 6, 5);
//    Plex.display();
//    delay(100);
//
//    Plex.clear();
//    Plex.rect(2, 2, 4, 3);
//    Plex.display();
//    delay(100);
//  
//    Plex.clear();
//    Plex.rect(3, 3, 2, 1);
//    Plex.display();
//    delay(100);
//    Plex.clear();
//    Plex.display();
//  }
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
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
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
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



