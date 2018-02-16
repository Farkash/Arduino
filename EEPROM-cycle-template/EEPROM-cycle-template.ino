#include <EEPROM.h>

int toggleState;
int EEPROMaddress = 0;
int amount_of_cycles = 7;

void setup()
{
  toggleState = EEPROM.read(EEPROMaddress);
  upToggleState();

  Serial.begin(9600);
  Serial.println(toggleState);
}

void loop()
{
  switch(toggleState){
  case 1:

    break;
  case 2:
    break;
    
  case 3:
    break;
    
  case 4:
  
    break;
  case 5:
  
    break;
  case 6:
  
    break;
  case 7:
  
    break;
  default:
    EEPROM.write(EEPROMaddress, 0);
  } 
}

//Ups or resets the state counter
void upToggleState(){
  toggleState++;
  if (toggleState > amount_of_cycles) toggleState = 1;
  EEPROM.write(EEPROMaddress, toggleState);
}


