#ifndef MUSIC_H
#define MUSIC_H

#include "asset_manager.h"
#include "audio_locator.h"

#include "SDL_mixer.h"

namespace nim {
    class Music : public Asset {
    public:
        Music();
        Music(const char *id, const char *filename);
        Music(const Music &other);
        Music(Music &&other) noexcept;
        ~Music();

        Music &operator=(const Music &other);
        Music &operator=(Music &&other) noexcept;

        void Play();
        void Pause();
        void Resume();
        void Stop();

    private:
        std::shared_ptr<Mix_Music> music;
        SDLAudio *audioSystem;
    };
}// namespace nim

#endif//MUSIC_H
