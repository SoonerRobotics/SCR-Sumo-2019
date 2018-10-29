#include <XBOXRECV.h>

// Satisfy the IDE, which needs to see the include statment in the ino too.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>

USB Usb;
XBOXRECV Xbox(&Usb);
const int CNTRL_NUM = 0; // Number of controller, 0-3 (1-4)

const int LEFT_SPEED = 5; // Pin (PWM) that controls speed of left motor
const int LEFT_FWD = 2; // When output HIGH, motor spins forward.
const int LEFT_REV = 4; // When output HIGH, motor spins backward.
const int RIGHT_SPEED = 6; // Pin (PWM) that controls speed of right motor
const int RIGHT_FWD = 7; // When output HIGH, motor spins forward.
const int RIGHT_REV = 8; // When output HIGH, motor spins backward.

const double MAX_SPEED = 200.0; // Maximum speed of motor, from 0-255

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
      leftY = Xbox.getAnalogHat(LeftHatY, CNTRL_NUM);
      rightY = Xbox.getAnalogHat(RightHatY, CNTRL_NUM);

      leftPower = abs(leftY * MAX_SPEED / MAX_STICK); // Scale value from 0 to MAX_SPEED based on left stick y input
      rightPower = abs(rightY * MAX_SPEED / MAX_STICK); // Scale value from 0 to MAX_SPEED based on right stick y input

      if (leftY > HAT_TOLERANCE) {
        digitalWrite(LEFT_FWD, HIGH);
        digitalWrite(LEFT_REV, LOW);
        analogWrite(LEFT_SPEED, leftPower);
      }
      else if (leftY < -1 * HAT_TOLERANCE) {
        digitalWrite(LEFT_FWD, LOW)
        digitalWrite(LEFT_REV, HIGH);
        analogWrite(LEFT_SPEED, leftPower);
      }
      else {
        digitalWrite(LEFT_FWD, LOW);
        digitalWrite(LEFT_REV, LOW);
        analogWrite(LEFT_SPEED, 0);
      }
      
      if (rightY > HAT_TOLERANCE) {
        digitalWrite(RIGHT_FWD, HIGH);
        digitalWrite(RIGHT_REV, LOW);
        analogWrite(RIGHT_SPEED, leftPower);
      }
      else if (rightY < -1 * HAT_TOLERANCE) {
        digitalWrite(RIGHT_FWD, LOW)
        digitalWrite(RIGHT_REV, HIGH);
        analogWrite(RIGHT_SPEED, leftPower);
      }
      else {
        digitalWrite(RIGHT_FWD, LOW);
        digitalWrite(RIGHT_REV, LOW);
        analogWrite(RIGHT_SPEED, 0);
      }
    }
  }
}
