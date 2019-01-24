void setup() {
  Serial.begin(9600);
  pinMode(7,OUTPUT);
  pinMode(6,INPUT);
  //for 3-pin ultrasonic
  //pinMode(A0, INPUT);
}

void loop() {
  // Send out pulse
  digitalWrite(7,HIGH);
  delayMicroseconds(10);
  digitalWrite(7,LOW);
  // Wait for echo
  Serial.println(pulseIn(6,HIGH)/148.0);
  
  /* Code for 3-pin ultrasonic
  double sum = 0;
  for (int i = 0; i < 500; i++) {
    sum += analogRead(A0);
  }
  Serial.println(sum / 5000.0);
  */
}
