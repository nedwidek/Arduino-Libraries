// Class to use Parallax 2x16 LCD Display (#27976-RT, #27977-RT)
// Author: Erik Nedwidek
// Date: 2012/07/01
// License: BSD

#ifndef ParallaxLCD_h
#define ParallaxLCD_h

#include "Arduino.h"
#include <SoftwareSerial.h>

class ParallaxLCD : public SoftwareSerial {
public:
    ParallaxLCD(int pin, int baud);
    void clear();
    void backlight(bool on);
    void displayMode(bool on, bool cursor, bool blink);
    void moveCursor(int row, int col);
    void defineCustom(int custom, byte data[]);
    void displayCustom(int custom);
    void set64thNote();
    void set32ndNote();
    void set16thNote();
    void set8thNote();
    void setQuarterNote();
    void setHalfNote();
    void setFullNote();
    void setScale3();
    void setScale4();
    void setScale5();
    void setScale6();
    void setScale7();
    void playNote(int);

    static const int A          = 220;
    static const int A_SHARP    = 221;
    static const int B          = 222;
    static const int C          = 223;
    static const int C_SHARP    = 224;
    static const int D          = 225;
    static const int D_SHARP    = 226;
    static const int E          = 227;
    static const int F          = 228;
    static const int F_SHARP    = 229;
    static const int G          = 230;
    static const int G_SHARP    = 231;
    static const int PAUSE      = 232;

private:
    int _pin;
    void setScale(int);
    void setNoteLength(int);
};

#endif
