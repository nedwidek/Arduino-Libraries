// Class to use Parallax 3-Axis Gyroscope (27911-RT)
// Author: Erik Nedwidek
// Date: 2013/03/14
// License: BSD

#include "Arduino.h"
#include "Gyroscope.h"
#include <Wire.h>

/**
 * Constructor. Assumes that this is the primary Gyroscope and 
 * that SDO is connected to ground. 
 *  
 * @author nedwidek (2013/03/14)
 * 
 */
Gyroscope::Gyroscope() {
    this->_GYRO_ADDR = GYRO_ADDR0;
}

/**
 * Constructor. Allows you to choose primary or secondary 
 * gyroscope address. 
 *  
 * @author nedwidek (2013/03/14)
 *  
 * @param isSecondary true if SDO is connected to Vcc 
 *                    (secondary) or false if SDO is connected
 *                    to ground (primary).
 *  
 */
Gyroscope::Gyroscope(bool isSecondary) {
    this->setIsSecondary(isSecondary);
}

/**
 * Start the wire library. This does not need to be called if 
 * you have already started the wire library or used another 
 * class that has already done it. 
 *  
 * @author nedwidek (2013/03/14)
 * 
 */
void Gyroscope::begin() {
    Wire.begin();
}

/**
 * Starts the gyroscope in default mode with rotation 
 * information on all axes being measured. 
 *  
 * @author nedwidek (2013/03/14)
 * 
 */
void Gyroscope::setModeDefault() {
    this->setMode(true, true, true, true);
}

/**
 * Sleeps the gyroscope. This can be used when you don't need 
 * measurements and would like to save power. 
 *  
 * @author nedwidek (2013/03/14)
 * 
 */
void Gyroscope::setModeSleep() {
    this->setMode(false, false, false, false);
}

/**
 *  
 * Allows full access to the gyroscopes modes. Most useful when 
 * you want to turn the gyroscope on, but only for specific 
 * axes. 
 *  
 * @author nedwidek (2013/03/14)
 *  
 * @param isPowered Turns the power on when true. 
 * @param isXOn Measure rotation information on the X axis.
 * @param isYOn Measure rotation information on the Y axis.
 * @param isZOn Measure rotation information on the Z axis.
 *  
 */
void Gyroscope::setMode(bool isPowered, bool isXOn, bool isYOn, bool isZOn) {
    byte value = 0x00;

    if (isPowered) {
        value |= 0x08;
    }
    if (isXOn) {
        value |= 0x04;
    }
    if (isYOn) {
        value |= 0x02;
    }
    if (isZOn) {
        value |= 0x01;
    }

    this->i2cWrite(GYRO_CTRL_REG1, value);
}

/**
 * Measure the rotation information and place the output in the 
 * x, y, and z members of this class. 
 *  
 * @author nedwidek (2013/03/14)
 * 
 */
void Gyroscope::read() {
    byte* buffer = this->i2cRead(GYRO_OUT_X_L | 0x80, 6);
    
    this->x = buffer[1] << 8 | buffer[0];
    this->y = buffer[3] << 8 | buffer[2];
    this->z = buffer[5] << 8 | buffer[4];
}

/**
 * Write a value to a register on the device being managed. 
 * Refer to the datasheet for valid values and registers. All 
 * registers are mapped to defined constants in the .h file. 
 *  
 * @author nedwidek (2013/03/14) 
 * @param reg The register address. 
 * @param value The value to write to the register. 
 * 
 */
void Gyroscope::i2cWrite(byte reg, byte value) {
    Wire.beginTransmission(this->_GYRO_ADDR);
    Wire.write(reg);
    Wire.write(value);
    Wire.endTransmission();
}

/**
 * Read values from a register or registers. The gyroscope can 
 * be instructed to automatically advance registers by setting 
 * the MSb. Example: 
 *    i2cRead(GYRO_OUT_X_L | 0x80, 6);
 * The gyro will start reporting the values of the registers 
 * starting with the X output low byte. The returned buffer will 
 * only contain the values of X low, X high, Y low, Y high, Z 
 * low, and Z high. 
 *  
 * @author nedwidek (2013/03/14) 
 * @param reg The register to read from (or the register to 
 *            start at.
 * @param length The number of bytes to read. 
 * @return A buffer containing the requested values. 
 * 
 */
uint8_t* Gyroscope::i2cRead(byte reg, int length) {
    uint8_t buffer[length];

    Wire.beginTransmission(this->_GYRO_ADDR);
    Wire.write(reg);
    Wire.endTransmission();
    Wire.requestFrom((uint8_t)this->_GYRO_ADDR, (uint8_t)length);

    while (Wire.available() < length);

    Serial.println("---------------------");
    for (uint8_t i=0; i < length; i++) {
        buffer[i] = Wire.read();
    }
    Wire.endTransmission();

    return buffer;
}

/**
 * Setter method to set the device address we wish to talk to. 
 * If you are using two gyroscopes you can use this method to 
 * allow one instance of this class to switch between the two 
 * devices. 
 *  
 * @author nedwidek (2013/03/14)
 *  
 * @param isSecondary true if SDO is connected to Vcc 
 *                    (secondary) or false if SDO is connected
 *                    to ground (primary).
 *  
 */
void Gyroscope::setIsSecondary(bool isSecondary) {
    if (isSecondary) {
        this->_GYRO_ADDR = GYRO_ADDR1;
    } else {
        this->_GYRO_ADDR = GYRO_ADDR0;
    }
}
