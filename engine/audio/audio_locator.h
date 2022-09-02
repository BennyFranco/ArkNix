#ifndef AUDIO_LOCATOR_H
#define AUDIO_LOCATOR_H

#include "audio.h"
#include "sdl_audio.h"
#include <memory>

namespace nim {
    class AudioLocator {
    public:
        static Audio *GetAudio();
        static void Initialize();

    private:
        static std::unique_ptr<Audio> audio;
    };
}// namespace nim
#endif// AUDIO_LOCATOR_H