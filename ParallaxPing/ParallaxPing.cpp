// Class to use Parallax Ping))) Ultrasonic Sensor (#28015-RT)
// Author: Erik Nedwidek
// Date: 2012/07/01
// License: BSD

#include "Arduino.h"
#include "ParallaxPing.h"

/**
 * Constructor. Sets delay to enough microseconds to comfortably 
 * cover 20' or 6m. (Round trip of full range of 10' or 3m) 
 * 
 * @author nedwidek (2012/07/01)
 * 
 * @param pin Signal line
 */
ParallaxPing::ParallaxPing(int pin) {
    this->_pin = pin;
    this->_delay = 200000;
}

/**
 * Constructor. 
 * 
 * @author nedwidek (2012/07/01)
 * 
 * @param pin Signal line
 * @param delay Maximum delay to wait for the sensor pulse.
 */
ParallaxPing::ParallaxPing(int pin, long delay) {
    this->_pin = pin;
    this->_delay = delay;
}

/**
 * Returns range in microseconds
 * 
 * @author nedwidek (2012/07/01)
 * 
 * @return The raw range in microseconds. Useful when 
 *         adjustments need to be made.
 */
long ParallaxPing::rangeRaw() {
    return this->ping() / 2;
}

/**
 * Returns range in meters
 * 
 * @author nedwidek (2012/07/01)
 * 
 * @return The range in meters 
 */
float ParallaxPing::rangeMeters() {
    return this->rangeRaw() / 2900.0;
}

/**
 * Returns range in centimeters
 * 
 * @author nedwidek (2012/07/01)
 * 
 * @return The range in centimeters.
 */
float ParallaxPing::rangeCentimeters() {
    return this->rangeRaw() / 29.0;
}

/**
 * Returns range in inches
 * 
 * @author nedwidek (2012/07/01)
 * 
 * @return The range in inches. 
 */
float ParallaxPing::rangeInches() {
    return this->rangeRaw() / 74.0;
}

/**
 * Returns range in feet
 * 
 * @author nedwidek (2012/07/01)
 * 
 * @return The range in feet. 
 */
float ParallaxPing::rangeFeet() {
    return this->rangeRaw() / 885.0;
}

/**
 * Set the pin the sensor is connected to. Useful for 
 * controlling multiple sensors with one instance of this class.
 * 
 * @author nedwidek (2012/07/01)
 * 
 * @return The range in inches. 
 */
void ParallaxPing::setPin(int pin) {
    this->_pin = pin;
}

void ParallaxPing::setDelay(long delay) {
    this->_delay = delay;
}

/**
 * Make a measurement with the sensor.
 * 
 * @author nedwidek (2012/07/01)
 * 
 * @return The round trip time for the ultrasonic chirp in ms. 
 */
long ParallaxPing::ping() {
    // Tell the sensor we want a reading
    pinMode(_pin, OUTPUT);
    digitalWrite(_pin, LOW);
    delayMicroseconds(2);
    digitalWrite(_pin, HIGH);
    delayMicroseconds(5);
    digitalWrite(_pin, LOW);

    // Sensor sends back a pulse whose width is the roundtrip time for the ping. We return the pulse width, which is in ms.
    pinMode(_pin, INPUT);
    return pulseIn(_pin, HIGH, _delay);
}
