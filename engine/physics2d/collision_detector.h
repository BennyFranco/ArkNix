#ifndef COLLISION_DETECTOR_H
#define COLLISION_DETECTOR_H

#include "collision_layer.h"
#include "game_object.h"
#include "transform.h"

namespace nim {
    class CollisionDetector {
    public:
        static CollisionDetector &Instance();
        void Update(const std::vector<GameObject> &gameObjects);
        bool TestCollision(const Bounds &a, const Bounds &b);

    public:
        Layer player = Layer::Enemy;
        uint enemies = Layer::Bullet | Layer::Player;
        Layer bullet = Layer::Enemy;

    private:
        CollisionDetector() {}
    };
}// namespace nim
#endif//COLLISION_DETECTOR_H