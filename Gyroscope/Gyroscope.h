// Class to use Parallax 3-Axis Gyroscope (27911-RT)
// Author: Erik Nedwidek
// Date: 2013/03/14
// License: BSD

#ifndef Gyroscope_h
#define Gyroscope_h

#include "Arduino.h"

// Gyroscope addresses (primary [SDO to Gnd]/secondary [SDO to +5V])
#define GYRO_ADDR0 (0x68)
#define GYRO_ADDR1 (0x69)

// Gyroscope registers (See datasheet for documentation).
#define GYRO_WHO_AM_I       (0x0F)
#define GYRO_CTRL_REG1      (0x20)
#define GYRO_CTRL_REG2      (0x21)
#define GYRO_CTRL_REG3      (0x22)
#define GYRO_CTRL_REG4      (0x23)
#define GYRO_CTRL_REG5      (0x24)
#define GYRO_REFERENCE      (0x25)
#define GYRO_OUT_TEMP       (0x26)
#define GYRO_STATUS_REG     (0x27)
#define GYRO_OUT_X_L        (0x28)
#define GYRO_OUT_X_H        (0x29)
#define GYRO_OUT_Y_L        (0x2A)
#define GYRO_OUT_Y_H        (0x2B)
#define GYRO_OUT_Z_L        (0x2C)
#define GYRO_OUT_Z_H        (0x2D)
#define GYRO_FIFO_CTRL_REG  (0x2E)
#define GYRO_FIFO_SRC_REG   (0x2F)
#define GYRO_INT1_CFG       (0x30)
#define GYRO_INT1_SRC       (0x31)
#define GYRO_INT1_TSH_XL    (0x32)
#define GYRO_INT1_TSH_XH    (0x33)
#define GYRO_INT1_TSH_YL    (0x34)
#define GYRO_INT1_TSH_YH    (0x35)
#define GYRO_INT1_TSH_ZL    (0x36)
#define GYRO_INT1_TSH_ZH    (0x37)
#define GYRO_INT1_DURATION  (0x38)


// See .cpp source for method documentation.
class Gyroscope {
public:
    Gyroscope();
    Gyroscope(bool isSecondary);
    void begin();
    void setModeDefault();
    void setModeSleep();
    void setMode(bool isPowered, bool isXOn, bool isYOn, bool isZOn);
    void read(); 
    void i2cWrite(byte reg, byte value);
    uint8_t* i2cRead(byte reg, int length);
    void setIsSecondary(bool isSecondary);
    int x;
    int y;
    int z;
private:
    uint8_t _GYRO_ADDR;
};

#endif
