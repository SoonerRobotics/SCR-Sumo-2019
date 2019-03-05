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
  maxPower = 95;
  //setPwmFrequency(speedPin, 1);
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
    analogWrite(speedPin, maxPower * 255.0 * abs(power) / 10000.0);
  }
  else if (this->power < 0.0 && this->power >= -100.0) {
    digitalWrite(directionPin, LOW);
    analogWrite(speedPin, maxPower * 255.0 * abs(power) / 10000.0);
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

void Motor::setMaxPower(int power) {
  maxPower = power;
}

/**
 * Divides a given PWM pin frequency by a divisor.
 * 
 * The resulting frequency is equal to the base frequency divided by
 * the given divisor:
 *   - Base frequencies:
 *      o The base frequency for pins 3, 9, 10, and 11 is 31250 Hz.
 *      o The base frequency for pins 5 and 6 is 62500 Hz.
 *   - Divisors:
 *      o The divisors available on pins 5, 6, 9 and 10 are: 1, 8, 64,
 *        256, and 1024.
 *      o The divisors available on pins 3 and 11 are: 1, 8, 32, 64,
 *        128, 256, and 1024.
 * 
 * PWM frequencies are tied together in pairs of pins. If one in a
 * pair is changed, the other is also changed to match:
 *   - Pins 5 and 6 are paired on timer0
 *   - Pins 9 and 10 are paired on timer1
 *   - Pins 3 and 11 are paired on timer2
 * 
 * Note that this function will have side effects on anything else
 * that uses timers:
 *   - Changes on pins 3, 5, 6, or 11 may cause the delay() and
 *     millis() functions to stop working. Other timing-related
 *     functions may also be affected.
 *   - Changes on pins 9 or 10 will cause the Servo library to function
 *     incorrectly.
 * 
 * Thanks to macegr of the Arduino forums for his documentation of the
 * PWM frequency divisors. His post can be viewed at:
 *   http://forum.arduino.cc/index.php?topic=16612#msg121031
 */
void Motor::setPwmFrequency(int pin, int divisor) {
  byte mode;
  if(pin == 5 || pin == 6 || pin == 9 || pin == 10) {
    switch(divisor) {
      case 1: mode = 0x01; break;
      case 8: mode = 0x02; break;
      case 64: mode = 0x03; break;
      case 256: mode = 0x04; break;
      case 1024: mode = 0x05; break;
      default: return;
    }
    if(pin == 5 || pin == 6) {
      TCCR0B = TCCR0B & 0b11111000 | mode;
    } else {
      TCCR1B = TCCR1B & 0b11111000 | mode;
    }
  } else if(pin == 3 || pin == 11) {
    switch(divisor) {
      case 1: mode = 0x01; break;
      case 8: mode = 0x02; break;
      case 32: mode = 0x03; break;
      case 64: mode = 0x04; break;
      case 128: mode = 0x05; break;
      case 256: mode = 0x06; break;
      case 1024: mode = 0x07; break;
      default: return;
    }
    TCCR2B = TCCR2B & 0b11111000 | mode;
  }
}
