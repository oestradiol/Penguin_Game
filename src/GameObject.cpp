#include <algorithm>
using namespace std;

#include "h_files/GameObject.h"
#include "h_files/Component.h"

GameObject::GameObject()
    : isDead(false) { }

GameObject::~GameObject() {
    components.clear();
}

void GameObject::Update(float dt) {
    for (auto& component : components) {
        component->Update(dt);
    }
}

void GameObject::Render() {
    for (auto& component : components) {
        component->Render();
    }
}

bool GameObject::IsDead() const {
    return isDead;
}

void GameObject::RequestDelete() {
    isDead = true;
}

void GameObject::AddComponent(Component* cpt) {
    components.emplace_back(cpt);
}

void GameObject::RemoveComponent(Component* cpt) {
    size_t len = components.size() - 1;
    for (size_t i = 0; i <= len; i++) {
        size_t pos = len - i;
        if (components[pos].get() == cpt) {
            components.erase(components.begin() + pos);
            return;
        }
    }
}

Component* GameObject::GetComponent(const string& type) const {
    for (auto& component : components) {
        if (component->Is(type)) {
            return component.get();
        }
    }
    return nullptr;
}

std::vector<Component*> GameObject::GetAllComponents() const {
    std::vector<Component*> result;
    result.resize(components.size());
    for (auto& component : components) {
        result.push_back(component.get());
    }
    return result;
}