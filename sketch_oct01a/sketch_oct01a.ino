const int led = 13;
const int sonar = A0; // Pin of sonar sensor (analog)
const int SAMPLES = 250; // Number of samples to average sensor reading over
const double OFFSET = 0.0; //Calibrate sensor by offsetting the distance it reads

double total;
double average;
double distance;

void setup() {
  // put your setup code here, to run once:
  pinMode(led, OUTPUT);
  pinMode(sonar, INPUT);
  Serial.begin(9600);
}

void loop() {
  total = 0;
  for (int i = 0; i < SAMPLES; i++) {
    total += analogRead(sonar);
  }
  average = total / (double)SAMPLES;
  distance = average / 2.0 + OFFSET; // Distance in inches
  //distance = 2.54 * (average / 2.0) + OFFSET; // Distance in centimeters
  /*
  if (distance >= 20) {
    digitalWrite(led, LOW);
  }
  else if (distance < 20 && distance > 10) {
    digitalWrite(led, HIGH);
  }
  else {
    digitalWrite(led, HIGH);
    delay(50);
    digitalWrite(led, LOW);
    delay(50);
  }
  */
  Serial.println(distance);
}
