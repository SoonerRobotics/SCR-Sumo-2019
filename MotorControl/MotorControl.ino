/* Controls two motors using left and right sticks on Wireless XBox 360 Controller
 *  
 *  Each motor is controlled with 3 signals:
 *  
 *  1 "analog" signal to set the speed of the motor: SPEED
 *  The motor controller wants a PWM signal
 *  On the Arduino, this means we have to use a pin that has a tilde (~) by its number
 *  Then we can use analogWrite to send a value between 0 (coasting, motor off) 
 *  and 255 (motor on, full speed in chosen direction or braking)
 *  
 *  2 digital signals to set direction: FWD,REV
 *  These signals can be output from almost any pin using digitalWrite
 *  Directional signals can be summarized with the following truth table:
 *  ____________________
 * |FWD,REV  |MOTOR DIR.|
 * |---------|----------|
 * |LOW,LOW  |BRAKE*    |
 * |LOW,HIGH |REVERSE   |
 * |HIGH,LOW |FORWARD   |
 * |HIGH,HIGH|BRAKE*    |
 * |_________|__________|
 * *SPEED must be nonzero
 */

#include <XBOXRECV.h>

// Satisfy the IDE, which needs to see the include statment in the ino too.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>

USB Usb;
XBOXRECV Xbox(&Usb);
const int CNTRL_NUM = 0; // Number of controller, 0-3 (1-4)
const int MAX_STICK = 32767; // Maximum input value received from analog sticks (should not change)
const int STICK_TOLERANCE = 7500; // Input from the analog sticks below this value will be ignored

const int LEFT_SPEED = 5; // Pin (PWM) that controls speed of left motor
const int LEFT_FWD = 2; // When output HIGH, left motor spins forward
const int LEFT_REV = 4; // When output HIGH, left motor spins backward
const int RIGHT_SPEED = 6; // Pin (PWM) that controls speed of right motor
const int RIGHT_FWD = 7; // When output HIGH, right motor spins forward
const int RIGHT_REV = 8; // When output HIGH, right motor spins backward

const double MAX_SPEED = 50.0; // Maximum speed of motors, from 0.0-255.0
const double TURBO_SPEED = 200.0; // Max speed when turbo button is pressed

int leftY;
int rightY;
int leftPower;
int rightPower;

void setup() {
  pinMode(LEFT_SPEED, OUTPUT);
  pinMode(LEFT_FWD, OUTPUT);
  pinMode(LEFT_REV, OUTPUT);
  pinMode(RIGHT_SPEED, OUTPUT);
  pinMode(RIGHT_FWD, OUTPUT);
  pinMode(RIGHT_REV, OUTPUT);
  Serial.begin(115200);
#if !defined(__MIPSEL__)
  while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
#endif
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1); //halt
  }
  Serial.print(F("\r\nXbox Wireless Receiver Library Started"));
}
void loop() {
  Usb.Task();
  if (Xbox.XboxReceiverConnected) {
    if (Xbox.Xbox360Connected[CNTRL_NUM]) {
      // Get analog stick y-values
      leftY = Xbox.getAnalogHat(LeftHatY, CNTRL_NUM);
      rightY = Xbox.getAnalogHat(RightHatY, CNTRL_NUM);

      if (Xbox.getButtonPress(R1, CNTRL_NUM)) {
        Serial.print(millis());
        Serial.print('\t');
        Serial.println("Turbo pressed");
        leftPower = abs(leftY * TURBO_SPEED / MAX_STICK);
        rightPower = abs(rightY * TURBO_SPEED / MAX_STICK);
      }
      else {
        Serial.print(millis());
        Serial.print('\t');
        Serial.println("Turbo not pressed");
        leftPower = abs(leftY * MAX_SPEED / MAX_STICK);
        rightPower = abs(rightY * MAX_SPEED / MAX_STICK);                
      }
      // Linearly scale values from 0 to MAX_SPEED based on y-input from stick

      // Left stick is pushed forward
      if (leftY > STICK_TOLERANCE) {
        digitalWrite(LEFT_FWD, HIGH);
        digitalWrite(LEFT_REV, LOW);
        analogWrite(LEFT_SPEED, leftPower);
      }
      // Left stick is pushed backward
      else if (leftY < -1 * STICK_TOLERANCE) {
        digitalWrite(LEFT_FWD, LOW);
        digitalWrite(LEFT_REV, HIGH);
        analogWrite(LEFT_SPEED, leftPower);
      }
      // Left stick is not pushed or pushed less than tolerance
      else {
        digitalWrite(LEFT_FWD, LOW);
        digitalWrite(LEFT_REV, LOW);
        analogWrite(LEFT_SPEED, 255);
      }

      // Right stick is pushed forward
      if (rightY > STICK_TOLERANCE) {
        digitalWrite(RIGHT_FWD, HIGH);
        digitalWrite(RIGHT_REV, LOW);
        analogWrite(RIGHT_SPEED, rightPower);
      }
      // Right stick is pushed backward
      else if (rightY < -1 * STICK_TOLERANCE) {
        digitalWrite(RIGHT_FWD, LOW);
        digitalWrite(RIGHT_REV, HIGH);
        analogWrite(RIGHT_SPEED, rightPower);
      }
      // Right stick is not pushed or pushed less than tolerance
      else {
        digitalWrite(RIGHT_FWD, LOW);
        digitalWrite(RIGHT_REV, LOW);
        analogWrite(RIGHT_SPEED, 255);
      }
    }
    // If controller is disconnected
    else {
      // Cut power to motors
      digitalWrite(LEFT_FWD, LOW);
      digitalWrite(LEFT_REV, LOW);
      analogWrite(LEFT_SPEED, 0);
      digitalWrite(RIGHT_FWD, LOW);
      digitalWrite(RIGHT_REV, LOW);
      analogWrite(RIGHT_SPEED, 0);
    }
  }
  // If receiver is disconnected
  else {
    // Cut power to motors
    digitalWrite(LEFT_FWD, LOW);
    digitalWrite(LEFT_REV, LOW);
    analogWrite(LEFT_SPEED, 0);
    digitalWrite(RIGHT_FWD, LOW);
    digitalWrite(RIGHT_REV, LOW);
    analogWrite(RIGHT_SPEED, 0);
    }
}
