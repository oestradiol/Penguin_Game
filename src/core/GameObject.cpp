#include <algorithm>
using namespace std;

#include "../components/headers/Component.h"
#include "headers/GameObject.h"
#include "headers/Camera.h"

GameObject::GameObject()
    : started(false), destroyRequested(false) { }

GameObject::~GameObject() {
    Camera::Unfollow(this);
    components.clear();
}

void GameObject::Start() {
    for (const auto& component : components)
        component->Start();
    
    started = true;
}

void GameObject::Update(float dt) {
    size_t len = components.size() - 1;
    for (size_t i = 0; i <= len; i++) {
        size_t pos = len - i;
        if (!components[pos]->IsDestroyed()) {
            components[pos]->Update(dt);
        } else {
            components.erase(components.begin() + pos);
        }
    }
}

void GameObject::Render() {
    for (auto& component : components) {
        component->Render();
    }
}

void GameObject::AddComponent(Component* cpt) {
    components.emplace_back(cpt);
    if (started)
        cpt->Start();
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
    for (const auto& component : components) {
        if (component->Is(type)) {
            return component.get();
        }
    }
    return nullptr;
}

vector<Component*> GameObject::GetAllComponents() const {
    vector<Component*> result;
    result.resize(components.size());
    for (auto& component : components) {
        result.push_back(component.get());
    }
    return result;
}