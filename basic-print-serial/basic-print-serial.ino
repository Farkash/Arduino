//A variable to hold the level of coolness
int coolFactor = 3;
 
void setup() {
 
  Serial.begin(9600);
 
}
 
void loop() {
 
  //Send the value of coolFactor to the the Serial port.
  //So we can see it in the serial monitor window
  Serial.print(coolFactor);
 
}



