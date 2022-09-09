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
        EnemiesManager(EnemiesManager &&other) noexcept;
        ~EnemiesManager() override = default;

        EnemiesManager &operator=(const EnemiesManager &other);
        EnemiesManager &operator=(EnemiesManager &&other) noexcept;

        void Init() override;
        void Update() override;

        inline void SetRows(uint nRows) { rows = nRows; }
        inline void SetColumns(uint nCols) { columns = nCols; }

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
        uint columns;
        uint rows;
        const float spriteSize = 48;
        const float offsetX = 48;
        const float offsetY = 48;
        bool prepareForTransition = false;
    };
}// namespace galaga

namespace YAML {
    template<>
    struct convert<galaga::EnemiesManager *> {
        static YAML::Node encode(const galaga::EnemiesManager *component) {
            YAML::Node node;
            // TODO: Implement encoder for galaga::EnemiesManager *
            return node;
        }
    };
    template<>
    struct convert<galaga::EnemiesManager> {
        static bool decode(const YAML::Node &node, galaga::EnemiesManager &component) {
            if (!node["name"]) return false;
            galaga::EnemiesManager enemiesManager;
            if (node["columns"]) enemiesManager.SetColumns(node["columns"].as<uint>());
            if (node["rows"]) enemiesManager.SetRows(node["rows"].as<uint>());
            component = std::move(enemiesManager);
            return true;
        }
    };
}// namespace YAML
#endif// ENEMIES_MANAGER_H