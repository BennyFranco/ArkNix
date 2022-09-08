#ifndef GALAGA_H
#define GALAGA_H

#include "game.h"

namespace galaga {
    class Galaga : public nim::Game {
    public:
        static Galaga &Instance();
        void Awake() override;

    private:
        Galaga() = default;
    };
}// namespace galaga
#endif//GALAGA_H