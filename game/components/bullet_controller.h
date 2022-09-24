#ifndef BULLET_CONTROLLER_H
#define BULLET_CONTROLLER_H

#include "component.h"
#include "input_locator.h"
#include "sound_component.h"

namespace galaga {
    class BulletController : public nim::Component {
    public:
        BulletController();
        BulletController(const BulletController &other);
        BulletController(BulletController &&other) noexcept;
        ~BulletController() override;

        BulletController &operator=(const BulletController &other);
        BulletController &operator=(BulletController &&other) noexcept;

        void Init() override;
        void Update() override;

        void Fire();

    private:
        nim::Input *input;// owned by input locator;
        nim::SoundComponent<nim::Sound> *shoot{};
    };
}// namespace galaga
#endif//BULLET_CONTROLLER_H