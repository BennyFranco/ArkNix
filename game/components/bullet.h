#ifndef BULLET_H
#define BULLET_H

#include "component.h"

namespace galaga {
    class Bullet : public nim::Component {
    public:
        Bullet();
        Bullet(const Bullet &other);
        Bullet(Bullet &&other);
        ~Bullet();

        Bullet &operator=(const Bullet &other);
        Bullet &operator=(Bullet &&other);

        virtual void Update() override;
    };
}// namespace galaga
#endif//BULLET_H