// Class to use TMP36 temperature sensor (http://www.adafruit.com/products/165)
// Author: Erik Nedwidek
// Date: 2013/03/14
// License: BSD

#include "Arduino.h"
#include "TMP36.h"

/**
 * Constructor. Assumes that sensor Vref is set to 5V.
 *  
 * @author nedwidek (2013/03/14)
 * 
 * @param pin Signal line
 */
TMP36::TMP36(int pin) {
    this->_pin = pin;
    this->_Vref = this->_V5;
}

/**
 * Constructor. 
 * 
 * @author nedwidek (2013/03/14)
 * 
 * @param pin Signal line
 * @param is5V true if the Vref of the sensor is connected to 5V
 *             or false if it is connected to 3.3V.
 */ 
TMP36::TMP36(int pin, bool is5V) {
    this->_pin = pin;
    if (is5V) {
        this->_Vref = this->_V5;
    } else {
        this->_Vref = this->_V33;
    }
}

/**
 * Gets the milivolts read at the analog pin. 
 * 
 * @author nedwidek (2013/03/14)
 * 
 * @return The milivolts read at the pin.
 */
long TMP36::mV() {
    int reading = analogRead(this->_pin);

    return (float) reading * this->_Vref / 1024.0;
}

/**
 * Gets the temperature in °C. 
 * 
 * @author nedwidek (2013/03/14)
 * 
 * @return The temperature in °C.
 */
float TMP36::temperatureC() {
    float Vpin = this->mV();

    return (float) (Vpin - 500) / 10.0;
}

/**
 * Gets the temperature in °F 
 * 
 * @author nedwidek (2013/03/14)
 * 
 * @return The temperature in °F.
 */
float TMP36::temperatureF() {
    float temperatureC = this->temperatureC();

    return (float) temperatureC* 9.0/5.0 + 32;
}

void TMP36::setPin(int pin) {
    this->_pin = pin;
}

void TMP36::setIs5V(bool is5V) {
    if (is5V) {
        this->_Vref = this->_V5;
    } else {
        this->_Vref = this->_V33;
    }
}

