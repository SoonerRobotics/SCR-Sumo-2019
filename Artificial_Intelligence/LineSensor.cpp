#include "LineSensor.h"
#include <Arduino.h>
#include <ArduinoSort.h>

LineSensor::LineSensor() {
  
}

LineSensor::LineSensor(int dataPin) {
  this->dataPin = dataPin;
  pinMode(dataPin, INPUT);
  // Collect sample values of ground reflectance at robot's starting position
  int values[20];
  for (int i = 0; i < 20; i++) {
    values[i] = analogRead(dataPin);
  }
  sortArray(values, 20);
  
  // Set threshold to median of sample values
  // TODO: Replace 1 with different value determined by testing line sensor
  reflectanceThreshold = values[20 / 2] - 1;
}

LineSensor::LineSensor(int dataPin, int threshold) {
  this->dataPin = dataPin;
  pinMode(dataPin, INPUT);
  reflectanceThreshold = threshold;
}

bool LineSensor::seeWhite() {
  return (analogRead(dataPin) < reflectanceThreshold);
}

int LineSensor::getRawReflectance() {
  return analogRead(dataPin);
}
