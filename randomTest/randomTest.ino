int redPin = 11;
int greenPin = 10;
int bluePin = 9;

void setup()
{
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT); 

  Serial.begin(9600);
}

void loop()
{
//    randomFlash();
//  red();
//  redRandomDelay();
  swirlCycle();
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


void randomFlash() {
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
  delay(500);
//  delay(random(5,1000));
//  setColor(0,0,0);
//  delay(50);
  Serial.println(String(convertedR) + "," + String(convertedG) + "," + String(convertedB));
}


void red() {
  setColor(127,0,0);
}

void redRandomDelay(){
  setColor(127,0,0);
  delay(random(50, 5000));
  setColor(0,0,0);
  delay(random(5,500));
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
