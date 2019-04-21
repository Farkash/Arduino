#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#define NEO_PIN 6
#define BRIGHTNESS 5

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix
  (
    32, 8, NEO_PIN,
    NEO_MATRIX_BOTTOM     + NEO_MATRIX_RIGHT +
    NEO_MATRIX_ROWS + NEO_MATRIX_PROGRESSIVE,
    NEO_GRB            + NEO_KHZ800
  );

#define BUTTON_PIN 12
#define BUZZER_PIN 5
long randomPixelLast = 0;
int randomIteration = 0;
int previousGreeting = 0;
int x = matrix.width();
int r, g, b;
bool oldState = HIGH;
int showType = 0;

class Pot
{
  // Class Member Variable
  int potPin;

  // Constructor - creates a pot instance 
  // and initializes the member variable
  public:
  Pot(int pin)
  {
    potPin = pin;
  }

  int adjustVolts()
  {
    // get the reading from the potentiometer
    int rawVoltage = analogRead(potPin);
    int voltage;
    
    // convert the voltage into more usable number as a multiplier
    // I just want it to return values between 1 and 10
    if(rawVoltage < 50)
    {
      voltage = 1;
    }
    else if(rawVoltage >= 50 & rawVoltage < 100)
    {
      voltage = 2;
    }
    else if(rawVoltage >= 100 & rawVoltage < 200)
    {
      voltage = 3;
    }
    else if(rawVoltage >= 200 & rawVoltage < 300)
    {
      voltage = 4;
    }
    else if(rawVoltage >= 300 & rawVoltage < 400)
    {
      voltage = 5;
    }
    else if(rawVoltage >= 400 & rawVoltage < 500)
    {
      voltage = 6;
    }
    else if(rawVoltage >= 500 & rawVoltage < 600)
    {
      voltage = 7;
    }
    else if(rawVoltage >= 600 & rawVoltage < 700)
    {
      voltage = 8;
    }
    else if(rawVoltage >= 700 & rawVoltage < 800)
    {
      voltage = 9;
    }
    else if(rawVoltage > 800)
    {
      voltage = 10;
    }

    return voltage;
  }
  
};

// Create instances of the potentiometer class
Pot pot1(A1);
Pot pot2(A2);
Pot pot3(A3);

void setup() 
{
  Serial.begin(9600);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
//  matrix.setBrightness(BRIGHTNESS);
  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setTextColor(matrix.Color(0, 50, 0));  
  //for random:
//  randomSeed(analogRead(A6));
}

void loop() 
{ 
  // Get current button state.
  bool newState = digitalRead(BUTTON_PIN);
//  Serial.println(newState);

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
      if (showType > 1)
        showType=0;
    }
  }
  // Set the last button state to the old state.
  oldState = newState;
  if(millis() < 8000)
  {
    matrix.fillScreen(0);
    matrix.setCursor(x, 0);
    matrix.print(F("Hello David!"));
    if(--x < -70) 
    {
      x = matrix.width();
    }
    matrix.show();
    delay(100); 
  }
  else
  {
    startShow(showType);
  }
}

void startShow(int i) {
  switch(i){
    case 0: randomPixel();
            break;
    case 1: matrix.clear();
            explosions();
            break;
  }
}


long randomColorPicker(int a, int b)
{
  int rint = random(a,b);
  int diff = b - a;
  float interval = 255 / diff;
  int intervalInt = (int)interval;
  return rint * intervalInt;
}

void randomPixel()
{
  int count = 50 * pot2.adjustVolts();
  int wait = (11 - pot3.adjustVolts());
  Serial.println(wait);
  if (millis() - randomPixelLast >= wait)
  {
    if (randomIteration == 0) // only change color at beginning of cycle
    {
      r = randomColorPicker(0,5);
      g = randomColorPicker(0,5);
      b = randomColorPicker(0,5);
    }
    float red = (r/10) * pot1.adjustVolts();
    int redAdj = (int)red;
    float green = (g/10) * pot1.adjustVolts();
    int greenAdj = (int)green;
    float blue = (b/10) * pot1.adjustVolts();
    int blueAdj = (int)blue;
    int x = random(8);
    int y = random(8);
    int state = random(2);
    if(state == 0)
    {
      matrix.drawPixel(x, y, matrix.Color(0, 0, 0));
    }
    else
    {
      matrix.drawPixel(x, y, matrix.Color(redAdj, greenAdj, blueAdj));
    }
    matrix.show();
    if (randomIteration <= count)
    {
      randomIteration++;
    }
    else
    {
      randomIteration = 0;
    }
    randomPixelLast = millis();
  }
}

void explosions()
{
  int count = 50 * pot2.adjustVolts();
  int wait = (11 - pot3.adjustVolts());
  Serial.println(wait);
  if (millis() - randomPixelLast >= wait)
  {
    if (randomIteration == 0) // only change color at beginning of cycle
    {
      r = randomColorPicker(0,5);
      g = randomColorPicker(0,5);
      b = randomColorPicker(0,5);
    }
    float red = (r/10) * pot1.adjustVolts();
    int redAdj = (int)red;
    float green = (g/10) * pot1.adjustVolts();
    int greenAdj = (int)green;
    float blue = (b/10) * pot1.adjustVolts();
    int blueAdj = (int)blue;
    int x = random(8);
    int y = random(8);
    int state = random(2);
    if(state == 0)
    {
      matrix.drawCircle(x, y, matrix.Color(0, 0, 0));
    }
    else
    {
      matrix.drawPixel(x, y, matrix.Color(redAdj, greenAdj, blueAdj));
    }
    matrix.show();
    if (randomIteration <= count)
    {
      randomIteration++;
    }
    else
    {
      randomIteration = 0;
    }
    randomPixelLast = millis();
  }
}
