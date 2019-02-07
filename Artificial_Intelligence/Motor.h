class Motor {
  private:
    int MAX_POWER = 95;
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
};
