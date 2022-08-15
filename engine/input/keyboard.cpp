#include "keyboard.h"

bool Keyboard::GetKeyDown(Key key) {
    return InputLocator::GetInput()->GetKeyDown(key);
}

bool Keyboard::GetKeyUp(Key key) {
    return InputLocator::GetInput()->GetKeyUp(key);
}