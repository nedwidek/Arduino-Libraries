// Class to use Parallax Ping))) Ultrasonic Sensor (#28015-RT)
// Author: Erik Nedwidek
// Date: 2012/07/01
// License: BSD

#ifndef ParallaxPing_h
#define ParallaxPing_h

#include "Arduino.h"

class ParallaxPing {
public:
    ParallaxPing(int pin);
    ParallaxPing(int pin, long delay);
    long rangeRaw();
    float rangeMeters();
    float rangeCentimeters();
    float rangeInches();
    float rangeFeet();
    void setPin(int pin);
    void setDelay(long delay);
private:
    int _pin;
    long _delay;
    long ping();
};

#endif
