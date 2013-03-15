// Class to use Parallax 3-Axis Compass (29133-RT)
// Author: Erik Nedwidek
// Date: 2013/03/14
// License: BSD

#ifndef Compass_h
#define Compass_h

#include "Arduino.h"

// Compass I2C address
#define COMPASS_ADDR (0x1E )

// Compass registers
#define COMPASS_CONFIG_A (0x00)
#define COMPASS_CONFIG_B (0x01)
#define COMPASS_MODE     (0x02)
#define COMPASS_OUT_X_H  (0x03)
#define COMPASS_OUT_X_L  (0x04)
#define COMPASS_OUT_Z_H  (0x05)
#define COMPASS_OUT_Z_L  (0x06)
#define COMPASS_OUT_Y_H  (0x07)
#define COMPASS_OUT_Y_L  (0x08)
#define COMPASS_STATUS   (0x09)
#define COMPASS_IDENT_A  (0x0A)
#define COMPASS_IDENT_B  (0x0B)
#define COMPASS_IDENT_C  (0x0C)

// Modes: Continuous; Single; Idle
#define COMPASS_MODE_C   (0x00)
#define COMPASS_MODE_S   (0x01)
#define COMPASS_MODE_I   (0x03)

// Gain values
#define GAIN__88_VAL     (0x00)
#define GAIN__88_RES     (0.73)
#define GAIN_1_3_VAL     (0x20)
#define GAIN_1_3_RES     (0.92)
#define GAIN_1_9_VAL     (0x40)
#define GAIN_1_9_RES     (1.22)
#define GAIN_2_5_VAL     (0x60)
#define GAIN_2_5_RES     (1.52)
#define GAIN_4_0_VAL     (0x80)
#define GAIN_4_0_RES     (2.27)
#define GAIN_4_7_VAL     (0XA0)
#define GAIN_4_7_RES     (2.56)
#define GAIN_5_6_VAL     (0xC0)
#define GAIN_5_6_RES     (3.03)
#define GAIN_8_1_VAL     (0xE0)
#define GAIN_8_1_RES     (4.35)

class Compass {
public:
    Compass();
    void begin();
    void setModeContinuous();
    void setModeSingle();
    void setModeSleep();
    void setGain_88();
    void setGain1_3();
    void setGain1_9();
    void setGain2_5();
    void setGain4_0();
    void setGain4_7();
    void setGain5_6();
    void setGain8_1();
    void read();
    float heading();
    void i2cWrite(byte reg, byte value);
    uint8_t* i2cRead(byte reg, int length);
    int rawX, rawY, rawZ;
    float scaledX, scaledY, scaledZ;
private:
    float res;
    uint8_t val;
    void setGain();
};

#endif
