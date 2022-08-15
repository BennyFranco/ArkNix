#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "input_locator.h"

class Keyboard {
public:
    static bool GetKeyDown(Key key);
    static bool GetKeyUp(Key key);
};

#endif// KEYBOARD_H