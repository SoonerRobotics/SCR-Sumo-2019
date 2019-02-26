#ifndef LINESENSOR_H
#define LINESENSOR_H

class LineSensor {
  private:
    int dataPin;
    int reflectanceThreshold;
  
  public:
    LineSensor();
    LineSensor(int dataPin);
    LineSensor(int dataPin, int threshold);
    int getRawReflectance();
    bool seeWhite();
};

#endif
