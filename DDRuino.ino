/*@ file DDRunino.ino
 * 
 * Simple Arduino sketch to run a DDR pad as a keyboard
 * 
 * https://git.beesbuzz.biz/fluffy/DDRuino/
 */

#include <Keyboard.h>

// Uncomment this to enable the serial debugger to determine the pin mappings
//#define DEBUG

struct Input {
    int pin;
    int keyCode;
    bool state;
};

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
    Serial.begin(9600);

#ifdef DEBUG
    for (int i = 0; i < 12; i++) {
      pinMode(i, INPUT_PULLUP);
    }
#endif

    for (auto i : mapping) {
        pinMode(i.pin, INPUT_PULLUP);
        i.state = HIGH;
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
        bool val = !digitalRead(i.pin);
        if (val != i.state) {
            if (val) {
                // TODO debounce
                Keyboard.press(i.keyCode);
            } else {
                Keyboard.release(i.keyCode);
            }

            i.state = val;
        }
    }
}
