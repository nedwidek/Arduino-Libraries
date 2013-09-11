// Class to use RadioShack's 1m LED Strips Model 2760249: http://www.radioshack.com/product/index.jsp?productId=16306856
// Author: Erik Nedwidek
// Date: 2013/09/10
// License: BSD
 
#ifndef RS2760249_h
#define RS2760249_h

#include "Arduino.h"

class RS2760249 {
public:
    RS2760249(int pin);
    RS2760249(int pin, int segments);
    void reset();
    void send(uint32_t data);
    void sendPattern(unsigned long data[], int length);
    void clear();
private:
    uint8_t pin;
    int segments;
    void init(int pin, int segments);
};

#endif

