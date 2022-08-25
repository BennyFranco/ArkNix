#ifndef N_TIME_H
#define N_TIME_H
#include "SDL.h"
#include "types.h"
#include <memory>

namespace nim {
    class NimTime {
    public:
        static NimTime &Instance() {
            static std::unique_ptr<NimTime> instance{new NimTime()};
            return *instance;
        }
        uint GetTicks() { return SDL_GetTicks64(); }

    private:
        NimTime() {}
    };
}// namespace nim
#endif// N_TIME_H