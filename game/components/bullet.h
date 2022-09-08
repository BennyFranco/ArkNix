#ifndef BULLET_H
#define BULLET_H

#include "component.h"

namespace galaga {
    class Bullet : public nim::Component {
    public:
        Bullet();
        Bullet(nim::Direction dir);
        Bullet(const Bullet &other);
        Bullet(Bullet &&other);
        ~Bullet();

        Bullet &operator=(const Bullet &other);
        Bullet &operator=(Bullet &&other);

        virtual void Update() override;
        virtual void OnCollisionEnter(const nim::GameObject &other) override;

    public:
        nim::Direction direction = nim::Direction::Up;
    };
}// namespace galaga
#endif//BULLET_H