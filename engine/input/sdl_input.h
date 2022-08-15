#ifndef SDL_INPUT_H
#define SDL_INPUT_H

#include "events/action.h"
#include "input.h"
#include <SDL.h>

class SDLInput : public Input {
public:
    void Init() override;
    void Update() override;
    void Quit() override;
    bool GetKeyDown(Key key) override;
    bool GetKeyUp(Key key) override;

private:
    void PrintDebugKey(SDL_Event *event);
    SDL_KeyCode ConvertNimKeyToSDLKey(Key key);

private:
    // https://wiki.libsdl.org/SDL_Event
    SDL_Event event;
};
#endif// SDL_INPUT_H