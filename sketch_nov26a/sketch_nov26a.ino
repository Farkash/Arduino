int buzzPin = 4;

void setup() {

}

void loop() {
  tone(buzzPin, 1000, 500);
  delay(1000);
  tone(buzzPin, 500, 500);
  delay(1000);
  tone(buzzPin, 1500, 500);
  delay(1000);
  tone(buzzPin, 2000, 500);
  delay(1000);
//  noTone(buzzPin);
}
