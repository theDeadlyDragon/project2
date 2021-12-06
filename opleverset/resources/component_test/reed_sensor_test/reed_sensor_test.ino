void setup() {
  Serial.begin(115200);
  pinMode(16, INPUT);

}

void loop() {
  Serial.print(digitalRead(16));  
}
