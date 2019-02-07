#include "Motor.h"
#include <Arduino.h>

Motor::Motor() {
  
}

Motor::Motor(int directionPin, int speedPin, int enablePin, bool reversed) {
  this->directionPin = directionPin;
  this->speedPin = speedPin;
  this->enablePin = enablePin;
  this->reversed = reversed;
  this->enable(true);
  pinMode(directionPin, OUTPUT);
  pinMode(speedPin, OUTPUT);
  pinMode(enablePin, OUTPUT);
  power = 0.0;
}

/*
 * Set power of motor from -100.0 to 100.0
 * 
 * Scales power parameter from 0 to MAX_POWER% of 255
 */
void Motor::setPower(double power) {
  if (reversed) {
    this->power = -1 * power;
  }
  else {
    this->power = power;
  }
  if (this->power >= 0.0 && this->power <= 100.0) {
    digitalWrite(directionPin, HIGH);
    analogWrite(speedPin, MAX_POWER * 255.0 * abs(power) / 10000.0);
  }
  else if (this->power < 0.0 && this->power >= -100.0) {
    digitalWrite(directionPin, LOW);
    analogWrite(speedPin, MAX_POWER * 255.0 * abs(power) / 10000.0);
  }
}

void Motor::enable(bool enable) {
  if (enable) {
    digitalWrite(enablePin, HIGH);
  }
  else {
    digitalWrite(enablePin, LOW);
  }
}

/*
 * Defines which way is "forward" for the motor
 * 
 * Mainly used when setting up the motor to ensure it spins in the desired direction
 */
void Motor::setDirection(bool forward) {
  reversed = !forward;
}
