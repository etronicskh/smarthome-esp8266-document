#define OUTPUT1 D1
#define OUTPUT2 D2
#define OUTPUT3 D8
#define OUTPUT4 D6

void setup() {
  Serial.begin(115200);
  pinMode(OUTPUT1, OUTPUT);
  pinMode(OUTPUT2, OUTPUT);
  pinMode(OUTPUT3, OUTPUT);
  pinMode(OUTPUT4, OUTPUT);
}

void loop() {
  digitalWrite(OUTPUT1, 1);
  delay(1000);
  digitalWrite(OUTPUT1, 0);
  delay(500);

  digitalWrite(OUTPUT2, 1);
  delay(1000);
  digitalWrite(OUTPUT2, 0);
  delay(500);

  digitalWrite(OUTPUT3, 1);
  delay(1000);
  digitalWrite(OUTPUT3, 0);
  delay(500);

  digitalWrite(OUTPUT4, 1);
  delay(1000);
  digitalWrite(OUTPUT4, 0);
  delay(500);
}
