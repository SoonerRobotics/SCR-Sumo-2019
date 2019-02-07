#include "Ultrasonic.h"
#include <Arduino.h>

Ultrasonic::Ultrasonic() {
  
}

Ultrasonic::Ultrasonic(int dataPin) {
  this->dataPin = dataPin;
  pinMode(dataPin, INPUT);
}

double Ultrasonic::getRawDistance() {
  return analogRead(dataPin);
}
