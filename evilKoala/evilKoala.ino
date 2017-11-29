#include <EEPROM.h>

int toggleState;
int EEPROMaddress = 0;
int redPin = 11;
int greenPin = 10;
int bluePin = 9;

//uncomment this line if using a Common Anode LED
//#define COMMON_ANODE

void setup()
{
  toggleState = EEPROM.read(EEPROMaddress);
  upToggleState();
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT); 

  Serial.begin(9600);
  Serial.println(toggleState);
}

void loop()
{
  switch(toggleState){
  case 1:
    red();
    break;
  case 2:
    redRandomDelay();
    break;
  case 3:
    flashRed();
    break;
  case 4:
    flashRedDim();
    break;
  case 5:
    flashGreen();
    break;
  case 6:
    flashGreenDim();
    break;
  case 7:
    flashBlue();
    break;
  case 8:
    flashBlueDim();
    break;
  case 9:
    flashYellow();
    break;
  case 10:
    flashYellowDim();
    break;
  case 11:
    flashPurple();
    break;
  case 12:
    flashPurpleDim();
    break;
  case 13:
    flashAqua();
    break;
  case 14:
    flashAquaDim();
    break;
  case 15:
    randomColor();
    break;
  case 16:
    randomColorAndDelay();
    break;
  case 17:
    swirlCycle();
    break;
  default:
    EEPROM.write(EEPROMaddress, 0);
  } 
}

void setColor(int red, int green, int blue)
{
  #ifdef COMMON_ANODE
    red = 255 - red;
    green = 255 - green;
    blue = 255 - blue;
  #endif
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);  
}

//Ups or resets the state counter
void upToggleState(){
  toggleState++;
  if (toggleState > 17) toggleState = 1;
  EEPROM.write(EEPROMaddress, toggleState);
}

void swirlCycle() {
  for(int i = 0; i < 256; i++){
    setColor(i,0,0);
    delay(10);
  }

  for(int i = 255; i > -1; i--){
    setColor(i,0,0);
    delay(10);
  }
  setColor(0,0,0);
//  delay(200);

  for(int i = 0; i < 256; i++){
    setColor(0,i,0);
    delay(10);
  }

  for(int i = 255; i > -1; i--){
    setColor(0,i,0);
    delay(10);
  }
  setColor(0,0,0);
//  delay(200);

  for(int i = 0; i < 256; i++){
    setColor(0,0,i);
    delay(10);
  }

  for(int i = 255; i > -1; i--){
    setColor(0,0,i);
    delay(10);
  }
  setColor(0,0,0);
//  delay(200);

  for(int i = 0; i < 256; i++){
    setColor(i,i,0);
    delay(10);
  }

  for(int i = 255; i > -1; i--){
    setColor(i,i,0);
    delay(10);
  }
  setColor(0,0,0);
//  delay(200);

  for(int i = 0; i < 256; i++){
    setColor(i,0,i);
    delay(10);
  }

  for(int i = 255; i > -1; i--){
    setColor(i,0,i);
    delay(10);
  }
  setColor(0,0,0);
//  delay(200);

  for(int i = 0; i < 256; i++){
    setColor(0,i,i);
    delay(10);
  }

  for(int i = 255; i > -1; i--){
    setColor(0,i,i);
    delay(10);
  }
  setColor(0,0,0);
//  delay(200);

  for(int i = 0; i < 256; i++){
    setColor(i,255-i,0);
    delay(10);
  }

  for(int i = 255; i > -1; i--){
    setColor(i,255-i,0);
    delay(10);
  }
  setColor(0,0,0);
//  delay(200);

  for(int i = 0; i < 256; i++){
    setColor(i,i,255-i);
    delay(10);
  }

  for(int i = 255; i > -1; i--){
    setColor(i,i,255-i);
    delay(10);
  }
  setColor(0,0,0);
//  delay(200);
  
  for(int i = 0; i < 256; i++){
    setColor(i,255-i,i);
    delay(10);
  }

  for(int i = 255; i > -1; i--){
    setColor(i,255-i,i);
    delay(10);
  }
  setColor(0,0,0);
//  delay(200);
}

void red() {
  setColor(80,0,0);
}

void redRandomDelay(){
  setColor(127,0,0);
  delay(random(50, 5000));
  setColor(0,0,0);
  delay(random(5,500));
}

void flashRed() {
  setColor(255,0,0);
  delay(50);
  setColor(0,0,0);
  delay(50);
}

void flashRedDim() {
  setColor(50,0,0);
  delay(50);
  setColor(0,0,0);
  delay(50);
}

void flashGreen() {
  setColor(0,255,0);
  delay(50);
  setColor(0,0,0);
  delay(50);
}

void flashGreenDim() {
  setColor(0,50,0);
  delay(50);
  setColor(0,0,0);
  delay(50);
}

void flashBlue() {
  setColor(0,0,255);
  delay(50);
  setColor(0,0,0);
  delay(50);
}

void flashBlueDim() {
  setColor(0,0,50);
  delay(50);
  setColor(0,0,0);
  delay(50);
}

void flashYellow() {
  setColor(255,255,0);
  delay(50);
  setColor(0,0,0);
  delay(50);
}

void flashYellowDim() {
  setColor(50,50,0);
  delay(50);
  setColor(0,0,0);
  delay(50);
}

void flashPurple() {
  setColor(255,0,255);
  delay(50);
  setColor(0,0,0);
  delay(50);
}

void flashPurpleDim() {
  setColor(50,0,50);
  delay(50);
  setColor(0,0,0);
  delay(50);
}

void flashAqua() {
  setColor(0,255,255);
  delay(50);
  setColor(0,0,0);
  delay(50);
}

void flashAquaDim() {
  setColor(0,050,50);
  delay(50);
  setColor(0,0,0);
  delay(50);
}

void randomColor() {
  int randR = random(0,5);
  int randG = random(0,5);
  int randB = random(0,5);
  int convertedR;
  int convertedG;
  int convertedB;
  
  switch(randR) {
    case 0:
      convertedR = 0;
      break;
    case 1:
      convertedR = 63;
      break;
    case 2:
      convertedR = 127;
      break;
    case 3:
      convertedR = 191;
      break;
    case 4:
      convertedR = 255;
      break;
    default:
      convertedR = 0;
  }

  switch(randG) {
    case 0:
      convertedG = 0;
      break;
    case 1:
      convertedG = 63;
      break;
    case 2:
      convertedG = 127;
      break;
    case 3:
      convertedG = 191;
      break;
    case 4:
      convertedG = 255;
      break;
    default:
      convertedG = 0;
  }

    switch(randB) {
    case 0:
      convertedB = 0;
      break;
    case 1:
      convertedB = 63;
      break;
    case 2:
      convertedB = 127;
      break;
    case 3:
      convertedB = 191;
      break;
    case 4:
      convertedB = 255;
      break;
    default:
      convertedB = 0;
  }
  
  setColor(convertedR,convertedG, convertedB);
  delay(300);
  Serial.println(String(convertedR) + "," + String(convertedG) + "," + String(convertedB));
}


void randomColorAndDelay() {
  int randR = random(0,5);
  int randG = random(0,5);
  int randB = random(0,5);
  int convertedR;
  int convertedG;
  int convertedB;
  
  switch(randR) {
    case 0:
      convertedR = 0;
      break;
    case 1:
      convertedR = 63;
      break;
    case 2:
      convertedR = 127;
      break;
    case 3:
      convertedR = 191;
      break;
    case 4:
      convertedR = 255;
      break;
    default:
      convertedR = 0;
  }

  switch(randG) {
    case 0:
      convertedG = 0;
      break;
    case 1:
      convertedG = 63;
      break;
    case 2:
      convertedG = 127;
      break;
    case 3:
      convertedG = 191;
      break;
    case 4:
      convertedG = 255;
      break;
    default:
      convertedG = 0;
  }

    switch(randB) {
    case 0:
      convertedB = 0;
      break;
    case 1:
      convertedB = 63;
      break;
    case 2:
      convertedB = 127;
      break;
    case 3:
      convertedB = 191;
      break;
    case 4:
      convertedB = 255;
      break;
    default:
      convertedB = 0;
  }
  
  setColor(convertedR,convertedG, convertedB);
  delay(random(5,1000));
  Serial.println(String(convertedR) + "," + String(convertedG) + "," + String(convertedB));
}

