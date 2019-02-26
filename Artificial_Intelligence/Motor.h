#ifndef MOTOR_H
#define MOTOR_H

class Motor {
  private:
    int maxPower;;
    int directionPin;
    int speedPin;
    int enablePin;
    double power;
    bool reversed;
  
  public:
    Motor();
    Motor(int directionPin, int speedPin, int enablePin, bool reversed);
    void setPower(double power);
    void enable(bool enable);
    void setDirection(bool forward);
    void setMaxPower(int power);
    void setPwmFrequency(int pin, int divisor);
};

#endif
