// Test for XBOX controller and analog outputs
// Adjusts brightness of 4 LEDs representing the forward/backward power of 2 motors

#include <XBOXRECV.h>

// Satisfy the IDE, which needs to see the include statment in the ino too.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>

USB Usb;
XBOXRECV Xbox(&Usb);
const int CNTRL_NUM = 0; // Number of controller, 0-3 (1-4)
const int HAT_TOLERANCE = 7500;
const int MAX_STICK = 32767;

const int LEFT_FWD = 9;
const int LEFT_REV = 6;
const int RIGHT_FWD = 5;
const int RIGHT_REV = 3;

int leftPower;
int rightPower;
int leftY; // Raw y-value from left stick
int rightY; // Raw y-value from right stick

void setup() {
  pinMode(LEFT_FWD, OUTPUT);
  pinMode(LEFT_REV, OUTPUT);
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

      leftPower = leftY * 255.0 / MAX_STICK; // Scale value from 0-255 based on left stick y input
      rightPower = rightY * 255.0 / MAX_STICK; // Scale value from 0-255 based on right stick y input

      if (leftY > HAT_TOLERANCE) {
        analogWrite(LEFT_FWD, leftPower);
        analogWrite(LEFT_REV, 0);
      }
      else if (leftY < -1 * HAT_TOLERANCE) {
        analogWrite(LEFT_REV, -1 * leftPower);
        analogWrite(LEFT_FWD, 0);
      }
      else {
        analogWrite(LEFT_FWD, 0);
        analogWrite(LEFT_REV, 0);
      }
      
      if (rightY > HAT_TOLERANCE) {
        analogWrite(RIGHT_FWD, rightPower);
        analogWrite(RIGHT_REV, 0);
      }
      else if (rightY < -1 * HAT_TOLERANCE) {
        analogWrite(RIGHT_REV, -1 * rightPower);
        analogWrite(RIGHT_FWD, 0);
      }
      else {
        analogWrite(RIGHT_FWD, 0);
        analogWrite(RIGHT_REV, 0);
      }
    }
  }
}
