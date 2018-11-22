class NeoFavs
{
  // Class Member Variables
  // These are initialized at startup
  int pin;      // the number of the LED pin
 
  // These maintain the current state
  int ledState;                 // ledState used to set the LED
  unsigned long previousMillis;   // will store last time LED was updated
 
  // Constructor - creates a NeoFavs
  // and initializes the member variables and state
  public:
  NeoFavs(int pin, long on, long off)
  {
  ledPin = pin;
  pinMode(ledPin, OUTPUT);     
    
  OnTime = on;
  OffTime = off;
  
  ledState = LOW; 
  previousMillis = 0;
  }
};
