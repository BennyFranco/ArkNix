#ifndef COLLISION_DETECTOR_H
#define COLLISION_DETECTOR_H

#include "collision_layer.h"
#include "game_object.h"
#include "transform.h"
#include <unordered_map>

namespace nim {
    class CollisionDetector {
    public:
        static CollisionDetector &Instance();
        void Update(const std::vector<GameObject> &gameObjects);
        bool TestCollision(const Bounds &a, const Bounds &b);

    public:
        std::unordered_map<Layer, uint> collisionMatrix;

    private:
        CollisionDetector();
    };
}// namespace nim
#endif//COLLISION_DETECTOR_H