#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "component.h"
#include "entity.h"
#include <initializer_list>
#include <memory>
#include <string>
#include <vector>

namespace nim {
    class GameObject : public Entity {
    public:
        GameObject();
        GameObject(std::string name);
        GameObject(std::string name, Transform transform);
        // GameObject(const char *name, std::initializer_list<Component *> components);
        GameObject(const GameObject &other);
        GameObject(GameObject &&other);
        ~GameObject();

        GameObject &operator=(const GameObject &other);
        GameObject &operator=(GameObject &&other);

        virtual void Init() override;
        virtual void Update() override;
        virtual void Quit() override;

        void AddComponent(std::shared_ptr<Component> component);
        // Component *GetComponent(const char *id);
        std::vector<std::shared_ptr<Component>> Components() const { return components; }

        static void Destroy(const GameObject *go);
        static void Destroy(const GameObject *go, const uint msToDestroyIt);
        static GameObject *Instantiate(std::string name, Transform transform, std::shared_ptr<Component> component);
        static GameObject *Instantiate(GameObject &&go);
        static GameObject *Instantiate(std::string name, Transform transform,
                                       std::initializer_list<std::shared_ptr<Component>> newComponents);

    public:
        std::string name;
        std::shared_ptr<Transform> transform;

    private:
        std::vector<std::shared_ptr<Component>> components;
    };
}// namespace nim
#endif//GAME_OBJECT_H