// Class to use TMP36 temperature sensor (http://www.adafruit.com/products/165)
// Author: Erik Nedwidek
// Date: 2013/03/14
// License: BSD

#ifndef TMP36_h
#define TMP36_h

#include "Arduino.h"

class TMP36 {
public:
    TMP36(int pin);
    TMP36(int pin, bool is5V);
    long mV();
    float temperatureC();
    float temperatureF();
    void setPin(int pin);
    void setIs5V(bool is5V);
private:
    int _pin;
    int _Vref;
    static const float _V5  = 5000.0;
    static const float _V33 = 3300.0;
};

#endif
