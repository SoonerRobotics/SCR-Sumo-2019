#include "LineSensor.h"
#include <Arduino.h>

LineSensor::LineSensor() {
  
}

LineSensor::LineSensor(int dataPin) {
  this->dataPin = dataPin;
  reflectanceThreshold = analogRead(dataPin);
  pinMode(dataPin, INPUT);
}

LineSensor::LineSensor(int dataPin, int threshold) {
  this->dataPin = dataPin;
  reflectanceThreshold = threshold;
  pinMode(dataPin, INPUT);
}

bool LineSensor::seeWhite() {
  return (analogRead(dataPin) < reflectanceThreshold);
}

int LineSensor::getRawReflectance() {
  return analogRead(dataPin);
}
