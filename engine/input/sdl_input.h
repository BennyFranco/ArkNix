#ifndef SDL_INPUT_H
#define SDL_INPUT_H

#include "input.h"
#include <SDL.h>

namespace nim {
    class SDLInput : public Input {
    public:
        void Init() override;
        void Update() override;
        void Quit() override;
        bool GetKey(Key key) override;
        bool GetKeyDown(Key key) override;
        bool GetKeyUp(Key key) override;

    private:
        void PrintDebugKey(SDL_Event *event);
        SDL_KeyCode ConvertNimKeyToSDLKey(Key key);

    private:
        // https://wiki.libsdl.org/SDL_Event
        SDL_Event event;
    };
}// namespace nim
#endif// SDL_INPUT_H