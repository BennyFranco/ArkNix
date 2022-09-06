#ifndef SDL_AUDIO_H
#define SDL_AUDIO_H

#include "audio.h"
#include <SDL.h>
#include <SDL_mixer.h>

namespace nim {
    class SDLAudio : public Audio {
    public:
        void Init() override;
        void Quit() override;
        void Play(Mix_Chunk &sound, int channel = -1, int loops = 0);
        void Play(Mix_Music &music, int loops = -1);
        void Pause();
        void ResumeMusic();
        void Stop();

    private:
        bool initialized = true;
    };
}// namespace nim
#endif// SDL_AUDIO_H