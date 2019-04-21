int a0Pin = A0;    // select the input pin for the potentiometer
int a0Value;  // variable to store the value coming from the pot
int a1Pin = A1;    // select the input pin for the potentiometer
int a1Value;  // variable to store the value coming from the pot
int a2Pin = A2;    // select the input pin for the potentiometer
int a2Value;  // variable to store the value coming from the pot
int a3Pin = A3;    // select the input pin for the potentiometer
int a3Value;  // variable to store the value coming from the pot


void setup() {
  Serial.begin(9600);

}

void loop() {
  a0Value = analogRead(a0Pin);
  a1Value = analogRead(a1Pin);
  a2Value = analogRead(a2Pin);
  a3Value = analogRead(a3Pin);
  Serial.println(a0Value);
  Serial.println(a1Value);
  Serial.println(a2Value);
  Serial.println(a3Value);
}
