/*@ file DDRunino.ino
 *
 * Simple Arduino sketch to run a DDR pad as a keyboard
 *
 * https://git.beesbuzz.biz/fluffy/DDRuino/
 */

#include <Keyboard.h>

//! Uncomment this to enable the serial debugger to determine the pin mappings
//#define DEBUG

//! Debounce time in milliseconds
constexpr int debounceTime = 20;

//! Input button
struct Input {
    int pin;        //!< Input pin
    int keyCode;    //!< Mapped key
    bool pressed;   //!< Last read state
    unsigned long lastChange;   //!< Last update time
};

/*! Map the input pins to a button on the pad; use debug mode to determine
 *  your button layout if you're not sure
 */
Input mapping[] = {
    { 4, KEY_RETURN },
    { 5, KEY_ESC },
    { 6, KEY_UP_ARROW },
    { 7, KEY_DOWN_ARROW },
    { 8, KEY_RIGHT_ARROW },
    { 9, KEY_LEFT_ARROW },
};

void setup()
{
#ifdef DEBUG
    Serial.begin(9600);

    for (int i = 0; i < 12; i++) {
      pinMode(i, INPUT_PULLUP);
    }
#endif

    unsigned long now = millis();

    for (auto i : mapping) {
        pinMode(i.pin, INPUT_PULLUP);
        i.pressed = false;
        i.lastChange = now;
    }

    Keyboard.begin();
}

void loop()
{
#ifdef DEBUG
    for (int i = 0; i < 12; i++) {
      Serial.print(!digitalRead(i) ? "0123456789abcdef"[i] : ' ');
    }
    Serial.print('\n');
#endif

    for (auto& i : mapping) {
        unsigned long now = millis();
        bool val = !digitalRead(i.pin);
        if (val != i.pressed && (i.lastChange + debounceTime) < now) {
            if (val) {
                Keyboard.press(i.keyCode);
            } else {
                Keyboard.release(i.keyCode);
            }

            i.pressed = val;
            i.lastChange = now;
        }
    }
}
