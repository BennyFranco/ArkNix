#include "input_locator.h"

std::unique_ptr<Input> InputLocator::input;

void InputLocator::Initialize() {
    input = std::make_unique<SDLInput>();
    input->Init();
}