#ifndef COLLISION_LAYER_H
#define COLLISION_LAYER_H
#include "types.h"

namespace nim {
    enum Layer : uint {
        None = 0u,
        Enemy = 1 << 0,
        Player = 1 << 1,
        Bullet = 1 << 2
    };
}
#endif