int sensorPin = A0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  long sensorValue = analogRead(sensorPin);
  Serial.println(sensorValue);
}
