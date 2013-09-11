// Class to use RadioShack's 1m LED Strips Model 2760249: http://www.radioshack.com/product/index.jsp?productId=16306856
// Author: Erik Nedwidek
// Date: 2013/09/10
// License: BSD

#include "Arduino.h"
#include "RS2760249.h"

#if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
#define PORT PORTF
#define MAX_PIN 7
#define STRIP_PINOUT DDRF
#else
#define PORT PORTC
#define MAX_PIN 5
#define STRIP_PINOUT DDRC
#endif

#define NOP "nop\n\t"

RS2760249::RS2760249(int pin, int segments) {
    this->init(pin, segments);
}

RS2760249::RS2760249(int pin) {
    this->init(pin, 10);
}

void RS2760249::reset() {
    //(PORT &= (0xFF ^ this->pin));
    delayMicroseconds(24);
}

void RS2760249::clear() {
    this->reset();
    for (int i=0; i<this->segments; i++) {
        this->send(0x000000);
    }
}

void RS2760249::send(uint32_t data) {
    int i;
    unsigned long j=0x000001;

    for (i=0; i<24; i++) {
        if (data & j) {
            (PORT |= this->pin);
            __asm__(NOP NOP NOP NOP NOP NOP NOP NOP NOP NOP NOP NOP NOP NOP NOP NOP NOP NOP NOP NOP NOP NOP NOP NOP NOP NOP NOP NOP);
            (PORT &= (0xFF ^ this->pin));
        } else {
            (PORT |= this->pin);
            __asm__(NOP NOP NOP NOP NOP NOP NOP NOP NOP);
            (PORT &= (0xFF ^ this->pin));
            __asm__(NOP NOP NOP);
        }
        j<<=1;
    }
}

void RS2760249::sendPattern(unsigned long data[], int length) {
    noInterrupts();
    for (int i=0; i<length; i++) {
        this->send(data[i]);
    }
    interrupts();

}

void RS2760249::init(int pin, int segments) {
    // Inelegant. If they pass an invalid pin, we just won't work.
    if (pin > MAX_PIN) {
        this->pin = 0x00;
    } else {
        uint8_t pinmodes = 0x01;
        pinmodes <<= pin;
        this->pin = pinmodes;
    }

    this->segments = segments;

    // Set the pin to output.
    (STRIP_PINOUT |= this->pin);
    this->reset();
}
