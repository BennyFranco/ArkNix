#include "collision_detector.h"
#include <iostream>

using namespace nim;

CollisionDetector::CollisionDetector() {
    collisionMatrix[Layer::None] = 0;
    collisionMatrix[Layer::Player] = Layer::Enemy;
    collisionMatrix[Layer::Enemy] = Layer::Bullet | Layer::Player;
    collisionMatrix[Layer::Bullet] = Layer::Player;
}

CollisionDetector &CollisionDetector::Instance() {
    static std::unique_ptr<CollisionDetector> instance{new CollisionDetector()};
    return *instance;
}

void CollisionDetector::Update(const std::list<GameObject> &gameObjects) {
    for (auto aIt = gameObjects.begin(); aIt != gameObjects.end(); aIt++) {
        if (aIt->collisionLayer == Layer::None) continue;

        auto collisionLayers = collisionMatrix[aIt->collisionLayer];
        for (auto bIt = std::next(aIt); bIt != gameObjects.end(); bIt++) {

            if (!(bIt->collisionLayer & collisionLayers)) continue;

            if (TestCollision(aIt->transform->GetBounds(), bIt->transform->GetBounds())) {
                std::cout << "Collision: [" << aIt->name << "] & [" << bIt->name << "] \n";
                bIt->OnCollisionEnter(*aIt);
            }
        }
    }
}

bool CollisionDetector::TestCollision(const Bounds &a, const Bounds &b) {
    if (a.bottom <= b.bottom) return false;
    if (a.top >= b.bottom) return false;
    if (a.right <= b.left) return false;
    if (a.left >= b.right) return false;

    return true;
}