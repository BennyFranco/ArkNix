#include "audio_locator.h"

using namespace nim;

std::unique_ptr<Audio> AudioLocator::audio;

Audio *AudioLocator::GetAudio() { return audio.get(); }

void AudioLocator::Initialize() {
    audio = std::make_unique<SDLAudio>();
    audio->Init();
}