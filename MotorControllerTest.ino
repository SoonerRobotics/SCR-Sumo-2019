// Test for XBOX controller, which outputs directional input
const int MaxDir = 32768;
const int hatTolerance = 7500;
const int minSpeed = 100;
int leftWheel;
int rightWheel;

#include <XBOXRECV.h>

// Satisfy the IDE, which needs to see the include statment in the ino too.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>

USB Usb;
XBOXRECV Xbox(&Usb);

void setup() {
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
    //Set Speed by L2 and R2
    if (Xbox.getButtonPressed(L2, 0) < minSpeed)
      leftWheel = minSpeed;
    else
      leftWheel = Xbox.getButtonPress(L2, 0);
    if (Xbox.getButtonPressed(R2, 0) < minSpeed)
      rightWheel = minSpeed;
    else
      rightWheel = Xbox.getButtonPress(R2, 0);
    
    //Multiply based on Directions of sticks
    //Left side first
    if (Xbox.getAnalogHat(LeftHatY, 0) < hatTolerance && Xbox.getAnalogHat(LeftHatY, 0) > -hatTolerance)
    {
      leftWheel = leftWheel * 0;
    }
    else if (Xbox.getAnalogHat(LeftHatY, 0) > hatTolerance )
    {
      leftWheel = leftWheel * 1;
    }
    else if (Xbox.getAnalogHat(LeftHatY, 0) < -hatTolerance)
    {
      leftWheel = leftWheel * -1;
    }
    
      //Right side second
    if (Xbox.getAnalogHat(RightHatY, 0) < hatTolerance && Xbox.getAnalogHat(RightHatY, 0) > -hatTolerance)
    {
      rightWheel = rightWheel * 0;
    }
    else if (Xbox.getAnalogHat(RightHatY, 0) > hatTolerance )
    {
      rightWheel = rightWheel * 1;
    }
    else if (Xbox.getAnalogHat(RightHatY, 0) < -hatTolerance)
    {
      rightWheel = rightWheel * -1;
    }
    
    //Final Output
    Serial.print("Left Wheel: ");
    Serial.print(leftWheel);
    Serial.print("\tRight Wheel: ");
    Serial.print(rightWheel);
    Serial.print("\n");
  }
}
