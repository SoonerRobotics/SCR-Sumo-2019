//Diagnostic Code, makes the built in LED blink on the Arduino.
//Replace LED_BUILTIN with a pin # to use another LED.
const int LED = LED_BUILTIN;

void setup() {
  pinMode(LED, OUTPUT);
}

void loop() {
  blink();
}

void blink() {
  digitalWrite(LED, HIGH);
  delay(1000);
  digitalWrite(LED, LOW);
  delay(1000);
}
