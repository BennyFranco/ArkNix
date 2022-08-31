#ifndef ENEMIES_MANAGER_H
#define ENEMIES_MANAGER_H

#include "component.h"
#include "types.h"

namespace galaga {
    enum class EnemyType {
        Alan,
        BonBon,
        Lips
    };

    class EnemiesManager : public nim::Component {
    public:
        EnemiesManager();
        EnemiesManager(const EnemiesManager &other);
        EnemiesManager(EnemiesManager &&other);
        ~EnemiesManager();

        EnemiesManager &operator=(const EnemiesManager &other);
        EnemiesManager &operator=(EnemiesManager &&other);

        virtual void Init() override;
        virtual void Update() override;

    private:
        void CreateGrid();
        std::string GenerateEnemyName();

    private:
        const uint rowSize = 12;
        const float spriteSize = 48;
        const float offsetX = 48;
    };
}// namespace galaga
#endif// ENEMIES_MANAGER_H