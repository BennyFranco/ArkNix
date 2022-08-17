#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "component.h"
#include "entity.h"
#include <initializer_list>
#include <string>
#include <unordered_map>

namespace nim {
    class GameObject : public Entity, public Transform {
    public:
        GameObject();
        GameObject(const char *name);
        GameObject(const char *name, std::initializer_list<Component *> components);
        virtual void Init() override {}
        virtual void Update() override;
        virtual void Quit() override {}

        void AddComponent(const char *id, Component *component);
        Component *GetComponent(const char *id);

    public:
        std::string name;

    private:
        std::unordered_map<std::string, Component *> components;
    };
}// namespace nim
#endif//GAME_OBJECT_H