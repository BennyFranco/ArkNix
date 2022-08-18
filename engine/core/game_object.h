#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "component.h"
#include "entity.h"
#include <initializer_list>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace nim {
    class GameObject : public Entity {
    public:
        GameObject();
        GameObject(const char *name);
        // GameObject(const char *name, std::initializer_list<Component *> components);
        GameObject(const GameObject &other);
        GameObject(GameObject &&other);
        ~GameObject();

        GameObject &operator=(const GameObject &other);
        GameObject &operator=(GameObject &&other);

        virtual void Init() override {}
        virtual void Update() override;
        virtual void Quit() override {}

        void AddComponent(std::shared_ptr<Component> component);
        // Component *GetComponent(const char *id);

    public:
        std::string name;
        std::unique_ptr<Transform> transform;

    private:
        std::vector<std::shared_ptr<Component>> components;
    };
}// namespace nim
#endif//GAME_OBJECT_H