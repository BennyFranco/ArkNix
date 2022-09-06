#include "music.h"

using namespace nim;

Music::Music() {
    audioSystem = dynamic_cast<SDLAudio *>(AudioLocator::GetAudio());
}

Music::Music(const char *id, const char *filename) {
    audioSystem = dynamic_cast<SDLAudio *>(AudioLocator::GetAudio());
    this->id = id;
    music.reset(Mix_LoadMUS(filename), [](Mix_Music *sound) { Mix_FreeMusic(sound); });
    this->filename = filename;
}

Music::Music(const Music &other) {
    id = other.id;
    filename = other.filename;
    music = other.music;
    audioSystem = other.audioSystem;
}

Music::Music(Music &&other) noexcept {
    id = std::move(other.id);
    filename = std::move(other.filename);
    music = std::move(other.music);
    audioSystem = other.audioSystem;
    other.audioSystem = nullptr;
}

Music::~Music() = default;

Music &Music::operator=(const Music &other) {
    if (&other != this) {
        id = other.id;
        filename = other.filename;
        music = other.music;
        audioSystem = other.audioSystem;
    }

    return *this;
}

Music &Music::operator=(Music &&other) noexcept {
    if (&other != this) {
        id = std::move(other.id);
        filename = std::move(other.filename);
        music = std::move(other.music);
        audioSystem = other.audioSystem;
        other.audioSystem = nullptr;
    }
    return *this;
}

void Music::Play() {
    audioSystem->Play(*music);
}

void Music::Pause() {
    audioSystem->Pause();
}

void Music::Resume() {
    audioSystem->ResumeMusic();
}

void Music::Stop() {
    audioSystem->Stop();
}