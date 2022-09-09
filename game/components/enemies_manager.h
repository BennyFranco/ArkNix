#ifndef ENEMIES_MANAGER_H
#define ENEMIES_MANAGER_H

#include "animation_component.h"
#include "component.h"
#include "types.h"

namespace galaga {
    class EnemiesManager : public nim::Component {
    public:
        EnemiesManager();
        EnemiesManager(const EnemiesManager &other);
        EnemiesManager(EnemiesManager &&other);
        ~EnemiesManager() override = default;

        EnemiesManager &operator=(const EnemiesManager &other);
        EnemiesManager &operator=(EnemiesManager &&other);

        void Init() override;
        void Update() override;

    private:
        void CreateGrid();
        std::string GenerateEnemyName();
        nim::AnimationComponent GenerateEnemy();
        nim::AnimationComponent GenerateAlan();
        nim::AnimationComponent GenerateBonBon();
        nim::AnimationComponent GenerateLips();

    public:
        static uint enemiesLeft;

    private:
        const uint columns = 12;
        const uint rows = 4;
        const float spriteSize = 48;
        const float offsetX = 48;
        const float offsetY = 48;
        //uint enemiesLeft = 0;
    };
}// namespace galaga
#endif// ENEMIES_MANAGER_H