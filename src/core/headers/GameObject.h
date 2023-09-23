#pragma once

#include <vector>
#include <memory>

#include "../../utils/headers/Rect.h"
class Component; // Only here to resolve circular dependency.

class GameObject {
public:
    GameObject();
    ~GameObject();

    void Update(float dt);
    void Render();
    bool IsDestroyed() const;
    void Destroy();
    void AddComponent(Component* cpt);
    void RemoveComponent(Component* cpt);
    Component* GetComponent(const std::string& type) const;
    std::vector<Component*> GetAllComponents() const;

    Rect box;

private:
    std::vector< std::unique_ptr<Component> > components;
    bool destroyRequested;
};

inline bool GameObject::IsDestroyed() const {
    return destroyRequested;
}

inline void GameObject::Destroy() {
    destroyRequested = true;
}