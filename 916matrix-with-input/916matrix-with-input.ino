// TODO:
// Add a second button to control the mode. 
// Perfect setup: one button that changes potentiometer function,
// and one that changes the animation.

#include <Wire.h>
//#include <Adafruit_GFX.h>
#include <Adafruit_IS31FL3731.h>

// If you're using the full breakout...
Adafruit_IS31FL3731 ledmatrix = Adafruit_IS31FL3731();
// If you're using the FeatherWing version
//Adafruit_IS31FL3731_Wing ledmatrix = Adafruit_IS31FL3731_Wing();


// The lookup table to make the brightness changes be more visible
uint8_t sweep[] = {1, 2, 3, 4, 6, 8, 10, 15, 20, 30, 40, 60, 60, 40, 30, 20, 15, 10, 8, 6, 4, 3, 2, 1};
#define BUTTON_PIN   5
bool oldState = HIGH;
int mode = 0;
unsigned long randomLast = 0;
int potPin = A0;
int wait = 10;
int brightness = 10;
int text = 0;
int buzzerPin = 4;

#define DELAY 150             //Sets the time each generation is shown
#define RESEEDRATE 100        //Sets the rate the world is re-seeded
#define SIZEX 16   //Sets the X axis size
#define SIZEY 9   //Sets the Y axis size
byte world[2][SIZEX][SIZEY];  //Creates a double buffer world
const int density = 50;       //Sets density % during seeding
int geck = 0;                 //Counter for re-seeding


/////////////////////////////////////////////////////////////////////////////
//
// You can tweak these values to create a custom DNA molecule :)
//

const float stretch = 0.44;           // The width of each sine wave. Smaller values create wider sine waves. I like 0.44 .

const float phaseIncrement = 0.3;     // How fast the sines move. I like 0.1 .

// The phase of the "darker" sine wave will drift (relative to the "lighter" sine wave).
// This makes the DoubleHelix more organic/hypnotic .
const float driftIncrement = 0.019;   // The speed it drifts back and forth. Larger == faster. I like 0.019 .
const float driftForce = 0.4;         // The visual amount of drift. I like 0.4 .

// On every other column, light the LEDs between the sine waves, resembling the nucleotides of a DNA molecule.
// This looks good if we switch between lighting odd columns, then even columns -- the molecule appears to be moving.
const float barPhaseIncrement = 0.09; // Bar movement speed. Plz use values between 0..1 . I like 0.09 .

// Brightness values. Range is 0..7
const byte lightSineBrightness = 7;
const byte darkSineBrightness = 3;
const byte barBrightness = 1;

// (End tweak section)
/////////////////////////////////////////////////////////////////////////////



// These values change every frame:
float phase = 0.0;              // This is how "far" we've travelled along the DNA.
float driftPhase = 0.0; 
float barPhase = 0.0;  

void setup() {
  Serial.begin(9600);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  if (! ledmatrix.begin()) {
    Serial.println("IS31 not found");
    while (1);
  }
  Serial.println("IS31 found!");

  randomSeed(analogRead(5));
  seedWorld();
  tone(buzzerPin, 500);
  delay(100);
  tone(buzzerPin, 1000);
  delay(100);
  tone(buzzerPin, 1500);
  delay(100);
  tone(buzzerPin, 2000);
  delay(100);
  tone(buzzerPin, 2500);
  delay(100);
  tone(buzzerPin, 3000);
  delay(100);
  tone(buzzerPin, 3500);
  delay(100);
  tone(buzzerPin, 4000);
  delay(100);
  tone(buzzerPin, 4500);
  delay(100);
  tone(buzzerPin, 5000);
  delay(100);
  tone(buzzerPin, 5500);
  delay(100);
  tone(buzzerPin, 6000);
  delay(100);
  tone(buzzerPin, 6500);
  delay(100);
  tone(buzzerPin, 7000);
  delay(100);
  tone(buzzerPin, 7500);
  delay(100);
  noTone(buzzerPin);
}

void loop() 
{
  bool newState = digitalRead(BUTTON_PIN);
  if (newState == LOW && oldState == HIGH) 
  {
    // Short delay to debounce button.
    delay(20);
    // Check if button is still low after debounce.
    newState = digitalRead(BUTTON_PIN);
    if (newState == LOW) 
    {
      mode++;
      if (mode > 1)
        mode = 0;
      
      ledmatrix.setTextSize(1);
      ledmatrix.setTextWrap(false);  // we dont want text to wrap so it scrolls nicely
      ledmatrix.setTextColor(100);
      ledmatrix.setRotation(2);
      for (int8_t x=0; x>=-60; x--) 
      {
        ledmatrix.clear();
        ledmatrix.setCursor(x,0);
        if (mode == 0)
        {
          ledmatrix.print("Brightness");
        }
        else if (mode == 1)
        {
          ledmatrix.print("Speed>>>>>");
        }
        delay(20);
      }
      
      Serial.print("mode:");
      Serial.println(mode);
    }
  }
  // Set the last button state to the old state.
  oldState = newState;

  int potValue = analogRead(potPin);

  // the button controls which variable to change.
  switch(mode)
  {
    case 0: brightness = map(potValue, 0, 1023, 0, 255); 
            Serial.println(brightness);
            break;
    case 1: wait = map(potValue, 0, 1023, 255, 0);
            break;
  }
  randomPixel(wait, brightness);
//  plasma();
//  life();
//  helix();
//  swirl();
}


void randomPixel(byte wait, byte brightness)
{
  if(millis() - randomLast > wait)
  {
    int x = random(0,16);
    int y = random(0,9);
    int state = random(2);
    if(state == 0)
      ledmatrix.drawPixel(x, y, brightness);
    else
      ledmatrix.drawPixel(x, y, 0);
    randomLast = millis();
  }
}

void plasma()
{
  /*
  Plasma
   written by Zach Archer http://zacharcher.com/
   
   NOTES:
   - Requires the LoLshield library to run. Get the library here: http://code.google.com/p/lolshield/downloads/
   - How to install the library: http://www.arduino.cc/en/Hacking/Libraries
   
   This sketch moves two points along Lissajious curves. See: http://en.wikipedia.org/wiki/Lissajous_curve
   The distances between each LED and each point are multiplied,
   then this value is shaped using a sine function, and this sets the brightness of each LED.
   */

  // Convenient 2D point structure
  struct Point {
    float x;
    float y;
  };



  float phase = 0.0;
  float phaseIncrement = 0.2;  // Controls the speed of the moving points. Higher == faster. I like 0.08 .
  float colorStretch = 0.11;    // Higher numbers will produce tighter color bands. I like 0.11 .


  // This function is called every frame.
  while(true) {
    phase += phaseIncrement;

    // The two points move along Lissajious curves, see: http://en.wikipedia.org/wiki/Lissajous_curve
    // We want values that fit the LED grid: x values between 0..13, y values between 0..8 .
    // The sin() function returns values in the range of -1.0..1.0, so scale these to our desired ranges.
    // The phase value is multiplied by various constants; I chose these semi-randomly, to produce a nice motion.
    Point p1 = { 
      (sin(phase*1.000)+1.0) * 7.5, (sin(phase*1.310)+1.0) * 4.0                 };
    Point p2 = { 
      (sin(phase*1.770)+1.0) * 7.5, (sin(phase*2.865)+1.0) * 4.0                 };

    byte row, col;

    // For each row...
    for( row=0; row<9; row++ ) {
      float row_f = float(row);  // Optimization: Keep a floating point value of the row number, instead of recasting it repeatedly.

      // For each column...
      for( col=0; col<16; col++ ) {
        float col_f = float(col);  // Optimization.

        // Calculate the distance between this LED, and p1.
        Point dist1 = { 
          col_f - p1.x, row_f - p1.y                                 };  // The vector from p1 to this LED.
        float distance = sqrt( dist1.x*dist1.x + dist1.y*dist1.y );

        // Calculate the distance between this LED, and p2.
        Point dist2 = { 
          col_f - p2.x, row_f - p2.y                                 };  // The vector from p2 to this LED.
        // Multiply this with the other distance, this will create weird plasma values :)
        distance *= sqrt( dist2.x*dist2.x + dist2.y*dist2.y );
        //distance += sqrt( dist2.x*dist2.x + dist2.y*dist2.y );  // Variation: weird linear color bands. Might need to increase colorStretch


        // Warp the distance with a sin() function. As the distance value increases, the LEDs will get light,dark,light,dark,etc...
        // You can use a cos() for slightly different shading, or experiment with other functions. Go crazy!
        float color_f = (sin( distance * colorStretch ) + 1.0) * 0.5;  // range: 0.0...1.0

        // Square the color_f value to weight it towards 0. The image will be darker and have higher contrast.
        color_f *= color_f;
        //color_f *= color_f*color_f*color_f;  // Uncomment this line to make it even darker :)

        // Scale the color up to 0..7 . Max brightness is 7.
//        LedSign::Set( col, row, byte( round(color_f * 7.0) ) );
        ledmatrix.drawPixel(col, row, byte(round(color_f * 30.0)));
      }
    }
    // There's so much math happening, it's already a bit slow ;) No need for extra delays!
    //delay( 20 );
  }
}


void life() 
{
  static byte boring = 0;
  byte changed = 0;

  // Birth and death cycle 
  for (byte x = 0; x < SIZEX; x++) { 
    for (byte y = 0; y < SIZEY; y++) {
      // Default is for cell to stay the same
      byte alive = world[0][x][y];
//      LedSign::Set(x, y, alive);
      ledmatrix.drawPixel(x, y, (alive*255));

      byte count = neighbours(x, y); 
      if (count == 3 && !alive) {
        // A new cell is born
        alive = 1; 
        ++changed;
      } else if ((count < 2 || count > 3) && alive) {
        // Cell dies
        alive = 0;
        ++changed;
      }
      world[1][x][y] = alive;
    }
  }
  
  // Copy next generation into place
  for (byte x = 0; x < SIZEX; x++) { 
    for (byte y = 0; y < SIZEY; y++) {
      world[0][x][y] = world[1][x][y];
    }
  }

  if (changed)
    boring = 0;
  else
    ++boring;

  //Counts and then checks for re-seeding
  //Otherwise the display will die out at some point
  if (boring >= 5 || ++geck >= RESEEDRATE) {
    geck = 0;
    seedWorld();
  }

  delay(DELAY);
}

//Re-seeds based off of RESEEDRATE
void seedWorld()
{
  for (byte i = 0; i < SIZEX; i++) 
  {
    for (byte j = 0; j < SIZEY; j++) 
    {
      if (random(100) < density)
        world[0][i][j] = 1;
      else
        world[0][i][j] = 0;
    } 
  }
}

//Runs the rule checks, including screen wrap
byte neighbours(byte x, byte y) 
{
  return world[0][(x + 1) % SIZEX][y] + 
    world[0][x][(y + 1) % SIZEY] + 
    world[0][(x + SIZEX - 1) % SIZEX][y] + 
    world[0][x][(y + SIZEY - 1) % SIZEY] + 
    world[0][(x + 1) % SIZEX][(y + 1) % SIZEY] + 
    world[0][(x + SIZEX - 1) % SIZEX][(y + 1) % SIZEY] + 
    world[0][(x + SIZEX - 1) % SIZEX][(y + SIZEY - 1) % SIZEY] + 
    world[0][(x + 1) % SIZEX][(y + SIZEY - 1) % SIZEY];
}

void helix() 
{
  phase += phaseIncrement;  // Move the sine waves forward.
  
  // The "darker" sine wave drifts (relative to the "lighter" sine wave).
  driftPhase += driftIncrement;
  
  // Increment the position of the bars.
  barPhase += barPhaseIncrement;
  if( barPhase > 1.0 ) barPhase -= 1.0;  // Wrap this value between 0..1 .
  
  // We'll hilite either the even columns, or odd columns, depending on the value of barPhase.
  boolean drawEvenBars = (barPhase < 0.5);
  
  byte row, col;
  
  // For each column of LEDs...
  for( col=0; col<16; col++ ) {
  
    // This is the "raw" value for the lighter sine wave. Range: -1.0...1.0
    float lightSineThisColumn = sin( phase + float(col)*stretch );
    
    // Scale the "raw" value and round it off, so the range is 0..8 . This is the LED we're going to light in this column.
    int lightSine = int( round( lightSineThisColumn*4.0 ) ) + 4;
    
    // driftPhase controls the phase drift of the "darker" sine.
    // The drift amount is derived from this sin() function, so it will drift back and forth.
    // Orbit around 2.1, which is about 1/3 phase offset from the lighter sine wave (2*PI/3). Looks pretty good.
    float drift = 2.1 + (driftForce * sin( driftPhase ));
    
    // This is the LED we're going to light for the "dark" sine wave.
    // This is similar to computing the lightSine value, but it's compacted into one line :P
    int darkSine = int( round( sin(phase+drift+float(col)*stretch)*4.0 ) ) + 4;

    // For each LED within the column...
    for( row=0; row<9; row++ ) {
      
      // Does this LED belong to our light sine wave?      
      if( row==lightSine ) {
//        LedSign::Set( col, row, lightSineBrightness );  // The third argument is the brightness. Max bright == 7.
        ledmatrix.drawPixel(col, row, (lightSineBrightness*36));
        
      // Does this LED belong to our dark sine wave?
      } else if( row==darkSine ) {
//        LedSign::Set( col, row, darkSineBrightness );  // The third argument is the brightness.
        ledmatrix.drawPixel(col, row, (darkSineBrightness*36));
        
      } else {
        // This LED doesn't belong to either sine wave. So we'll turn it off, unless it belongs to a vertical bar.
        int color = 0;  // 0 == unlit
        
        // Alternate even/odd columns:
        //   If col is an odd number, (col & 0x1) evaluates to true. (Example: 13 == B1101, rightmost bit is 1, so it's odd!)
        //   The ^ operator is binary XOR. So this statement evaluates true if _one_ condition is met, but _not_ both.
        if( (col & 0x1) ^ (drawEvenBars) ) {
        
          // If lightSine is above this LED, and darkSine is below, then this LED belongs to a vertical bar.
          if( lightSine < darkSine ) {
            if( lightSine<row && row<darkSine ) {
              color = barBrightness;
            }
          
          // If darkSine is above, and lightSine is below, this LED belongs to a vertical bar.
          } else if( darkSine < lightSine ) {
            if( darkSine<row && row<lightSine ) {
              color = barBrightness;
            }
          }
        }
        
//        LedSign::Set( col, row, color );
        ledmatrix.drawPixel(col, row, (color*36));
      }
    }
  }
  
//  LedSign::Flip(true);
}



void swirl()
{
  // animate over all the pixels, and set the brightness from the sweep table
  for (uint8_t incr = 0; incr < 24; incr++)
    for (uint8_t x = 0; x < 16; x++)
      for (uint8_t y = 0; y < 9; y++)
        ledmatrix.drawPixel(x, y, sweep[(x+y+incr)%24]);
  delay(20);
}
