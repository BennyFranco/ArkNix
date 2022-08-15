#ifndef INPUT_SERVICE_LOCATOR_H
#define INPUT_SERVICE_LOCATOR_H

#include "input.h"
#include "sdl_input.h"
#include <memory>

class InputLocator {
public:
    static Input *GetInput() { return input.get(); }
    static void Initialize();

private:
    static std::unique_ptr<Input> input;
};
#endif// INPUT_SERVICE_LOCATOR_H