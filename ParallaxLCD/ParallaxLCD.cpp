// Class to use Parallax LCD 2x16 LCD Display (#27976-RT, #27977-RT, #27978-RT, #27979-RT)
// Author: Erik Nedwidek
// Date: 2012/07/01
// License: BSD

#include "Arduino.h"
#include <SoftwareSerial.h>
#include "ParallaxLCD.h"

/**
 * Constructor. Note that you need to not only include the 
 * Parallax.h file in your sketch, but also SoftwareSerial.h. 
 * This is because the Arduino IDE does not look at the library 
 * code to determine what files to copy to the build directory. 
 * It only looks at the sketch. If you have compile errors about 
 * SoftwareSerial being undefined, check your includes. 
 * 
 * @author nedwidek (2012/07/01)
 * 
 * @param pin Signal line 
 * @param baud Baud rate for display 
 */
ParallaxLCD::ParallaxLCD(int pin, int baud) : SoftwareSerial(pin, pin) {
    _pin = pin;
    pinMode(pin, OUTPUT);
    begin(baud);
}

/**
 * Clear the display. Requires 5ms.
 * 
 * @author nedwidek (2012/07/01)
 * 
 */
void ParallaxLCD::clear() {
    write(12);
    delay(5);
}

/**
 * Turns the backlight on and off.
 * 
 * @author nedwidek (2012/07/01)
 *  
 * @param on Backlight on when true. 
 */
void ParallaxLCD::backlight(bool on) {
    if (on) {
        write(17);
    } else {
        write(18);
    }
}

/**
 * Sets the display mode.
 * 
 * @author nedwidek (2012/07/01)
 *  
 * @param on Turns the display on when true. 
 * @param cursor Turns the cursor on when true. 
 * @param blink The cursor (if visible) will blink when true. 
 */
void ParallaxLCD::displayMode(bool on, bool cursor, bool blink) {
    if (!on) {
        write(21);
    } else {
        int mode = 22;
        if (cursor) {
            mode+=2;
        }
        if (blink) {
            mode++;
        }
        write(mode);
    }
}

/**
 * Moves the cursor to the given position. There is no bounds 
 * checking! Use only the maximums allowed by your LCD (zero 
 * indexed). 
 * 
 * @author nedwidek (2012/07/01)
 *  
 * @param row The row where the cursor should be placed, zero
 *            indexed. 
 * @param col The column where the cursor should be placed, zero
 *            indexed.
 */
void ParallaxLCD::moveCursor(int row, int col) {
    int mode = 128;
    mode += row * 20;
    mode += col;
    write(mode);
}

/**
 * Define one of the 8 custom characters.
 * 
 * @author nedwidek (2012/07/01)
 *  
 * @param custom The zero indexed custom character to create. 
 *               [0...7]
 * @param data The array containing the row data for the custom 
 *             character. Each custom character is 8 rows by 5
 *             columns. Refer to datasheet for more details.
 */
void ParallaxLCD::defineCustom(int custom, byte data[]) {
    write(custom+248);
    for (int i=0; i<8; i++) {
        write(data[i]);
    }
}

/**
 * Display one of the custom defined characters at the current 
 * cursor position. 
 * 
 * @author nedwidek (2012/07/01)
 *  
 * @param on The zero indexed custom character to display 
 *           [0...7]
 */
void ParallaxLCD::displayCustom(int custom) {
    write(custom);
}


/**
 * Sets the lenth of the note to play to a 64th.
 * 
 * @author nedwidek (2012/07/01)
 * 
 */
void ParallaxLCD::set64thNote() {
    setNoteLength(0);
}

/**
 * Sets the lenth of the note to play to a 32nd.
 * 
 * @author nedwidek (2012/07/01)
 * 
 */
void ParallaxLCD::set32ndNote() {
    setNoteLength(1);
}

/**
 * Sets the lenth of the note to play to a 16th.
 * 
 * @author nedwidek (2012/07/01)
 * 
 */
void ParallaxLCD::set16thNote() {
    setNoteLength(2);
}

/**
 * Sets the lenth of the note to play to a 8th.
 * 
 * @author nedwidek (2012/07/01)
 * 
 */
void ParallaxLCD::set8thNote() {
    setNoteLength(3);
}

/**
 * Sets the lenth of the note to play to a quarter.
 * 
 * @author nedwidek (2012/07/01)
 * 
 */
void ParallaxLCD::setQuarterNote() {
    setNoteLength(4);
}

/**
 * Sets the lenth of the note to play to a half.
 * 
 * @author nedwidek (2012/07/01)
 * 
 */
void ParallaxLCD::setHalfNote() {
    setNoteLength(5);
}

/**
 * Sets the lenth of the note to play to a full.
 * 
 * @author nedwidek (2012/07/01)
 * 
 */
void ParallaxLCD::setFullNote() {
    setNoteLength(6);
}

/**
 * Sets the 3rd scale.
 * 
 * @author nedwidek (2012/07/01)
 * 
 */
void ParallaxLCD::setScale3() {
    setScale(0);
}

/**
 * Sets the 4th scale.
 * 
 * @author nedwidek (2012/07/01)
 * 
 */
void ParallaxLCD::setScale4() {
    setScale(1);
}

/**
 * Sets the 5th scale.
 * 
 * @author nedwidek (2012/07/01)
 * 
 */
void ParallaxLCD::setScale5() {
    setScale(2);
}

/**
 * Sets the 6th scale.
 * 
 * @author nedwidek (2012/07/01)
 * 
 */
void ParallaxLCD::setScale6() {
    setScale(3);
}

/**
 * Sets the 7th scale.
 * 
 * @author nedwidek (2012/07/01)
 * 
 */
void ParallaxLCD::setScale7() {
    setScale(4);
}

/**
 * Once scale and length have been set, we can now play a given 
 * note. 
 * 
 * @author nedwidek (2012/07/01)
 *  
 * @param note The note to play. Use the constants defined in 
 *             the .h file. A, A_SHARP, B, C, C_SHARP, D,
 *             D_SHARP, E, F, F_SHARP, G, G_SHARP, and PAUSE
 *             (rest).
 *  
 *  
 *  
 */
void ParallaxLCD::playNote(int note) {
    write(note);
}

/**
 * Sets the scale of the note to play. Easier to use one of the 
 * convenience methods. 
 * 
 * @author nedwidek (2012/07/01)
 *  
 * @param scale The scale to play [3...7].
 */
void ParallaxLCD::setScale(int scale) {
    write(scale + 215);
}

/**
 * Sets the lenth of the note to play. Easier to use one of the 
 * convenience methods. 
 * 
 * @author nedwidek (2012/07/01)
 *  
 * @param len The value of the note length as defined in the 
 *            datasheet. Use a zero indexed offset from 208
 *            (64th note).
 */
void ParallaxLCD::setNoteLength(int len) {
    write(len + 208);
}
