// Class to use Parallax 3-Axis Compass (29133-RT)
// Author: Erik Nedwidek
// Date: 2013/03/14
// License: BSD


#include "Arduino.h"
#include "Compass.h"
#include <Wire.h>

/**
 * Constructor. Sensor field range is +/- 1.3 Ga by default. Use 
 * any of the setGainXXX methods to change this. 
 *  
 * @author nedwidek (2013/03/14)
 * 
 */
Compass::Compass() {
    this->res = GAIN_1_3_RES;
    this->val = GAIN_1_3_VAL;
}

/**
 * Start the wire library. This does not need to be called if 
 * you have already started the wire library or used another 
 * class that has already done it. 
 *  
 * @author nedwidek (2013/03/14)
 * 
 */
void Compass::begin() {
    Wire.begin();
}

/**
 * Start the compass in continuous measurement mode.
 *  
 * @author nedwidek (2013/03/14)
 * 
 */
void Compass::setModeContinuous() {
    this->i2cWrite(COMPASS_MODE, COMPASS_MODE_C);
}

/**
 * Start the compass in single measurement mode. Compass will 
 * idle/sleep after the measurement. 
 *  
 * @author nedwidek (2013/03/14)
 * 
 */
void Compass::setModeSingle() {
    this->i2cWrite(COMPASS_MODE, COMPASS_MODE_S);
}

/**
 * Put the compass in sleep mode. This can be used to to save 
 * power when the compass is not needed. 
 *  
 * @author nedwidek (2013/03/14)
 * 
 */
void Compass::setModeSleep() {
    this->i2cWrite(COMPASS_MODE, COMPASS_MODE_I);
}

/**
 * Set the sensitivity to a gain of 0.88 Ga
 *  
 * @author nedwidek (2013/03/14)
 * 
 */
void Compass::setGain_88() {
    this->val = GAIN__88_VAL;
    this->res = GAIN__88_RES;
    this->setGain();
}

/**
 * Set the sensitivity to a gain of 1.3 Ga
 *  
 * @author nedwidek (2013/03/14)
 * 
 */
void Compass::setGain1_3() {
    this->val = GAIN_1_3_VAL;
    this->res = GAIN_1_3_RES;
    this->setGain();
}

/**
 * Set the sensitivity to a gain of 1.9 Ga
 *  
 * @author nedwidek (2013/03/14)
 * 
 */
void Compass::setGain1_9() {
    this->val = GAIN_1_9_VAL;
    this->res = GAIN_1_9_RES;
    this->setGain();
}

/**
 * Set the sensitivity to a gain of 2.5 Ga
 *  
 * @author nedwidek (2013/03/14)
 * 
 */
void Compass::setGain2_5() {
    this->val = GAIN_2_5_VAL;
    this->res = GAIN_2_5_RES;
    this->setGain();
}

/**
 * Set the sensitivity to a gain of 4.0 Ga
 *  
 * @author nedwidek (2013/03/14)
 * 
 */
void Compass::setGain4_0() {
    this->val = GAIN_4_0_VAL;
    this->res = GAIN_4_0_RES;
    this->setGain();
}

/**
 * Set the sensitivity to a gain of 4.7 Ga
 *  
 * @author nedwidek (2013/03/14)
 * 
 */
void Compass::setGain4_7(){
    this->val = GAIN_4_7_VAL;
    this->res = GAIN_4_7_RES;
    this->setGain();
}

/**
 * Set the sensitivity to a gain of 5.6 Ga
 *  
 * @author nedwidek (2013/03/14)
 * 
 */
void Compass::setGain5_6() {
    this->val = GAIN_5_6_VAL;
    this->res = GAIN_5_6_RES;
    this->setGain();
}

/**
 * Set the sensitivity to a gain of 8.1 Ga
 *  
 * @author nedwidek (2013/03/14)
 * 
 */
void Compass::setGain8_1() {
    this->val = GAIN_8_1_VAL;
    this->res = GAIN_8_1_RES;
    this->setGain();
}

/**
 * Read the output registers and compute both raw and scaled X, 
 * Y and Z information. Values will be placed into the 
 * appropriate member variables. 
 *  
 * @author nedwidek (2013/03/14)
 * 
 */
void Compass::read() {
    uint8_t* buffer = this->i2cRead(COMPASS_OUT_X_H, 6);
    this->rawX = buffer[0] << 8 | buffer[1];
    this->rawZ = buffer[2] << 8 | buffer[3];
    this->rawY = buffer[4] << 8 | buffer[5];
    this->scaledX = this->rawX * this->res;
    this->scaledY = this->rawY * this->res;
    this->scaledZ = this->rawZ * this->res;
}

/**
 * Calls read() and then calculates and returns the heading. 
 * This is not tilt compensated (requires external 
 * accelerometer). 
 *  
 * @author nedwidek (2013/03/14)
 *  
 * @return The heading 0° - 360°. 
 */
float Compass::heading() {
    this->read();

    float heading = atan2(this->rawY, this->rawX);
    if (heading < 0) {
        heading += 2*PI;
    }

    heading *= 180/M_PI;

    return heading;
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
void Compass::i2cWrite(byte reg, byte value) {
    Wire.beginTransmission(COMPASS_ADDR);
    Wire.write(reg);
    Wire.write(value);
    Wire.endTransmission();
}

/**
 * Read values from a register or registers. The HMC5883L will 
 * autoincrement the registers. 
 *  
 * @author nedwidek (2013/03/14) 
 * @param reg The register to read from (or the register to 
 *            start at.
 * @param length The number of bytes to read. 
 * @return A buffer containing the requested values. 
 * 
 */
uint8_t* Compass::i2cRead(byte reg, int length) {
    uint8_t buffer[length];

    Wire.beginTransmission(COMPASS_ADDR);
    Wire.write(reg);
    Wire.endTransmission();
    Wire.requestFrom((uint8_t)COMPASS_ADDR, (uint8_t)length);

    while (Wire.available() < length);

    for (uint8_t i=0; i < length; i++) {
        buffer[i] = Wire.read();
    }
    Wire.endTransmission();

    return buffer;
}

void Compass::setGain() {
    i2cWrite(COMPASS_CONFIG_B, this->val);
}
