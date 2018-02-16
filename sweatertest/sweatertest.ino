#include <EEPROM.h>
#include <Adafruit_NeoPixel.h>
#include <math.h>

int toggleState;
int EEPROMaddress = 0;

void setup()
{
  toggleState = EEPROM.read(EEPROMaddress);
  upToggleState();

  Serial.begin(9600);

}

void loop() {
Serial.println(toggleState);
delay(300);
}

//Ups or resets the state counter
void upToggleState(){
  toggleState++;
  if (toggleState > 3) toggleState = 0;
  EEPROM.write(EEPROMaddress, toggleState);
}






