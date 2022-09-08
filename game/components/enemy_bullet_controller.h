#ifndef ENEMY_BULLET_CONTROLLER_H
#define ENEMY_BULLET_CONTROLLER_H

#include "component.h"

namespace galaga {

    class EnemyBulletController : public nim::Component {
    public:
        EnemyBulletController();
        EnemyBulletController(const EnemyBulletController &other);
        EnemyBulletController(EnemyBulletController &&other) noexcept;
        ~EnemyBulletController();

        EnemyBulletController &operator=(const EnemyBulletController &other);
        EnemyBulletController &operator=(EnemyBulletController &&other) noexcept;

        void Update() override;
        void Fire();
    };

}// namespace galaga

#endif//ENEMY_BULLET_CONTROLLER_H
