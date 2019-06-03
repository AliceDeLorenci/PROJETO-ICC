#define BUT 7

void setup() {
  Serial.begin(9600);
  pinMode(BUT,INPUT);

}

void loop() {
  Serial.println(digitalRead(BUT));
  delay(1000);

}
