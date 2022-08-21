#ifndef GALAGA_H
#define GALAGA_H

#include "game.h"

class Galaga : public nim::Game {
public:
    void Awake() override;
};
#endif//GALAGA_H