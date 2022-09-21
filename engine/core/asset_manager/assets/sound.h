#ifndef SOUND_H
#define SOUND_H

#include "asset_manager.h"
#include "audio_locator.h"

#include "SDL_mixer.h"

namespace nim {
    class Sound : public Asset {
    public:
        Sound();
        Sound(const char *id, const char *filename);
        Sound(const Sound &other);
        Sound(Sound &&other) noexcept;
        ~Sound();

        Sound &operator=(const Sound &other);
        Sound &operator=(Sound &&other) noexcept;

        void Play();
        bool IsPlaying();

    private:
        std::shared_ptr<Mix_Chunk> sound;
        SDLAudio *audioSystem;
    };
}// namespace nim
#endif//SOUND_H