#include "Motor.h"
#include "LineSensor.h"

const int LEFT_DIR = 4;
const int LEFT_SPD = 6;
const int LEFT_EN = 8;
const int RIGHT_DIR = 2;
const int RIGHT_SPD = 5;
const int RIGHT_EN = 7;

const int LINE_SENSOR = A0;

Motor motorLeft;
Motor motorRight;
LineSensor line1;

void setup() {
  motorLeft = Motor(LEFT_DIR, LEFT_SPD, LEFT_EN, true);
  motorRight = Motor(RIGHT_DIR, RIGHT_SPD, RIGHT_EN, true);
  line1 = LineSensor(LINE_SENSOR, 500);
  Serial.begin(9600);
}

void loop() {
  if (line1.seeWhite()) {
    motorLeft.setPower(0.0);
    motorRight.setPower(0.0);
  }
  else {
    motorLeft.setPower(15.0);
    motorRight.setPower(15.0);
  }
  Serial.println(line1.getRawReflectance());
}
