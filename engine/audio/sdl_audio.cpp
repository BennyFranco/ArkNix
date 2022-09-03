#include "sdl_audio.h"
#include <iostream>

using namespace nim;

void SDLAudio::Init() {
    if (SDL_InitSubSystem(SDL_INIT_AUDIO) < 0) {
        std::cout << "[SDLAudio] Cannot be initialized. Error: " << SDL_GetError() << "\n";
        return;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cout << "[SDL_mixer] Cannot be initialized. Error: " << Mix_GetError() << "\n";
        return;
    }
}

void SDLAudio::Quit() {
    Mix_Quit();
    SDL_QuitSubSystem(SDL_INIT_AUDIO);
}


void SDLAudio::Play(Mix_Chunk &sound, int channel, int loops) {
    Mix_PlayChannel(channel, &sound, loops);
}

void SDLAudio::Play(Mix_Music &music, int loops) {
    Mix_PlayMusic(&music, loops);
}

void SDLAudio::Pause() {
    Mix_PauseMusic();
}

void SDLAudio::ResumeMusic() {
    Mix_ResumeMusic();
}

void SDLAudio::Stop() {
    Mix_HaltMusic();
}