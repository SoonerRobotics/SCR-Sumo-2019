#include <ArduinoSort.h>
const int NUM_SAMPLES = 20;
int data[NUM_SAMPLES];
int medians[5];
void setup() {
  // put your setup code here, to run once:
  pinMode(A0, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i = 0; i < NUM_SAMPLES; i++) {
    data[i] = analogRead(A0);
  }

  sortArray(data, NUM_SAMPLES);
  Serial.println(data[NUM_SAMPLES / 2]);
  //Serial.println(analogRead(A0));
}
