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
    size_t len = components.size();
    for (size_t i = 0; i < len; i++)
        components[i]->Start();
    
    started = true;
}

void GameObject::Update(float dt) {
    size_t len = components.size();
    for (size_t i = 0; i < len; i++) {
        size_t pos = len - i - 1;
        if (!components[pos]->IsDestroyed()) {
            components[pos]->Update(dt);
        } else {
            components.erase(components.begin() + pos);
        }
    }
}

void GameObject::Render() {
    size_t len = components.size();
    for (size_t i = 0; i < len; i++) {
        components[i]->Render();
    }
}

void GameObject::AddComponent(Component* cpt) {
    components.emplace_back(cpt);
    if (started)
        cpt->Start();
}

void GameObject::RemoveComponent(Component* cpt) {
    size_t len = components.size();
    for (size_t i = 0; i < len; i++) {
        size_t pos = len - i - 1;
        if (components[pos].get() == cpt) {
            components.erase(components.begin() + pos);
            return;
        }
    }
}

Component* GameObject::GetComponent(const string& type) const {
    size_t len = components.size();
    for (size_t i = 0; i < len; i++) {
        if (components[i]->Is(type)) {
            return components[i].get();
        }
    }
    return nullptr;
}

set<string> GameObject::HasComponentsOfTypes(set<string> types) const {
    set<string> result;

    size_t leni = components.size();
    for (size_t i = 0; i < leni; i++) {
        for (auto j = types.begin(); j != types.end();) {
            if (components[i]->Is(*j)) {
                result.insert(*j);
                j = types.erase(j);
                continue;
            }
            j++;
        }
    }

    return result;
}

void GameObject::NotifyCollision(GameObject& other) const {
    size_t len = components.size();
    for (size_t i = 0; i < len; i++) {
        components[i]->NotifyCollision(other);
    }
}