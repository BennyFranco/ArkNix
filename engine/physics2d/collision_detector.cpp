#include "collision_detector.h"
#include <iostream>

using namespace nim;

CollisionDetector &CollisionDetector::Instance() {
    static std::unique_ptr<CollisionDetector> instance{new CollisionDetector()};
    return *instance;
}

void CollisionDetector::Update(const std::vector<GameObject> &gameObjects) {
    for (auto aIt = gameObjects.begin(); aIt != gameObjects.end(); aIt++) {
        if (aIt->collisionLayer == Layer::None) continue;
        for (auto bIt = aIt + 1; bIt != gameObjects.end(); bIt++) {
            if (TestCollision(aIt->transform->GetBounds(), bIt->transform->GetBounds())) {
                std::cout << "Collision: [" << aIt->name << "] & [" << bIt->name << "] \n";
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