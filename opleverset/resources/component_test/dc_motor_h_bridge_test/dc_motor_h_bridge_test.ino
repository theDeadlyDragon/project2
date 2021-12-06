void setup() {
  // put your setup code here, to run once:
  pinMode(16, OUTPUT);
  pinMode(17, OUTPUT);

  digitalWrite(16, LOW);
  digitalWrite(17, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(16, LOW);
  digitalWrite(17, HIGH);

  delay(3000);

  digitalWrite(17, LOW);
  digitalWrite(16, HIGH);

  delay(3000);

}
