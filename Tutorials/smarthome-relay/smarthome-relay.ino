void setup() {
  Serial.begin(115200);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D8, OUTPUT);
  pinMode(D6, OUTPUT);
}

void loop() {
  digitalWrite(D1, 1);
  delay(1000);
  digitalWrite(D1, 0);
  delay(500);

  digitalWrite(D2, 1);
  delay(1000);
  digitalWrite(D2, 0);
  delay(500);

  digitalWrite(D8, 1);
  delay(1000);
  digitalWrite(D8, 0);
  delay(500);

  digitalWrite(D6, 1);
  delay(1000);
  digitalWrite(D6, 0);
  delay(500);
}
