#include "sound.h"

using namespace nim;

Sound::Sound() {
    audioSystem = dynamic_cast<SDLAudio *>(AudioLocator::GetAudio());
}

Sound::Sound(const char *id, const char *filename) {
    audioSystem = dynamic_cast<SDLAudio *>(AudioLocator::GetAudio());
    this->id = id;
    sound.reset(Mix_LoadWAV(filename), [](Mix_Chunk *chunkSound) { Mix_FreeChunk(chunkSound); });
    this->filename = filename;
}

Sound::Sound(const Sound &other) {
    id = other.id;
    filename = other.filename;
    sound = other.sound;
    audioSystem = other.audioSystem;
}

Sound::Sound(Sound &&other) noexcept {
    id = std::move(other.id);
    filename = std::move(other.filename);
    sound = std::move(other.sound);
    audioSystem = other.audioSystem;

    other.audioSystem = nullptr;
}

Sound::~Sound() = default;

Sound &Sound::operator=(const Sound &other) {
    if (&other != this) {
        id = other.id;
        filename = other.filename;
        sound = other.sound;
        audioSystem = other.audioSystem;
    }

    return *this;
}

Sound &Sound::operator=(Sound &&other) noexcept {
    if (&other != this) {
        id = std::move(other.id);
        filename = std::move(other.filename);
        sound = std::move(other.sound);
        audioSystem = other.audioSystem;
        other.audioSystem = nullptr;
    }
    return *this;
}

void Sound::Play() {
    audioSystem->Play(*sound);
}
bool Sound::IsPlaying() {
    return Mix_Playing(-1) != 0;
}
