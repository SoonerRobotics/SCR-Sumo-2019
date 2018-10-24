// Test for XBOX controller, which outputs directional input

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
  Serial.println(F(Xbox.getAnalogHat(0, 0)));
  if (Xbox.XboxReceiverConnected) {
    for (uint8_t i = 0; i < 4; i++) { // For loop cycles through controllers 1 to 4
        // Turn on LED when A is clicked
        if (Xbox.getButtonClick(A, i)) {
          digitalWrite(led, HIGH);
          Serial.println(F("LED on")); 
        }
        // Turn off LED when B is clicked
        if (Xbox.getButtonClick(B, i)) {
          digitalWrite(led, LOW);
          Serial.println(F("LED off"));
        }
      }
    }
  }
}
