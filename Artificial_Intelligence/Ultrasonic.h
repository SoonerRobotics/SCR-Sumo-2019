class Ultrasonic {
  private:
    int dataPin;

  public:
    Ultrasonic();
    Ultrasonic(int dataPin);
    double getRawDistance();
};
