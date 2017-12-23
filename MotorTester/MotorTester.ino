void setup() {
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(0, OUTPUT);
  pinMode(2, OUTPUT);

}

void loop() {
  
  digitalWrite(5, 1);
  digitalWrite(4, 1);
  digitalWrite(0, 1);
  digitalWrite(2, 1);
  delay(5000);
  
  digitalWrite(5, 0);
  digitalWrite(4, 0);
  digitalWrite(0, 0);
  digitalWrite(2, 1);
  delay(1000);
  
  digitalWrite(5, 0);
  digitalWrite(4, 1);
  digitalWrite(0, 1);
  digitalWrite(2, 0);
  delay(1000);

  digitalWrite(5, 1);
  digitalWrite(4, 0);
  digitalWrite(0, 0);
  digitalWrite(2, 1);
  delay(1000);
  
}

