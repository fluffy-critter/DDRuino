#include <Keyboard.h>

struct Input {
    int pin;
    int keyCode;
    bool state;
};

Input mapping[] = {
    { 1, KEY_RETURN },
    { 2, KEY_ESC },
    { 3, KEY_UP_ARROW },
    { 4, KEY_DOWN_ARROW },
    { 5, KEY_RIGHT_ARROW },
    { 6, KEY_LEFT_ARROW },
};

void setup()
{
    for (auto i : mapping) {
        pinMode(i.pin, INPUT_PULLUP);
        i.state = false;
    }

    Keyboard.begin();
}

void loop()
{
    for (auto& i : mapping) {
        bool val = digitalRead(i.pin);
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
