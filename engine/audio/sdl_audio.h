#ifndef SDL_AUDIO_H
#define SDL_AUDIO_H

#include "audio.h"
#include <SDL.h>
#include <SDL_mixer.h>

namespace nim {
    class SDLAudio : public Audio {
        void Init() override;
        void Quit() override;
    };
}// namespace nim
#endif// SDL_AUDIO_H